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
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xrandr.h>
#include "headers/defines.h"
#include "headers/eventLoopDefines.h"
#include "headers/printEvent.h"

#define NoOptions /*-----------------------------*/ 0
#define FloatingFollowGrid /*--------------------*/ (1 << 0)
#define FloatingMinimalMoveOption /*-------------*/ (1 << 1)
#define FloatingMinimalResizeOption /*-----------*/ (1 << 2)
#define FloatingAllowStickingOption /*-----------*/ (1 << 3)
#define FloatingFollowSizeRequestsOption /*------*/ (1 << 4)
#define FloatingPortWindowsFromGriddingOption /*-*/ (1 << 5)
#define GriddingAllowBoundaryBreakXOption /*-----*/ (1 << 6)
#define GriddingAllowBoundaryBreakYOption /*-----*/ (1 << 7)
#define GriddingPortWindowsFromFloatingOption /*-*/ (1 << 8)
#define TilingUseGapsOption /*-------------------*/ (1 << 9)
#define TilingUseSeparatorsOption /*-------------*/ (1 << 10)
#define TilingMinimalResizeOption /*-------------*/ (1 << 11)

#define NoDefaultGridPosition /*-----------------*/ 0
#define CenterDefaultGridPosition /*-------------*/ 1
#define TopLeftDefaultGridPosition /*------------*/ 2
#define TopRightDefaultGridPosition /*-----------*/ 3
#define BottomLeftDefaultGridPosition /*---------*/ 4
#define BottomRightDefaultGridPosition /*--------*/ 5

#define FloatingManagementMode /*----------------*/ 1
#define GriddingManagementMode /*----------------*/ 2
#define TilingManagementMode /*------------------*/ 3

#define NoCommand /*-----------------------------*/ 0
#define SystemCommand /*-------------------------*/ 1
#define FloatingModeCommand /*-------------------*/ 2
#define GriddingModeCommand /*-------------------*/ 3
#define TilingModeCommand /*---------------------*/ 4
#define ShowGridCommand /*-----------------------*/ 5
#define EnlargeGridXCommand /*-------------------*/ 6
#define EnlargeGridYCommand /*-------------------*/ 7
#define EnlargeGridCommand /*--------------------*/ 8
#define ShrinkGridXCommand /*--------------------*/ 9
#define ShrinkGridYCommand /*--------------------*/ 10
#define ShrinkGridCommand /*---------------------*/ 11
#define ToggleGapsCommand /*---------------------*/ 12
#define RecascadeCommand /*----------------------*/ 13
#define RestartCommand /*------------------------*/ 14
#define ExitCommand /*---------------------------*/ 15
#define MoveCommand /*---------------------------*/ 16
#define MoveCenterCommand /*---------------------*/ 17
#define MoveTopCommand /*------------------------*/ 18
#define MoveBottomCommand /*---------------------*/ 19
#define MoveLeftCommand /*-----------------------*/ 20
#define MoveRightCommand /*----------------------*/ 21
#define MoveTopLeftCommand /*--------------------*/ 22
#define MoveTopRightCommand /*-------------------*/ 23
#define MoveBottomLeftCommand /*-----------------*/ 24
#define MoveBottomRightCommand /*----------------*/ 25
#define MoveNextMonitorCommand /*----------------*/ 26
#define MovePreviousMonitorCommand /*------------*/ 27
#define MoveAboveMonitorCommand /*---------------*/ 28
#define MoveBelowMonitorCommand /*---------------*/ 29
#define MoveLeftMonitorCommand /*----------------*/ 30
#define MoveRightMonitorCommand /*---------------*/ 31
// #define RevolveMonitorsCommand /*----------------*/ 32
#define AddWindowToGridCommand /*----------------*/ 33
#define RemoveWindowFromGridCommand /*-----------*/ 34
#define ToggleWindowGridCommand /*---------------*/ 35
#define MoveAboveGridSlotCommand /*--------------*/ 36
#define MoveBelowGridSlotCommand /*--------------*/ 37
#define MoveNextGridSlotCommand /*---------------*/ 38
#define MovePreviousGridSlotCommand /*-----------*/ 39
#define MoveUpOnGridCommand /*-------------------*/ 40
#define MoveDownOnGridCommand /*-----------------*/ 41
#define MoveLeftOnGridCommand /*-----------------*/ 42
#define MoveRightOnGridCommand /*----------------*/ 43
#define ExtendWindowUpCommand /*-----------------*/ 44
#define ExtendWindowDownCommand /*---------------*/ 45
#define ExtendWindowLeftCommand /*---------------*/ 46
#define ExtendWindowRightCommand /*--------------*/ 47
#define ExtendWindowUpLeftCommand /*-------------*/ 48
#define ExtendWindowUpRightCommand /*------------*/ 49
#define ExtendWindowDownLeftCommand /*-----------*/ 50
#define ExtendWindowDownRightCommand /*----------*/ 51
#define ShrinkWindowUpCommand /*-----------------*/ 52
#define ShrinkWindowDownCommand /*---------------*/ 53
#define ShrinkWindowLeftCommand /*---------------*/ 54
#define ShrinkWindowRightCommand /*--------------*/ 55
#define ShrinkWindowUpLeftCommand /*-------------*/ 56
#define ShrinkWindowUpRightCommand /*------------*/ 57
#define ShrinkWindowDownLeftCommand /*-----------*/ 58
#define ShrinkWindowDownRightCommand /*----------*/ 59
#define FullscreenCommand /*---------------------*/ 60
#define BigscreenCommand /*----------------------*/ 61
#define CloseCommand /*--------------------------*/ 62
#define KillCommand /*---------------------------*/ 63
#define DetachWindowCommand /*-------------------*/ 64

#define RootCommandCeiling /*--------------------*/ ExitCommand

#define NoCascadeMode /*-------------------------*/ 0
#define SimpleCascadeMode /*---------------------*/ 1
#define SmartCascadeMode /*----------------------*/ 2

#define NoMotionOptions /*-----------------------*/ 0
#define CanActOption /*--------------------------*/ (1 << 0)
#define HasLockedXOption /*----------------------*/ (1 << 1)
#define HasLockedYOption /*----------------------*/ (1 << 2)

#define NoMotionAction /*------------------------*/ 0
#define MoveMotionAction /*----------------------*/ 1
#define ResizeMotionAction /*--------------------*/ 2

#define NoMotionSubaction /*---------------------*/ 0
#define UpResizeMotionSubaction /*---------------*/ 1
#define DownResizeMotionSubaction /*-------------*/ 2
#define LeftResizeMotionSubaction /*-------------*/ 3
#define RightResizeMotionSubaction /*------------*/ 4
#define UpLeftResizeMotionSubaction /*-----------*/ 5
#define UpRightResizeMotionSubaction /*----------*/ 6
#define DownLeftResizeMotionSubaction /*---------*/ 7
#define DownRightResizeMotionSubaction /*--------*/ 8

#define NoContainerDirective /*------------------*/ 0
#define IncreaseContainerDirective /*------------*/ 1
#define DecreaseContainerDirective /*------------*/ 2

#define NoContainerOptions /*--------------------*/ 0
#define InPlaceContainerOption /*----------------*/ (1 << 0)

#define NoPointerInfo /*-------------------------*/ 0
#define ChangeToFloatingPointerInfo /*-----------*/ (1 << 0)
#define ChangeToGriddingPointerInfo /*-----------*/ (1 << 1)
#define ChangeToTilingPointerInfo /*-------------*/ (1 << 2)
#define MovePointerInfo /*-----------------------*/ (1 << 3)
#define RecascadePointerInfo /*------------------*/ (1 << 4)
#define AddToGridPointerInfo /*------------------*/ (1 << 5)
#define RemoveFromGridPointerInfo /*-------------*/ (1 << 6)
#define FullscreenPointerInfo /*-----------------*/ (1 << 7)
#define BigscreenPointerInfo /*------------------*/ (1 << 8)
#define MapPointerInfo /*------------------------*/ (1 << 9)

#define NoChanges /*-----------------------------*/ 1
#define ExtendChange /*--------------------------*/ 0
#define ShrinkChange /*--------------------------*/ 2

#define NoCascadeOptions /*----------------------*/ 0
#define OverrideGridWindowsCascadeOption /*------*/ (1 << 0)
#define OverrideMaximizedWindowsCascadeOption /*-*/ (1 << 1)

#define monitorCompare(m0, m1) ( \
	m0.name == m1.name && \
	m0.primary == m1.primary && \
	m0.automatic == m1.automatic && \
	m0.noutput == m1.noutput && \
	m0.x == m1.x && \
	m0.y == m1.y && \
	m0.width == m1.width && \
	m0.height == m1.height && \
	m0.mwidth == m1.mwidth && \
	m0.mheight == m1.mheight \
)

extern const char *programName;
extern Mode mode;
extern Display *display;

typedef uint16_t PointerInfo;
typedef uint32_t ARGB;
typedef uint8_t ManagementMode;
typedef uint16_t Options;
typedef uint8_t DefaultGridPosition;
typedef uint8_t ContainerDirective;
typedef uint8_t ContainerOption;
typedef uint8_t Change;
typedef uint8_t CascadeOptions;

typedef struct{
	uint8_t mode;
	CascadeOptions options;
	int offsetX;
	int offsetY;
} Cascade;

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
	int oldX;
	int oldY;
	unsigned int oldWidth;
	unsigned int oldHeight;
	ARGB oldBackgroundColor;
	bool shouldChangeProperty;
} MaximizedContainer;

inline static void grabRootKeysButtons(const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button);
inline static void grabContainerKeysButtons(const Window w, const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button);
static unsigned int getUnsignedInteger(FILE *const file, const char endCharacter);
static int getInteger(FILE *const file, const char endCharacter);
static bool containerIsMaximized(const Window w, const MaximizedContainer *const maximizedContainer, const unsigned int monitorAmount);
static bool findContainer(const Window w, const Container *const c, const unsigned int allocatedContainerAmount, unsigned int *const currentContainer);
static XRRMonitorInfo getPointerMonitorInfo(const XRRMonitorInfo *const monitors, const unsigned int monitorAmount);
static XRRMonitorInfo getWindowMonitorInfo(const Window w, const XRRMonitorInfo *const monitors, const unsigned int monitorAmount);
static void getGridSlotData(const XRRMonitorInfo monitorInfo, const unsigned int gridX, const unsigned int gridY, const unsigned int gridWidth, const unsigned int gridHeight, int *const x, int *const y, unsigned int *const width, unsigned int *const height);
static void createGrid(const XRRMonitorInfo *const monitors, const unsigned int monitorAmount, const unsigned int gridWidth, const unsigned int gridHeight, const ARGB gridSubwindowBorderColor, const ARGB gridSubwindowBackgroundColor, Window *const grid);
static void unmaximizeContainer(const Window w, const unsigned int monitorAmount, const ARGB floatingContainerBackgroundColor, const unsigned int shadow, const unsigned int borderX, const unsigned int borderY, MaximizedContainer *const maximizedContainer);
static void moveContainerToGridPosition(const Container container, const XRRMonitorInfo monitorInfo, const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int borderX, const unsigned int borderY);
static void moveContainerToMonitor(const XRRMonitorInfo source, const XRRMonitorInfo destination, const Window window, const Window subwindow, const unsigned int shadow, const unsigned int borderX, const unsigned int borderY);
inline static void clearWindowProperties(const Window w);
inline static void copyWindowProperties(const Window source, const Window destination);
inline static void ungrabContainerKeysButtons(const Window w, const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button);
inline static void ungrabRootKeysButtons(const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button);

void eventLoop(void){
	ManagementMode managementMode = FloatingManagementMode;
	Options option = FloatingMinimalMoveOption | FloatingMinimalResizeOption | FloatingAllowStickingOption | FloatingPortWindowsFromGriddingOption | GriddingAllowBoundaryBreakXOption | GriddingAllowBoundaryBreakYOption | GriddingPortWindowsFromFloatingOption | TilingUseGapsOption | TilingUseSeparatorsOption | TilingMinimalResizeOption;
	PointerInfo pointerInfo = ChangeToFloatingPointerInfo | ChangeToGriddingPointerInfo | MovePointerInfo | MapPointerInfo;
	DefaultGridPosition defaultGridPosition = CenterDefaultGridPosition;

	Cascade cascade = {
		.mode = SmartCascadeMode,
		.options = OverrideGridWindowsCascadeOption | OverrideMaximizedWindowsCascadeOption,
		.offsetX = 20,
		.offsetY = 20
	};

	MotionContainer motionContainer = {
		.action = NoMotionAction,
		.subaction = NoMotionSubaction,
		.options = NoMotionOptions
	};

	char *subwindowsPath = "/home/steven/.microwm/.subwindows";
	char *maximizedWindowsPath = "/home/steven/.microwm/.maximizedWindows";
	char *separatorsPath = "/home/steven/.microwm/.separators";



	// bool tilingPrioritizeY = 1;



	unsigned int floatingExtendWidth = 10;
	unsigned int floatingExtendHeight = 10;
	unsigned int floatingShrinkWidth = 10;
	unsigned int floatingShrinkHeight = 10;
	int floatingStickyThresholdX = 10;
	int floatingStickyThresholdY = 10;
	int floatingDistanceToTravelX = 50;
	int floatingDistanceToTravelY = 50;
	unsigned int tilingGapsX = 10;
	unsigned int tilingGapsY = 10;
	unsigned int tilingExtendWidth = 10;
	unsigned int tilingExtendHeight = 10;
	// unsigned int tilingShrinkWidth = 10;
	// unsigned int tilingShrinkHeight = 10;
	unsigned int tilingMinimumWidth = 20;
	unsigned int tilingMinimumHeight = 20;



	/*unsigned int tilingResizeX = 20;
	unsigned int tilingResizeY = 20;*/



	unsigned int gapsX;
	unsigned int gapsY;
	if(option & TilingUseGapsOption){
		gapsX = tilingGapsX;
		gapsY = tilingGapsY;
	}else{
		gapsX = 0;
		gapsY = 0;
	}

	Window lastCreatedWindow = None;

	ContainerDirective containerDirective = NoContainerDirective;
	unsigned int containerIncrementDecrementAmount = 5;

	unsigned int defaultContainerAmount = 5;
	unsigned int containerAmount = defaultContainerAmount;
	unsigned int allocatedContainerAmount = 0;
	XWindowAttributes windowAttributes;



	unsigned int shadow = 10;
	unsigned int borderUp = 1;
	unsigned int borderDown = 1;
	unsigned int borderLeft = 1;
	unsigned int borderRight = 1;
	const unsigned int borderX = borderLeft + borderRight;
	const unsigned int borderY = borderUp + borderDown;



	if(tilingMinimumWidth < borderX + 1){
		tilingMinimumWidth = borderX + 1;
	}
	if(tilingMinimumHeight < borderY + 1){
		tilingMinimumHeight = borderY + 1;
	}



	ARGB containerShadowColor = 0x7F000000;
	ARGB floatingContainerBackgroundColor = 0xFF00FF00;
	ARGB griddingContainerBackgroundColor = 0xFFFF0000;
	ARGB tilingContainerBackgroundColor = 0xFF0000FF;
	ARGB inGridContainerBackgroundColor = 0xFFFF7F00;
	ARGB gridSubwindowBorderColor = 0x10975C57;
	ARGB gridSubwindowBackgroundColor = 0x00000000;
	ARGB separatorBorderColor = 0xFFFFFFFF;
	ARGB separatorBackgroundColor = 0xFF000000;

	ARGB fullscreenContainerBackgroundColor = 0xFFFFFFFF;
	ARGB bigscreenContainerBackgroundColor = 0xFFFF007F;



	unsigned int gridWidth = 2;
	unsigned int gridHeight = 2;

	unsigned int separatorWidth = 12;
	unsigned int separatorBorder = 1;
	const unsigned int separatorBorders = 2 * separatorBorder;

	unsigned int currentContainer;

	bool separatorsExist = 0;
	unsigned int separatorAmount = 0;
	unsigned int mappedSeparatorAmount = 0;



	unsigned int monitorAmount;
	{
		XRRMonitorInfo *const monitorInfo = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&monitorAmount);
		if(monitorInfo){
			XRRFreeMonitors(monitorInfo);
		}else{
			monitorAmount = 1;
		}
	}
	MaximizedContainer maximizedContainer[monitorAmount];
	XRRMonitorInfo monitors[monitorAmount];
	unsigned int maxGridWidth = 20;
	unsigned int maxGridHeight = 20;
	{
		unsigned int ma;
		XRRMonitorInfo *const monitorInfo = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&ma);
		if(monitorInfo){
			if(ma == monitorAmount){
				unsigned int currentMonitor;
				{
					unsigned int width;
					unsigned int height;
					for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
						maximizedContainer[currentMonitor].window = None;
						maximizedContainer[currentMonitor].subwindow = None;
						monitors[currentMonitor] = monitorInfo[currentMonitor];
						width = monitors[currentMonitor].width / 3;
						height = monitors[currentMonitor].height / 3;
						if(maxGridWidth > width){
							maxGridWidth = width;
						}
						if(maxGridHeight > height){
							maxGridHeight = height;
						}
					}
				}
			}
			XRRFreeMonitors(monitorInfo);
		}
	}
	Window moveResizeWindow;
	unsigned int moveResizeWindowBorder = 1;
	if(option & FloatingMinimalMoveOption || option & FloatingMinimalResizeOption){
		const Window rootWindow = XDefaultRootWindow(display);
		ARGB moveResizeWindowBackgroundColor = 0x7FF07746;
		ARGB moveResizeWindowBorderColor = 0xFFF2C6B4;
		XVisualInfo visualInfo;
		XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo);
		XSetWindowAttributes windowAttributes = {
			.background_pixel = moveResizeWindowBackgroundColor,
			.border_pixel = moveResizeWindowBorderColor,
			.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone)
		};
		moveResizeWindow = XCreateWindow(display, rootWindow, 0, 0, 1, 1, moveResizeWindowBorder, visualInfo.depth, InputOutput, visualInfo.visual, CWBackPixel | CWBorderPixel | CWColormap, &windowAttributes);
	}



	bool canConfigurePosition = 1;
	Window commandedWindow = None;



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
				XRRSelectInput(display, XDefaultRootWindow(display), RRScreenChangeNotifyMask);
			}
		}
		XSync(display, False);
		do{
			fprintf(stdout, "begin\n");
			SETUP_CONTAINERS_SEPARATORS
			for(;;){
				XNextEvent(display, &event);
				printEvent(event);
				/*for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){
					fprintf(stdout, "%lu -> %lu\n", container[currentContainer].window, container[currentContainer].subwindow);
				}
				fprintf(stdout, "lastCreatedWindow: %lu\nallocatedContainerAmount: %u\n", lastCreatedWindow, allocatedContainerAmount);
				{
					Container c;
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
						c = container[currentContainer];
						fprintf(stdout, "\n(%u, %u) -> (%u, %u)\n", c.gridX, c.gridY, c.gridX + c.gridWidth, c.gridY);
						fprintf(stdout, "   Λ         |\n   |         V\n");
						fprintf(stdout, "(%u, %u) <- (%u, %u)\n\n", c.gridX, c.gridY + c.gridHeight, c.gridX + c.gridWidth, c.gridY + c.gridHeight);
					}
				}*/
				if(event.type == KeyPress || event.type == ButtonPress){
					KEYBUTTONPRESS
				}else if(event.type == KeyRelease || event.type == ButtonRelease){
					KEYBUTTONRELEASE
				}else if(event.type == MotionNotify){
					MOTIONNOTIFY
				}else if(event.type == EnterNotify){
					ENTERNOTIFY
				}else if(event.type == UnmapNotify){
					UNMAPNOTIFY
				}else if(event.type == MapRequest){
					copyWindowProperties(event.xmaprequest.window, container[allocatedContainerAmount].window);
					XRRMonitorInfo monitorInfo;
					if(pointerInfo & MapPointerInfo){
						monitorInfo = getPointerMonitorInfo(monitors, monitorAmount);
					}else{
						monitorInfo = getWindowMonitorInfo(event.xmaprequest.window, monitors, monitorAmount);
					}
					XMoveResizeWindow(display, container[allocatedContainerAmount].window, monitorInfo.x, monitorInfo.y, monitorInfo.width / gridWidth, monitorInfo.height / gridHeight);
					XReparentWindow(display, event.xmaprequest.window, container[allocatedContainerAmount].window, borderLeft, borderUp);
					container[allocatedContainerAmount].subwindow = event.xmaprequest.window;
					{
						unsigned int width;
						unsigned int height;
						if(managementMode == FloatingManagementMode){
							XSetWindowBorderWidth(display, container[allocatedContainerAmount].window, shadow);
							XSetWindowBackground(display, container[allocatedContainerAmount].window, floatingContainerBackgroundColor);
							if(option & FloatingFollowGrid){
								width = monitorInfo.width / gridWidth;
								height = monitorInfo.height / gridHeight;
							}else{
								width = monitorInfo.width / 2;
								height = monitorInfo.height / 2;
							}
							if(cascade.mode == SimpleCascadeMode){
								if(lastCreatedWindow){
									const XRRMonitorInfo monitorInfo1 = getWindowMonitorInfo(lastCreatedWindow, monitors, monitorAmount);
									if(monitorCompare(monitorInfo1, monitorInfo)){
										for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
											if(container[currentContainer].window == lastCreatedWindow){
												break;
											}
										}
										if(currentContainer < allocatedContainerAmount && !(container[currentContainer].option & InPlaceContainerOption || containerIsMaximized(container[currentContainer].window, maximizedContainer, monitorAmount))){
											XGetWindowAttributes(display, lastCreatedWindow, &windowAttributes);
											XMoveResizeWindow(display, container[allocatedContainerAmount].window, windowAttributes.x + cascade.offsetX, windowAttributes.y + cascade.offsetY, width, height);
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
									int x = monitorInfo.x + (monitorInfo.width - width) / 2 - shadow;
									int y = monitorInfo.y + (monitorInfo.height - height) / 2 - shadow;
									if(cascade.mode == SmartCascadeMode && lastCreatedWindow){
										unsigned int startingPoint = 0;
										x += cascade.offsetX;
										y += cascade.offsetY;
										for(currentContainer = startingPoint; currentContainer < allocatedContainerAmount; ++currentContainer){
											XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes);
											if(windowAttributes.x == x && windowAttributes.y == y && (unsigned int)windowAttributes.width == width && (unsigned int)windowAttributes.height == height){
												x += cascade.offsetX;
												y += cascade.offsetY;
												if(currentContainer == startingPoint){
													++startingPoint;
												}
												currentContainer = startingPoint;
											}
										}
									}
									XMoveResizeWindow(display, container[allocatedContainerAmount].window, x, y, width, height);
								}
							}
							XMoveResizeWindow(display, event.xmaprequest.window, borderLeft, borderUp, width - borderX, height - borderY);
							XSelectInput(display, container[allocatedContainerAmount].window, EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask);
							XSelectInput(display, event.xmaprequest.window, ButtonMotionMask | StructureNotifyMask);
							container[allocatedContainerAmount].option = NoContainerOptions;
						}else{
							XSetWindowBorderWidth(display, container[allocatedContainerAmount].window, 0);
							if(managementMode == GriddingManagementMode){
								XSetWindowBackground(display, container[allocatedContainerAmount].window, griddingContainerBackgroundColor);
								int x;
								int y;
								{
									unsigned int positionX;
									unsigned int positionY;
									if(defaultGridPosition == CenterDefaultGridPosition){
										positionX = gridWidth / 2;
										positionY = gridHeight / 2;
									}else if(defaultGridPosition == TopLeftDefaultGridPosition){
										positionX = 0;
										positionY = 0;
									}else if(defaultGridPosition == TopRightDefaultGridPosition){
										positionX = gridWidth - 1;
										positionY = 0;
									}else if(defaultGridPosition == BottomLeftDefaultGridPosition){
										positionX = 0;
										positionY = gridHeight - 1;
									}else{
										positionX = gridWidth - 1;
										positionY = gridHeight - 1;
									}
									getGridSlotData(monitorInfo, positionX, positionY, gridWidth, gridHeight, &x, &y, &width, &height);
									container[allocatedContainerAmount].gridX = positionX;
									container[allocatedContainerAmount].gridY = positionY;
								}
								XMoveResizeWindow(display, container[allocatedContainerAmount].window, monitorInfo.x + x, monitorInfo.y + y, width, height);
								XMoveResizeWindow(display, event.xmaprequest.window, borderLeft, borderUp, width - borderX, height - borderY);
								container[allocatedContainerAmount].gridWidth = 1;
								container[allocatedContainerAmount].gridHeight = 1;
							}else{
								XSetWindowBackground(display, container[allocatedContainerAmount].window, tilingContainerBackgroundColor);
								bool containerInMonitorMap[allocatedContainerAmount + 1];
								unsigned int monitorContainerAmount = 0;
								{
									XRRMonitorInfo mi;
									for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
										mi = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount);
										if(monitorCompare(mi, monitorInfo)){
											containerInMonitorMap[currentContainer] = 1;
											++monitorContainerAmount;
										}else{
											containerInMonitorMap[currentContainer] = 0;
										}
									}
								}
								containerInMonitorMap[allocatedContainerAmount] = 1;
								++monitorContainerAmount;
								++allocatedContainerAmount;
								height = monitorInfo.height - 2 * gapsY;
								const unsigned int totalSeparatorWidth = separatorWidth + separatorBorders;
								const unsigned int middleX = monitorContainerAmount / 2;
								const int y = monitorInfo.y + gapsY;
								const unsigned int subwindowHeight = height - borderY;
								const unsigned int separatorHeight = height - separatorBorders;
								const unsigned int separatorWidthGaps = totalSeparatorWidth + gapsX;
								unsigned int normalWidth;
								unsigned int abnormalWidth;
								{
									unsigned int reservedSpace;
									if(option & TilingUseSeparatorsOption){
										reservedSpace = 2 * monitorContainerAmount * gapsX + (monitorContainerAmount - 1) * totalSeparatorWidth;
									}else{
										reservedSpace = (monitorContainerAmount + 1) * gapsX;
									}
									normalWidth = (monitorInfo.width - reservedSpace) / monitorContainerAmount;
									abnormalWidth = (monitorInfo.width - reservedSpace) - (monitorContainerAmount - 1) * normalWidth;
								}
								unsigned int counter = 0;
								int x = monitorInfo.x + gapsX;
								unsigned int currentSeparator = 0;
								width = normalWidth;
								for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
									if(containerInMonitorMap[currentContainer]){
										XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height);
										XResizeWindow(display, container[currentContainer].subwindow, width - borderX, subwindowHeight);
										if(++counter == monitorContainerAmount){
											break;
										}
										x += width + gapsX;
										if(option & TilingUseSeparatorsOption){
											XMoveResizeWindow(display, separator[currentSeparator], x, y, separatorWidth, separatorHeight);
											if(currentSeparator >= mappedSeparatorAmount){
												XMapWindow(display, separator[currentSeparator]);
												++mappedSeparatorAmount;
											}
											x += separatorWidthGaps;
											++currentSeparator;
										}
										if(counter == middleX){
											width = abnormalWidth;
										}else{
											width = normalWidth;
										}
									}
								}
								--allocatedContainerAmount;
							}
							XSelectInput(display, container[allocatedContainerAmount].window, EnterWindowMask | SubstructureRedirectMask);
							XSelectInput(display, event.xmaprequest.window, StructureNotifyMask);
							container[allocatedContainerAmount].option = InPlaceContainerOption;
						}
					}
					XMapRaised(display, container[allocatedContainerAmount].window);
					XMapWindow(display, event.xmaprequest.window);
					XSetInputFocus(display, event.xmaprequest.window, RevertToPointerRoot, CurrentTime);
					lastCreatedWindow = container[allocatedContainerAmount].window;
					if(++allocatedContainerAmount == containerAmount){
						containerDirective = IncreaseContainerDirective;
						saveOpenClients:{
							FILE *file;
							if((file = fopen(subwindowsPath, "w"))){
								for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
									XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes);
									fprintf(file, "%lu %i %i %u %u %u\n", container[currentContainer].subwindow, windowAttributes.x, windowAttributes.y, windowAttributes.width, windowAttributes.height, container[currentContainer].option);
								}
								fclose(file);
							}
							if(managementMode == TilingManagementMode && option & TilingUseSeparatorsOption){
								if((file = fopen(separatorsPath, "w"))){
									for(unsigned int currentSeparator = 0; currentSeparator < mappedSeparatorAmount; ++currentSeparator){
										XGetWindowAttributes(display, separator[currentSeparator], &windowAttributes);
										fprintf(file, "%i %i %u\n", windowAttributes.x, windowAttributes.y, windowAttributes.height);
									}
									fclose(file);
								}
							}
							break;
						}
					}
				}else if(event.type == ConfigureNotify){
					fprintf(stdout, "configure: %lu == %lu\n", event.xconfigure.window, commandedWindow);
					if(event.xany.window == commandedWindow){
						commandedWindow = None;
					}
				}else if(event.type == ConfigureRequest){
					CONFIGUREREQUEST
				}else if(event.type == ClientMessage){
					fprintf(stdout, "---------------client message---------------\n");
				}else if(event.type == RRScreenChangeNotify + rrEventBase){
					mode = RestartMode;
					break;
				}
			}
			if(mode != ExitMode){
				FILE *const file = fopen(maximizedWindowsPath, "w");
				if(file){
					for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
						fprintf(file, "%lu %i %i %u %u %u %u\n", maximizedContainer[currentMonitor].subwindow, maximizedContainer[currentMonitor].oldX, maximizedContainer[currentMonitor].oldY, maximizedContainer[currentMonitor].oldWidth, maximizedContainer[currentMonitor].oldHeight, maximizedContainer[currentMonitor].oldBackgroundColor, maximizedContainer[currentMonitor].shouldChangeProperty);
					}
					fclose(file);
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
				for(currentSeparator = 0; currentSeparator < separatorAmount; ++currentSeparator){
					XDestroyWindow(display, separator[currentSeparator]);
				}
				mappedSeparatorAmount = 0;
				separatorsExist = 0;
			}
			if(containerDirective == IncreaseContainerDirective){
				containerAmount += containerIncrementDecrementAmount;
			}else{
				containerAmount -= containerIncrementDecrementAmount;
			}
			containerDirective = NoContainerDirective;
		}while(mode == ContinueMode);
	}
	ungrabRootKeysButtons(shortcutAmount, shortcut, buttonAmount, button);
	return;
}
inline static void grabRootKeysButtons(const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button){
	const Window rootWindow = XDefaultRootWindow(display);
	unsigned int current;
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
inline static void grabContainerKeysButtons(const Window w, const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button){
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
static unsigned int getUnsignedInteger(FILE *const file, const char endCharacter){
	unsigned int number = 0;
	char c;
	while((c = fgetc(file)) != endCharacter){
		number = number * 10 + c - 48;
	}
	return number;
}
static int getInteger(FILE *const file, const char endCharacter){
	int number = 0;
	char c;
	bool negative = 0;
	while((c = fgetc(file)) != endCharacter){
		if(c == '-'){
			negative = 1;
		}else{
			number = number * 10 + c - 48;
		}
	}
	if(negative){
		number = -number;
	}
	return number;
}
static bool containerIsMaximized(const Window w, const MaximizedContainer *const maximizedContainer, const unsigned int monitorAmount){
	bool value = 0;
	for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
		if(maximizedContainer[currentMonitor].window == w){
			value = 1;
			break;
		}
	}
	return value;
}
static bool findContainer(const Window w, const Container *const c, const unsigned int allocatedContainerAmount, unsigned int *const currentContainer){
	bool value = 0;
	for(unsigned int current = 0; current < allocatedContainerAmount; ++current){
		if(c[current].window == w){
			*currentContainer = current;
			value = 1;
			break;
		}
	}
	return value;
}
static XRRMonitorInfo getPointerMonitorInfo(const XRRMonitorInfo *const monitors, const unsigned int monitorAmount){
	unsigned int current = 0;
	if(monitorAmount > 1){
		int x = 0;
		int y = 0;
		{
			Window w;
			unsigned int masks;
			XQueryPointer(display, XDefaultRootWindow(display), &w, &w, &x, &y, &x, &y, &masks);
		}
		for(;;){
			if(monitors[current].x <= x && monitors[current].x + monitors[current].width > x && monitors[current].y <= y && monitors[current].y + monitors[current].height > y){
				break;
			}
			if(++current == monitorAmount){
				current = 0;
			}
		}
	}
	return monitors[current];
}
static XRRMonitorInfo getWindowMonitorInfo(const Window w, const XRRMonitorInfo *const monitors, const unsigned int monitorAmount){
	unsigned int monitorToUse;
	if(monitorAmount > 1){
		unsigned int current;
		XWindowAttributes windowAttributes;
		XGetWindowAttributes(display, w, &windowAttributes);
		unsigned int pixels;
		unsigned int height;
		unsigned int mostPixels = 0;
		if(windowAttributes.border_width){
			windowAttributes.border_width *= 2;
			windowAttributes.width += windowAttributes.border_width;
			windowAttributes.height += windowAttributes.border_width;
		}
		for(current = 0; current < monitorAmount; ++current){
			if(monitors[current].x > windowAttributes.x + windowAttributes.width){
				continue;
			}else if(monitors[current].x <= windowAttributes.x + windowAttributes.width && monitors[current].x + monitors[current].width > windowAttributes.x + windowAttributes.width){
				pixels = windowAttributes.x + windowAttributes.width;
			}else{
				pixels = monitors[current].x + monitors[current].width;
			}
			if(monitors[current].x > windowAttributes.x){
				pixels -= monitors[current].x;
			}else if(monitors[current].x <= windowAttributes.x && monitors[current].x + monitors[current].width > windowAttributes.x){
				pixels -= windowAttributes.x;
			}else{
				continue;
			}
			if(monitors[current].y > windowAttributes.y + windowAttributes.height){
				continue;
			}else if(monitors[current].y <= windowAttributes.y + windowAttributes.height && monitors[current].y + monitors[current].height > windowAttributes.y + windowAttributes.height){
				height = windowAttributes.y + windowAttributes.height;
			}else{
				height = monitors[current].y + monitors[current].height;
			}
			if(monitors[current].y > windowAttributes.y){
				height -= monitors[current].y;
			}else if(monitors[current].y <= windowAttributes.y && monitors[current].y + monitors[current].height > windowAttributes.y){
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
	}else{
		monitorToUse = 0;
	}
	return monitors[monitorToUse];
}
static void getGridSlotData(const XRRMonitorInfo monitorInfo, const unsigned int gridX, const unsigned int gridY, const unsigned int gridWidth, const unsigned int gridHeight, int *const x, int *const y, unsigned int *const width, unsigned int *const height){
	const unsigned int normalWidth = monitorInfo.width / gridWidth;
	const unsigned int abnormalWidth = monitorInfo.width - (gridWidth - 1) * normalWidth;
	const unsigned int normalHeight = monitorInfo.height / gridHeight;
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
		const Window rootWindow = XDefaultRootWindow(display);
		const uint16_t windowAttributesMasks = CWBackPixel | CWBorderPixel | CWOverrideRedirect | CWColormap;
		const unsigned int abnormalX = gridWidth / 2;
		const unsigned int abnormalY = gridHeight / 2;
		const unsigned int gridBorder = 1;
		const unsigned int gridBorders = 2 * gridBorder;
		unsigned int currentMonitor;
		XVisualInfo visualInfo;
		XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo);
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
		unsigned int finalWidth;
		unsigned int finalHeight;
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
static void unmaximizeContainer(const Window w, const unsigned int monitorAmount, const ARGB floatingContainerBackgroundColor, const unsigned int shadow, const unsigned int borderX, const unsigned int borderY, MaximizedContainer *const maximizedContainer){
	for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
		if(maximizedContainer[currentMonitor].window == w){
			if(maximizedContainer[currentMonitor].shouldChangeProperty){
				const Atom atom = None;
				XChangeProperty(display, maximizedContainer[currentMonitor].subwindow, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1);
			}
			if(maximizedContainer[currentMonitor].oldBackgroundColor == floatingContainerBackgroundColor){
				XSetWindowBorderWidth(display, w, shadow);
			}
			XSetWindowBackground(display, w, floatingContainerBackgroundColor);
			XUnmapWindow(display, w);
			XMapWindow(display, w);
			XMoveResizeWindow(display, w, maximizedContainer[currentMonitor].oldX, maximizedContainer[currentMonitor].oldY, maximizedContainer[currentMonitor].oldWidth, maximizedContainer[currentMonitor].oldHeight);
			XResizeWindow(display, maximizedContainer[currentMonitor].subwindow, maximizedContainer[currentMonitor].oldWidth - borderX, maximizedContainer[currentMonitor].oldHeight - borderY);
			maximizedContainer[currentMonitor].window = None;
			break;
		}
	}
	return;
}
static void moveContainerToGridPosition(const Container container, const XRRMonitorInfo monitorInfo, const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int borderX, const unsigned int borderY){
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	{
		int x1;
		int y1;
		getGridSlotData(monitorInfo, container.gridX, container.gridY, gridWidth, gridHeight, &x, &y, NULL, NULL);
		getGridSlotData(monitorInfo, container.gridX + container.gridWidth - 1, container.gridY + container.gridHeight - 1, gridWidth, gridHeight, &x1, &y1, &width, &height);
		width += x1 - x;
		height += y1 - y;
	}
	XMoveResizeWindow(display, container.window, monitorInfo.x + x, monitorInfo.y + y, width, height);
	XResizeWindow(display, container.subwindow, width - borderX, height - borderY);
	return;
}
static void moveContainerToMonitor(const XRRMonitorInfo source, const XRRMonitorInfo destination, const Window window, const Window subwindow, const unsigned int shadow, const unsigned int borderX, const unsigned int borderY){
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	{
		XWindowAttributes windowAttributes;
		XGetWindowAttributes(display, window, &windowAttributes);
		unsigned int sourcePercent;
		unsigned int destinationPercent;
		windowAttributes.x -= shadow;
		windowAttributes.y -= shadow;
		sourcePercent = source.width / 100;
		destinationPercent = destination.width / 100;
		if(windowAttributes.x < source.x){
			x = destination.x + (destinationPercent * ((source.x - windowAttributes.x) / sourcePercent));
		}else{
			x = destination.x + (destinationPercent * ((windowAttributes.x - source.x) / sourcePercent));
		}
		width = windowAttributes.width / sourcePercent * destinationPercent;
		sourcePercent = source.height / 100;
		destinationPercent = destination.height / 100;
		if(windowAttributes.y < source.y){
			y = destination.y + (destinationPercent * ((source.y - windowAttributes.y) / sourcePercent));
		}else{
			y = destination.y + (destinationPercent * ((windowAttributes.y - source.y) / sourcePercent));
		}
		height = windowAttributes.height / sourcePercent * destinationPercent;
		if(!width){
			width = borderX + 1;
		}
		if(!height){
			height = borderY + 1;
		}
	}
	XMoveResizeWindow(display, window, x + shadow, y + shadow, width, height);
	XResizeWindow(display, subwindow, width - borderX, height - borderY);
	return;
}
inline static void clearWindowProperties(const Window w){
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
inline static void copyWindowProperties(const Window source, const Window destination){
	unsigned int amount;
	Atom *const property = XListProperties(display, source, (int *)&amount);
	if(property){
		{
			const long int size = sizeof(Atom);
			Atom type;
			int format;
			unsigned long int itemAmount;
			unsigned long int bytesAfter;
			unsigned char *data;
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
inline static void ungrabContainerKeysButtons(const Window w, const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button){
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
inline static void ungrabRootKeysButtons(const unsigned int shortcutAmount, const Shortcut *const shortcut, const unsigned int buttonAmount, const Button *const button){
	const Window rootWindow = XDefaultRootWindow(display);
	unsigned int current;
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
