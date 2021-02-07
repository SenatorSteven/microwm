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
#include "headers/printEvent.h"

#define ONE64 /*-------------------------------------*/ ((uint64_t)1)

#define NoCommand /*---------------------------------*/ 0
#define ExecuteCommand /*----------------------------*/ 1
#define FloatingModeCommand /*-----------------------*/ 2
#define GriddingModeCommand /*-----------------------*/ 3
#define TilingModeCommand /*-------------------------*/ 4
#define ShowGridCommand /*---------------------------*/ 5
#define HideGridCommand /*---------------------------*/ 6
#define ToggleGridVisibilityCommand /*---------------*/ 7
#define EnlargeGridXCommand /*-----------------------*/ 8
#define EnlargeGridYCommand /*-----------------------*/ 9
#define EnlargeGridEitherCommand /*------------------*/ 10
#define EnlargeGridBothCommand /*--------------------*/ 11
#define ShrinkGridXCommand /*------------------------*/ 12
#define ShrinkGridYCommand /*------------------------*/ 13
#define ShrinkGridEitherCommand /*-------------------*/ 14
#define ShrinkGridBothCommand /*---------------------*/ 15
#define ToggleGapsCommand /*-------------------------*/ 16
#define RecascadeCommand /*--------------------------*/ 17
#define AttachCommand /*-----------------------------*/ 18
#define SwapNextMonitorCommand /*--------------------*/ 19
#define SwapPreviousMonitorCommand /*----------------*/ 20
#define SwapAboveMonitorCommand /*-------------------*/ 21
#define SwapBelowMonitorCommand /*-------------------*/ 22
#define SwapLeftMonitorCommand /*--------------------*/ 23
#define SwapRightMonitorCommand /*-------------------*/ 24
#define RevolveMonitorsNextCommand /*----------------*/ 25
#define RevolveMonitorsPreviousCommand /*------------*/ 26
#define RevolveMonitorsHorizontallyCommand /*--------*/ 27
#define RevolveMonitorsVerticallyCommand /*----------*/ 28
#define RestartCommand /*----------------------------*/ 29
#define ExitCommand /*-------------------------------*/ 30
#define MoveCommand /*-------------------------------*/ 31
#define ResizeCommand /*-----------------------------*/ 32
#define MoveResizeCommand /*-------------------------*/ 33
#define CancelMoveResizeCommand /*-------------------*/ 34
#define MoveTopCommand /*----------------------------*/ 35
#define MoveBottomCommand /*-------------------------*/ 36
#define MoveLeftCommand /*---------------------------*/ 37
#define MoveRightCommand /*--------------------------*/ 38
#define MoveTopLeftCommand /*------------------------*/ 39
#define MoveTopRightCommand /*-----------------------*/ 40
#define MoveBottomLeftCommand /*---------------------*/ 41
#define MoveBottomRightCommand /*--------------------*/ 42
#define MoveCenterCommand /*-------------------------*/ 43
#define MoveFullCommand /*---------------------------*/ 44
#define MoveNextMonitorCommand /*--------------------*/ 45
#define MovePreviousMonitorCommand /*----------------*/ 46
#define MoveAboveMonitorCommand /*-------------------*/ 47
#define MoveBelowMonitorCommand /*-------------------*/ 48
#define MoveLeftMonitorCommand /*--------------------*/ 49
#define MoveRightMonitorCommand /*-------------------*/ 50
#define AddToGridCommand /*--------------------------*/ 51
#define RemoveFromGridCommand /*---------------------*/ 52
#define ToggleAddRemoveGridCommand /*----------------*/ 53
#define MoveUpGridCommand /*-------------------------*/ 54
#define MoveDownGridCommand /*-----------------------*/ 55
#define MoveLeftGridCommand /*-----------------------*/ 56
#define MoveRightGridCommand /*----------------------*/ 57
#define ExtendUpCommand /*---------------------------*/ 58
#define ExtendDownCommand /*-------------------------*/ 59
#define ExtendLeftCommand /*-------------------------*/ 60
#define ExtendRightCommand /*------------------------*/ 61
#define ExtendUpLeftCommand /*-----------------------*/ 62
#define ExtendUpRightCommand /*----------------------*/ 63
#define ExtendDownLeftCommand /*---------------------*/ 64
#define ExtendDownRightCommand /*--------------------*/ 65
#define ShrinkUpCommand /*---------------------------*/ 66
#define ShrinkDownCommand /*-------------------------*/ 67
#define ShrinkLeftCommand /*-------------------------*/ 68
#define ShrinkRightCommand /*------------------------*/ 69
#define ShrinkUpLeftCommand /*-----------------------*/ 70
#define ShrinkUpRightCommand /*----------------------*/ 71
#define ShrinkDownLeftCommand /*---------------------*/ 72
#define ShrinkDownRightCommand /*--------------------*/ 73
#define FullscreenCommand /*-------------------------*/ 74
#define BigscreenCommand /*--------------------------*/ 75
#define DetachCommand /*-----------------------------*/ 76
#define CloseCommand /*------------------------------*/ 77
#define KillCommand /*-------------------------------*/ 78

#define RootCommandCeiling /*------------------------*/ ExitCommand

#define FloatingManagementMode /*--------------------*/ 0
#define GriddingManagementMode /*--------------------*/ 1
#define TilingManagementMode /*----------------------*/ 2

#define NoMotionAction /*----------------------------*/ 0
#define MoveMotionAction /*--------------------------*/ 1
#define ResizeMotionAction /*------------------------*/ 2

#define NoMotionOptions /*---------------------------*/ 0
#define HasLockedXMotionOption /*--------------------*/ (1 << 0)
#define HasLockedYMotionOption /*--------------------*/ (1 << 1)
#define SnappingMappedMotionOption /*----------------*/ (1 << 2)

#define NoOptions /*---------------------------------*/ 0
#define FloatingUseFocusedWindowColorOption /*-------*/ (ONE64 << 0)
#define FloatingFollowGridOption /*------------------*/ (ONE64 << 1)
#define FloatingMinimalMoveOption /*-----------------*/ (ONE64 << 2)
#define FloatingMinimalResizeOption /*---------------*/ (ONE64 << 3)
#define FloatingAllowMonitorStickingOption /*--------*/ (ONE64 << 4)
#define FloatingAllowSnappingOption /*---------------*/ (ONE64 << 5)
#define FloatingUseSnappingWindowOption /*-----------*/ (ONE64 << 6)
#define FloatingSnappingWindowFollowGridOption /*----*/ (ONE64 << 7)
#define FloatingPortWindowsFromGriddingOption /*-----*/ (ONE64 << 8)
#define FloatingAllowResizeOpposingOption /*---------*/ (ONE64 << 9) /**/
#define FloatingMinimalResizeOpposingOption /*-------*/ (ONE64 << 10) /**/
#define FloatingAllowCascadeToFloatingOption /*------*/ (ONE64 << 11)
#define InGridUseFocusedWindowColorOption /*---------*/ (ONE64 << 12)
#define InGridFollowGridOption /*--------------------*/ (ONE64 << 13)
#define InGridMinimalMoveOption /*-------------------*/ (ONE64 << 14) /**/
#define InGridMinimalResizeOption /*-----------------*/ (ONE64 << 15) /**/
#define InGridAllowResizeOpposingOption /*-----------*/ (ONE64 << 16) /*--*/
#define GriddingUseFocusedWindowColorOption /*-------*/ (ONE64 << 17)
#define GriddingFollowGridOption /*------------------*/ (ONE64 << 18)
#define GriddingMinimalMoveOption /*-----------------*/ (ONE64 << 19) /**/
#define GriddingMinimalResizeOption /*---------------*/ (ONE64 << 20) /**/
#define GriddingAllowResizeOpposingOption /*---------*/ (ONE64 << 21) /*--*/
#define GriddingPortWindowsFromFloatingOption /*-----*/ (ONE64 << 22)
#define GriddingEvenlyDistributeWindowsOption /*-----*/ (ONE64 << 23)
#define TilingUseFocusedWindowColorOption /*---------*/ (ONE64 << 24)
#define TilingFollowGridOption /*--------------------*/ (ONE64 << 25)
#define TilingUseSeparatorsOption /*-----------------*/ (ONE64 << 26)
#define TilingUseGapsOption /*-----------------------*/ (ONE64 << 27)
#define TilingMinimalMoveOption /*-------------------*/ (ONE64 << 28) /**/
#define TilingMinimalResizeOption /*-----------------*/ (ONE64 << 29) /**/
#define TilingSlamWindowsOption /*-------------------*/ (ONE64 << 30)
#define MaximizedUseFocusedWindowColorOption /*------*/ (ONE64 << 31)

#define NoPointerInfo /*-----------------------------*/ 0
#define ChangeToFloatingPointerInfo /*---------------*/ (1 << 0)
#define ChangeToGriddingPointerInfo /*---------------*/ (1 << 1)
#define ChangeToTilingPointerInfo /*-----------------*/ (1 << 2)
#define RecascadePointerInfo /*----------------------*/ (1 << 3)
#define AttachPointerInfo /*-------------------------*/ (1 << 4)
#define MovePointerInfo /*---------------------------*/ (1 << 5)
#define MoveToFloatingPointerInfo /*-----------------*/ (1 << 6)
#define NextPreviousMonitorPointerInfo /*------------*/ (1 << 7)
#define MoveToMonitorPointerInfo /*------------------*/ (1 << 8)
#define SwapMonitorsPointerInfo /*-------------------*/ (1 << 9)
#define RevolveMonitorsPointerInfo /*----------------*/ (1 << 10)
#define AddToGridPointerInfo /*----------------------*/ (1 << 11)
#define MoveOnGridPointerInfo /*---------------------*/ (1 << 12)
#define RemoveFromGridPointerInfo /*-----------------*/ (1 << 13)
#define DetachPointerInfo /*-------------------------*/ (1 << 14)
#define MoveToInGridPointerInfo /*-------------------*/ (1 << 15)
#define ExtendInGridPointerInfo /*-------------------*/ (1 << 16)
#define ShrinkInGridPointerInfo /*-------------------*/ (1 << 17)
#define MaximizePointerInfo /*-----------------------*/ (1 << 18)
#define MapPointerInfo /*----------------------------*/ (1 << 19)
#define ClientMessagePointerInfo /*------------------*/ (1 << 20)

#define NoCascadeMode /*-----------------------------*/ 0
#define SimpleCascadeMode /*-------------------------*/ 1
#define SmartCascadeMode /*--------------------------*/ 2

#define NoCascadeOptions /*--------------------------*/ 0
#define OverrideGridWindowsCascadeOption /*----------*/ (1 << 0)
#define OverrideMaximizedWindowsCascadeOption /*-----*/ (1 << 1)

#define NoDefaultGridPosition /*---------------------*/ 0
#define TopLeftDefaultGridPosition /*----------------*/ 1
#define TopRightDefaultGridPosition /*---------------*/ 2
#define BottomLeftDefaultGridPosition /*-------------*/ 3
#define BottomRightDefaultGridPosition /*------------*/ 4
#define CenterDefaultGridPosition /*-----------------*/ 5

#define NoGridOptions /*-----------------------------*/ 0
#define ExistsGridOption /*--------------------------*/ (1 << 0)
#define MappedGridOption /*--------------------------*/ (1 << 1)

#define NoTilingResize /*----------------------------*/ 1
#define ExtendTilingResize /*------------------------*/ 0
#define ShrinkTilingResize /*------------------------*/ 2

#define NoTilingPrioritization /*--------------------*/ 0
#define MoveTopLeftYTilingPrioritization /*----------*/ (1 << 0)
#define MoveTopRightYTilingPrioritization /*---------*/ (1 << 1)
#define MoveBottomLeftYTilingPrioritization /*-------*/ (1 << 2)
#define MoveBottomRightYTilingPrioritization /*------*/ (1 << 3)
#define ExtendUpLeftYTilingPrioritization /*---------*/ (1 << 4)
#define ExtendUpRightYTilingPrioritization /*--------*/ (1 << 5)
#define ExtendDownLeftYTilingPrioritization /*-------*/ (1 << 6)
#define ExtendDownRightYTilingPrioritization /*------*/ (1 << 7)
#define ShrinkUpLeftYTilingPrioritization /*---------*/ (1 << 8)
#define ShrinkUpRightYTilingPrioritization /*--------*/ (1 << 9)
#define ShrinkDownLeftYTilingPrioritization /*-------*/ (1 << 10)
#define ShrinkDownRightYTilingPrioritization /*------*/ (1 << 11)

#define NoContainerOptions /*------------------------*/ 0
#define MappedContainerOption /*---------------------*/ (1 << 0)
#define InGridContainerOption /*---------------------*/ (1 << 1)
#define MaximizedContainerOption /*------------------*/ (1 << 2)

#define NoMotionSubaction /*-------------------------*/ 0
#define UpResizeMotionSubaction /*-------------------*/ 1
#define DownResizeMotionSubaction /*-----------------*/ 2
#define LeftResizeMotionSubaction /*-----------------*/ 3
#define RightResizeMotionSubaction /*----------------*/ 4
#define UpLeftResizeMotionSubaction /*---------------*/ 5
#define UpRightResizeMotionSubaction /*--------------*/ 6
#define DownLeftResizeMotionSubaction /*-------------*/ 7
#define DownRightResizeMotionSubaction /*------------*/ 8
#define TopSnappingMotionSubaction /*----------------*/ 9
#define BottomSnappingMotionSubaction /*-------------*/ 10
#define LeftSnappingMotionSubaction /*---------------*/ 11
#define RightSnappingMotionSubaction /*--------------*/ 12
#define TopLeftSnappingMotionSubaction /*------------*/ 13
#define TopRightSnappingMotionSubaction /*-----------*/ 14
#define BottomLeftSnappingMotionSubaction /*---------*/ 15
#define BottomRightSnappingMotionSubaction /*--------*/ 16
#define CenterSnappingMotionSubaction /*-------------*/ 17

#define SnappingMotionSubactionOffset /*-------------*/ TopSnappingMotionSubaction

#define _NET_WM_STATE_REMOVE /*----------------------*/ 0
#define _NET_WM_STATE_ADD /*-------------------------*/ 1
#define _NET_WM_STATE_TOGGLE /*----------------------*/ 2

#define NextAdjacentMonitor /*-----------------------*/ 0
#define PreviousAdjacentMonitor /*-------------------*/ 1
#define AboveAdjacentMonitor /*----------------------*/ 2
#define BelowAdjacentMonitor /*----------------------*/ 3
#define LeftAdjacentMonitor /*-----------------------*/ 4
#define RightAdjacentMonitor /*----------------------*/ 5

#define NoEnterInputException /*---------------------*/ 0
#define ExecuteEnterInputException /*----------------*/ (1 << 0)
#define ChangeManagementModeEnterInputException /*---*/ (1 << 1)
#define ResizeGridEnterInputException /*-------------*/ (1 << 2)
#define ToggleGapsEnterInputException /*-------------*/ (1 << 3)
#define RecascadeEnterInputException /*--------------*/ (1 << 4)
#define AttachEnterInputException /*-----------------*/ (1 << 5)
#define SwapMonitorsEnterInputException /*-----------*/ (1 << 6)
#define RevolveMonitorsEnterInputException /*--------*/ (1 << 7)
#define CancelMoveResizeEnterInputException /*-------*/ (1 << 8)
#define MoveToEnterInputException /*-----------------*/ (1 << 9)
#define MoveMonitorEnterInputException /*------------*/ (1 << 10)
#define ToggleAddRemoveGridEnterInputException /*----*/ (1 << 11)
#define MoveGridEnterInputException /*---------------*/ (1 << 12)
#define ExtendEnterInputException /*-----------------*/ (1 << 13)
#define ShrinkEnterInputException /*-----------------*/ (1 << 14)
#define MaximizeEnterInputException /*---------------*/ (1 << 15)

#define EnterInputMethod /*--------------------------*/ (1 << 0)
#define KeyPressInputMethod /*-----------------------*/ (1 << 1)
#define ButtonPressInputMethod /*--------------------*/ (1 << 2)

#define UNMAPALLWINDOWS_DEC /*-----------------------*/ static void unmapAllWindows(const Container *current, const Container *const wall)
#define UNMAXIMIZEALLCONTAINERS_DEC /*---------------*/ static void unmaximizeAllContainers(const Atom _NET_WM_STATE, const Atom _NET_WM_STATE_FULLSCREEN, const unsigned int monitorAmount, const Container *const containerWall, Container *container, MaximizedContainer *maximizedContainer)
#define MAPALLWINDOWS_DEC /*-------------------------*/ static void mapAllWindows(const Container *current, const Container *const wall)
#define GETGRIDSLOTDATA_DEC /*-----------------------*/ static void getGridSlotData(const unsigned int monitorWidth, const unsigned int monitorHeight, const unsigned int gridX, const unsigned int gridY, const unsigned int gridWidth, const unsigned int gridHeight, int *const x, int *const y, unsigned int *const width, unsigned int *const height)
#define CREATEGRID_DEC /*----------------------------*/ static void createGrid(const XRRMonitorInfo *monitor, const unsigned int monitorAmount, const unsigned int gridWidth, const unsigned int gridHeight, const ARGB subwindowBorderColor, const ARGB subwindowBackgroundColor, const Window *const grid)
#define UNMAXIMIZECONTAINER_DEC /*-------------------*/ static void unmaximizeContainer(const Container *const focused, const unsigned int monitorAmount, const unsigned int borderX, const unsigned int borderY, const Atom _NET_WM_STATE, const Atom _NET_WM_STATE_FULLSCREEN, Container *const c, MaximizedContainer *maximizedContainer)
#define MOVECONTAINERTOGRIDPOSITION_DEC /*-----------*/ static void moveContainerToGridPosition(const Container *const c, const XRRMonitorInfo *const m, const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int borderX, const unsigned int borderY)
#define GETCURRENTPOINTERMONITOR_DEC /*--------------*/ static unsigned int getCurrentPointerMonitor(const XRRMonitorInfo *monitor, const unsigned int monitorAmount)
#define GETCURRENTWINDOWMONITOR_DEC /*---------------*/ static unsigned int getCurrentWindowMonitor(const Window w, const XRRMonitorInfo *monitor, const unsigned int monitorAmount)
#define FINDWINDOW_DEC /*----------------------------*/ static bool findWindow(const Window w, const Window *location, const uint8_t size, const unsigned int amount, unsigned int *const current)
#define GETADJACENTSURFACESIZE_DEC /*----------------*/ static unsigned int getAdjacentSurfaceSize(const int position00, const int position01, const int size00, const int size01, const int position10, const int position11, const int size10)
#define PRINTERROR_DEC /*----------------------------*/ static void _printError(const char *const string, const bool openErrorStream, const char *const path)
#define FINDMONITOR_DEC /*---------------------------*/ static const XRRMonitorInfo *findMonitor(const AdjacentMonitor adjacentMonitor, const unsigned int displayWidth, const unsigned int displayHeight, const XRRMonitorInfo *const start, const XRRMonitorInfo *const found, const XRRMonitorInfo *const wall)
#define MOVECONTAINERTOMONITOR_DEC /*----------------*/ static void moveContainerToFloatingPosition(const Window w, const Window s, const XRRMonitorInfo *const source, const XRRMonitorInfo *const destination, const Options option, const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int windowDivisor, const unsigned int borderX, const unsigned int borderY, const unsigned int minimumWidth, const unsigned int minimumHeight)
#define MAXIMIZECONTAINER_DEC /*---------------------*/ static void maximizeContainer(const Command command, const XRRMonitorInfo *const monitor, const ManagementMode managementMode, const Colors *const color, const Atom _NET_WM_STATE, const Atom _NET_WM_STATE_FULLSCREEN, const unsigned int borderX, const unsigned int borderY, const Container *const focused, Container *const c, MaximizedContainer *const mc)

#define printError(s) /*-----------------------------*/ _printError(s, openErrorStream, errorStreamPath)

#define closedInterval(point, bound0, bound1) /*-----*/ ((point) >= (bound0) && (point) <= (bound1))
#define closedOpenInterval(point, bound0, bound1) /*-*/ ((point) >= (bound0) && (point) < (bound1))
#define changeProperties(w, s, p, t, f, m, d, e) /*--*/ XChangeProperty(display, w, p, t, f, m, d, e); XChangeProperty(display, s, p, t, f, m, d, e)

#define managementMode(mm) /*------------------------*/ (managementMode == mm##ManagementMode)
#define motionAction(ma) /*--------------------------*/ (motionContainer.action == ma##MotionAction)
#define command(c) /*--------------------------------*/ (command == c##Command)

#define option(o) /*---------------------------------*/ (option & o##Option)
#define pointerInfo(pi) /*---------------------------*/ (pointerInfo & pi##PointerInfo)
#define gridOption(go) /*----------------------------*/ (gridOption & go##GridOption)
#define tilingPrioritize(tp) /*----------------------*/ (tilingPrioritize & tp##TilingPrioritization)
#define motionOption(mo) /*--------------------------*/ (motionContainer.option & mo##MotionOption)
#define cascadeOption(co) /*-------------------------*/ (cascade.option & co##CascadeOption)

extern const char *programName;
extern Mode mode;
extern Display *display;
extern FILE *errorStream;
extern void *containerData;
extern unsigned int containerAmount;

typedef uint8_t Command;
typedef uint16_t AttributesMasks;
typedef uint8_t ManagementMode;
typedef uint32_t InputMasks;
typedef uint64_t Options;
typedef uint32_t PointerInfo;
typedef uint8_t CascadeOptions;
typedef uint8_t DefaultGridPosition;
typedef uint8_t GridOptions;
typedef uint8_t TilingResize;
typedef uint16_t TilingPrioritization;
typedef uint8_t TilingReplacingMode;
typedef uint8_t TilingPlacingMode;
typedef uint32_t ARGB;
typedef uint8_t AdjacentMonitor;
typedef uint16_t EnterInputException;
typedef uint8_t InputMethod;
typedef uint8_t Flags;

typedef struct{
	const ARGB *oldBackgroundColor;
	Window window;
	Window subwindow;
	int oldX;
	int oldY;
	unsigned int oldWidth;
	unsigned int oldHeight;
	unsigned int oldBorder;
	bool shouldChangeProperty;
} MaximizedContainer;

typedef struct{
	Window window;
	Window subwindow;
	unsigned int gridX;
	unsigned int gridY;
	unsigned int gridWidth;
	unsigned int gridHeight;
	uint8_t option;
} Container;

typedef struct{
	ARGB floating;
	ARGB gridding;
	ARGB tiling;
	ARGB inGrid;
	ARGB fullscreen;
	ARGB bigscreen;
} ContainerBackground;

typedef struct{
	ARGB glassBorder;
	ARGB glassBackground;
	ARGB minimalMoveBorder;
	ARGB minimalMoveBackground;
	ARGB minimalResizeBorder;
	ARGB minimalResizeBackground;
	ARGB snappingBackground;
	ARGB snappingBorder;
} MotionContainerColor;

typedef struct{
	ARGB containerShadow;
	ARGB gridSubwindowBorder;
	ARGB gridSubwindowBackground;
	ARGB separatorBorder;
	ARGB separatorBackground;
	ContainerBackground containerBackground;
	ContainerBackground focusedContainerBackground;
	MotionContainerColor motionContainer;
} Colors;

typedef struct{
	unsigned int up;
	unsigned int down;
	unsigned int left;
	unsigned int right;
	unsigned int x;
	unsigned int y;
} DirectionAxis;

typedef struct{
	uint16_t masks;
	uint16_t keycode;
	Command command;
} Shortcut;

typedef struct{
	uint16_t masks;
	uint8_t button;
	Command command;
} Button;

typedef struct{
	Window window;
	Window subwindow;
	Window glass;
	Window minimalWindow;
	Window snappingWindow;
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	int pointerOffsetX;
	int pointerOffsetY;
	int escapeX;
	int escapeY;
	unsigned int previousMonitor;
	unsigned int minimalMoveBorder;
	unsigned int minimalResizeBorder;
	unsigned int snappingBorder;
	unsigned int snappingDivisorX;
	unsigned int snappingDivisorY;
	DirectionAxis snappingOffset;
	Command snap;
	Command snap1;
	Command snap2;
	Command snap3;
	Command snap4;
	Command snap5;
	Command snap6;
	Command snap7;
	Command snap8;
	uint8_t option;
	uint8_t action;
	uint8_t subaction;
} MotionContainer;

typedef struct{
	const char *command;
	uint16_t masks;
	uint16_t keyButton;
} Execute;

typedef struct{
	int offsetX;
	int offsetY;
	CascadeOptions option;
	uint8_t mode;
} Cascade;

typedef struct{
	Atom PROTOCOLS;
	Atom DELETE_WINDOW;
} ICCCMAtoms;

typedef struct{
	struct{
		struct{
			Atom this;
			Atom FULLSCREEN;
		} STATE;
	} WM;
} EWMHAtoms;

typedef struct{
	struct{
		const MaximizedContainer *wall;
		MaximizedContainer *start;
		MaximizedContainer *current;
	} mc;
	struct{
		const Container *wall;
		Container *start;
		Container *current;
	} c;
	struct{
		const XRRMonitorInfo *wall;
		XRRMonitorInfo *start;
		XRRMonitorInfo *current;
	} m;
	struct{
		const Window *wall;
		Window *start;
		Window *current;
	} g;
	struct{
		const Shortcut *wall;
		Shortcut *start;
		Shortcut *current;
	} s;
	struct{
		const Button *wall;
		Button *start;
		Button *current;
	} b;
	struct{
		const Execute *wall;
		Execute *start;
		Execute *current;
	} e;
} DataCursors;

UNMAPALLWINDOWS_DEC;
UNMAXIMIZEALLCONTAINERS_DEC;
MAPALLWINDOWS_DEC;
GETGRIDSLOTDATA_DEC;
CREATEGRID_DEC;
UNMAXIMIZECONTAINER_DEC;
MOVECONTAINERTOGRIDPOSITION_DEC;
GETCURRENTPOINTERMONITOR_DEC;
GETCURRENTWINDOWMONITOR_DEC;
FINDWINDOW_DEC;
GETADJACENTSURFACESIZE_DEC;
PRINTERROR_DEC;
FINDMONITOR_DEC;
MOVECONTAINERTOMONITOR_DEC;
MAXIMIZECONTAINER_DEC;









typedef struct{
	unsigned int minimumWidth;
	unsigned int minimumHeight;
	unsigned int extendWidth;
	unsigned int extendHeight;
	unsigned int shrinkWidth;
	unsigned int shrinkHeight;
	unsigned int baseGapsX;
	unsigned int baseGapsY;
	unsigned int alternativeGapsX;
	unsigned int alternativeGapsY;
	unsigned int gapsX;
	unsigned int gapsY;
	unsigned int windowDivisor;
	TilingPlacingMode placingMode;
	EnterInputException enterInputException;
} TilingData;









#define sameMonitor(m0, m1) /*-----------------------*/ ((m0).name == (m1).name && (m0).mwidth == (m1).mwidth && (m0).mheight == (m1).mheight)



#define REMOVETILINGWINDOW_DEC /*--------------------*/ static void removeTilingWindow(void)



#define NoMonitorValue /*----------------------------*/ 0
#define RootMonitorValue /*--------------------------*/ 1

#define HorizontalEqualTilingPlacingMode /*----------*/ 0
#define VerticalEqualTilingPlacingMode /*------------*/ 1

#define TopDivisorTilingPlacingMode /*---------------*/ 2
#define BottomDivisorTilingPlacingMode /*------------*/ 3
#define LeftDivisorTilingPlacingMode /*--------------*/ 4
#define RightDivisorTilingPlacingMode /*-------------*/ 5

#define EqualTilingRearangementMode /*---------------*/ 0
#define UnequalClosestTilingRearangementMode /*------*/ 1
#define UnequalFarthestTilingRearangementMode /*-----*/ 2

typedef unsigned int MonitorValue;
typedef uint8_t RearangementMode;

#define ADDTILINGWINDOW /*---------------------------*/ addTilingWindow(event.xmaprequest.parent, event.xmaprequest.window, containerAmount, cursor.m.current, gapsX, gapsY, border.x, border.y, cursor.c.wall, cursor.c.start, openErrorStream, errorStreamPath, tilingPlacingMode, tilingWindowDivisor, tilingMinimumWidth);

static void addTilingWindow(
							const Window w, const Window s,
							const unsigned int containerAmount,
							const XRRMonitorInfo *const monitor,
							const unsigned int gapsX, const unsigned int gapsY,
							const unsigned int borderX, const unsigned int borderY,
							const Container *const containerWall,
							const Container *containerCurrent,
							const bool openErrorStream,
							const char *const errorStreamPath,
							const TilingPlacingMode placingMode,
							const unsigned int windowDivisor,
							const unsigned int minimumWidth
){
	const int mx = (*monitor).x;
	const int my = (*monitor).y;
	const unsigned int mwidth = (*monitor).width;
	const unsigned int mheight = (*monitor).height;
	unsigned int width;
	unsigned int height;
	if(containerAmount){
		MonitorValue *monitorValue = malloc(containerAmount * sizeof(bool));
		Window root;
		int x;
		int y;
		unsigned int border;
		unsigned int depth;
		unsigned int monitorContainerAmount = 0;
		if(!monitorValue){
			printError("ram is full, could not add window in tiling mode");
		}
		addContainerToMonitor:{
			XGetGeometry(display, (*containerCurrent).window, &root, &x, &y, &width, &height, &border, &depth);
			if(closedOpenInterval(x, mx, mx + (int)mwidth) && closedOpenInterval(y, my, my + (int)mheight)){
				*monitorValue = RootMonitorValue;
				++monitorContainerAmount;
			}else{
				*monitorValue = NoMonitorValue;
			}
			if(++containerCurrent < containerWall){
				++monitorValue;
				goto addContainerToMonitor;
			}
		}
		if(monitorContainerAmount){
			unsigned int newWidth;
			unsigned int newHeight;
			int newX;
			int newY;
			unsigned int oldWidth = (*monitor).width - 2 * gapsX;



			int xToCheck = (*monitor).x + (*monitor).width - gapsX;
			int y1ToCheck = (*monitor).y - gapsX;
			int y2ToCheck = (*monitor).y + (*monitor).height - gapsX;
			unsigned int i;
			unsigned int ii;
			unsigned int level = 1;
			unsigned int iter = 1;
			unsigned int nextIter = 0;
			bool foundNone;



			containerCurrent -= containerAmount;
			monitorValue -= containerAmount - 1;



			oldWidth -= oldWidth / windowDivisor - gapsX;



			for(;;){
				foundNone = 1;
				for(i = 0; i < iter; ++i){
					if(level > 1){
						unsigned int currentIter = 0;
						for(ii = 0; ii < containerAmount; ++ii){
							if(monitorValue[ii] == level && currentIter == i){
								XGetGeometry(display, containerCurrent[ii].window, &root, &x, &y, &width, &height, &border, &depth);
								break;
							}
							++currentIter;
						}
						xToCheck = x - gapsX;
						y1ToCheck = y - gapsX;
						y2ToCheck = y + height - gapsX;
					}
					for(ii = 0; ii < containerAmount; ++ii){
						if(monitorValue[ii] == RootMonitorValue){
							XGetGeometry(display, containerCurrent[ii].window, &root, &x, &y, &width, &height, &border, &depth);
							if(x + (int)width == xToCheck && (closedInterval(y, y1ToCheck, y2ToCheck) || closedInterval(y + (int)height, y1ToCheck, y2ToCheck))){
								foundNone = 0;
								++monitorValue[ii];
								++nextIter;
							}
						}
					}
				}
				if(foundNone){
					break;
				}
				++level;
				iter = nextIter;
				nextIter = 0;
			}
			for(i = 0; i < containerAmount; ++i){
				fprintf(stdout, "%u\n", monitorValue[i]);
			}



			{
				RearangementMode rearangementMode = UnequalFarthestTilingRearangementMode;
				switch(rearangementMode){
					case EqualTilingRearangementMode:{
						/**/



					}
					case UnequalClosestTilingRearangementMode:{
						/**/



					}
					default:{
						unsigned int reduceWidth = (mwidth - 2 * gapsX) / windowDivisor;



#define ToEditMonitorValue /*-*/ 2



						unsigned int i;
						for(i = 0; i < containerAmount; ++i){
							XGetGeometry(display, containerCurrent[i].window, &root, &x, &y, &width, &height, &border, &depth);
							if(x == mx + (int)gapsX && width - minimumWidth > reduceWidth){
								monitorValue[ii] = ToEditMonitorValue;
							}
						}
						for(i = 0; i < containerAmount; ++i){
							if(monitorValue[i] == ToEditMonitorValue){
								XGetGeometry(display, containerCurrent[i].window, &root, &x, &y, &width, &height, &border, &depth);



								/**/



							}
						}



					}
				}
			}









			newWidth = (mwidth - 2 * gapsX) / windowDivisor;
			newX = mx + mwidth - gapsX - newWidth;
			newY = my + gapsY;
			newHeight = mheight - 2 * gapsY;
			XMoveResizeWindow(display, w, newX, newY, newWidth, newHeight);
			XResizeWindow(display, s, newWidth - borderX, newHeight - borderY);
			free(monitorValue);
		}else{
			free(monitorValue);
			goto placeFirstTilingWindow;
		}
	}else{
		placeFirstTilingWindow:{
			width = mwidth - 2 * gapsX;
			height = mheight - 2 * gapsY;
			XMoveResizeWindow(display, w, mx + gapsX, my + gapsY, width, height);
			XResizeWindow(display, s, width - borderX, height - borderY);
		}
	}









	/*const Options useSeparatorsOption = option & TilingUseSeparatorsOption;
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
			if(tilingPlacingMode == HorizontalEqualTilingPlacingMode){
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
			counter = 0;
			do{
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
			}while(++counter < monitorContainerAmount);
		}
		XMoveResizeWindow(display, container[allocatedContainerAmount].window, x, y, width, height);
		XResizeWindow(display, event.xmaprequest.window, width - border.axis.x, height - border.axis.y);
	}else{



		//



	}*/
	return;
}









REMOVETILINGWINDOW_DEC{
	/*if(managementMode == TilingManagementMode && allocatedContainerAmount){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	bool containerInMonitorMap[allocatedContainerAmount]; \
	if(monitorContainerAmount){ \
		const Options useSeparatorsOption = option & TilingUseSeparatorsOption; \
		if(tilingReplacingMode <= VerticalEqualTilingReplacingMode){ \
			int x = monitorInfo.x + gapsX; \
			int y = monitorInfo.y + gapsY; \
			unsigned int width; \
			unsigned int height; \
			unsigned int counter = 0; \
			int *position; \
			unsigned int *size; \
			unsigned int gaps; \
			unsigned int totalSeparatorWidth = separatorBorders + separatorWidth; \
			unsigned int abnormal; \
			unsigned int normal; \
			unsigned int currentContainerList[monitorContainerAmount]; \
			int *attribute; \
			{ \
				unsigned int monitorSize; \
				unsigned int availableSpace; \
				if(tilingReplacingMode == HorizontalEqualTilingReplacingMode){ \
					height = monitorInfo.height - 2 * gapsY; \
					position = &x; \
					size = &width; \
					gaps = gapsX; \
					monitorSize = monitorInfo.width; \
					attribute = &windowAttributes.x; \
				}else{ \
					width = monitorInfo.width - 2 * gapsX; \
					position = &y; \
					size = &height; \
					gaps = gapsY; \
					monitorSize = monitorInfo.height; \
					attribute = &windowAttributes.y; \
				} \
				if(useSeparatorsOption){ \
					availableSpace = monitorSize - (2 * monitorContainerAmount * gaps + (monitorContainerAmount - 1) * totalSeparatorWidth); \
				}else{ \
					availableSpace = monitorSize - (monitorContainerAmount + 1) * gaps; \
				} \
				normal = availableSpace / monitorContainerAmount; \
				abnormal = availableSpace - (monitorContainerAmount - 1) * normal; \
			} \
			*size = normal; \
			totalSeparatorWidth += gaps; \
			{ \
				int attributeList[monitorContainerAmount]; \
				currentContainer = 0; \
				for(;;){ \
					if(containerInMonitorMap[currentContainer]){ \
						XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
						currentContainerList[counter] = currentContainer; \
						attributeList[counter] = *attribute; \
						if(++counter == monitorContainerAmount){ \
							break; \
						} \
					} \
					++currentContainer; \
				} \
				const unsigned int monitorContainerAmount1 = monitorContainerAmount + 1; \
				unsigned int ccl; \
				int al; \
				for(currentContainer = 1; currentContainer < monitorContainerAmount; ++currentContainer){ \
					for(counter = 1; counter < monitorContainerAmount1 - currentContainer; ++counter){ \
						if(attributeList[counter - 1] > attributeList[counter]){ \
							ccl = currentContainerList[counter]; \
							currentContainerList[counter] = currentContainerList[counter - 1]; \
							currentContainerList[counter - 1] = ccl; \
							al = attributeList[counter]; \
							attributeList[counter] = attributeList[counter - 1]; \
							attributeList[counter - 1] = al; \
						} \
					} \
				} \
			} \
			{ \
				const unsigned int middle = monitorContainerAmount / 2; \
				counter = 0; \
				for(;;){ \
					currentContainer = currentContainerList[counter]; \
					XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
					if(++counter == monitorContainerAmount){ \
						break; \
					} \
					*position += *size + gaps; \
					if(useSeparatorsOption){ \
						*position += totalSeparatorWidth; \
					} \
					if(counter == middle){ \
						*size = abnormal; \
					}else{ \
						*size = normal; \
					} \
				} \
			} \
		} \
	}*/



	return;
}









void eventLoop(void){
	const Window rootWindow = XDefaultRootWindow(display);
	const Container *focused = NULL;
	ManagementMode managementMode = GriddingManagementMode;
	Options option = FloatingUseFocusedWindowColorOption | FloatingMinimalMoveOption | FloatingMinimalResizeOption | FloatingAllowMonitorStickingOption | FloatingAllowSnappingOption | FloatingUseSnappingWindowOption | FloatingPortWindowsFromGriddingOption | InGridUseFocusedWindowColorOption | GriddingUseFocusedWindowColorOption | GriddingPortWindowsFromFloatingOption | TilingUseFocusedWindowColorOption | TilingUseSeparatorsOption | TilingUseGapsOption | MaximizedUseFocusedWindowColorOption;
	PointerInfo pointerInfo = MovePointerInfo;
	GridOptions gridOption = NoGridOptions;
	Cascade cascade;
	DefaultGridPosition defaultGridPosition = TopLeftDefaultGridPosition;
	DirectionAxis border;
	Colors color;
	DataCursors cursor;
	TilingPrioritization tilingPrioritize;
	MotionContainer motionContainer;
	ICCCMAtoms WM;
	EWMHAtoms _NET;
	TilingPlacingMode tilingPlacingMode = RightDivisorTilingPlacingMode;
	InputMethod inputMethod = EnterInputMethod | KeyPressInputMethod | ButtonPressInputMethod;
	unsigned int monitorAmount;
	unsigned int shortcutAmount = 51;
	unsigned int buttonAmount = 3;
	unsigned int executeAmount = 1;
	unsigned int separatorWidth = 12;
	unsigned int separatorBorder = 1;
	unsigned int shadow = 10;
	unsigned int displayWidth = XDisplayWidth(display, XDefaultScreen(display));
	unsigned int displayHeight = XDisplayHeight(display, XDefaultScreen(display));



	unsigned int floatingMinimumWidth = 20;
	unsigned int floatingMinimumHeight = 20;
	unsigned int floatingMaximumWidth = displayWidth;
	unsigned int floatingMaximumHeight = displayHeight;
	unsigned int floatingExtendWidth = 10;
	unsigned int floatingExtendHeight = 10;
	unsigned int floatingShrinkWidth = 10;
	unsigned int floatingShrinkHeight = 10;
	int floatingStickyThresholdX = 10;
	int floatingStickyThresholdY = 10;
	int floatingDistanceToTravelX = 50;
	int floatingDistanceToTravelY = 50;
	int floatingSnappingThreshold = 50;
	unsigned int floatingWindowDivisor = 2;
	EnterInputException floatingEnterInputException = ResizeGridEnterInputException | CancelMoveResizeEnterInputException | MoveToEnterInputException | MoveMonitorEnterInputException | ToggleAddRemoveGridEnterInputException | MoveGridEnterInputException | ExtendEnterInputException | ShrinkEnterInputException;



	unsigned int gridWidth = 7;
	unsigned int gridHeight = 7;
	unsigned int gridMinWidth = 1;
	unsigned int gridMinHeight = 1;
	unsigned int gridMaxWidth = 20;
	unsigned int gridMaxHeight = 20;
	EnterInputException griddingEnterInputException = ResizeGridEnterInputException | CancelMoveResizeEnterInputException | MoveToEnterInputException | MoveMonitorEnterInputException | ToggleAddRemoveGridEnterInputException | MoveGridEnterInputException | ExtendEnterInputException | ShrinkEnterInputException;
	EnterInputException inGridEnterInputException = ResizeGridEnterInputException | CancelMoveResizeEnterInputException | MoveToEnterInputException | MoveMonitorEnterInputException | ToggleAddRemoveGridEnterInputException | MoveGridEnterInputException | ExtendEnterInputException | ShrinkEnterInputException;



	unsigned int tilingMinimumWidth = 20;
	unsigned int tilingMinimumHeight = 20;
	unsigned int tilingExtendWidth = 10;
	unsigned int tilingExtendHeight = 10;
	unsigned int tilingShrinkWidth = 10;
	unsigned int tilingShrinkHeight = 10;
	unsigned int tilingGapsX = 10;
	unsigned int tilingGapsY = 10;
	unsigned int gapsX;
	unsigned int gapsY;
	unsigned int tilingWindowDivisor = 3;
	EnterInputException tilingEnterInputException = ResizeGridEnterInputException | CancelMoveResizeEnterInputException | MoveToEnterInputException | MoveMonitorEnterInputException | ToggleAddRemoveGridEnterInputException | MoveGridEnterInputException | ExtendEnterInputException | ShrinkEnterInputException;



	void *data = NULL;
	char *errorStreamPath = NULL;
	bool canConfigurePosition = 1;
	bool openErrorStream = 0;
	bool forcePointerMonitor;
	bool keyDoubling = 0;
	bool buttonDoubling = 0;
	Command command = NoCommand;
	Window genericWindow;
	unsigned int genericBorder;
	unsigned int genericDepth;
	int genericInteger;
	unsigned int genericUnsignedInteger;
	unsigned int current;
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	XVisualInfo visualInfo;
	XSetWindowAttributes createWindowAttributes;
	XEvent event;
	XEvent e;
	int rrEventBase;
	{
		XRRMonitorInfo *monitor = XRRGetMonitors(display, rootWindow, True, &genericInteger);
		if(!monitor){
			printError("could not retrieve monitors");
			mode = ExitMode;
			goto emergencyExit;
		}
		monitorAmount = genericInteger;
		if(!(data = malloc(shortcutAmount * sizeof(Shortcut) + buttonAmount * sizeof(Button) + executeAmount * sizeof(Execute) + monitorAmount * (sizeof(XRRMonitorInfo) + sizeof(Window))))){
			printError("ram is full, could not store general data");
			XRRFreeMonitors(monitor);
			mode = ExitMode;
			goto emergencyExit;
		}
		cursor.s.start = (Shortcut *)data;
		cursor.s.wall = cursor.s.start + shortcutAmount;
		cursor.b.start = (Button *)cursor.s.wall;
		cursor.b.wall = cursor.b.start + buttonAmount;
		cursor.e.start = (Execute *)cursor.b.wall;
		cursor.e.wall = cursor.e.start + executeAmount;
		cursor.m.start = (XRRMonitorInfo *)cursor.e.wall;
		cursor.m.wall = cursor.m.start + monitorAmount;
		cursor.g.start = (Window *)cursor.m.wall;
		cursor.g.wall = cursor.g.start + monitorAmount;
		cursor.m.current = cursor.m.start;
		storeMonitor:{
			*cursor.m.current = *monitor;
			if(++cursor.m.current < cursor.m.wall){
				++monitor;
				goto storeMonitor;
			}
		}
		XRRFreeMonitors(monitor - monitorAmount + 1);
	}
	if(!(containerData || (containerData = malloc(monitorAmount * sizeof(MaximizedContainer) + containerAmount * sizeof(Container))))){
		printError("ram is full, could not store containers");
		mode = ExitMode;
		goto emergencyExit;
	}
	cursor.mc.start = (MaximizedContainer *)containerData;
	cursor.mc.wall = cursor.mc.start + monitorAmount;
	cursor.c.start = (Container *)cursor.mc.wall;
	cursor.c.wall = cursor.c.start + containerAmount;



	cursor.s.current = cursor.s.start;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 39;
	(*cursor.s.current).command = ExecuteCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 12;
	(*cursor.s.current).command = FloatingModeCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 13;
	(*cursor.s.current).command = GriddingModeCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 14;
	(*cursor.s.current).command = TilingModeCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 42;
	(*cursor.s.current).command = ToggleGridVisibilityCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 43;
	(*cursor.s.current).command = ToggleGapsCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod1Mask;
	(*cursor.s.current).keycode = 38;
	(*cursor.s.current).command = AttachCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 27;
	(*cursor.s.current).command = RecascadeCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 9;
	(*cursor.s.current).command = SwapLeftMonitorCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod1Mask;
	(*cursor.s.current).keycode = 88;
	(*cursor.s.current).command = MoveBottomCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod1Mask;
	(*cursor.s.current).keycode = 83;
	(*cursor.s.current).command = MoveLeftCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod1Mask;
	(*cursor.s.current).keycode = 85;
	(*cursor.s.current).command = MoveRightCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod1Mask;
	(*cursor.s.current).keycode = 79;
	(*cursor.s.current).command = MoveTopLeftCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod1Mask;
	(*cursor.s.current).keycode = 81;
	(*cursor.s.current).command = MoveTopRightCommand;
	++cursor.s.current;
	(*cursor.s.current).keycode = 87;
	(*cursor.s.current).masks = ControlMask | Mod1Mask;
	(*cursor.s.current).command = MoveBottomLeftCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod1Mask;
	(*cursor.s.current).keycode = 89;
	(*cursor.s.current).command = MoveBottomRightCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod1Mask;
	(*cursor.s.current).keycode = 84;
	(*cursor.s.current).command = MoveCenterCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod1Mask;
	(*cursor.s.current).keycode = 80;
	(*cursor.s.current).command = MoveFullCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 58;
	(*cursor.s.current).command = MoveNextMonitorCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 58;
	(*cursor.s.current).command = MovePreviousMonitorCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod4Mask;
	(*cursor.s.current).keycode = 111;
	(*cursor.s.current).command = MoveAboveMonitorCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod4Mask;
	(*cursor.s.current).keycode = 116;
	(*cursor.s.current).command = MoveBelowMonitorCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod4Mask;
	(*cursor.s.current).keycode = 113;
	(*cursor.s.current).command = MoveLeftMonitorCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod4Mask;
	(*cursor.s.current).keycode = 114;
	(*cursor.s.current).command = MoveRightMonitorCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 38;
	(*cursor.s.current).command = ToggleAddRemoveGridCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 111;
	(*cursor.s.current).command = MoveUpGridCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 116;
	(*cursor.s.current).command = MoveDownGridCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 113;
	(*cursor.s.current).command = MoveLeftGridCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 114;
	(*cursor.s.current).command = MoveRightGridCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod1Mask | Mod4Mask;
	(*cursor.s.current).keycode = 80;
	(*cursor.s.current).command = ExtendUpCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod1Mask | Mod4Mask;
	(*cursor.s.current).keycode = 88;
	(*cursor.s.current).command = ExtendDownCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod1Mask | Mod4Mask;
	(*cursor.s.current).keycode = 83;
	(*cursor.s.current).command = ExtendLeftCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod1Mask | Mod4Mask;
	(*cursor.s.current).keycode = 85;
	(*cursor.s.current).command = ExtendRightCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod1Mask | Mod4Mask;
	(*cursor.s.current).keycode = 79;
	(*cursor.s.current).command = ExtendUpLeftCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod1Mask | Mod4Mask;
	(*cursor.s.current).keycode = 81;
	(*cursor.s.current).command = ExtendUpRightCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod1Mask | Mod4Mask;
	(*cursor.s.current).keycode = 87;
	(*cursor.s.current).command = ExtendDownLeftCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod1Mask | Mod4Mask;
	(*cursor.s.current).keycode = 89;
	(*cursor.s.current).command = ExtendDownRightCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 80;
	(*cursor.s.current).command = ShrinkUpCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 88;
	(*cursor.s.current).command = ShrinkDownCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 83;
	(*cursor.s.current).command = ShrinkLeftCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 85;
	(*cursor.s.current).command = ShrinkRightCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 79;
	(*cursor.s.current).command = ShrinkUpLeftCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 81;
	(*cursor.s.current).command = ShrinkUpRightCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 87;
	(*cursor.s.current).command = ShrinkDownLeftCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask | Mod4Mask;
	(*cursor.s.current).keycode = 89;
	(*cursor.s.current).command = ShrinkDownRightCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = None;
	(*cursor.s.current).keycode = 95;
	(*cursor.s.current).command = FullscreenCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ShiftMask;
	(*cursor.s.current).keycode = 95;
	(*cursor.s.current).command = BigscreenCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = ControlMask | Mod1Mask;
	(*cursor.s.current).keycode = 40;
	(*cursor.s.current).command = DetachCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 24;
	(*cursor.s.current).command = CloseCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 45;
	(*cursor.s.current).command = KillCommand;
	++cursor.s.current;
	(*cursor.s.current).masks = Mod4Mask;
	(*cursor.s.current).keycode = 57;
	(*cursor.s.current).command = MoveResizeCommand;



	cursor.b.current = cursor.b.start;
	(*cursor.b.current).masks = Mod4Mask;
	(*cursor.b.current).button = Button4;
	(*cursor.b.current).command = EnlargeGridBothCommand;
	++cursor.b.current;
	(*cursor.b.current).masks = Mod4Mask;
	(*cursor.b.current).button = Button5;
	(*cursor.b.current).command = ShrinkGridBothCommand;
	++cursor.b.current;
	(*cursor.b.current).masks = Mod4Mask;
	(*cursor.b.current).button = Button1;
	(*cursor.b.current).command = MoveResizeCommand;



	XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo);
	createWindowAttributes.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone);



	border.up = 1;
	border.down = 1;
	border.left = 1;
	border.right = 1;
	border.x = border.left + border.right;
	border.y = border.up + border.down;



	color.containerShadow = 0x7F000000;
	color.gridSubwindowBorder = 0x10975C57;
	color.gridSubwindowBackground = 0x00000000;
	color.separatorBorder = 0xFFFFFFFF;
	color.separatorBackground = 0xFF000000;
	color.focusedContainerBackground.floating = 0xFF00FF00;
	color.focusedContainerBackground.gridding = 0xFFFF0000;
	color.focusedContainerBackground.tiling = 0xFF0000FF;
	color.focusedContainerBackground.inGrid = 0xFFFF7F00;
	color.focusedContainerBackground.fullscreen = 0xFFFFFFFF;
	color.focusedContainerBackground.bigscreen = 0xFFFF007F;
	color.containerBackground.floating = 0xFF000000;
	color.containerBackground.gridding = 0xFF000000;
	color.containerBackground.tiling = 0xFF000000;
	color.containerBackground.inGrid = 0xFF000000;
	color.containerBackground.fullscreen = 0xFF000000;
	color.containerBackground.bigscreen = 0xFF000000;
	color.motionContainer.glassBorder = 0x00000000;
	color.motionContainer.glassBackground = 0x00000000;
	color.motionContainer.minimalMoveBorder = 0xFFF2C6B4;
	color.motionContainer.minimalMoveBackground = 0x7FF07746;
	color.motionContainer.minimalResizeBorder = 0xFFF2C6B4;
	color.motionContainer.minimalResizeBackground = 0x7FF07746;
	color.motionContainer.snappingBackground = 0x00000000;
	color.motionContainer.snappingBorder = 0xFFFFFFFF;



	if(floatingWindowDivisor < 1){
		floatingWindowDivisor = 1;
	}
	if(floatingMinimumWidth < border.x + 1){
		floatingMinimumWidth = border.x + 1;
	}
	if(floatingMinimumHeight < border.y + 1){
		floatingMinimumHeight = border.y + 1;
	}
	if(tilingMinimumWidth < border.x + 1){
		tilingMinimumWidth = border.x + 1;
	}
	if(tilingMinimumHeight < border.y + 1){
		tilingMinimumHeight = border.y + 1;
	}
	if(option(TilingUseGaps)){
		gapsX = tilingGapsX;
		gapsY = tilingGapsY;
	}else{
		gapsX = 0;
		gapsY = 0;
	}



	tilingPrioritize = NoTilingPrioritization;



	{
		Command *cursor = &motionContainer.snap;
		*cursor = MoveFullCommand;
		*(++cursor) = MoveCenterCommand;
		*(++cursor) = MoveLeftCommand;
		*(++cursor) = MoveRightCommand;
		*(++cursor) = MoveTopLeftCommand;
		*(++cursor) = MoveTopRightCommand;
		*(++cursor) = MoveBottomLeftCommand;
		*(++cursor) = MoveBottomRightCommand;
		*(++cursor) = NoCommand;
	}
	motionContainer.snappingWindow = None;
	motionContainer.minimalMoveBorder = 1;
	motionContainer.minimalResizeBorder = 1;
	motionContainer.snappingBorder = 1;
	motionContainer.snappingDivisorX = 2;
	motionContainer.snappingDivisorY = 2;
	motionContainer.snappingOffset.up = 5;
	motionContainer.snappingOffset.down = 5;
	motionContainer.snappingOffset.left = 5;
	motionContainer.snappingOffset.right = 5;
	motionContainer.snappingOffset.x = motionContainer.snappingOffset.left + motionContainer.snappingOffset.right;
	motionContainer.snappingOffset.y = motionContainer.snappingOffset.up + motionContainer.snappingOffset.down;
	motionContainer.action = NoMotionAction;



	{
		const AttributesMasks masks = CWBackPixel | CWBorderPixel | CWOverrideRedirect | CWColormap;
		createWindowAttributes.background_pixel = 0x00000000;
		createWindowAttributes.border_pixel = 0x00000000;
		createWindowAttributes.override_redirect = True;
		cursor.g.current = cursor.g.start;
		cursor.m.current = cursor.m.start;
		cursor.mc.current = cursor.mc.start;
		setupMonitorProperties:{
			*cursor.g.current = XCreateWindow(display, rootWindow, (*cursor.m.current).x, (*cursor.m.current).y, (*cursor.m.current).width, (*cursor.m.current).height, 0, visualInfo.depth, InputOutput, visualInfo.visual, masks, &createWindowAttributes);
			(*cursor.mc.current).window = None;
			(*cursor.mc.current).subwindow = None;
			width = (*cursor.m.current).width / 3;
			height = (*cursor.m.current).height / 3;
			if(gridMaxWidth > width){
				gridMaxWidth = width;
			}
			if(gridMaxHeight > height){
				gridMaxHeight = height;
			}
			if(++cursor.m.current < cursor.m.wall){
				++cursor.g.current;
				++cursor.mc.current;
				goto setupMonitorProperties;
			}
		}
	}
	if(gridMinWidth > gridMaxWidth){
		gridMinWidth = gridMaxWidth;
	}
	if(gridMinHeight > gridMaxHeight){
		gridMinHeight = gridMaxHeight;
	}



	WM.PROTOCOLS = XInternAtom(display, "WM_PROTOCOLS", False);
	WM.DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False);
	_NET.WM.STATE.this = XInternAtom(display, "_NET_WM_STATE", False);
	_NET.WM.STATE.FULLSCREEN = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);



	cascade.offsetX = 20;
	cascade.offsetY = 20;
	cascade.option = OverrideGridWindowsCascadeOption | OverrideMaximizedWindowsCascadeOption;
	cascade.mode = SmartCascadeMode;



	createWindowAttributes.background_pixel = color.motionContainer.glassBackground;
	createWindowAttributes.border_pixel = color.motionContainer.glassBorder;
	motionContainer.glass = XCreateWindow(display, rootWindow, 0, 0, displayWidth, displayHeight, 0, visualInfo.depth, InputOutput, visualInfo.visual, CWBackPixel | CWBorderPixel | CWOverrideRedirect | CWColormap, &createWindowAttributes);
	XSelectInput(display, motionContainer.glass, ButtonReleaseMask | PointerMotionMask);



	if(option(FloatingMinimalMove) || option(FloatingMinimalResize)){
		createWindowAttributes.border_pixel = 0x00000000;
		motionContainer.minimalWindow = XCreateWindow(display, rootWindow, 0, 0, 1, 1, 0, visualInfo.depth, InputOutput, visualInfo.visual, CWBorderPixel | CWColormap, &createWindowAttributes);
	}



	if(option(FloatingUseSnappingWindow)){
		createWindowAttributes.background_pixel = color.motionContainer.snappingBackground;
		createWindowAttributes.border_pixel = color.motionContainer.snappingBorder;
		motionContainer.snappingWindow = XCreateWindow(display, rootWindow, 0, 0, 1, 1, motionContainer.snappingBorder, visualInfo.depth, InputOutput, visualInfo.visual, CWBackPixel | CWBorderPixel | CWColormap, &createWindowAttributes);
	}



	createWindowAttributes.border_pixel = color.containerShadow;



	if(shortcutAmount){
		cursor.s.current = cursor.s.start;
		grabRootKey:{
			if((*cursor.s.current).command <= RootCommandCeiling && (*cursor.s.current).keycode != AnyKey){
				XGrabKey(display, (*cursor.s.current).keycode, (*cursor.s.current).masks, rootWindow, True, GrabModeAsync, GrabModeAsync);
			}
			if(++cursor.s.current < cursor.s.wall){
				goto grabRootKey;
			}
		}
	}
	if(buttonAmount){
		cursor.b.current = cursor.b.start;
		grabRootButton:{
			if((*cursor.b.current).command <= RootCommandCeiling && (*cursor.b.current).button != AnyButton){
				XGrabButton(display, (*cursor.b.current).button, (*cursor.b.current).masks, rootWindow, True, NoEventMask, GrabModeAsync, GrabModeAsync, None, None);
			}
			if(++cursor.b.current < cursor.b.wall){
				goto grabRootButton;
			}
		}
	}
	XSelectInput(display, rootWindow, SubstructureRedirectMask);
	XRRSelectInput(display, rootWindow, RRScreenChangeNotifyMask);
	if(!XRRQueryExtension(display, &rrEventBase, &genericInteger)){
		printError("could not query the xrandr extension");
		rrEventBase = 0;
	}
	event.type = None;
	XSync(display, False);
	eventLoop:{
		if(inputMethod & EnterInputMethod){
			XSync(display, False);
			if(!XPending(display)){
				command = NoCommand;
			}
		}
		XNextEvent(display, &event);
		printEvent(event);
		switch(event.type){
			case KeyPress:{
				goto keyPressEvent;
			}
			case KeyRelease:{
				goto keyReleaseEvent;
			}
			case ButtonPress:{
				goto buttonPressEvent;
			}
			case ButtonRelease:{
				goto buttonReleaseEvent;
			}
			case MotionNotify:{
				goto motionNotifyEvent;
			}
			case EnterNotify:{
				goto enterNotifyEvent;
			}
			case DestroyNotify:{
				goto destroyNotifyEvent;
			}
			case UnmapNotify:{
				goto unmapNotifyEvent;
			}
			case MapRequest:{
				goto mapRequestEvent;
			}
			case ConfigureNotify:{
				goto eventLoop;
			}
			case ConfigureRequest:{
				goto configureRequestEvent;
			}
			case ClientMessage:{
				goto clientMessageEvent;
			}
			default:{
				if(event.type == RRScreenChangeNotify + rrEventBase){
					goto screenChangeNotifyEvent;
				}
				if(openErrorStream){
					if((errorStream = fopen(errorStreamPath, "w"))){
						fprintf(errorStream, "%s: unexpected event (%u), ignored\n", programName, event.type);
						fclose(errorStream);
						goto eventLoop;
					}
					goto eventLoop;
				}
				fprintf(errorStream, "%s: unexpected event (%u), ignored\n", programName, event.type);
				goto eventLoop;
			}
		}
		keyPressEvent:{
			if(shortcutAmount){
				cursor.s.current = cursor.s.start;
				findShortcut:{
					if((*cursor.s.current).keycode == event.xkey.keycode && (*cursor.s.current).masks == event.xkey.state){
						command = (*cursor.s.current).command;
						if(motionContainer.action && !command(CancelMoveResize)){
							goto keyButtonRelease;
						}
						forcePointerMonitor = 0;
						goto findCommand;
					}
					if(++cursor.s.current < cursor.s.wall){
						goto findShortcut;
					}
				}
			}
		}
		goto eventLoop;
		keyReleaseEvent:{
			if(motionContainer.action && shortcutAmount){
				goto keyButtonRelease;
			}
		}
		goto eventLoop;
		buttonPressEvent:{
			if(buttonAmount){
				cursor.b.current = cursor.b.start;
				findButton:{
					if((*cursor.b.current).button == event.xbutton.button && (*cursor.b.current).masks == event.xbutton.state){
						command = (*cursor.b.current).command;
						if(motionContainer.action && !command(CancelMoveResize)){
							goto keyButtonRelease;
						}
						forcePointerMonitor = 0;
						goto findCommand;
					}
					if(++cursor.b.current < cursor.b.wall){
						goto findButton;
					}
				}
			}
		}
		goto eventLoop;
		buttonReleaseEvent:{
			if(motionContainer.action && buttonAmount){
				keyButtonRelease:{
					XUnmapWindow(display, motionContainer.glass);
					motionContainer.action = NoMotionAction;
					if(motionAction(Move)){
						if(motionContainer.subaction){
							if(motionOption(SnappingMapped)){
								XUnmapWindow(display, motionContainer.snappingWindow);
							}
							command = *(&motionContainer.snap + motionContainer.subaction - SnappingMotionSubactionOffset);
							if(command){
								if(option(FloatingMinimalMove)){
									XUnmapWindow(display, motionContainer.window);
									genericWindow = motionContainer.window;
									motionContainer.window = motionContainer.minimalWindow;
									motionContainer.minimalWindow = genericWindow;
									genericUnsignedInteger = shadow;
									shadow = motionContainer.minimalMoveBorder;
									motionContainer.minimalMoveBorder = genericUnsignedInteger;
								}
								if(pointerInfo(Move)){
									forcePointerMonitor = 1;
								}else{
									forcePointerMonitor = 0;
								}
								event.xany.window = motionContainer.window;
								motionContainer.action = NoMotionAction;
								goto findCommand;
							}
						}
						if(option(FloatingMinimalMove)){
							XGetGeometry(display, motionContainer.window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
							XMoveWindow(display, motionContainer.minimalWindow, x + shadow - motionContainer.minimalMoveBorder, y + shadow - motionContainer.minimalMoveBorder);
							XUnmapWindow(display, motionContainer.window);
							genericWindow = motionContainer.window;
							motionContainer.window = motionContainer.minimalWindow;
							motionContainer.minimalWindow = genericWindow;
							genericUnsignedInteger = shadow;
							shadow = motionContainer.minimalMoveBorder;
							motionContainer.minimalMoveBorder = genericUnsignedInteger;
						}
						goto eventLoop;
					}
					if(option(FloatingMinimalResize)){
						XGetGeometry(display, motionContainer.window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
						XMoveResizeWindow(display, motionContainer.minimalWindow, x + motionContainer.minimalMoveBorder - shadow, y + motionContainer.minimalMoveBorder - shadow, width, height);
						XResizeWindow(display, motionContainer.subwindow, width - border.x, height - border.y);
						XUnmapWindow(display, motionContainer.window);
						genericWindow = motionContainer.window;
						motionContainer.window = motionContainer.minimalWindow;
						motionContainer.minimalWindow = genericWindow;
					}
					goto eventLoop;
				}
			}
		}
		goto eventLoop;
		motionNotifyEvent:{
			if(XPending(display)){
				XPeekEvent(display, &e);
				if(e.type == MotionNotify){
					goto eventLoop;
				}
			}
			if(motionAction(Move)){
				if(option(FloatingAllowMonitorSticking)){
					current = getCurrentWindowMonitor(motionContainer.window, cursor.m.start, monitorAmount);
					cursor.m.current = cursor.m.start + current;
					if(current != motionContainer.previousMonitor){
						if(motionOption(HasLockedX) && motionContainer.x != (*cursor.m.current).x && motionContainer.x + (int)motionContainer.width != (*cursor.m.current).x + (*cursor.m.current).width){
							motionContainer.option ^= HasLockedXMotionOption;
						}
						if(motionOption(HasLockedY) && motionContainer.y != (*cursor.m.current).y && motionContainer.y + (int)motionContainer.height != (*cursor.m.current).y + (*cursor.m.current).height){
							motionContainer.option ^= HasLockedYMotionOption;
						}
					}
					motionContainer.previousMonitor = current;
					if(closedOpenInterval(motionContainer.x, (*cursor.m.current).x, (*cursor.m.current).x + floatingStickyThresholdX)){
						if(!motionOption(HasLockedX)){
							motionContainer.x = (*cursor.m.current).x;
							XMoveWindow(display, motionContainer.window, motionContainer.x - shadow, motionContainer.y - shadow);
							motionContainer.escapeX = event.xmotion.x_root + floatingDistanceToTravelX;
							motionContainer.option |= HasLockedXMotionOption;
						}else{
							if(event.xmotion.x_root >= motionContainer.escapeX){
								motionContainer.option ^= HasLockedXMotionOption;
							}
						}
					}else if(closedInterval(motionContainer.x + (int)motionContainer.width, (*cursor.m.current).x + (*cursor.m.current).width - floatingStickyThresholdX, (*cursor.m.current).x + (*cursor.m.current).width)){
						if(!motionOption(HasLockedX)){
							motionContainer.x = (*cursor.m.current).x + (*cursor.m.current).width - motionContainer.width;
							XMoveWindow(display, motionContainer.window, motionContainer.x - shadow, motionContainer.y - shadow);
							motionContainer.escapeX = event.xmotion.x_root - floatingDistanceToTravelX;
							motionContainer.option |= HasLockedXMotionOption;
						}else{
							if(event.xmotion.x_root <= motionContainer.escapeX){
								motionContainer.option ^= HasLockedXMotionOption;
							}
						}
					}
					if(closedOpenInterval(motionContainer.y, (*cursor.m.current).y, (*cursor.m.current).y + floatingStickyThresholdY)){
						if(!motionOption(HasLockedY)){
							motionContainer.y = (*cursor.m.current).y;
							XMoveWindow(display, motionContainer.window, motionContainer.x - shadow, motionContainer.y - shadow);
							motionContainer.escapeY = event.xmotion.y_root + floatingDistanceToTravelY;
							motionContainer.option |= HasLockedYMotionOption;
						}else{
							if(event.xmotion.y_root >= motionContainer.escapeY){
								motionContainer.option ^= HasLockedYMotionOption;
							}
						}
					}else if(closedInterval(motionContainer.y + (int)motionContainer.height, (*cursor.m.current).y + (*cursor.m.current).height - floatingStickyThresholdY, (*cursor.m.current).y + (*cursor.m.current).height)){
						if(!motionOption(HasLockedY)){
							motionContainer.y = (*cursor.m.current).y + (*cursor.m.current).height - motionContainer.height;
							XMoveWindow(display, motionContainer.window, motionContainer.x - shadow, motionContainer.y - shadow);
							motionContainer.escapeY = event.xmotion.y_root - floatingDistanceToTravelY;
							motionContainer.option |= HasLockedYMotionOption;
						}else{
							if(event.xmotion.y_root <= motionContainer.escapeY){
								motionContainer.option ^= HasLockedYMotionOption;
							}
						}
					}
					if(!motionOption(HasLockedX)){
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX + shadow;
						if(!motionOption(HasLockedY)){
							goto changeUnlockedY;
						}
						goto moveUnlocked;
					}
					if(!motionOption(HasLockedY)){
						changeUnlockedY:{
							motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY + shadow;
							moveUnlocked:{
								XMoveWindow(display, motionContainer.window, motionContainer.x - shadow, motionContainer.y - shadow);
							}
						}
					}
				}else{
					XMoveWindow(display, motionContainer.window, event.xmotion.x_root - motionContainer.pointerOffsetX, event.xmotion.y_root - motionContainer.pointerOffsetY);
				}
				if(option(FloatingAllowSnapping)){
					cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
					if(closedOpenInterval(event.xmotion.y_root, (*cursor.m.current).y, (*cursor.m.current).y + floatingSnappingThreshold)){
						if(closedOpenInterval(event.xmotion.x_root, (*cursor.m.current).x, (*cursor.m.current).x + floatingSnappingThreshold)){
							if(motionContainer.subaction != TopLeftSnappingMotionSubaction){
								motionContainer.subaction = TopLeftSnappingMotionSubaction;
								goto moveSnappingWindow;
							}
							goto eventLoop;
						}
						if(closedOpenInterval(event.xmotion.x_root, (*cursor.m.current).x + floatingSnappingThreshold, (*cursor.m.current).x + (*cursor.m.current).width - floatingSnappingThreshold)){
							if(motionContainer.subaction != TopSnappingMotionSubaction){
								motionContainer.subaction = TopSnappingMotionSubaction;
								goto moveSnappingWindow;
							}
							goto eventLoop;
						}
						if(motionContainer.subaction != TopRightSnappingMotionSubaction){
							motionContainer.subaction = TopRightSnappingMotionSubaction;
							goto moveSnappingWindow;
						}
						goto eventLoop;
					}
					if(closedOpenInterval(event.xmotion.y_root, (*cursor.m.current).y + floatingSnappingThreshold, (*cursor.m.current).y + (*cursor.m.current).height - floatingSnappingThreshold)){
						if(closedOpenInterval(event.xmotion.x_root, (*cursor.m.current).x, (*cursor.m.current).x + floatingSnappingThreshold)){
							if(motionContainer.subaction != LeftSnappingMotionSubaction){
								motionContainer.subaction = LeftSnappingMotionSubaction;
								goto moveSnappingWindow;
							}
							goto eventLoop;
						}
						if(closedOpenInterval(event.xmotion.x_root, (*cursor.m.current).x + floatingSnappingThreshold, (*cursor.m.current).x + (*cursor.m.current).width - floatingSnappingThreshold)){
							if(motionContainer.subaction != CenterSnappingMotionSubaction){
								motionContainer.subaction = CenterSnappingMotionSubaction;
								goto moveSnappingWindow;
							}
							goto eventLoop;
						}
						if(motionContainer.subaction != RightSnappingMotionSubaction){
							motionContainer.subaction = RightSnappingMotionSubaction;
							goto moveSnappingWindow;
						}
						goto eventLoop;
					}
					if(closedOpenInterval(event.xmotion.y_root, (*cursor.m.current).y + (*cursor.m.current).height - floatingSnappingThreshold, (*cursor.m.current).y + (*cursor.m.current).height)){
						if(closedOpenInterval(event.xmotion.x_root, (*cursor.m.current).x, (*cursor.m.current).x + floatingSnappingThreshold)){
							if(motionContainer.subaction != BottomLeftSnappingMotionSubaction){
								motionContainer.subaction = BottomLeftSnappingMotionSubaction;
								goto moveSnappingWindow;
							}
							goto eventLoop;
						}
						if(closedOpenInterval(event.xmotion.x_root, (*cursor.m.current).x + floatingSnappingThreshold, (*cursor.m.current).x + (*cursor.m.current).width - floatingSnappingThreshold)){
							if(motionContainer.subaction != BottomSnappingMotionSubaction){
								motionContainer.subaction = BottomSnappingMotionSubaction;
								goto moveSnappingWindow;
							}
							goto eventLoop;
						}
						if(motionContainer.subaction != BottomRightSnappingMotionSubaction){
							motionContainer.subaction = BottomRightSnappingMotionSubaction;
							moveSnappingWindow:{
								if(motionContainer.snappingWindow){
									if(option(FloatingSnappingWindowFollowGrid)){
										motionContainer.snappingDivisorX = gridWidth;
										motionContainer.snappingDivisorY = gridHeight;
									}
									switch(*(&motionContainer.snap + motionContainer.subaction - SnappingMotionSubactionOffset)){
										case MoveTopCommand:{
											x = (*cursor.m.current).x - motionContainer.snappingBorder + motionContainer.snappingOffset.left;
											y = (*cursor.m.current).y - motionContainer.snappingBorder + motionContainer.snappingOffset.up;
											width = (*cursor.m.current).width - motionContainer.snappingOffset.x;
											height = (*cursor.m.current).height / motionContainer.snappingDivisorY - motionContainer.snappingOffset.y;
											break;
										}
										case MoveBottomCommand:{
											x = (*cursor.m.current).x - motionContainer.snappingBorder + motionContainer.snappingOffset.left;
											height = (*cursor.m.current).height / motionContainer.snappingDivisorY - motionContainer.snappingOffset.y;
											y = (*cursor.m.current).y + (*cursor.m.current).height - height - motionContainer.snappingBorder - motionContainer.snappingOffset.down;
											width = (*cursor.m.current).width - motionContainer.snappingOffset.x;
											break;
										}
										case MoveLeftCommand:{
											x = (*cursor.m.current).x - motionContainer.snappingBorder + motionContainer.snappingOffset.left;
											y = (*cursor.m.current).y - motionContainer.snappingBorder + motionContainer.snappingOffset.up;
											width = (*cursor.m.current).width / motionContainer.snappingDivisorX - motionContainer.snappingOffset.x;
											height = (*cursor.m.current).height - motionContainer.snappingOffset.y;
											break;
										}
										case MoveRightCommand:{
											y = (*cursor.m.current).y - motionContainer.snappingBorder + motionContainer.snappingOffset.up;
											width = (*cursor.m.current).width / motionContainer.snappingDivisorX - motionContainer.snappingOffset.x;
											x = (*cursor.m.current).x + (*cursor.m.current).width - width - motionContainer.snappingBorder - motionContainer.snappingOffset.right;
											height = (*cursor.m.current).height - motionContainer.snappingOffset.y;
											break;
										}
										case MoveTopLeftCommand:{
											x = (*cursor.m.current).x - motionContainer.snappingBorder + motionContainer.snappingOffset.left;
											y = (*cursor.m.current).y - motionContainer.snappingBorder + motionContainer.snappingOffset.up;
											width = (*cursor.m.current).width / motionContainer.snappingDivisorX - motionContainer.snappingOffset.x;
											height = (*cursor.m.current).height / motionContainer.snappingDivisorY - motionContainer.snappingOffset.y;
											break;
										}
										case MoveTopRightCommand:{
											y = (*cursor.m.current).y - motionContainer.snappingBorder + motionContainer.snappingOffset.up;
											width = (*cursor.m.current).width / motionContainer.snappingDivisorX - motionContainer.snappingOffset.x;
											x = (*cursor.m.current).x + (*cursor.m.current).width - width - motionContainer.snappingBorder - motionContainer.snappingOffset.right;
											height = (*cursor.m.current).height / motionContainer.snappingDivisorY - motionContainer.snappingOffset.y;
											break;
										}
										case MoveBottomLeftCommand:{
											x = (*cursor.m.current).x - motionContainer.snappingBorder + motionContainer.snappingOffset.left;
											height = (*cursor.m.current).height / motionContainer.snappingDivisorY - motionContainer.snappingOffset.y;
											y = (*cursor.m.current).y + (*cursor.m.current).height - height - motionContainer.snappingBorder - motionContainer.snappingOffset.down;
											width = (*cursor.m.current).width / motionContainer.snappingDivisorX - motionContainer.snappingOffset.x;
											break;
										}
										case MoveBottomRightCommand:{
											width = (*cursor.m.current).width / motionContainer.snappingDivisorX - motionContainer.snappingOffset.x;
											height = (*cursor.m.current).height / motionContainer.snappingDivisorY - motionContainer.snappingOffset.y;
											x = (*cursor.m.current).x + (*cursor.m.current).width - width - motionContainer.snappingBorder - motionContainer.snappingOffset.right;
											y = (*cursor.m.current).y + (*cursor.m.current).height - height - motionContainer.snappingBorder - motionContainer.snappingOffset.down;
											break;
										}
										case MoveCenterCommand:{
											width = (*cursor.m.current).width / motionContainer.snappingDivisorX - motionContainer.snappingOffset.x;
											height = (*cursor.m.current).height / motionContainer.snappingDivisorY - motionContainer.snappingOffset.y;
											x = (*cursor.m.current).x + ((*cursor.m.current).width - width) / 2 - motionContainer.snappingBorder;
											y = (*cursor.m.current).y + ((*cursor.m.current).height - height) / 2 - motionContainer.snappingBorder;
											break;
										}
										case MoveFullCommand:{
											x = (*cursor.m.current).x - motionContainer.snappingBorder + motionContainer.snappingOffset.left;
											y = (*cursor.m.current).y - motionContainer.snappingBorder + motionContainer.snappingOffset.up;
											width = (*cursor.m.current).width - motionContainer.snappingOffset.x;
											height = (*cursor.m.current).height - motionContainer.snappingOffset.y;
											break;
										}
										default:{
											if(motionOption(SnappingMapped)){
												XUnmapWindow(display, motionContainer.snappingWindow);
												motionContainer.option ^= SnappingMappedMotionOption;
											}
											motionContainer.subaction = NoMotionSubaction;
											goto eventLoop;
										}
									}
									XMoveResizeWindow(display, motionContainer.snappingWindow, x, y, width, height);
									if(!motionOption(SnappingMapped)){
										if(gridOption(Mapped)){
											cursor.g.current = cursor.g.start;
											lowerGrid:{
												XLowerWindow(display, *cursor.g.current);
												if(++cursor.g.current < cursor.g.wall){
													goto lowerGrid;
												}
											}
										}
										XLowerWindow(display, motionContainer.snappingWindow);
										XMapWindow(display, motionContainer.snappingWindow);
										motionContainer.option |= SnappingMappedMotionOption;
									}
									goto eventLoop;
								}
							}
						}
					}
				}
				goto eventLoop;
			}
			switch(motionContainer.subaction){
				case UpResizeMotionSubaction:{
					motionContainer.height += motionContainer.y + motionContainer.pointerOffsetY - event.xmotion.y_root;
					if((int)motionContainer.height < (int)floatingMinimumHeight){
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY - floatingMinimumHeight + motionContainer.height;
						motionContainer.height = floatingMinimumHeight;
					}else{
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY;
					}
					XMoveResizeWindow(display, motionContainer.window, motionContainer.x, motionContainer.y, motionContainer.width, motionContainer.height);
					break;
				}
				case DownResizeMotionSubaction:{
					motionContainer.height -= motionContainer.y + motionContainer.pointerOffsetY - event.xmotion.y_root;
					if((int)motionContainer.height < (int)floatingMinimumHeight){
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY + floatingMinimumHeight - motionContainer.height;
						motionContainer.height = floatingMinimumHeight;
					}else{
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY;
					}
					XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height);
					break;
				}
				case LeftResizeMotionSubaction:{
					motionContainer.width += motionContainer.x + motionContainer.pointerOffsetX - event.xmotion.x_root;
					if((int)motionContainer.width < (int)floatingMinimumWidth){
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX - floatingMinimumWidth + motionContainer.width;
						motionContainer.width = floatingMinimumWidth;
					}else{
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX;
					}
					XMoveResizeWindow(display, motionContainer.window, motionContainer.x, motionContainer.y, motionContainer.width, motionContainer.height);
					break;
				}
				case RightResizeMotionSubaction:{
					motionContainer.width -= motionContainer.x + motionContainer.pointerOffsetX - event.xmotion.x_root;
					if((int)motionContainer.width < (int)floatingMinimumWidth){
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX + floatingMinimumWidth - motionContainer.width;
						motionContainer.width = floatingMinimumWidth;
					}else{
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX;
					}
					XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height);
					break;
				}
				case UpLeftResizeMotionSubaction:{
					motionContainer.height += motionContainer.y + motionContainer.pointerOffsetY - event.xmotion.y_root;
					motionContainer.width += motionContainer.x + motionContainer.pointerOffsetX - event.xmotion.x_root;
					if((int)motionContainer.height < (int)floatingMinimumHeight){
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY - floatingMinimumHeight + motionContainer.height;
						motionContainer.height = floatingMinimumHeight;
					}else{
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY;
					}
					if((int)motionContainer.width < (int)floatingMinimumWidth){
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX - floatingMinimumWidth + motionContainer.width;
						motionContainer.width = floatingMinimumWidth;
					}else{
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX;
					}
					XMoveResizeWindow(display, motionContainer.window, motionContainer.x, motionContainer.y, motionContainer.width, motionContainer.height);
					break;
				}
				case UpRightResizeMotionSubaction:{
					motionContainer.height += motionContainer.y + motionContainer.pointerOffsetY - event.xmotion.y_root;
					motionContainer.width -= motionContainer.x + motionContainer.pointerOffsetX - event.xmotion.x_root;
					if((int)motionContainer.height < (int)floatingMinimumHeight){
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY - floatingMinimumHeight + motionContainer.height;
						motionContainer.height = floatingMinimumHeight;
					}else{
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY;
					}
					if((int)motionContainer.width < (int)floatingMinimumWidth){
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX + floatingMinimumWidth - motionContainer.width;
						motionContainer.width = floatingMinimumWidth;
					}else{
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX;
					}
					XMoveResizeWindow(display, motionContainer.window, x, motionContainer.y, motionContainer.width, motionContainer.height);
					break;
				}
				case DownLeftResizeMotionSubaction:{
					motionContainer.height -= motionContainer.y + motionContainer.pointerOffsetY - event.xmotion.y_root;
					motionContainer.width += motionContainer.x + motionContainer.pointerOffsetX - event.xmotion.x_root;
					if((int)motionContainer.height < (int)floatingMinimumHeight){
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY + floatingMinimumHeight - motionContainer.height;
						motionContainer.height = floatingMinimumHeight;
					}else{
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY;
					}
					if((int)motionContainer.width < (int)floatingMinimumWidth){
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX - floatingMinimumWidth + motionContainer.width;
						motionContainer.width = floatingMinimumWidth;
					}else{
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX;
					}
					XMoveResizeWindow(display, motionContainer.window, motionContainer.x, y, motionContainer.width, motionContainer.height);
					break;
				}
				default:{
					motionContainer.height -= motionContainer.y + motionContainer.pointerOffsetY - event.xmotion.y_root;
					motionContainer.width -= motionContainer.x + motionContainer.pointerOffsetX - event.xmotion.x_root;
					if((int)motionContainer.height < (int)floatingMinimumHeight){
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY + floatingMinimumHeight - motionContainer.height;
						motionContainer.height = floatingMinimumHeight;
					}else{
						motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY;
					}
					if((int)motionContainer.width < (int)floatingMinimumWidth){
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX + floatingMinimumWidth - motionContainer.width;
						motionContainer.width = floatingMinimumWidth;
					}else{
						motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX;
					}
					XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height);
					break;
				}
			}
			if(!option(FloatingMinimalResize)){
				XResizeWindow(display, motionContainer.subwindow, motionContainer.width - border.x, motionContainer.height - border.y);
			}
		}
		goto eventLoop;
		enterNotifyEvent:{
			if(!motionContainer.action && (!focused || event.xcrossing.window != (*focused).window) && findWindow(event.xcrossing.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if((*cursor.c.current).option & MappedContainerOption){
					if(inputMethod & EnterInputMethod){
						const EnterInputException *exception;
						const Command enterCommand = command;
						command = NoCommand;
						switch(managementMode){
							case FloatingManagementMode:{
								if((*cursor.c.current).option & InGridContainerOption){
									exception = &inGridEnterInputException;
									break;
								}
								exception = &floatingEnterInputException;
								break;
							}
							case GriddingManagementMode:{
								exception = &griddingEnterInputException;
								break;
							}
							default:{
								exception = &tilingEnterInputException;
								break;
							}
						}
						switch(enterCommand){
							case ExecuteCommand:{
								if(*exception & ExecuteEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case FloatingModeCommand:
							case GriddingModeCommand:
							case TilingModeCommand:{
								if(*exception & ChangeManagementModeEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case EnlargeGridXCommand:
							case EnlargeGridYCommand:
							case EnlargeGridEitherCommand:
							case EnlargeGridBothCommand:
							case ShrinkGridXCommand:
							case ShrinkGridYCommand:
							case ShrinkGridEitherCommand:
							case ShrinkGridBothCommand:{
								if(*exception & ResizeGridEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case ToggleGapsCommand:{
								if(*exception & ToggleGapsEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case RecascadeCommand:{
								if(*exception & RecascadeEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case AttachCommand:{
								if(*exception & AttachEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case SwapNextMonitorCommand:
							case SwapPreviousMonitorCommand:
							case SwapAboveMonitorCommand:
							case SwapBelowMonitorCommand:
							case SwapLeftMonitorCommand:
							case SwapRightMonitorCommand:{
								if(*exception & SwapMonitorsEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case RevolveMonitorsNextCommand:
							case RevolveMonitorsPreviousCommand:
							case RevolveMonitorsHorizontallyCommand:
							case RevolveMonitorsVerticallyCommand:{
								if(*exception & RevolveMonitorsEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case CancelMoveResizeCommand:{
								if(*exception & CancelMoveResizeEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case MoveTopCommand:
							case MoveBottomCommand:
							case MoveLeftCommand:
							case MoveRightCommand:
							case MoveTopLeftCommand:
							case MoveTopRightCommand:
							case MoveBottomLeftCommand:
							case MoveBottomRightCommand:
							case MoveCenterCommand:
							case MoveFullCommand:{
								if(*exception & MoveToEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case MoveNextMonitorCommand:
							case MovePreviousMonitorCommand:
							case MoveAboveMonitorCommand:
							case MoveBelowMonitorCommand:
							case MoveLeftMonitorCommand:
							case MoveRightMonitorCommand:{
								if(*exception & MoveMonitorEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case AddToGridCommand:
							case RemoveFromGridCommand:
							case ToggleAddRemoveGridCommand:{
								if(*exception & ToggleAddRemoveGridEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case MoveUpGridCommand:
							case MoveDownGridCommand:
							case MoveLeftGridCommand:
							case MoveRightGridCommand:{
								if(*exception & MoveGridEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case ExtendUpCommand:
							case ExtendDownCommand:
							case ExtendLeftCommand:
							case ExtendRightCommand:
							case ExtendUpLeftCommand:
							case ExtendUpRightCommand:
							case ExtendDownLeftCommand:
							case ExtendDownRightCommand:{
								if(*exception & ExtendEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case ShrinkUpCommand:
							case ShrinkDownCommand:
							case ShrinkLeftCommand:
							case ShrinkRightCommand:
							case ShrinkUpLeftCommand:
							case ShrinkUpRightCommand:
							case ShrinkDownLeftCommand:
							case ShrinkDownRightCommand:{
								if(*exception & ShrinkEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							case FullscreenCommand:
							case BigscreenCommand:{
								if(*exception & MaximizeEnterInputException){
									goto eventLoop;
								}
								goto changeFocusedWindowBackground0;
							}
							default:{
								goto changeFocusedWindowBackground0;
							}
						}
					}
					changeFocusedWindowBackground0:{
						const ARGB *c = &color.containerBackground.floating;
						if(focused){
							changeFocusedWindowBackground1:{
								if((*focused).option & MaximizedContainerOption){
									if(option(MaximizedUseFocusedWindowColor)){
										findWindow((*focused).window, &(*cursor.mc.start).window, sizeof(MaximizedContainer), monitorAmount, &current);
										if((*(cursor.mc.start + current)).shouldChangeProperty){
											c += 4;
											goto setFocusedWindowBackground;
										}
										c += 5;
										goto setFocusedWindowBackground;
									}
								}else{
									switch(managementMode){
										case FloatingManagementMode:{
											if((*focused).option & InGridContainerOption){
												if(option(InGridUseFocusedWindowColor)){
													c += 3;
													goto setFocusedWindowBackground;
												}
												break;
											}
											if(option(FloatingUseFocusedWindowColor)){
												goto setFocusedWindowBackground;
											}
											break;
										}
										case GriddingManagementMode:{
											if(option(GriddingUseFocusedWindowColor)){
												c += 1;
												goto setFocusedWindowBackground;
											}
											break;
										}
										default:{
											if(option(TilingUseFocusedWindowColor)){
												c += 2;
												setFocusedWindowBackground:{
													XSetWindowBackground(display, (*focused).window, *c);
													XClearArea(display, (*focused).window, 0, 0, 0, 0, False);
												}
											}
											break;
										}
									}
								}
							}
						}
						if(focused != cursor.c.current){
							focused = cursor.c.current;
							c = &color.focusedContainerBackground.floating;
							goto changeFocusedWindowBackground1;
						}
					}
					XRaiseWindow(display, event.xcrossing.window);
					XSetInputFocus(display, (*focused).subwindow, RevertToPointerRoot, CurrentTime);
				}
			}
		}
		goto eventLoop;
		destroyNotifyEvent:{
			if(findWindow(event.xdestroywindow.window, &(*cursor.c.start).subwindow, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				event.xany.window = (*cursor.c.current).window;
				if((*cursor.c.current).option & MappedContainerOption){
					goto unmapWindow;
				}
				destroyWindow:{
					XDestroyWindow(display, event.xany.window);
					if((*cursor.c.current).option & MaximizedContainerOption){
						findWindow(event.xany.window, &(*cursor.mc.start).window, sizeof(MaximizedContainer), monitorAmount, &current);
						cursor.mc.current = cursor.mc.start + current;
						(*cursor.mc.current).window = None;
						(*cursor.mc.current).subwindow = None;
					}
					{
						const Container c = *(cursor.c.start + --containerAmount);
						*(cursor.c.start + containerAmount) = *cursor.c.current;
						*cursor.c.current = c;
					}
					if(!(containerData = realloc(containerData, monitorAmount * sizeof(MaximizedContainer) + containerAmount * sizeof(Container)))){
						printError("ram is full, could not restore containers");
						mode = ExitMode;
						goto eventLoopExit;
					}
					genericUnsignedInteger = focused - cursor.c.start;
					cursor.mc.start = (MaximizedContainer *)containerData;
					cursor.mc.wall = cursor.mc.start + monitorAmount;
					cursor.c.start = (Container *)cursor.mc.wall;
					cursor.c.wall = cursor.c.start + containerAmount;
					if(focused){
						focused = cursor.c.start + genericUnsignedInteger;
					}
				}
			}
		}
		goto eventLoop;
		unmapNotifyEvent:{
			if(findWindow(event.xunmap.window, &(*cursor.c.start).subwindow, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				unmapWindow:{
					XUnmapWindow(display, (*cursor.c.current).window);
					XSetInputFocus(display, rootWindow, RevertToPointerRoot, CurrentTime);
					if(managementMode(Tiling)){
						removeTilingWindow();
					}
					if(cursor.c.current == focused){
						focused = NULL;
					}
					(*cursor.c.current).option ^= MappedContainerOption;
				}
				if(event.type == DestroyNotify){
					goto destroyWindow;
				}
			}
		}
		goto eventLoop;
		mapRequestEvent:{
			if(pointerInfo(Map)){
				current = getCurrentPointerMonitor(cursor.m.start, monitorAmount);
			}else{
				current = getCurrentWindowMonitor(event.xmaprequest.window, cursor.m.start, monitorAmount);
			}
			mapWindow:{
				if(!(containerData = realloc(containerData, monitorAmount * sizeof(MaximizedContainer) + (containerAmount + 1) * sizeof(Container)))){
					printError("ram is full, could not restore containers");
					mode = ExitMode;
					goto eventLoopExit;
				}
				genericUnsignedInteger = focused - cursor.c.start;
				cursor.mc.start = (MaximizedContainer *)containerData;
				cursor.mc.wall = cursor.mc.start + monitorAmount;
				cursor.c.start = (Container *)cursor.mc.wall;
				cursor.c.wall = cursor.c.start + containerAmount;
				if(focused){
					focused = cursor.c.start + genericUnsignedInteger;
				}
				cursor.c.current = cursor.c.start + containerAmount;
				cursor.m.current = cursor.m.start + current;
				event.xmaprequest.parent = XCreateWindow(display, rootWindow, 0, 0, 1, 1, 0, visualInfo.depth, InputOutput, visualInfo.visual, CWBorderPixel | CWColormap, &createWindowAttributes);
				if(shortcutAmount){
					cursor.s.current = cursor.s.start;
					grabContainerKey:{
						if((*cursor.s.current).command > RootCommandCeiling && (*cursor.s.current).keycode != AnyKey){
							XGrabKey(display, (*cursor.s.current).keycode, (*cursor.s.current).masks, event.xmaprequest.parent, True, GrabModeAsync, GrabModeAsync);
						}
						if(++cursor.s.current < cursor.s.wall){
							goto grabContainerKey;
						}
					}
				}
				if(buttonAmount){
					cursor.b.current = cursor.b.start;
					grabContainerButton:{
						if((*cursor.b.current).command > RootCommandCeiling && (*cursor.b.current).button != AnyButton){
							XGrabButton(display, (*cursor.b.current).button, (*cursor.b.current).masks, event.xmaprequest.parent, True, NoEventMask, GrabModeAsync, GrabModeAsync, None, None);
						}
						if(++cursor.b.current < cursor.b.wall){
							goto grabContainerButton;
						}
					}
				}
				XReparentWindow(display, event.xmaprequest.window, event.xmaprequest.parent, border.left, border.up);
				XMapWindow(display, event.xmaprequest.window);
				{
					Atom *property = XListProperties(display, event.xmaprequest.window, &genericInteger);
					if(property){
						if(genericInteger){
							const long int size = sizeof(Atom);
							const Atom *const propertyWall = property + genericInteger;
							Atom type;
							int format;
							unsigned long int propertyAmount;
							unsigned long int bytesAfter;
							unsigned char *data;
							changeProperty:{
								if(XGetWindowProperty(display, event.xmaprequest.window, *property, 0, size, False, AnyPropertyType, &type, &format, &propertyAmount, &bytesAfter, &data) == Success && data){
									XChangeProperty(display, event.xmaprequest.parent, *property, type, format, PropModeReplace, data, propertyAmount);
									XFree(data);
								}
								if(++property < propertyWall){
									goto changeProperty;
								}
								property -= genericInteger;
							}
						}
						XFree(property);
					}
				}
				(*cursor.c.current).option = NoContainerOptions;
				switch(managementMode){
					case FloatingManagementMode:{
						XSetWindowBorderWidth(display, event.xmaprequest.parent, shadow);
						XSetWindowBackground(display, event.xmaprequest.parent, color.containerBackground.floating);
						if(option(FloatingFollowGrid)){
							width = (*cursor.m.current).width / gridWidth;
							height = (*cursor.m.current).height / gridHeight;
						}else{
							width = (*cursor.m.current).width / 2;
							height = (*cursor.m.current).height / 2;
						}
						{
							Window lastCreatedWindow;
							if(containerAmount){
								lastCreatedWindow = (*(--cursor.c.current)).window;
							}else{
								lastCreatedWindow = None;
							}
							if(cascade.mode == SimpleCascadeMode){
								if(lastCreatedWindow && !((*cursor.c.current).option & InGridContainerOption) && !((*cursor.c.current).option & MaximizedContainerOption)){
									if(getCurrentWindowMonitor(lastCreatedWindow, cursor.m.start, monitorAmount) != current){
										goto uncascadedPosition;
									}
									XGetGeometry(display, lastCreatedWindow, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
									XMoveResizeWindow(display, event.xmaprequest.parent, x + cascade.offsetX, y + cascade.offsetY, width, height);
								}else{
									goto uncascadedPosition;
								}
							}else{
								uncascadedPosition:{
									x = (*cursor.m.current).x + ((*cursor.m.current).width - width) / 2 - shadow;
									y = (*cursor.m.current).y + ((*cursor.m.current).height - height) / 2 - shadow;
									if(cascade.mode == SmartCascadeMode && lastCreatedWindow){
										const int xCopy = x;
										const int yCopy = y;
										Container *start;
										int x1;
										int y1;
										unsigned int width1;
										unsigned int height1;
										int offsetX = cascade.offsetX;
										int offsetY = cascade.offsetY;
										bool hasSwitchedDirections = 0;
										smartCascade:{
											start = cursor.c.start;
											cursor.c.current = cursor.c.start;
											cascadeToDirection:{
												XGetGeometry(display, (*cursor.c.current).window, &genericWindow, &x1, &y1, &width1, &height1, &genericBorder, &genericDepth);
												if(x1 == x && y1 == y){
													x += offsetX;
													y += offsetY;
													if(cursor.c.current == start){
														++start;
													}
													cursor.c.current = start;
												}else{
													++cursor.c.current;
												}
												if(cursor.c.current < cursor.c.wall){
													goto cascadeToDirection;
												}
											}
											if(!hasSwitchedDirections && (x >= (*cursor.m.current).x + (*cursor.m.current).width || y >= (*cursor.m.current).y + (*cursor.m.current).height)){
												x = xCopy;
												offsetX = -offsetX;
												y = yCopy;
												offsetY = -offsetY;
												hasSwitchedDirections = 1;
												goto smartCascade;
											}
										}
									}
									XMoveResizeWindow(display, event.xmaprequest.parent, x, y, width, height);
								}
							}
						}
						XResizeWindow(display, event.xmaprequest.window, width - border.x, height - border.y);
						XSelectInput(display, event.xmaprequest.parent, ButtonReleaseMask | EnterWindowMask | SubstructureRedirectMask);
						XSelectInput(display, event.xmaprequest.window, ButtonReleaseMask | StructureNotifyMask);
						break;
					}
					case GriddingManagementMode:{
						XSetWindowBackground(display, event.xmaprequest.parent, color.containerBackground.gridding);
						switch(defaultGridPosition){
							case TopLeftDefaultGridPosition:{
								(*cursor.c.current).gridX = 0;
								(*cursor.c.current).gridY = 0;
								break;
							}
							case TopRightDefaultGridPosition:{
								(*cursor.c.current).gridX = gridWidth - 1;
								(*cursor.c.current).gridY = 0;
								break;
							}
							case BottomLeftDefaultGridPosition:{
								(*cursor.c.current).gridX = 0;
								(*cursor.c.current).gridY = gridHeight - 1;
								break;
							}
							case BottomRightDefaultGridPosition:{
								(*cursor.c.current).gridX = gridWidth - 1;
								(*cursor.c.current).gridY = gridHeight - 1;
								break;
							}
							default:{
								(*cursor.c.current).gridX = gridWidth / 2;
								(*cursor.c.current).gridY = gridHeight / 2;
								break;
							}
						}
						getGridSlotData((*cursor.m.current).width, (*cursor.m.current).height, (*cursor.c.current).gridX, (*cursor.c.current).gridY, gridWidth, gridHeight, &x, &y, &width, &height);
						(*cursor.c.current).gridWidth = 1;
						(*cursor.c.current).gridHeight = 1;
						(*cursor.c.current).option |= InGridContainerOption;
						XMoveResizeWindow(display, event.xmaprequest.parent, (*cursor.m.current).x + x, (*cursor.m.current).y + y, width, height);
						XResizeWindow(display, event.xmaprequest.window, width - border.x, height - border.y);
						XSelectInput(display, event.xmaprequest.parent, EnterWindowMask | SubstructureRedirectMask);
						XSelectInput(display, event.xmaprequest.window, StructureNotifyMask);
						break;
					}
					default:{
						XSetWindowBackground(display, event.xmaprequest.parent, color.containerBackground.tiling);
						ADDTILINGWINDOW;
						XSelectInput(display, event.xmaprequest.parent, EnterWindowMask | SubstructureRedirectMask);
						XSelectInput(display, event.xmaprequest.window, StructureNotifyMask);
						break;
					}
				}
				++containerAmount;
				(*cursor.c.current).window = event.xmaprequest.parent;
				(*cursor.c.current).subwindow = event.xmaprequest.window;
				(*cursor.c.current).option |= MappedContainerOption;
				++cursor.c.wall;
				XMapRaised(display, event.xmaprequest.parent);
				if(motionContainer.action){
					XMapRaised(display, motionContainer.window);
					XMapRaised(display, motionContainer.glass);
					goto eventLoop;
				}
				event.xcrossing.window = event.xmaprequest.window;
				goto changeFocusedWindowBackground0;
			}
		}
		configureRequestEvent:{
			if(XPending(display)){
				XPeekEvent(display, &e);
				if(e.type == ConfigureRequest){
					goto eventLoop;
				}
			}
			if(findWindow(event.xconfigurerequest.window, &(*cursor.c.start).subwindow, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if((*cursor.c.current).option & MaximizedContainerOption){
					goto eventLoop;
				}
				XGetGeometry(display, (*cursor.c.current).window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
				if(!managementMode(Tiling)){
					if(canConfigurePosition){
						if(!((*cursor.c.current).option & InGridContainerOption)){
							if(event.xconfigurerequest.value_mask & CWX){
								x = event.xconfigurerequest.x - border.left;
								if(event.xconfigurerequest.value_mask & CWY){
									y = event.xconfigurerequest.y - border.up;
								}
								goto configureWindow;
							}
							if(event.xconfigurerequest.value_mask & CWY){
								y = event.xconfigurerequest.y - border.up;
								configureWindow:{
									XMoveWindow(display, (*cursor.c.current).window, x, y);
								}
							}
							canConfigurePosition = 0;
						}
					}else{
						if(!XPending(display)){
							canConfigurePosition = 1;
						}
					}
				}
				{
					XWindowChanges windowChanges;
					unsigned int masks = None;
					if(event.xconfigurerequest.value_mask & CWWidth){
						windowChanges.width = event.xconfigurerequest.width;
						masks |= CWWidth;
					}
					if(event.xconfigurerequest.value_mask & CWHeight){
						windowChanges.height = event.xconfigurerequest.height;
						masks |= CWHeight;
					}
					if(event.xconfigurerequest.value_mask & CWBorderWidth){
						windowChanges.border_width = event.xconfigurerequest.border_width;
						width -= event.xconfigurerequest.border_width;
						height -= event.xconfigurerequest.border_width;
						masks |= CWBorderWidth;
					}
					if(masks){
						XConfigureWindow(display, event.xconfigurerequest.window, masks, &windowChanges);
						XResizeWindow(display, event.xconfigurerequest.window, width - border.x, height - border.y);
					}
				}
				goto eventLoop;
			}
			cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
			if(event.xconfigurerequest.value_mask){
				XWindowChanges windowChanges;
				unsigned int masks = None;
				if(event.xconfigurerequest.value_mask & CWX){
					windowChanges.x = event.xconfigurerequest.x;
					masks |= CWX;
				}
				if(event.xconfigurerequest.value_mask & CWY){
					windowChanges.y = event.xconfigurerequest.y;
					masks |= CWY;
				}
				if(event.xconfigurerequest.value_mask & CWWidth){
					windowChanges.width = event.xconfigurerequest.width;
					masks |= CWWidth;
				}
				if(event.xconfigurerequest.value_mask & CWHeight){
					windowChanges.height = event.xconfigurerequest.height;
					masks |= CWHeight;
				}
				if(event.xconfigurerequest.value_mask & CWBorderWidth){
					windowChanges.border_width = event.xconfigurerequest.border_width;
					windowChanges.width -= windowChanges.border_width;
					windowChanges.height -= windowChanges.border_width;
					masks |= CWBorderWidth;
				}
				if(masks){
					XConfigureWindow(display, event.xconfigurerequest.window, masks, &windowChanges);
				}
			}
			XMoveResizeWindow(display, event.xconfigurerequest.window, (*cursor.m.current).x, (*cursor.m.current).y, (*cursor.m.current).width / gridWidth - border.x, (*cursor.m.current).height / gridHeight - border.y);
		}
		goto eventLoop;
		clientMessageEvent:{
			if(event.xclient.message_type == _NET.WM.STATE.this){
				if(findWindow(event.xclient.window, &(*cursor.c.start).subwindow, sizeof(Container), containerAmount, &current)){
					Atom data0;
					Atom data1;
					switch(event.xclient.format){
						case 8:{
							data0 = *event.xclient.data.b;
							data1 = *(event.xclient.data.b + 1);
							break;
						}
						case 16:{
							data0 = *event.xclient.data.s;
							data1 = *(event.xclient.data.s + 1);
							break;
						}
						default:{
							data0 = *event.xclient.data.l;
							data1 = *(event.xclient.data.l + 1);
							break;
						}
					}
					cursor.c.current = cursor.c.start + current;
					event.xclient.window = (*cursor.c.current).window;
					switch(data0){
						case _NET_WM_STATE_REMOVE:{
							if(data1 == _NET.WM.STATE.FULLSCREEN){
								unmaximizeClient:{
									unmaximizeContainer(focused, monitorAmount, border.x, border.y, _NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, cursor.c.current, cursor.mc.start);
								}
							}
							goto eventLoop;
						}
						case _NET_WM_STATE_ADD:{
							if(data1 == _NET.WM.STATE.FULLSCREEN){
								maximizeClient:{
									if(pointerInfo(ClientMessage)){
										current = getCurrentPointerMonitor(cursor.m.start, monitorAmount);
									}else{
										current = getCurrentWindowMonitor(event.xclient.window, cursor.m.start, monitorAmount);
									}
									if((*cursor.c.current).option & MaximizedContainerOption){
										unmaximizeContainer(focused, monitorAmount, border.x, border.y, _NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, cursor.c.current, cursor.mc.start);
									}
									maximizeContainer(FullscreenCommand, cursor.m.start + current, managementMode, &color, _NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, border.x, border.y, focused, cursor.c.current, cursor.mc.start + current);
								}
							}
							goto eventLoop;
						}
						case _NET_WM_STATE_TOGGLE:{
							if(data1 == _NET.WM.STATE.FULLSCREEN){
								if((*cursor.c.current).option & MaximizedContainerOption){
									goto unmaximizeClient;
								}
								goto maximizeClient;
							}
							goto eventLoop;
						}
						default:{
							goto eventLoop;
						}
					}
				}
			}
		}
		goto eventLoop;
		screenChangeNotifyEvent:{
			if(XPending(display)){
				XPeekEvent(display, &e);
				if(e.type == RRScreenChangeNotify + rrEventBase){
					goto eventLoop;
				}
			}
			{
				XRRMonitorInfo *const monitor = XRRGetMonitors(display, rootWindow, True, &genericInteger);
				if(!monitor){
					printError("could not update screen");
				}
				{
					genericUnsignedInteger = genericInteger;
					if(genericUnsignedInteger != monitorAmount){
						/*void *const old = data;
						if((data = malloc(shortcutAmount * sizeof(Shortcut) + buttonAmount * sizeof(Button) + executeAmount * sizeof(Execute) + amount * (sizeof(XRRMonitorInfo) + sizeof(Window))))){
							const Shortcut *const shortcutStart = cursor.s.start;
							const Shortcut *const shortcutWall = cursor.s.wall;
							const Button *const buttonStart = cursor.b.start;
							const Button *const buttonWall = cursor.b.wall;
							const Execute *const executeStart = cursor.e.start;
							const Execute *const executeWall = cursor.e.wall;
							const XRRMonitorInfo *const monitorStart = cursor.m.start;
							const XRRMonitorInfo *const monitorWall = cursor.m.wall;
							const Window *const gridStart = cursor.g.start;
							const Window *const gridWall = cursor.g.wall;



							cursor.s.start = (Shortcut *)data;
							cursor.s.wall = cursor.s.start + shortcutAmount;
							cursor.b.start = (Button *)cursor.s.wall;
							cursor.b.wall = cursor.b.start + buttonAmount;
							cursor.e.start = (Execute *)cursor.b.wall;
							cursor.e.wall = cursor.e.start + executeAmount;



							cursor.m.start = (XRRMonitorInfo *)cursor.e.wall;
							cursor.m.wall = cursor.m.start + amount;
							cursor.g.start = (Window *)cursor.m.wall;
							cursor.g.wall = cursor.g.start + amount;



							{
								unsigned int i;
								unsigned int ii;
								unsigned int iii;
								unsigned int fulfilled = 0;
								for(i = 0; i < amount; ++i){
									cursor.m.start[i].name = None;
									for(ii = 0; ii < monitorAmount; ++ii){
										if(sameMonitor(monitorStart[ii], monitor[i])){
											cursor.m.start[i] = monitor[i];
											++fulfilled;
											break;
										}
									}
								}
								if(fulfilled < amount){
									for(i = 0; i < amount; ++i){
										if(!cursor.m.start[i].name){



										}
									}
								}
							}



							free(old);
						}else{
							printError("ram is full, could not store new general data");
							XRRFreeMonitors(monitor);
							goto eventLoop;
						}*/
					}else{
						/**/









					}
					monitorAmount = genericUnsignedInteger;
				}
				XRRUpdateConfiguration(&event);
				displayWidth = XDisplayWidth(display, XDefaultScreen(display));
				displayHeight = XDisplayHeight(display, XDefaultScreen(display));
				{
					cursor.m.current = cursor.m.start;
					reSetupMonitorProperties:{
						width = (*cursor.m.current).width / 3;
						height = (*cursor.m.current).height / 3;
						if(gridMaxWidth > width){
							gridMaxWidth = width;
						}
						if(gridMaxHeight > height){
							gridMaxHeight = height;
						}
						if(++cursor.m.current < cursor.m.wall){
							goto reSetupMonitorProperties;
						}
					}
				}
				if(gridMinWidth > gridMaxWidth){
					gridMinWidth = gridMaxWidth;
				}
				if(gridMinHeight > gridMaxHeight){
					gridMinHeight = gridMaxHeight;
				}
				if(gridOption(Exists)){
					cursor.g.current = cursor.g.start;
					destroyGridSubwindows:{
						XDestroySubwindows(display, *cursor.g.current);
						if(++cursor.g.current < cursor.g.wall){
							goto destroyGridSubwindows;
						}
					}
					createGrid(cursor.m.start, monitorAmount, gridWidth, gridHeight, color.gridSubwindowBorder, color.gridSubwindowBackground, cursor.g.start);
					if(gridOption(Mapped)){
						cursor.g.current = cursor.g.start;
						lowerMapGridWindow0:{
							XLowerWindow(display, *cursor.g.current);
							XMapWindow(display, *cursor.g.current);
							if(++cursor.g.current < cursor.g.wall){
								goto lowerMapGridWindow0;
							}
						}
					}
				}
				XRRFreeMonitors(monitor);
			}









			/*if(amount == monitorAmount){
				cursor.m.current = cursor.m.start;
				for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){
					*cursor.m.current = monitors[currentMonitor];
					XMoveResizeWindow(display, *(cursor.g.start + currentMonitor), (*cursor.m.current).x, (*cursor.m.current).y, (*cursor.m.current).width, (*cursor.m.current).height);
					++cursor.m.current;
				}
				x = 0;
				y = 0;
				for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){
					currentMonitor = getCurrentWindowMonitor(container[currentContainer].window, cursor.m.start, monitorAmount);
					if(managementMode(Tiling)){









					}else if(container[currentContainer].option & InGridContainerOption){
						cursor.c.current = cursor.c.start + currentContainer;
						cursor.m.current = cursor.m.start + currentMonitor;
						moveContainerToGridPosition(cursor.c.current, cursor.m.current, gridWidth, gridHeight, border.x, border.y);
					}else{









					}
				}
			}*/









		}
		goto eventLoop;
		findCommand:{
			switch(command){
				case ExecuteCommand:{
					goto executeCommand;
				}
				case FloatingModeCommand:{
					goto floatingModeCommand;
				}
				case GriddingModeCommand:{
					goto griddingModeCommand;
				}
				case TilingModeCommand:{
					goto tilingModeCommand;
				}
				case ShowGridCommand:
				case HideGridCommand:
				case ToggleGridVisibilityCommand:{
					goto showHideToggleGridCommand;
				}
				case EnlargeGridXCommand:{
					goto enlargeGridXCommand;
				}
				case EnlargeGridYCommand:{
					goto enlargeGridYCommand;
				}
				case EnlargeGridEitherCommand:{
					goto enlargeGridEitherCommand;
				}
				case EnlargeGridBothCommand:{
					goto enlargeGridBothCommand;
				}
				case ShrinkGridXCommand:{
					goto shrinkGridXCommand;
				}
				case ShrinkGridYCommand:{
					goto shrinkGridYCommand;
				}
				case ShrinkGridEitherCommand:{
					goto shrinkGridEitherCommand;
				}
				case ShrinkGridBothCommand:{
					goto shrinkGridBothCommand;
				}
				case ToggleGapsCommand:{
					goto toggleGapsCommand;
				}
				case RecascadeCommand:{
					goto recascadeCommand;
				}
				case AttachCommand:{
					goto attachCommand;
				}
				case SwapNextMonitorCommand:
				case SwapPreviousMonitorCommand:
				case SwapAboveMonitorCommand:
				case SwapBelowMonitorCommand:
				case SwapLeftMonitorCommand:
				case SwapRightMonitorCommand:{
					goto swapMonitorsCommand;
				}
				case RevolveMonitorsNextCommand:
				case RevolveMonitorsPreviousCommand:
				case RevolveMonitorsHorizontallyCommand:
				case RevolveMonitorsVerticallyCommand:{
					goto revolveMonitorsCommand;
				}
				case RestartCommand:{
					goto eventLoopExit;
				}
				case ExitCommand:{
					mode = ExitMode;
					goto eventLoopExit;
				}
				case MoveCommand:
				case ResizeCommand:
				case MoveResizeCommand:{
					goto moveResizeCommand;
				}
				case CancelMoveResizeCommand:{
					goto cancelMoveResizeCommand;
				}
				case MoveTopCommand:
				case MoveBottomCommand:
				case MoveLeftCommand:
				case MoveRightCommand:
				case MoveTopLeftCommand:
				case MoveTopRightCommand:
				case MoveBottomLeftCommand:
				case MoveBottomRightCommand:{
					goto moveToCommand;
				}
				case MoveCenterCommand:
				case MoveFullCommand:{
					goto moveCenterFull;
				}
				case MoveNextMonitorCommand:
				case MovePreviousMonitorCommand:
				case MoveAboveMonitorCommand:
				case MoveBelowMonitorCommand:
				case MoveLeftMonitorCommand:
				case MoveRightMonitorCommand:{
					goto moveMonitorCommand;
				}
				case AddToGridCommand:
				case RemoveFromGridCommand:
				case ToggleAddRemoveGridCommand:{
					goto addRemoveToggleGridCommand;
				}
				case MoveUpGridCommand:
				case MoveDownGridCommand:
				case MoveLeftGridCommand:
				case MoveRightGridCommand:{
					goto moveInsideGridCommand;
				}
				case ExtendUpCommand:
				case ExtendDownCommand:
				case ExtendLeftCommand:
				case ExtendRightCommand:
				case ExtendUpLeftCommand:
				case ExtendUpRightCommand:
				case ExtendDownLeftCommand:
				case ExtendDownRightCommand:{
					goto extendCommand;
				}
				case ShrinkUpCommand:
				case ShrinkDownCommand:
				case ShrinkLeftCommand:
				case ShrinkRightCommand:
				case ShrinkUpLeftCommand:
				case ShrinkUpRightCommand:
				case ShrinkDownLeftCommand:
				case ShrinkDownRightCommand:{
					goto shrinkCommand;
				}
				case FullscreenCommand:
				case BigscreenCommand:{
					goto fullscreenBigscreenCommand;
				}
				case DetachCommand:{
					goto detachCommand;
				}
				case CloseCommand:{
					goto closeCommand;
				}
				default:{
					goto killCommand;
				}
			}
		}
		executeCommand:{
			if(executeAmount){
				cursor.e.current = cursor.e.start;
				findExecuteCommand:{
					if((*cursor.e.current).keyButton == event.xkey.keycode && (*cursor.e.current).masks == event.xkey.state){
						system((*cursor.e.current).command);
						goto eventLoop;
					}
					if(++cursor.e.current < cursor.e.wall){
						goto findExecuteCommand;
					}
				}
			}
		}
		goto eventLoop;
		floatingModeCommand:{
			if(!managementMode(Floating)){
				if(containerAmount){
					unmapAllWindows(cursor.c.start, cursor.c.wall);
					unmaximizeAllContainers(_NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, monitorAmount, cursor.c.wall, cursor.c.start, cursor.mc.start);
					{
						const bool portWindowsFromGridding = managementMode(Gridding) && option(FloatingPortWindowsFromGridding);
						const InputMasks windowMasks = ButtonReleaseMask | EnterWindowMask | SubstructureRedirectMask;
						const InputMasks subwindowMasks = ButtonReleaseMask | StructureNotifyMask;
						cursor.c.current = cursor.c.start;
						editContainerFloating:{
							genericWindow = (*cursor.c.current).window;
							if(portWindowsFromGridding){
								XSetWindowBackground(display, genericWindow, color.containerBackground.inGrid);
							}else{
								XSelectInput(display, genericWindow, windowMasks);
								XSelectInput(display, (*cursor.c.current).subwindow, subwindowMasks);
								XSetWindowBorderWidth(display, genericWindow, shadow);
								XSetWindowBackground(display, genericWindow, color.containerBackground.floating);
								if((*cursor.c.current).option & InGridContainerOption){
									(*cursor.c.current).option ^= InGridContainerOption;
								}
							}
							if(++cursor.c.current < cursor.c.wall){
								goto editContainerFloating;
							}
						}
					}
					{
						const Options followGrid = option(FloatingFollowGrid);
						unsigned int subwindowWidth;
						unsigned int subwindowHeight;
						int offsetX;
						int offsetY;
						int monitorRightBorder;
						int monitorBottomBorder;
						int xCopy;
						int yCopy;
						if(option(FloatingAllowCascadeToFloating)){
							offsetX = cascade.offsetX;
							offsetY = cascade.offsetY;
						}else{
							offsetX = 0;
							offsetY = 0;
						}
						if(pointerInfo(ChangeToFloating)){
							cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
							if(followGrid){
								width = (*cursor.m.current).width / gridWidth;
								height = (*cursor.m.current).height / gridHeight;
							}else{
								width = (*cursor.m.current).width / floatingWindowDivisor;
								height = (*cursor.m.current).height / floatingWindowDivisor;
							}
							cursor.c.current = cursor.c.start;
							x = (*cursor.m.current).x + ((*cursor.m.current).width - width) / 2 - shadow;
							y = (*cursor.m.current).y + ((*cursor.m.current).height - height) / 2 - shadow;
							subwindowWidth = width - border.x;
							subwindowHeight = height - border.y;
							monitorRightBorder = (*cursor.m.current).x + (*cursor.m.current).width;
							monitorBottomBorder = (*cursor.m.current).y + (*cursor.m.current).height;
							xCopy = x;
							yCopy = y;
							portToFloating0:{
								if(!((*cursor.c.current).option & InGridContainerOption)){
									XMoveResizeWindow(display, (*cursor.c.current).window, x, y, width, height);
									XResizeWindow(display, (*cursor.c.current).subwindow, subwindowWidth, subwindowHeight);
									x += offsetX;
									y += offsetY;
									if(x >= monitorRightBorder || y >= monitorBottomBorder){
										x = xCopy - offsetX;
										y = yCopy - offsetY;
										offsetX = -offsetX;
										offsetY = -offsetY;
									}
								}
								if(++cursor.m.current < cursor.m.wall){
									goto portToFloating0;
								}
							}
						}else{
							cursor.m.current = cursor.m.start;
							current = 0;
							cascadeToFloatingPerMonitor:{
								if(followGrid){
									width = (*cursor.m.current).width / gridWidth;
									height = (*cursor.m.current).height / gridHeight;
								}else{
									width = (*cursor.m.current).width / floatingWindowDivisor;
									height = (*cursor.m.current).height / floatingWindowDivisor;
								}
								cursor.c.current = cursor.c.start;
								x = (*cursor.m.current).x + ((*cursor.m.current).width - width) / 2;
								y = (*cursor.m.current).y + ((*cursor.m.current).height - height) / 2;
								subwindowWidth = width - border.x;
								subwindowHeight = height - border.y;
								monitorRightBorder = (*cursor.m.current).x + (*cursor.m.current).width;
								monitorBottomBorder = (*cursor.m.current).y + (*cursor.m.current).height;
								xCopy = x;
								yCopy = y;
								portToFloating1:{
									if(!((*cursor.c.current).option & InGridContainerOption)){
										if(getCurrentWindowMonitor((*cursor.c.current).window, cursor.m.start, monitorAmount) == current){
											XMoveResizeWindow(display, (*cursor.c.current).window, x, y, width, height);
											XResizeWindow(display, (*cursor.c.current).subwindow, subwindowWidth, subwindowHeight);
											x += offsetX;
											y += offsetY;
											if(x >= monitorRightBorder || y >= monitorBottomBorder){
												x = xCopy - offsetX;
												y = yCopy - offsetY;
												offsetX = -offsetX;
												offsetY = -offsetY;
											}
										}
									}
									if(++cursor.c.current < cursor.c.wall){
										goto portToFloating1;
									}
								}
								if(++cursor.m.current < cursor.m.wall){
									++current;
									goto cascadeToFloatingPerMonitor;
								}
							}
						}
					}
					if(focused){
						if((*focused).option & InGridContainerOption){
							if(option(InGridUseFocusedWindowColor)){
								XSetWindowBackground(display, (*focused).window, color.focusedContainerBackground.inGrid);
							}
						}else{
							if(option(FloatingUseFocusedWindowColor)){
								XSetWindowBackground(display, (*focused).window, color.focusedContainerBackground.floating);
							}
						}
					}
					mapAllWindows(cursor.c.start, cursor.c.wall);
				}
				managementMode = FloatingManagementMode;
			}
		}
		goto eventLoop;
		griddingModeCommand:{
			if(!managementMode(Gridding) && containerAmount){
				const PointerInfo windowPointerInfo = pointerInfo(ChangeToGridding);
				unsigned int amount;
				unsigned int *gridX;
				unsigned int *gridY;
				if(windowPointerInfo){
					cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
					amount = 1;
				}else{
					amount = monitorAmount;
				}
				if(!(gridX = malloc(2 * amount * sizeof(unsigned int)))){
					printError("ram is full, could not change to gridding mode");
					goto eventLoop;
				}
				gridY = gridX + amount;
				unmapAllWindows(cursor.c.start, cursor.c.wall);
				unmaximizeAllContainers(_NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, monitorAmount, cursor.c.wall, cursor.c.start, cursor.mc.start);
				{
					const InputMasks windowMasks = EnterWindowMask | SubstructureRedirectMask;
					const Options portWindowsFromFloating = option(GriddingPortWindowsFromFloating);
					const Options evenlyDistributeWindows = option(GriddingEvenlyDistributeWindows);
					unsigned int gX = 0;
					unsigned int gY = 0;
					if(!evenlyDistributeWindows){
						switch(defaultGridPosition){
							case TopRightDefaultGridPosition:{
								gX = gridWidth - 1;
								break;
							}
							case BottomLeftDefaultGridPosition:{
								gY = gridHeight - 1;
								break;
							}
							case BottomRightDefaultGridPosition:{
								gX = gridWidth - 1;
								gY = gridHeight - 1;
								break;
							}
							default:{
								gX = gridWidth / 2;
								gY = gridHeight / 2;
								break;
							}
						}
					}
					cursor.c.current = cursor.c.start;
					current = 0;
					setGriddingModeGridPositions:{
						*gridX = gX;
						*gridY = gY;
						if(++current < amount){
							++gridX;
							++gridY;
							goto setGriddingModeGridPositions;
						}
						gridX -= amount - 1;
						gridY -= amount - 1;
					}
					current = cursor.m.current - cursor.m.start;
					portToGridding:{
						genericWindow = (*cursor.c.current).window;
						if((*cursor.c.current).option & InGridContainerOption){
							if(!portWindowsFromFloating){
								goto editGriddingWindow;
							}
						}else{
							XSelectInput(display, genericWindow, windowMasks);
							XSelectInput(display, (*cursor.c.current).subwindow, StructureNotifyMask);
							XSetWindowBorderWidth(display, genericWindow, 0);
							(*cursor.c.current).option |= InGridContainerOption;
							editGriddingWindow:{
								if(!windowPointerInfo){
									current = getCurrentWindowMonitor(genericWindow, cursor.m.start, monitorAmount);
									cursor.m.current = cursor.m.start + current;
									gX = *(gridX + current);
									gY = *(gridY + current);
								}
								getGridSlotData((*cursor.m.current).width, (*cursor.m.current).height, gX, gY, gridWidth, gridHeight, &x, &y, &width, &height);
								XMoveResizeWindow(display, genericWindow, (*cursor.m.current).x + x, (*cursor.m.current).y + y, width, height);
								XResizeWindow(display, (*cursor.c.current).subwindow, width - border.x, height - border.y);
								(*cursor.c.current).gridX = gX;
								(*cursor.c.current).gridY = gY;
								(*cursor.c.current).gridWidth = 1;
								(*cursor.c.current).gridHeight = 1;
								if(evenlyDistributeWindows){
									if(++gX == gridWidth){
										gX = 0;
										if(++gY == gridHeight){
											gY = 0;
										}
									}
									*(gridX + current) = gX;
									*(gridY + current) = gY;
								}
							}
						}
						XSetWindowBackground(display, genericWindow, color.containerBackground.gridding);
						if(++cursor.c.current < cursor.c.wall){
							goto portToGridding;
						}
					}
				}
				if(option(GriddingUseFocusedWindowColor) && focused){
					XSetWindowBackground(display, (*focused).window, color.focusedContainerBackground.gridding);
				}
				mapAllWindows(cursor.c.start, cursor.c.wall);
				managementMode = GriddingManagementMode;
				free(gridX);
			}
		}
		goto eventLoop;
		tilingModeCommand:{
			if(!managementMode(Tiling)){
				if(containerAmount){
					unmapAllWindows(cursor.c.start, cursor.c.wall);
					unmaximizeAllContainers(_NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, monitorAmount, cursor.c.wall, cursor.c.start, cursor.mc.start);
					{
						/*const InputMasks windowMasks = EnterWindowMask | SubstructureRedirectMask; \
						const unsigned int totalSeparatorWidth = separatorBorders + separatorWidth; \
						const unsigned int totalSeparatorWidthGaps = totalSeparatorWidth + gapsX; \
						Window window; \
						Window subwindow; \
						unsigned int middleX; \
						int x; \
						int y; \
						unsigned int separatorAmount; \
						unsigned int availableSpace; \
						unsigned int normalWidth; \
						unsigned int abnormalWidth; \
						unsigned int height; \
						unsigned int subwindowAbnormalWidth; \
						unsigned int subwindowHeight; \
						unsigned int abnormalWidthGaps; \
						unsigned int subwindowNormalWidth; \
						unsigned int normalWidthGaps; \
						if(pointerInfo & ChangeToTilingPointerInfo){ \
							monitorInfo = getPointerMonitorInfo(); \
							middleX = allocatedContainerAmount / 2; \
							x = monitorInfo.x + gapsX; \
							y = monitorInfo.y + gapsY; \
							separatorAmount = allocatedContainerAmount - 1; \
							if(option & TilingUseSeparatorsOption){ \
								availableSpace = monitorInfo.width - (2 * allocatedContainerAmount * gapsX + (allocatedContainerAmount - 1) * totalSeparatorWidth); \
							}else{ \
								availableSpace = monitorInfo.width - (allocatedContainerAmount + 1) * gapsX; \
							} \
							normalWidth = availableSpace / allocatedContainerAmount; \
							abnormalWidth = availableSpace - (allocatedContainerAmount - 1) * normalWidth; \
							height = monitorInfo.height - 2 * gapsY; \
							subwindowAbnormalWidth = normalWidth - border.axis.x; \
							subwindowHeight = height - border.axis.y; \
							abnormalWidthGaps = abnormalWidth + gapsX; \
							subwindowNormalWidth = abnormalWidth - border.axis.x; \
							normalWidthGaps = normalWidth + gapsX; \
							currentContainer = 0; \
							do{ \
								window = container[currentContainer].window; \
								subwindow = container[currentContainer].subwindow; \
								if(!container[currentContainer].inGrid){ \
									XSelectInput(display, window, windowMasks); \
									XSelectInput(display, subwindow, StructureNotifyMask); \
									XSetWindowBorderWidth(display, window, 0); \
								}else{ \
									container[currentContainer].inGrid = 0; \
								} \
								XSetWindowBackground(display, window, color.containerBackground.tiling); \
								XUnmapWindow(display, window); \
								XMapWindow(display, window); \
								if(currentContainer == middleX){ \
									XMoveResizeWindow(display, window, x, y, abnormalWidth, height); \
									XResizeWindow(display, subwindow, subwindowAbnormalWidth, subwindowHeight); \
									x += abnormalWidthGaps; \
								}else{ \
									XMoveResizeWindow(display, window, x, y, normalWidth, height); \
									XResizeWindow(display, subwindow, subwindowNormalWidth, subwindowHeight); \
									x += normalWidthGaps; \
								} \
								if(option & TilingUseSeparatorsOption){ \
									x += totalSeparatorWidthGaps; \
								} \
							}while(++currentContainer < allocatedContainerAmount); \
						}else{ \
							unsigned int windowsAssigned; \
							unsigned int currentMonitorContainer; \
							currentMonitor = 0; \
							do{ \
								windowsAssigned = 0; \
								currentContainer = 0; \
								do{ \
									monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
									if(monitorCompare(monitorInfo, monitors[currentMonitor])){ \
										++windowsAssigned; \
									} \
								}while(++currentContainer < allocatedContainerAmount); \
								if(windowsAssigned){ \
									currentMonitorContainer = 0; \
									middleX = windowsAssigned / 2; \
									x = monitors[currentMonitor].x + gapsX; \
									y = monitors[currentMonitor].y + gapsY; \
									separatorAmount = windowsAssigned - 1; \
									if(option & TilingUseSeparatorsOption){ \
										availableSpace = monitors[currentMonitor].width - (2 * windowsAssigned * gapsX + separatorAmount * totalSeparatorWidth); \
									}else{ \
										availableSpace = monitors[currentMonitor].width - (windowsAssigned + 1) * gapsX; \
									} \
									normalWidth = availableSpace / windowsAssigned; \
									abnormalWidth = availableSpace - separatorAmount * normalWidth; \
									height = monitors[currentMonitor].height - 2 * gapsY; \
									subwindowAbnormalWidth = normalWidth - border.axis.x; \
									subwindowHeight = height - border.axis.y; \
									abnormalWidthGaps = abnormalWidth + gapsX; \
									subwindowNormalWidth = abnormalWidth - border.axis.x; \
									normalWidthGaps = normalWidth + gapsX; \
									currentContainer = 0; \
									do{ \
										monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
										if(monitorCompare(monitorInfo, monitors[currentMonitor])){ \
											window = container[currentContainer].window; \
											subwindow = container[currentContainer].subwindow; \
											if(!container[currentContainer].inGrid){ \
												XSelectInput(display, window, windowMasks); \
												XSelectInput(display, subwindow, StructureNotifyMask); \
												XSetWindowBorderWidth(display, window, 0); \
											}else{ \
												container[currentContainer].inGrid = 0; \
											} \
											XSetWindowBackground(display, window, color.containerBackground.tiling); \
											XUnmapWindow(display, window); \
											XMapWindow(display, window); \
											if(currentMonitorContainer == middleX){ \
												XMoveResizeWindow(display, window, x, y, abnormalWidth, height); \
												XResizeWindow(display, subwindow, subwindowAbnormalWidth, subwindowHeight); \
												x += abnormalWidthGaps; \
											}else{ \
												XMoveResizeWindow(display, window, x, y, normalWidth, height); \
												XResizeWindow(display, subwindow, subwindowNormalWidth, subwindowHeight); \
												x += normalWidthGaps; \
											} \
											if(option & TilingUseSeparatorsOption){ \
												x += totalSeparatorWidthGaps; \
											} \
											++currentMonitorContainer; \
										} \
									}while(++currentContainer < allocatedContainerAmount); \
								} \
							}while(++currentMonitor < monitorAmount); \
						}*/









					}
					if(option(TilingUseFocusedWindowColor) && focused){
						XSetWindowBackground(display, (*focused).window, color.focusedContainerBackground.tiling);
					}
					mapAllWindows(cursor.c.start, cursor.c.wall);
				}
				managementMode = TilingManagementMode;
			}
		}
		goto eventLoop;
		showHideToggleGridCommand:{
			switch(command){
				case ShowGridCommand:{
					if(!gridOption(Mapped)){
						goto showGrid;
					}
					goto eventLoop;
				}
				case HideGridCommand:{
					if(gridOption(Mapped)){
						goto hideGrid;
					}
					goto eventLoop;
				}
				default:{
					if(!gridOption(Mapped)){
						showGrid:{
							if(!gridOption(Exists)){
								createGrid(cursor.m.start, monitorAmount, gridWidth, gridHeight, color.gridSubwindowBorder, color.gridSubwindowBackground, cursor.g.start);
								gridOption |= ExistsGridOption;
							}
							cursor.g.current = cursor.g.start;
							lowerMapGridWindow1:{
								XLowerWindow(display, *cursor.g.current);
								XMapWindow(display, *cursor.g.current);
								if(++cursor.g.current < cursor.g.wall){
									goto lowerMapGridWindow1;
								}
							}
							gridOption |= MappedGridOption;
						}
						goto eventLoop;
					}
					hideGrid:{
						cursor.g.current = cursor.g.start;
						unmapGridWindow:{
							XUnmapWindow(display, *cursor.g.current);
							if(++cursor.g.current < cursor.g.wall){
								goto unmapGridWindow;
							}
						}
						gridOption ^= MappedGridOption;
					}
					goto eventLoop;
				}
			}
		}
		enlargeGridXCommand:{
			if(gridWidth < gridMaxWidth){
				++gridWidth;
				goto deleteGrid;
			}
		}
		goto eventLoop;
		enlargeGridYCommand:{
			if(gridHeight < gridMaxHeight){
				++gridHeight;
				goto deleteGrid;
			}
		}
		goto eventLoop;
		enlargeGridEitherCommand:{
			if(gridWidth < gridMaxWidth){
				++gridWidth;
				if(gridHeight < gridMaxHeight){
					++gridHeight;
				}
				goto deleteGrid;
			}
			if(gridHeight < gridMaxHeight){
				++gridHeight;
				goto deleteGrid;
			}
		}
		goto eventLoop;
		enlargeGridBothCommand:{
			if(gridWidth < gridMaxWidth && gridHeight < gridMaxHeight){
				++gridWidth;
				++gridHeight;
				goto deleteGrid;
			}
		}
		goto eventLoop;
		shrinkGridXCommand:{
			if(gridWidth > gridMinWidth){
				--gridWidth;
				goto deleteGrid;
			}
		}
		goto eventLoop;
		shrinkGridYCommand:{
			if(gridHeight > gridMinHeight){
				--gridHeight;
				goto deleteGrid;
			}
		}
		goto eventLoop;
		shrinkGridEitherCommand:{
			if(gridWidth > gridMinWidth){
				--gridWidth;
				if(gridHeight > gridMinHeight){
					--gridHeight;
				}
				goto deleteGrid;
			}
			if(gridHeight > gridMinHeight){
				--gridHeight;
				goto deleteGrid;
			}
		}
		goto eventLoop;
		shrinkGridBothCommand:{
			if(gridWidth > gridMinWidth && gridHeight > gridMinHeight){
				--gridWidth;
				--gridHeight;
				deleteGrid:{
					if(gridOption(Exists)){
						cursor.g.current = cursor.g.start;
						if(gridOption(Mapped)){
							destroyMappedGridSubwindows:{
								XDestroySubwindows(display, *cursor.g.current);
								if(++cursor.g.current < cursor.g.wall){
									goto destroyMappedGridSubwindows;
								}
							}
							createGrid(cursor.m.start, monitorAmount, gridWidth, gridHeight, color.gridSubwindowBorder, color.gridSubwindowBackground, cursor.g.start);
							cursor.g.current = cursor.g.start;
							lowerGridWindow:{
								XLowerWindow(display, *cursor.g.current);
								if(++cursor.g.current < cursor.g.wall){
									goto lowerGridWindow;
								}
							}
						}else{
							destroyUnmappedGridSubwindows:{
								XDestroySubwindows(display, *cursor.g.current);
								if(++cursor.g.current < cursor.g.wall){
									goto destroyUnmappedGridSubwindows;
								}
							}
							gridOption ^= ExistsGridOption;
						}
					}
					if(!managementMode(Tiling) && containerAmount){
						cursor.c.current = cursor.c.start;
						moveResizeGridWindow:{
							if((*cursor.c.current).option & InGridContainerOption){
								cursor.m.current = cursor.m.start + getCurrentWindowMonitor((*cursor.c.current).window, cursor.m.start, monitorAmount);
								if((*cursor.c.current).gridX + (*cursor.c.current).gridWidth - 1 == gridWidth){
									if(!--(*cursor.c.current).gridWidth){
										--(*cursor.c.current).gridX;
										++(*cursor.c.current).gridWidth;
									}
								}
								if((*cursor.c.current).gridY + (*cursor.c.current).gridHeight - 1 == gridHeight){
									if(!--(*cursor.c.current).gridHeight){
										--(*cursor.c.current).gridY;
										++(*cursor.c.current).gridHeight;
									}
								}
								getGridSlotData((*cursor.m.current).width, (*cursor.m.current).height, (*cursor.c.current).gridX + (*cursor.c.current).gridWidth - 1, (*cursor.c.current).gridY + (*cursor.c.current).gridHeight - 1, gridWidth, gridHeight, &x, &y, &width, &height);
								width += x;
								height += y;
								getGridSlotData((*cursor.m.current).width, (*cursor.m.current).height, (*cursor.c.current).gridX, (*cursor.c.current).gridY, gridWidth, gridHeight, &x, &y, NULL, NULL);
								width -= x;
								height -= y;
								if((*cursor.c.current).option & MaximizedContainerOption){
									findWindow((*cursor.c.current).window, &(*cursor.mc.start).window, sizeof(MaximizedContainer), monitorAmount, &current);
									cursor.m.current = cursor.m.start + current;
									cursor.mc.current = cursor.mc.start + current;
									(*cursor.mc.current).oldX = (*cursor.m.current).x + x;
									(*cursor.mc.current).oldY = (*cursor.m.current).y + y;
									(*cursor.mc.current).oldWidth = width;
									(*cursor.mc.current).oldHeight = height;
								}else{
									XMoveResizeWindow(display, (*cursor.c.current).window, (*cursor.m.current).x + x, (*cursor.m.current).y + y, width, height);
									XResizeWindow(display, (*cursor.c.current).subwindow, width - border.x, height - border.y);
								}
							}
							if(++cursor.c.current < cursor.c.wall){
								goto moveResizeGridWindow;
							}
						}
					}
				}
			}
		}
		goto eventLoop;
		toggleGapsCommand:{
			/*int offsetX; \
			int offsetY; \
			if(option & TilingUseGapsOption){ \
				offsetX = tilingGapsX; \
				offsetY = tilingGapsY; \
				gapsX = 0; \
				gapsY = 0; \
				option ^= TilingUseGapsOption; \
			}else{ \
				offsetX = -tilingGapsX; \
				offsetY = -tilingGapsY; \
				gapsX = tilingGapsX; \
				gapsY = tilingGapsY; \
				option |= TilingUseGapsOption; \
			} \
			if(managementMode == TilingManagementMode && allocatedContainerAmount){ \
				const int lastOffsetX = offsetX + gapsX; \
				const int lastOffsetY = offsetY + gapsY; \
				currentContainer = 0; \
				do{ \
					XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
					monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
					if(windowAttributes.x + windowAttributes.width == monitorInfo.x + monitorInfo.width - lastOffsetX){ \
						windowAttributes.width += 2 * offsetX; \
					}else{ \
						windowAttributes.width += offsetX; \
					} \
					if(windowAttributes.y + windowAttributes.height == monitorInfo.y + monitorInfo.height - lastOffsetY){ \
						windowAttributes.height += 2 * offsetY; \
					}else{ \
						windowAttributes.height += offsetY; \
					} \
					XMoveResizeWindow(display, container[currentContainer].window, windowAttributes.x - offsetX, windowAttributes.y - offsetY, windowAttributes.width, windowAttributes.height); \
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
				}while(++currentContainer < allocatedContainerAmount); \
			}*/
		}
		goto eventLoop;
		recascadeCommand:{
			if(managementMode(Floating) && containerAmount){
				const CascadeOptions overrideGridWindows = cascade.option & OverrideGridWindowsCascadeOption;
				const CascadeOptions overrideMaximizedWindows = cascade.option & OverrideMaximizedWindowsCascadeOption;
				if(pointerInfo(Recascade)){
					cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
					if(option(FloatingFollowGrid)){
						width = (*cursor.m.current).width / gridWidth;
						height = (*cursor.m.current).height / gridHeight;
					}else{
						width = (*cursor.m.current).width / floatingWindowDivisor;
						height = (*cursor.m.current).height / floatingWindowDivisor;
					}
					x = (*cursor.m.current).x + ((*cursor.m.current).width - width) / 2 - shadow;
					y = (*cursor.m.current).y + ((*cursor.m.current).height - height) / 2 - shadow;
					cursor.c.current = cursor.c.start;
					recascade0:{
						genericWindow = (*cursor.c.current).window;
						if((!((*cursor.c.current).option & MaximizedContainerOption) || overrideMaximizedWindows) && (!((*cursor.c.current).option & InGridContainerOption) || overrideGridWindows)){
							if((*cursor.c.current).option & MaximizedContainerOption){
								unmaximizeContainer(focused, monitorAmount, border.x, border.y, _NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, cursor.c.current, cursor.mc.start);
							}
							if((*cursor.c.current).option & InGridContainerOption){
								XSetWindowBorderWidth(display, genericWindow, shadow);
								XSetWindowBackground(display, genericWindow, color.containerBackground.floating);
								XClearArea(display, genericWindow, 0, 0, 0, 0, False);
								(*cursor.c.current).option ^= InGridContainerOption;
							}
							XMoveResizeWindow(display, genericWindow, x, y, width, height);
							XResizeWindow(display, (*cursor.c.current).subwindow, width - border.x, height - border.y);
							x += cascade.offsetX;
							y += cascade.offsetY;
						}
						if(++cursor.c.current < cursor.c.wall){
							goto recascade0;
						}
					}
				}else{
					cursor.m.current = cursor.m.start;
					current = 0;
					recascadePerMonitor:{
						if(option(FloatingFollowGrid)){
							width = (*cursor.m.current).width / gridWidth;
							height = (*cursor.m.current).height / gridHeight;
						}else{
							width = (*cursor.m.current).width / floatingWindowDivisor;
							height = (*cursor.m.current).height / floatingWindowDivisor;
						}
						x = (*cursor.m.current).x + ((*cursor.m.current).width - width) / 2 - shadow;
						y = (*cursor.m.current).y + ((*cursor.m.current).height - height) / 2 - shadow;
						cursor.c.current = cursor.c.start;
						recascade1:{
							if(getCurrentWindowMonitor(event.xmaprequest.window, cursor.m.start, monitorAmount) == current){
								genericWindow = (*cursor.c.current).window;
								if((!((*cursor.c.current).option & MaximizedContainerOption) || overrideMaximizedWindows) && (!((*cursor.c.current).option & InGridContainerOption) || overrideGridWindows)){
									if((*cursor.c.current).option & MaximizedContainerOption){
										unmaximizeContainer(focused, monitorAmount, border.x, border.y, _NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, cursor.c.current, cursor.mc.start);
									}
									if((*cursor.c.current).option & InGridContainerOption){
										XSetWindowBorderWidth(display, genericWindow, shadow);
										XSetWindowBackground(display, genericWindow, color.containerBackground.floating);
										XClearArea(display, genericWindow, 0, 0, 0, 0, False);
										(*cursor.c.current).option ^= InGridContainerOption;
									}
									XMoveResizeWindow(display, genericWindow, x, y, width, height);
									XResizeWindow(display, (*cursor.c.current).subwindow, width - border.x, height - border.y);
									x += cascade.offsetX;
									y += cascade.offsetY;
								}
							}
							if(++cursor.c.current < cursor.c.wall){
								goto recascade1;
							}
						}
						if(++cursor.m.current < cursor.m.wall){
							++current;
							goto recascadePerMonitor;
						}
					}
				}
			}
		}
		goto eventLoop;
		attachCommand:{
			if(event.xkey.subwindow && !findWindow(event.xkey.subwindow, cursor.g.start, sizeof(Window), monitorAmount, &current) && !findWindow(event.xkey.subwindow, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				event.xmaprequest.window = event.xkey.subwindow;
				if(pointerInfo(Attach)){
					current = getCurrentPointerMonitor(cursor.m.start, monitorAmount);
					goto mapWindow;
				}
				current = getCurrentWindowMonitor(event.xmaprequest.window, cursor.m.start, monitorAmount);
				goto mapWindow;
			}
		}
		goto eventLoop;
		swapMonitorsCommand:{
			if(pointerInfo(SwapMonitors)){
				cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
			}else{
				if(!focused || !findWindow((*focused).window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
					goto eventLoop;
				}
				cursor.m.current = cursor.m.start + getCurrentWindowMonitor((*focused).window, cursor.m.start, monitorAmount);
			}
			{
				const XRRMonitorInfo *const newMonitor = findMonitor(command - SwapNextMonitorCommand, displayWidth, displayHeight, cursor.m.start, cursor.m.current, cursor.m.wall);
				if(newMonitor){
					const XRRMonitorInfo *monitorToUse;
					cursor.c.current = cursor.c.start;
					swapWindowsFloating:{
						current = getCurrentWindowMonitor((*cursor.c.current).window, cursor.m.start, monitorAmount);
						if(cursor.m.start + current == cursor.m.current){
							monitorToUse = newMonitor;
						}else if(cursor.m.start + current == newMonitor){
							monitorToUse = cursor.m.current;
						}
						switch(managementMode){
							case FloatingManagementMode:{
								if((*cursor.c.current).option & InGridContainerOption){
									goto swapGriddingInGrid;
								}
								moveContainerToFloatingPosition((*cursor.c.current).window, (*cursor.c.current).subwindow, cursor.m.current, monitorToUse, option, gridWidth, gridHeight, floatingWindowDivisor, border.x, border.y, floatingMinimumWidth, floatingMinimumHeight);
								break;
							}
							case GriddingManagementMode:{
								swapGriddingInGrid:{
									moveContainerToGridPosition(cursor.c.current, monitorToUse, gridWidth, gridHeight, border.x, border.y);
								}
								break;
							}
							default:{
								/**/



								break;
							}
						}
						if(++cursor.c.current < cursor.c.wall){
							goto swapWindowsFloating;
						}
					}
				}
			}
		}
		goto eventLoop;
		revolveMonitorsCommand:{
			if(pointerInfo(RevolveMonitors)){
				cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
			}else{
				if(!focused || !findWindow((*focused).window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
					goto eventLoop;
				}
				cursor.m.current = cursor.m.start + getCurrentWindowMonitor((*focused).window, cursor.m.start, monitorAmount);
			}
			switch(command){
				case RevolveMonitorsNextCommand:{
					/**/



					goto eventLoop;
				}
				case RevolveMonitorsPreviousCommand:{
					/**/



					goto eventLoop;
				}
				case RevolveMonitorsHorizontallyCommand:{
					/**/



					goto eventLoop;
				}
				default:{
					/**/



					goto eventLoop;
				}
			}
		}
		goto eventLoop;
		moveResizeCommand:{
			if(findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if((*cursor.c.current).option & MaximizedContainerOption){
					goto eventLoop;
				}
				switch(command){
					case MoveCommand:{
						if(!event.xbutton.subwindow){
							goto eventLoop;
						}
						moveTiling:{
							switch(managementMode){
								case FloatingManagementMode:{
									if((*cursor.c.current).option & InGridContainerOption){
										goto moveGriddingInGrid;
									}
									XGetGeometry(display, event.xany.window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
									if(option(FloatingMinimalMove)){
										XSetWindowBorderWidth(display, motionContainer.minimalWindow, motionContainer.minimalMoveBorder);
										XSetWindowBorder(display, motionContainer.minimalWindow, color.motionContainer.minimalMoveBorder);
										XSetWindowBackground(display, motionContainer.minimalWindow, color.motionContainer.minimalMoveBackground);
										XMoveResizeWindow(display, motionContainer.minimalWindow, x + shadow - motionContainer.minimalMoveBorder, y + shadow - motionContainer.minimalMoveBorder, width, height);
										XMapRaised(display, motionContainer.minimalWindow);
										motionContainer.window = motionContainer.minimalWindow;
										motionContainer.minimalWindow = event.xany.window;
										genericUnsignedInteger = shadow;
										shadow = motionContainer.minimalMoveBorder;
										motionContainer.minimalMoveBorder = genericUnsignedInteger;
									}else{
										motionContainer.window = event.xany.window;
									}
									motionContainer.x = x + shadow;
									motionContainer.y = y + shadow;
									motionContainer.width = width;
									motionContainer.height = height;
									motionContainer.previousMonitor = getCurrentWindowMonitor(motionContainer.window, cursor.m.start, monitorAmount);
									motionContainer.pointerOffsetX = event.xbutton.x + shadow;
									motionContainer.pointerOffsetY = event.xbutton.y + shadow;
									motionContainer.option = NoMotionOptions;
									motionContainer.action = MoveMotionAction;
									motionContainer.subaction = NoMotionSubaction;
									goto exitMoveResize;
								}
								case GriddingManagementMode:{
									moveGriddingInGrid:{
										/**/









									}
									goto exitMoveResize;
								}
								default:{
									/**/









									goto exitMoveResize;
								}
							}
						}
					}
					case ResizeCommand:{
						if(event.xbutton.subwindow){
							goto eventLoop;
						}
						resizeTiling:{
							switch(managementMode){
								case FloatingManagementMode:{
									if((*cursor.c.current).option & InGridContainerOption){
										goto resizeGriddingInGrid;
									}
									XGetGeometry(display, event.xany.window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
									if(event.xbutton.y < (int)border.up){
										if(event.xbutton.x < (int)border.left){
											motionContainer.subaction = UpLeftResizeMotionSubaction;
										}else if(event.xbutton.x < (int)(width - border.right)){
											motionContainer.subaction = UpResizeMotionSubaction;
										}else{
											motionContainer.subaction = UpRightResizeMotionSubaction;
										}
									}else if(event.xbutton.y < (int)(height - border.down)){
										if(event.xbutton.x < (int)border.left){
											motionContainer.subaction = LeftResizeMotionSubaction;
										}else{
											motionContainer.subaction = RightResizeMotionSubaction;
										}
									}else{
										if(event.xbutton.x < (int)border.left){
											motionContainer.subaction = DownLeftResizeMotionSubaction;
										}else if(event.xbutton.x < (int)(width - border.right)){
											motionContainer.subaction = DownResizeMotionSubaction;
										}else{
											motionContainer.subaction = DownRightResizeMotionSubaction;
										}
									}
									motionContainer.x = x;
									motionContainer.y = y;
									motionContainer.pointerOffsetX = event.xbutton.x + shadow;
									motionContainer.pointerOffsetY = event.xbutton.y + shadow;
									if(option(FloatingMinimalResize)){
										XSetWindowBorderWidth(display, motionContainer.minimalWindow, motionContainer.minimalResizeBorder);
										XSetWindowBorder(display, motionContainer.minimalWindow, color.motionContainer.minimalResizeBorder);
										XSetWindowBackground(display, motionContainer.minimalWindow, color.motionContainer.minimalResizeBackground);
										XMoveResizeWindow(display, motionContainer.minimalWindow, x + shadow - motionContainer.minimalMoveBorder, y + shadow - motionContainer.minimalMoveBorder, width, height);
										XMapRaised(display, motionContainer.minimalWindow);
										motionContainer.window = motionContainer.minimalWindow;
										motionContainer.minimalWindow = event.xany.window;
										switch(motionContainer.subaction){
											case UpResizeMotionSubaction:{
												motionContainer.x += shadow - motionContainer.minimalMoveBorder;
												motionContainer.y += shadow - motionContainer.minimalMoveBorder;
												motionContainer.pointerOffsetX += motionContainer.minimalMoveBorder - shadow;
												motionContainer.pointerOffsetY += motionContainer.minimalMoveBorder - shadow;
												break;
											}
											case LeftResizeMotionSubaction:{
												motionContainer.x += shadow - motionContainer.minimalMoveBorder;
												motionContainer.y += shadow - motionContainer.minimalMoveBorder;
												motionContainer.pointerOffsetX += motionContainer.minimalMoveBorder - shadow;
												motionContainer.pointerOffsetY += motionContainer.minimalMoveBorder - shadow;
												break;
											}
											case RightResizeMotionSubaction:{
												motionContainer.x += shadow - motionContainer.minimalMoveBorder;
												motionContainer.y += shadow - motionContainer.minimalMoveBorder;
												motionContainer.pointerOffsetX += motionContainer.minimalMoveBorder - shadow;
												motionContainer.pointerOffsetY += motionContainer.minimalMoveBorder - shadow;
												break;
											}
											case UpLeftResizeMotionSubaction:{
												motionContainer.x += shadow - motionContainer.minimalMoveBorder;
												motionContainer.y += shadow - motionContainer.minimalMoveBorder;
												motionContainer.pointerOffsetX += motionContainer.minimalMoveBorder - shadow;
												motionContainer.pointerOffsetY += motionContainer.minimalMoveBorder - shadow;
												break;
											}
											case UpRightResizeMotionSubaction:{
												x += shadow - motionContainer.minimalMoveBorder;
												motionContainer.y += shadow - motionContainer.minimalMoveBorder;
												motionContainer.pointerOffsetY += motionContainer.minimalMoveBorder - shadow;
												break;
											}
											case DownLeftResizeMotionSubaction:{
												y += shadow - motionContainer.minimalMoveBorder;
												motionContainer.x += shadow - motionContainer.minimalMoveBorder;
												motionContainer.pointerOffsetX += motionContainer.minimalMoveBorder - shadow;
												break;
											}
											default:{
												break;
											}
										}
									}else{
										motionContainer.window = event.xany.window;
									}
									motionContainer.subwindow = (*cursor.c.current).subwindow;
									motionContainer.width = width;
									motionContainer.height = height;
									motionContainer.action = ResizeMotionAction;
									goto exitMoveResize;
								}
								case GriddingManagementMode:{
									resizeGriddingInGrid:{
										/**/









									}
									goto exitMoveResize;
								}
								default:{
									/**/









									goto exitMoveResize;
								}
							}
						}
					}
					default:{
						if(event.xbutton.subwindow){
							goto moveTiling;
						}
						goto resizeTiling;
					}
				}
				exitMoveResize:{
					XMapRaised(display, motionContainer.glass);
				}
			}
		}
		goto eventLoop;
		cancelMoveResizeCommand:{
			if(motionContainer.action){
				switch(managementMode){
					case FloatingManagementMode:{
						if((*cursor.c.current).option & InGridContainerOption){
							if(motionAction(Move)){
								if(option(InGridMinimalMove)){
									goto cancelMoveResize;
								}
								goto eventLoop;
							}
							if(option(InGridMinimalResize)){
								goto cancelMoveResize;
							}
							goto eventLoop;
						}
						if(motionAction(Move)){
							if(option(FloatingMinimalMove)){
								goto cancelMoveResize;
							}
							goto eventLoop;
						}
						if(option(FloatingMinimalResize)){
							goto cancelMoveResize;
						}
						goto eventLoop;
					}
					case GriddingManagementMode:{
						if(motionAction(Move)){
							if(option(GriddingMinimalMove)){
								goto cancelMoveResize;
							}
							goto eventLoop;
						}
						if(option(GriddingMinimalResize)){
							goto cancelMoveResize;
						}
						goto eventLoop;
					}
					default:{
						if(motionAction(Move)){
							if(option(TilingMinimalMove)){
								goto cancelMoveResize;
							}
							goto eventLoop;
						}
						if(option(TilingMinimalResize)){
							cancelMoveResize:{
								if(motionContainer.subaction && motionOption(SnappingMapped)){
									XUnmapWindow(display, motionContainer.snappingWindow);
								}
								XUnmapWindow(display, motionContainer.window);
								XUnmapWindow(display, motionContainer.glass);
								genericWindow = motionContainer.window;
								motionContainer.window = motionContainer.minimalWindow;
								motionContainer.minimalWindow = genericWindow;
								if(motionAction(Move)){
									genericUnsignedInteger = shadow;
									shadow = motionContainer.minimalMoveBorder;
									motionContainer.minimalMoveBorder = genericUnsignedInteger;
								}
								motionContainer.action = NoMotionAction;
							}
						}
						goto eventLoop;
					}
				}
			}
		}
		goto eventLoop;
		moveToCommand:{
			if(findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if((*cursor.c.current).option & MaximizedContainerOption){
					goto eventLoop;
				}
				switch(managementMode){
					case FloatingManagementMode:{
						if((*cursor.c.current).option & InGridContainerOption){
							goto moveToGriddingInGrid;
							break;
						}
						if(forcePointerMonitor || pointerInfo(MoveToFloating)){
							cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
						}else{
							cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
						}
						if(option(FloatingFollowGrid)){
							width = (*cursor.m.current).width / gridWidth;
							height = (*cursor.m.current).height / gridHeight;
						}else{
							width = (*cursor.m.current).width / floatingWindowDivisor;
							height = (*cursor.m.current).height / floatingWindowDivisor;
						}
						x = (*cursor.m.current).x;
						y = (*cursor.m.current).y;
						switch(command){
							case MoveTopCommand:{
								width = (*cursor.m.current).width;
								break;
							}
							case MoveBottomCommand:{
								y += (*cursor.m.current).height - height;
								width = (*cursor.m.current).width;
								break;
							}
							case MoveLeftCommand:{
								height = (*cursor.m.current).height;
								break;
							}
							case MoveRightCommand:{
								x += (*cursor.m.current).width - width;
								height = (*cursor.m.current).height;
								break;
							}
							case MoveTopRightCommand:{
								x += (*cursor.m.current).width - width;
								break;
							}
							case MoveBottomLeftCommand:{
								y += (*cursor.m.current).height - height;
								break;
							}
							case MoveBottomRightCommand:{
								x += (*cursor.m.current).width - width;
								y += (*cursor.m.current).height - height;
								break;
							}
							default:{
								break;
							}
						}
						XRaiseWindow(display, event.xany.window);
						XMoveResizeWindow(display, event.xany.window, x - shadow, y - shadow, width, height);
						XResizeWindow(display, (*cursor.c.current).subwindow, width - border.x, height - border.y);
						goto eventLoop;
					}
					case GriddingManagementMode:{
						moveToGriddingInGrid:{
							Options followGrid;
							if(pointerInfo(MoveToInGrid)){
								cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
							}else{
								cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
							}
							if(managementMode(Gridding)){
								followGrid = option(GriddingFollowGrid);
							}else{
								followGrid = option(InGridFollowGrid);
							}
							x = (*cursor.m.current).x;
							y = (*cursor.m.current).y;
							switch(command){
								case MoveTopCommand:{
									if(followGrid){
										(*cursor.c.current).gridHeight = 1;
									}else{
										(*cursor.c.current).gridHeight = gridHeight / 2;
										if(!(*cursor.c.current).gridHeight){
											(*cursor.c.current).gridHeight = 1;
										}
									}
									(*cursor.c.current).gridX = 0;
									(*cursor.c.current).gridY = 0;
									(*cursor.c.current).gridWidth = gridWidth;
									goto moveToInGrid;
								}
								case MoveBottomCommand:{
									if(followGrid){
										(*cursor.c.current).gridY = gridHeight - 1;
										(*cursor.c.current).gridHeight = 1;
									}else{
										(*cursor.c.current).gridHeight = gridHeight / 2;
										if(!(*cursor.c.current).gridHeight){
											(*cursor.c.current).gridHeight = 1;
										}
										(*cursor.c.current).gridY = gridHeight - (*cursor.c.current).gridHeight;
									}
									(*cursor.c.current).gridX = 0;
									(*cursor.c.current).gridWidth = gridWidth;
									goto moveToInGrid;
								}
								case MoveLeftCommand:{
									if(followGrid){
										(*cursor.c.current).gridWidth = 1;
									}else{
										(*cursor.c.current).gridWidth = gridWidth / 2;
										if(!(*cursor.c.current).gridWidth){
											(*cursor.c.current).gridWidth = 1;
										}
									}
									(*cursor.c.current).gridX = 0;
									(*cursor.c.current).gridY = 0;
									(*cursor.c.current).gridHeight = gridHeight;
									goto moveToInGrid;
								}
								case MoveRightCommand:{
									if(followGrid){
										(*cursor.c.current).gridX = gridWidth - 1;
										(*cursor.c.current).gridWidth = 1;
									}else{
										(*cursor.c.current).gridWidth = gridWidth / 2;
										if(!(*cursor.c.current).gridWidth){
											(*cursor.c.current).gridWidth = 1;
										}
										(*cursor.c.current).gridX = gridWidth - (*cursor.c.current).gridWidth;
									}
									(*cursor.c.current).gridY = 0;
									(*cursor.c.current).gridHeight = gridHeight;
									goto moveToInGrid;
								}
								default:{
									if(followGrid){
										(*cursor.c.current).gridWidth = 1;
										(*cursor.c.current).gridHeight = 1;
									}else{
										(*cursor.c.current).gridWidth = gridWidth / 2;
										(*cursor.c.current).gridHeight = gridHeight / 2;
										if(!(*cursor.c.current).gridWidth){
											(*cursor.c.current).gridWidth = 1;
										}
										if(!(*cursor.c.current).gridHeight){
											(*cursor.c.current).gridHeight = 1;
										}
									}
									switch(command){
										case MoveTopLeftCommand:{
											(*cursor.c.current).gridX = 0;
											(*cursor.c.current).gridY = 0;
											break;
										}
										case MoveTopRightCommand:{
											(*cursor.c.current).gridX = gridWidth - (*cursor.c.current).gridWidth;
											(*cursor.c.current).gridY = 0;
											break;
										}
										case MoveBottomLeftCommand:{
											(*cursor.c.current).gridX = 0;
											(*cursor.c.current).gridY = gridHeight - (*cursor.c.current).gridHeight;
											break;
										}
										default:{
											(*cursor.c.current).gridX = gridWidth - (*cursor.c.current).gridWidth;
											(*cursor.c.current).gridY = gridHeight - (*cursor.c.current).gridHeight;
											break;
										}
									}
									moveToInGrid:{
										moveContainerToGridPosition(cursor.c.current, cursor.m.current, gridWidth, gridHeight, border.x, border.y);
									}
								}
							}
						}
						goto eventLoop;
					}
					default:{
						if(containerAmount > 1){
							if(option(TilingSlamWindows)){
								slamTo:{
									/**/









								}
							}else{
								Command command1 = NoCommand;
								XGetGeometry(display, event.xany.window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
								cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
								switch(command){
									case MoveTopCommand:{
										if(y > (*cursor.m.current).y + (int)gapsY){
											break;
										}
										goto tryToSlamY;
									}
									case MoveBottomCommand:{
										if(y + (int)height < (*cursor.m.current).y + (*cursor.m.current).height - (int)gapsY){
											break;
										}
										tryToSlamY:{
											if(x > (*cursor.m.current).x + (int)gapsX || width < (unsigned int)(*cursor.m.current).width - 2 * gapsX){
												goto slamTo;
											}
											if(option(TilingFollowGrid)){
												genericUnsignedInteger = (*cursor.m.current).height / gridHeight;
											}else{
												genericUnsignedInteger = (*cursor.m.current).height / floatingWindowDivisor;
											}
											if(height != genericUnsignedInteger){
												goto slamTo;
											}
										}
										goto eventLoop;
									}
									case MoveLeftCommand:{
										if(x > (*cursor.m.current).x + (int)gapsX){
											break;
										}
										goto tryToSlamX;
									}
									case MoveRightCommand:{
										if(x + (int)width < (*cursor.m.current).x + (*cursor.m.current).width - (int)gapsX){
											break;
										}
										tryToSlamX:{
											if(y > (*cursor.m.current).y + (int)gapsY || height < (unsigned int)(*cursor.m.current).height - 2 * gapsY){
												goto slamTo;
											}
											if(option(TilingFollowGrid)){
												genericUnsignedInteger = (*cursor.m.current).width / gridWidth;
											}else{
												genericUnsignedInteger = (*cursor.m.current).width / floatingWindowDivisor;
											}
											if(width != genericUnsignedInteger){
												goto slamTo;
											}
										}
										goto eventLoop;
									}
									case MoveTopLeftCommand:{
										const bool moveLeft = x > (*cursor.m.current).x + (int)gapsX;
										const TilingPrioritization prioritizeY = tilingPrioritize(MoveTopLeftY);
										if(y > (*cursor.m.current).y + (int)gapsY){
											if(moveLeft){
												if(prioritizeY){
													command = MoveTopCommand;
													command1 = MoveLeftCommand;
												}else{
													command = MoveLeftCommand;
													command1 = MoveTopCommand;
												}
												break;
											}
											command = MoveTopCommand;
										}else if(moveLeft){
											command = MoveLeftCommand;
										}else{
											if(prioritizeY){
												goto tryToSlamY;
											}
											goto tryToSlamX;
										}
										break;
									}
									case MoveTopRightCommand:{
										const bool moveRight = x + (int)width < (*cursor.m.current).x + (*cursor.m.current).width - (int)gapsX;
										const TilingPrioritization prioritizeY = tilingPrioritize(MoveTopRightY);
										if(y > (*cursor.m.current).y + (int)gapsY){
											if(moveRight){
												if(prioritizeY){
													command = MoveTopCommand;
													command1 = MoveRightCommand;
												}else{
													command = MoveRightCommand;
													command1 = MoveTopCommand;
												}
												break;
											}
											command = MoveTopCommand;
										}else if(moveRight){
											command = MoveRightCommand;
										}else{
											if(prioritizeY){
												goto tryToSlamY;
											}
											goto tryToSlamX;
										}
										break;
									}
									case MoveBottomLeftCommand:{
										const bool moveLeft = x > (*cursor.m.current).x + (int)gapsX;
										const TilingPrioritization prioritizeY = tilingPrioritize(MoveBottomLeftY);
										if(y + (int)height < (*cursor.m.current).y + (*cursor.m.current).height - (int)gapsY){
											if(moveLeft){
												if(prioritizeY){
													command = MoveBottomCommand;
													command1 = MoveLeftCommand;
												}else{
													command = MoveLeftCommand;
													command1 = MoveBottomCommand;
												}
												break;
											}
											command = MoveBottomCommand;
										}else if(moveLeft){
											command = MoveLeftCommand;
										}else{
											if(prioritizeY){
												goto tryToSlamY;
											}
											goto tryToSlamX;
										}
										break;
									}
									default:{
										const bool moveRight = x + (int)width < (*cursor.m.current).x + (*cursor.m.current).width - (int)gapsX;
										const TilingPrioritization prioritizeY = tilingPrioritize(MoveBottomRightY);
										if(y + (int)height < (*cursor.m.current).y + (*cursor.m.current).height - (int)gapsY){
											if(moveRight){
												if(prioritizeY){
													command = MoveBottomCommand;
													command1 = MoveRightCommand;
												}else{
													command = MoveRightCommand;
													command1 = MoveBottomCommand;
												}
												break;
											}
											command = MoveBottomCommand;
										}else if(moveRight){
											command = MoveRightCommand;
										}else{
											if(prioritizeY){
												goto tryToSlamY;
											}
											goto tryToSlamX;
										}
										break;
									}
								}
								{
									const Container *const found = cursor.c.current;
									const int *position00;
									const int *position01;
									const unsigned int *size00;
									const unsigned int *size01;
									const int *position10;
									const int *position11;
									const unsigned int *size10;
									const Container *containerToUse = cursor.c.wall;
									int x1;
									int y1;
									unsigned int width1;
									unsigned int height1;
									unsigned int spacing;
									unsigned int monitorSize;
									unsigned int pixels = 0;
									unsigned int mostPixels = 0;
									moveToTiling:{
										switch(command){
											case MoveTopCommand:{
												position00 = &y1;
												size00 = &height1;
												position10 = &y;
												goto verticalMove;
											}
											case MoveBottomCommand:{
												position00 = &y;
												size00 = &height;
												position10 = &y1;
												verticalMove:{
													position01 = &x1;
													spacing = gapsY;
													size01 = &width1;
													position11 = &x;
													size10 = &width;
													monitorSize = (*cursor.m.current).width - 2 * gapsX;
												}
												break;
											}
											case MoveLeftCommand:{
												position00 = &x1;
												size00 = &width1;
												position10 = &x;
												goto horizontalMove;
											}
											default:{
												position00 = &x;
												size00 = &width;
												position10 = &x1;
												horizontalMove:{
													position01 = &y1;
													spacing = gapsX;
													size01 = &height1;
													position11 = &y;
													size10 = &height;
													monitorSize = (*cursor.m.current).height - 2 * gapsY;
												}
												break;
											}
										}
										if(option(TilingUseSeparators)){
											spacing = 2 * (spacing + separatorBorder) + separatorWidth;
										}
										cursor.c.current = cursor.c.start;
										findWindowToMoveTo:{
											if(cursor.c.current != found){
												XGetGeometry(display, (*cursor.c.current).window, &genericWindow, &x1, &y1, &width1, &height1, &genericBorder, &genericDepth);
												pixels = getAdjacentSurfaceSize(*position00, *position01, *size00 + spacing, *size01, *position10, *position11, *size10);
												if(pixels > mostPixels){
													containerToUse = cursor.c.current;
													mostPixels = pixels;
													if(*size01 == monitorSize){
														goto moveToTilingLoopControl;
													}
												}
											}
											if(++cursor.c.current < cursor.c.wall){
												goto findWindowToMoveTo;
											}
										}
										moveToTilingLoopControl:{
											XGetGeometry(display, (*containerToUse).window, &genericWindow, &x1, &y1, &width1, &height1, &genericBorder, &genericDepth);
											XMoveResizeWindow(display, event.xany.window, x1, y1, width1, height1);
											XResizeWindow(display, (*found).subwindow, width1 - border.x, height1 - border.y);
											XMoveResizeWindow(display, (*containerToUse).window, x, y, width, height);
											XResizeWindow(display, (*containerToUse).subwindow, width - border.x, height - border.y);
											if(command1){
												command = command1;
												command1 = NoCommand;
												goto moveToTiling;
											}
										}
									}
								}
							}
						}
						goto eventLoop;
					}
				}
			}
		}
		goto eventLoop;
		moveCenterFull:{
			if(!managementMode(Tiling) && findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if((*cursor.c.current).option & MaximizedContainerOption){
					goto eventLoop;
				}
				if((*cursor.c.current).option & InGridContainerOption){
					if(forcePointerMonitor || pointerInfo(MoveToInGrid)){
						cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
					}else{
						cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
					}
					if(command(MoveCenter)){
						(*cursor.c.current).gridX = gridWidth / 2;
						(*cursor.c.current).gridY = gridHeight / 2;
						(*cursor.c.current).gridWidth = 1;
						(*cursor.c.current).gridHeight = 1;
					}else{
						(*cursor.c.current).gridX = 0;
						(*cursor.c.current).gridY = 0;
						(*cursor.c.current).gridWidth = gridWidth;
						(*cursor.c.current).gridHeight = gridHeight;
					}
					moveContainerToGridPosition(cursor.c.current, cursor.m.current, gridWidth, gridHeight, border.x, border.y);
					goto eventLoop;
				}
				if(forcePointerMonitor || pointerInfo(MoveToFloating)){
					cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
				}else{
					cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
				}
				x = (*cursor.m.current).x;
				y = (*cursor.m.current).y;
				width = (*cursor.m.current).width;
				height = (*cursor.m.current).height;
				if(command(MoveCenter)){
					if(option(FloatingFollowGrid)){
						width /= gridWidth;
						height /= gridHeight;
					}else{
						width /= floatingWindowDivisor;
						height /= floatingWindowDivisor;
					}
					x += ((*cursor.m.current).width - width) / 2;
					y += ((*cursor.m.current).height - height) / 2;
				}
				XRaiseWindow(display, event.xany.window);
				XMoveResizeWindow(display, event.xany.window, x - shadow, y - shadow, width, height);
				XResizeWindow(display, (*cursor.c.current).subwindow, width - border.x, height - border.y);
			}
		}
		goto eventLoop;
		moveMonitorCommand:{
			if(findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if(pointerInfo(MoveToMonitor)){
					cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
				}else{
					cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
				}
				{
					const XRRMonitorInfo *const newMonitor = findMonitor(command - MoveNextMonitorCommand, displayWidth, displayHeight, cursor.m.start, cursor.m.current, cursor.m.wall);
					if(newMonitor){
						const Options isMaximized = (*cursor.c.current).option & MaximizedContainerOption;
						if(isMaximized){
							if((*(cursor.mc.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount))).shouldChangeProperty){
								command = FullscreenCommand;
							}else{
								command = BigscreenCommand;
							}
							cursor.mc.current = cursor.mc.start + (newMonitor - cursor.m.start);
							if((*cursor.mc.current).window && findWindow((*cursor.mc.current).window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
								unmaximizeContainer(focused, monitorAmount, border.x, border.y, _NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, cursor.c.start + current, cursor.mc.start);
							}
							unmaximizeContainer(focused, monitorAmount, border.x, border.y, _NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, cursor.c.current, cursor.mc.start);
						}
						switch(managementMode){
							case FloatingManagementMode:{
								if((*cursor.c.current).option & InGridContainerOption){
									moveContainerToGridPosition(cursor.c.current, newMonitor, gridWidth, gridHeight, border.x, border.y);
									break;
								}
								moveContainerToFloatingPosition(event.xany.window, (*cursor.c.current).subwindow, cursor.m.current, newMonitor, option, gridWidth, gridHeight, floatingWindowDivisor, border.x, border.y, floatingMinimumWidth, floatingMinimumHeight);
								break;
							}
							case GriddingManagementMode:{
								moveContainerToGridPosition(cursor.c.current, newMonitor, gridWidth, gridHeight, border.x, border.y);
								break;
							}
							default:{
								/*removeTiling();
								addTiling();*/
								break;
							}
						}
						if(isMaximized){
							maximizeContainer(FullscreenCommand, newMonitor, managementMode, &color, _NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, border.x, border.y, focused, cursor.c.current, cursor.mc.current);
						}
					}
				}
			}
		}
		goto eventLoop;
		addRemoveToggleGridCommand:{
			if(managementMode(Floating) && findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if((*cursor.c.current).option & MaximizedContainerOption){
					goto eventLoop;
				}
				switch(command){
					case AddToGridCommand:{
						if(!((*cursor.c.current).option & InGridContainerOption)){
							goto addToGrid;
						}
						goto eventLoop;
					}
					case RemoveFromGridCommand:{
						if((*cursor.c.current).option & InGridContainerOption){
							goto removeFromGrid;
						}
						goto eventLoop;
					}
					default:{
						if(!((*cursor.c.current).option & InGridContainerOption)){
							addToGrid:{
								if(pointerInfo(AddToGrid)){
									cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
								}else{
									cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
								}
								switch(defaultGridPosition){
									case TopLeftDefaultGridPosition:{
										(*cursor.c.current).gridX = 0;
										(*cursor.c.current).gridY = 0;
										break;
									}
									case TopRightDefaultGridPosition:{
										(*cursor.c.current).gridX = gridWidth - 1;
										(*cursor.c.current).gridY = 0;
										break;
									}
									case BottomLeftDefaultGridPosition:{
										(*cursor.c.current).gridX = 0;
										(*cursor.c.current).gridY = gridHeight - 1;
										break;
									}
									case BottomRightDefaultGridPosition:{
										(*cursor.c.current).gridX = gridWidth - 1;
										(*cursor.c.current).gridY = gridHeight - 1;
										break;
									}
									default:{
										(*cursor.c.current).gridX = gridWidth / 2;
										(*cursor.c.current).gridY = gridHeight / 2;
										break;
									}
								}
								getGridSlotData((*cursor.m.current).width, (*cursor.m.current).height, (*cursor.c.current).gridX, (*cursor.c.current).gridY, gridWidth, gridHeight, &x, &y, &width, &height);
								x += (*cursor.m.current).x;
								y += (*cursor.m.current).y;
								(*cursor.c.current).gridWidth = 1;
								(*cursor.c.current).gridHeight = 1;
								(*cursor.c.current).option |= InGridContainerOption;
								XSelectInput(display, event.xany.window, EnterWindowMask | SubstructureRedirectMask);
								XSelectInput(display, (*cursor.c.current).subwindow, StructureNotifyMask);
								if(focused == cursor.c.current){
									XSetWindowBackground(display, event.xany.window, color.focusedContainerBackground.inGrid);
								}else{
									XSetWindowBackground(display, event.xany.window, color.containerBackground.inGrid);
								}
								XRaiseWindow(display, event.xany.window);
								XSetWindowBorderWidth(display, event.xany.window, 0);
								goto addRemoveGrid;
							}
						}
						removeFromGrid:{
							if(pointerInfo(RemoveFromGrid)){
								cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
							}else{
								cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
							}
							if(option(FloatingFollowGrid)){
								width = (*cursor.m.current).width / gridWidth;
								height = (*cursor.m.current).height / gridHeight;
							}else{
								width = (*cursor.m.current).width / floatingWindowDivisor;
								height = (*cursor.m.current).height / floatingWindowDivisor;
							}
							x = (*cursor.m.current).x + ((*cursor.m.current).width - width) / 2 - shadow;
							y = (*cursor.m.current).y + ((*cursor.m.current).height - height) / 2 - shadow;
							(*cursor.c.current).option ^= InGridContainerOption;
							XSelectInput(display, event.xany.window, ButtonReleaseMask | EnterWindowMask | SubstructureRedirectMask);
							XSelectInput(display, (*cursor.c.current).subwindow, ButtonReleaseMask | StructureNotifyMask);
							if(focused == cursor.c.current){
								XSetWindowBackground(display, event.xany.window, color.focusedContainerBackground.floating);
							}else{
								XSetWindowBackground(display, event.xany.window, color.containerBackground.floating);
							}
							XRaiseWindow(display, event.xany.window);
							XSetWindowBorderWidth(display, event.xany.window, shadow);
							addRemoveGrid:{
								XClearArea(display, event.xany.window, 0, 0, 0, 0, False);
								XMoveResizeWindow(display, event.xany.window, x, y, width, height);
								XResizeWindow(display, (*cursor.c.current).subwindow, width - border.x, height - border.y);
							}
						}
						goto eventLoop;
					}
				}
			}
		}
		goto eventLoop;
		moveInsideGridCommand:{
			if(findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if((*cursor.c.current).option & MaximizedContainerOption || !((*cursor.c.current).option & InGridContainerOption)){
					goto eventLoop;
				}
				switch(command){
					case MoveUpGridCommand:{
						if((*cursor.c.current).gridY){
							--(*cursor.c.current).gridY;
							goto moveInsideGrid;
						}
						goto eventLoop;
					}
					case MoveDownGridCommand:{
						if((*cursor.c.current).gridY + (*cursor.c.current).gridHeight < gridHeight){
							++(*cursor.c.current).gridY;
							goto moveInsideGrid;
						}
						goto eventLoop;
					}
					case MoveLeftGridCommand:{
						if((*cursor.c.current).gridX){
							--(*cursor.c.current).gridX;
							goto moveInsideGrid;
						}
						goto eventLoop;
					}
					default:{
						if((*cursor.c.current).gridX + (*cursor.c.current).gridWidth < gridWidth){
							++(*cursor.c.current).gridX;
							moveInsideGrid:{
								if(pointerInfo(MoveOnGrid)){
									cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
								}else{
									cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
								}
								moveContainerToGridPosition(cursor.c.current, cursor.m.current, gridWidth, gridHeight, border.x, border.y);
							}
						}
						goto eventLoop;
					}
				}
			}
		}
		goto eventLoop;
		extendCommand:{
			if(findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if((*cursor.c.current).option & MaximizedContainerOption){
					goto eventLoop;
				}
				switch(managementMode){
					case FloatingManagementMode:{
						if((*cursor.c.current).option & InGridContainerOption){
							goto extendGriddingInGrid;
						}
						XGetGeometry(display, event.xany.window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
						switch(command){
							case ExtendUpCommand:
							case ExtendDownCommand:{
								if(height < floatingMaximumHeight){
									if(command(ExtendUp)){
										y -= floatingExtendHeight;
									}
									height += floatingExtendHeight;
									if(height > floatingMaximumHeight){
										if(command(ExtendUp)){
											y += floatingMaximumHeight - height;
										}
										height = floatingMaximumHeight;
									}
									goto extendShrinkFloating;
								}
								goto eventLoop;
							}
							case ExtendLeftCommand:
							case ExtendRightCommand:{
								if(width < floatingMaximumWidth){
									if(command(ExtendLeft)){
										x -= floatingExtendWidth;
									}
									width += floatingExtendWidth;
									if(width > floatingMaximumWidth){
										if(command(ExtendLeft)){
											x += floatingMaximumWidth - width;
										}
										width = floatingMaximumWidth;
									}
									goto extendShrinkFloating;
								}
								goto eventLoop;
							}
							default:{
								if(height < floatingMaximumHeight){
									if(command <= ExtendUpRightCommand){
										y -= floatingExtendHeight;
									}
									height += floatingExtendHeight;
									if(height > floatingMaximumHeight){
										if(command <= ExtendUpRightCommand){
											y += floatingMaximumHeight - height;
										}
										height = floatingMaximumHeight;
									}
									if(width < floatingMaximumWidth){
										goto extendWidthFloating;
									}
									goto extendShrinkFloating;
								}
								if(width < floatingMaximumWidth){
									extendWidthFloating:{
										if(command(ShrinkUpLeft) || command(ShrinkDownLeft)){
											x -= floatingExtendWidth;
										}
										width += floatingExtendWidth;
										if(width > floatingMaximumWidth){
											if(command(ExtendLeft)){
												x += floatingMaximumWidth - width;
											}
											width = floatingMaximumWidth;
										}
									}
									goto extendShrinkFloating;
								}
								goto eventLoop;
							}
						}
					}
					case GriddingManagementMode:{
						extendGriddingInGrid:{
							switch(command){
								case ExtendUpCommand:{
									if((*cursor.c.current).gridY){
										--(*cursor.c.current).gridY;
										++(*cursor.c.current).gridHeight;
										goto extendInGrid;
									}
									goto eventLoop;
								}
								case ExtendDownCommand:{
									if((*cursor.c.current).gridY + (*cursor.c.current).gridHeight < gridHeight){
										++(*cursor.c.current).gridHeight;
										goto extendInGrid;
									}
									goto eventLoop;
								}
								case ExtendLeftCommand:{
									if((*cursor.c.current).gridX){
										--(*cursor.c.current).gridX;
										++(*cursor.c.current).gridWidth;
										goto extendInGrid;
									}
									goto eventLoop;
								}
								case ExtendRightCommand:{
									if((*cursor.c.current).gridX + (*cursor.c.current).gridWidth < gridWidth){
										++(*cursor.c.current).gridWidth;
										goto extendInGrid;
									}
									goto eventLoop;
								}
								case ExtendUpLeftCommand:{
									if((*cursor.c.current).gridY){
										--(*cursor.c.current).gridY;
										++(*cursor.c.current).gridHeight;
										if((*cursor.c.current).gridX){
											--(*cursor.c.current).gridX;
											++(*cursor.c.current).gridWidth;
										}
										goto extendInGrid;
									}
									if((*cursor.c.current).gridX){
										--(*cursor.c.current).gridX;
										++(*cursor.c.current).gridWidth;
										goto extendInGrid;
									}
									goto eventLoop;
								}
								case ExtendUpRightCommand:{
									if((*cursor.c.current).gridY){
										--(*cursor.c.current).gridY;
										++(*cursor.c.current).gridHeight;
										if((*cursor.c.current).gridX + (*cursor.c.current).gridWidth < gridWidth){
											++(*cursor.c.current).gridWidth;
										}
										goto extendInGrid;
									}
									if((*cursor.c.current).gridX + (*cursor.c.current).gridWidth < gridWidth){
										++(*cursor.c.current).gridWidth;
										goto extendInGrid;
									}
									goto eventLoop;
								}
								case ExtendDownLeftCommand:{
									if((*cursor.c.current).gridY + (*cursor.c.current).gridHeight < gridHeight){
										++(*cursor.c.current).gridHeight;
										if((*cursor.c.current).gridX){
											--(*cursor.c.current).gridX;
											++(*cursor.c.current).gridWidth;
										}
										goto extendInGrid;
									}
									if((*cursor.c.current).gridX){
										--(*cursor.c.current).gridX;
										++(*cursor.c.current).gridWidth;
										goto extendInGrid;
									}
									goto eventLoop;
								}
								default:{
									if((*cursor.c.current).gridY + (*cursor.c.current).gridHeight < gridHeight){
										++(*cursor.c.current).gridHeight;
										if((*cursor.c.current).gridX + (*cursor.c.current).gridWidth < gridWidth){
											++(*cursor.c.current).gridWidth;
										}
										goto extendInGrid;
									}
									if((*cursor.c.current).gridX + (*cursor.c.current).gridWidth < gridWidth){
										++(*cursor.c.current).gridWidth;
										extendInGrid:{
											if(pointerInfo(ExtendInGrid)){
												cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
											}else{
												cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
											}
											moveContainerToGridPosition(cursor.c.current, cursor.m.current, gridWidth, gridHeight, border.x, border.y);
										}
									}
									goto eventLoop;
								}
							}
						}
					}
					default:{
						TilingResize *const resize = malloc(containerAmount * sizeof(TilingResize));
						Command command1 = NoCommand;
						if(!resize){
							printError("ram is full, could not resize tiling window");
							goto eventLoop;
						}
						XGetGeometry(display, event.xany.window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
						current = getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
						cursor.m.current = cursor.m.start + current;
						switch(command){
							case ExtendUpCommand:{
								if(y > (*cursor.m.current).y + (int)gapsY){
									break;
								}
								goto eventLoop;
							}
							case ExtendDownCommand:{
								if(y + (int)height < (*cursor.m.current).y + (*cursor.m.current).height - (int)gapsY){
									break;
								}
								goto eventLoop;
							}
							case ExtendLeftCommand:{
								if(x > (*cursor.m.current).x + (int)gapsX){
									break;
								}
								goto eventLoop;
							}
							case ExtendRightCommand:{
								if(x + (int)width < (*cursor.m.current).x + (*cursor.m.current).width - (int)gapsX){
									break;
								}
								goto eventLoop;
							}
							case ExtendUpLeftCommand:{
								const bool extendLeft = x > (*cursor.m.current).x + (int)gapsX;
								if(y > (*cursor.m.current).y + (int)gapsY){
									if(extendLeft){
										if(tilingPrioritize(ExtendUpLeftY)){
											command = ExtendUpCommand;
											command1 = ExtendLeftCommand;
										}else{
											command = ExtendLeftCommand;
											command1 = ExtendUpCommand;
										}
										break;
									}
									command = ExtendUpCommand;
									break;
								}else if(extendLeft){
									command = ExtendLeftCommand;
									break;
								}
								goto eventLoop;
							}
							case ExtendUpRightCommand:{
								const bool extendRight = x + (int)width < (*cursor.m.current).x + (*cursor.m.current).width - (int)gapsX;
								if(y > (*cursor.m.current).y + (int)gapsY){
									if(extendRight){
										if(tilingPrioritize(ExtendUpRightY)){
											command = ExtendUpCommand;
											command1 = ExtendRightCommand;
										}else{
											command = ExtendRightCommand;
											command1 = ExtendUpCommand;
										}
										break;
									}
									command = ExtendUpCommand;
									break;
								}else if(extendRight){
									command = ExtendRightCommand;
									break;
								}
								goto eventLoop;
							}
							case ExtendDownLeftCommand:{
								const bool extendLeft = x > (*cursor.m.current).x + (int)gapsX;
								if(y + (int)height < (*cursor.m.current).y + (*cursor.m.current).height - (int)gapsY){
									if(extendLeft){
										if(tilingPrioritize(ExtendUpLeftY)){
											command = ExtendDownCommand;
											command1 = ExtendLeftCommand;
										}else{
											command = ExtendLeftCommand;
											command1 = ExtendDownCommand;
										}
										break;
									}
									command = ExtendDownCommand;
									break;
								}else if(extendLeft){
									command = ExtendLeftCommand;
									break;
								}
								goto eventLoop;
							}
							default:{
								const bool extendRight = x + (int)width < (*cursor.m.current).x + (*cursor.m.current).width - (int)gapsX;
								if(y + (int)height < (*cursor.m.current).y + (*cursor.m.current).height - (int)gapsY){
									if(extendRight){
										if(tilingPrioritize(ExtendUpRightY)){
											command = ExtendDownCommand;
											command1 = ExtendRightCommand;
										}else{
											command = ExtendRightCommand;
											command1 = ExtendDownCommand;
										}
										break;
									}
									command = ExtendDownCommand;
									break;
								}else if(extendRight){
									command = ExtendRightCommand;
									break;
								}
								goto eventLoop;
							}
						}
						{
							const int *position0;
							const Container *containerCurrent1;
							const int *position2;
							const int *position3;
							const unsigned int *size0;
							const int *position4;
							const int *position5;
							const unsigned int *size1;
							const unsigned int *size2;
							const unsigned int *size3;
							const TilingResize *const resizeWall = resize + containerAmount;
							TilingResize *resizeCurrent;
							int x1;
							int y1;
							unsigned int width1;
							unsigned int height1;
							int *position1;
							TilingResize *resizeCurrent1;
							int x2;
							int y2;
							unsigned int width2;
							unsigned int height2;
							unsigned int separationWidth;
							unsigned int customExtend;
							unsigned int tilingMinimum;
							unsigned int resizeAmount = 0;
							unsigned int offset;
							unsigned int *size4;
							unsigned int currentResize;
							extendTiling:{
								switch(command){
									case ExtendUpCommand:{
										position2 = &y1;
										position3 = &y2;
										size0 = &height2;
										offset = 1;
										goto verticalExtension;
									}
									case ExtendDownCommand:{
										position2 = &y2;
										position3 = &y1;
										size0 = &height1;
										offset = 0;
										verticalExtension:{
											position0 = &y1;
											position1 = &y;
											separationWidth = gapsY;
											position4 = &x2;
											position5 = &x1;
											size1 = &width1;
											size2 = &width2;
											size3 = &height2;
											customExtend = tilingExtendHeight;
											tilingMinimum = tilingMinimumHeight;
											size4 = &height;
										}
										break;
									}
									case ExtendLeftCommand:{
										position2 = &x1;
										position3 = &x2;
										size0 = &width2;
										offset = 1;
										goto horizontalExtension;
									}
									default:{
										position2 = &x2;
										position3 = &x1;
										size0 = &width1;
										offset = 0;
										horizontalExtension:{
											position0 = &x1;
											position1 = &x;
											separationWidth = gapsX;
											position4 = &y2;
											position5 = &y1;
											size1 = &height1;
											size2 = &height2;
											size3 = &width2;
											customExtend = tilingExtendWidth;
											tilingMinimum = tilingMinimumWidth;
											size4 = &width;
										}
										break;
									}
								}
								if(option(TilingUseSeparators)){
									separationWidth = 2 * (separationWidth + separatorBorder) + separatorWidth;
								}
								resizeCurrent = resize;
								setResize0:{
									*resizeCurrent = NoTilingResize;
									if(++resizeCurrent < resizeWall){
										goto setResize0;
									}
								}
								resizeCurrent = resize;
								cursor.c.current = cursor.c.start;
								addWindowToListExtend:{
									if(*resizeCurrent == NoTilingResize){
										XGetGeometry(display, (*cursor.c.current).window, &genericWindow, &x1, &y1, &width1, &height1, &genericBorder, &genericDepth);
										if(*position0 == *position1 && getCurrentWindowMonitor((*cursor.c.current).window, cursor.m.start, monitorAmount) == current){
											resizeCurrent1 = resize;
											containerCurrent1 = cursor.c.start;
											addOpposingWindowToListExtend:{
												if(*resizeCurrent1 == NoTilingResize){
													XGetGeometry(display, (*containerCurrent1).window, &genericWindow, &x2, &y2, &width2, &height2, &genericBorder, &genericDepth);
													if(*position2 == *position3 + (int)(*size0 + separationWidth)){
														if(closedOpenInterval(*position4, *position5, *position5 + (int)*size1) || closedOpenInterval(*position4 + (int)*size2, *position5, *position5 + (int)*size1) || closedOpenInterval(*position5, *position4, *position4 + (int)*size2)){
															if(getCurrentWindowMonitor((*containerCurrent1).window, cursor.m.start, monitorAmount) == current){
																if(*size3 - customExtend < tilingMinimum){
																	customExtend = *size3 - tilingMinimum;
																	if(!customExtend){
																		goto extendTilingLoopControl;
																	}
																}
																*resizeCurrent1 = ShrinkTilingResize;
																++resizeAmount;
															}
														}
													}
												}
												if(++resizeCurrent1 < resizeWall){
													++containerCurrent1;
													goto addOpposingWindowToListExtend;
												}
											}
											*resizeCurrent = ExtendTilingResize;
											++resizeAmount;
										}
									}
									if(++resizeCurrent < resizeWall){
										++cursor.c.current;
										goto addWindowToListExtend;
									}
								}
								if(resizeAmount){
									resizeCurrent = resize;
									offset *= customExtend;
									currentResize = 0;
									resizeExtendWindowTiling:{
										if(*resizeCurrent != NoTilingResize){
											cursor.c.current = cursor.c.start + (resizeCurrent - resize);
											XGetGeometry(display, (*cursor.c.current).window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
											*position1 += *resizeCurrent / 2 * customExtend - offset;
											*size4 += customExtend - *resizeCurrent * customExtend;
											XMoveResizeWindow(display, (*cursor.c.current).window, x, y, width, height);
											XResizeWindow(display, (*cursor.c.current).subwindow, width - border.x, height - border.y);
											if(++currentResize == resizeAmount){
												goto extendTilingLoopControl;
											}
										}
										++resizeCurrent;
										goto resizeExtendWindowTiling;
									}
								}
								extendTilingLoopControl:{
									if(command1){
										command = command1;
										command1 = NoCommand;
										goto extendTiling;
									}
								}
							}
						}
						free(resize);
						goto eventLoop;
					}
				}
			}
		}
		goto eventLoop;
		shrinkCommand:{
			if(findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if((*cursor.c.current).option & MaximizedContainerOption){
					goto eventLoop;
				}
				switch(managementMode){
					case FloatingManagementMode:{
						if((*cursor.c.current).option & InGridContainerOption){
							goto shrinkGriddingInGrid;
						}
						XGetGeometry(display, event.xany.window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
						switch(command){
							case ShrinkUpCommand:
							case ShrinkDownCommand:{
								if(height > floatingMinimumHeight){
									if(command(ShrinkDown)){
										y += floatingShrinkHeight;
									}
									height -= floatingShrinkHeight;
									if((int)height < (int)floatingMinimumHeight){
										if(command(ShrinkDown)){
											y -= floatingMinimumHeight - height;
										}
										height = floatingMinimumHeight;
									}
									goto extendShrinkFloating;
								}
								goto eventLoop;
							}
							case ShrinkLeftCommand:
							case ShrinkRightCommand:{
								if(width > floatingMinimumWidth){
									if(command(ShrinkRight)){
										x += floatingShrinkWidth;
									}
									width -= floatingShrinkWidth;
									if((int)width < (int)floatingMinimumWidth){
										if(command(ShrinkRight)){
											x -= floatingMinimumWidth - width;
										}
										width = floatingMinimumWidth;
									}
									goto extendShrinkFloating;
								}
								goto eventLoop;
							}
							default:{
								if(height > floatingMinimumHeight){
									if(command >= ShrinkDownLeftCommand){
										y += floatingShrinkHeight;
									}
									height -= floatingShrinkHeight;
									if((int)height < (int)floatingMinimumHeight){
										if(command >= ShrinkDownLeftCommand){
											y -= floatingMinimumHeight - height;
										}
										height = floatingMinimumHeight;
									}
									if(width > floatingMinimumWidth){
										goto shrinkWidthFloating;
									}
									goto extendShrinkFloating;
								}
								if(width > floatingMinimumWidth){
									shrinkWidthFloating:{
										if(command(ShrinkUpRight) || command(ShrinkDownRight)){
											x += floatingShrinkWidth;
										}
										width -= floatingShrinkWidth;
										if((int)width < (int)floatingMinimumWidth){
											if(command(ShrinkUpRight) || command(ShrinkDownRight)){
												x -= floatingMinimumWidth - width;
											}
											width = floatingMinimumWidth;
										}
									}
									extendShrinkFloating:{
										XRaiseWindow(display, event.xany.window);
										XMoveResizeWindow(display, event.xany.window, x, y, width, height);
										XResizeWindow(display, (*cursor.c.current).subwindow, width - border.x, height - border.y);
									}
								}
								goto eventLoop;
							}
						}
					}
					case GriddingManagementMode:{
						shrinkGriddingInGrid:{
							switch(command){
								case ShrinkUpCommand:
								case ShrinkDownCommand:{
									if((*cursor.c.current).gridHeight > 1){
										if(command(ShrinkDown)){
											++(*cursor.c.current).gridY;
										}
										--(*cursor.c.current).gridHeight;
										goto shrinkInGrid;
									}
									goto eventLoop;
								}
								case ShrinkLeftCommand:
								case ShrinkRightCommand:{
									if((*cursor.c.current).gridWidth > 1){
										if(command(ShrinkRight)){
											++(*cursor.c.current).gridX;
										}
										--(*cursor.c.current).gridWidth;
										goto shrinkInGrid;
									}
									goto eventLoop;
								}
								default:{
									if((*cursor.c.current).gridHeight > 1){
										if(command >= ShrinkDownLeftCommand){
											++(*cursor.c.current).gridY;
										}
										--(*cursor.c.current).gridHeight;
										if((*cursor.c.current).gridWidth > 1){
											goto shrinkWidthInGrid;
										}
										goto shrinkInGrid;
									}
									if((*cursor.c.current).gridWidth > 1){
										shrinkWidthInGrid:{
											if(command(ShrinkUpRight) || command(ShrinkDownRight)){
												++(*cursor.c.current).gridX;
											}
											--(*cursor.c.current).gridWidth;
										}
										shrinkInGrid:{
											if(pointerInfo(ShrinkInGrid)){
												cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
											}else{
												cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
											}
											moveContainerToGridPosition(cursor.c.current, cursor.m.current, gridWidth, gridHeight, border.x, border.y);
										}
									}
									goto eventLoop;
								}
							}
						}
					}
					default:{
						TilingResize *const resize = malloc(containerAmount * sizeof(TilingResize));
						Command command1 = NoCommand;
						if(!resize){
							printError("ram is full, could not resize tiling window");
							goto eventLoop;
						}
						XGetGeometry(display, event.xany.window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
						current = getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
						cursor.m.current = cursor.m.start + current;
						switch(command){
							case ShrinkUpCommand:{
								if(y + (int)height < (*cursor.m.current).y + (*cursor.m.current).height - (int)gapsY && height > tilingMinimumHeight){
									break;
								}
								goto eventLoop;
							}
							case ShrinkDownCommand:{
								if(y > (*cursor.m.current).y + (int)gapsY && height > tilingMinimumHeight){
									break;
								}
								goto eventLoop;
							}
							case ShrinkLeftCommand:{
								if(x + (int)width < (*cursor.m.current).x + (*cursor.m.current).width - (int)gapsX && width > tilingMinimumWidth){
									break;
								}
								goto eventLoop;
							}
							case ShrinkRightCommand:{
								if(x > (*cursor.m.current).x + (int)gapsX && width > tilingMinimumWidth){
									break;
								}
								goto eventLoop;
							}
							case ShrinkUpLeftCommand:{
								const bool shrinkLeft = x > (*cursor.m.current).x + (int)gapsX && width > tilingMinimumWidth;
								if(y > (*cursor.m.current).y + (int)gapsY && height > tilingMinimumHeight){
									if(shrinkLeft){
										if(tilingPrioritize(ShrinkUpLeftY)){
											command = ShrinkUpCommand;
											command1 = ShrinkLeftCommand;
										}else{
											command = ShrinkLeftCommand;
											command1 = ShrinkUpCommand;
										}
										break;
									}
									command = ShrinkUpCommand;
									break;
								}else if(shrinkLeft){
									command = ShrinkLeftCommand;
									break;
								}
								goto eventLoop;
							}
							case ShrinkUpRightCommand:{
								const bool shrinkRight = x + (int)width < (*cursor.m.current).x + (*cursor.m.current).width - (int)gapsX && width > tilingMinimumWidth;
								if(y > (*cursor.m.current).y + (int)gapsY && height > tilingMinimumHeight){
									if(shrinkRight){
										if(tilingPrioritize(ShrinkUpRightY)){
											command = ShrinkUpCommand;
											command1 = ShrinkRightCommand;
										}else{
											command = ShrinkRightCommand;
											command1 = ShrinkUpCommand;
										}
										break;
									}
									command = ShrinkUpCommand;
									break;
								}else if(shrinkRight){
									command = ShrinkRightCommand;
									break;
								}
								goto eventLoop;
							}
							case ShrinkDownLeftCommand:{
								const bool shrinkLeft = x > (*cursor.m.current).x + (int)gapsX && width > tilingMinimumWidth;
								if(y + (int)height < (*cursor.m.current).y + (*cursor.m.current).height - (int)gapsY && height > tilingMinimumHeight){
									if(shrinkLeft){
										if(tilingPrioritize(ShrinkDownLeftY)){
											command = ShrinkDownCommand;
											command1 = ShrinkLeftCommand;
										}else{
											command = ShrinkLeftCommand;
											command1 = ShrinkDownCommand;
										}
										break;
									}
									command = ShrinkDownCommand;
									break;
								}else if(shrinkLeft){
									command = ShrinkLeftCommand;
									break;
								}
								goto eventLoop;
							}
							default:{
								const bool shrinkRight = x + (int)width < (*cursor.m.current).x + (*cursor.m.current).width - (int)gapsX && width > tilingMinimumWidth;
								if(y + (int)height < (*cursor.m.current).y + (*cursor.m.current).height - (int)gapsY && height > tilingMinimumHeight){
									if(shrinkRight){
										if(tilingPrioritize(ShrinkDownRightY)){
											command = ShrinkDownCommand;
											command1 = ShrinkRightCommand;
										}else{
											command = ShrinkRightCommand;
											command1 = ShrinkDownCommand;
										}
										break;
									}
									command = ShrinkDownCommand;
									break;
								}else if(shrinkRight){
									command = ShrinkRightCommand;
									break;
								}
								goto eventLoop;
							}
						}
						{
							const int *position0;
							const Container *containerCurrent1;
							const int *position2;
							const int *position3;
							const unsigned int *size1;
							const int *position4;
							const int *position5;
							const unsigned int *size2;
							const unsigned int *size3;
							const TilingResize *const resizeWall = resize + containerAmount;
							TilingResize *resizeCurrent;
							int x1;
							int y1;
							unsigned int width1;
							unsigned int height1;
							int *position1;
							unsigned int *size0;
							unsigned int customShrink;
							unsigned int tilingMinimum;
							TilingResize *resizeCurrent1;
							int x2;
							int y2;
							unsigned int width2;
							unsigned int height2;
							unsigned int separationWidth;
							unsigned int resizeAmount = 0;
							unsigned int offset;
							unsigned int currentResize = 0;
							shrinkTiling:{
								switch(command){
									case ShrinkUpCommand:{
										position2 = &y2;
										position3 = &y1;
										size1 = &height1;
										offset = 1;
										goto verticalShrinkage;
									}
									case ShrinkDownCommand:{
										position2 = &y1;
										position3 = &y2;
										size1 = &height2;
										offset = 0;
										verticalShrinkage:{
											position0 = &y1;
											position1 = &y;
											size0 = &height;
											customShrink = tilingShrinkHeight;
											tilingMinimum = tilingMinimumHeight;
											separationWidth = gapsY;
											position4 = &x2;
											position5 = &x1;
											size2 = &width1;
											size3 = &width2;
										}
										break;
									}
									case ShrinkLeftCommand:{
										position2 = &x2;
										position3 = &x1;
										size1 = &width1;
										offset = 1;
										goto horizontalShrinkage;
									}
									default:{
										position2 = &x1;
										position3 = &x2;
										size1 = &width2;
										offset = 0;
										horizontalShrinkage:{
											position0 = &x1;
											position1 = &x;
											size0 = &width;
											customShrink = tilingShrinkWidth;
											tilingMinimum = tilingMinimumWidth;
											separationWidth = gapsX;
											position4 = &y2;
											position5 = &y1;
											size2 = &height1;
											size3 = &height2;
										}
										break;
									}
								}
								if(option(TilingUseSeparators)){
									separationWidth = 2 * (separationWidth + separatorBorder) + separatorWidth;
								}
								resizeCurrent = resize;
								setResize1:{
									*resizeCurrent = NoTilingResize;
									if(++resizeCurrent < resizeWall){
										goto setResize1;
									}
								}
								resizeCurrent = resize;
								cursor.c.current = cursor.c.start;
								addWindowToListShrink:{
									if(*resizeCurrent == NoTilingResize){
										XGetGeometry(display, (*cursor.c.current).window, &genericWindow, &x1, &y1, &width1, &height1, &genericBorder, &genericDepth);
										if(*position0 == *position1 && getCurrentWindowMonitor((*cursor.c.current).window, cursor.m.start, monitorAmount) == current){
											if(*size0 - customShrink < tilingMinimum){
												customShrink = *size0 - tilingMinimum;
												if(!customShrink){
													goto shrinkTilingLoopControl;
												}
											}
											resizeCurrent1 = resize;
											containerCurrent1 = cursor.c.start;
											addOpposingWindowToListShrink:{
												if(*resizeCurrent1 == NoTilingResize){
													XGetGeometry(display, (*containerCurrent1).window, &genericWindow, &x2, &y2, &width2, &height2, &genericBorder, &genericDepth);
													if(*position2 == *position3 + (int)(*size1 + separationWidth)){
														if(closedOpenInterval(*position4, *position5, *position5 + (int)*size2) || closedOpenInterval(*position4 + (int)*size3, *position5, *position5 + (int)*size2) || closedOpenInterval(*position5, *position4, *position4 + (int)*size3)){
															if(getCurrentWindowMonitor((*containerCurrent1).window, cursor.m.start, monitorAmount) == current){
																*resizeCurrent1 = ExtendTilingResize;
																++resizeAmount;
															}
														}
													}
												}
												if(++resizeCurrent1 < resizeWall){
													++containerCurrent1;
													goto addOpposingWindowToListShrink;
												}
											}
											*resize = ShrinkTilingResize;
											++resizeAmount;
										}
									}
									if(++resizeCurrent < resizeWall){
										++cursor.c.current;
										goto addWindowToListShrink;
									}
								}
								if(resizeAmount){
									resizeCurrent = resize;
									offset *= customShrink;
									currentResize = 0;
									resizeShrinkWindowTiling:{
										if(*resizeCurrent != NoTilingResize){
											cursor.c.current = cursor.c.start + (resizeCurrent - resize);
											XGetGeometry(display, (*cursor.c.current).window, &genericWindow, &x, &y, &width, &height, &genericBorder, &genericDepth);
											*position1 += *resizeCurrent / 2 * customShrink - offset;
											*size0 += customShrink - *resizeCurrent * customShrink;
											XMoveResizeWindow(display, (*cursor.c.current).window, x, y, width, height);
											XResizeWindow(display, (*cursor.c.current).subwindow, width - border.x, height - border.y);
											if(++currentResize == resizeAmount){
												goto shrinkTilingLoopControl;
											}
										}
										++resizeCurrent;
										goto resizeShrinkWindowTiling;
									}
								}
								shrinkTilingLoopControl:{
									if(command1){
										command = command1;
										command1 = NoCommand;
										goto shrinkTiling;
									}
								}
							}
						}
						free(resize);
						goto eventLoop;
					}
				}
			}
		}
		goto eventLoop;
		fullscreenBigscreenCommand:{
			if(findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if(pointerInfo(Maximize)){
					current = getCurrentPointerMonitor(cursor.m.start, monitorAmount);
				}else{
					current = getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
				}
				cursor.mc.current = cursor.mc.start + current;
				if((*cursor.mc.current).window){
					genericWindow = (*cursor.mc.current).window;
					unmaximizeContainer(focused, monitorAmount, border.x, border.y, _NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, cursor.c.current, cursor.mc.start);
					if(genericWindow == event.xany.window){
						goto eventLoop;
					}
				}
				maximizeContainer(command, cursor.m.start + current, managementMode, &color, _NET.WM.STATE.this, _NET.WM.STATE.FULLSCREEN, border.x, border.y, focused, cursor.c.current, cursor.mc.current);
			}
		}
		goto eventLoop;
		detachCommand:{
			if(findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				if(pointerInfo(Detach)){
					cursor.m.current = cursor.m.start + getCurrentPointerMonitor(cursor.m.start, monitorAmount);
				}else{
					cursor.m.current = cursor.m.start + getCurrentWindowMonitor(event.xany.window, cursor.m.start, monitorAmount);
				}
				width = (*cursor.m.current).width / floatingWindowDivisor;
				height = (*cursor.m.current).height / floatingWindowDivisor;
				genericWindow = (*cursor.c.current).subwindow;
				XSelectInput(display, genericWindow, NoEventMask);
				XReparentWindow(display, genericWindow, rootWindow, (*cursor.m.current).x + ((*cursor.m.current).width - width) / 2, (*cursor.m.current).y + ((*cursor.m.current).height - height) / 2);
				XResizeWindow(display, genericWindow, width, height);
				XSetInputFocus(display, rootWindow, RevertToPointerRoot, CurrentTime);
				if(managementMode(Tiling)){
					removeTilingWindow();
				}
				if(cursor.c.current == focused){
					focused = NULL;
				}
				goto destroyWindow;
			}
		}
		goto eventLoop;
		closeCommand:{
			if(findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				e.xclient.type = ClientMessage;
				e.xclient.send_event = False;
				e.xclient.display = display;
				e.xclient.window = (*(cursor.c.start + current)).subwindow;
				e.xclient.message_type = WM.PROTOCOLS;
				e.xclient.format = 32;
				*e.xclient.data.l = WM.DELETE_WINDOW;
				*(e.xclient.data.l + 1) = CurrentTime;
				XSendEvent(display, e.xclient.window, False, PropertyChangeMask, &e);
			}
		}
		goto eventLoop;
		killCommand:{
			if(findWindow(event.xany.window, &(*cursor.c.start).window, sizeof(Container), containerAmount, &current)){
				cursor.c.current = cursor.c.start + current;
				XKillClient(display, (*cursor.c.current).subwindow);
				XSetInputFocus(display, rootWindow, RevertToPointerRoot, CurrentTime);
				if(managementMode(Tiling)){
					removeTilingWindow();
				}
				if(cursor.c.current == focused){
					focused = NULL;
				}
				(*cursor.c.current).option ^= MappedContainerOption;
				goto destroyWindow;
			}
		}
		goto eventLoop;
	}
	eventLoopExit:{
		if(mode(Exit)){
			if(containerAmount){
				cursor.c.current = cursor.c.start;
				returnClient:{
					XReparentWindow(display, (*cursor.c.current).subwindow, rootWindow, 0, 0);
					XDestroyWindow(display, (*cursor.c.current).window);
					if(++cursor.c.current < cursor.c.wall){
						goto returnClient;
					}
				}
			}
		}else{
			XUngrabKey(display, AnyKey, AnyModifier, rootWindow);
			XUngrabButton(display, AnyButton, AnyModifier, rootWindow);
			if(containerAmount){
				cursor.c.current = cursor.c.start;
				ungrabContainerWindow:{
					XUngrabKey(display, AnyKey, AnyModifier, (*cursor.c.current).window);
					XUngrabButton(display, AnyButton, AnyModifier, (*cursor.c.current).window);
					if(++cursor.c.current < cursor.c.wall){
						goto ungrabContainerWindow;
					}
				}
			}
		}
	}
	emergencyExit:{
		free(data);
	}
	return;
}
UNMAPALLWINDOWS_DEC{
	loop:{
		XUnmapWindow(display, (*current).window);
		if(++current < wall){
			goto loop;
		}
	}
	return;
}
MAPALLWINDOWS_DEC{
	loop:{
		XMapWindow(display, (*current).window);
		if(++current < wall){
			goto loop;
		}
	}
	return;
}
FINDWINDOW_DEC{
	bool value = 0;
	if(amount){
		unsigned int c = 0;
		loop:{
			if(*location == w){
				*current = c;
				value = 1;
			}else if(++c < amount){
				location = (Window *)((uint8_t *)location + size);
				goto loop;
			}
		}
	}
	return value;
}
UNMAXIMIZEALLCONTAINERS_DEC{
	const long int size = sizeof(Atom);
	const Atom atom = None;
	unsigned int current = 0;
	Atom type;
	int format;
	unsigned long int propertyAmount;
	unsigned long int bytesAfter;
	unsigned char *data;
	unsigned char *d;
	unsigned int currentProperty;
	findMaximized:{
		if((*maximizedContainer).window){
			if((*maximizedContainer).shouldChangeProperty){
				if(XGetWindowProperty(display, (*maximizedContainer).subwindow, _NET_WM_STATE, 0, size, False, XA_ATOM, &type, &format, &propertyAmount, &bytesAfter, &data) == Success && data){
					d = data;
					currentProperty = 0;
					findStateFullscreen:{
						if(*d == _NET_WM_STATE_FULLSCREEN){
							*d = *(data + --propertyAmount);
							*(data + propertyAmount) = None;
						}else{
							if(++currentProperty < propertyAmount){
								++d;
								goto findStateFullscreen;
							}
							--propertyAmount;
						}
					}
					if(propertyAmount){
						changeProperties((*maximizedContainer).window, (*maximizedContainer).subwindow, _NET_WM_STATE, XA_ATOM, 32, PropModeReplace, (unsigned char *)data, propertyAmount);
						XFree(data);
					}else{
						XFree(data);
						goto noProperties;
					}
				}else{
					noProperties:{
						changeProperties((*maximizedContainer).window, (*maximizedContainer).subwindow, _NET_WM_STATE, XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1);
					}
				}
			}
			(*maximizedContainer).window = None;
			(*maximizedContainer).subwindow = None;
		}
		if(++current < monitorAmount){
			++maximizedContainer;
			goto findMaximized;
		}
	}
	findMaximizedContainer:{
		if(container < containerWall){
			if((*container).option & MaximizedContainerOption){
				(*container).option ^= MaximizedContainerOption;
			}
			++container;
			goto findMaximizedContainer;
		}
	}
	return;
}
GETGRIDSLOTDATA_DEC{
	unsigned int normal = monitorWidth / gridWidth;
	unsigned int abnormal = monitorWidth - (gridWidth - 1) * normal;
	if(x){
		if(gridX > gridWidth / 2){
			*x = (gridX - 1) * normal + abnormal;
		}else{
			*x = gridX * normal;
		}
	}
	if(width){
		if(gridX == gridWidth / 2){
			*width = abnormal;
		}else{
			*width = normal;
		}
	}
	normal = monitorHeight / gridHeight;
	abnormal = monitorHeight - (gridHeight - 1) * normal;
	if(y){
		if(gridY > gridHeight / 2){
			*y = (gridY - 1) * normal + abnormal;
		}else{
			*y = gridY * normal;
		}
	}
	if(height){
		if(gridY == gridHeight / 2){
			*height = abnormal;
		}else{
			*height = normal;
		}
	}
	return;
}
CREATEGRID_DEC{
	const unsigned int middleY = gridHeight / 2;
	const unsigned int middleX = gridWidth / 2;
	const unsigned int gridBorders = 2;
	const unsigned int gridBorder = 1;
	unsigned int currentY;
	unsigned int normalHeight;
	int currentOffsetY;
	unsigned int abnormalHeight;
	int offsetY;
	unsigned int normalWidth;
	unsigned int abnormalWidth;
	int offsetX;
	unsigned int currentX;
	int currentOffsetX;
	int y;
	unsigned int height;
	int x;
	unsigned int width;
	unsigned int current = 0;
	do{
		currentY = 0;
		normalHeight = (*monitor).height / gridHeight;
		currentOffsetY = 0;
		abnormalHeight = (*monitor).height - (gridHeight - 1) * normalHeight;
		offsetY = abnormalHeight - normalHeight;
		normalWidth = (*monitor).width / gridWidth;
		abnormalWidth = (*monitor).width - (gridWidth - 1) * normalWidth;
		offsetX = abnormalWidth - normalWidth;
		do{
			currentX = 0;
			currentOffsetX = 0;
			y = currentY * normalHeight + currentOffsetY;
			if(currentY == middleY){
				currentOffsetY = offsetY;
				height = abnormalHeight;
			}else{
				height = normalHeight;
			}
			do{
				x = currentX * normalWidth + currentOffsetX;
				if(currentX == middleX){
					currentOffsetX = offsetX;
					width = abnormalWidth;
				}else{
					width = normalWidth;
				}
				XCreateSimpleWindow(display, grid[current], x, y, width - gridBorders, height - gridBorders, gridBorder, subwindowBorderColor, subwindowBackgroundColor);
			}while(++currentX < gridWidth);
		}while(++currentY < gridHeight);
		XMapSubwindows(display, grid[current]);
		++monitor;
	}while(++current < monitorAmount);
	return;
}
UNMAXIMIZECONTAINER_DEC{
	unsigned int currentMonitor;
	if(findWindow((*c).window, &(*maximizedContainer).window, sizeof(MaximizedContainer), monitorAmount, &currentMonitor)){
		const Window s = (*c).subwindow;
		const Window w = (*c).window;
		maximizedContainer += currentMonitor;
		if((*maximizedContainer).shouldChangeProperty){
			Atom type;
			int format;
			unsigned long int propertyAmount;
			unsigned long int bytesAfter;
			unsigned char *data;
			if(XGetWindowProperty(display, s, _NET_WM_STATE, 0, sizeof(Atom), False, XA_ATOM, &type, &format, &propertyAmount, &bytesAfter, &data) == Success && data){
				{
					unsigned int currentProperty = 0;
					unsigned char *d = data;
					findStateFullscreen:{
						if(*d == _NET_WM_STATE_FULLSCREEN){
							*d = *(data + --propertyAmount);
							*(data + propertyAmount) = None;
						}else{
							if(++currentProperty < propertyAmount){
								++d;
								goto findStateFullscreen;
							}
							--propertyAmount;
						}
					}
				}
				if(propertyAmount){
					changeProperties(w, s, _NET_WM_STATE, XA_ATOM, 32, PropModeReplace, (unsigned char *)data, propertyAmount);
					XFree(data);
				}else{
					XFree(data);
					goto noProperties;
				}
			}else{
				noProperties:{
					const Atom atom = None;
					changeProperties(w, s, _NET_WM_STATE, XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1);
				}
			}
		}
		if(c == focused){
			XSetWindowBackground(display, w, *((*maximizedContainer).oldBackgroundColor + 6));
		}else{
			XSetWindowBackground(display, w, *(*maximizedContainer).oldBackgroundColor);
		}
		XRaiseWindow(display, w);
		XSetWindowBorderWidth(display, w, (*maximizedContainer).oldBorder);
		XClearArea(display, w, 0, 0, 0, 0, False);
		XMoveResizeWindow(display, w, (*maximizedContainer).oldX, (*maximizedContainer).oldY, (*maximizedContainer).oldWidth, (*maximizedContainer).oldHeight);
		XResizeWindow(display, s, (*maximizedContainer).oldWidth - borderX, (*maximizedContainer).oldHeight - borderY);
		(*maximizedContainer).window = None;
		(*maximizedContainer).subwindow = None;
		(*c).option ^= MaximizedContainerOption;
	}
	return;
}
MOVECONTAINERTOGRIDPOSITION_DEC{
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	getGridSlotData((*m).width, (*m).height, (*c).gridX + (*c).gridWidth - 1, (*c).gridY + (*c).gridHeight - 1, gridWidth, gridHeight, &x, &y, &width, &height);
	width += x;
	height += y;
	getGridSlotData((*m).width, (*m).height, (*c).gridX, (*c).gridY, gridWidth, gridHeight, &x, &y, NULL, NULL);
	width -= x;
	height -= y;
	XRaiseWindow(display, (*c).window);
	XMoveResizeWindow(display, (*c).window, (*m).x + x, (*m).y + y, width, height);
	XResizeWindow(display, (*c).subwindow, width - borderX, height - borderY);
	return;
}
GETCURRENTPOINTERMONITOR_DEC{
	unsigned int current = 0;
	if(monitorAmount > 1){
		int x = 0;
		int y = 0;
		{
			Window w;
			uint32_t masks;
			XQueryPointer(display, XDefaultRootWindow(display), &w, &w, &x, &y, &x, &y, &masks);
		}
		loop:{
			if(!closedOpenInterval(x, (*monitor).x, (*monitor).x + (*monitor).width) || !closedOpenInterval(y, (*monitor).y, (*monitor).y + (*monitor).height)){
				if(++current < monitorAmount){
					++monitor;
					goto loop;
				}
				current = 0;
			}
		}
	}
	return current;
}
GETCURRENTWINDOWMONITOR_DEC{
	unsigned int monitorToUse = 0;
	if(monitorAmount > 1){
		int x;
		int y;
		unsigned int width;
		unsigned int height;
		{
			Window root;
			unsigned int border;
			unsigned int depth;
			XGetGeometry(display, w, &root, &x, &y, &width, &height, &border, &depth);
			border *= 2;
			width += border;
			height += border;
		}
		{
			unsigned int current = 0;
			unsigned int pixels0;
			unsigned int pixels1;
			unsigned int mostPixels = 0;
			loop:{
				if((*monitor).x > x + (int)width || (*monitor).x + (*monitor).width <= x || (*monitor).y > y + (int)height || (*monitor).y + (*monitor).height <= y){
					goto loopControl;
				}
				if((*monitor).x + (*monitor).width <= x + (int)width){
					pixels0 = (*monitor).x + (*monitor).width;
				}else{
					pixels0 = x + width;
				}
				if((*monitor).x > x){
					pixels0 -= (*monitor).x;
				}else{
					pixels0 -= x;
				}
				if((*monitor).y + (*monitor).height <= y + (int)height){
					pixels1 = (*monitor).y + (*monitor).height;
				}else{
					pixels1 = y + height;
				}
				if((*monitor).y > y){
					pixels1 -= (*monitor).y;
				}else{
					pixels1 -= y;
				}
				pixels0 *= pixels1;
				if(pixels0 > mostPixels){
					mostPixels = pixels0;
					monitorToUse = current;
				}
				loopControl:{
					if(++current < monitorAmount){
						++monitor;
						goto loop;
					}
				}
			}
		}
	}
	return monitorToUse;
}
GETADJACENTSURFACESIZE_DEC{
	unsigned int pixels = 0;
	if(position00 + size00 == position10){
		if(closedOpenInterval(position01, position11, position11 + size10)){
			if(position01 + size01 < position11 + size10){
				pixels = size01;
				goto emergencyExit;
			}
			pixels = position11 + size10 - position01;
			goto emergencyExit;
		}
		if(closedOpenInterval(position01 + size01, position11, position11 + size10)){
			pixels = position01 + size01 - position11;
			goto emergencyExit;
		}
		if(closedOpenInterval(position11, position01, position01 + size01)){
			pixels = size10;
		}
	}
	emergencyExit:{}
	return pixels;
}
PRINTERROR_DEC{
	if(openErrorStream){
		if((errorStream = fopen(path, "w"))){
			fprintf(errorStream, "%s: %s\n", programName, string);
			fclose(errorStream);
			goto emergencyExit;
		}
		goto emergencyExit;
	}
	fprintf(errorStream, "%s: %s\n", programName, string);
	emergencyExit:{}
	return;
}
FINDMONITOR_DEC{
	const XRRMonitorInfo *newMonitor = NULL;
	switch(adjacentMonitor){
		case NextAdjacentMonitor:{
			if(found + 1 < wall){
				newMonitor = found + 1;
			}
			goto emergencyExit;
		}
		case PreviousAdjacentMonitor:{
			if(found > start){
				newMonitor = found - 1;
			}
			goto emergencyExit;
		}
		default:{
			const XRRMonitorInfo *current = start;
			unsigned int pixels;
			unsigned int mostPixels = 0;
			switch(adjacentMonitor){
				case AboveAdjacentMonitor:{
					if((*found).y){
						goto loop;
					}
					goto emergencyExit;
				}
				case BelowAdjacentMonitor:{
					if((*found).y + (*found).height < (int)displayHeight){
						goto loop;
					}
					goto emergencyExit;
				}
				case LeftAdjacentMonitor:{
					if((*found).x){
						goto loop;
					}
					goto emergencyExit;
				}
				default:{
					if((*found).x + (*found).width < (int)displayWidth){
						loop:{
							switch(adjacentMonitor){
								case AboveAdjacentMonitor:{
									pixels = getAdjacentSurfaceSize((*current).y, (*current).x, (*current).height, (*current).width, (*found).y, (*found).x, (*found).width);
									break;
								}
								case BelowAdjacentMonitor:{
									pixels = getAdjacentSurfaceSize((*found).y, (*found).x, (*found).height, (*found).width, (*current).y, (*current).x, (*current).width);
									break;
								}
								case LeftAdjacentMonitor:{
									pixels = getAdjacentSurfaceSize((*current).x, (*current).y, (*current).width, (*current).height, (*found).x, (*found).y, (*found).height);
									break;
								}
								default:{
									pixels = getAdjacentSurfaceSize((*found).x, (*found).y, (*found).width, (*found).height, (*current).x, (*current).y, (*current).height);
									break;
								}
							}
							if(pixels > mostPixels){
								newMonitor = current;
								mostPixels = pixels;
							}
							if(++current < wall){
								goto loop;
							}
							goto emergencyExit;
						}
					}
					goto emergencyExit;
				}
			}
		}
	}
	emergencyExit:{}
	return newMonitor;
}
MOVECONTAINERTOMONITOR_DEC{
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	{
		unsigned int shadow;
		{
			Window root;
			unsigned int depth;
			XGetGeometry(display, w, &root, &x, &y, &width, &height, &shadow, &depth);
		}
		{
			unsigned int sourceReducedWidth;
			unsigned int sourceReducedHeight;
			unsigned int destinationReducedWidth;
			unsigned int destinationReducedHeight;
			if(option(FloatingFollowGrid)){
				sourceReducedWidth = (*source).width / gridWidth;
				sourceReducedHeight = (*source).height / gridHeight;
				destinationReducedWidth = (*destination).width / gridWidth;
				destinationReducedHeight = (*destination).height / gridHeight;
			}else{
				sourceReducedWidth = (*source).width / windowDivisor;
				sourceReducedHeight = (*source).height / windowDivisor;
				destinationReducedWidth = (*destination).width / windowDivisor;
				destinationReducedHeight = (*destination).height / windowDivisor;
			}
			x += shadow;
			y += shadow;
			if(x == (*source).x){
				if(width == sourceReducedWidth){
					width = destinationReducedWidth;
				}else{
					width = width * (*destination).width / (*source).width;
				}
				x = (*destination).x - shadow;
			}else if(x + (int)width == (*source).x + (int)(*source).width){
				if(width == sourceReducedWidth){
					width = destinationReducedWidth;
				}else{
					width = width * (*destination).width / (*source).width;
				}
				x = (*destination).x + (*destination).width - width - shadow;
			}else{
				x = (x - (*source).x) * (*destination).width / (*source).width + (*destination).x - shadow;
				width = width * (*destination).width / (*source).width;
			}
			if(y == (*source).y){
				if(height == sourceReducedHeight){
					height = destinationReducedHeight;
				}else{
					height = height * (*destination).height / (*source).height;
				}
				y = (*destination).y - shadow;
			}else if(y + (int)height == (*source).y + (int)(*source).height){
				if(height == sourceReducedHeight){
					height = destinationReducedHeight;
				}else{
					height = height * (*destination).height / (*source).height;
				}
				y = (*destination).y + (*destination).height - height - shadow;
			}else{
				y = (y - (*source).y) * (*destination).height / (*source).height + (*destination).y - shadow;
				height = height * (*destination).height / (*source).height;
			}
		}
	}
	if(width < minimumWidth){
		width = minimumWidth;
	}
	if(height < minimumHeight){
		height = minimumHeight;
	}
	XMoveResizeWindow(display, w, x, y, width, height);
	XResizeWindow(display, s, width - borderX, height - borderY);
	return;
}
MAXIMIZECONTAINER_DEC{
	const Window w = (*c).window;
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	unsigned int border;
	{
		Window root;
		unsigned int depth;
		XGetGeometry(display, w, &root, &x, &y, &width, &height, &border, &depth);
	}
	{
		const Window s = (*c).subwindow;
		bool isFocused = 0;
		if(focused && (*focused).window == w){
			isFocused = 1;
		}
		if(command(Fullscreen)){
			changeProperties(w, s, _NET_WM_STATE, XA_ATOM, 32, PropModeAppend, (unsigned char *)&_NET_WM_STATE_FULLSCREEN, 1);
			if(isFocused){
				XSetWindowBackground(display, w, (*color).focusedContainerBackground.fullscreen);
			}else{
				XSetWindowBackground(display, w, (*color).containerBackground.fullscreen);
			}
			(*mc).shouldChangeProperty = 1;
		}else{
			if(isFocused){
				XSetWindowBackground(display, w, (*color).focusedContainerBackground.bigscreen);
			}else{
				XSetWindowBackground(display, w, (*color).containerBackground.bigscreen);
			}
			(*mc).shouldChangeProperty = 0;
		}
		XRaiseWindow(display, w);
		if(!((*c).option & InGridContainerOption)){
			XSetWindowBorderWidth(display, w, 0);
		}
		XClearArea(display, w, 0, 0, 0, 0, False);
		XMoveResizeWindow(display, w, (*monitor).x, (*monitor).y, (*monitor).width, (*monitor).height);
		XResizeWindow(display, s, (*monitor).width - borderX, (*monitor).height - borderY);
		switch(managementMode){
			case FloatingManagementMode:{
				if((*c).option & InGridContainerOption){
					(*mc).oldBackgroundColor = &(*color).containerBackground.inGrid;
					break;
				}
				(*mc).oldBackgroundColor = &(*color).containerBackground.floating;
				break;
			}
			case GriddingManagementMode:{
				(*mc).oldBackgroundColor = &(*color).containerBackground.gridding;
				break;
			}
			default:{
				(*mc).oldBackgroundColor = &(*color).containerBackground.tiling;
				break;
			}
		}
		(*mc).window = w;
		(*mc).subwindow = s;
		(*mc).oldX = x;
		(*mc).oldY = y;
		(*mc).oldWidth = width;
		(*mc).oldHeight = height;
		(*mc).oldBorder = border;
		(*c).option |= MaximizedContainerOption;
	}
	return;
}
