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

#define NoOptions /*------------------------*/ 0
#define FloatingFollowGrid /*---------------*/ (1 << 0)
#define FloatingMinimalResizeOption /*------*/ (1 << 1)
#define FloatingAllowStickingOption /*------*/ (1 << 2)
#define GridingAllowBoundaryBreakXOption /*-*/ (1 << 3)
#define GridingAllowBoundaryBreakYOption /*-*/ (1 << 4)
// #define TilingOption /*---------------------*/ (1 << 5)

#define NoDefaultGridPosition /*------------*/ 0
#define TopLeftDefaultGridPosition /*-------*/ 1
#define TopRightDefaultGridPosition /*------*/ 2
#define BottomLeftDefaultGridPosition /*----*/ 3
#define BottomRightDefaultGridPosition /*---*/ 4
#define CenterDefaultGridPosition /*--------*/ 5

#define FloatingManagementMode /*-----------*/ 1
#define GridingManagementMode /*------------*/ 2
#define TilingManagementMode /*-------------*/ 3

#define NoCommand /*------------------------*/ 0
#define SystemCommand /*--------------------*/ 1
#define FloatingModeCommand /*--------------*/ 2
#define GridingModeCommand /*---------------*/ 3
#define TilingModeCommand /*----------------*/ 4
#define ShowGridCommand /*------------------*/ 5
#define EnlargeGridCommand /*---------------*/ 6
#define ShrinkGridCommand /*----------------*/ 7
#define RecascadeCommand /*-----------------*/ 8
#define RestartCommand /*-------------------*/ 9
#define ExitCommand /*----------------------*/ 10
#define MoveCommand /*----------------------*/ 11
#define MoveTopCommand /*-------------------*/ 12
#define MoveBottomCommand /*----------------*/ 13
#define MoveLeftCommand /*------------------*/ 14
#define MoveRightCommand /*-----------------*/ 15
#define MoveCenterCommand /*----------------*/ 16
#define MoveTopLeftCommand /*---------------*/ 17
#define MoveTopRightCommand /*--------------*/ 18
#define MoveBottomLeftCommand /*------------*/ 19
#define MoveBottomRightCommand /*-----------*/ 20
#define MoveNextMonitorCommand /*-----------*/ 21
#define MovePreviousMonitorCommand /*-------*/ 22
#define MoveAboveMonitorCommand /*----------*/ 23
#define MoveBelowMonitorCommand /*----------*/ 24
#define MoveLeftMonitorCommand /*-----------*/ 25
#define MoveRightMonitorCommand /*----------*/ 26
// #define RevolveMonitorsCommand /*-----------*/ 27
#define AddWindowToGridCommand /*-----------*/ 27
#define RemoveWindowFromGridCommand /*------*/ 28
#define ToggleWindowGridCommand /*----------*/ 29
#define MoveFirstGridSlotCommand /*---------*/ 30
#define MoveLastGridSlotCommand /*----------*/ 31
#define MoveAboveGridSlotCommand /*---------*/ 32
#define MoveBelowGridSlotCommand /*---------*/ 33
#define MoveNextGridSlotCommand /*----------*/ 34
#define MovePreviousGridSlotCommand /*------*/ 35
#define MoveUpOnGridCommand /*--------------*/ 36
#define MoveDownOnGridCommand /*------------*/ 37
#define MoveLeftOnGridCommand /*------------*/ 38
#define MoveRightOnGridCommand /*-----------*/ 39
#define ExtendWindowUpCommand /*------------*/ 40
#define ExtendWindowDownCommand /*----------*/ 41
#define ExtendWindowLeftCommand /*----------*/ 42
#define ExtendWindowRightCommand /*---------*/ 43
#define ExtendWindowUpLeftCommand /*--------*/ 44
#define ExtendWindowUpRightCommand /*-------*/ 45
#define ExtendWindowDownLeftCommand /*------*/ 46
#define ExtendWindowDownRightCommand /*-----*/ 47
#define ShrinkWindowUpCommand /*------------*/ 48
#define ShrinkWindowDownCommand /*----------*/ 49
#define ShrinkWindowLeftCommand /*----------*/ 50
#define ShrinkWindowRightCommand /*---------*/ 51
#define ShrinkWindowUpLeftCommand /*--------*/ 52
#define ShrinkWindowUpRightCommand /*-------*/ 53
#define ShrinkWindowDownLeftCommand /*------*/ 54
#define ShrinkWindowDownRightCommand /*-----*/ 55
#define FullscreenCommand /*----------------*/ 56
#define BigscreenCommand /*-----------------*/ 57
#define CloseCommand /*---------------------*/ 58
#define KillCommand /*----------------------*/ 59
// #define FocusCommand /*---------------------*/ 60

#define RootCommandCeiling /*---------------*/ ExitCommand

#define NoCascadeMode /*--------------------*/ 0
#define SimpleCascadeMode /*----------------*/ 1
#define SmartCascadeMode /*-----------------*/ 2

#define NoMotionOptions /*------------------*/ 0
#define CanActOption /*---------------------*/ (1 << 0)
#define HasLockedXOption /*-----------------*/ (1 << 1)
#define HasLockedYOption /*-----------------*/ (1 << 2)

#define NoMotionAction /*-------------------------*/ 0
#define MoveMotionAction /*-----------------------*/ 1
#define ResizeMotionAction /*---------------------*/ 2

#define NoMotionSubaction /*----------------------*/ 0
#define UpResizeMotionSubaction /*----------------*/ 1
#define DownResizeMotionSubaction /*--------------*/ 2
#define LeftResizeMotionSubaction /*--------------*/ 3
#define RightResizeMotionSubaction /*-------------*/ 4
#define UpLeftResizeMotionSubaction /*------------*/ 5
#define UpRightResizeMotionSubaction /*-----------*/ 6
#define DownLeftResizeMotionSubaction /*----------*/ 7
#define DownRightResizeMotionSubaction /*---------*/ 8

#define NoContainerDirective /*-------------*/ 0
#define IncreaseContainerDirective /*-------*/ 1
#define DecreaseContainerDirective /*-------*/ 2

#define NoContainerOptions /*---------------*/ 0
#define InGridContainerOption /*------------*/ (1 << 0)
// #define InTileContainerOption /*------------*/ (1 << 1)
// #define FreezeStackingContainerOption /*----*/ (1 << 2)

#define NoPointerInfo /*--------------------*/ 0
#define ChangeToFloatingPointerInfo /*------*/ (1 << 0)
#define ChangeToGridingPointerInfo /*-------*/ (1 << 1)
#define ChangeToTilingPointerInfo /*--------*/ (1 << 2)
#define MovePointerInfo /*------------------*/ (1 << 3)
#define RecascadePointerInfo /*-------------*/ (1 << 4)
#define AddToGridPointerInfo /*-------------*/ (1 << 5)
#define RemoveFromGridPointerInfo /*--------*/ (1 << 6)
#define FullscreenPointerInfo /*------------*/ (1 << 7)
#define BigscreenPointerInfo /*-------------*/ (1 << 8)
#define MapPointerInfo /*-------------------*/ (1 << 9)

#define monitorCompare(m0, m1) \
(m0.name == m1.name && \
m0.primary == m1.primary && \
m0.automatic == m1.automatic && \
m0.noutput == m1.noutput && \
m0.x == m1.x && \
m0.y == m1.y && \
m0.width == m1.width && \
m0.height == m1.height && \
m0.mwidth == m1.mwidth && \
m0.mheight == m1.mheight)

extern const char *programName;
extern Mode mode;
extern Display *display;

typedef uint16_t PointerInfo;
typedef uint32_t ARGB;
typedef uint8_t ManagementMode;
typedef uint8_t Options;
typedef uint8_t DefaultGridPosition;
typedef uint8_t ContainerDirective;
typedef uint8_t ContainerOption;

typedef struct{
	uint8_t mode;
	bool overrideGridWindows;
	int offsetX;
	int offsetY;
} Cascade;

typedef struct{
	Window window;
	Window subwindow;
	ContainerOption option;
	unsigned int gridX;
	unsigned int gridY;
	unsigned int gridWidth;
	unsigned int gridHeight;
} Container;

typedef struct{
	Window window;
	Window subwindow;
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	int pointerOffsetX;
	int pointerOffsetY;
	int positionOffset;
	int movementBorderX;
	int movementBorderY;
	uint8_t options;
	uint8_t action;
	uint8_t subaction;
} MotionContainer;

typedef struct{
	Window window;
	ContainerOption option;
} LastCreatedContainer;

static void grabRootKeysButtons(const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button);
static void grabContainerKeysButtons(const Window w, const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button);
static XRRMonitorInfo getPointerMonitorInfo(const XRRMonitorInfo *const monitors, const unsigned int monitorAmount);
static XRRMonitorInfo getWindowMonitorInfo(const Window w, const XRRMonitorInfo *const monitors, const unsigned int monitorAmount);
static void getGridSlotData(const XRRMonitorInfo monitorInfo, const unsigned int gridX, const unsigned int gridY, const unsigned int gridWidth, const unsigned int gridHeight, int *const x, int *const y, unsigned int *const width, unsigned int *const height);
static void createGrid(const XRRMonitorInfo *const monitors, const unsigned int monitorAmount, const unsigned int gridWidth, const unsigned int gridHeight, const ARGB gridSubwindowBorderColor, const ARGB gridSubwindowBackgroundColor, Window *const grid);
static void moveInGridContainerToMonitor(const XRRMonitorInfo monitor, const Container container, const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int innerBorders);
static void moveContainerToMonitor(const XRRMonitorInfo source, const XRRMonitorInfo destination, const Window window, const Window subwindow, const unsigned int border, const unsigned int innerBorders);
static void clearWindowProperties(const Window w);
static void copyWindowProperties(const Window source, const Window destination);
static void ungrabContainerKeysButtons(const Window w, const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button);
static void ungrabRootKeysButtons(const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button);

void eventLoop(void){
	ManagementMode managementMode = FloatingManagementMode;
	Options option = FloatingMinimalResizeOption | FloatingAllowStickingOption | GridingAllowBoundaryBreakXOption | GridingAllowBoundaryBreakYOption;
	PointerInfo pointerInfo = MapPointerInfo | MovePointerInfo | ChangeToFloatingPointerInfo | ChangeToGridingPointerInfo;
	DefaultGridPosition defaultGridPosition = CenterDefaultGridPosition;

	Cascade cascade = {
		.mode = SmartCascadeMode,
		.overrideGridWindows = 0,
		.offsetX = 20,
		.offsetY = 20
	};

	LastCreatedContainer lastCreatedContainer = {
		.window = None
	};

	MotionContainer motionContainer = {
		.action = NoMotionAction,
		.subaction = NoMotionSubaction,
		.options = NoMotionOptions
	};

	char *subwindowsPath = "/home/steven/.microwm/.subwindows";



	int floatingStickyThresholdX = 10;
	int floatingStickyThresholdY = 10;
	int floatingDistanceToTravelX = 50;
	int floatingDistanceToTravelY = 50;



	/*unsigned int tilingMinimumWidth = 20;
	unsigned int tilingMinimumHeight = 20;
	unsigned int tilingGapsX = 10;
	unsigned int tilingGapsY = 10;*/



	ContainerDirective containerDirective = NoContainerDirective;
	unsigned int containerIncrementAmount = 5;

	unsigned int defaultContainerAmount = 5;
	unsigned int containerAmount = defaultContainerAmount;
	unsigned int allocatedContainerAmount = 0;
	XWindowAttributes windowAttributes;

	unsigned int border = 10;

	unsigned int innerBorder = 1;
	const unsigned int innerBorders = 2 * innerBorder;



	ARGB containerBorderColor = 0x7F000000;
	ARGB floatingContainerBackgroundColor = 0xFF00FF00;
	ARGB gridingContainerBackgroundColor = 0xFFFF0000;
	ARGB tilingContainerBackgroundColor = 0xFF0000FF;
	ARGB inGridContainerBackgroundColor = 0xFFFF0000;
	ARGB gridSubwindowBorderColor = 0x10975C57;
	ARGB gridSubwindowBackgroundColor = 0x00000000;
	ARGB separatorBorderColor = 0xFF000000;
	ARGB separatorBackgroundColor = 0xFF000000;



	unsigned int gridWidth = 2;
	unsigned int gridHeight = 2;

	unsigned int separatorWidth = 12;
	unsigned int separatorBorder = 1;

	unsigned int currentContainer;

	bool separatorsExist = 0;
	unsigned int mappedSeparatorAmount = 0;

	unsigned int extendWidth = 10;
	unsigned int extendHeight = 10;
	unsigned int shrinkWidth = 10;
	unsigned int shrinkHeight = 10;



	unsigned int monitorAmount;
	unsigned int maxGridWidth = 20;
	unsigned int maxGridHeight = 20;
	{
		XRRMonitorInfo *const monitorInfo = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&monitorAmount);
		if(monitorInfo){
			{
				unsigned int width;
				unsigned int height;
				for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
					width = monitorInfo[currentMonitor].width / 3;
					height = monitorInfo[currentMonitor].height / 3;
					if(maxGridWidth > width){
						maxGridWidth = width;
					}
					if(maxGridHeight > height){
						maxGridHeight = height;
					}
				}
			}
			XRRFreeMonitors(monitorInfo);
		}else{
			monitorAmount = 1;
		}
	}
	XRRMonitorInfo monitors[monitorAmount];
	{
		unsigned int ma;
		XRRMonitorInfo *const monitorInfo = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&ma);
		if(monitorInfo){
			if(ma == monitorAmount){
				for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
					monitors[currentMonitor] = monitorInfo[currentMonitor];
				}
			}
			XRRFreeMonitors(monitorInfo);
		}
	}



	Window resizeWindow;
	unsigned int resizeWindowBorder = 1;
	if(option & FloatingMinimalResizeOption){
		ARGB resizeWindowBackgroundColor = 0x7FF07746;
		ARGB resizeWindowBorderColor = 0xFFF2C6B4;
		const Window rootWindow = XDefaultRootWindow(display);
		XVisualInfo visualInfo;
		XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo);
		XSetWindowAttributes windowAttributes = {
			.background_pixel = resizeWindowBackgroundColor,
			.border_pixel = resizeWindowBorderColor,
			.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone)
		};
		resizeWindow = XCreateWindow(display, rootWindow, 0, 0, 1, 1, resizeWindowBorder, visualInfo.depth, InputOutput, visualInfo.visual, CWBackPixel | CWBorderPixel | CWColormap, &windowAttributes);
	}



	Window grid[monitorAmount];

	bool gridExists = 0;
	bool gridMapped = 0;

	SET_KEYS_BUTTONS
	grabRootKeysButtons(shortcutAmount, shortcut, buttonAmount, button);
	{
		XEvent event;
		int rrEventBase;
		{
			int rrErrorBase;
			if(!XRRQueryExtension(display, &rrEventBase, &rrErrorBase)){
				fprintf(stderr, "%s: could not query the xrandr extension\n", programName);
				rrEventBase = 0;
			}
		}
		XSync(display, False);
		do{
			fprintf(stdout, "begin\n");
			Container container[containerAmount];
			Window separator[containerAmount - 1];
			{
				const Window rootWindow = XDefaultRootWindow(display);
				XSelectInput(display, rootWindow, SubstructureRedirectMask);
				{
					XVisualInfo visualInfo;
					XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo);
					const uint16_t windowAttributesMasks = CWBackPixel | CWBorderPixel | CWColormap;
					XSetWindowAttributes windowAttributes = {
						.background_pixel = separatorBackgroundColor,
						.border_pixel = separatorBorderColor,
						.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone)
					};
					unsigned int currentBorder;
					if(managementMode == FloatingManagementMode){
						currentBorder = border;
						windowAttributes.background_pixel = floatingContainerBackgroundColor;
					}else if(managementMode == GridingManagementMode){
						currentBorder = 0;
						windowAttributes.background_pixel = gridingContainerBackgroundColor;
					}else{
						const unsigned int separatorAmount = containerAmount - 1;
						for(unsigned int currentSeparator = 0; currentSeparator < separatorAmount; ++currentSeparator){
							separator[currentSeparator] = XCreateWindow(display, rootWindow, 0, 0, 1, 1, border, visualInfo.depth, InputOutput, visualInfo.visual, windowAttributesMasks, &windowAttributes);
						}
						separatorsExist = 1;
						currentBorder = 0;
						windowAttributes.background_pixel = tilingContainerBackgroundColor;
					}
					windowAttributes.border_pixel = containerBorderColor;
					Window w;
					for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){
						w = XCreateWindow(display, rootWindow, 0, 0, 1, 1, currentBorder, visualInfo.depth, InputOutput, visualInfo.visual, windowAttributesMasks, &windowAttributes);
						grabContainerKeysButtons(w, shortcutAmount, shortcut, buttonAmount, button);
						container[currentContainer].window = w;
						container[currentContainer].subwindow = None;
					}
				}
			}
			REALLOCATE_SUBWINDOWS
			for(;;){
				XNextEvent(display, &event);
				printEvent(event);
				/*for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){
					fprintf(stdout, "%lu -> %lu\n", container[currentContainer].window, container[currentContainer].subwindow);
				}
				fprintf(stdout, "lastCreatedWindow: %lu\nallocatedContainerAmount: %u\n", lastCreatedContainer.window, allocatedContainerAmount);
				{
					Container c;
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
						c = container[currentContainer];
						fprintf(stdout, "\n(%u, %u) -> (%u, %u)\n", c.gridX, c.gridY, c.gridX + c.gridWidth, c.gridY);
						fprintf(stdout, "   Λ         |\n   |         V\n");
						fprintf(stdout, "(%u, %u) <- (%u, %u)\n\n", c.gridX, c.gridY + c.gridHeight, c.gridX + c.gridWidth, c.gridY + c.gridHeight);
					}
				}*/
				if(event.type == KeyPress){
					KEYPRESS
				}else if(event.type == KeyRelease){
					BUTTONRELEASE
				}else if(event.type == ButtonPress){
					BUTTONPRESS
				}else if(event.type == ButtonRelease){
					BUTTONRELEASE
				}else if(event.type == MotionNotify){
					MOTIONNOTIFY
				}else if(event.type == EnterNotify){
					ENTERNOTIFY
				}else if(event.type == UnmapNotify){
					UNMAPNOTIFY
				}else if(event.type == MapRequest){
					copyWindowProperties(event.xmaprequest.window, container[allocatedContainerAmount].window);
					XReparentWindow(display, event.xmaprequest.window, container[allocatedContainerAmount].window, 0, 0);
					XRRMonitorInfo monitorInfo;
					if(pointerInfo & MapPointerInfo){
						monitorInfo = getPointerMonitorInfo(monitors, monitorAmount);
					}else{
						monitorInfo = getWindowMonitorInfo(event.xmaprequest.window, monitors, monitorAmount);
					}
					{
						unsigned int width;
						unsigned int height;
						if(managementMode == FloatingManagementMode){
							XSetWindowBorderWidth(display, container[allocatedContainerAmount].window, border);
							XSetWindowBackground(display, container[allocatedContainerAmount].window, floatingContainerBackgroundColor);
							if(option & FloatingFollowGrid){
								width = monitorInfo.width / gridWidth;
								height = monitorInfo.height / gridHeight;
							}else{
								width = monitorInfo.width / 2;
								height = monitorInfo.height / 2;
							}
							if(cascade.mode == SimpleCascadeMode){
								if(lastCreatedContainer.window && !(lastCreatedContainer.option & InGridContainerOption)){
									if(XGetWindowAttributes(display, lastCreatedContainer.window, &windowAttributes)){
										XMoveResizeWindow(display, container[allocatedContainerAmount].window, windowAttributes.x + cascade.offsetX, windowAttributes.y + cascade.offsetY, width, height);
									}else{
										goto uncascadedPosition;
									}
								}else{
									goto uncascadedPosition;
								}
							}else{
								uncascadedPosition:{
									int x = monitorInfo.x + (monitorInfo.width - width) / 2 - border;
									int y = monitorInfo.y + (monitorInfo.height - height) / 2 - border;
									if(cascade.mode == SmartCascadeMode && lastCreatedContainer.window){
										unsigned int startingPoint = 0;
										for(currentContainer = startingPoint; currentContainer < allocatedContainerAmount; ++currentContainer){
											if(XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes)){
												if(windowAttributes.x == x && windowAttributes.y == y && (unsigned int)windowAttributes.width == width && (unsigned int)windowAttributes.height == height){
													x += cascade.offsetX;
													y += cascade.offsetY;
													if(currentContainer == startingPoint){
														++startingPoint;
													}
													currentContainer = startingPoint;
													continue;
												}
											}
										}
									}
									XMoveResizeWindow(display, container[allocatedContainerAmount].window, x, y, width, height);
								}
							}
							XMoveResizeWindow(display, event.xmaprequest.window, innerBorder, innerBorder, width - innerBorders, height - innerBorders);
							XSelectInput(display, container[allocatedContainerAmount].window, EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask);
							XSelectInput(display, event.xmaprequest.window, ButtonMotionMask | StructureNotifyMask);
							container[allocatedContainerAmount].option = NoContainerOptions;
						}else if(managementMode == GridingManagementMode){
							XSetWindowBorderWidth(display, container[allocatedContainerAmount].window, 0);
							XSetWindowBackground(display, container[allocatedContainerAmount].window, gridingContainerBackgroundColor);
							int x;
							int y;
							{
								unsigned int positionX;
								unsigned int positionY;
								if(defaultGridPosition == TopLeftDefaultGridPosition){
									positionX = 0;
									positionY = 0;
								}else if(defaultGridPosition == TopRightDefaultGridPosition){
									positionX = gridWidth - 1;
									positionY = 0;
								}else if(defaultGridPosition == BottomLeftDefaultGridPosition){
									positionX = 0;
									positionY = gridHeight - 1;
								}else if(defaultGridPosition == BottomRightDefaultGridPosition){
									positionX = gridWidth - 1;
									positionY = gridHeight - 1;
								}else{
									positionX = gridWidth / 2;
									positionY = gridHeight / 2;
								}
								getGridSlotData(monitorInfo, positionX, positionY, gridWidth, gridHeight, &x, &y, &width, &height);
							}
							XMoveResizeWindow(display, container[allocatedContainerAmount].window, monitorInfo.x + x, monitorInfo.y + y, width, height);
							XMoveResizeWindow(display, event.xmaprequest.window, innerBorder, innerBorder, width - innerBorders, height - innerBorders);
							XSelectInput(display, container[allocatedContainerAmount].window, EnterWindowMask | SubstructureRedirectMask);
							XSelectInput(display, event.xmaprequest.window, StructureNotifyMask);
							container[allocatedContainerAmount].option = InGridContainerOption;
							container[allocatedContainerAmount].gridX = 0;
							container[allocatedContainerAmount].gridY = 0;
							container[allocatedContainerAmount].gridWidth = 1;
							container[allocatedContainerAmount].gridHeight = 1;
						}else{
							XSetWindowBorderWidth(display, container[allocatedContainerAmount].window, 0);
							XSetWindowBackground(display, container[allocatedContainerAmount].window, tilingContainerBackgroundColor);









							{
								XRRMonitorInfo mi;
								for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
									mi = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount);
									if(monitorCompare(mi, monitorInfo)){



										//



									}
								}
							}









							XSelectInput(display, container[allocatedContainerAmount].window, EnterWindowMask | SubstructureRedirectMask);
							XSelectInput(display, event.xmaprequest.window, StructureNotifyMask);
							container[allocatedContainerAmount].option = InGridContainerOption;
						}
					}
					XMapRaised(display, container[allocatedContainerAmount].window);
					XMapWindow(display, event.xmaprequest.window);
					XSetInputFocus(display, event.xmaprequest.window, RevertToPointerRoot, CurrentTime);
					lastCreatedContainer.window = container[allocatedContainerAmount].window;
					lastCreatedContainer.option = container[allocatedContainerAmount].option;
					container[allocatedContainerAmount].subwindow = event.xmaprequest.window;
					if(++allocatedContainerAmount == containerAmount){
						containerDirective = IncreaseContainerDirective;
						saveOpenClients:{
							FILE *const file = fopen(subwindowsPath, "w");
							if(file){
								for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
									XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes);
									fprintf(file, "%lu %i %i %u %u %u\n", container[currentContainer].subwindow, windowAttributes.x, windowAttributes.y, windowAttributes.width, windowAttributes.height, container[currentContainer].option);
								}
								fclose(file);
							}
							break;
						}
					}
				}else if(event.type == ConfigureRequest){
					CONFIGUREREQUEST
				}else if(event.type == ClientMessage){
					//



				}else if(event.type == RRScreenChangeNotify + rrEventBase){
					mode = RestartMode;
					break;
				}
			}
			{
				const Window rootWindow = XDefaultRootWindow(display);
				Window w;
				Window s;
				XSelectInput(display, rootWindow, NoEventMask);
				for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
					w = container[currentContainer].window;
					s = container[currentContainer].subwindow;
					ungrabContainerKeysButtons(w, shortcutAmount, shortcut, buttonAmount, button);
					XSelectInput(display, s, NoEventMask);
					XSelectInput(display, w, NoEventMask);
					XUnmapWindow(display, s);
					XUnmapWindow(display, w);
					XReparentWindow(display, s, rootWindow, 0, 0);
					XDestroyWindow(display, w);
				}
			}
			if(separatorsExist){
				unsigned int currentSeparator;
				for(currentSeparator = 0; currentSeparator < mappedSeparatorAmount; ++currentSeparator){
					XUnmapWindow(display, separator[currentSeparator]);
				}
				--containerAmount;
				for(currentSeparator = 0; currentSeparator < containerAmount; ++currentSeparator){
					XDestroyWindow(display, separator[currentSeparator]);
				}
				++containerAmount;
				mappedSeparatorAmount = 0;
				separatorsExist = 0;
			}
			if(containerDirective == IncreaseContainerDirective){
				containerAmount += containerIncrementAmount;
				containerDirective = NoContainerDirective;
			}else if(containerDirective == DecreaseContainerDirective){
				containerAmount -= containerIncrementAmount;
				containerDirective = NoContainerDirective;
			}
		}while(mode == ContinueMode);
	}
	ungrabRootKeysButtons(shortcutAmount, shortcut, buttonAmount, button);
	return;
}
static void grabRootKeysButtons(const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button){
	unsigned int current;
	const Window rootWindow = XDefaultRootWindow(display);
	for(current = 0; current < shortcutAmount; ++current){
		if(shortcut[current].command <= RootCommandCeiling){
			if(shortcut[current].keycode != AnyKey){
				XGrabKey(display, shortcut[current].keycode, shortcut[current].masks, rootWindow, True, GrabModeAsync, GrabModeAsync);
			}
		}
	}
	for(current = 0; current < buttonAmount; ++current){
		if(button[current].command <= RootCommandCeiling){
			if(button[current].button != AnyButton){
				XGrabButton(display, button[current].button, button[current].masks, rootWindow, True, NoEventMask, GrabModeAsync, GrabModeAsync, None, None);
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
static XRRMonitorInfo getPointerMonitorInfo(const XRRMonitorInfo *const monitors, const unsigned int monitorAmount){
	unsigned int current;
	if(monitorAmount == 1){
		current = 0;
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
		for(current = 0; current < monitorAmount; ++current){
			if(monitors[current].x <= x && monitors[current].x + monitors[current].width > x && monitors[current].y <= y && monitors[current].y + monitors[current].height > y){
				goto emergencyExit;
			}
		}
		if(current == monitorAmount){
			current = 0;
		}
	}
	emergencyExit:{}
	return monitors[current];
}
static XRRMonitorInfo getWindowMonitorInfo(const Window w, const XRRMonitorInfo *const monitors, const unsigned int monitorAmount){
	XRRMonitorInfo monitorInfo;
	if(monitorAmount == 1){
		monitorInfo = *monitors;
	}else{
		unsigned int current;
		XWindowAttributes windowAttributes;
		unsigned int pixels;
		unsigned int height;
		unsigned int mostPixels = 0;
		unsigned int monitorToUse = 0;
		XGetWindowAttributes(display, w, &windowAttributes);
		if(windowAttributes.border_width){
			windowAttributes.border_width *= 2;
			windowAttributes.width += windowAttributes.border_width;
			windowAttributes.height += windowAttributes.border_width;
		}
		for(current = 0; current < monitorAmount; ++current){
			monitorInfo = monitors[current];
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
				monitorToUse = current;
			}
		}
		monitorInfo = monitors[monitorToUse];
	}
	return monitorInfo;
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
static void createGrid(const XRRMonitorInfo *const monitors, const unsigned int monitorAmount, const unsigned int gridWidth, const unsigned int gridHeight, const ARGB gridSubwindowBorderColor, const ARGB gridSubwindowBackgroundColor, Window *const grid){
	if(monitorAmount){
		unsigned int currentMonitor;
		const Window rootWindow = XDefaultRootWindow(display);
		XVisualInfo visualInfo;
		XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo);
		const uint16_t windowAttributesMasks = CWBackPixel | CWBorderPixel | CWOverrideRedirect | CWColormap;
		XSetWindowAttributes windowAttributes = {
			.background_pixel = 0x00000000,
			.border_pixel = 0x00000000,
			.override_redirect = True,
			.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone)
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
			grid[currentMonitor] = XCreateWindow(display, rootWindow, monitors[currentMonitor].x, monitors[currentMonitor].y, monitors[currentMonitor].width, monitors[currentMonitor].height, 0, visualInfo.depth, InputOutput, visualInfo.visual, windowAttributesMasks, &windowAttributes);
			width = monitors[currentMonitor].width / gridWidth;
			height = monitors[currentMonitor].height / gridHeight;
			abnormalWidth = monitors[currentMonitor].width - (gridWidth - 1) * width;
			abnormalHeight = monitors[currentMonitor].height - (gridHeight - 1) * height;
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
	return;
}
static void moveInGridContainerToMonitor(const XRRMonitorInfo m, const Container c, const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int innerBorders){
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	{
		int x1;
		int y1;
		getGridSlotData(m, c.gridX, c.gridY, gridWidth, gridHeight, &x, &y, NULL, NULL);
		getGridSlotData(m, c.gridX + c.gridWidth - 1, c.gridY + c.gridHeight - 1, gridWidth, gridHeight, &x1, &y1, &width, &height);
		width += x1 - x;
		height += y1 - y;
	}
	XMoveResizeWindow(display, c.window, m.x + x, m.y + y, width, height);
	XResizeWindow(display, c.subwindow, width - innerBorders, height - innerBorders);
	return;
}
static void moveContainerToMonitor(const XRRMonitorInfo source, const XRRMonitorInfo destination, const Window window, const Window subwindow, const unsigned int border, const unsigned int innerBorders){
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	{
		XWindowAttributes windowAttributes;
		XGetWindowAttributes(display, window, &windowAttributes);
		windowAttributes.x -= border;
		windowAttributes.y -= border;
		unsigned int percent = source.width / 100;
		if(windowAttributes.x < source.x){
			x = (source.x - windowAttributes.x) / percent;
		}else{
			x = (windowAttributes.x - source.x) / percent;
		}
		width = windowAttributes.width / percent;
		percent = destination.width / 100;
		x = destination.x + (percent * x);
		width *= percent;
		percent = source.height / 100;
		if(windowAttributes.y < source.y){
			y = (source.y - windowAttributes.y) / percent;
		}else{
			y = (windowAttributes.y - source.y) / percent;
		}
		height = windowAttributes.height / percent;
		percent = destination.height / 100; 
		y = destination.y + (percent * y);
		height *= percent;
		if(!width){
			width = innerBorders + 1;
		}
		if(!height){
			height = innerBorders + 1;
		}
	}
	XMoveResizeWindow(display, window, x, y, width, height);
	XResizeWindow(display, subwindow, width - innerBorders, height - innerBorders);
	return;
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
	unsigned int amount;
	Atom *const property = XListProperties(display, source, (int *)&amount);
	if(property){
		{
			Atom type;
			int format;
			unsigned long int itemAmount;
			unsigned long int bytesAfter;
			unsigned char *data;
			const long int size = sizeof(Atom);
			for(unsigned int current = 0; current < amount; ++current){
				if(XGetWindowProperty(display, source, property[current], 0, size, False, AnyPropertyType, &type, &format, &itemAmount, &bytesAfter, &data) == Success){
					if(data){
						XChangeProperty(display, destination, property[current], type, format, PropModeReplace, data, itemAmount);
						XFree(data);
					}
				}
			}
		}
		XFree(property);
	}
	return;
}
static void ungrabContainerKeysButtons(const Window w, const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button){
	unsigned int current;
	for(current = 0; current < shortcutAmount; ++current){
		if(shortcut[current].command > RootCommandCeiling){
			if(shortcut[current].keycode != AnyKey){
				XUngrabKey(display, shortcut[current].keycode, shortcut[current].masks, w);
			}
		}
	}
	for(current = 0; current < buttonAmount; ++current){
		if(button[current].command > RootCommandCeiling){
			if(button[current].button != AnyButton){
				XUngrabButton(display, button[current].button, button[current].masks, w);
			}
		}
	}
	return;
}
static void ungrabRootKeysButtons(const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button){
	unsigned int current;
	const Window rootWindow = XDefaultRootWindow(display);
	for(current = 0; current < shortcutAmount; ++current){
		if(shortcut[current].command <= RootCommandCeiling){
			if(shortcut[current].keycode != AnyKey){
				XUngrabKey(display, shortcut[current].keycode, shortcut[current].masks, rootWindow);
			}
		}
	}
	for(current = 0; current < buttonAmount; ++current){
		if(button[current].command <= RootCommandCeiling){
			if(button[current].button != AnyButton){
				XUngrabButton(display, button[current].button, button[current].masks, rootWindow);
			}
		}
	}
	return;
}
