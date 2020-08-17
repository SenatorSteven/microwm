/* eventLoop.c

MIT License

Copyright (C) 2019 Stefanos "Steven" Tsakiris

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xrandr.h>
#include "headers/defines.h"
#include "headers/eventLoopDefines.h"
#include "headers/printEvent.h"

#define NoCascadeMode /*----------*/ 0
#define SimpleCascadeMode /*------*/ 1
#define SmartCascadeMode /*-------*/ 2

#define NoAction /*---------------*/ 0
#define MoveAction /*-------------*/ 1
#define ResizeAction /*-----------*/ 2

#define NoSubaction /*------------*/ 0
#define MoveResizeSubaction /*----*/ 1
#define ResizeSubaction /*--------*/ 2



#define NoPointerInfo /*----------*/ 0
#define MapPointerInfo /*---------*/ (1 << 0)
#define MovePointerInfo /*--------*/ (1 << 1)
#define RecascadePointerInfo /*---*/ (1 << 2)

#define GridPointerInfo /*--------*/ (1 << 3)

#define MoveMonitorPointerInfo /*-*/ (1 << 4)



extern const char *programName;
extern Mode mode;
extern Display *display;

typedef uint8_t PointerInfo;

typedef struct{
	uint8_t mode;
	bool overrideGridWindows;
	int offsetX;
	int offsetY;
} Cascade;

typedef struct{
	Window window;
	Window subwindow;
	bool inGrid;
	unsigned int gridX;
	unsigned int gridY;
	unsigned int gridWidth;
	unsigned int gridHeight;
} Container;

static void grabRootKeysButtons(const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button);
static void grabContainerKeysButtons(const Window w, const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button);
static void createGrid(const unsigned int monitorAmount, const unsigned int gridWidth, const unsigned int gridHeight, const ARGB gridSubwindowBorderColor, const ARGB gridSubwindowBackgroundColor, Window *const grid);
static void getGridSlotData(const XRRMonitorInfo monitorInfo, const unsigned int gridX, const unsigned int gridY, const unsigned int gridWidth, const unsigned int gridHeight, int *const x, int *const y, unsigned int *const width, unsigned int *const height);
static XRRMonitorInfo getPointerMonitorInfo(void);
static XRRMonitorInfo getWindowMonitorInfo(const Window w);
static void clearWindowProperties(const Window w);
static void copyWindowProperties(const Window source, const Window destination);

void eventLoop(void){
	ManagementMode managementMode = FloatingManagementMode;



	Options option = NoOptions;
	option = AllowGridBoundaryBreakXOption | AllowGridBoundaryBreakYOption;



	unsigned int minimumTilingWidth = 20;
	unsigned int minimumTilingHeight = 20;

	bool shouldIncreaseContainers = 0;
	unsigned int containerIncrementAmount = 5;

	Cascade cascade = {
		.mode = SmartCascadeMode,
		.overrideGridWindows = 0,
		.offsetX = 20,
		.offsetY = 20
	};

	Window lastCreatedWindow = None;
	unsigned int defaultContainerAmount = 5;
	unsigned int containerAmount = defaultContainerAmount;
	unsigned int allocatedContainerAmount = 0;
	XWindowAttributes windowAttributes;

	unsigned int border = 10;
	const unsigned int borders = 2 * border;

	unsigned int innerBorder = 1;
	const unsigned int innerBorders = 2 * innerBorder;

	// ARGB containerBorderColor = 0x0F000000;
	ARGB containerBorderColor = 0x7F000000;
	ARGB containerBackgroundColor = 0xFF00FF00;



	ARGB inGridContainerBackgroundColor = 0xFFFF0000;



	unsigned int gridWidth = 2;
	unsigned int gridHeight = 2;

	PointerInfo pointerInfo = NoPointerInfo;
	pointerInfo = MapPointerInfo | MovePointerInfo | RecascadePointerInfo;

	int x;
	int y;
	// int xpos;
	// int ypos;
	int xtouse;
	int ytouse;
	unsigned int width;
	unsigned int height;

	uint8_t action = NoAction;
	// uint8_t subaction = NoSubaction;

	Container motionContainer;

	bool gridExists = 0;
	bool gridMapped = 0;

	ARGB gridSubwindowBorderColor = 0x10975C57;
	ARGB gridSubwindowBackgroundColor = 0x00000000;

	unsigned int maxGridWidth = 20;
	unsigned int maxGridHeight = 20;



	unsigned int extendWidth = 10;
	unsigned int extendHeight = 10;

	unsigned int shrinkWidth = 10;
	unsigned int shrinkHeight = 10;



	// ARGB focusWindowBorderColor = 0xFFFFFF00;



	unsigned int monitorAmount;
	{
		XRRMonitorInfo *const monitorInfo = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&monitorAmount);
		if(monitorInfo){
			XRRFreeMonitors(monitorInfo);
		}else{
			monitorAmount = 0;
		}
	}



	Window grid[monitorAmount];



	XSelectInput(display, XDefaultRootWindow(display), StructureNotifyMask | SubstructureRedirectMask);



	unsigned int shortcutAmount = 45;
	Shortcut shortcut[shortcutAmount];
	{
		unsigned int currentShortcut = 0;
		shortcut[currentShortcut].keycode = 55;
		shortcut[currentShortcut].masks = Mod4Mask;
		shortcut[currentShortcut].command = FloatingModeCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 56;
		shortcut[currentShortcut].masks = Mod4Mask;
		shortcut[currentShortcut].command = GridModeCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 57;
		shortcut[currentShortcut].masks = Mod4Mask;
		shortcut[currentShortcut].command = TilingModeCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 42;
		shortcut[currentShortcut].masks = Mod4Mask;
		shortcut[currentShortcut].command = ShowGridCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 27;
		shortcut[currentShortcut].masks = Mod4Mask;
		shortcut[currentShortcut].command = RecascadeCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 80;
		shortcut[currentShortcut].masks = ControlMask | Mod1Mask;
		shortcut[currentShortcut].command = MoveTopCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 88;
		shortcut[currentShortcut].masks = ControlMask | Mod1Mask;
		shortcut[currentShortcut].command = MoveBottomCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 83;
		shortcut[currentShortcut].masks = ControlMask | Mod1Mask;
		shortcut[currentShortcut].command = MoveLeftCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 85;
		shortcut[currentShortcut].masks = ControlMask | Mod1Mask;
		shortcut[currentShortcut].command = MoveRightCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 84;
		shortcut[currentShortcut].masks = ControlMask | Mod1Mask;
		shortcut[currentShortcut].command = MoveCenterCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 79;
		shortcut[currentShortcut].masks = ControlMask | Mod1Mask;
		shortcut[currentShortcut].command = MoveTopLeftCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 81;
		shortcut[currentShortcut].masks = ControlMask | Mod1Mask;
		shortcut[currentShortcut].command = MoveTopRightCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 87;
		shortcut[currentShortcut].masks = ControlMask | Mod1Mask;
		shortcut[currentShortcut].command = MoveBottomLeftCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 89;
		shortcut[currentShortcut].masks = ControlMask | Mod1Mask;
		shortcut[currentShortcut].command = MoveBottomRightCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 58;
		shortcut[currentShortcut].masks = Mod4Mask;
		shortcut[currentShortcut].command = MoveNextMonitorCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 58;
		shortcut[currentShortcut].masks = ShiftMask | Mod4Mask;
		shortcut[currentShortcut].command = MovePreviousMonitorCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 39;
		shortcut[currentShortcut].masks = Mod4Mask;
		shortcut[currentShortcut].command = AddWindowToGridCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 26;
		shortcut[currentShortcut].masks = Mod4Mask;
		shortcut[currentShortcut].command = RemoveWindowFromGridCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 38;
		shortcut[currentShortcut].masks = Mod4Mask;
		shortcut[currentShortcut].command = ToggleWindowGridCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 10;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = MoveFirstGridSlotCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 11;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = MoveLastGridSlotCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 111;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = MoveAboveGridSlotCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 116;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = MoveBelowGridSlotCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 114;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = MoveNextGridSlotCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 113;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = MovePreviousGridSlotCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 80;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = ExtendWindowUpCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 88;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = ExtendWindowDownCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 83;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = ExtendWindowLeftCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 85;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = ExtendWindowRightCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 79;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = ExtendWindowUpLeftCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 81;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = ExtendWindowUpRightCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 87;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = ExtendWindowDownLeftCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 89;
		shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask;
		shortcut[currentShortcut].command = ExtendWindowDownRightCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 80;
		shortcut[currentShortcut].masks = ShiftMask | Mod4Mask;
		shortcut[currentShortcut].command = ShrinkWindowUpCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 88;
		shortcut[currentShortcut].masks = ShiftMask | Mod4Mask;
		shortcut[currentShortcut].command = ShrinkWindowDownCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 83;
		shortcut[currentShortcut].masks = ShiftMask | Mod4Mask;
		shortcut[currentShortcut].command = ShrinkWindowLeftCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 85;
		shortcut[currentShortcut].masks = ShiftMask | Mod4Mask;
		shortcut[currentShortcut].command = ShrinkWindowRightCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 79;
		shortcut[currentShortcut].masks = ShiftMask | Mod4Mask;
		shortcut[currentShortcut].command = ShrinkWindowUpLeftCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 81;
		shortcut[currentShortcut].masks = ShiftMask | Mod4Mask;
		shortcut[currentShortcut].command = ShrinkWindowUpRightCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 87;
		shortcut[currentShortcut].masks = ShiftMask | Mod4Mask;
		shortcut[currentShortcut].command = ShrinkWindowDownLeftCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 89;
		shortcut[currentShortcut].masks = ShiftMask | Mod4Mask;
		shortcut[currentShortcut].command = ShrinkWindowDownRightCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 95;
		shortcut[currentShortcut].masks = None;
		shortcut[currentShortcut].command = FullscreenCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 95;
		shortcut[currentShortcut].masks = ShiftMask;
		shortcut[currentShortcut].command = BigscreenCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 24;
		shortcut[currentShortcut].masks = Mod4Mask;
		shortcut[currentShortcut].command = CloseCommand;
		++currentShortcut;
		shortcut[currentShortcut].keycode = 45;
		shortcut[currentShortcut].masks = Mod4Mask;
		shortcut[currentShortcut].command = KillCommand;
	}



	unsigned int buttonAmount = 3;
	Button button[buttonAmount];
	{
		unsigned int currentButton = 0;
		button[currentButton].button = Button4;
		button[currentButton].masks = Mod4Mask;
		button[currentButton].command = EnlargeGridCommand;
		++currentButton;
		button[currentButton].button = Button5;
		button[currentButton].masks = Mod4Mask;
		button[currentButton].command = ShrinkGridCommand;
		++currentButton;
		button[currentButton].button = Button1;
		button[currentButton].masks = Mod4Mask;
		button[currentButton].command = MoveCommand;
	}



	grabRootKeysButtons(shortcutAmount, shortcut, buttonAmount, button);



	XEvent event;
	XSync(display, False);
	do{
		// fprintf(stdout, "[re]started\n");
		Container container[containerAmount];
		{
			Window w;
			XVisualInfo visualInfo;
			XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo);
			XSetWindowAttributes windowAttributes = {
				.background_pixel = containerBackgroundColor,
				.border_pixel = containerBorderColor,
				.colormap = XCreateColormap(display, XDefaultRootWindow(display), visualInfo.visual, AllocNone)
			};
			for(unsigned int currentContainer = 0; currentContainer < containerAmount; ++currentContainer){
				w = XCreateWindow(display, XDefaultRootWindow(display), 0, 0, 1, 1, border, visualInfo.depth, InputOutput, visualInfo.visual, CWBackPixel | CWBorderPixel | CWColormap, &windowAttributes);
				container[currentContainer].subwindow = None;
				container[currentContainer].inGrid = 0;
				XSelectInput(display, w, ButtonReleaseMask | EnterWindowMask | /*LeaveWindowMask |*/ ButtonMotionMask);
				grabContainerKeysButtons(w, shortcutAmount, shortcut, buttonAmount, button);
				container[currentContainer].window = w;
			}
		}
		REALLOCATE_SUBWINDOWS
		for(;;){
			XNextEvent(display, &event);
			printEvent(event);
			/*for(unsigned int currentContainer = 0; currentContainer < containerAmount; ++currentContainer){
				fprintf(stdout, "%lu -> %lu\n", container[currentContainer].window, container[currentContainer].subwindow);
			}
			fprintf(stdout, "lastCreated: %lu\nallocatedContainerAmount: %u\n", lastCreatedWindow, allocatedContainerAmount);
			for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
				fprintf(stdout, "\n(%u, %u) -> (%u, %u)\n", container[currentContainer].gridX, container[currentContainer].gridY, container[currentContainer].gridX + container[currentContainer].gridWidth, container[currentContainer].gridY);
				fprintf(stdout, "   Λ         |\n   |         V\n");
				fprintf(stdout, "(%u, %u) <- (%u, %u)\n\n", container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, container[currentContainer].gridX + container[currentContainer].gridWidth, container[currentContainer].gridY + container[currentContainer].gridHeight);
			}*/
			if(event.type == KeyPress){
				KEYPRESS
			}else if(event.type == ButtonPress){
				BUTTONPRESS
			}else if(event.type == ButtonRelease){
				action = NoAction;
			}else if(event.type == MotionNotify){
				xtouse = event.xmotion.x_root;
				ytouse = event.xmotion.y_root;
				// motion:{
					if(action == MoveAction){
						XMoveWindow(display, motionContainer.window, xtouse - x, ytouse - y);
					}else{
						/*if(subaction == MoveResizeSubaction){
							width += xpos - xtouse + x;
							height += ypos - ytouse + y;
							if((int)width <= (int)innerBorders){
								width = innerBorders + 1;
								xtouse = xpos + x;
							}else{
								xpos = xtouse - x;
							}
							if((int)height <= (int)innerBorders){
								height = innerBorders + 1;
								ytouse = ypos + y;
							}else{
								ypos = ytouse - y;
							}
							XMoveResizeWindow(display, motionContainer.subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders);
							XMoveResizeWindow(display, motionContainer.window, xtouse - x, ytouse - y, width, height);
						}else{
							width += xtouse - x - xpos;
							height += ytouse - y - ypos;
							if((int)width <= (int)innerBorders){
								width = innerBorders + 1;
							}
							if((int)height <= (int)innerBorders){
								height = innerBorders + 1;
							}
							XResizeWindow(display, motionContainer.subwindow, width - innerBorders, height - innerBorders);
							XResizeWindow(display, motionContainer.window, width, height);
							xpos = xtouse - x;
							ypos = ytouse - y;
						}*/
					}
				// }
			}else if(event.type == EnterNotify){
				for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
					if(event.xcrossing.window == container[currentContainer].window){
						if(container[currentContainer].subwindow){
							XMapRaised(display, event.xcrossing.window);
							XSetInputFocus(display, event.xcrossing.window, RevertToPointerRoot, CurrentTime);
						}
						break;
					}else if(event.xcrossing.window == container[currentContainer].subwindow){
						XMapRaised(display, event.xcrossing.window);
						XSetInputFocus(display, event.xcrossing.window, RevertToPointerRoot, CurrentTime);
						break;
					}
				}
			/*}else if(event.type == LeaveNotify){
				if(action){
					xtouse = event.xcrossing.x_root;
					ytouse = event.xcrossing.y_root;
					goto motion;
				}*/
			}else if(event.type == UnmapNotify){
				for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
					if(event.xunmap.window == container[currentContainer].subwindow){
						XUnmapWindow(display, container[currentContainer].window);
						XSetInputFocus(display, XDefaultRootWindow(display), RevertToPointerRoot, CurrentTime);
						clearWindowProperties(container[currentContainer].window);
						container[currentContainer].subwindow = None;
						if(container[currentContainer].inGrid){
							XSetWindowBorderWidth(display, event.xany.window, border);
							container[currentContainer].inGrid = 0;
						}
						--allocatedContainerAmount;
						unsigned int currentContainer1;
						Window tempWindow;
						lastCreatedWindow = None;
						for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){
							if(!container[currentContainer].subwindow){
								for(currentContainer1 = currentContainer; currentContainer1 < containerAmount - 1; ++currentContainer1){
									tempWindow = container[currentContainer1 + 1].window;
									container[currentContainer1 + 1].window = container[currentContainer1].window;
									container[currentContainer1].window = tempWindow;
									container[currentContainer1].subwindow = container[currentContainer1 + 1].subwindow;
								}
							}else{
								lastCreatedWindow = container[currentContainer].window;
							}
						}
						break;
					}
				}
			}else if(event.type == MapRequest){
				copyWindowProperties(event.xmaprequest.window, container[allocatedContainerAmount].window);
				container[allocatedContainerAmount].subwindow = event.xmaprequest.window;
				XRRMonitorInfo monitorInfo;
				if(pointerInfo & MapPointerInfo){
					monitorInfo = getPointerMonitorInfo();
				}else{
					monitorInfo = getWindowMonitorInfo(event.xmaprequest.window);
				}
				XReparentWindow(display, event.xmaprequest.window, container[allocatedContainerAmount].window, 0, 0);
				const unsigned int width = monitorInfo.width / gridWidth;
				const unsigned int height = monitorInfo.height / gridHeight;
				if(cascade.mode == SimpleCascadeMode){
					if(lastCreatedWindow != None){
						if(XGetWindowAttributes(display, lastCreatedWindow, &windowAttributes)){
							goto cascadedPosition;
						}else{
							goto uncascadedPosition;
						}
					}else{
						goto uncascadedPosition;
					}
				}else if(cascade.mode == SmartCascadeMode){
					if(lastCreatedWindow != None){
						if(XGetWindowAttributes(display, lastCreatedWindow, &windowAttributes)){
							if(windowAttributes.x == monitorInfo.x + (int)(monitorInfo.width - width - borders) / 2 && windowAttributes.y == monitorInfo.y + (int)(monitorInfo.height - height - borders) / 2){
								cascadedPosition:{



									XMoveResizeWindow(display, container[allocatedContainerAmount].window, windowAttributes.x + cascade.offsetX, windowAttributes.y + cascade.offsetY, width, height);



								}
							}else{
								goto uncascadedPosition;
							}
						}else{
							goto uncascadedPosition;
						}
					}else{
						goto uncascadedPosition;
					}
				}else{
					uncascadedPosition:{
						XMoveResizeWindow(display, container[allocatedContainerAmount].window, monitorInfo.x + (monitorInfo.width - width) / 2 - border, monitorInfo.y + (monitorInfo.height - height) / 2 - border, width, height);
					}
				}
				XMoveResizeWindow(display, event.xmaprequest.window, innerBorder, innerBorder, width - innerBorders, height - innerBorders);



				XSelectInput(display, event.xmaprequest.window, ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | StructureNotifyMask);



				XMapRaised(display, container[allocatedContainerAmount].window);
				XMapRaised(display, event.xmaprequest.window);



				XSetInputFocus(display, event.xmaprequest.window, RevertToPointerRoot, CurrentTime);



				lastCreatedWindow = container[allocatedContainerAmount].window;
				if(++allocatedContainerAmount == containerAmount){
					FILE *file = fopen("/home/steven/.microwm/.subwindows", "w");
					unsigned int currentContainer;
					if(file){
						for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){
							XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes);
							fprintf(file, "%lu %i %i %u %u\n", container[currentContainer].subwindow, windowAttributes.x, windowAttributes.y, windowAttributes.width, windowAttributes.height);
						}
						fclose(file);
					}
					for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){
						XReparentWindow(display, container[currentContainer].subwindow, XDefaultRootWindow(display), 0, 0);
					}
					shouldIncreaseContainers = 1;
					break;
				}









			}else if(event.type == ConfigureNotify){
				/*for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
					if(container[currentContainer].subwindow == event.xconfigure.window){
						XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
						XMoveWindow(display, container[currentContainer].window, event.xconfigure.x - innerBorder - border, event.xconfigure.y - innerBorder - border);
						XMoveWindow(display, event.xconfigure.window, innerBorder, innerBorder);
						break;
					}
				}*/









			}else if(event.type == ConfigureRequest){
				const XRRMonitorInfo monitorInfo = getPointerMonitorInfo();
				XMoveResizeWindow(display, event.xmaprequest.window, monitorInfo.x, monitorInfo.y, monitorInfo.width / gridWidth - innerBorders, monitorInfo.height / gridHeight - innerBorders);
			}else if(event.type == ClientMessage){
				//



			}
		}
		for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
			XUnmapWindow(display, container[currentContainer].window);
			XDestroyWindow(display, container[currentContainer].window);
		}
		if(shouldIncreaseContainers == 1){
			containerAmount += containerIncrementAmount;
			shouldIncreaseContainers = 0;
		}
	}while(mode == ContinueMode);
	return;
}
static void grabRootKeysButtons(const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button){
	unsigned int current;
	for(current = 0; current < shortcutAmount; ++current){
		if(shortcut[current].command <= RootCommandCeiling){
			if(shortcut[current].keycode != AnyKey){
				XGrabKey(display, shortcut[current].keycode, shortcut[current].masks, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
			}
		}
	}
	for(current = 0; current < buttonAmount; ++current){
		if(button[current].command <= RootCommandCeiling){
			if(button[current].button != AnyButton){
				XGrabButton(display, button[current].button, button[current].masks, XDefaultRootWindow(display), True, NoEventMask, GrabModeAsync, GrabModeAsync, None, None);
			}
		}
	}
	return;
}
static void grabContainerKeysButtons(const Window w, const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button){
	unsigned int current;
	for(current = 0; current < shortcutAmount; ++current){
		if(shortcut[current].command > RootCommandCeiling){
			if(shortcut[current].keycode != AnyKey){
				XGrabKey(display, shortcut[current].keycode, shortcut[current].masks, w, True, GrabModeAsync, GrabModeAsync);
			}
		}
	}
	for(current = 0; current < buttonAmount; ++current){
		if(button[current].command > RootCommandCeiling){
			if(button[current].button != AnyButton){
				XGrabButton(display, button[current].button, button[current].masks, w, True, NoEventMask, GrabModeAsync, GrabModeAsync, None, None);
			}
		}
	}
	return;
}
static void createGrid(const unsigned int monitorAmount, const unsigned int gridWidth, const unsigned int gridHeight, const ARGB gridSubwindowBorderColor, const ARGB gridSubwindowBackgroundColor, Window *const grid){
	if(monitorAmount){
		unsigned int ma;
		XRRMonitorInfo *const monitorInfo = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&ma);
		if(monitorInfo){
			if(ma == monitorAmount){
				unsigned int currentMonitor;
				XVisualInfo visualInfo;
				XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo);
				XSetWindowAttributes windowAttributes = {
					.background_pixel = 0x00000000,
					.border_pixel = 0x00000000,
					.override_redirect = True,
					.colormap = XCreateColormap(display, XDefaultRootWindow(display), visualInfo.visual, AllocNone)
				};
				unsigned int width;
				unsigned int height;
				unsigned int abnormalWidth;
				unsigned int abnormalHeight;
				int offsetY;
				unsigned int y;
				int offsetX;
				unsigned int x;
				int finalX;
				int finalY;
				const unsigned int abnormalX = gridWidth / 2;
				const unsigned int abnormalY = gridHeight / 2;
				unsigned int finalWidth;
				unsigned int finalHeight;
				const unsigned int gridBorder = 1;
				const unsigned int gridBorders = 2 * gridBorder;
				for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
					grid[currentMonitor] = XCreateWindow(display, XDefaultRootWindow(display), monitorInfo[currentMonitor].x, monitorInfo[currentMonitor].y, monitorInfo[currentMonitor].width, monitorInfo[currentMonitor].height, 0, visualInfo.depth, InputOutput, visualInfo.visual, CWBackPixel | CWBorderPixel | CWOverrideRedirect | CWColormap, &windowAttributes);
					width = monitorInfo[currentMonitor].width / gridWidth;
					height = monitorInfo[currentMonitor].height / gridHeight;
					abnormalWidth = monitorInfo[currentMonitor].width - (gridWidth - 1) * width;
					abnormalHeight = monitorInfo[currentMonitor].height - (gridHeight - 1) * height;
					offsetY = 0;
					for(y = 0; y < gridHeight; ++y){
						offsetX = 0;
						for(x = 0; x < gridWidth; ++x){
							finalX = x * width;
							finalY = y * height;
							if(x == abnormalX){
								offsetX = width - abnormalWidth;
								if(offsetX < 0){
									offsetX = -offsetX;
								}
								finalX -= offsetX;
								finalWidth = abnormalWidth;
							}else{
								finalWidth = width;
							}
							if(y == abnormalY){
								offsetY = height - abnormalHeight;
								if(offsetY < 0){
									offsetY = -offsetY;
								}
								finalY -= offsetY;
								finalHeight = abnormalHeight;
							}else{
								finalHeight = height;
							}
							XCreateSimpleWindow(display, grid[currentMonitor], finalX + offsetX, finalY + offsetY, finalWidth - gridBorders, finalHeight - gridBorders, gridBorder, gridSubwindowBorderColor, gridSubwindowBackgroundColor);
						}
					}
				}
			}
			XRRFreeMonitors(monitorInfo);
		}
	}
	return;
}
static void getGridSlotData(const XRRMonitorInfo monitorInfo, const unsigned int gridX, const unsigned int gridY, const unsigned int gridWidth, const unsigned int gridHeight, int *const x, int *const y, unsigned int *const width, unsigned int *const height){
	const unsigned int normalWidth = monitorInfo.width / gridWidth;
	const unsigned int normalHeight = monitorInfo.height / gridHeight;
	const unsigned int abnormalWidth = monitorInfo.width - (gridWidth - 1) * normalWidth;
	const unsigned int abnormalHeight = monitorInfo.height - (gridHeight - 1) * normalHeight;
	if(x){
		if(gridX > gridWidth / 2){
			*x = (gridX - 1) * normalWidth + abnormalWidth;
		}else{
			*x = gridX * normalWidth;
		}
	}
	if(y){
		if(gridY > gridHeight / 2){
			*y = (gridY - 1) * normalHeight + abnormalHeight;
		}else{
			*y = gridY * normalHeight;
		}
	}
	if(width){
		if(gridX == gridWidth / 2){
			*width = abnormalWidth;
		}else{
			*width = normalWidth;
		}
	}
	if(height){
		if(gridY == gridHeight / 2){
			*height = abnormalHeight;
		}else{
			*height = normalHeight;
		}
	}
	return;
}
static XRRMonitorInfo getWindowMonitorInfo(const Window w){
	XRRMonitorInfo monitorInfo;
	unsigned int monitorAmount;
	XRRMonitorInfo *const mi = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&monitorAmount);
	if(mi){
		if(monitorAmount == 1){
			monitorInfo = *mi;
		}else{
			unsigned int currentMonitor;
			XWindowAttributes windowAttributes;
			XGetWindowAttributes(display, w, &windowAttributes);
			unsigned int pixels;
			unsigned int height;
			unsigned int mostPixels = 0;
			unsigned int monitorToUse = 0;
			if(windowAttributes.border_width){
				windowAttributes.border_width *= 2;
				windowAttributes.width += windowAttributes.border_width;
				windowAttributes.height += windowAttributes.border_width;
			}
			for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
				monitorInfo = mi[currentMonitor];
				if(monitorInfo.x > windowAttributes.x + windowAttributes.width){
					continue;
				}else if(monitorInfo.x <= windowAttributes.x + windowAttributes.width && monitorInfo.x + monitorInfo.width > windowAttributes.x + windowAttributes.width){
					pixels = windowAttributes.x + windowAttributes.width;
				}else{
					pixels = monitorInfo.x + monitorInfo.width;
				}
				if(monitorInfo.x > windowAttributes.x){
					pixels -= monitorInfo.x;
				}else if(monitorInfo.x <= windowAttributes.x && monitorInfo.x + monitorInfo.width > windowAttributes.x){
					pixels -= windowAttributes.x;
				}else{
					continue;
				}
				if(monitorInfo.y > windowAttributes.y + windowAttributes.height){
					continue;
				}else if(monitorInfo.y <= windowAttributes.y + windowAttributes.height && monitorInfo.y + monitorInfo.height > windowAttributes.y + windowAttributes.height){
					height = windowAttributes.y + windowAttributes.height;
				}else{
					height = monitorInfo.y + monitorInfo.height;
				}
				if(monitorInfo.y > windowAttributes.y){
					height -= monitorInfo.y;
				}else if(monitorInfo.y <= windowAttributes.y && monitorInfo.y + monitorInfo.height > windowAttributes.y){
					height -= windowAttributes.y;
				}else{
					continue;
				}
				pixels *= height;
				if(pixels > mostPixels){
					mostPixels = pixels;
					monitorToUse = currentMonitor;
				}
			}
			monitorInfo = mi[monitorToUse];
		}
		XRRFreeMonitors(mi);
	}else{
		monitorInfo.x = 0;
		monitorInfo.y = 0;
		monitorInfo.width = 1000;
		monitorInfo.height = 1000;
	}
	return monitorInfo;
}
static XRRMonitorInfo getPointerMonitorInfo(void){
	XRRMonitorInfo monitorInfo;
	unsigned int monitorAmount;
	XRRMonitorInfo *const mi = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&monitorAmount);
	if(mi){
		if(monitorAmount == 1){
			monitorInfo = *mi;
		}else{
			int x;
			int y;
			{
				Window w;
				unsigned int masks;
				if(!XQueryPointer(display, XDefaultRootWindow(display), &w, &w, &x, &y, &x, &y, &masks)){
					x = 0;
					y = 0;
				}
			}
			unsigned int currentMonitor;
			for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
				monitorInfo = mi[currentMonitor];
				if(monitorInfo.x <= x && monitorInfo.x + monitorInfo.width > x && monitorInfo.y <= y && monitorInfo.y + monitorInfo.height > y){
					break;
				}
			}
			if(currentMonitor == monitorAmount){
				monitorInfo = *mi;
			}
		}
		XRRFreeMonitors(mi);
	}else{
		monitorInfo.x = 0;
		monitorInfo.y = 0;
		monitorInfo.width = 1000;
		monitorInfo.height = 1000;
	}
	return monitorInfo;
}
static void clearWindowProperties(const Window w){
	unsigned int amount;
	Atom *const property = XListProperties(display, w, (int *)&amount);
	if(property){
		for(unsigned int current = 0; current < amount; ++current){
			XDeleteProperty(display, w, property[current]);
		}
		XFree(property);
	}
	return;
}
static void copyWindowProperties(const Window source, const Window destination){
	unsigned int propertyAmount;
	Atom *const property = XListProperties(display, source, (int *)&propertyAmount);
	if(property){
		{
			Atom type;
			int format;
			unsigned long int itemAmount;
			unsigned long int bytesAfter;
			unsigned char *data;
			const long int size = sizeof(Atom);
			for(unsigned int currentProperty = 0; currentProperty < propertyAmount; ++currentProperty){
				if(XGetWindowProperty(display, source, property[currentProperty], 0, size, False, AnyPropertyType, &type, &format, &itemAmount, &bytesAfter, &data) == Success){
					if(data){
						XChangeProperty(display, destination, property[currentProperty], type, format, PropModeReplace, data, itemAmount);
						XFree(data);
					}
				}
			}
		}
		XFree(property);
	}
	return;
}
