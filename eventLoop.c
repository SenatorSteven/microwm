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

#define NoOptions /*------------------------------*/ 0
#define FloatingFollowGrid /*---------------------*/ (1 << 0)
#define FloatingMinimalMoveOption /*--------------*/ (1 << 1)
#define FloatingMinimalResizeOption /*------------*/ (1 << 2)
#define FloatingAllowStickingOption /*------------*/ (1 << 3)
#define FloatingAllowDirectionStickingOption /*---*/ (1 << 4)
#define FloatingUseDirectionOutlineOption /*------*/ (1 << 5)
#define FloatingFollowSizeRequestsOption /*-------*/ (1 << 6)
#define FloatingPortWindowsFromGriddingOption /*--*/ (1 << 7)
#define GriddingMinimalMoveOption /*--------------*/ (1 << 8)
#define GriddingPortWindowsFromFloatingOption /*--*/ (1 << 9)
#define TilingFollowGrid /*-----------------------*/ (1 << 10)
#define TilingUseSeparatorsOption /*--------------*/ (1 << 11)
#define TilingUseGapsOption /*--------------------*/ (1 << 12)
#define TilingMinimalMoveOption /*----------------*/ (1 << 13)
#define TilingMinimalResizeOption /*--------------*/ (1 << 14)
#define TilingSlamWindowsToDirectionOption /*-----*/ (1 << 15)

#define NoDefaultGridPosition /*------------------*/ 0
#define TopLeftDefaultGridPosition /*-------------*/ 1
#define TopRightDefaultGridPosition /*------------*/ 2
#define BottomLeftDefaultGridPosition /*----------*/ 3
#define BottomRightDefaultGridPosition /*---------*/ 4
#define CenterDefaultGridPosition /*--------------*/ 5

#define FloatingManagementMode /*-----------------*/ 1
#define GriddingManagementMode /*-----------------*/ 2
#define TilingManagementMode /*-------------------*/ 3

#define NoCommand /*------------------------------*/ 0
#define SystemCommand /*--------------------------*/ 1
#define FloatingModeCommand /*--------------------*/ 2
#define GriddingModeCommand /*--------------------*/ 3
#define TilingModeCommand /*----------------------*/ 4
#define ToggleGridCommand /*----------------------*/ 5
#define EnlargeGridXCommand /*--------------------*/ 6
#define EnlargeGridYCommand /*--------------------*/ 7
#define EnlargeGridCommand /*---------------------*/ 8
#define ShrinkGridXCommand /*---------------------*/ 9
#define ShrinkGridYCommand /*---------------------*/ 10
#define ShrinkGridCommand /*----------------------*/ 11
#define ToggleGapsCommand /*----------------------*/ 12
#define RecascadeCommand /*-----------------------*/ 13
#define AttachWindowCommand /*--------------------*/ 14
#define RestartCommand /*-------------------------*/ 15
#define ExitCommand /*----------------------------*/ 16
#define MoveCommand /*----------------------------*/ 17
#define MoveTopCommand /*-------------------------*/ 18
#define MoveBottomCommand /*----------------------*/ 19
#define MoveLeftCommand /*------------------------*/ 20
#define MoveRightCommand /*-----------------------*/ 21
#define MoveTopLeftCommand /*---------------------*/ 22
#define MoveTopRightCommand /*--------------------*/ 23
#define MoveBottomLeftCommand /*------------------*/ 24
#define MoveBottomRightCommand /*-----------------*/ 25
#define MoveCenterCommand /*----------------------*/ 26
#define MoveFullCommand /*------------------------*/ 27
#define MoveNextMonitorCommand /*-----------------*/ 28
#define MovePreviousMonitorCommand /*-------------*/ 29
#define MoveAboveMonitorCommand /*----------------*/ 30
#define MoveBelowMonitorCommand /*----------------*/ 31
#define MoveLeftMonitorCommand /*-----------------*/ 32
#define MoveRightMonitorCommand /*----------------*/ 33
#define RevolveMonitorsCommand /*-----------------*/ 34
#define AddWindowToGridCommand /*-----------------*/ 35
#define RemoveWindowFromGridCommand /*------------*/ 36
#define ToggleWindowGridCommand /*----------------*/ 37
#define MoveUpGridCommand /*----------------------*/ 38
#define MoveDownGridCommand /*--------------------*/ 39
#define MoveLeftGridCommand /*--------------------*/ 40
#define MoveRightGridCommand /*-------------------*/ 41
#define ExtendWindowUpCommand /*------------------*/ 42
#define ExtendWindowDownCommand /*----------------*/ 43
#define ExtendWindowLeftCommand /*----------------*/ 44
#define ExtendWindowRightCommand /*---------------*/ 45
#define ExtendWindowUpLeftCommand /*--------------*/ 46
#define ExtendWindowUpRightCommand /*-------------*/ 47
#define ExtendWindowDownLeftCommand /*------------*/ 48
#define ExtendWindowDownRightCommand /*-----------*/ 49
#define ShrinkWindowUpCommand /*------------------*/ 50
#define ShrinkWindowDownCommand /*----------------*/ 51
#define ShrinkWindowLeftCommand /*----------------*/ 52
#define ShrinkWindowRightCommand /*---------------*/ 53
#define ShrinkWindowUpLeftCommand /*--------------*/ 54
#define ShrinkWindowUpRightCommand /*-------------*/ 55
#define ShrinkWindowDownLeftCommand /*------------*/ 56
#define ShrinkWindowDownRightCommand /*-----------*/ 57
#define FullscreenCommand /*----------------------*/ 58
#define BigscreenCommand /*-----------------------*/ 59
#define DetachWindowCommand /*--------------------*/ 60
#define CloseCommand /*---------------------------*/ 61
#define KillCommand /*----------------------------*/ 62

#define RootCommandCeiling /*---------------------*/ ExitCommand

#define NoCascadeMode /*--------------------------*/ 0
#define SimpleCascadeMode /*----------------------*/ 1
#define SmartCascadeMode /*-----------------------*/ 2

#define NoMotionOptions /*------------------------*/ 0
#define CanActMotionOption /*---------------------*/ (1 << 0)
#define HasLockedXMotionOption /*-----------------*/ (1 << 1)
#define HasLockedYMotionOption /*-----------------*/ (1 << 2)

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
#define TopDirectionMotionSubaction /*------------*/ 9
#define BottomDirectionMotionSubaction /*---------*/ 10
#define LeftDirectionMotionSubaction /*-----------*/ 11
#define RightDirectionMotionSubaction /*----------*/ 12
#define TopLeftDirectionMotionSubaction /*--------*/ 13
#define TopRightDirectionMotionSubaction /*-------*/ 14
#define BottomLeftDirectionMotionSubaction /*-----*/ 15
#define BottomRightDirectionMotionSubaction /*----*/ 16

#define DirectionMotionSubactionOffset /*---------*/ TopDirectionMotionSubaction

#define NoPointerInfo /*--------------------------*/ 0
#define ChangeToFloatingPointerInfo /*------------*/ (1 << 0)
#define ChangeToGriddingPointerInfo /*------------*/ (1 << 1)
#define ChangeToTilingPointerInfo /*--------------*/ (1 << 2)
#define MovePointerInfo /*------------------------*/ (1 << 3)
#define RecascadePointerInfo /*-------------------*/ (1 << 4)
#define AddToGridPointerInfo /*-------------------*/ (1 << 5)
#define RemoveFromGridPointerInfo /*--------------*/ (1 << 6)
#define FullscreenPointerInfo /*------------------*/ (1 << 7)
#define BigscreenPointerInfo /*-------------------*/ (1 << 8)
#define MapPointerInfo /*-------------------------*/ (1 << 9)
#define InGridPointerInfo /*----------------------*/ (1 << 10)

#define NoChanges /*------------------------------*/ 1
#define ExtendChange /*---------------------------*/ 0
#define ShrinkChange /*---------------------------*/ 2

#define NoCascadeOptions /*-----------------------*/ 0
#define OverrideGridWindowsCascadeOption /*-------*/ (1 << 0)
#define OverrideMaximizedWindowsCascadeOption /*--*/ (1 << 1)

#define HorizontalEqualTilingPlacingMode /*-------*/ 0
#define VerticalEqualTilingPlacingMode /*---------*/ 1
#define RightDivisorTilingPlacingMode /*----------*/ 2

#define HorizontalEqualTilingReplacingMode /*-----*/ 0
#define VerticalEqualTilingReplacingMode /*-------*/ 1
#define RightDivisorTilingReplacingMode /*--------*/ 2

#define grabRootKeysButtons(void) /*--------------*/ _grabRootKeysButtons(shortcut, shortcutAmount, button, buttonAmount)
#define grabContainerKeysButtons(w) /*------------*/ _grabContainerKeysButtons(w, shortcut, shortcutAmount, button, buttonAmount)
#define getUnsignedInteger(c) /*------------------*/ _getUnsignedInteger(file, c)
#define getInteger(c) /*--------------------------*/ _getInteger(file, c)
#define containerIsMaximized(w) /*----------------*/ _containerIsMaximized(w, maximizedContainer, monitorAmount)
#define findContainer(w) /*-----------------------*/ _findContainer(w, container, allocatedContainerAmount, &currentContainer)
#define getPointerMonitorInfo(void) /*------------*/ _getPointerMonitorInfo(monitors, monitorAmount)
#define getWindowMonitorInfo(w) /*----------------*/ _getWindowMonitorInfo(w, monitors, monitorAmount)
#define createGrid(void) /*-----------------------*/ _createGrid(monitors, monitorAmount, gridWidth, gridHeight, color.gridSubwindowBorder, color.gridSubwindowBackground, grid)
#define unmaximizeContainer(w, shadow, bg) /*-----*/ _unmaximizeContainer(w, monitorAmount, shadow, bg, border.axis, maximizedContainer, &commandedWindow)
#define maximizeContainer(w, mi) /*---------------*/ _maximizeContainer(w, container[currentContainer].subwindow, container[currentContainer].inGrid, mi, command, color.containerBackground, border.axis, managementMode, &maximizedContainer[currentMonitor], &commandedWindow)
#define moveContainerToGridPosition(c, mi) /*-----*/ _moveContainerToGridPosition(c, mi, gridWidth, gridHeight, border.axis)
#define moveContainerToMonitor(w, s, src, dst) /*-*/ _moveContainerToMonitor(w, s, src, dst, shadow, border.axis)
#define ungrabRootKeysButtons(void) /*------------*/ _ungrabRootKeysButtons(shortcut, shortcutAmount, button, buttonAmount)

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

#define closedOpenInterval(point, bound0, bound1) ( \
	point >= bound0 && \
	point < bound1 \
)

#define closedInterval(point, bound0, bound1) ( \
	point >= bound0 && \
	point <= bound1 \
)



// #define FloatingResizeOpposingWindowOption /*-*/ (1 << x)



extern const char *programName;
extern Mode mode;
extern Display *display;

typedef uint16_t PointerInfo;
typedef uint32_t ARGB;
typedef uint8_t ManagementMode;
typedef uint16_t Options;
typedef uint8_t DefaultGridPosition;
typedef uint8_t Change;
typedef uint8_t CascadeOptions;
typedef uint8_t TilingPlacingMode;
typedef uint8_t TilingReplacingMode;
typedef uint8_t Command;
typedef uint16_t AttributesMasks;
typedef uint32_t InputMasks;

typedef struct{
	uint16_t keycode;
	uint16_t masks;
	Command command;
} Shortcut;

typedef struct{
	uint8_t button;
	uint16_t masks;
	Command command;
} Button;

typedef struct{
	unsigned int x;
	unsigned int y;
} BorderAxis;

typedef struct{
	unsigned int up;
	unsigned int down;
	unsigned int left;
	unsigned int right;
	BorderAxis axis;
} Border;

typedef struct{
	ARGB floating;
	ARGB gridding;
	ARGB tiling;
	ARGB inGrid;
	ARGB fullscreen;
	ARGB bigscreen;
} ContainerBackground;

typedef struct{
	ARGB containerShadow;
	ARGB gridSubwindowBorder;
	ARGB gridSubwindowBackground;
	ARGB separatorBorder;
	ARGB separatorBackground;
	ContainerBackground containerBackground;
} Color;

typedef struct{
	uint8_t mode;
	CascadeOptions options;
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
	Command direction[8];
} MotionContainer;

inline static void _grabRootKeysButtons(const Shortcut *const shortcut, const unsigned int shortcutAmount, const Button *const button, const unsigned int buttonAmount);
inline static void _grabContainerKeysButtons(const Window w, const Shortcut *const shortcut, const unsigned int shortcutAmount, const Button *const button, const unsigned int buttonAmount);
static unsigned int _getUnsignedInteger(FILE *const file, const char endCharacter);
static int _getInteger(FILE *const file, const char endCharacter);
static bool _containerIsMaximized(const Window w, const MaximizedContainer *const maximizedContainer, const unsigned int monitorAmount);
static bool _findContainer(const Window w, const Container *const c, const unsigned int allocatedContainerAmount, unsigned int *const currentContainer);
static XRRMonitorInfo _getPointerMonitorInfo(const XRRMonitorInfo *const monitors, const unsigned int monitorAmount);
static XRRMonitorInfo _getWindowMonitorInfo(const Window w, const XRRMonitorInfo *const monitors, const unsigned int monitorAmount);
static void getGridSlotData(const XRRMonitorInfo monitorInfo, const unsigned int gridX, const unsigned int gridY, const unsigned int gridWidth, const unsigned int gridHeight, int *const x, int *const y, unsigned int *const width, unsigned int *const height);
static void _createGrid(const XRRMonitorInfo *const monitors, const unsigned int monitorAmount, const unsigned int gridWidth, const unsigned int gridHeight, const ARGB gridSubwindowBorderColor, const ARGB gridSubwindowBackgroundColor, const Window *const grid);
static void _unmaximizeContainer(const Window w, const unsigned int monitorAmount, const unsigned int shadow, const ARGB floatingContainerBackgroundColor, const BorderAxis border, MaximizedContainer *const maximizedContainer, Window *const commandedWindow);
static void _maximizeContainer(const Window w, const Window s, const bool inGrid, const XRRMonitorInfo monitorInfo, const Command command, const ContainerBackground containerBackground, const BorderAxis border, const ManagementMode managementMode, MaximizedContainer *const maximizedContainer, Window *const commandedWindow);
static void _moveContainerToGridPosition(const Container container, const XRRMonitorInfo monitorInfo, const unsigned int gridWidth, const unsigned int gridHeight, const BorderAxis border);
static void _moveContainerToMonitor(const Window w, const Window s, const XRRMonitorInfo source, const XRRMonitorInfo destination, const unsigned int shadow, const BorderAxis border);
inline static void clearWindowProperties(const Window w);
inline static void copyWindowProperties(const Window source, const Window destination);
inline static void _ungrabRootKeysButtons(const Shortcut *const shortcut, const unsigned int shortcutAmount, const Button *const button, const unsigned int buttonAmount);









typedef struct{
	unsigned int extendWidth;
	unsigned int extendHeight;
	unsigned int shrinkWidth;
	unsigned int shrinkHeight;
	int stickyThresholdX;
	int stickyThresholdY;
	int distanceToTravelX;
	int distanceToTravelY;
	int floatingDirectionThresholdCorner;
	int floatingDirectionThresholdDominant;
	int floatingDirectionThresholdSubmissive;
} Floating;

typedef struct{
	unsigned int gapsX;
	unsigned int gapsY;
	unsigned int extendWidth;
	unsigned int extendHeight;
	unsigned int shrinkWidth;
	unsigned int shrinkHeight;
	unsigned int minimumWidth;
	unsigned int minimumHeight;
	unsigned int newWindowDivisor;
} Tiling;









void eventLoop(void){
	const Window rootWindow = XDefaultRootWindow(display);
	ManagementMode managementMode = FloatingManagementMode;
	Options option = FloatingMinimalMoveOption | FloatingMinimalResizeOption | FloatingAllowStickingOption | FloatingAllowDirectionStickingOption | FloatingUseDirectionOutlineOption | FloatingPortWindowsFromGriddingOption | GriddingPortWindowsFromFloatingOption | TilingUseSeparatorsOption | TilingUseGapsOption | TilingMinimalResizeOption;
	PointerInfo pointerInfo = ChangeToFloatingPointerInfo | ChangeToGriddingPointerInfo | MovePointerInfo | MapPointerInfo;
	DefaultGridPosition defaultGridPosition = TopLeftDefaultGridPosition;

	Cascade cascade = {
		.mode = SmartCascadeMode,
		.options = OverrideGridWindowsCascadeOption | OverrideMaximizedWindowsCascadeOption,
		.offsetX = 20,
		.offsetY = 20
	};

	MotionContainer motionContainer = {
		.action = NoMotionAction,
		.subaction = NoMotionSubaction,
		.options = NoMotionOptions,
		.direction[0] = MoveFullCommand,
		.direction[1] = MoveCenterCommand,
		.direction[2] = MoveLeftCommand,
		.direction[3] = MoveRightCommand,
		.direction[4] = MoveTopLeftCommand,
		.direction[5] = MoveTopRightCommand,
		.direction[6] = MoveBottomLeftCommand,
		.direction[7] = MoveBottomRightCommand
	};

	char *subwindowsPath = "/home/steven/.microwm/.subwindows";
	char *maximizedWindowsPath = "/home/steven/.microwm/.maximizedWindows";



	XVisualInfo visualInfo;
	XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo);



	// bool tilingPrioritizeY = 1;



	unsigned int floatingExtendWidth = 10;
	unsigned int floatingExtendHeight = 10;
	unsigned int floatingShrinkWidth = 10;
	unsigned int floatingShrinkHeight = 10;
	int floatingStickyThresholdX = 10;
	int floatingStickyThresholdY = 10;
	int floatingDistanceToTravelX = 50;
	int floatingDistanceToTravelY = 50;
	int floatingDirectionThreshold = 50;
	unsigned int tilingGapsX = 10;
	unsigned int tilingGapsY = 10;
	unsigned int tilingExtendWidth = 10;
	unsigned int tilingExtendHeight = 10;
	// unsigned int tilingShrinkWidth = 10;
	// unsigned int tilingShrinkHeight = 10;
	unsigned int tilingMinimumWidth = 20;
	unsigned int tilingMinimumHeight = 20;
	unsigned int tilingNewWindowDivisor = 3;
	if(!tilingMinimumWidth){
		tilingMinimumWidth = 1;
	}
	if(!tilingMinimumHeight){
		tilingMinimumHeight = 1;
	}
	if(tilingNewWindowDivisor < 2){
		tilingNewWindowDivisor = 2;
	}



	FILE *errorStream = stderr;



	TilingPlacingMode tilingPlacingMode = HorizontalEqualTilingPlacingMode;
	TilingReplacingMode tilingReplacingMode = HorizontalEqualTilingReplacingMode;



	unsigned int gapsX;
	unsigned int gapsY;
	if(option & TilingUseGapsOption){
		gapsX = tilingGapsX;
		gapsY = tilingGapsY;
	}else{
		gapsX = 0;
		gapsY = 0;
	}

	unsigned int currentMonitor;

	unsigned int containerIncrementDecrementAmount = 5;
	int containerChangeAmount = 0;
	unsigned int defaultContainerAmount = 5;
	unsigned int containerAmount = defaultContainerAmount;
	unsigned int allocatedContainerAmount = 0;



	unsigned int shadow = 10;
	Border border = {
		.up = 1,
		.down = 1,
		.left = 1,
		.right = 1,
		.axis = {
			.x = border.left + border.right,
			.y = border.up + border.down
		}
	};
	if(tilingMinimumWidth < border.axis.x + 1){
		tilingMinimumWidth = border.axis.x + 1;
	}
	if(tilingMinimumHeight < border.axis.y + 1){
		tilingMinimumHeight = border.axis.y + 1;
	}



	Color color = {
		.containerShadow = 0x7F000000,
		.gridSubwindowBorder = 0x10975C57,
		.gridSubwindowBackground = 0x00000000,
		.separatorBorder = 0xFFFFFFFF,
		.separatorBackground = 0xFF000000,
		.containerBackground = {
			.floating = 0xFF00FF00,
			.gridding = 0xFFFF0000,
			.tiling = 0xFF0000FF,
			.inGrid = 0xFFFF7F00,
			.fullscreen = 0xFFFFFFFF,
			.bigscreen = 0xFFFF007F
		}
	};

	unsigned int gridWidth = 2;
	unsigned int gridHeight = 2;

	unsigned int separatorWidth = 12;
	unsigned int separatorBorder = 1;
	const unsigned int separatorBorders = 2 * separatorBorder;

	unsigned int currentContainer;



	unsigned int monitorAmount;
	{
		XRRMonitorInfo *const monitorInfo = XRRGetMonitors(display, rootWindow, True, (int *)&monitorAmount);
		if(monitorInfo){
			XRRFreeMonitors(monitorInfo);
		}else{
			monitorAmount = 1;
		}
	}
	XRRMonitorInfo monitors[monitorAmount];
	MaximizedContainer maximizedContainer[monitorAmount];
	Window grid[monitorAmount];
	unsigned int maxGridWidth = 20;
	unsigned int maxGridHeight = 20;
	{
		unsigned int ma;
		XRRMonitorInfo *const monitorInfo = XRRGetMonitors(display, rootWindow, True, (int *)&ma);
		if(monitorInfo){
			const AttributesMasks masks = CWBackPixel | CWBorderPixel | CWOverrideRedirect | CWColormap;
			XSetWindowAttributes windowAttributes = {
				.background_pixel = 0x00000000,
				.border_pixel = 0x00000000,
				.override_redirect = True,
				.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone)
			};
			unsigned int width;
			unsigned int height;
			for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
				monitors[currentMonitor] = monitorInfo[currentMonitor];
				maximizedContainer[currentMonitor].window = None;
				maximizedContainer[currentMonitor].subwindow = None;
				grid[currentMonitor] = XCreateWindow(display, rootWindow, monitors[currentMonitor].x, monitors[currentMonitor].y, monitors[currentMonitor].width, monitors[currentMonitor].height, 0, visualInfo.depth, InputOutput, visualInfo.visual, masks, &windowAttributes);
				width = monitors[currentMonitor].width / 3;
				height = monitors[currentMonitor].height / 3;
				if(maxGridWidth > width){
					maxGridWidth = width;
				}
				if(maxGridHeight > height){
					maxGridHeight = height;
				}
			}
			XRRFreeMonitors(monitorInfo);
		}
	}



	Window moveResizeWindow;
	unsigned int moveResizeWindowBorder = 1;
	if(option & FloatingMinimalMoveOption || option & FloatingMinimalResizeOption){
		ARGB backgroundColor = 0x7FF07746;
		ARGB borderColor = 0xFFF2C6B4;
		XSetWindowAttributes windowAttributes = {
			.background_pixel = backgroundColor,
			.border_pixel = borderColor,
			.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone)
		};
		moveResizeWindow = XCreateWindow(display, rootWindow, 0, 0, 1, 1, moveResizeWindowBorder, visualInfo.depth, InputOutput, visualInfo.visual, CWBackPixel | CWBorderPixel | CWColormap, &windowAttributes);
	}



	Window directionOutlineWindow;
	unsigned int directionOutlineWindowBorder = 1;
	bool directionOutlineWindowMapped = 0;
	unsigned int directionOutlineWindowEqualOffsetX = 10;
	unsigned int directionOutlineWindowEqualOffsetY = 10;
	if(option & FloatingUseDirectionOutlineOption){
		ARGB backgroundColor = 0x00000000;
		ARGB borderColor = 0xFFFFFFFF;
		XSetWindowAttributes windowAttributes = {
			.background_pixel = backgroundColor,
			.border_pixel = borderColor,
			.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone)
		};
		directionOutlineWindow = XCreateWindow(display, rootWindow, 0, 0, 1, 1, directionOutlineWindowBorder, visualInfo.depth, InputOutput, visualInfo.visual, CWBackPixel | CWBorderPixel | CWColormap, &windowAttributes);
	}else{
		directionOutlineWindow = None;
	}



	bool canConfigurePosition = 1;
	Window commandedWindow = None;



	XWindowAttributes windowAttributes;
	XRRMonitorInfo monitorInfo;

	bool gridExists = 0;
	bool gridMapped = 0;

	Command command;

	SET_KEYS_BUTTONS
	grabRootKeysButtons();
	{
		XEvent event;
		int rrEventBase;
		{
			int rrErrorBase;
			if(!XRRQueryExtension(display, &rrEventBase, &rrErrorBase)){
				fprintf(errorStream, "%s: could not query the xrandr extension\n", programName);
				rrEventBase = 0;
				XRRSelectInput(display, rootWindow, RRScreenChangeNotifyMask);
			}
		}
		XSync(display, False);
		do{
			SETUP_CONTAINERS
			for(;;){
				XNextEvent(display, &event);
				printEvent(event);
				if(event.type == KeyPress){
					KEYPRESS
				}else if(event.type == KeyRelease){
					KEYRELEASE
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
					if(pointerInfo & MapPointerInfo){
						monitorInfo = getPointerMonitorInfo();
					}else{
						monitorInfo = getWindowMonitorInfo(event.xmaprequest.window);
					}
					mapWindow:{
						copyWindowProperties(event.xmaprequest.window, container[allocatedContainerAmount].window);
						XReparentWindow(display, event.xmaprequest.window, container[allocatedContainerAmount].window, border.left, border.up);
						{
							unsigned int width;
							unsigned int height;
							if(managementMode == FloatingManagementMode){
								XSetWindowBorderWidth(display, container[allocatedContainerAmount].window, shadow);
								XSetWindowBackground(display, container[allocatedContainerAmount].window, color.containerBackground.floating);
								if(option & FloatingFollowGrid){
									width = monitorInfo.width / gridWidth;
									height = monitorInfo.height / gridHeight;
								}else{
									width = monitorInfo.width / 2;
									height = monitorInfo.height / 2;
								}
								{
									Window lastCreatedWindow;
									if(allocatedContainerAmount){
										lastCreatedWindow = container[allocatedContainerAmount - 1].window;
									}else{
										lastCreatedWindow = None;
									}
									if(cascade.mode == SimpleCascadeMode){
										if(lastCreatedWindow){
											const XRRMonitorInfo monitorInfo1 = getWindowMonitorInfo(lastCreatedWindow);
											if(monitorCompare(monitorInfo1, monitorInfo)){
												for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
													if(container[currentContainer].window == lastCreatedWindow){
														break;
													}
												}
												if(currentContainer < allocatedContainerAmount && !(container[currentContainer].inGrid || containerIsMaximized(container[currentContainer].window))){
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
								}
								XMoveResizeWindow(display, event.xmaprequest.window, border.left, border.up, width - border.axis.x, height - border.axis.y);
								XSelectInput(display, container[allocatedContainerAmount].window, ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask);
								XSelectInput(display, event.xmaprequest.window, ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask);
								container[allocatedContainerAmount].inGrid = 0;
							}else{
								XSetWindowBorderWidth(display, container[allocatedContainerAmount].window, 0);
								if(managementMode == GriddingManagementMode){
									XSetWindowBackground(display, container[allocatedContainerAmount].window, color.containerBackground.gridding);
									int x;
									int y;
									if(defaultGridPosition == TopLeftDefaultGridPosition){
										container[allocatedContainerAmount].gridX = 0;
										container[allocatedContainerAmount].gridY = 0;
									}else if(defaultGridPosition == TopRightDefaultGridPosition){
										container[allocatedContainerAmount].gridX = gridWidth - 1;
										container[allocatedContainerAmount].gridY = 0;
									}else if(defaultGridPosition == BottomLeftDefaultGridPosition){
										container[allocatedContainerAmount].gridX = 0;
										container[allocatedContainerAmount].gridY = gridHeight - 1;
									}else if(defaultGridPosition == BottomRightDefaultGridPosition){
										container[allocatedContainerAmount].gridX = gridWidth - 1;
										container[allocatedContainerAmount].gridY = gridHeight - 1;
									}else{
										container[allocatedContainerAmount].gridX = gridWidth / 2;
										container[allocatedContainerAmount].gridY = gridHeight / 2;
									}
									getGridSlotData(monitorInfo, container[allocatedContainerAmount].gridX, container[allocatedContainerAmount].gridY, gridWidth, gridHeight, &x, &y, &width, &height);
									XMoveResizeWindow(display, container[allocatedContainerAmount].window, monitorInfo.x + x, monitorInfo.y + y, width, height);
									XMoveResizeWindow(display, event.xmaprequest.window, border.left, border.up, width - border.axis.x, height - border.axis.y);
									container[allocatedContainerAmount].inGrid = 1;
									container[allocatedContainerAmount].gridWidth = 1;
									container[allocatedContainerAmount].gridHeight = 1;
								}else{
									XSetWindowBackground(display, container[allocatedContainerAmount].window, color.containerBackground.tiling);
									if(allocatedContainerAmount){
										bool containerInMonitorMap[allocatedContainerAmount];
										unsigned int monitorContainerAmount = 0;
										{
											XRRMonitorInfo mi;
											currentContainer = 0;
											do{
												mi = getWindowMonitorInfo(container[currentContainer].window);
												if(monitorCompare(mi, monitorInfo)){
													containerInMonitorMap[currentContainer] = 1;
													++monitorContainerAmount;
												}else{
													containerInMonitorMap[currentContainer] = 0;
												}
											}while(++currentContainer < allocatedContainerAmount);
										}
										if(monitorContainerAmount){
											const Options useSeparatorsOption = option & TilingUseSeparatorsOption;
											if(tilingPlacingMode <= VerticalEqualTilingPlacingMode){









												unsigned int counter = 0;
												int x = monitorInfo.x + gapsX;
												int y = monitorInfo.y + gapsY;
												unsigned int width;
												unsigned int height;
												int *position;
												unsigned int *size;
												unsigned int gaps;
												unsigned int totalSeparatorWidth = separatorBorders + separatorWidth;
												unsigned int abnormal;
												unsigned int normal;
												unsigned int currentContainerList[monitorContainerAmount];
												int *attribute;
												{
													unsigned int monitorSize;
													unsigned int availableSpace;
													if(tilingReplacingMode == HorizontalEqualTilingReplacingMode){
														height = monitorInfo.height - 2 * gapsY;
														position = &x;
														size = &width;
														gaps = gapsX;
														monitorSize = monitorInfo.width;
														attribute = &windowAttributes.x;
													}else{
														width = monitorInfo.width - 2 * gapsX;
														position = &y;
														size = &height;
														gaps = gapsY;
														monitorSize = monitorInfo.height;
														attribute = &windowAttributes.y;
													}
													if(useSeparatorsOption){
														availableSpace = monitorSize - (2 * (monitorContainerAmount + 1) * gaps + monitorContainerAmount * totalSeparatorWidth);
													}else{
														availableSpace = monitorSize - (monitorContainerAmount + 2) * gaps;
													}
													normal = availableSpace / (monitorContainerAmount + 1);
													abnormal = availableSpace - monitorContainerAmount * normal;
												}
												*size = normal;
												totalSeparatorWidth += gaps;
												{
													int attributeList[monitorContainerAmount];
													currentContainer = 0;
													for(;;){
														if(containerInMonitorMap[currentContainer]){
															XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes);
															currentContainerList[counter] = currentContainer;
															attributeList[counter] = *attribute;
															if(++counter == monitorContainerAmount){
																break;
															}
														}
														++currentContainer;
													}
													const unsigned int monitorContainerAmount1 = monitorContainerAmount + 1;
													unsigned int ccl;
													int al;
													for(currentContainer = 1; currentContainer < monitorContainerAmount; ++currentContainer){
														for(counter = 1; counter < monitorContainerAmount1 - currentContainer; ++counter){
															if(attributeList[counter - 1] > attributeList[counter]){
																ccl = currentContainerList[counter];
																currentContainerList[counter] = currentContainerList[counter - 1];
																currentContainerList[counter - 1] = ccl;
																al = attributeList[counter];
																attributeList[counter] = attributeList[counter - 1];
																attributeList[counter - 1] = al;
															}
														}
													}
												}
												{
													const unsigned int middle = (monitorContainerAmount + 1) / 2;
													for(counter = 0; counter < monitorContainerAmount; ++counter){
														currentContainer = currentContainerList[counter];
														XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height);
														XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y);
														*position += *size + gaps;
														if(useSeparatorsOption){
															*position += totalSeparatorWidth;
														}
														if(counter == middle){
															*size = abnormal;
														}else{
															*size = normal;
														}
													}
												}
												XMoveResizeWindow(display, container[allocatedContainerAmount].window, x, y, width, height);
												XResizeWindow(display, event.xmaprequest.window, width - border.axis.x, height - border.axis.y);
											}else{



												//



											}
										}else{
											goto placeFirstTilingWindow;
										}
									}else{
										placeFirstTilingWindow:{
											monitorInfo.width -= 2 * gapsX;
											monitorInfo.height -= 2 * gapsY;
											XMoveResizeWindow(display, container[allocatedContainerAmount].window, monitorInfo.x + gapsX, monitorInfo.y + gapsY, monitorInfo.width, monitorInfo.height);
											XResizeWindow(display, event.xmaprequest.window, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y);
										}
									}
								}
								XSelectInput(display, container[allocatedContainerAmount].window, EnterWindowMask | SubstructureRedirectMask);
								XSelectInput(display, event.xmaprequest.window, StructureNotifyMask);
							}
						}
						XMapRaised(display, container[allocatedContainerAmount].window);
						XMapWindow(display, event.xmaprequest.window);
						XSetInputFocus(display, event.xmaprequest.window, RevertToPointerRoot, CurrentTime);
						container[allocatedContainerAmount].subwindow = event.xmaprequest.window;
						if(++allocatedContainerAmount == containerAmount){
							containerChangeAmount = containerIncrementDecrementAmount;
							saveOpenClients:{
								FILE *file;
								if((file = fopen(subwindowsPath, "w"))){
									for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
										XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes);
										fprintf(file, "%lu %i %i %u %u %u %u %u %u %u\n", container[currentContainer].subwindow, windowAttributes.x, windowAttributes.y, windowAttributes.width, windowAttributes.height, container[currentContainer].inGrid, container[currentContainer].gridX, container[currentContainer].gridY, container[currentContainer].gridWidth, container[currentContainer].gridHeight);
									}
									fclose(file);
								}
								break;
							}
						}
					}
				}else if(event.type == ConfigureNotify){
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
					for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
						fprintf(file, "%lu %i %i %u %u %u %u\n", maximizedContainer[currentMonitor].subwindow, maximizedContainer[currentMonitor].oldX, maximizedContainer[currentMonitor].oldY, maximizedContainer[currentMonitor].oldWidth, maximizedContainer[currentMonitor].oldHeight, maximizedContainer[currentMonitor].oldBackgroundColor, maximizedContainer[currentMonitor].shouldChangeProperty);
					}
					fclose(file);
				}
			}
			{
				Window w;
				Window s;
				XSelectInput(display, rootWindow, NoEventMask);
				for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){
					w = container[currentContainer].window;
					s = container[currentContainer].subwindow;
					XSelectInput(display, s, NoEventMask);
					XSelectInput(display, w, NoEventMask);
					XUnmapWindow(display, s);
					XUnmapWindow(display, w);
					XReparentWindow(display, s, rootWindow, 0, 0);
					XDestroyWindow(display, w);
				}
			}
			containerAmount += containerChangeAmount;
			containerChangeAmount = 0;
		}while(mode == ContinueMode);
	}
	ungrabRootKeysButtons();
	return;
}
inline static void _grabRootKeysButtons(const Shortcut *const shortcut, const unsigned int shortcutAmount, const Button *const button, const unsigned int buttonAmount){
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
inline static void _grabContainerKeysButtons(const Window w, const Shortcut *const shortcut, const unsigned int shortcutAmount, const Button *const button, const unsigned int buttonAmount){
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
static unsigned int _getUnsignedInteger(FILE *const file, const char endCharacter){
	unsigned int number = 0;
	char c;
	while((c = fgetc(file)) != endCharacter){
		number = number * 10 + c - 48;
	}
	return number;
}
static int _getInteger(FILE *const file, const char endCharacter){
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
static bool _containerIsMaximized(const Window w, const MaximizedContainer *const maximizedContainer, const unsigned int monitorAmount){
	bool value = 0;
	for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
		if(maximizedContainer[currentMonitor].window == w){
			value = 1;
			break;
		}
	}
	return value;
}
static bool _findContainer(const Window w, const Container *const c, const unsigned int allocatedContainerAmount, unsigned int *const currentContainer){
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
static XRRMonitorInfo _getPointerMonitorInfo(const XRRMonitorInfo *const monitors, const unsigned int monitorAmount){
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
			if(closedOpenInterval(x, monitors[current].x, monitors[current].x + monitors[current].width) && closedOpenInterval(y, monitors[current].y, monitors[current].y + monitors[current].height)){
				break;
			}
			if(++current == monitorAmount){
				current = 0;
				break;
			}
		}
	}
	return monitors[current];
}
static XRRMonitorInfo _getWindowMonitorInfo(const Window w, const XRRMonitorInfo *const monitors, const unsigned int monitorAmount){
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
			}else if(closedOpenInterval(windowAttributes.x + windowAttributes.width, monitors[current].x, monitors[current].x + monitors[current].width)){
				pixels = windowAttributes.x + windowAttributes.width;
			}else{
				pixels = monitors[current].x + monitors[current].width;
			}
			if(monitors[current].x > windowAttributes.x){
				pixels -= monitors[current].x;
			}else if(closedOpenInterval(windowAttributes.x, monitors[current].x, monitors[current].x + monitors[current].width)){
				pixels -= windowAttributes.x;
			}else{
				continue;
			}
			if(monitors[current].y > windowAttributes.y + windowAttributes.height){
				continue;
			}else if(closedOpenInterval(windowAttributes.y + windowAttributes.height, monitors[current].y, monitors[current].y + monitors[current].height)){
				height = windowAttributes.y + windowAttributes.height;
			}else{
				height = monitors[current].y + monitors[current].height;
			}
			if(monitors[current].y > windowAttributes.y){
				height -= monitors[current].y;
			}else if(closedOpenInterval(windowAttributes.y, monitors[current].y, monitors[current].y + monitors[current].height)){
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
static void _createGrid(const XRRMonitorInfo *const monitors, const unsigned int monitorAmount, const unsigned int gridWidth, const unsigned int gridHeight, const ARGB gridSubwindowBorderColor, const ARGB gridSubwindowBackgroundColor, const Window *const grid){
	const unsigned int middleX = gridWidth / 2;
	const unsigned int middleY = gridHeight / 2;
	const unsigned int gridBorder = 1;
	const unsigned int gridBorders = 2 * gridBorder;
	unsigned int currentMonitor;
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
				if(x == middleX){
					offsetX = width - abnormalWidth;
					if(offsetX < 0){
						offsetX = -offsetX;
					}
					finalX -= offsetX;
					finalWidth = abnormalWidth;
				}else{
					finalWidth = width;
				}
				if(y == middleY){
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
	return;
}
static void _unmaximizeContainer(const Window w, const unsigned int monitorAmount, const unsigned int shadow, const ARGB floatingContainerBackgroundColor, const BorderAxis border, MaximizedContainer *const maximizedContainer, Window *const commandedWindow){
	for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
		if(maximizedContainer[currentMonitor].window == w){
			if(maximizedContainer[currentMonitor].shouldChangeProperty){
				const Atom atom = None;
				XChangeProperty(display, maximizedContainer[currentMonitor].subwindow, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1);
			}
			if(maximizedContainer[currentMonitor].oldBackgroundColor == floatingContainerBackgroundColor){
				XSetWindowBorderWidth(display, w, shadow);
			}
			XSetWindowBackground(display, w, maximizedContainer[currentMonitor].oldBackgroundColor);
			XUnmapWindow(display, w);
			XMapWindow(display, w);
			XMoveResizeWindow(display, w, maximizedContainer[currentMonitor].oldX, maximizedContainer[currentMonitor].oldY, maximizedContainer[currentMonitor].oldWidth, maximizedContainer[currentMonitor].oldHeight);
			XResizeWindow(display, maximizedContainer[currentMonitor].subwindow, maximizedContainer[currentMonitor].oldWidth - border.x, maximizedContainer[currentMonitor].oldHeight - border.y);
			maximizedContainer[currentMonitor].window = None;
			*commandedWindow = maximizedContainer[currentMonitor].subwindow;
			maximizedContainer[currentMonitor].subwindow = None;
			break;
		}
	}
	return;
}
static void _maximizeContainer(const Window w, const Window s, const bool inGrid, const XRRMonitorInfo monitorInfo, const Command command, const ContainerBackground containerBackground, const BorderAxis border, const ManagementMode managementMode, MaximizedContainer *const maximizedContainer, Window *const commandedWindow){
	if(!inGrid){
		XSetWindowBorderWidth(display, w, 0);
	}
	if(command == FullscreenCommand){
		{
			const Atom atom = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);
			XChangeProperty(display, s, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1);
		}
		(*maximizedContainer).shouldChangeProperty = 1;
		XSetWindowBackground(display, w, containerBackground.fullscreen);
	}else{
		(*maximizedContainer).shouldChangeProperty = 0;
		XSetWindowBackground(display, w, containerBackground.bigscreen);
	}
	XUnmapWindow(display, w);
	XMapRaised(display, w);
	XWindowAttributes windowAttributes;
	XGetWindowAttributes(display, w, &windowAttributes);
	XMoveResizeWindow(display, w, monitorInfo.x, monitorInfo.y, monitorInfo.width, monitorInfo.height);
	XResizeWindow(display, s, monitorInfo.width - border.x, monitorInfo.height - border.y);
	(*maximizedContainer).window = w;
	(*maximizedContainer).subwindow = s;
	(*maximizedContainer).oldX = windowAttributes.x;
	(*maximizedContainer).oldY = windowAttributes.y;
	(*maximizedContainer).oldWidth = windowAttributes.width;
	(*maximizedContainer).oldHeight = windowAttributes.height;
	if(managementMode == TilingManagementMode){
		(*maximizedContainer).oldBackgroundColor = containerBackground.tiling;
	}else if(managementMode == GriddingManagementMode){
		(*maximizedContainer).oldBackgroundColor = containerBackground.gridding;
	}else if(inGrid){
		(*maximizedContainer).oldBackgroundColor = containerBackground.inGrid;
	}else{
		(*maximizedContainer).oldBackgroundColor = containerBackground.floating;
	}
	*commandedWindow = s;
	return;
}
static void _moveContainerToGridPosition(const Container container, const XRRMonitorInfo monitorInfo, const unsigned int gridWidth, const unsigned int gridHeight, const BorderAxis border){
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
	XResizeWindow(display, container.subwindow, width - border.x, height - border.y);
	return;
}
static void _moveContainerToMonitor(const Window w, const Window s, const XRRMonitorInfo source, const XRRMonitorInfo destination, const unsigned int shadow, const BorderAxis border){
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	{
		XWindowAttributes windowAttributes;
		XGetWindowAttributes(display, w, &windowAttributes);
		unsigned int sourcePercent = source.width / 100;
		unsigned int destinationPercent = destination.width / 100;
		windowAttributes.x -= shadow;
		windowAttributes.y -= shadow;
		if(windowAttributes.x < source.x){
			x = destination.x + (source.x - windowAttributes.x) * destinationPercent / sourcePercent;
		}else{
			x = destination.x + (windowAttributes.x - source.x) * destinationPercent / sourcePercent;
		}
		width = windowAttributes.width * destinationPercent / sourcePercent;
		sourcePercent = source.height / 100;
		destinationPercent = destination.height / 100;
		if(windowAttributes.y < source.y){
			y = destination.y + (source.y - windowAttributes.y) * destinationPercent / sourcePercent;
		}else{
			y = destination.y + (windowAttributes.y - source.y) * destinationPercent / sourcePercent;
		}
		height = windowAttributes.height * destinationPercent / sourcePercent;
		if(!width){
			width = border.x + 1;
		}
		if(!height){
			height = border.y + 1;
		}
	}
	XMoveResizeWindow(display, w, x + shadow, y + shadow, width, height);
	XResizeWindow(display, s, width - border.x, height - border.y);
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
inline static void _ungrabRootKeysButtons(const Shortcut *const shortcut, const unsigned int shortcutAmount, const Button *const button, const unsigned int buttonAmount){
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
