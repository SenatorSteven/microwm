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

#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <xcb/xcb.h>
#include <xcb/randr.h>
#include "headers/defines.h"
#include "headers/eventLoop.h"
#include "headers/printEvent.h"

#define SYSTEM_FAIL /*-------------------------------------*/ -1

#define ONE32 /*-------------------------------------------*/ 1
#define ONE64 /*-------------------------------------------*/ 1L

#define MOTIONOPTIONONE /*---------------------------------*/ ONE32
#define OPTIONONE /*---------------------------------------*/ ONE64
#define POINTERINFOONE /*----------------------------------*/ ONE32
#define CASCADEINFOONE /*----------------------------------*/ ONE32
#define TILINGPRIORITIZATIONONE /*-------------------------*/ ONE32
#define CONTAINEROPTIONONE /*------------------------------*/ ONE32
#define ENTERINPUTEXCEPTIONONE /*--------------------------*/ ONE32
#define ENTERINPUTMETHODONE /*-----------------------------*/ ONE32
#define FLAGONE /*-----------------------------------------*/ ONE32

#define XCB_CONFIG_WINDOW_X_Y /*---------------------------*/ (XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y)
#define XCB_CONFIG_WINDOW_X_WIDTH /*-----------------------*/ (XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_WIDTH)
#define XCB_CONFIG_WINDOW_Y_HEIGHT /*----------------------*/ (XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_HEIGHT)
#define XCB_CONFIG_WINDOW_X_WIDTH_HEIGHT /*----------------*/ (XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT)
#define XCB_CONFIG_WINDOW_Y_WIDTH_HEIGHT /*----------------*/ (XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT)
#define XCB_CONFIG_WINDOW_WIDTH_HEIGHT /*------------------*/ (XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT)
#define XCB_CONFIG_WINDOW_WIDTH_HEIGHT_BORDER /*-----------*/ (XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT | XCB_CONFIG_WINDOW_BORDER_WIDTH)
#define XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT /*--------------*/ (XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT)
#define XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT_BORDER /*-------*/ (XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT | XCB_CONFIG_WINDOW_BORDER_WIDTH)
#define XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT_STACK /*--------*/ (XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT | XCB_CONFIG_WINDOW_STACK_MODE)
#define XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT_BORDER_STACK /*-*/ (XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT | XCB_CONFIG_WINDOW_BORDER_WIDTH | XCB_CONFIG_WINDOW_STACK_MODE)

#ifdef XCB_RANDR_SCREEN_CHANGE_NOTIFY
	#undef XCB_RANDR_SCREEN_CHANGE_NOTIFY
#endif
#define XCB_RANDR_SCREEN_CHANGE_NOTIFY /*------------------*/ 89

#define NoCommand /*---------------------------------------*/ 0
#define ExecuteCommand /*----------------------------------*/ 1
#define FloatingModeCommand /*-----------------------------*/ 2
#define GriddingModeCommand /*-----------------------------*/ 3
#define TilingModeCommand /*-------------------------------*/ 4
#define CancelMoveResizeCommand /*-------------------------*/ 5
#define ShowGridCommand /*---------------------------------*/ 6
#define HideGridCommand /*---------------------------------*/ 7
#define ToggleGridVisibilityCommand /*---------------------*/ 8
#define EnlargeGridXCommand /*-----------------------------*/ 9
#define EnlargeGridYCommand /*-----------------------------*/ 10
#define EnlargeGridEitherCommand /*------------------------*/ 11
#define EnlargeGridBothCommand /*--------------------------*/ 12
#define ShrinkGridXCommand /*------------------------------*/ 13
#define ShrinkGridYCommand /*------------------------------*/ 14
#define ShrinkGridEitherCommand /*-------------------------*/ 15
#define ShrinkGridBothCommand /*---------------------------*/ 16
#define ToggleGapsCommand /*-------------------------------*/ 17
#define CascadeCommand /*----------------------------------*/ 18
#define AttachCommand /*-----------------------------------*/ 19
#define SwapNextMonitorCommand /*--------------------------*/ 20
#define SwapPreviousMonitorCommand /*----------------------*/ 21
#define SwapAboveMonitorCommand /*-------------------------*/ 22
#define SwapBelowMonitorCommand /*-------------------------*/ 23
#define SwapLeftMonitorCommand /*--------------------------*/ 24
#define SwapRightMonitorCommand /*-------------------------*/ 25
#define RevolveMonitorsNextCommand /*----------------------*/ 26
#define RevolveMonitorsPreviousCommand /*------------------*/ 27
#define RevolveMonitorsAboveCommand /*---------------------*/ 28
#define RevolveMonitorsBelowCommand /*---------------------*/ 29
#define RevolveMonitorsLeftCommand /*----------------------*/ 30
#define RevolveMonitorsRightCommand /*---------------------*/ 31
#define RestartCommand /*----------------------------------*/ 32
#define ExitCommand /*-------------------------------------*/ 33
#define MoveCommand /*-------------------------------------*/ 34
#define ResizeCommand /*-----------------------------------*/ 35
#define MoveResizeCommand /*-------------------------------*/ 36
#define MoveTopCommand /*----------------------------------*/ 37
#define MoveBottomCommand /*-------------------------------*/ 38
#define MoveLeftCommand /*---------------------------------*/ 39
#define MoveRightCommand /*--------------------------------*/ 40
#define MoveTopLeftCommand /*------------------------------*/ 41
#define MoveTopRightCommand /*-----------------------------*/ 42
#define MoveBottomLeftCommand /*---------------------------*/ 43
#define MoveBottomRightCommand /*--------------------------*/ 44
#define MoveCenterCommand /*-------------------------------*/ 45
#define MoveFullCommand /*---------------------------------*/ 46
#define MoveNextMonitorCommand /*--------------------------*/ 47
#define MovePreviousMonitorCommand /*----------------------*/ 48
#define MoveAboveMonitorCommand /*-------------------------*/ 49
#define MoveBelowMonitorCommand /*-------------------------*/ 50
#define MoveLeftMonitorCommand /*--------------------------*/ 51
#define MoveRightMonitorCommand /*-------------------------*/ 52
#define AddToGridCommand /*--------------------------------*/ 53
#define RemoveFromGridCommand /*---------------------------*/ 54
#define ToggleAddRemoveGridCommand /*----------------------*/ 55
#define MoveUpGridCommand /*-------------------------------*/ 56
#define MoveDownGridCommand /*-----------------------------*/ 57
#define MoveLeftGridCommand /*-----------------------------*/ 58
#define MoveRightGridCommand /*----------------------------*/ 59
#define ExtendUpCommand /*---------------------------------*/ 60
#define ExtendDownCommand /*-------------------------------*/ 61
#define ExtendLeftCommand /*-------------------------------*/ 62
#define ExtendRightCommand /*------------------------------*/ 63
#define ExtendUpLeftCommand /*-----------------------------*/ 64
#define ExtendUpRightCommand /*----------------------------*/ 65
#define ExtendDownLeftCommand /*---------------------------*/ 66
#define ExtendDownRightCommand /*--------------------------*/ 67
#define ShrinkUpCommand /*---------------------------------*/ 68
#define ShrinkDownCommand /*-------------------------------*/ 69
#define ShrinkLeftCommand /*-------------------------------*/ 70
#define ShrinkRightCommand /*------------------------------*/ 71
#define ShrinkUpLeftCommand /*-----------------------------*/ 72
#define ShrinkUpRightCommand /*----------------------------*/ 73
#define ShrinkDownLeftCommand /*---------------------------*/ 74
#define ShrinkDownRightCommand /*--------------------------*/ 75
#define FullscreenCommand /*-------------------------------*/ 76
#define BigscreenCommand /*--------------------------------*/ 77
#define DetachCommand /*-----------------------------------*/ 78
#define CloseCommand /*------------------------------------*/ 79
#define KillCommand /*-------------------------------------*/ 80

#define RootCommandCeiling /*------------------------------*/ ExitCommand

#define NoneMotionAction /*--------------------------------*/ 0
#define MoveMotionAction /*--------------------------------*/ 1
#define ResizeMotionAction /*------------------------------*/ 2

#define NoneMotionOption /*--------------------------------*/ 0
#define LockedXMotionOption /*-----------------------------*/ (MOTIONOPTIONONE << 0)
#define LockedYMotionOption /*-----------------------------*/ (MOTIONOPTIONONE << 1)
#define SnappingMappedMotionOption /*----------------------*/ (MOTIONOPTIONONE << 2)

#define NoneOption /*--------------------------------------*/ 0
#define FloatingUseFocusedWindowColorOption /*-------------*/ (OPTIONONE << 0)
#define FloatingFollowGridOption /*------------------------*/ (OPTIONONE << 1)
#define FloatingMinimalMoveOption /*-----------------------*/ (OPTIONONE << 2)
#define FloatingMinimalResizeOption /*---------------------*/ (OPTIONONE << 3)
#define FloatingAllowMonitorStickingOption /*--------------*/ (OPTIONONE << 4)
#define FloatingAllowSnappingOption /*---------------------*/ (OPTIONONE << 5)
#define FloatingUseSnappingWindowOption /*-----------------*/ (OPTIONONE << 6)
#define FloatingSnappingWindowFollowGridOption /*----------*/ (OPTIONONE << 7)
#define FloatingPortWindowsFromGriddingOption /*-----------*/ (OPTIONONE << 8)
#define FloatingAllowResizeOpposingOption /*---------------*/ (OPTIONONE << 9) /**/
#define FloatingMinimalResizeOpposingOption /*-------------*/ (OPTIONONE << 10) /**/
#define FloatingAllowCascadeToFloatingOption /*------------*/ (OPTIONONE << 11)
#define GriddingUseFocusedWindowColorOption /*-------------*/ (OPTIONONE << 12)
#define GriddingFollowGridOption /*------------------------*/ (OPTIONONE << 13)
#define GriddingMinimalMoveOption /*-----------------------*/ (OPTIONONE << 14) /**/
#define GriddingMinimalResizeOption /*---------------------*/ (OPTIONONE << 15) /**/
#define GriddingAllowResizeOpposingOption /*---------------*/ (OPTIONONE << 16) /*--*/
#define GriddingPortWindowsFromFloatingOption /*-----------*/ (OPTIONONE << 17)
#define GriddingEvenlyDistributeWindowsOption /*-----------*/ (OPTIONONE << 18)
#define TilingUseFocusedWindowColorOption /*---------------*/ (OPTIONONE << 19)
#define TilingFollowGridOption /*--------------------------*/ (OPTIONONE << 20)
#define TilingUseSeparatorsOption /*-----------------------*/ (OPTIONONE << 21)
#define TilingUseGapsOption /*-----------------------------*/ (OPTIONONE << 22)
#define TilingMinimalMoveOption /*-------------------------*/ (OPTIONONE << 23) /**/
#define TilingMinimalResizeOption /*-----------------------*/ (OPTIONONE << 24) /**/
#define TilingSlamWindowsOption /*-------------------------*/ (OPTIONONE << 25)
#define InGridUseFocusedWindowColorOption /*---------------*/ (OPTIONONE << 26)
#define InGridFollowGridOption /*--------------------------*/ (OPTIONONE << 27)
#define InGridMinimalMoveOption /*-------------------------*/ (OPTIONONE << 28) /**/
#define InGridMinimalResizeOption /*-----------------------*/ (OPTIONONE << 29) /**/
#define InGridAllowResizeOpposingOption /*-----------------*/ (OPTIONONE << 30) /*--*/
#define MaximizedUseFocusedWindowColorOption /*------------*/ (OPTIONONE << 31)

#define NonePointerInfo /*---------------------------------*/ 0
#define ChangeToFloatingPointerInfo /*---------------------*/ (POINTERINFOONE << 0)
#define ChangeToGriddingPointerInfo /*---------------------*/ (POINTERINFOONE << 1)
#define ChangeToTilingPointerInfo /*-----------------------*/ (POINTERINFOONE << 2)
#define CascadePointerInfo /*------------------------------*/ (POINTERINFOONE << 3)
#define AttachPointerInfo /*-------------------------------*/ (POINTERINFOONE << 4)
#define MovePointerInfo /*---------------------------------*/ (POINTERINFOONE << 5)
#define MoveToFloatingPointerInfo /*-----------------------*/ (POINTERINFOONE << 6)
#define NextPreviousMonitorPointerInfo /*------------------*/ (POINTERINFOONE << 7)
#define MoveToMonitorPointerInfo /*------------------------*/ (POINTERINFOONE << 8)
#define SwapMonitorsPointerInfo /*-------------------------*/ (POINTERINFOONE << 9)
#define RevolveMonitorsPointerInfo /*----------------------*/ (POINTERINFOONE << 10)
#define AddToGridPointerInfo /*----------------------------*/ (POINTERINFOONE << 11)
#define MoveOnGridPointerInfo /*---------------------------*/ (POINTERINFOONE << 12)
#define RemoveFromGridPointerInfo /*-----------------------*/ (POINTERINFOONE << 13)
#define DetachPointerInfo /*-------------------------------*/ (POINTERINFOONE << 14)
#define MoveToInGridPointerInfo /*-------------------------*/ (POINTERINFOONE << 15)
#define ExtendInGridPointerInfo /*-------------------------*/ (POINTERINFOONE << 16)
#define ShrinkInGridPointerInfo /*-------------------------*/ (POINTERINFOONE << 17)
#define MaximizePointerInfo /*-----------------------------*/ (POINTERINFOONE << 18)
#define MapPointerInfo /*----------------------------------*/ (POINTERINFOONE << 19)
#define ClientMessagePointerInfo /*------------------------*/ (POINTERINFOONE << 20)

#define NoneCascadeMode /*---------------------------------*/ 0
#define SimpleCascadeMode /*-------------------------------*/ 1
#define SmartCascadeMode /*--------------------------------*/ 2

#define NoneCascadeOption /*-------------------------------*/ 0
#define OverrideGridWindowsCascadeOption /*----------------*/ (CASCADEINFOONE << 0)
#define OverrideMaximizedWindowsCascadeOption /*-----------*/ (CASCADEINFOONE << 1)

#define NoneDefaultGridPosition /*-------------------------*/ 0
#define TopLeftDefaultGridPosition /*----------------------*/ 1
#define TopRightDefaultGridPosition /*---------------------*/ 2
#define BottomLeftDefaultGridPosition /*-------------------*/ 3
#define BottomRightDefaultGridPosition /*------------------*/ 4
#define CenterDefaultGridPosition /*-----------------------*/ 5

#define NoTilingResize /*----------------------------------*/ 1
#define ExtendTilingResize /*------------------------------*/ 0
#define ShrinkTilingResize /*------------------------------*/ 2

#define NoneTilingPrioritization /*------------------------*/ 0
#define MoveTopLeftYTilingPrioritization /*----------------*/ (TILINGPRIORITIZATIONONE << 0)
#define MoveTopRightYTilingPrioritization /*---------------*/ (TILINGPRIORITIZATIONONE << 1)
#define MoveBottomLeftYTilingPrioritization /*-------------*/ (TILINGPRIORITIZATIONONE << 2)
#define MoveBottomRightYTilingPrioritization /*------------*/ (TILINGPRIORITIZATIONONE << 3)
#define ExtendUpLeftYTilingPrioritization /*---------------*/ (TILINGPRIORITIZATIONONE << 4)
#define ExtendUpRightYTilingPrioritization /*--------------*/ (TILINGPRIORITIZATIONONE << 5)
#define ExtendDownLeftYTilingPrioritization /*-------------*/ (TILINGPRIORITIZATIONONE << 6)
#define ExtendDownRightYTilingPrioritization /*------------*/ (TILINGPRIORITIZATIONONE << 7)
#define ShrinkUpLeftYTilingPrioritization /*---------------*/ (TILINGPRIORITIZATIONONE << 8)
#define ShrinkUpRightYTilingPrioritization /*--------------*/ (TILINGPRIORITIZATIONONE << 9)
#define ShrinkDownLeftYTilingPrioritization /*-------------*/ (TILINGPRIORITIZATIONONE << 10)
#define ShrinkDownRightYTilingPrioritization /*------------*/ (TILINGPRIORITIZATIONONE << 11)

#define NoneContainerOptions /*----------------------------*/ 0
#define MappedContainerOption /*---------------------------*/ (CONTAINEROPTIONONE << 0)
#define InGridContainerOption /*---------------------------*/ (CONTAINEROPTIONONE << 1)
#define MaximizedContainerOption /*------------------------*/ (CONTAINEROPTIONONE << 2)

#define NoneMotionSubaction /*-----------------------------*/ 0
#define UpResizeMotionSubaction /*-------------------------*/ 1
#define DownResizeMotionSubaction /*-----------------------*/ 2
#define LeftResizeMotionSubaction /*-----------------------*/ 3
#define RightResizeMotionSubaction /*----------------------*/ 4
#define UpLeftResizeMotionSubaction /*---------------------*/ 5
#define UpRightResizeMotionSubaction /*--------------------*/ 6
#define DownLeftResizeMotionSubaction /*-------------------*/ 7
#define DownRightResizeMotionSubaction /*------------------*/ 8
#define TopSnappingMotionSubaction /*----------------------*/ 9
#define BottomSnappingMotionSubaction /*-------------------*/ 10
#define LeftSnappingMotionSubaction /*---------------------*/ 11
#define RightSnappingMotionSubaction /*--------------------*/ 12
#define TopLeftSnappingMotionSubaction /*------------------*/ 13
#define TopRightSnappingMotionSubaction /*-----------------*/ 14
#define BottomLeftSnappingMotionSubaction /*---------------*/ 15
#define BottomRightSnappingMotionSubaction /*--------------*/ 16
#define CenterSnappingMotionSubaction /*-------------------*/ 17

#define SnappingMotionSubactionOffset /*-------------------*/ TopSnappingMotionSubaction

#define _NET_WM_STATE_REMOVE /*----------------------------*/ 0
#define _NET_WM_STATE_ADD /*-------------------------------*/ 1
#define _NET_WM_STATE_TOGGLE /*----------------------------*/ 2

#define NextAdjacentMonitor /*-----------------------------*/ 0
#define PreviousAdjacentMonitor /*-------------------------*/ 1
#define AboveAdjacentMonitor /*----------------------------*/ 2
#define BelowAdjacentMonitor /*----------------------------*/ 3
#define LeftAdjacentMonitor /*-----------------------------*/ 4
#define RightAdjacentMonitor /*----------------------------*/ 5

#define NoManagementMode /*--------------------------------*/ 0
#define FloatingManagementMode /*--------------------------*/ 1
#define GriddingManagementMode /*--------------------------*/ 2
#define TilingManagementMode /*----------------------------*/ 3

#define NoneEnterInputException /*-------------------------*/ 0
#define ExecuteEnterInputException /*----------------------*/ (ENTERINPUTEXCEPTIONONE << 0)
#define ChangeManagementModeEnterInputException /*---------*/ (ENTERINPUTEXCEPTIONONE << 1)
#define CancelMoveResizeEnterInputException /*-------------*/ (ENTERINPUTEXCEPTIONONE << 2)
#define ResizeGridEnterInputException /*-------------------*/ (ENTERINPUTEXCEPTIONONE << 3)
#define ToggleGapsEnterInputException /*-------------------*/ (ENTERINPUTEXCEPTIONONE << 4)
#define CascadeEnterInputException /*----------------------*/ (ENTERINPUTEXCEPTIONONE << 5)
#define AttachEnterInputException /*-----------------------*/ (ENTERINPUTEXCEPTIONONE << 6)
#define SwapMonitorsEnterInputException /*-----------------*/ (ENTERINPUTEXCEPTIONONE << 7)
#define RevolveMonitorsEnterInputException /*--------------*/ (ENTERINPUTEXCEPTIONONE << 8)
#define MoveToEnterInputException /*-----------------------*/ (ENTERINPUTEXCEPTIONONE << 9)
#define MoveMonitorEnterInputException /*------------------*/ (ENTERINPUTEXCEPTIONONE << 10)
#define ToggleAddRemoveGridEnterInputException /*----------*/ (ENTERINPUTEXCEPTIONONE << 11)
#define MoveGridEnterInputException /*---------------------*/ (ENTERINPUTEXCEPTIONONE << 12)
#define ExtendEnterInputException /*-----------------------*/ (ENTERINPUTEXCEPTIONONE << 13)
#define ShrinkEnterInputException /*-----------------------*/ (ENTERINPUTEXCEPTIONONE << 14)
#define MaximizeEnterInputException /*---------------------*/ (ENTERINPUTEXCEPTIONONE << 15)

#define EnterInputMethod /*--------------------------------*/ (ENTERINPUTMETHODONE << 0)
#define KeyPressInputMethod /*-----------------------------*/ (ENTERINPUTMETHODONE << 1)
#define ButtonPressInputMethod /*--------------------------*/ (ENTERINPUTMETHODONE << 2)

#define NoneFlag /*----------------------------------------*/ 0
#define AllowKeyDoublingFlag /*----------------------------*/ (FLAGONE << 0)
#define AllowButtonDoublingFlag /*-------------------------*/ (FLAGONE << 1)
#define AllowCommandSendingFlag /*-------------------------*/ (FLAGONE << 2)
#define SnapInMonitorFlag /*-------------------------------*/ (FLAGONE << 3)

#define xcb_get_geometry_reply /*--------------------------*/ (void *)xcb_get_geometry_reply
#define xcb_get_input_focus_reply /*-----------------------*/ (void *)xcb_get_input_focus_reply
#define xcb_get_property_reply /*--------------------------*/ (void *)xcb_get_property_reply
#define xcb_list_properties_reply /*-----------------------*/ (void *)xcb_list_properties_reply
#define xcb_query_pointer_reply /*-------------------------*/ (void *)xcb_query_pointer_reply
#define xcb_randr_get_crtc_info_reply /*-------------------*/ (void *)xcb_randr_get_crtc_info_reply
#define xcb_randr_get_screen_resources_crtcs /*------------*/ (void *)xcb_randr_get_screen_resources_crtcs
#define xcb_randr_get_screen_resources_reply /*------------*/ (void *)xcb_randr_get_screen_resources_reply

#define xcb_sync(void) /*----------------------------------*/ free(xcb_get_input_focus_reply(connection, xcb_get_input_focus(connection), NULL))

#define GETADJACENTSURFACESIZE_DEC /*----------------------*/ static unsigned int getAdjacentSurfaceSize(const int position00, const int position01, const int size00, const int size01, const int position10, const int position11, const int size10)
#define FINDWINDOW_DEC /*----------------------------------*/ static bool findWindow(const xcb_window_t w, const xcb_window_t *location, const uint8_t size, const unsigned int amount, unsigned int *const current)
#define UNMAXIMIZECONTAINER_DEC /*-------------------------*/ static void _unmaximizeContainer(const unsigned int monitorAmount, const Container *const focused, Container *const c, MaximizedContainer *maximizedContainer)
#define MAXIMIZECONTAINER_DEC /*---------------------------*/ static void maximizeContainer(const Command command, const Monitor *const monitor, const Container *const focused, Container *const c, MaximizedContainer *const mc)
#define GETPOINTERMONITOR_DEC /*---------------------------*/ static unsigned int _getPointerMonitor(const Monitor *monitor, const unsigned int monitorAmount)
#define GETWINDOWMONITOR_DEC /*----------------------------*/ static unsigned int _getWindowMonitor(const xcb_window_t w, const Monitor *monitor, const unsigned int monitorAmount)
#define MOVEGRIDDINGCONTAINER_DEC /*-----------------------*/ static void moveGriddingContainer(const Container *const c, const Monitor *const m, const unsigned int gridWidth, const unsigned int gridHeight)
#define GETGRIDSLOTDATA_DEC /*-----------------------------*/ static void getGridSlotData(const unsigned int monitorWidth, const unsigned int monitorHeight, const unsigned int gridX, const unsigned int gridY, const unsigned int gridWidth, const unsigned int gridHeight, int *const x, int *const y, unsigned int *const width, unsigned int *const height)
#define DRAWGRID_DEC /*------------------------------------*/ static void _drawGrid(const Monitor *monitor, const unsigned int monitorAmount, const unsigned int gridWidth, const unsigned int gridHeight, const xcb_window_t *const grid)
#define FINDMONITOR_DEC /*---------------------------------*/ static Monitor *_findMonitor(const Monitor *const start, const Monitor *const wall, const AdjacentMonitor adjacentMonitor, const Monitor *const found)
#define MOVEFLOATINGCONTAINER_DEC /*-----------------------*/ static void moveFloatingContainer(const xcb_window_t w, const xcb_window_t s, const Monitor *const source, const Monitor *const destination, const Options option, const unsigned int gridWidth, const unsigned int gridHeight, const unsigned int windowDivisor, const unsigned int minimumWidth, const unsigned int minimumHeight)
#define COMMANDSERVER_DEC /*-------------------------------*/ static void *commandServer(void *containerStart)
#define PRINTUNEXPECTEDEVENT_DEC /*------------------------*/ static void printUnexpectedEvent(const unsigned int event)
				
#define unmaximizeContainer(f, c, mc) /*-------------------*/ _unmaximizeContainer(monitorAmount, f, c, mc)
#define getPointerMonitor(void) /*-------------------------*/ _getPointerMonitor(monitorStart, monitorAmount)
#define getWindowMonitor(w) /*-----------------------------*/ _getWindowMonitor(w, monitorStart, monitorAmount)
#define findMonitor(am, f) /*------------------------------*/ _findMonitor(monitorStart, monitorWall, am, f)
#define drawGrid(void) /*----------------------------------*/ _drawGrid(monitorStart, monitorAmount, gridWidth, gridHeight, gridStart);

#define closedInterval(point, bound0, bound1) /*-----------*/ ((point) >= (bound0) && (point) <= (bound1))
#define closedOpenInterval(point, bound0, bound1) /*-------*/ ((point) >= (bound0) && (point) < (bound1))

#define areCodeMasks(struct, event) /*---------------------*/ ((*(struct)).code == (*(xcb_key_press_event_t *)event).detail && (*(struct)).masks == (*(xcb_key_press_event_t *)event).state)
#define isShortcut(shortcut, event) /*---------------------*/ areCodeMasks(shortcut, event)
#define isButton(button, event) /*-------------------------*/ areCodeMasks(button, event)
#define isExecute(execute, event) /*-----------------------*/ areCodeMasks(execute, event)

#define changeProperties(w, s, m, p, t, f, a, d) /*--------*/ xcb_change_property(connection, m, w, p, t, f, a, d); xcb_change_property(connection, m, s, p, t, f, a, d)

#define setMotionAction(a) /*------------------------------*/ (motionContainerAction = a##MotionAction)
#define isAnyMotionAction(void) /*-------------------------*/ (motionContainerAction)
#define isMotionAction(a) /*-------------------------------*/ (motionContainerAction == a##MotionAction)

#define setMotionSubaction(s) /*---------------------------*/ (motionContainerSubaction = s##MotionSubaction)
#define isAnyMotionSubaction(void) /*----------------------*/ (motionContainerSubaction)
#define isMotionSubaction(s) /*----------------------------*/ (motionContainerSubaction == s##MotionSubaction)

#define setManagementMode(m) /*----------------------------*/ (program.managementMode = m##ManagementMode)
#define isManagementMode(m) /*-----------------------------*/ (program.managementMode == m##ManagementMode)

#define setContainerOption(c, o) /*------------------------*/ ((c).option = o##ContainerOption)
#define addContainerOption(c, o) /*------------------------*/ ((c).option |= o##ContainerOption)
#define removeContainerOption(c, o) /*---------------------*/ ((c).option ^= o##ContainerOption)
#define hasContainerOption(c, o) /*------------------------*/ ((c).option & o##ContainerOption)

#define setMotionOption(o) /*------------------------------*/ (motionContainerOption = o##MotionOption)
#define addMotionOption(o) /*------------------------------*/ (motionContainerOption |= o##MotionOption)
#define removeMotionOption(o) /*---------------------------*/ (motionContainerOption ^= o##MotionOption)
#define hasMotionOption(o) /*------------------------------*/ (motionContainerOption & o##MotionOption)

#define setFlag(f) /*--------------------------------------*/ (flag = f##Flag)
#define addFlag(f) /*--------------------------------------*/ (flag |= f##Flag)
#define removeFlag(f) /*-----------------------------------*/ (flag ^= f##Flag)
#define hasFlag(f) /*--------------------------------------*/ (flag & f##Flag)

#define consumeRedundantEvents(e0, e1, name) /*------------*/ \
consumeRedundant##name:{ \
	if(((e1) = xcb_poll_for_event(connection))){ \
		if((*(e1)).response_type == name){ \
			free(e0); \
			(e0) = (e1); \
			goto consumeRedundant##name; \
		} \
	}else if(printConnectionError()){ \
		goto eventLoopExit; \
	} \
}

extern const char *programName;
extern const xcb_screen_t *screen;
extern const char *errorPath;
extern bool mustOpenErrorStream;
extern FILE *errorStream;
extern xcb_connection_t *connection;
extern xcb_generic_error_t *genericError;
extern xcb_generic_reply_t *reply;
extern Mode mode;
extern ProgramData *programData;

typedef uint8_t Command;
typedef uint8_t CascadeOptions;
typedef uint8_t CascadeMode;
typedef uint8_t InputMethod;
typedef uint64_t Options;
typedef uint16_t AttributeMasks;
typedef uint8_t Depth;
typedef uint32_t WindowAttribute;
typedef uint16_t EnterInputException;
typedef uint32_t PointerInfo;
typedef uint8_t DefaultGridPosition;
typedef uint8_t AdjacentMonitor;
typedef uint16_t TilingPrioritization;
typedef uint8_t TilingResize;
typedef uint8_t Flags;
typedef uint8_t ContainerOptions;
typedef uint8_t MotionOption;
typedef uint8_t MotionAction;
typedef uint8_t MotionSubaction;

typedef struct{
	int x;
	int y;
	unsigned int width;
	unsigned int height;
} Monitor, Rectangle;

typedef struct{
	const ARGB *oldBackgroundColor;
	int oldX;
	int oldY;
	unsigned int oldWidth;
	unsigned int oldHeight;
	unsigned int oldBorder;
	xcb_window_t window;
	xcb_window_t subwindow;
	bool shouldChangeProperty;
} MaximizedContainer;

typedef struct{
	unsigned int gridX;
	unsigned int gridY;
	unsigned int gridWidth;
	unsigned int gridHeight;
	xcb_window_t window;
	xcb_window_t subwindow;
	ContainerOptions option;
} Container;

typedef struct{
	uint16_t masks;
	uint8_t code;
	Command command;
} Shortcut, Button;

typedef struct{
	Command s0;
	Command s1;
	Command s2;
	Command s3;
	Command s4;
	Command s5;
	Command s6;
	Command s7;
	Command s8;
} SnapPositions;

typedef struct{
	const char *command;
	uint16_t masks;
	uint8_t code;
} Execute;

FINDWINDOW_DEC;
UNMAXIMIZECONTAINER_DEC;
MAXIMIZECONTAINER_DEC;
GETPOINTERMONITOR_DEC;
GETWINDOWMONITOR_DEC;
MOVEGRIDDINGCONTAINER_DEC;
GETGRIDSLOTDATA_DEC;
DRAWGRID_DEC;
FINDMONITOR_DEC;
GETADJACENTSURFACESIZE_DEC;
MOVEFLOATINGCONTAINER_DEC;
COMMANDSERVER_DEC;
PRINTUNEXPECTEDEVENT_DEC;



#define motionNotify /*------------------------------------*/ ((xcb_motion_notify_event_t *)event)
#define configureRequest /*--------------------------------*/ ((xcb_configure_request_event_t *)event)

#define setDefaultGridPosition(p) /*-----------------------*/ (defaultGridPosition = p##DefaultGridPosition)

#define isCommand(c) /*------------------------------------*/ (command == c##Command)

#define setCascadeMode(m) /*-------------------------------*/ (cascadeMode = m##CascadeMode)
#define isCascadeMode(m) /*--------------------------------*/ (cascadeMode == m##CascadeMode)

#define setTilingPrioritization(p) /*----------------------*/ (tilingPrioritization = p##TilingPrioritization)
#define hasTilingPrioritization(p) /*----------------------*/ (tilingPrioritization & p##TilingPrioritization)

#define setPointerInfo(i) /*-------------------------------*/ (pointerInfo = i##PointerInfo)
#define hasPointerInfo(i) /*-------------------------------*/ (pointerInfo & i##PointerInfo)

#define setInputMethod(m) /*-------------------------------*/ (inputMethod = m##InputMethod)
#define hasInputMethod(m) /*-------------------------------*/ (inputMethod & m##InputMethod)

#define setOption(o) /*------------------------------------*/ (option = o##Option)
#define hasOption(o) /*------------------------------------*/ (option & o##Option)

#define setEnterInputException(v, e) /*--------------------*/ (v##EnterInputException = e##EnterInputException);
#define hasEnterInputException(e) /*-----------------------*/ (*(EnterInputException *)genericPointer & e##EnterInputException)

#define setCascadeOption(o) /*-----------------------------*/ (cascadeOption = o##CascadeOption)
#define hasCascadeOption(o) /*-----------------------------*/ (cascadeOption & o##CascadeOption)



























/*
struct sigaction{
	void     (*sa_handler)(int);
	sigset_t   sa_mask;
	int        sa_flags;
};
sigaction(int signum, const struct sigaction *restrict act, struct sigaction *restrict oldact)

SIGABRT      P1990      Core    Abort signal from abort(3)
SIGFPE       P1990      Core    Floating-point exception
SIGILL       P1990      Core    Illegal Instruction
SIGQUIT      P1990      Core    Quit from keyboard
SIGSEGV      P1990      Core    Invalid memory reference
SIGALRM      P1990      Term    Timer signal from alarm(2)
SIGHUP       P1990      Term    Hangup detected on controlling terminal
SIGINT       P1990      Term    Interrupt from keyboard
SIGPIPE      P1990      Term    Broken pipe: write to pipe with no
SIGTERM      P1990      Term    Termination signal
SIGUSR1      P1990      Term    User-defined signal 1
SIGTSTP      P1990      Stop    Stop typed at terminal
SIGTTIN      P1990      Stop    Terminal input for background process
SIGTTOU      P1990      Stop    Terminal output for background process
SIGCONT      P1990      Cont    Continue if stopped

SIGKILL      P1990      Term    Kill signal
SIGSTOP      P1990      Stop    Stop process

SIGBUS       P2001      Core    Bus error (bad memory access)
*/



























#define hasCascadeOption(o) /*-----------------------------*/ (cascadeOption & o##CascadeOption)



#define TopAddWindowRule /*--------------------------------*/ 0
#define BottomAddWindowRule /*-----------------------------*/ 1
#define LeftAddWindowRule /*-------------------------------*/ 2
#define RightAddWindowRule /*------------------------------*/ 3

#define setAddWindowRule(r) /*-----------------------------*/ (addWindowRule = r##AddWindowRule)

typedef uint8_t AddWindowRule;



#define addTilingWindow(void) /*---------------------------*/ _addTilingWindow(containerAmount, gapsX, gapsY, containerStart, containerWall, containerCurrent, monitorStart, monitorCurrent, option, gridWidth, gridHeight, monitorAmount, addWindowRule, tilingWindowDivisorX, tilingWindowDivisorY)
#define ADDTILINGWINDOW_DEC /*-----------------------------*/ static void _addTilingWindow(const unsigned int containerAmount, \
                                                                                           const unsigned int gapsX, \
                                                                                           const unsigned int gapsY, \
                                                                                           const Container *const containerStart, \
                                                                                           const Container *const containerWall, \
                                                                                           const Container *const newContainer, \
                                                                                           const Monitor *const monitorStart, \
                                                                                           const Monitor *const monitor, \
                                                                                           const Options option, \
                                                                                           const unsigned int gridWidth, \
                                                                                           const unsigned int gridHeight, \
                                                                                           const unsigned int monitorAmount, \
                                                                                           const unsigned int addWindowRule, \
                                                                                           const unsigned int tilingWindowDivisorX, \
                                                                                           const unsigned int tilingWindowDivisorY)

ADDTILINGWINDOW_DEC{
	struct{
		WindowAttribute a0;
		WindowAttribute a1;
		WindowAttribute a2;
		WindowAttribute a3;
	} attribute;
	if(!containerAmount){
		addFirstWindow:{
			attribute.a0 = (*monitor).x + gapsX;
			attribute.a1 = (*monitor).y + gapsY;
			attribute.a2 = (*monitor).width - 2 * gapsX;
			attribute.a3 = (*monitor).height - 2 * gapsY;
			xcb_configure_window(connection, (*newContainer).window, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
			attribute.a2 -= (*programData).borderX;
			attribute.a3 -= (*programData).borderY;
			xcb_configure_window(connection, (*newContainer).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
			return;
		}
	}
	{
		unsigned int containerSize = containerAmount * sizeof(bool);
		void *data;



		bool *containerInMonitor;
		unsigned int monitorContainerAmount = 0;
		{
			const xcb_window_t *containerWindowCurrent = &(*containerStart).window;
			const unsigned int currentMonitor = monitor - monitorStart;
			if((data = malloc(containerSize))){
				containerInMonitor = data;
				findSameMonitorWindow0:{
					if(getWindowMonitor(*containerWindowCurrent) == currentMonitor){
						*containerInMonitor = true;
						++monitorContainerAmount;
					}else{
						*containerInMonitor = false;
					}
					containerWindowCurrent += sizeof(Container);
					if((void *)containerWindowCurrent < (void *)containerWall){
						++containerInMonitor;
						goto findSameMonitorWindow0;
					}
				}
				if(!monitorContainerAmount){
					free(data);
					goto addFirstWindow;
				}
			}else{
				findSameMonitorWindow1:{
					if(getWindowMonitor(*containerWindowCurrent) == currentMonitor){
						++monitorContainerAmount;
					}
					containerWindowCurrent += sizeof(Container);
					if((void *)containerWindowCurrent < (void *)containerWall){
						goto findSameMonitorWindow1;
					}
				}
				if(!monitorContainerAmount){
					goto addFirstWindow;
				}
				printError("not enough ram, could not restore tiling container data");
				return;
			}
		}



		/**/



		if(!(data = realloc(data, containerSize + monitorContainerAmount * sizeof(Rectangle)))){
			printError("not enough ram, could not restore tiling container data");
			return;
		}
		containerInMonitor = data;
		{
			const Container *containerCurrent = containerStart;
			Rectangle *rectangleStart = (Rectangle *)(containerInMonitor + containerAmount);
			Rectangle *rectangleCurrent = rectangleStart;
			Monitor smallerMonitor = *monitor;
			getRectangles:{
				if(*containerInMonitor){
					if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent).window), NULL))){
						(*rectangleCurrent).width = 0;
					}else{
						(*rectangleCurrent).x = (*(xcb_get_geometry_reply_t *)reply).x;
						(*rectangleCurrent).y = (*(xcb_get_geometry_reply_t *)reply).y;
						(*rectangleCurrent).width = (*(xcb_get_geometry_reply_t *)reply).width;
						(*rectangleCurrent).height = (*(xcb_get_geometry_reply_t *)reply).height;
						free(reply);
					}
					++rectangleCurrent;
				}
				if(++containerCurrent < containerWall){
					++containerInMonitor;
					goto getRectangles;
				}
			}









			if(hasOption(TilingFollowGrid)){
				getGridSlotData((*monitor).width, (*monitor).height, 0, 0, gridWidth, gridHeight, NULL, NULL, &width, &height);
			}else{
				width = (*monitor).width / tilingWindowDivisorX;
				height = (*monitor).height / tilingWindowDivisorY;
			}
			switch(addWindowRule){
				case TopAddWindowRule:{
					width = (*monitor).width - 2 * gapsX;
					smallerMonitor.y += height + gapsY;
					smallerMonitor.height -= height + gapsY;
					break;
				}
				case BottomAddWindowRule:{
					y = (*monitor).y + (*monitor).height - gapsY - height;
					width = (*monitor).width - 2 * gapsX;
					smallerMonitor.height -= height + gapsY;
					break;
				}
				case LeftAddWindowRule:{
					height = (*monitor).height - 2 * gapsY;
					smallerMonitor.x += width + gapsX;
					smallerMonitor.width -= width + gapsX;
					break;
				}
				default:{
					x = (*monitor).x + (*monitor).width - gapsX - width;
					height = (*monitor).height - 2 * gapsY;
					smallerMonitor.width -= width + gapsX;
					break;
				}
			}









			/**/









			{
				const unsigned int borderX = (*programData).borderX;
				const unsigned int borderY = (*programData).borderY;
				containerInMonitor = data;
				rectangleCurrent = rectangleStart;
				containerCurrent = containerStart;
				configureWindows:{
					if(*containerInMonitor){
						attribute.a0 = (*rectangleCurrent).x;
						attribute.a1 = (*rectangleCurrent).y;
						attribute.a2 = (*rectangleCurrent).width;
						attribute.a3 = (*rectangleCurrent).height;
						xcb_configure_window(connection, (*containerCurrent).window, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
						attribute.a2 -= borderX;
						attribute.a3 -= borderY;
						xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
						++rectangleCurrent;
					}
					if(++containerCurrent < containerWall){
						++containerInMonitor;
						goto configureWindows;
					}
				}
			}
			free(data);
		}
	}









	/*
	- record stacking order of monitor windows (O(nlogn)) from new window line
	- move / resize monitor
	- move / resize monitor windows
	*/



	/*const Container *containerCurrent = containerStart;
	bool *const containerInMonitor = malloc(containerAmount * sizeof(bool));
	bool *currentInMonitor = containerInMonitor;
	unsigned int monitorContainerAmount = 0;
	{
		const unsigned int currentMonitor = monitor - monitorStart;
		findSameMonitorWindow:{
			if(getWindowMonitor((*containerCurrent).window) == currentMonitor){
				*currentInMonitor = 1;
				++monitorContainerAmount;
			}else{
				*currentInMonitor = 0;
			}
			if(++containerCurrent < containerWall){
				++currentInMonitor;
				goto findSameMonitorWindow;
			}
		}
		if(!monitorContainerAmount){
			free(containerInMonitor);
			goto addFirstWindow;
		}
	}









	int x = (*monitor).x + gapsX;
	int y = (*monitor).y + gapsY;
	unsigned int width;
	unsigned int height;
	Monitor smallerMonitor = *monitor;
	Rectangle *data;
	Rectangle *dataCurrent;
	{
		if(hasOption(TilingFollowGrid)){
			getGridSlotData((*monitor).width, (*monitor).height, 0, 0, gridWidth, gridHeight, NULL, NULL, &width, &height);
		}else{
			width = (*monitor).width / tilingWindowDivisorX;
			height = (*monitor).height / tilingWindowDivisorY;
		}
		switch(addWindowRule){
			case TopAddWindowRule:{
				width = (*monitor).width - 2 * gapsX;
				smallerMonitor.y += height + gapsY;
				smallerMonitor.height -= height + gapsY;
				break;
			}
			case BottomAddWindowRule:{
				y = (*monitor).y + (*monitor).height - gapsY - height;
				width = (*monitor).width - 2 * gapsX;
				smallerMonitor.height -= height + gapsY;
				break;
			}
			case LeftAddWindowRule:{
				height = (*monitor).height - 2 * gapsY;
				smallerMonitor.x += width + gapsX;
				smallerMonitor.width -= width + gapsX;
				break;
			}
			default:{
				x = (*monitor).x + (*monitor).width - gapsX - width;
				height = (*monitor).height - 2 * gapsY;
				smallerMonitor.width -= width + gapsX;
				break;
			}
		}
		{
			data = malloc(monitorContainerAmount * sizeof(Rectangle));
			if(data){
				dataCurrent = data;
				containerCurrent = containerStart;
				currentInMonitor = containerInMonitor;
				loop:{
					if(*currentInMonitor && (reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent).window), NULL))){
						(*dataCurrent).x = (*(xcb_get_geometry_reply_t *)reply).x;
						(*dataCurrent).y = (*(xcb_get_geometry_reply_t *)reply).y;
						(*dataCurrent).width = (*(xcb_get_geometry_reply_t *)reply).width;
						(*dataCurrent).height = (*(xcb_get_geometry_reply_t *)reply).height;
						++dataCurrent;
						free(reply);
					}
					if(++containerCurrent < containerWall){
						++currentInMonitor;
						goto loop;
					}
				}









				containerCurrent = containerStart;
				currentInMonitor = containerInMonitor;
				dataCurrent = data;
				loop1:{
					if(*currentInMonitor){
						if((*dataCurrent).x == (*monitor).x){
							
						}
					}
					if(++containerCurrent < containerWall){
						++currentInMonitor;
						goto loop1;
					}
				}









				free(data);
			}
		}
	}*/
	return;
}



























xcb_window_t receiver;
unsigned int containerAmount;



EVENTLOOP_DEC{
	const xcb_window_t glass = xcb_generate_id(connection);
	const xcb_colormap_t colormap = xcb_generate_id(connection);
	const xcb_window_t motionContainerGlass = xcb_generate_id(connection);
	const xcb_window_t motionContainerSnappingWindow = xcb_generate_id(connection);
	xcb_window_t motionContainerMinimalWindow = xcb_generate_id(connection);
	xcb_window_t motionContainerWindow = XCB_NONE;
	xcb_window_t motionContainerSubwindow;
	unsigned int snappingBorder;
	unsigned int snappingDivisorX;
	unsigned int snappingDivisorY;
	unsigned int snappingOffsetUp;
	unsigned int snappingOffsetDown;
	unsigned int snappingOffsetLeft;
	unsigned int snappingOffsetRight;
	unsigned int snappingOffsetX;
	unsigned int snappingOffsetY;
	unsigned int motionContainerMinimalMoveBorder;
	unsigned int motionContainerMinimalResizeBorder;
	int escapeX = 0;
	int escapeY = 0;
	int pointerOffsetX = 0;
	int pointerOffsetY = 0;
	unsigned int motionContainerPreviousMonitor;
	MotionOption motionContainerOption = NoneMotionOption;
	MotionAction motionContainerAction;
	MotionSubaction motionContainerSubaction = NoneMotionSubaction;



	AddWindowRule addWindowRule;



	Container *focused = NULL;
	void *containerData = NULL;
	void *userData = NULL;
	Options option;
	PointerInfo pointerInfo;
	ProgramData program;
	AttributeMasks attributeMasks;
	xcb_visualid_t visual;
	Depth depth;
	InputMethod inputMethod;
	unsigned int shortcutAmount;
	unsigned int buttonAmount;
	unsigned int executeAmount;
	SnapPositions snapPosition;
	Flags flag;
	EnterInputException floatingEnterInputException;
	EnterInputException griddingEnterInputException;
	EnterInputException inGridEnterInputException;
	EnterInputException tilingEnterInputException;
	unsigned int floatingWindowDivisor;
	unsigned int gridWidth;
	unsigned int gridHeight;
	unsigned int shadow;
	DefaultGridPosition defaultGridPosition;
	bool isGridMapped;
	int floatingStickyThresholdX;
	int floatingStickyThresholdY;
	int floatingDistanceToTravelX;
	int floatingDistanceToTravelY;
	int floatingSnappingThreshold;
	unsigned int floatingMinimumWidth;
	unsigned int floatingMinimumHeight;
	int cascadeOffsetX;
	int cascadeOffsetY;
	CascadeOptions cascadeOption;
	CascadeMode cascadeMode;
	unsigned int gridMinWidth;
	unsigned int gridMinHeight;
	unsigned int gridMaxWidth;
	unsigned int gridMaxHeight;
	TilingPrioritization tilingPrioritization;
	unsigned int tilingMinimumWidth;
	unsigned int tilingMinimumHeight;
	unsigned int tilingExtendWidth;
	unsigned int tilingExtendHeight;
	unsigned int tilingShrinkWidth;
	unsigned int tilingShrinkHeight;
	unsigned int tilingGapsX;
	unsigned int tilingGapsY;
	unsigned int tilingWindowDivisorX = 3;
	unsigned int tilingWindowDivisorY = 3;
	unsigned int separatorWidth;
	unsigned int separatorBorder;
	unsigned int floatingMaximumWidth;
	unsigned int floatingMaximumHeight;
	unsigned int floatingExtendWidth;
	unsigned int floatingExtendHeight;
	unsigned int floatingShrinkWidth;
	unsigned int floatingShrinkHeight;
	unsigned int borderUp;
	unsigned int borderDown;
	unsigned int borderLeft;
	unsigned int borderRight;
	unsigned int monitorAmount;
	unsigned int rootShortcutAmount;
	unsigned int rootButtonAmount;
	MaximizedContainer *maximizedContainerStart;
	MaximizedContainer *maximizedContainerCurrent;
	MaximizedContainer *maximizedContainerWall;
	Container *containerStart = NULL;
	Container *containerCurrent = NULL;
	Container *containerWall = NULL;
	Monitor *monitorStart;
	Monitor *monitorCurrent;
	Monitor *monitorWall;
	xcb_window_t *gridStart = NULL;
	xcb_window_t *gridCurrent;
	xcb_window_t *gridWall = NULL;
	Shortcut *shortcutStart;
	Shortcut *shortcutCurrent;
	Shortcut *shortcutWall;
	Button *buttonStart;
	Button *buttonCurrent;
	Button *buttonWall;
	Execute *executeStart;
	Execute *executeCurrent;
	Execute *executeWall;
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	void *genericPointer;
	xcb_window_t genericWindow;
	struct{
		WindowAttribute a0;
		WindowAttribute a1;
		WindowAttribute a2;
		WindowAttribute a3;
		WindowAttribute a4;
		WindowAttribute a5;
		WindowAttribute a6;
		WindowAttribute a7;
	} attribute;
	xcb_generic_event_t *event = NULL;
	xcb_generic_event_t *e = NULL;
	Command command = NoCommand;
	unsigned int current;
	unsigned int genericUnsignedInteger;
	unsigned int gapsX;
	unsigned int gapsY;
    pthread_t thread;



	containerAmount = 0;
	receiver = xcb_generate_id(connection);









	/*start*/
	setMode(Continue);
	programData = &program;
	program.managementMode = NoManagementMode;
	visual = (*screen).root_visual;
	depth = (*screen).root_depth;
	attribute.a0 = 0x00000000;
	attribute.a1 = 0x00000000;
	attribute.a2 = true;
	attribute.a3 = colormap;
	{
		xcb_depth_iterator_t depthIterator = xcb_screen_allowed_depths_iterator(screen);
		iterateDepths:{
			if((*depthIterator.data).depth == 32){
				xcb_visualtype_iterator_t visualIterator = xcb_depth_visuals_iterator(depthIterator.data);
				iterateVisuals:{
					if((*visualIterator.data)._class != XCB_VISUAL_CLASS_TRUE_COLOR){
						if(!visualIterator.rem){
							goto not32Bits;
						}
						xcb_visualtype_next(&visualIterator);
						goto iterateVisuals;
					}
					visual = (*visualIterator.data).visual_id;
					depth = (*depthIterator.data).depth;
				}
			}else if(depthIterator.rem){
				xcb_depth_next(&depthIterator);
				goto iterateDepths;
			}else{
				not32Bits:{
					printError("could not get 32-bit visual data");
				}
			}
		}
	}
	{
		struct{
			xcb_intern_atom_cookie_t c0;
			xcb_intern_atom_cookie_t c1;
			xcb_intern_atom_cookie_t c2;
			xcb_intern_atom_cookie_t c3;
			xcb_intern_atom_cookie_t c4;
		} cookie;
		xcb_intern_atom_cookie_t *c = &cookie.c0;
		genericPointer = &program.COMMAND;
		current = 0;
		cookie.c0 = xcb_intern_atom_unchecked(connection, false, 7, "COMMAND");
		cookie.c1 = xcb_intern_atom_unchecked(connection, false, 12, "WM_PROTOCOLS");
		cookie.c2 = xcb_intern_atom_unchecked(connection, false, 16, "WM_DELETE_WINDOW");
		cookie.c3 = xcb_intern_atom_unchecked(connection, false, 13, "_NET_WM_STATE");
		cookie.c4 = xcb_intern_atom_unchecked(connection, false, 24, "_NET_WM_STATE_FULLSCREEN");
		getAtomReply:{
			if(!(reply = xcb_intern_atom_reply(connection, *c, NULL))){
				*(xcb_atom_t *)genericPointer = XCB_NONE;
			}else{
				*(xcb_atom_t *)genericPointer = (*(xcb_intern_atom_reply_t *)reply).atom;
				free(reply);
			}
			if(++current < 5){
				++c;
				genericPointer = (xcb_atom_t *)genericPointer + 1;
				goto getAtomReply;
			}
		}
	}



	/*xcb_create_window(connection, depth, receiver, (*screen).root, 0, 0, 1, 1, 0, XCB_WINDOW_CLASS_INPUT_ONLY, visual, XCB_NONE, NULL);*/



	xcb_create_colormap(connection, XCB_COLORMAP_ALLOC_NONE, colormap, (*screen).root, visual);
	xcb_create_window(connection, depth, glass, (*screen).root, 0, 0, (*screen).width_in_pixels, (*screen).height_in_pixels, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, visual, XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_OVERRIDE_REDIRECT | XCB_CW_COLORMAP, &attribute);
	xcb_create_window(connection, depth, motionContainerGlass, (*screen).root, 0, 0, (*screen).width_in_pixels, (*screen).height_in_pixels, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, visual, XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_OVERRIDE_REDIRECT | XCB_CW_COLORMAP, &attribute);
	xcb_create_window(connection, depth, motionContainerMinimalWindow, (*screen).root, 0, 0, 1, 1, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, visual, XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_OVERRIDE_REDIRECT | XCB_CW_COLORMAP, &attribute);
	xcb_create_window(connection, depth, motionContainerSnappingWindow, (*screen).root, 0, 0, 1, 1, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, visual, XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_OVERRIDE_REDIRECT | XCB_CW_COLORMAP, &attribute);
	attribute.a0 = XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION;
	xcb_change_window_attributes(connection, motionContainerGlass, XCB_CW_EVENT_MASK, &attribute);
	readConfig:{
		setOption(None);
		setFlag(None);
		setPointerInfo(None);
		setDefaultGridPosition(None);
		setTilingPrioritization(None);
		setInputMethod(ButtonPress);
		setEnterInputException(floating, None);
		setEnterInputException(gridding, None);
		setEnterInputException(inGrid, None);
		setEnterInputException(tiling, None);



		shortcutAmount = 0;
		buttonAmount = 0;
		executeAmount = 0;



		isGridMapped = false;



		program.colorContainerShadow = 0x00000000;
		program.colorGridSubwindowBorder = 0x00000000;
		program.colorGridSubwindowBackground = 0x00000000;
		program.colorSeparatorBorder = 0x00000000;
		program.colorSeparatorBackground = 0x00000000;
		program.colorFocusedContainerBackgroundFloating = 0x00000000;
		program.colorFocusedContainerBackgroundGridding = 0x00000000;
		program.colorFocusedContainerBackgroundTiling = 0x00000000;
		program.colorFocusedContainerBackgroundInGrid = 0x00000000;
		program.colorFocusedContainerBackgroundFullscreen = 0x00000000;
		program.colorFocusedContainerBackgroundBigscreen = 0x00000000;
		program.colorContainerBackgroundFloating = 0x00000000;
		program.colorContainerBackgroundGridding = 0x00000000;
		program.colorContainerBackgroundTiling = 0x00000000;
		program.colorContainerBackgroundInGrid = 0x00000000;
		program.colorContainerBackgroundFullscreen = 0x00000000;
		program.colorContainerBackgroundBigscreen = 0x00000000;
		program.colorMotionContainerGlassBorder = 0x00000000;
		program.colorMotionContainerGlassBackground = 0x00000000;
		program.colorMotionContainerMinimalMoveBorder = 0x00000000;
		program.colorMotionContainerMinimalMoveBackground = 0x00000000;
		program.colorMotionContainerMinimalResizeBorder = 0x00000000;
		program.colorMotionContainerMinimalResizeBackground = 0x00000000;
		program.colorMotionContainerSnappingBackground = 0x00000000;
		program.colorMotionContainerSnappingBorder = 0x00000000;



		cascadeOffsetX = 0;
		cascadeOffsetY = 0;
		setCascadeOption(None);
		setCascadeMode(None);



		borderUp = 0;
		borderDown = 0;
		borderLeft = 0;
		borderRight = 0;
		snapPosition.s0 = NoCommand;
		snapPosition.s1 = NoCommand;
		snapPosition.s2 = NoCommand;
		snapPosition.s3 = NoCommand;
		snapPosition.s4 = NoCommand;
		snapPosition.s5 = NoCommand;
		snapPosition.s6 = NoCommand;
		snapPosition.s7 = NoCommand;
		snapPosition.s8 = NoCommand;
		floatingWindowDivisor = 0;



		gridMinWidth = 0;
		gridMinHeight = 0;
		gridMaxWidth = 0;
		gridMaxHeight = 0;



		gridWidth = 0;
		gridHeight = 0;
		shadow = 0;



		tilingMinimumWidth = 0;
		tilingMinimumHeight = 0;
		tilingExtendWidth = 0;
		tilingExtendHeight = 0;
		tilingShrinkWidth = 0;
		tilingShrinkHeight = 0;
		tilingGapsX = 0;
		tilingGapsY = 0;



		separatorWidth = 0;
		separatorBorder = 0;
		floatingMaximumWidth = 0;
		floatingMaximumHeight = 0;
		floatingExtendWidth = 0;
		floatingExtendHeight = 0;
		floatingShrinkWidth = 0;
		floatingShrinkHeight = 0;



		floatingStickyThresholdX = 0;
		floatingStickyThresholdY = 0;
		floatingDistanceToTravelX = 0;
		floatingDistanceToTravelY = 0;
		floatingSnappingThreshold = 0;
		floatingMinimumWidth = 0;
		floatingMinimumHeight = 0;









		/**/









		option = FloatingUseFocusedWindowColorOption | /*FloatingMinimalMoveOption |*/ FloatingMinimalResizeOption | FloatingAllowMonitorStickingOption | FloatingAllowSnappingOption | FloatingUseSnappingWindowOption | FloatingPortWindowsFromGriddingOption | InGridUseFocusedWindowColorOption | GriddingUseFocusedWindowColorOption | GriddingPortWindowsFromFloatingOption | TilingUseFocusedWindowColorOption | TilingUseSeparatorsOption | TilingUseGapsOption | MaximizedUseFocusedWindowColorOption;
		setManagementMode(Floating);
		inputMethod = EnterInputMethod | KeyPressInputMethod | ButtonPressInputMethod;
		pointerInfo = MovePointerInfo;
		setDefaultGridPosition(TopLeft);
		shortcutAmount = 51;
		buttonAmount = 3;
		executeAmount = 1;



		addFlag(AllowCommandSending);



		separatorWidth = 12;
		separatorBorder = 1;
		floatingMaximumWidth = (*screen).width_in_pixels;
		floatingMaximumHeight = (*screen).height_in_pixels;
		floatingExtendWidth = 10;
		floatingExtendHeight = 10;
		floatingShrinkWidth = 10;
		floatingShrinkHeight = 10;



		cascadeOffsetX = 20;
		cascadeOffsetY = 20;
		cascadeOption = OverrideGridWindowsCascadeOption | OverrideMaximizedWindowsCascadeOption;
		setCascadeMode(Smart);



		floatingWindowDivisor = 2;



		program.colorContainerShadow = 0x7F000000;
		program.colorGridSubwindowBorder = 0x10975C57;
		program.colorGridSubwindowBackground = 0x00000000;
		program.colorSeparatorBorder = 0xFFFFFFFF;
		program.colorSeparatorBackground = 0xFF000000;
		program.colorFocusedContainerBackgroundFloating = 0xFF00FF00;
		program.colorFocusedContainerBackgroundGridding = 0xFFFF0000;
		program.colorFocusedContainerBackgroundTiling = 0xFF0000FF;
		program.colorFocusedContainerBackgroundInGrid = 0xFFFF7F00;
		program.colorFocusedContainerBackgroundFullscreen = 0xFFFFFFFF;
		program.colorFocusedContainerBackgroundBigscreen = 0xFFFF007F;
		program.colorContainerBackgroundFloating = 0xFF000000;
		program.colorContainerBackgroundGridding = 0xFF000000;
		program.colorContainerBackgroundTiling = 0xFF000000;
		program.colorContainerBackgroundInGrid = 0xFF000000;
		program.colorContainerBackgroundFullscreen = 0xFF000000;
		program.colorContainerBackgroundBigscreen = 0xFF000000;
		program.colorMotionContainerGlassBorder = 0x00000000;
		program.colorMotionContainerGlassBackground = 0x00000000;
		program.colorMotionContainerMinimalMoveBorder = 0xFFF2C6B4;
		program.colorMotionContainerMinimalMoveBackground = 0x7FF07746;
		program.colorMotionContainerMinimalResizeBorder = 0xFFF2C6B4;
		program.colorMotionContainerMinimalResizeBackground = 0x7FF07746;
		program.colorMotionContainerSnappingBackground = 0x00000000;
		program.colorMotionContainerSnappingBorder = 0xFFFFFFFF;



		floatingEnterInputException = CancelMoveResizeEnterInputException | ResizeGridEnterInputException | SwapMonitorsEnterInputException | RevolveMonitorsEnterInputException | MoveToEnterInputException | MoveMonitorEnterInputException | ToggleAddRemoveGridEnterInputException | MoveGridEnterInputException | ExtendEnterInputException | ShrinkEnterInputException;
		griddingEnterInputException = CancelMoveResizeEnterInputException | ResizeGridEnterInputException | SwapMonitorsEnterInputException | RevolveMonitorsEnterInputException | MoveToEnterInputException | MoveMonitorEnterInputException | ToggleAddRemoveGridEnterInputException | MoveGridEnterInputException | ExtendEnterInputException | ShrinkEnterInputException;
		inGridEnterInputException = CancelMoveResizeEnterInputException | ResizeGridEnterInputException | SwapMonitorsEnterInputException | RevolveMonitorsEnterInputException | MoveToEnterInputException | MoveMonitorEnterInputException | ToggleAddRemoveGridEnterInputException | MoveGridEnterInputException | ExtendEnterInputException | ShrinkEnterInputException;
		tilingEnterInputException = CancelMoveResizeEnterInputException | ResizeGridEnterInputException | SwapMonitorsEnterInputException | RevolveMonitorsEnterInputException | MoveToEnterInputException | MoveMonitorEnterInputException | ToggleAddRemoveGridEnterInputException | MoveGridEnterInputException | ExtendEnterInputException | ShrinkEnterInputException;



		borderUp = 1;
		borderDown = 1;
		borderLeft = 1;
		borderRight = 1;



		gridMinWidth = 1;
		gridMinHeight = 1;
		gridMaxWidth = 20;
		gridMaxHeight = 20;



		tilingMinimumWidth = 20;
		tilingMinimumHeight = 20;
		tilingExtendWidth = 10;
		tilingExtendHeight = 10;
		tilingShrinkWidth = 10;
		tilingShrinkHeight = 10;
		tilingGapsX = 10;
		tilingGapsY = 10;



		gridWidth = 7;
		gridHeight = 7;
		shadow = 10;



		floatingStickyThresholdX = 10;
		floatingStickyThresholdY = 10;
		floatingDistanceToTravelX = 0;
		floatingDistanceToTravelY = 0;
		floatingSnappingThreshold = 50;
		floatingMinimumWidth = 20;
		floatingMinimumHeight = 20;



		program.borderX = borderLeft + borderRight;
		program.borderY = borderUp + borderDown;



		if(!(reply = xcb_randr_get_screen_resources_reply(connection, xcb_randr_get_screen_resources(connection, (*screen).root), &genericError))){
			printXCBError();
			free(genericError);
			setMode(Exit);
			goto emergencyExit;
		}
		monitorAmount = xcb_randr_get_screen_resources_crtcs_length((xcb_randr_get_screen_resources_reply_t *)reply);
		if(!(userData = malloc(shortcutAmount * sizeof(Shortcut) + buttonAmount * sizeof(Button) + executeAmount * sizeof(Execute) + monitorAmount * (sizeof(Monitor) + sizeof(MaximizedContainer) + sizeof(xcb_window_t)) + (hasFlag(AllowCommandSending)? 257 : 0)))){
			printError("not enough ram, could not store general data");
			free(reply);
			setMode(Exit);
			goto emergencyExit;
		}
		shortcutStart = (Shortcut *)userData;
		shortcutWall = shortcutStart + shortcutAmount;
		buttonStart = (Button *)shortcutWall;
		buttonWall = buttonStart + buttonAmount;
		executeStart = (Execute *)buttonWall;
		executeWall = executeStart + executeAmount;
		monitorStart = (Monitor *)executeWall;
		monitorWall = monitorStart + monitorAmount;
		maximizedContainerStart = (MaximizedContainer *)monitorWall;
		maximizedContainerWall = maximizedContainerStart + monitorAmount;
		gridStart = (xcb_window_t *)maximizedContainerWall;
		gridWall = gridStart + monitorAmount;
		genericPointer = xcb_randr_get_screen_resources_crtcs((xcb_randr_get_screen_resources_reply_t *)reply);
		free(reply);
		monitorCurrent = monitorStart;
		maximizedContainerCurrent = maximizedContainerStart;
		gridCurrent = gridStart;
		attribute.a0 = 0x00000000;
		attribute.a1 = 0x00000000;
		attribute.a2 = true;
		attribute.a3 = colormap;
		storeMonitors:{
			if(!(reply = xcb_randr_get_crtc_info_reply(connection, xcb_randr_get_crtc_info_unchecked(connection, *(xcb_randr_crtc_t *)genericPointer, XCB_CURRENT_TIME), NULL))){
				(*monitorCurrent).x = 0;
				(*monitorCurrent).y = 0;
				(*monitorCurrent).width = 0;
				(*monitorCurrent).height = 0;
			}else{
				(*monitorCurrent).x = (*(xcb_randr_get_crtc_info_reply_t *)reply).x;
				(*monitorCurrent).y = (*(xcb_randr_get_crtc_info_reply_t *)reply).y;
				(*monitorCurrent).width = (*(xcb_randr_get_crtc_info_reply_t *)reply).width;
				(*monitorCurrent).height = (*(xcb_randr_get_crtc_info_reply_t *)reply).height;
				free(reply);
			}
			width = (*monitorCurrent).width / 3;
			height = (*monitorCurrent).height / 3;
			if(gridMaxWidth > width){
				gridMaxWidth = width;
			}
			if(gridMaxHeight > height){
				gridMaxHeight = height;
			}
			(*maximizedContainerCurrent).window = XCB_NONE;
			(*maximizedContainerCurrent).subwindow = XCB_NONE;
			*gridCurrent = xcb_generate_id(connection);
			xcb_create_window(connection, depth, *gridCurrent, (*screen).root, (*monitorCurrent).x, (*monitorCurrent).y, (*monitorCurrent).width, (*monitorCurrent).height, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, visual, XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_OVERRIDE_REDIRECT | XCB_CW_COLORMAP, &attribute);
			if(++monitorCurrent < monitorWall){
				genericPointer = (xcb_randr_crtc_t *)genericPointer + 1;
				++maximizedContainerCurrent;
				++gridCurrent;
				goto storeMonitors;
			}
		}



		{
			Command *cursor = &snapPosition.s0;
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
		motionContainerMinimalMoveBorder = 1;
		motionContainerMinimalResizeBorder = 1;
		snappingBorder = 1;
		snappingDivisorX = 2;
		snappingDivisorY = 2;
		snappingOffsetUp = 5;
		snappingOffsetDown = 5;
		snappingOffsetLeft = 5;
		snappingOffsetRight = 5;
		snappingOffsetX = snappingOffsetLeft + snappingOffsetRight;
		snappingOffsetY = snappingOffsetUp + snappingOffsetDown;
		setMotionAction(None);



		shortcutCurrent = shortcutStart;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 39;
		(*shortcutCurrent).command = ExecuteCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 12;
		(*shortcutCurrent).command = FloatingModeCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 13;
		(*shortcutCurrent).command = GriddingModeCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 14;
		(*shortcutCurrent).command = TilingModeCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 42;
		(*shortcutCurrent).command = ToggleGridVisibilityCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 43;
		(*shortcutCurrent).command = ToggleGapsCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1;
		(*shortcutCurrent).code = 38;
		(*shortcutCurrent).command = AttachCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 27;
		(*shortcutCurrent).command = CascadeCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 9;
		(*shortcutCurrent).command = RevolveMonitorsNextCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1;
		(*shortcutCurrent).code = 88;
		(*shortcutCurrent).command = MoveBottomCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1;
		(*shortcutCurrent).code = 83;
		(*shortcutCurrent).command = MoveLeftCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1;
		(*shortcutCurrent).code = 85;
		(*shortcutCurrent).command = MoveRightCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1;
		(*shortcutCurrent).code = 79;
		(*shortcutCurrent).command = MoveTopLeftCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1;
		(*shortcutCurrent).code = 81;
		(*shortcutCurrent).command = MoveTopRightCommand;
		++shortcutCurrent;
		(*shortcutCurrent).code = 87;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1;
		(*shortcutCurrent).command = MoveBottomLeftCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1;
		(*shortcutCurrent).code = 89;
		(*shortcutCurrent).command = MoveBottomRightCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1;
		(*shortcutCurrent).code = 84;
		(*shortcutCurrent).command = MoveCenterCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1;
		(*shortcutCurrent).code = 80;
		(*shortcutCurrent).command = MoveFullCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 58;
		(*shortcutCurrent).command = MoveNextMonitorCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 58;
		(*shortcutCurrent).command = MovePreviousMonitorCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 111;
		(*shortcutCurrent).command = MoveAboveMonitorCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 116;
		(*shortcutCurrent).command = MoveBelowMonitorCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 113;
		(*shortcutCurrent).command = MoveLeftMonitorCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 114;
		(*shortcutCurrent).command = MoveRightMonitorCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 38;
		(*shortcutCurrent).command = ToggleAddRemoveGridCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 111;
		(*shortcutCurrent).command = MoveUpGridCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 116;
		(*shortcutCurrent).command = MoveDownGridCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 113;
		(*shortcutCurrent).command = MoveLeftGridCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 114;
		(*shortcutCurrent).command = MoveRightGridCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_1 | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 80;
		(*shortcutCurrent).command = ExtendUpCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_1 | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 88;
		(*shortcutCurrent).command = ExtendDownCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_1 | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 83;
		(*shortcutCurrent).command = ExtendLeftCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_1 | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 85;
		(*shortcutCurrent).command = ExtendRightCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_1 | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 79;
		(*shortcutCurrent).command = ExtendUpLeftCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_1 | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 81;
		(*shortcutCurrent).command = ExtendUpRightCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_1 | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 87;
		(*shortcutCurrent).command = ExtendDownLeftCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_1 | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 89;
		(*shortcutCurrent).command = ExtendDownRightCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 80;
		(*shortcutCurrent).command = ShrinkUpCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 88;
		(*shortcutCurrent).command = ShrinkDownCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 83;
		(*shortcutCurrent).command = ShrinkLeftCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 85;
		(*shortcutCurrent).command = ShrinkRightCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 79;
		(*shortcutCurrent).command = ShrinkUpLeftCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 81;
		(*shortcutCurrent).command = ShrinkUpRightCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 87;
		(*shortcutCurrent).command = ShrinkDownLeftCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT | XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 89;
		(*shortcutCurrent).command = ShrinkDownRightCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_NONE;
		(*shortcutCurrent).code = 95;
		(*shortcutCurrent).command = FullscreenCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_SHIFT;
		(*shortcutCurrent).code = 95;
		(*shortcutCurrent).command = BigscreenCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_CONTROL | XCB_MOD_MASK_1;
		(*shortcutCurrent).code = 40;
		(*shortcutCurrent).command = DetachCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 24;
		(*shortcutCurrent).command = CloseCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 45;
		(*shortcutCurrent).command = KillCommand;
		++shortcutCurrent;
		(*shortcutCurrent).masks = XCB_MOD_MASK_4;
		(*shortcutCurrent).code = 57;
		(*shortcutCurrent).command = MoveResizeCommand;



		buttonCurrent = buttonStart;
		(*buttonCurrent).masks = XCB_MOD_MASK_4;
		(*buttonCurrent).code = XCB_BUTTON_INDEX_4;
		(*buttonCurrent).command = EnlargeGridBothCommand;
		++buttonCurrent;
		(*buttonCurrent).masks = XCB_MOD_MASK_4;
		(*buttonCurrent).code = XCB_BUTTON_INDEX_5;
		(*buttonCurrent).command = ShrinkGridBothCommand;
		++buttonCurrent;
		(*buttonCurrent).masks = XCB_MOD_MASK_4;
		(*buttonCurrent).code = XCB_BUTTON_INDEX_1;
		(*buttonCurrent).command = MoveResizeCommand;



		rootShortcutAmount = 9;
		rootButtonAmount = 2;



		genericWindow = (*screen).root;
		if(rootShortcutAmount){
			shortcutCurrent = shortcutStart;
			shortcutWall = shortcutStart + rootShortcutAmount;
			grabRootKey:{
				if((*shortcutCurrent).code != XCB_GRAB_ANY){
					xcb_grab_key(connection, true, genericWindow, (*shortcutCurrent).masks, (*shortcutCurrent).code, XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC);
				}
				if(++shortcutCurrent < shortcutWall){
					goto grabRootKey;
				}
			}
			shortcutWall = shortcutStart + shortcutAmount;
		}
		if(rootButtonAmount){
			buttonCurrent = buttonStart;
			buttonWall = buttonStart + rootButtonAmount;
			grabRootButton:{
				if((*buttonCurrent).code != XCB_GRAB_ANY){
					xcb_grab_button(connection, true, genericWindow, XCB_EVENT_MASK_NO_EVENT, XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC, XCB_NONE, XCB_NONE, (*buttonCurrent).code, (*buttonCurrent).masks);
				}
				if(++buttonCurrent < buttonWall){
					goto grabRootButton;
				}
			}
			buttonWall = buttonStart + buttonAmount;
		}
		if(floatingWindowDivisor < 1 || floatingWindowDivisor > 10){
			floatingWindowDivisor = 1;
		}
		if(floatingMinimumWidth < program.borderX + 1){
			floatingMinimumWidth = program.borderX + 1;
		}
		if(floatingMinimumHeight < program.borderY + 1){
			floatingMinimumHeight = program.borderY + 1;
		}
		if(tilingMinimumWidth < program.borderX + 1){
			tilingMinimumWidth = program.borderX + 1;
		}
		if(tilingMinimumHeight < program.borderY + 1){
			tilingMinimumHeight = program.borderY + 1;
		}
		if(hasOption(TilingUseGaps)){
			gapsX = tilingGapsX;
			gapsY = tilingGapsY;
		}else{
			gapsX = 0;
			gapsY = 0;
		}
		if(gridMinWidth > gridMaxWidth){
			gridMinWidth = gridMaxWidth;
		}
		if(gridMinHeight > gridMaxHeight){
			gridMinHeight = gridMaxHeight;
		}
		if(gridWidth > gridMaxWidth){
			gridWidth = gridMaxWidth;
		}else if(gridWidth < gridMinWidth){
			gridWidth = gridMinWidth;
		}
		if(gridHeight > gridMaxHeight){
			gridHeight = gridMaxHeight;
		}else if(gridHeight < gridMinHeight){
			gridHeight = gridMinHeight;
		}
		attribute.a0 = snappingBorder;
		xcb_configure_window(connection, motionContainerSnappingWindow, XCB_CONFIG_WINDOW_BORDER_WIDTH, &attribute);
		attribute.a0 = program.colorMotionContainerSnappingBackground;
		attribute.a1 = program.colorMotionContainerSnappingBorder;
		xcb_change_window_attributes(connection, motionContainerSnappingWindow, XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL, &attribute);
		attribute.a0 = program.colorMotionContainerGlassBackground;
		attribute.a1 = program.colorMotionContainerGlassBorder;
		xcb_change_window_attributes(connection, motionContainerGlass, XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL, &attribute);
		if(hasFlag(AllowCommandSending)){
			pthread_create(&thread, NULL, commandServer, containerStart);
		}
		if(isGridMapped){
			goto showGrid;
		}
	}
	eventLoop:{
		xcb_flush(connection);
		free(event);
		if(e){
			event = e;
			e = NULL;
		}else if(hasInputMethod(Enter) && command){
			xcb_sync();
			if(!(event = xcb_poll_for_event(connection))){
				if(printConnectionError()){
					goto eventLoopExit;
				}
				command = NoCommand;
				goto waitForEvent;
			}
		}else{
			waitForEvent:{
				if(!(event = xcb_wait_for_event(connection))){
					if(printConnectionError()){
						goto eventLoopExit;
					}
					goto waitForEvent;
				}
			}
		}
		if((*event).response_type > 128){
			(*event).response_type -= 128;
		}
#if DEBUG == true
		printEvent((*event).response_type);
#endif
		switch((*event).response_type){
			case XCB_NONE:{
				genericError = (xcb_generic_error_t *)event;
				printXCBError();
				goto eventLoop;
			}
			case XCB_KEY_PRESS:{
				goto keyPressEvent;
			}
			case XCB_KEY_RELEASE:{
				goto keyReleaseEvent;
			}
			case XCB_BUTTON_PRESS:{
				goto buttonPressEvent;
			}
			case XCB_BUTTON_RELEASE:{
				goto buttonReleaseEvent;
			}
			case XCB_MOTION_NOTIFY:{
				goto motionNotifyEvent;
			}
			case XCB_ENTER_NOTIFY:{
				goto enterNotifyEvent;
			}
			case XCB_FOCUS_IN:{
				goto eventLoop;
			}
			case XCB_FOCUS_OUT:{
				goto eventLoop;
			}
			case XCB_DESTROY_NOTIFY:{
				goto destroyNotifyEvent;
			}
			case XCB_UNMAP_NOTIFY:{
				goto unmapNotifyEvent;
			}
			case XCB_MAP_REQUEST:{
				goto mapRequestEvent;
			}
			case XCB_CONFIGURE_NOTIFY:{
				if(containerAmount && findWindow((*(xcb_configure_notify_event_t *)event).event, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
					printError("over");
				}else if(containerAmount && findWindow((*(xcb_configure_notify_event_t *)event).event, &(*containerStart).subwindow, sizeof(Container), containerAmount, &current)){
					printError("sub");
				}
				goto eventLoop;
			}
			case XCB_CONFIGURE_REQUEST:{
				goto configureRequestEvent;
			}
			case XCB_CLIENT_MESSAGE:{
				goto clientMessageEvent;
			}
			case XCB_MAPPING_NOTIFY:{
				goto eventLoop;
			}
			case XCB_RANDR_SCREEN_CHANGE_NOTIFY:{
				goto screenChangeNotifyEvent;
			}
			default:{
				if(!mustOpenErrorStream || (errorStream = fopen(errorPath, "a"))){
					printUnexpectedEvent((*event).response_type);
					if(mustOpenErrorStream){
						fclose(errorStream);
					}
				}
				goto eventLoop;
			}
		}
		keyPressEvent:{
			if(shortcutAmount){
				shortcutCurrent = shortcutStart;
				findShortcut:{
					if(isShortcut(shortcutCurrent, event)){
						command = (*shortcutCurrent).command;
						if(isAnyMotionAction() && !isCommand(CancelMoveResize)){
							goto keyButtonRelease;
						}
						genericWindow = (*(xcb_key_press_event_t *)event).event;
						goto findCommand;
					}
					if(++shortcutCurrent < shortcutWall){
						goto findShortcut;
					}
				}
			}
			goto eventLoop;
		}
		keyReleaseEvent:{
			if(isAnyMotionAction() && shortcutAmount){
				goto keyButtonRelease;
			}
			goto eventLoop;
		}
		buttonPressEvent:{
			if(buttonAmount){
				buttonCurrent = buttonStart;
				findButton:{
					if(isButton(buttonCurrent, event)){
						command = (*buttonCurrent).command;
						if(isAnyMotionAction() && !isCommand(CancelMoveResize)){
							goto keyButtonRelease;
						}
						genericWindow = (*(xcb_button_press_event_t *)event).event;
						goto findCommand;
					}
					if(++buttonCurrent < buttonWall){
						goto findButton;
					}
				}
			}
			goto eventLoop;
		}
		buttonReleaseEvent:{
			if(isAnyMotionAction() && buttonAmount){
				keyButtonRelease:{
					xcb_unmap_window(connection, motionContainerGlass);
					switch(motionContainerAction){
						case MoveMotionAction:{
							setMotionAction(None);
							if(isAnyMotionSubaction()){
								if(hasMotionOption(SnappingMapped)){
									xcb_unmap_window(connection, motionContainerSnappingWindow);
								}
								command = *(&snapPosition.s0 + motionContainerSubaction - SnappingMotionSubactionOffset);
								if(command){
									if(hasOption(FloatingMinimalMove)){
										genericWindow = motionContainerWindow;
										motionContainerWindow = motionContainerMinimalWindow;
										motionContainerMinimalWindow = genericWindow;
										genericUnsignedInteger = shadow;
										shadow = motionContainerMinimalMoveBorder;
										motionContainerMinimalMoveBorder = genericUnsignedInteger;
										xcb_unmap_window(connection, genericWindow);
									}
									if(hasPointerInfo(Move)){
										addFlag(SnapInMonitor);
									}
									genericWindow = motionContainerWindow;
									goto findCommand;
								}
							}
							if(hasOption(FloatingMinimalMove)){
								if((reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, motionContainerWindow), NULL))){
									attribute.a0 = (*(xcb_get_geometry_reply_t *)reply).x + shadow - motionContainerMinimalMoveBorder;
									attribute.a1 = (*(xcb_get_geometry_reply_t *)reply).y + shadow - motionContainerMinimalMoveBorder;
									free(reply);
									xcb_configure_window(connection, motionContainerMinimalWindow, XCB_CONFIG_WINDOW_X_Y, &attribute);
								}
								genericWindow = motionContainerWindow;
								motionContainerWindow = motionContainerMinimalWindow;
								motionContainerMinimalWindow = genericWindow;
								genericUnsignedInteger = shadow;
								shadow = motionContainerMinimalMoveBorder;
								motionContainerMinimalMoveBorder = genericUnsignedInteger;
								xcb_unmap_window(connection, genericWindow);
							}
							goto eventLoop;
						}
						case ResizeMotionAction:{
							setMotionAction(None);
							if(hasOption(FloatingMinimalResize)){
								if((reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, motionContainerWindow), NULL))){
									attribute.a0 = (*(xcb_get_geometry_reply_t *)reply).x + motionContainerMinimalMoveBorder - shadow;
									attribute.a1 = (*(xcb_get_geometry_reply_t *)reply).y + motionContainerMinimalMoveBorder - shadow;
									attribute.a2 = (*(xcb_get_geometry_reply_t *)reply).width;
									attribute.a3 = (*(xcb_get_geometry_reply_t *)reply).height;
									free(reply);
									xcb_configure_window(connection, motionContainerMinimalWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
									attribute.a2 -= program.borderX;
									attribute.a3 -= program.borderY;
									xcb_configure_window(connection, motionContainerSubwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
								}
								genericWindow = motionContainerWindow;
								motionContainerWindow = motionContainerMinimalWindow;
								motionContainerMinimalWindow = genericWindow;
								xcb_unmap_window(connection, genericWindow);
							}
							goto eventLoop;
						}
						default:{
							setMotionAction(None);
							goto eventLoop;
						}
					}
				}
			}
			goto eventLoop;
		}
		motionNotifyEvent:{
			consumeRedundantEvents(event, e, XCB_MOTION_NOTIFY);
			switch(motionContainerAction){
				case MoveMotionAction:{
					if(hasOption(FloatingAllowMonitorSticking)){
						current = getWindowMonitor(motionContainerWindow);
						monitorCurrent = monitorStart + current;
						if(current != motionContainerPreviousMonitor){
							if(hasMotionOption(LockedX) && x != (*monitorCurrent).x && x + (int)width != (*monitorCurrent).x + (int)(*monitorCurrent).width){
								removeMotionOption(LockedX);
							}
							if(hasMotionOption(LockedY) && y != (*monitorCurrent).y && y + (int)height != (*monitorCurrent).y + (int)(*monitorCurrent).height){
								removeMotionOption(LockedY);
							}
						}
						motionContainerPreviousMonitor = current;
						attributeMasks = XCB_NONE;
						if(closedOpenInterval(x, (*monitorCurrent).x, (*monitorCurrent).x + floatingStickyThresholdX)){
							if(!hasMotionOption(LockedX)){
								x = (*monitorCurrent).x;
								escapeX = (*motionNotify).root_x + floatingDistanceToTravelX;
								attribute.a0 = x - shadow;
								genericPointer = (WindowAttribute *)genericPointer + 1;
								attributeMasks |= XCB_CONFIG_WINDOW_X;
								addMotionOption(LockedX);
							}else if((*motionNotify).root_x >= escapeX){
								removeMotionOption(LockedX);
								goto unlockedX;
							}
						}else if(closedInterval(x + (int)width, (*monitorCurrent).x + (int)(*monitorCurrent).width - floatingStickyThresholdX, (*monitorCurrent).x + (int)(*monitorCurrent).width)){
							if(!hasMotionOption(LockedX)){
								x = (*monitorCurrent).x + (*monitorCurrent).width - width;
								escapeX = (*motionNotify).root_x - floatingDistanceToTravelX;
								attribute.a0 = x - shadow;
								genericPointer = (WindowAttribute *)genericPointer + 1;
								attributeMasks |= XCB_CONFIG_WINDOW_X;
								addMotionOption(LockedX);
							}else if((*motionNotify).root_x <= escapeX){
								removeMotionOption(LockedX);
								goto unlockedX;
							}
						}else if(!hasMotionOption(LockedX)){
							unlockedX:{
								attribute.a0 = (*motionNotify).root_x - pointerOffsetX;
								x = attribute.a0 + shadow;
								genericPointer = (WindowAttribute *)genericPointer + 1;
								attributeMasks |= XCB_CONFIG_WINDOW_X;
							}
						}
						if(closedOpenInterval(y, (*monitorCurrent).y, (*monitorCurrent).y + floatingStickyThresholdY)){
							if(!hasMotionOption(LockedY)){
								y = (*monitorCurrent).y;
								escapeY = (*motionNotify).root_y + floatingDistanceToTravelY;
								*(WindowAttribute *)genericPointer = y - shadow;
								attributeMasks |= XCB_CONFIG_WINDOW_Y;
								addMotionOption(LockedY);
							}else if((*motionNotify).root_y >= escapeY){
								removeMotionOption(LockedY);
								goto unlockedY;
							}
						}else if(closedInterval(y + (int)height, (*monitorCurrent).y + (int)(*monitorCurrent).height - floatingStickyThresholdY, (*monitorCurrent).y + (int)(*monitorCurrent).height)){
							if(!hasMotionOption(LockedY)){
								y = (*monitorCurrent).y + (*monitorCurrent).height - height;
								escapeY = (*motionNotify).root_y - floatingDistanceToTravelY;
								*(WindowAttribute *)genericPointer = y - shadow;
								attributeMasks |= XCB_CONFIG_WINDOW_Y;
								addMotionOption(LockedY);
							}else if((*motionNotify).root_y <= escapeY){
								removeMotionOption(LockedY);
								goto unlockedY;
							}
						}else if(!hasMotionOption(LockedY)){
							unlockedY:{
								*(WindowAttribute *)genericPointer = (*motionNotify).root_y - pointerOffsetY;
								y = *(WindowAttribute *)genericPointer + shadow;
								attributeMasks |= XCB_CONFIG_WINDOW_Y;
							}
						}
						if(attributeMasks){
							xcb_configure_window(connection, motionContainerWindow, attributeMasks, &attribute);
							genericPointer = &attribute;
						}
					}else{
						attribute.a0 = (*motionNotify).root_x - pointerOffsetX;
						attribute.a1 = (*motionNotify).root_y - pointerOffsetY;
						xcb_configure_window(connection, motionContainerWindow, XCB_CONFIG_WINDOW_X_Y, &attribute);
					}
					if(hasOption(FloatingAllowSnapping)){
						monitorCurrent = monitorStart + getPointerMonitor();
						if(closedOpenInterval((*motionNotify).root_y, (*monitorCurrent).y, (*monitorCurrent).y + floatingSnappingThreshold)){
							if(closedOpenInterval((*motionNotify).root_x, (*monitorCurrent).x, (*monitorCurrent).x + floatingSnappingThreshold)){
								if(!isMotionSubaction(TopLeftSnapping)){
									setMotionSubaction(TopLeftSnapping);
									goto moveSnappingWindow;
								}
								goto eventLoop;
							}
							if(closedOpenInterval((*motionNotify).root_x, (*monitorCurrent).x + floatingSnappingThreshold, (*monitorCurrent).x + (int)(*monitorCurrent).width - floatingSnappingThreshold)){
								if(!isMotionSubaction(TopSnapping)){
									setMotionSubaction(TopSnapping);
									goto moveSnappingWindow;
								}
								goto eventLoop;
							}
							if(!isMotionSubaction(TopRightSnapping)){
								setMotionSubaction(TopRightSnapping);
								goto moveSnappingWindow;
							}
							goto eventLoop;
						}
						if(closedOpenInterval((*motionNotify).root_y, (*monitorCurrent).y + floatingSnappingThreshold, (*monitorCurrent).y + (int)(*monitorCurrent).height - floatingSnappingThreshold)){
							if(closedOpenInterval((*motionNotify).root_x, (*monitorCurrent).x, (*monitorCurrent).x + floatingSnappingThreshold)){
								if(!isMotionSubaction(LeftSnapping)){
									setMotionSubaction(LeftSnapping);
									goto moveSnappingWindow;
								}
								goto eventLoop;
							}
							if(closedOpenInterval((*motionNotify).root_x, (*monitorCurrent).x + floatingSnappingThreshold, (*monitorCurrent).x + (int)(*monitorCurrent).width - floatingSnappingThreshold)){
								if(!isMotionSubaction(CenterSnapping)){
									setMotionSubaction(CenterSnapping);
									goto moveSnappingWindow;
								}
								goto eventLoop;
							}
							if(!isMotionSubaction(RightSnapping)){
								setMotionSubaction(RightSnapping);
								goto moveSnappingWindow;
							}
							goto eventLoop;
						}
						if(closedOpenInterval((*motionNotify).root_y, (*monitorCurrent).y + (int)(*monitorCurrent).height - floatingSnappingThreshold, (*monitorCurrent).y + (int)(*monitorCurrent).height)){
							if(closedOpenInterval((*motionNotify).root_x, (*monitorCurrent).x, (*monitorCurrent).x + floatingSnappingThreshold)){
								if(!isMotionSubaction(BottomLeftSnapping)){
									setMotionSubaction(BottomLeftSnapping);
									goto moveSnappingWindow;
								}
								goto eventLoop;
							}
							if(closedOpenInterval((*motionNotify).root_x, (*monitorCurrent).x + floatingSnappingThreshold, (*monitorCurrent).x + (int)(*monitorCurrent).width - floatingSnappingThreshold)){
								if(!isMotionSubaction(BottomSnapping)){
									setMotionSubaction(BottomSnapping);
									goto moveSnappingWindow;
								}
								goto eventLoop;
							}
							if(!isMotionSubaction(BottomRightSnapping)){
								setMotionSubaction(BottomRightSnapping);
								moveSnappingWindow:{
									if(motionContainerSnappingWindow){
										if(hasOption(FloatingSnappingWindowFollowGrid)){
											snappingDivisorX = gridWidth;
											snappingDivisorY = gridHeight;
										}
										switch(*(&snapPosition.s0 + motionContainerSubaction - SnappingMotionSubactionOffset)){
											case MoveTopCommand:{
												attribute.a0 = (*monitorCurrent).x + snappingOffsetLeft - snappingBorder;
												attribute.a1 = (*monitorCurrent).y + snappingOffsetUp - snappingBorder;
												attribute.a2 = (*monitorCurrent).width - snappingOffsetX;
												attribute.a3 = (*monitorCurrent).height / snappingDivisorY - snappingOffsetY;
												break;
											}
											case MoveBottomCommand:{
												attribute.a0 = (*monitorCurrent).x + snappingOffsetLeft - snappingBorder;
												attribute.a3 = (*monitorCurrent).height / snappingDivisorY - snappingOffsetY;
												attribute.a1 = (*monitorCurrent).y + (*monitorCurrent).height - attribute.a3 - snappingBorder - snappingOffsetDown;
												attribute.a2 = (*monitorCurrent).width - snappingOffsetX;
												break;
											}
											case MoveLeftCommand:{
												attribute.a0 = (*monitorCurrent).x + snappingOffsetLeft - snappingBorder;
												attribute.a1 = (*monitorCurrent).y + snappingOffsetUp - snappingBorder;
												attribute.a2 = (*monitorCurrent).width / snappingDivisorX - snappingOffsetX;
												attribute.a3 = (*monitorCurrent).height - snappingOffsetY;
												break;
											}
											case MoveRightCommand:{
												attribute.a1 = (*monitorCurrent).y + snappingOffsetUp - snappingBorder;
												attribute.a2 = (*monitorCurrent).width / snappingDivisorX - snappingOffsetX;
												attribute.a0 = (*monitorCurrent).x + (*monitorCurrent).width - attribute.a2 - snappingBorder - snappingOffsetRight;
												attribute.a3 = (*monitorCurrent).height - snappingOffsetY;
												break;
											}
											case MoveTopLeftCommand:{
												attribute.a0 = (*monitorCurrent).x + snappingOffsetLeft - snappingBorder;
												attribute.a1 = (*monitorCurrent).y + snappingOffsetUp - snappingBorder;
												attribute.a2 = (*monitorCurrent).width / snappingDivisorX - snappingOffsetX;
												attribute.a3 = (*monitorCurrent).height / snappingDivisorY - snappingOffsetY;
												break;
											}
											case MoveTopRightCommand:{
												attribute.a1 = (*monitorCurrent).y + snappingOffsetUp - snappingBorder;
												attribute.a2 = (*monitorCurrent).width / snappingDivisorX - snappingOffsetX;
												attribute.a0 = (*monitorCurrent).x + (*monitorCurrent).width - attribute.a2 - snappingBorder - snappingOffsetRight;
												attribute.a3 = (*monitorCurrent).height / snappingDivisorY - snappingOffsetY;
												break;
											}
											case MoveBottomLeftCommand:{
												attribute.a0 = (*monitorCurrent).x + snappingOffsetLeft - snappingBorder;
												attribute.a3 = (*monitorCurrent).height / snappingDivisorY - snappingOffsetY;
												attribute.a1 = (*monitorCurrent).y + (*monitorCurrent).height - attribute.a3 - snappingBorder - snappingOffsetDown;
												attribute.a2 = (*monitorCurrent).width / snappingDivisorX - snappingOffsetX;
												break;
											}
											case MoveBottomRightCommand:{
												attribute.a2 = (*monitorCurrent).width / snappingDivisorX - snappingOffsetX;
												attribute.a3 = (*monitorCurrent).height / snappingDivisorY - snappingOffsetY;
												attribute.a0 = (*monitorCurrent).x + (*monitorCurrent).width - attribute.a2 - snappingBorder - snappingOffsetRight;
												attribute.a1 = (*monitorCurrent).y + (*monitorCurrent).height - attribute.a3 - snappingBorder - snappingOffsetDown;
												break;
											}
											case MoveCenterCommand:{
												attribute.a2 = (*monitorCurrent).width / snappingDivisorX - snappingOffsetX;
												attribute.a3 = (*monitorCurrent).height / snappingDivisorY - snappingOffsetY;
												attribute.a0 = (*monitorCurrent).x + ((*monitorCurrent).width - attribute.a2) / 2 - snappingBorder;
												attribute.a1 = (*monitorCurrent).y + ((*monitorCurrent).height - attribute.a3) / 2 - snappingBorder;
												break;
											}
											case MoveFullCommand:{
												attribute.a0 = (*monitorCurrent).x + snappingOffsetLeft - snappingBorder;
												attribute.a1 = (*monitorCurrent).y + snappingOffsetUp - snappingBorder;
												attribute.a2 = (*monitorCurrent).width - snappingOffsetX;
												attribute.a3 = (*monitorCurrent).height - snappingOffsetY;
												break;
											}
											default:{
												if(hasMotionOption(SnappingMapped)){
													xcb_unmap_window(connection, motionContainerSnappingWindow);
													removeMotionOption(SnappingMapped);
												}
												setMotionSubaction(None);
												goto eventLoop;
											}
										}
										xcb_configure_window(connection, motionContainerSnappingWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
										if(!hasMotionOption(SnappingMapped)){
											attribute.a0 = XCB_STACK_MODE_BELOW;
											if(isGridMapped){
												gridCurrent = gridStart;
												lowerGrid:{
													xcb_configure_window(connection, *gridCurrent, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
													if(++gridCurrent < gridWall){
														goto lowerGrid;
													}
												}
											}
											xcb_configure_window(connection, motionContainerSnappingWindow, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
											xcb_map_window(connection, motionContainerSnappingWindow);
											addMotionOption(SnappingMapped);
										}
										goto eventLoop;
									}
								}
							}
						}
					}
					goto eventLoop;
				}
				case ResizeMotionAction:{
					switch(motionContainerSubaction){
						case UpResizeMotionSubaction:{
							height += y + pointerOffsetY - (*motionNotify).root_y;
							if((int)height < (int)floatingMinimumHeight){
								y = (*motionNotify).root_y - pointerOffsetY + height - floatingMinimumHeight;
								height = floatingMinimumHeight;
							}else{
								y = (*motionNotify).root_y - pointerOffsetY;
							}
							attribute.a0 = y;
							attribute.a1 = height;
							xcb_configure_window(connection, motionContainerWindow, XCB_CONFIG_WINDOW_Y_HEIGHT, &attribute);
							break;
						}
						case DownResizeMotionSubaction:{
							height -= y + pointerOffsetY - (*motionNotify).root_y;
							if((int)height < (int)floatingMinimumHeight){
								y = (*motionNotify).root_y - pointerOffsetY + floatingMinimumHeight - height;
								height = floatingMinimumHeight;
							}else{
								y = (*motionNotify).root_y - pointerOffsetY;
							}
							attribute.a0 = height;
							xcb_configure_window(connection, motionContainerWindow, XCB_CONFIG_WINDOW_HEIGHT, &attribute);
							break;
						}
						case LeftResizeMotionSubaction:{
							width += x + pointerOffsetX - (*motionNotify).root_x;
							if((int)width < (int)floatingMinimumWidth){
								x = (*motionNotify).root_x - pointerOffsetX + width - floatingMinimumWidth;
								width = floatingMinimumWidth;
							}else{
								x = (*motionNotify).root_x - pointerOffsetX;
							}
							attribute.a0 = x;
							attribute.a1 = width;
							xcb_configure_window(connection, motionContainerWindow, XCB_CONFIG_WINDOW_X_WIDTH, &attribute);
							break;
						}
						case RightResizeMotionSubaction:{
							width -= x + pointerOffsetX - (*motionNotify).root_x;
							if((int)width < (int)floatingMinimumWidth){
								x = (*motionNotify).root_x - pointerOffsetX + floatingMinimumWidth - width;
								width = floatingMinimumWidth;
							}else{
								x = (*motionNotify).root_x - pointerOffsetX;
							}
							attribute.a0 = width;
							xcb_configure_window(connection, motionContainerWindow, XCB_CONFIG_WINDOW_WIDTH, &attribute);
							break;
						}
						case UpLeftResizeMotionSubaction:{
							height += y + pointerOffsetY - (*motionNotify).root_y;
							width += x + pointerOffsetX - (*motionNotify).root_x;
							if((int)height < (int)floatingMinimumHeight){
								y = (*motionNotify).root_y - pointerOffsetY + height - floatingMinimumHeight;
								height = floatingMinimumHeight;
							}else{
								y = (*motionNotify).root_y - pointerOffsetY;
							}
							if((int)width < (int)floatingMinimumWidth){
								x = (*motionNotify).root_x - pointerOffsetX + width - floatingMinimumWidth;
								width = floatingMinimumWidth;
							}else{
								x = (*motionNotify).root_x - pointerOffsetX;
							}
							attribute.a0 = x;
							attribute.a1 = y;
							attribute.a2 = width;
							attribute.a3 = height;
							xcb_configure_window(connection, motionContainerWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
							break;
						}
						case UpRightResizeMotionSubaction:{
							height += y + pointerOffsetY - (*motionNotify).root_y;
							width -= x + pointerOffsetX - (*motionNotify).root_x;
							if((int)height < (int)floatingMinimumHeight){
								y = (*motionNotify).root_y - pointerOffsetY + height - floatingMinimumHeight;
								height = floatingMinimumHeight;
							}else{
								y = (*motionNotify).root_y - pointerOffsetY;
							}
							if((int)width < (int)floatingMinimumWidth){
								y = (*motionNotify).root_y - pointerOffsetY + height - floatingMinimumHeight;
								height = floatingMinimumHeight;
							}else{
								y = (*motionNotify).root_y - pointerOffsetY;
							}
							attribute.a0 = y;
							attribute.a1 = width;
							attribute.a2 = height;
							xcb_configure_window(connection, motionContainerWindow, XCB_CONFIG_WINDOW_Y_WIDTH_HEIGHT, &attribute);
							break;
						}
						case DownLeftResizeMotionSubaction:{
							height -= y + pointerOffsetY - (*motionNotify).root_y;
							width += x + pointerOffsetX - (*motionNotify).root_x;
							if((int)height < (int)floatingMinimumHeight){
								y = (*motionNotify).root_y - pointerOffsetY + floatingMinimumHeight - height;
								height = floatingMinimumHeight;
							}else{
								y = (*motionNotify).root_y - pointerOffsetY;
							}
							if((int)width < (int)floatingMinimumWidth){
								x = (*motionNotify).root_x - pointerOffsetX + width - floatingMinimumWidth;
								width = floatingMinimumWidth;
							}else{
								x = (*motionNotify).root_x - pointerOffsetX;
							}
							attribute.a0 = x;
							attribute.a1 = width;
							attribute.a2 = height;
							xcb_configure_window(connection, motionContainerWindow, XCB_CONFIG_WINDOW_X_WIDTH_HEIGHT, &attribute);
							break;
						}
						case DownRightResizeMotionSubaction:{
							height -= y + pointerOffsetY - (*motionNotify).root_y;
							width -= x + pointerOffsetX - (*motionNotify).root_x;
							if((int)height < (int)floatingMinimumHeight){
								y = (*motionNotify).root_y - pointerOffsetY + floatingMinimumHeight - height;
								height = floatingMinimumHeight;
							}else{
								y = (*motionNotify).root_y - pointerOffsetY;
							}
							if((int)width < (int)floatingMinimumWidth){
								x = (*motionNotify).root_x - pointerOffsetX + floatingMinimumWidth - width;
								width = floatingMinimumWidth;
							}else{
								x = (*motionNotify).root_x - pointerOffsetX;
							}
							attribute.a0 = width;
							attribute.a1 = height;
							xcb_configure_window(connection, motionContainerWindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute);
							break;
						}
						default:{
							goto keyButtonRelease;
						}
					}
					if(!hasOption(FloatingMinimalResize)){
						attribute.a0 = width - program.borderX;
						attribute.a1 = height - program.borderY;
						xcb_configure_window(connection, motionContainerSubwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute);
					}
					goto eventLoop;
				}
				default:{
					goto keyButtonRelease;
				}
			}
		}
		enterNotifyEvent:{
			if(!isAnyMotionAction() && !(focused && (*(xcb_enter_notify_event_t *)event).event == (*focused).window) && containerAmount && findWindow((*(xcb_enter_notify_event_t *)event).event, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				containerCurrent = containerStart + current;
				if(!hasContainerOption(*containerCurrent, Mapped)){
					goto eventLoop;
				}
				if(hasInputMethod(Enter)){
					genericUnsignedInteger = command;
					command = NoCommand;
					switch(program.managementMode){
						case FloatingManagementMode:{
							if(hasContainerOption(*containerCurrent, InGrid)){
								genericPointer = &inGridEnterInputException;
								break;
							}
							genericPointer = &floatingEnterInputException;
							break;
						}
						case GriddingManagementMode:{
							genericPointer = &griddingEnterInputException;
							break;
						}
						default:{
							genericPointer = &tilingEnterInputException;
							break;
						}
					}
					switch(genericUnsignedInteger){
						case ExecuteCommand:{
							if(hasEnterInputException(Execute)){
								goto eventLoop;
							}
							goto changeFocusedWindowBackground0;
						}
						case FloatingModeCommand:
						case GriddingModeCommand:
						case TilingModeCommand:{
							if(hasEnterInputException(ChangeManagementMode)){
								goto eventLoop;
							}
							goto changeFocusedWindowBackground0;
						}
						case CancelMoveResizeCommand:{
							if(hasEnterInputException(CancelMoveResize)){
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
							if(hasEnterInputException(ResizeGrid)){
								goto eventLoop;
							}
							goto changeFocusedWindowBackground0;
						}
						case ToggleGapsCommand:{
							if(hasEnterInputException(ToggleGaps)){
								goto eventLoop;
							}
							goto changeFocusedWindowBackground0;
						}
						case CascadeCommand:{
							if(hasEnterInputException(Cascade)){
								goto eventLoop;
							}
							goto changeFocusedWindowBackground0;
						}
						case AttachCommand:{
							if(hasEnterInputException(Attach)){
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
							if(hasEnterInputException(SwapMonitors)){
								goto eventLoop;
							}
							goto changeFocusedWindowBackground0;
						}
						case RevolveMonitorsNextCommand:
						case RevolveMonitorsPreviousCommand:
						case RevolveMonitorsAboveCommand:
						case RevolveMonitorsBelowCommand:
						case RevolveMonitorsLeftCommand:
						case RevolveMonitorsRightCommand:{
							if(hasEnterInputException(RevolveMonitors)){
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
							if(hasEnterInputException(MoveTo)){
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
							if(hasEnterInputException(MoveMonitor)){
								goto eventLoop;
							}
							goto changeFocusedWindowBackground0;
						}
						case AddToGridCommand:
						case RemoveFromGridCommand:
						case ToggleAddRemoveGridCommand:{
							if(hasEnterInputException(ToggleAddRemoveGrid)){
								goto eventLoop;
							}
							goto changeFocusedWindowBackground0;
						}
						case MoveUpGridCommand:
						case MoveDownGridCommand:
						case MoveLeftGridCommand:
						case MoveRightGridCommand:{
							if(hasEnterInputException(MoveGrid)){
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
							if(hasEnterInputException(Extend)){
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
							if(hasEnterInputException(Shrink)){
								goto eventLoop;
							}
							goto changeFocusedWindowBackground0;
						}
						case FullscreenCommand:
						case BigscreenCommand:{
							if(hasEnterInputException(Maximize)){
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
					if(focused){
						genericPointer = &program.colorContainerBackgroundFloating;
						changeFocusedWindowBackground1:{
							if(hasContainerOption(*focused, Maximized)){
								if(hasOption(MaximizedUseFocusedWindowColor)){
									findWindow((*focused).window, &(*maximizedContainerStart).window, sizeof(MaximizedContainer), monitorAmount, &current);
									if((*(maximizedContainerStart + current)).shouldChangeProperty){
										genericPointer = (ARGB *)genericPointer + 4;
										goto setFocusedWindowBackground;
									}
									genericPointer = (ARGB *)genericPointer + 5;
									goto setFocusedWindowBackground;
								}
							}else{
								switch(program.managementMode){
									case FloatingManagementMode:{
										if(hasContainerOption(*focused, InGrid)){
											if(hasOption(InGridUseFocusedWindowColor)){
												genericPointer = (ARGB *)genericPointer + 3;
												goto setFocusedWindowBackground;
											}
											break;
										}
										if(hasOption(FloatingUseFocusedWindowColor)){
											goto setFocusedWindowBackground;
										}
										break;
									}
									case GriddingManagementMode:{
										if(hasOption(GriddingUseFocusedWindowColor)){
											genericPointer = (ARGB *)genericPointer + 1;
											goto setFocusedWindowBackground;
										}
										break;
									}
									default:{
										if(hasOption(TilingUseFocusedWindowColor)){
											genericPointer = (ARGB *)genericPointer + 2;
											setFocusedWindowBackground:{
												xcb_change_window_attributes(connection, (*focused).window, XCB_CW_BACK_PIXEL, genericPointer);
												xcb_clear_area(connection, false, (*focused).window, 0, 0, 0, 0);
											}
										}
										break;
									}
								}
							}
						}
					}
					if(focused != containerCurrent){
						focused = containerCurrent;
						genericPointer = &program.colorFocusedContainerBackgroundFloating;
						goto changeFocusedWindowBackground1;
					}
				}
				attribute.a0 = XCB_STACK_MODE_ABOVE;
				xcb_configure_window(connection, (*focused).window, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
				xcb_set_input_focus(connection, XCB_INPUT_FOCUS_POINTER_ROOT, (*focused).subwindow, XCB_CURRENT_TIME);
			}
			goto eventLoop;
		}
		destroyNotifyEvent:{
			if(containerAmount && findWindow((*(xcb_destroy_notify_event_t *)event).window, &(*containerStart).subwindow, sizeof(Container), containerAmount, &current)){
				containerCurrent = containerStart + current;
				if(hasContainerOption(*containerCurrent, Mapped)){
					goto unmapWindow;
				}
				destroyWindow:{
					xcb_destroy_window(connection, (*containerCurrent).window);
					if(hasContainerOption(*containerCurrent, Maximized)){
						findWindow((*containerCurrent).window, &(*maximizedContainerStart).window, sizeof(MaximizedContainer), monitorAmount, &current);
						maximizedContainerCurrent = maximizedContainerStart + current;
						(*maximizedContainerCurrent).window = XCB_NONE;
						(*maximizedContainerCurrent).subwindow = XCB_NONE;
					}
					{
						Container c;
						--containerWall;
						pushOldContainerDown:{
							if(containerCurrent < containerWall){
								c = *containerCurrent;
								*containerCurrent = *(containerCurrent + 1);
								*(++containerCurrent) = c;
								goto pushOldContainerDown;
							}
						}
					}
					if(!(containerData = realloc(containerData, --containerAmount * sizeof(Container))) && containerAmount){
						printError("not enough ram, could not restore containers");
						setMode(Exit);
						goto eventLoopExit;
					}
					current = focused - containerStart;
					containerStart = (Container *)containerData;
					containerWall = containerStart + containerAmount;
					if(focused){
						focused = containerStart + current;
					}
				}
			}
			goto eventLoop;
		}
		unmapNotifyEvent:{
			if(containerAmount && findWindow((*(xcb_unmap_notify_event_t *)event).window, &(*containerStart).subwindow, sizeof(Container), containerAmount, &current)){
				containerCurrent = containerStart + current;
				unmapWindow:{
					attribute.a0 = XCB_STACK_MODE_ABOVE;
					xcb_configure_window(connection, glass, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
					xcb_map_window(connection, glass);
					xcb_flush(connection);
					xcb_set_input_focus(connection, XCB_INPUT_FOCUS_POINTER_ROOT, (*screen).root, XCB_CURRENT_TIME);
					xcb_unmap_window(connection, (*containerCurrent).window);
					if(isManagementMode(Tiling)){
						/*removeTilingWindow();*/
					}
					if(containerCurrent == focused){
						focused = NULL;
					}
					xcb_unmap_window(connection, glass);
					removeContainerOption(*containerCurrent, Mapped);
				}
				if((*event).response_type == XCB_DESTROY_NOTIFY){
					goto destroyWindow;
				}
			}
			goto eventLoop;
		}
		mapRequestEvent:{
			if(hasPointerInfo(Map)){
				current = getPointerMonitor();
			}else{
				current = getWindowMonitor((*(xcb_map_request_event_t *)event).window);
			}
			mapWindow:{
				const xcb_window_t subwindow = (*(xcb_map_request_event_t *)event).window;
				if(!(containerData = realloc(containerData, (containerAmount + 1) * sizeof(Container)))){
					printError("not enough ram, could not restore containers");
					setMode(Exit);
					goto eventLoopExit;
				}
				genericUnsignedInteger = focused - containerStart;
				containerStart = (Container *)containerData;
				containerWall = containerStart + containerAmount;
				if(focused){
					focused = containerStart + genericUnsignedInteger;
				}
				containerCurrent = containerWall;
				monitorCurrent = monitorStart + current;
				genericWindow = xcb_generate_id(connection);
				switch(program.managementMode){
					case FloatingManagementMode:{
						attribute.a0 = program.colorContainerBackgroundFloating;
						attribute.a2 = XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_FOCUS_CHANGE | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT         | XCB_EVENT_MASK_STRUCTURE_NOTIFY;
						genericUnsignedInteger = shadow;
						break;
					}
					case GriddingManagementMode:{
						attribute.a0 = program.colorContainerBackgroundGridding;
						attribute.a2 = XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_FOCUS_CHANGE | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT         | XCB_EVENT_MASK_STRUCTURE_NOTIFY;
						genericUnsignedInteger = 0;
						break;
					}
					default:{
						attribute.a0 = program.colorContainerBackgroundTiling;
						attribute.a2 = XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_FOCUS_CHANGE | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT         | XCB_EVENT_MASK_STRUCTURE_NOTIFY;
						genericUnsignedInteger = 0;
						break;
					}
				}
				attribute.a1 = program.colorContainerShadow;
				attribute.a3 = colormap;
				xcb_create_window(connection, depth, genericWindow, (*screen).root, 0, 0, 1, 1, genericUnsignedInteger, XCB_WINDOW_CLASS_INPUT_OUTPUT, visual, XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_EVENT_MASK | XCB_CW_COLORMAP, &attribute);
				if(shortcutAmount - rootShortcutAmount){
					shortcutCurrent = shortcutStart + rootShortcutAmount;
					grabContainerKey:{
						if((*shortcutCurrent).code != XCB_GRAB_ANY){
							xcb_grab_key(connection, true, genericWindow, (*shortcutCurrent).masks, (*shortcutCurrent).code, XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC);
						}
						if(++shortcutCurrent < shortcutWall){
							goto grabContainerKey;
						}
					}
				}
				if(buttonAmount - rootButtonAmount){
					buttonCurrent = buttonStart + rootButtonAmount;
					grabContainerButton:{
						if((*buttonCurrent).code != XCB_GRAB_ANY){
							xcb_grab_button(connection, true, genericWindow, XCB_EVENT_MASK_NO_EVENT, XCB_GRAB_MODE_ASYNC, XCB_GRAB_MODE_ASYNC, XCB_NONE, XCB_NONE, (*buttonCurrent).code, (*buttonCurrent).masks);
						}
						if(++buttonCurrent < buttonWall){
							goto grabContainerButton;
						}
					}
				}
				xcb_reparent_window(connection, subwindow, genericWindow, borderLeft, borderUp);
				xcb_map_window(connection, subwindow);
				if((reply = xcb_list_properties_reply(connection, xcb_list_properties_unchecked(connection, subwindow), NULL))){
					if((*(xcb_list_properties_reply_t *)reply).atoms_len){









						xcb_get_property_reply_t *property;
						xcb_atom_t *atom = xcb_list_properties_atoms((xcb_list_properties_reply_t *)reply);
						genericPointer = atom + (*(xcb_list_properties_reply_t *)reply).atoms_len;
						changeProperty:{
							if((property = xcb_get_property_reply(connection, xcb_get_property_unchecked(connection, false, subwindow, *atom, XCB_GET_PROPERTY_TYPE_ANY, 0, 100), NULL))){
								xcb_change_property(connection, XCB_PROP_MODE_REPLACE, genericWindow, *atom, (*property).type, (*property).format, xcb_get_property_value_length(property), xcb_get_property_value(property));
								free(property);
							}
							if(++atom < (xcb_atom_t *)genericPointer){
								goto changeProperty;
							}
						}









					}
					free(reply);
				}
				(*containerCurrent).window = genericWindow;
				(*containerCurrent).subwindow = subwindow;
				setContainerOption(*containerCurrent, Mapped);
				switch(program.managementMode){
					case FloatingManagementMode:{
						if(hasOption(FloatingFollowGrid)){
							attribute.a2 = (*monitorCurrent).width / gridWidth;
							attribute.a3 = (*monitorCurrent).height / gridHeight;
						}else{
							attribute.a2 = (*monitorCurrent).width / 2;
							attribute.a3 = (*monitorCurrent).height / 2;
						}
						attribute.a0 = (*monitorCurrent).x + ((*monitorCurrent).width - attribute.a2) / 2 - shadow;
						attribute.a1 = (*monitorCurrent).y + ((*monitorCurrent).height - attribute.a3) / 2 - shadow;
						{
							xcb_window_t lastCreatedWindow;
							if(containerAmount){
								lastCreatedWindow = (*(containerCurrent - 1)).window;
							}else{
								lastCreatedWindow = XCB_NONE;
							}
							if(isCascadeMode(Simple)){
								if(!lastCreatedWindow || hasContainerOption(*(containerCurrent - 1), InGrid) || hasContainerOption(*(containerCurrent - 1), Maximized) || getWindowMonitor(lastCreatedWindow) != current){
									goto uncascadedPosition;
								}
								if((reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, lastCreatedWindow), NULL))){
									attribute.a0 = (*(xcb_get_geometry_reply_t *)reply).x + cascadeOffsetX;
									attribute.a1 = (*(xcb_get_geometry_reply_t *)reply).y + cascadeOffsetY;
									attribute.a2 = (*(xcb_get_geometry_reply_t *)reply).width;
									attribute.a3 = (*(xcb_get_geometry_reply_t *)reply).height;
									free(reply);
									xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
								}
							}else{
								if(isCascadeMode(Smart) && lastCreatedWindow){
									int offsetX = cascadeOffsetX;
									int offsetY = cascadeOffsetY;
									bool hasSwitchedDirections = false;
									x = attribute.a0;
									y = attribute.a1;
									smartCascade:{
										genericPointer = containerStart;
										containerCurrent = containerStart;
										cascadeToDirection:{
											if((reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent).window), NULL))){
												if((*(xcb_get_geometry_reply_t *)reply).x == x && (*(xcb_get_geometry_reply_t *)reply).y == y){
													x += offsetX;
													y += offsetY;
													if(containerCurrent == (Container *)genericPointer){
														genericPointer = (Container *)genericPointer + 1;
													}
													containerCurrent = genericPointer;
												}else{
													++containerCurrent;
												}
												free(reply);
											}else{
												++containerCurrent;
											}
											if(containerCurrent < containerWall){
												goto cascadeToDirection;
											}
										}
										if(!hasSwitchedDirections && (x >= (*monitorCurrent).x + (int)(*monitorCurrent).width || y >= (*monitorCurrent).y + (int)(*monitorCurrent).height)){
											x = attribute.a0;
											offsetX = -offsetX;
											y = attribute.a1;
											offsetY = -offsetY;
											hasSwitchedDirections = true;
											goto smartCascade;
										}
									}
								}
								uncascadedPosition:{
									xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
								}
							}
						}
						attribute.a2 -= program.borderX;
						attribute.a3 -= program.borderY;
						xcb_configure_window(connection, subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
						attribute.a0 = XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_STRUCTURE_NOTIFY;
						break;
					}
					case GriddingManagementMode:{
						switch(defaultGridPosition){
							case TopLeftDefaultGridPosition:{
								(*containerCurrent).gridX = 0;
								(*containerCurrent).gridY = 0;
								break;
							}
							case TopRightDefaultGridPosition:{
								(*containerCurrent).gridX = gridWidth - 1;
								(*containerCurrent).gridY = 0;
								break;
							}
							case BottomLeftDefaultGridPosition:{
								(*containerCurrent).gridX = 0;
								(*containerCurrent).gridY = gridHeight - 1;
								break;
							}
							case BottomRightDefaultGridPosition:{
								(*containerCurrent).gridX = gridWidth - 1;
								(*containerCurrent).gridY = gridHeight - 1;
								break;
							}
							default:{
								(*containerCurrent).gridX = gridWidth / 2;
								(*containerCurrent).gridY = gridHeight / 2;
								break;
							}
						}
						getGridSlotData((*monitorCurrent).width, (*monitorCurrent).height, (*containerCurrent).gridX, (*containerCurrent).gridY, gridWidth, gridHeight, (int *)&attribute.a0, (int *)&attribute.a1, &attribute.a2, &attribute.a3);
						(*containerCurrent).gridWidth = 1;
						(*containerCurrent).gridHeight = 1;
						addContainerOption(*containerCurrent, InGrid);
						attribute.a0 += (*monitorCurrent).x;
						attribute.a1 += (*monitorCurrent).y;
						xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
						attribute.a2 -= program.borderX;
						attribute.a3 -= program.borderY;
						xcb_configure_window(connection, subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
						attribute.a0 = XCB_EVENT_MASK_STRUCTURE_NOTIFY;
						break;
					}
					default:{
						addTilingWindow();
						attribute.a0 = XCB_EVENT_MASK_STRUCTURE_NOTIFY;
						break;
					}
				}
				++containerAmount;
				++containerWall;
				{
					const Container c = *containerCurrent;
					++containerStart;
					pushNewContainerUp:{
						if(c.window < (*(containerCurrent - 1)).window && containerCurrent > containerStart){
							*containerCurrent = *(containerCurrent - 1);
							--containerCurrent;
							goto pushNewContainerUp;
						}
					}
					*containerCurrent = c;
					--containerStart;
				}
				xcb_change_window_attributes(connection, subwindow, XCB_CW_EVENT_MASK, &attribute);
				attribute.a0 = XCB_STACK_MODE_ABOVE;
				xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
				xcb_map_window(connection, genericWindow);
				if(isAnyMotionAction()){
					xcb_configure_window(connection, motionContainerWindow, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
					xcb_configure_window(connection, motionContainerGlass, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
					goto eventLoop;
				}
				goto changeFocusedWindowBackground0;
			}
		}
		configureRequestEvent:{
			consumeRedundantEvents(event, e, XCB_CONFIGURE_REQUEST);
			genericWindow = (*configureRequest).window;
			if(containerAmount && findWindow(genericWindow, &(*containerStart).subwindow, sizeof(Container), containerAmount, &current)){
				containerCurrent = containerStart + current;
				if(hasContainerOption(*containerCurrent, Maximized)){
					goto eventLoop;
				}
				if(!isManagementMode(Tiling) && !hasContainerOption(*containerCurrent, InGrid)){
					if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_X){
						attribute.a0 = (*configureRequest).x - borderLeft;
						attributeMasks = XCB_CONFIG_WINDOW_X;
						if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_Y){
							attribute.a1 = (*configureRequest).y - borderUp;
							attributeMasks |= XCB_CONFIG_WINDOW_Y;
						}
						goto configureWindow;
					}
					if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_Y){
						attribute.a0 = (*configureRequest).y - borderUp;
						attributeMasks = XCB_CONFIG_WINDOW_Y;
						configureWindow:{
							xcb_configure_window(connection, (*containerCurrent).window, attributeMasks, &attribute);
						}
					}
				}
				if(!((*configureRequest).value_mask & XCB_CONFIG_WINDOW_WIDTH_HEIGHT_BORDER)){
					goto eventLoop;
				}
				attributeMasks = XCB_NONE;
				genericPointer = &attribute;









				if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_WIDTH){
					*(WindowAttribute *)genericPointer = (*configureRequest).width;
					genericPointer = (WindowAttribute *)genericPointer + 1;
					attributeMasks |= XCB_CONFIG_WINDOW_WIDTH;
				}
				if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_HEIGHT){
					*(WindowAttribute *)genericPointer = (*configureRequest).height;
					genericPointer = (WindowAttribute *)genericPointer + 1;
					attributeMasks |= XCB_CONFIG_WINDOW_HEIGHT;
				}
				if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_BORDER_WIDTH){
					*(WindowAttribute *)genericPointer = (*configureRequest).border_width;
					if((WindowAttribute *)genericPointer > &attribute.a0){
						attribute.a0 -= *(WindowAttribute *)genericPointer;
						if((WindowAttribute *)genericPointer > &attribute.a1){
							attribute.a1 -= *(WindowAttribute *)genericPointer;
						}
					}
					attributeMasks |= XCB_CONFIG_WINDOW_BORDER_WIDTH;
				}
				xcb_configure_window(connection, genericWindow, attributeMasks, &attribute);
				if(attributeMasks & XCB_CONFIG_WINDOW_WIDTH_HEIGHT){
					if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent).window), NULL))){
						goto eventLoop;
					}
					attribute.a0 = (*(xcb_get_geometry_reply_t *)reply).width - (*(xcb_get_geometry_reply_t *)reply).border_width - program.borderX;
					attribute.a1 = (*(xcb_get_geometry_reply_t *)reply).height - (*(xcb_get_geometry_reply_t *)reply).border_width - program.borderY;
					free(reply);
					if((int)attribute.a0 < 1){
						attribute.a0 = 1;
					}
					if((int)attribute.a1 < 1){
						attribute.a1 = 1;
					}
					xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute);
				}









				goto eventLoop;
			}
			monitorCurrent = monitorStart + getPointerMonitor();
			if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT_BORDER){
				attributeMasks = XCB_NONE;
				genericPointer = &attribute;
				if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_X){
					*(WindowAttribute *)genericPointer = (*configureRequest).x;
					genericPointer = (WindowAttribute *)genericPointer + 1;
					attributeMasks |= XCB_CONFIG_WINDOW_X;
				}
				if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_Y){
					*(WindowAttribute *)genericPointer = (*configureRequest).y;
					genericPointer = (WindowAttribute *)genericPointer + 1;
					attributeMasks |= XCB_CONFIG_WINDOW_Y;
				}
				if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_WIDTH){
					*(WindowAttribute *)genericPointer = (*configureRequest).width;
					genericPointer = (WindowAttribute *)genericPointer + 1;
					attributeMasks |= XCB_CONFIG_WINDOW_WIDTH;
				}
				if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_HEIGHT){
					*(WindowAttribute *)genericPointer = (*configureRequest).height;
					genericPointer = (WindowAttribute *)genericPointer + 1;
					attributeMasks |= XCB_CONFIG_WINDOW_HEIGHT;
				}
				if((*configureRequest).value_mask & XCB_CONFIG_WINDOW_BORDER_WIDTH){
					*(WindowAttribute *)genericPointer = (*configureRequest).border_width;
					genericPointer = &attribute;
					if(attributeMasks & XCB_CONFIG_WINDOW_X){
						genericPointer = (WindowAttribute *)genericPointer + 1;
					}
					if(attributeMasks & XCB_CONFIG_WINDOW_Y){
						genericPointer = (WindowAttribute *)genericPointer + 1;
					}
					if(attributeMasks & XCB_CONFIG_WINDOW_WIDTH){
						*(WindowAttribute *)genericPointer -= (*configureRequest).border_width;
						genericPointer = (WindowAttribute *)genericPointer + 1;
					}
					if(attributeMasks & XCB_CONFIG_WINDOW_HEIGHT){
						*(WindowAttribute *)genericPointer -= (*configureRequest).border_width;
					}
					attributeMasks |= XCB_CONFIG_WINDOW_BORDER_WIDTH;
				}
				if(attributeMasks){
					xcb_configure_window(connection, genericWindow, attributeMasks, &attribute);
				}
			}
			attribute.a0 = (*monitorCurrent).x;
			attribute.a1 = (*monitorCurrent).y;
			attribute.a2 = (*monitorCurrent).width / gridWidth - program.borderX;
			attribute.a3 = (*monitorCurrent).height / gridHeight - program.borderY;
			xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
			goto eventLoop;
		}
		clientMessageEvent:{
			if((*(xcb_client_message_event_t *)event).type == program._NET_WM_STATE){
				if(containerAmount && findWindow((*(xcb_client_message_event_t *)event).window, &(*containerStart).subwindow, sizeof(Container), containerAmount, &current)){
					xcb_atom_t data0;
					xcb_atom_t data1;
					genericPointer = &(*(xcb_client_message_event_t *)event).data;
					switch((*(xcb_client_message_event_t *)event).format){
						case 32:{
							data0 = *(uint32_t *)genericPointer;
							data1 = *((uint32_t *)genericPointer + 1);
							break;
						}
						case 16:{
							data0 = *(uint16_t *)genericPointer;
							data1 = *((uint16_t *)genericPointer + 1);
							break;
						}
						default:{
							data0 = *(uint8_t *)genericPointer;
							data1 = *((uint8_t *)genericPointer + 1);
							break;
						}
					}
					/*switch((*(xcb_client_message_event_t *)event).format){
						case 8:{
							genericPointer = &(*(xcb_client_message_event_t *)event).data;
							data0 = *(*(xcb_client_message_event_t *)event).data.data8;
							data1 = *((*(xcb_client_message_event_t *)event).data.data8 + 1);
							break;
						}
						case 16:{
							data0 = *(*(xcb_client_message_event_t *)event).data.data16;
							data1 = *((*(xcb_client_message_event_t *)event).data.data16 + 1);
							break;
						}
						default:{
							data0 = *(*(xcb_client_message_event_t *)event).data.data32;
							data1 = *((*(xcb_client_message_event_t *)event).data.data32 + 1);
							break;
						}
					}*/
					containerCurrent = containerStart + current;
					switch(data0){
						case _NET_WM_STATE_REMOVE:{
							if(data1 == program._NET_WM_STATE_FULLSCREEN){
								goto unmaximizeClient;
							}
							goto eventLoop;
						}
						case _NET_WM_STATE_ADD:{
							if(data1 == program._NET_WM_STATE_FULLSCREEN){
								goto maximizeClient;
							}
							goto eventLoop;
						}
						default:{
							if(data1 == program._NET_WM_STATE_FULLSCREEN){
								if(hasContainerOption(*containerCurrent, Maximized)){
									unmaximizeClient:{
										unmaximizeContainer(focused, containerCurrent, maximizedContainerStart);
									}
									goto eventLoop;
								}
								maximizeClient:{
									if(hasPointerInfo(ClientMessage)){
										current = getPointerMonitor();
									}else{
										current = getWindowMonitor((*containerCurrent).window);
									}
									if(hasContainerOption(*containerCurrent, Maximized)){
										unmaximizeContainer(focused, containerCurrent, maximizedContainerStart);
									}
									maximizeContainer(FullscreenCommand, monitorStart + current, focused, containerCurrent, maximizedContainerStart + current);
								}
							}
							goto eventLoop;
						}
					}
				}
			}
			goto eventLoop;
		}
		screenChangeNotifyEvent:{
			consumeRedundantEvents(event, e, XCB_RANDR_SCREEN_CHANGE_NOTIFY);
			/**/









			goto eventLoop;
		}
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
				case CancelMoveResizeCommand:{
					goto cancelMoveResizeCommand;
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
				case CascadeCommand:{
					goto cascadeCommand;
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
				case RevolveMonitorsAboveCommand:
				case RevolveMonitorsBelowCommand:
				case RevolveMonitorsLeftCommand:
				case RevolveMonitorsRightCommand:{
					goto revolveMonitorsCommand;
				}
				case RestartCommand:{
					goto eventLoopExit;
				}
				case ExitCommand:{
					setMode(Exit);
					goto eventLoopExit;
				}
				case MoveCommand:
				case ResizeCommand:
				case MoveResizeCommand:{
					goto moveResizeCommand;
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
					goto moveCenterFullCommand;
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
				case KillCommand:{
					goto killCommand;
				}
				default:{
					printError("unrecognized command, probably an unauthorized software-level change");
					goto eventLoop;
				}
			}
		}
		executeCommand:{
			if(!executeAmount){
				goto eventLoop;
			}
			executeCurrent = executeStart;
			findExecuteCommand:{
				if(isExecute(executeCurrent, event)){
					if(system((*executeCurrent).command) == SYSTEM_FAIL){
						printError("could not execute user-specified program");
					}
					goto eventLoop;
				}
				if(++executeCurrent < executeWall){
					goto findExecuteCommand;
				}
			}
			goto eventLoop;
		}
		floatingModeCommand:{
			if(isManagementMode(Floating)){
				goto eventLoop;
			}
			if(containerAmount){
				attribute.a0 = XCB_STACK_MODE_ABOVE;
				xcb_configure_window(connection, glass, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
				xcb_map_window(connection, glass);
				xcb_flush(connection);
				{
					const bool portWindowsFromGridding = isManagementMode(Gridding) && hasOption(FloatingPortWindowsFromGridding);
					const WindowAttribute windowMasks = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
					containerCurrent = containerStart;
					attribute.a0 = shadow;
					attribute.a1 = program.colorContainerBackgroundFloating;
					attribute.a2 = XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT;
					attribute.a3 = XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_STRUCTURE_NOTIFY;
					editContainerFloating:{
						genericWindow = (*containerCurrent).window;
						if(portWindowsFromGridding){
							xcb_change_window_attributes(connection, genericWindow, XCB_CW_BACK_PIXEL, &program.colorContainerBackgroundInGrid);
						}else{
							xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_BORDER_WIDTH, &attribute);
							xcb_change_window_attributes(connection, genericWindow, windowMasks, &attribute.a1);
							xcb_change_window_attributes(connection, (*containerCurrent).subwindow, XCB_CW_EVENT_MASK, &attribute.a3);
							if(hasContainerOption(*containerCurrent, InGrid)){
								removeContainerOption(*containerCurrent, InGrid);
							}
						}
						if(++containerCurrent < containerWall){
							goto editContainerFloating;
						}
					}
				}
				{
					const Options followGrid = hasOption(FloatingFollowGrid);
					int offsetX = 0;
					int offsetY = 0;
					if(hasOption(FloatingAllowCascadeToFloating)){
						offsetX = cascadeOffsetX;
						offsetY = cascadeOffsetY;
					}
					if(hasPointerInfo(ChangeToFloating)){
						unsigned int monitorBorderX;
						unsigned int totalWidth;
						unsigned int monitorBorderY;
						unsigned int totalHeight;
						monitorCurrent = monitorStart + getPointerMonitor();
						if(hasOption(FloatingFollowGrid)){
							attribute.a2 = (*monitorCurrent).width / gridWidth;
							attribute.a3 = (*monitorCurrent).height / gridHeight;
						}else{
							attribute.a2 = (*monitorCurrent).width / floatingWindowDivisor;
							attribute.a3 = (*monitorCurrent).height / floatingWindowDivisor;
						}
						containerCurrent = containerStart;
						if(cascadeOffsetX < 0){
							monitorBorderX = (*monitorCurrent).x;
							totalWidth = 2 * shadow + attribute.a2;
						}else if(cascadeOffsetX > 0){
							monitorBorderX = (*monitorCurrent).x + (*monitorCurrent).width;
						}
						if(cascadeOffsetY < 0){
							monitorBorderY = (*monitorCurrent).y;
							totalHeight = 2 * shadow + attribute.a3;
						}else if(cascadeOffsetY > 0){
							monitorBorderY = (*monitorCurrent).y + (*monitorCurrent).height;
						}
						attribute.a0 = (*monitorCurrent).x + ((*monitorCurrent).width - attribute.a2) / 2 - shadow;
						attribute.a1 = (*monitorCurrent).y + ((*monitorCurrent).height - attribute.a3) / 2 - shadow;
						attribute.a4 = attribute.a2 - program.borderX;
						attribute.a5 = attribute.a3 - program.borderY;
						portToFloating0:{
							if(!hasContainerOption(*containerCurrent, InGrid)){
								xcb_configure_window(connection, (*containerCurrent).window, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
								xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a4);
								attribute.a0 += offsetX;
								attribute.a1 += offsetY;
								if((cascadeOffsetX > 0 && attribute.a0 >= monitorBorderX) || (cascadeOffsetX < 0 && attribute.a0 + totalWidth < monitorBorderX) || (cascadeOffsetY > 0 && attribute.a1 >= monitorBorderY) || (cascadeOffsetY < 0 && attribute.a1 + totalHeight < monitorBorderY)){
									attribute.a0 = ((*monitorCurrent).x + ((*monitorCurrent).width - attribute.a2) / 2 - shadow) - offsetX;
									attribute.a1 = ((*monitorCurrent).y + ((*monitorCurrent).height - attribute.a3) / 2 - shadow) - offsetY;
									offsetX = -offsetX;
									offsetY = -offsetY;
								}
							}
							if(++monitorCurrent < monitorWall){
								goto portToFloating0;
							}
						}
						goto floatingModeCommandExit;
					}
					genericUnsignedInteger = 6 * sizeof(WindowAttribute) + 4 * sizeof(unsigned int);
					if((genericPointer = malloc(monitorAmount * genericUnsignedInteger))){
						unsigned int *const monitorBorderX = (unsigned int *)((WindowAttribute *)genericPointer + 6);
						unsigned int *const totalWidth = monitorBorderX + 1;
						unsigned int *const monitorBorderY = totalWidth + 1;
						unsigned int *const totalHeight = monitorBorderY + 1;
						current = 0;
						monitorCurrent = monitorStart;
						cascadeToFloatingPerMonitor0:{
							if(hasOption(FloatingFollowGrid)){
								*((WindowAttribute *)genericPointer + 2) = (*monitorCurrent).width / gridWidth;
								*((WindowAttribute *)genericPointer + 3) = (*monitorCurrent).height / gridHeight;
							}else{
								*((WindowAttribute *)genericPointer + 2) = (*monitorCurrent).width / floatingWindowDivisor;
								*((WindowAttribute *)genericPointer + 3) = (*monitorCurrent).height / floatingWindowDivisor;
							}
							if(cascadeOffsetX < 0){
								*(monitorBorderX + current) = (*monitorCurrent).x;
								*(totalWidth + current) = 2 * shadow + *((WindowAttribute *)genericPointer + 2);
							}else if(cascadeOffsetX > 0){
								*(monitorBorderX + current) = (*monitorCurrent).x + (*monitorCurrent).width;
							}
							if(cascadeOffsetY < 0){
								*(monitorBorderY + current) = (*monitorCurrent).y;
								*(totalHeight + current) = 2 * shadow + *((WindowAttribute *)genericPointer + 3);
							}else if(cascadeOffsetY > 0){
								*(monitorBorderY + current) = (*monitorCurrent).y + (*monitorCurrent).height;
							}
							*(WindowAttribute *)genericPointer = (*monitorCurrent).x + ((*monitorCurrent).width - *((WindowAttribute *)genericPointer + 2)) / 2 - shadow;
							*((WindowAttribute *)genericPointer + 1) = (*monitorCurrent).y + ((*monitorCurrent).height - *((WindowAttribute *)genericPointer + 3)) / 2 - shadow;
							*((WindowAttribute *)genericPointer + 4) = *((WindowAttribute *)genericPointer + 2) - program.borderX;
							*((WindowAttribute *)genericPointer + 5) = *((WindowAttribute *)genericPointer + 3) - program.borderY;
							if(++current < monitorAmount){
								genericPointer = (uint8_t *)genericPointer + genericUnsignedInteger;
								++monitorCurrent;
								goto cascadeToFloatingPerMonitor0;
							}
							genericPointer = (uint8_t *)genericPointer - (monitorAmount - 1) * genericUnsignedInteger;
						}
						containerCurrent = containerStart;
						portToFloating1:{
							if(!hasContainerOption(*containerCurrent, InGrid)){
								current = getWindowMonitor((*containerCurrent).window);
								genericPointer = (uint8_t *)genericPointer + current * genericUnsignedInteger;
								xcb_configure_window(connection, (*containerCurrent).window, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, genericPointer);
								xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, (WindowAttribute *)genericPointer + 4);
								*(WindowAttribute *)genericPointer += offsetX;
								*((WindowAttribute *)genericPointer + 1) += offsetY;
								if((cascadeOffsetX > 0 && *(WindowAttribute *)genericPointer >= *(monitorBorderX + current)) || (cascadeOffsetX < 0 && *(WindowAttribute *)genericPointer + *(totalWidth + current) < *(monitorBorderX + current)) || (cascadeOffsetY > 0 && *((WindowAttribute *)genericPointer + 1) >= *(monitorBorderY + current)) || (cascadeOffsetY < 0 && *((WindowAttribute *)genericPointer + 1) + *(totalHeight + current) < *(monitorBorderY + current))){
									monitorCurrent = monitorStart + current;
									*(WindowAttribute *)genericPointer = ((*monitorCurrent).x + ((*monitorCurrent).width - *((WindowAttribute *)genericPointer + 2)) / 2 - shadow) - offsetX;
									*((WindowAttribute *)genericPointer + 1) = ((*monitorCurrent).y + ((*monitorCurrent).height - *((WindowAttribute *)genericPointer + 3)) / 2 - shadow) - offsetY;
									offsetX = -offsetX;
									offsetY = -offsetY;
								}
								genericPointer = (uint8_t *)genericPointer - current * genericUnsignedInteger;
							}
							if(++containerCurrent < containerWall){
								goto portToFloating1;
							}
						}
						free(genericPointer);
						goto floatingModeCommandExit;
					}
					{
						unsigned int monitorBorderX;
						unsigned int totalWidth;
						unsigned int monitorBorderY;
						unsigned int totalHeight;
						monitorCurrent = monitorStart;
						current = 0;
						cascadeToFloatingPerMonitor1:{
							if(followGrid){
								attribute.a2 = (*monitorCurrent).width / gridWidth;
								attribute.a3 = (*monitorCurrent).height / gridHeight;
							}else{
								attribute.a2 = (*monitorCurrent).width / floatingWindowDivisor;
								attribute.a3 = (*monitorCurrent).height / floatingWindowDivisor;
							}
							containerCurrent = containerStart;
							if(cascadeOffsetX < 0){
								monitorBorderX = (*monitorCurrent).x;
								totalWidth = 2 * shadow + attribute.a2;
							}else if(cascadeOffsetX > 0){
								monitorBorderX = (*monitorCurrent).x + (*monitorCurrent).width;
							}
							if(cascadeOffsetY < 0){
								monitorBorderY = (*monitorCurrent).y;
								totalHeight = 2 * shadow + attribute.a3;
							}else if(cascadeOffsetY > 0){
								monitorBorderY = (*monitorCurrent).y + (*monitorCurrent).height;
							}
							attribute.a0 = (*monitorCurrent).x + ((*monitorCurrent).width - attribute.a2) / 2;
							attribute.a1 = (*monitorCurrent).y + ((*monitorCurrent).height - attribute.a3) / 2;
							attribute.a4 = attribute.a2 - program.borderX;
							attribute.a5 = attribute.a3 - program.borderY;
							portToFloating2:{
								if(!hasContainerOption(*containerCurrent, InGrid) && getWindowMonitor((*containerCurrent).window) == current){
									xcb_configure_window(connection, (*containerCurrent).window, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
									xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a4);
									attribute.a0 += offsetX;
									attribute.a1 += offsetY;
									if((cascadeOffsetX > 0 && attribute.a0 >= monitorBorderX) || (cascadeOffsetX < 0 && attribute.a0 + totalWidth < monitorBorderX) || (cascadeOffsetY > 0 && attribute.a1 >= monitorBorderY) || (cascadeOffsetY < 0 && attribute.a1 + totalHeight < monitorBorderY)){
										attribute.a0 = ((*monitorCurrent).x + ((*monitorCurrent).width - attribute.a2) / 2) - offsetX;
										attribute.a1 = ((*monitorCurrent).y + ((*monitorCurrent).height - attribute.a3) / 2) - offsetY;
										offsetX = -offsetX;
										offsetY = -offsetY;
									}
								}
								if(++containerCurrent < containerWall){
									goto portToFloating2;
								}
							}
							if(++monitorCurrent < monitorWall){
								++current;
								goto cascadeToFloatingPerMonitor1;
							}
						}
					}
				}
				floatingModeCommandExit:{
					if(focused){
						if(hasContainerOption(*focused, InGrid)){
							if(hasOption(InGridUseFocusedWindowColor)){
								genericPointer = &program.colorFocusedContainerBackgroundInGrid;
								goto changeFocusedBackgroundFloating;
							}
						}else{
							if(hasOption(FloatingUseFocusedWindowColor)){
								genericPointer = &program.colorFocusedContainerBackgroundFloating;
								changeFocusedBackgroundFloating:{
									xcb_change_window_attributes(connection, (*focused).window, XCB_CW_BACK_PIXEL, &genericPointer);
								}
							}
						}
					}
					xcb_unmap_window(connection, glass);
				}
			}
			program.managementMode = FloatingManagementMode;
			goto eventLoop;
		}
		griddingModeCommand:{
			if(isManagementMode(Gridding)){
				goto eventLoop;
			}
			if(containerAmount){
				const PointerInfo windowPointerInfo = hasPointerInfo(ChangeToGridding);
				unsigned int *gridX;
				unsigned int *gridY;
				if(windowPointerInfo){
					current = getPointerMonitor();
					monitorCurrent = monitorStart + current;
					genericUnsignedInteger = 1;
				}else{
					genericUnsignedInteger = monitorAmount;
				}
				if((gridX = malloc(2 * genericUnsignedInteger * sizeof(unsigned int)))){
#undef BASED









					gridY = gridX + genericUnsignedInteger;
					attribute.a0 = XCB_STACK_MODE_ABOVE;
					xcb_configure_window(connection, glass, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
					xcb_map_window(connection, glass);
					xcb_flush(connection);
					{
						const Options portWindowsFromFloating = hasOption(GriddingPortWindowsFromFloating);
						const WindowAttribute windowEventMasks = XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT;
						const Options evenlyDistributeWindows = hasOption(GriddingEvenlyDistributeWindows);
						AttributeMasks configureWindowMasks;
						AttributeMasks configureSubwindowMasks;
						AttributeMasks changeWindowMasks;
						AttributeMasks changeSubwindowMasks;
						unsigned int gX = 0;
						unsigned int gY = 0;
						if(!evenlyDistributeWindows){
							switch(defaultGridPosition){
								case TopLeftDefaultGridPosition:{
									break;
								}
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
						genericPointer = gridY;
						setGriddingModeGridPositions:{
							*gridX = gX;
							*gridY = gY;
							if(++gridX < (unsigned int *)genericPointer){
								++gridY;
								goto setGriddingModeGridPositions;
							}
							gridX -= genericUnsignedInteger;
							gridY = genericPointer;
						}
						containerCurrent = containerStart;
						portToGridding:{
							configureWindowMasks = XCB_NONE;
							configureSubwindowMasks = XCB_NONE;
							changeWindowMasks = XCB_CW_BACK_PIXEL;
							changeSubwindowMasks = XCB_NONE;
							genericWindow = (*containerCurrent).window;
							attribute.a0 = program.colorContainerBackgroundGridding;
							if(hasContainerOption(*containerCurrent, InGrid)){
								if(!portWindowsFromFloating){
									goto editGriddingWindow;
								}
							}else{
								configureWindowMasks |= XCB_CONFIG_WINDOW_BORDER_WIDTH;
								changeWindowMasks |= XCB_CW_EVENT_MASK;
								changeSubwindowMasks |= XCB_CW_EVENT_MASK;
								attribute.a7 = 0;
								attribute.a1 = windowEventMasks;
								attribute.a2 = XCB_EVENT_MASK_STRUCTURE_NOTIFY;
								addContainerOption(*containerCurrent, InGrid);
								editGriddingWindow:{
									if(!windowPointerInfo){
										current = getWindowMonitor(genericWindow);
										monitorCurrent = monitorStart + current;
										gX = *(gridX + current);
										gY = *(gridY + current);
									}
									getGridSlotData((*monitorCurrent).width, (*monitorCurrent).height, gX, gY, gridWidth, gridHeight, (int *)&attribute.a3, (int *)&attribute.a4, &attribute.a5, &attribute.a6);
									configureWindowMasks |= XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT;
									configureSubwindowMasks |= XCB_CONFIG_WINDOW_WIDTH_HEIGHT;
									attribute.a3 += (*monitorCurrent).x;
									attribute.a4 += (*monitorCurrent).y;
									(*containerCurrent).gridX = gX;
									(*containerCurrent).gridY = gY;
									(*containerCurrent).gridWidth = 1;
									(*containerCurrent).gridHeight = 1;
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
							if(configureWindowMasks){
								xcb_configure_window(connection, genericWindow, configureWindowMasks, &attribute.a3);
							}
							if(configureSubwindowMasks){
								attribute.a5 -= program.borderX;
								attribute.a6 -= program.borderY;
								xcb_configure_window(connection, (*containerCurrent).subwindow, configureSubwindowMasks, &attribute.a5);
							}
							xcb_change_window_attributes(connection, genericWindow, changeWindowMasks, &attribute);
							if(changeSubwindowMasks){
								xcb_change_window_attributes(connection, (*containerCurrent).subwindow, changeSubwindowMasks, &attribute.a2);
							}
							xcb_clear_area(connection, false, genericWindow, 0, 0, 0, 0);
							if(++containerCurrent < containerWall){
								goto portToGridding;
							}
						}
					}
					free(gridX);
					if(hasOption(GriddingUseFocusedWindowColor) && focused){
						xcb_change_window_attributes(connection, (*focused).window, XCB_CW_BACK_PIXEL, &program.colorFocusedContainerBackgroundGridding);
						xcb_clear_area(connection, false, (*focused).window, 0, 0, 0, 0);
					}
					xcb_unmap_window(connection, glass);
					setManagementMode(Gridding);
					goto eventLoop;
				}
				{
					/**/



				}









#define BASED
			}
			setManagementMode(Gridding);
			goto eventLoop;
		}
		tilingModeCommand:{
			if(isManagementMode(Tiling)){
				goto eventLoop;
			}
			if(containerAmount){
				/**/



			}
			setManagementMode(Tiling);
			goto eventLoop;
		}
		cancelMoveResizeCommand:{
			if(!isAnyMotionAction()){
				goto eventLoop;
			}
			switch(program.managementMode){
				case FloatingManagementMode:{
					if(hasContainerOption(*containerCurrent, InGrid)){
						if(isMotionAction(Move)){
							if(!hasOption(InGridMinimalMove)){
								goto eventLoop;
							}
							goto cancelMoveResize;
						}
						if(!hasOption(InGridMinimalResize)){
							goto eventLoop;
						}
						goto cancelMoveResize;
					}
					if(isMotionAction(Move)){
						if(!hasOption(FloatingMinimalMove)){
							goto eventLoop;
						}
						goto cancelMoveResize;
					}
					if(!hasOption(FloatingMinimalResize)){
						goto eventLoop;
					}
					goto cancelMoveResize;
				}
				case GriddingManagementMode:{
					if(isMotionAction(Move)){
						if(!hasOption(GriddingMinimalMove)){
							goto eventLoop;
						}
						goto cancelMoveResize;
					}
					if(!hasOption(GriddingMinimalResize)){
						goto eventLoop;
					}
					goto cancelMoveResize;
				}
				default:{
					if(isMotionAction(Move)){
						if(!hasOption(TilingMinimalMove)){
							goto eventLoop;
						}
						goto cancelMoveResize;
					}
					if(!hasOption(TilingMinimalResize)){
						goto eventLoop;
					}
					cancelMoveResize:{
						if(isAnyMotionSubaction() && hasMotionOption(SnappingMapped)){
							xcb_unmap_window(connection, motionContainerSnappingWindow);
						}
						if(isMotionAction(Move)){
							genericUnsignedInteger = shadow;
							shadow = motionContainerMinimalMoveBorder;
							motionContainerMinimalMoveBorder = genericUnsignedInteger;
						}
						xcb_unmap_window(connection, motionContainerWindow);
						xcb_unmap_window(connection, motionContainerGlass);
						genericWindow = motionContainerWindow;
						motionContainerWindow = motionContainerMinimalWindow;
						motionContainerMinimalWindow = genericWindow;
						setMotionAction(None);
					}
					goto eventLoop;
				}
			}
		}
		showHideToggleGridCommand:{
			switch(command){
				case ShowGridCommand:{
					if(isGridMapped){
						goto eventLoop;
					}
					goto showGrid;
				}
				case HideGridCommand:{
					if(!isGridMapped){
						goto eventLoop;
					}
					goto hideGrid;
				}
				default:{
					if(!isGridMapped){
						showGrid:{
							gridCurrent = gridStart;
							attribute.a0 = XCB_STACK_MODE_BELOW;
							lowerMapGridWindow:{
								xcb_configure_window(connection, *gridCurrent, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
								xcb_map_window(connection, *gridCurrent);
								if(++gridCurrent < gridWall){
									goto lowerMapGridWindow;
								}
							}
							xcb_flush(connection);
							drawGrid();
							isGridMapped = true;
						}
						goto eventLoop;
					}
					hideGrid:{
						gridCurrent = gridStart;
						unmapGridWindow:{
							xcb_unmap_window(connection, *gridCurrent);
							if(++gridCurrent < gridWall){
								goto unmapGridWindow;
							}
						}
						isGridMapped = false;
					}
					goto eventLoop;
				}
			}
		}
		enlargeGridXCommand:{
			if(gridWidth >= gridMaxWidth){
				goto eventLoop;
			}
			++gridWidth;
			goto adjustGrid;
		}
		enlargeGridYCommand:{
			if(gridHeight >= gridMaxHeight){
				goto eventLoop;
			}
			++gridHeight;
			goto adjustGrid;
		}
		enlargeGridEitherCommand:{
			if(gridWidth < gridMaxWidth){
				++gridWidth;
				if(gridHeight < gridMaxHeight){
					++gridHeight;
				}
				goto adjustGrid;
			}
			if(gridHeight >= gridMaxHeight){
				goto eventLoop;
			}
			++gridHeight;
			goto adjustGrid;
		}
		enlargeGridBothCommand:{
			if(gridWidth >= gridMaxWidth || gridHeight >= gridMaxHeight){
				goto eventLoop;
			}
			++gridWidth;
			++gridHeight;
			goto adjustGrid;
		}
		shrinkGridXCommand:{
			if(gridWidth <= gridMinWidth){
				goto eventLoop;
			}
			--gridWidth;
			goto adjustGrid;
		}
		shrinkGridYCommand:{
			if(gridHeight <= gridMinHeight){
				goto eventLoop;
			}
			--gridHeight;
			goto adjustGrid;
		}
		shrinkGridEitherCommand:{
			if(gridWidth > gridMinWidth){
				--gridWidth;
				if(gridHeight > gridMinHeight){
					--gridHeight;
				}
				goto adjustGrid;
			}
			if(gridHeight <= gridMinHeight){
				goto eventLoop;
			}
			--gridHeight;
			goto adjustGrid;
		}
		shrinkGridBothCommand:{
			if(gridWidth <= gridMinWidth || gridHeight <= gridMinHeight){
				goto eventLoop;
			}
			--gridWidth;
			--gridHeight;
			adjustGrid:{
				if(isGridMapped){
					drawGrid();
				}
				if(!isManagementMode(Tiling) && containerAmount){
					containerCurrent = containerStart;
					moveResizeGridWindow:{
						if(hasContainerOption(*containerCurrent, InGrid)){
							current = getWindowMonitor((*containerCurrent).window);
							monitorCurrent = monitorStart + current;
							if((*containerCurrent).gridX + (*containerCurrent).gridWidth - 1 == gridWidth){
								if(!--(*containerCurrent).gridWidth){
									--(*containerCurrent).gridX;
									++(*containerCurrent).gridWidth;
								}
							}
							if((*containerCurrent).gridY + (*containerCurrent).gridHeight - 1 == gridHeight){
								if(!--(*containerCurrent).gridHeight){
									--(*containerCurrent).gridY;
									++(*containerCurrent).gridHeight;
								}
							}
							getGridSlotData((*monitorCurrent).width, (*monitorCurrent).height, (*containerCurrent).gridX + (*containerCurrent).gridWidth - 1, (*containerCurrent).gridY + (*containerCurrent).gridHeight - 1, gridWidth, gridHeight, &x, &y, &attribute.a2, &attribute.a3);
							attribute.a2 += x;
							attribute.a3 += y;
							getGridSlotData((*monitorCurrent).width, (*monitorCurrent).height, (*containerCurrent).gridX, (*containerCurrent).gridY, gridWidth, gridHeight, (int *)&attribute.a0, (int *)&attribute.a1, NULL, NULL);
							attribute.a2 -= attribute.a0;
							attribute.a3 -= attribute.a1;
							attribute.a0 += (*monitorCurrent).x;
							attribute.a1 += (*monitorCurrent).y;
							if(hasContainerOption(*containerCurrent, Maximized)){
								maximizedContainerCurrent = maximizedContainerStart + current;
								(*maximizedContainerCurrent).oldX = attribute.a0;
								(*maximizedContainerCurrent).oldY = attribute.a1;
								(*maximizedContainerCurrent).oldWidth = attribute.a2;
								(*maximizedContainerCurrent).oldHeight = attribute.a3;
							}else{
								xcb_configure_window(connection, (*containerCurrent).window, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
								attribute.a2 -= program.borderX;
								attribute.a3 -= program.borderY;
								xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
							}
						}
						if(++containerCurrent < containerWall){
							goto moveResizeGridWindow;
						}
					}
				}
			}
			goto eventLoop;
		}
		toggleGapsCommand:{
			/**/



			goto eventLoop;
		}
		cascadeCommand:{
			if(!isManagementMode(Floating) || !containerAmount){
				goto eventLoop;
			}
			{
				const CascadeOptions overrideGridWindows = hasCascadeOption(OverrideGridWindows);
				const CascadeOptions overrideMaximizedWindows = hasCascadeOption(OverrideMaximizedWindows);
				AttributeMasks windowMasks;
				int offsetX = 0;
				int offsetY = 0;
				if(hasOption(FloatingAllowCascadeToFloating)){
					offsetX = cascadeOffsetX;
					offsetY = cascadeOffsetY;
				}
				if(hasPointerInfo(Cascade)){
					unsigned int monitorBorderX;
					unsigned int totalWidth;
					unsigned int monitorBorderY;
					unsigned int totalHeight;
					monitorCurrent = monitorStart + getPointerMonitor();
					if(hasOption(FloatingFollowGrid)){
						attribute.a2 = (*monitorCurrent).width / gridWidth;
						attribute.a3 = (*monitorCurrent).height / gridHeight;
					}else{
						attribute.a2 = (*monitorCurrent).width / floatingWindowDivisor;
						attribute.a3 = (*monitorCurrent).height / floatingWindowDivisor;
					}
					containerCurrent = containerStart;
					if(cascadeOffsetX < 0){
						monitorBorderX = (*monitorCurrent).x;
						totalWidth = 2 * shadow + attribute.a2;
					}else if(cascadeOffsetX > 0){
						monitorBorderX = (*monitorCurrent).x + (*monitorCurrent).width;
					}
					if(cascadeOffsetY < 0){
						monitorBorderY = (*monitorCurrent).y;
						totalHeight = 2 * shadow + attribute.a3;
					}else if(cascadeOffsetY > 0){
						monitorBorderY = (*monitorCurrent).y + (*monitorCurrent).height;
					}
					attribute.a0 = (*monitorCurrent).x + ((*monitorCurrent).width - attribute.a2) / 2 - shadow;
					attribute.a1 = (*monitorCurrent).y + ((*monitorCurrent).height - attribute.a3) / 2 - shadow;
					attribute.a4 = shadow;
					attribute.a5 = attribute.a2 - program.borderX;
					attribute.a6 = attribute.a3 - program.borderY;
					cascade0:{
						if((!hasContainerOption(*containerCurrent, Maximized) || overrideMaximizedWindows) && (!hasContainerOption(*containerCurrent, InGrid) || overrideGridWindows)){
							genericWindow = (*containerCurrent).window;
							windowMasks = XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT;
							if(hasContainerOption(*containerCurrent, Maximized)){
								unmaximizeContainer(focused, containerCurrent, maximizedContainerStart);
							}
							if(hasContainerOption(*containerCurrent, InGrid)){
								windowMasks |= XCB_CONFIG_WINDOW_BORDER_WIDTH;
								xcb_change_window_attributes(connection, genericWindow, XCB_CW_BACK_PIXEL, &program.colorContainerBackgroundFloating);
								xcb_clear_area(connection, false, genericWindow, 0, 0, 0, 0);
								removeContainerOption(*containerCurrent, InGrid);
							}
							xcb_configure_window(connection, genericWindow, windowMasks, &attribute);
							xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a5);
							attribute.a0 += offsetX;
							attribute.a1 += offsetY;
							if((cascadeOffsetX > 0 && attribute.a0 >= monitorBorderX) || (cascadeOffsetX < 0 && attribute.a0 + totalWidth < monitorBorderX) || (cascadeOffsetY > 0 && attribute.a1 >= monitorBorderY) || (cascadeOffsetY < 0 && attribute.a1 + totalHeight < monitorBorderY)){
								attribute.a0 = x - offsetX;
								attribute.a1 = y - offsetY;
								offsetX = -offsetX;
								offsetY = -offsetY;
							}
						}
						if(++containerCurrent < containerWall){
							goto cascade0;
						}
					}
					goto eventLoop;
				}
				genericUnsignedInteger = 7 * sizeof(WindowAttribute) + 4 * sizeof(unsigned int);
				if((genericPointer = malloc(monitorAmount * genericUnsignedInteger))){
					unsigned int *const monitorBorderX = (unsigned int *)((WindowAttribute *)genericPointer + 7);
					unsigned int *const totalWidth = monitorBorderX + 1;
					unsigned int *const monitorBorderY = totalWidth + 1;
					unsigned int *const totalHeight = monitorBorderY + 1;
					current = 0;
					monitorCurrent = monitorStart;
					cascadePerMonitor0:{
						if(hasOption(FloatingFollowGrid)){
							*((WindowAttribute *)genericPointer + 2) = (*monitorCurrent).width / gridWidth;
							*((WindowAttribute *)genericPointer + 3) = (*monitorCurrent).height / gridHeight;
						}else{
							*((WindowAttribute *)genericPointer + 2) = (*monitorCurrent).width / floatingWindowDivisor;
							*((WindowAttribute *)genericPointer + 3) = (*monitorCurrent).height / floatingWindowDivisor;
						}
						if(cascadeOffsetX < 0){
							*(monitorBorderX + current) = (*monitorCurrent).x;
							*(totalWidth + current) = 2 * shadow + *((WindowAttribute *)genericPointer + 2);
						}else if(cascadeOffsetX > 0){
							*(monitorBorderX + current) = (*monitorCurrent).x + (*monitorCurrent).width;
						}
						if(cascadeOffsetY < 0){
							*(monitorBorderY + current) = (*monitorCurrent).y;
							*(totalHeight + current) = 2 * shadow + *((WindowAttribute *)genericPointer + 3);
						}else if(cascadeOffsetY > 0){
							*(monitorBorderY + current) = (*monitorCurrent).y + (*monitorCurrent).height;
						}
						*(WindowAttribute *)genericPointer = (*monitorCurrent).x + ((*monitorCurrent).width - *((WindowAttribute *)genericPointer + 2)) / 2 - shadow;
						*((WindowAttribute *)genericPointer + 1) = (*monitorCurrent).y + ((*monitorCurrent).height - *((WindowAttribute *)genericPointer + 3)) / 2 - shadow;
						*((WindowAttribute *)genericPointer + 4) = shadow;
						*((WindowAttribute *)genericPointer + 5) = *((WindowAttribute *)genericPointer + 2) - program.borderX;
						*((WindowAttribute *)genericPointer + 6) = *((WindowAttribute *)genericPointer + 3) - program.borderY;
						if(++current < monitorAmount){
							genericPointer = (uint8_t *)genericPointer + genericUnsignedInteger;
							++monitorCurrent;
							goto cascadePerMonitor0;
						}
						genericPointer = (uint8_t *)genericPointer - (monitorAmount - 1) * genericUnsignedInteger;
					}
					containerCurrent = containerStart;
					cascade1:{
						if((!hasContainerOption(*containerCurrent, Maximized) || overrideMaximizedWindows) && (!hasContainerOption(*containerCurrent, InGrid) || overrideGridWindows)){
							genericWindow = (*containerCurrent).window;
							current = getWindowMonitor((*containerCurrent).window);
							genericPointer =(uint8_t *)genericPointer + current * genericUnsignedInteger;
							windowMasks = XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT;
							if(hasContainerOption(*containerCurrent, Maximized)){
								unmaximizeContainer(focused, containerCurrent, maximizedContainerStart);
							}
							if(hasContainerOption(*containerCurrent, InGrid)){
								windowMasks |= XCB_CONFIG_WINDOW_BORDER_WIDTH;
								xcb_change_window_attributes(connection, genericWindow, XCB_CW_BACK_PIXEL, &program.colorContainerBackgroundFloating);
								xcb_clear_area(connection, false, genericWindow, 0, 0, 0, 0);
								removeContainerOption(*containerCurrent, InGrid);
							}
							xcb_configure_window(connection, genericWindow, windowMasks, genericPointer);
							xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, (WindowAttribute *)genericPointer + 5);
							*(WindowAttribute *)genericPointer += offsetX;
							*((WindowAttribute *)genericPointer + 1) += offsetY;
							if((cascadeOffsetX > 0 && *(WindowAttribute *)genericPointer >= *(monitorBorderX + current)) || (cascadeOffsetX < 0 && *(WindowAttribute *)genericPointer + *(totalWidth + current) < *(monitorBorderX + current)) || (cascadeOffsetY > 0 && *((WindowAttribute *)genericPointer + 1) >= *(monitorBorderY + current)) || (cascadeOffsetY < 0 && *((WindowAttribute *)genericPointer + 1) + *(totalHeight + current) < *(monitorBorderY + current))){
								monitorCurrent = monitorStart + current;
								*(WindowAttribute *)genericPointer = ((*monitorCurrent).x + ((*monitorCurrent).width - *((WindowAttribute *)genericPointer + 2)) / 2 - shadow) - offsetX;
								*((WindowAttribute *)genericPointer + 1) = ((*monitorCurrent).y + ((*monitorCurrent).height - *((WindowAttribute *)genericPointer + 3)) / 2 - shadow) - offsetY;
								offsetX = -offsetX;
								offsetY = -offsetY;
							}
							genericPointer = (uint8_t *)genericPointer - current * genericUnsignedInteger;
						}
						if(++containerCurrent < containerWall){
							goto cascade1;
						}
					}
					free(genericPointer);
					goto eventLoop;
				}
				{
					unsigned int monitorBorderX;
					unsigned int totalWidth;
					unsigned int monitorBorderY;
					unsigned int totalHeight;
					monitorCurrent = monitorStart;
					current = 0;
					attribute.a4 = shadow;
					cascadePerMonitor1:{
						if(hasOption(FloatingFollowGrid)){
							attribute.a2 = (*monitorCurrent).width / gridWidth;
							attribute.a3 = (*monitorCurrent).height / gridHeight;
						}else{
							attribute.a2 = (*monitorCurrent).width / floatingWindowDivisor;
							attribute.a3 = (*monitorCurrent).height / floatingWindowDivisor;
						}
						containerCurrent = containerStart;
						if(cascadeOffsetX < 0){
							monitorBorderX = (*monitorCurrent).x;
							totalWidth = 2 * shadow + attribute.a2;
						}else if(cascadeOffsetX > 0){
							monitorBorderX = (*monitorCurrent).x + (*monitorCurrent).width;
						}
						if(cascadeOffsetY < 0){
							monitorBorderY = (*monitorCurrent).y;
							totalHeight = 2 * shadow + attribute.a3;
						}else if(cascadeOffsetY > 0){
							monitorBorderY = (*monitorCurrent).y + (*monitorCurrent).height;
						}
						attribute.a0 = (*monitorCurrent).x + ((*monitorCurrent).width - attribute.a2) / 2 - shadow;
						attribute.a1 = (*monitorCurrent).y + ((*monitorCurrent).height - attribute.a3) / 2 - shadow;
						attribute.a5 = attribute.a2 - program.borderX;
						attribute.a6 = attribute.a3 - program.borderY;
						cascade2:{
							if(getWindowMonitor((*containerCurrent).window) == current){
								if((!hasContainerOption(*containerCurrent, Maximized) || overrideMaximizedWindows) && (!hasContainerOption(*containerCurrent, InGrid) || overrideGridWindows)){
									genericWindow = (*containerCurrent).window;
									windowMasks = XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT;
									if(hasContainerOption(*containerCurrent, Maximized)){
										unmaximizeContainer(focused, containerCurrent, maximizedContainerStart);
									}
									if(hasContainerOption(*containerCurrent, InGrid)){
										windowMasks |= XCB_CONFIG_WINDOW_BORDER_WIDTH;
										xcb_change_window_attributes(connection, genericWindow, XCB_CW_BACK_PIXEL, &program.colorContainerBackgroundFloating);
										xcb_clear_area(connection, false, genericWindow, 0, 0, 0, 0);
										removeContainerOption(*containerCurrent, InGrid);
									}
									xcb_configure_window(connection, genericWindow, windowMasks, &attribute);
									xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a5);
									attribute.a0 += offsetX;
									attribute.a1 += offsetY;
									if((cascadeOffsetX > 0 && attribute.a0 >= monitorBorderX) || (cascadeOffsetX < 0 && attribute.a0 + totalWidth < monitorBorderX) || (cascadeOffsetY > 0 && attribute.a1 >= monitorBorderY) || (cascadeOffsetY < 0 && attribute.a1 + totalHeight < monitorBorderY)){
										attribute.a0 = x - offsetX;
										attribute.a1 = y - offsetY;
										offsetX = -offsetX;
										offsetY = -offsetY;
									}
								}
							}
							if(++containerCurrent < containerWall){
								goto cascade2;
							}
						}
						if(++current < monitorAmount){
							++monitorCurrent;
							goto cascadePerMonitor1;
						}
					}
				}
			}
			goto eventLoop;
		}
		attachCommand:{
			genericWindow = (*(xcb_key_press_event_t *)event).child;
			if(!genericWindow || (containerAmount && (findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current) || findWindow(genericWindow, gridStart, sizeof(xcb_window_t), monitorAmount, &current)))){
				goto eventLoop;
			}
			(*(xcb_map_request_event_t *)event).window = genericWindow;
			if(hasPointerInfo(Attach)){
				current = getPointerMonitor();
				goto mapWindow;
			}
			current = getWindowMonitor(genericWindow);
			goto mapWindow;
		}
		swapMonitorsCommand:{
			if(!(genericPointer = findMonitor(command - SwapNextMonitorCommand, monitorCurrent))){
				goto eventLoop;
			}
			if(hasPointerInfo(SwapMonitors)){
				monitorCurrent = monitorStart + getPointerMonitor();
			}else{
				if(!focused){
					goto eventLoop;
				}
				monitorCurrent = monitorStart + getWindowMonitor((*focused).window);
			}
			attribute.a0 = XCB_STACK_MODE_ABOVE;
			xcb_configure_window(connection, glass, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
			xcb_map_window(connection, glass);
			xcb_flush(connection);
			{
				Command command0;
				unsigned int offset0;
				Container *c0 = NULL;
				Command command1;
				unsigned int offset1;
				Container *c1 = NULL;
				{
					Monitor *oldMonitor;
					Monitor *monitorToUse;
					containerCurrent = containerStart;
					swapWindows:{
						current = getWindowMonitor((*containerCurrent).window);
						if(monitorStart + current == monitorCurrent){
							oldMonitor = monitorCurrent;
							monitorToUse = genericPointer;
						}else if(monitorStart + current == genericPointer){
							oldMonitor = genericPointer;
							monitorToUse = monitorCurrent;
						}else{
							goto swapWindowsLoopControl;
						}
						if(hasContainerOption(*containerCurrent, Maximized)){
							if(!c0){
								if((*(maximizedContainerStart + current)).shouldChangeProperty){
									command0 = FullscreenCommand;
								}else{
									command0 = BigscreenCommand;
								}
								offset0 = monitorToUse - monitorStart;
								c0 = containerCurrent;
							}else{
								if((*(maximizedContainerStart + current)).shouldChangeProperty){
									command1 = FullscreenCommand;
								}else{
									command1 = BigscreenCommand;
								}
								offset1 = monitorToUse - monitorStart;
								c1 = containerCurrent;
							}
							unmaximizeContainer(focused, containerCurrent, maximizedContainerStart);
						}
						switch(program.managementMode){
							case FloatingManagementMode:{
								if(hasContainerOption(*containerCurrent, InGrid)){
									goto swapGriddingInGrid;
								}
								moveFloatingContainer((*containerCurrent).window, (*containerCurrent).subwindow, oldMonitor, monitorToUse, option, gridWidth, gridHeight, floatingWindowDivisor, floatingMinimumWidth, floatingMinimumHeight);
								break;
							}
							case GriddingManagementMode:{
								swapGriddingInGrid:{
									moveGriddingContainer(containerCurrent, monitorToUse, gridWidth, gridHeight);
								}
								break;
							}
							default:{
								/**/



								break;
							}
						}
						swapWindowsLoopControl:{
							if(++containerCurrent < containerWall){
								goto swapWindows;
							}
						}
					}
				}
				if(c0){
					maximizeContainer(command0, monitorStart + offset0, focused, c0, maximizedContainerStart + offset0);
					if(c1){
						maximizeContainer(command1, monitorStart + offset1, focused, c1, maximizedContainerStart + offset0);
					}
				}
				xcb_unmap_window(connection, glass);
			}
			goto eventLoop;
		}
		revolveMonitorsCommand:{
			if(monitorAmount <= 1 || !containerAmount){
				goto eventLoop;
			}
			if(command > RevolveMonitorsPreviousCommand){
				if(hasPointerInfo(RevolveMonitors)){
					monitorCurrent = monitorStart + getPointerMonitor();
				}else{
					if(!focused){
						goto eventLoop;
					}
					monitorCurrent = monitorStart + getWindowMonitor((*focused).window);
				}
			}
			if(!(genericPointer = malloc(monitorAmount * (sizeof(Monitor *) + sizeof(Command) + sizeof(unsigned int) + sizeof(Container *))))){
				printError("not enough ram, could not revolve monitors");
				goto eventLoop;
			}
			attribute.a0 = XCB_STACK_MODE_ABOVE;
			xcb_configure_window(connection, glass, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
			xcb_map_window(connection, glass);
			xcb_flush(connection);
			{
				Monitor **monitors = (Monitor **)genericPointer;
				Command *commands = (Command *)(monitors + monitorAmount);
				unsigned int *offsets = (unsigned int *)(commands + monitorAmount);
				Container **containers = (Container **)(offsets + monitorAmount);
				Container *const *wall = containers;
				switch(command){
					case RevolveMonitorsNextCommand:{
						monitorCurrent = monitorStart + 1;
						setDefaultRevolveMonitorsNext:{
							*monitors = monitorCurrent;
							++monitors;
							if(++monitorCurrent < monitorWall){
								goto setDefaultRevolveMonitorsNext;
							}
						}
						*monitors = monitorStart;
						monitors = (Monitor **)genericPointer;
						goto revolveMonitors;
					}
					case RevolveMonitorsPreviousCommand:{
						*monitors = monitorWall - 1;
						++monitors;
						monitorCurrent = monitorStart;
						setDefaultRevolveMonitorsPrevious:{
							*monitors = monitorCurrent;
							if(++monitors < (Monitor **)commands){
								++monitorCurrent;
								goto setDefaultRevolveMonitorsPrevious;
							}
						}
						monitors = (Monitor **)genericPointer;
						goto revolveMonitors;
					}
					default:{
						const Command command1 = command;
						Monitor **farthest;
						Monitor *m = monitorCurrent;
						bool flag = false;
						*monitors = NULL;
						monitors += monitorAmount;
						setDefaultRevolveMonitors:{
							*monitors = NULL;
							if(--monitors > (Monitor **)genericPointer){
								goto setDefaultRevolveMonitors;
							}
						}
						command -= RevolveMonitorsNextCommand;
						storeAdjacentMonitors0:{
							farthest = monitors + (m - monitorStart);
							if((m = findMonitor(command, m))){
								*farthest = m;
								flag = true;
								goto storeAdjacentMonitors0;
							}
						}
						switch(command1){
							case RevolveMonitorsAboveCommand:
							case RevolveMonitorsLeftCommand:{
								++command;
								break;
							}
							default:{
								--command;
								break;
							}
						}
						m = monitorCurrent;
						storeAdjacentMonitors1:{
							if((monitorCurrent = findMonitor(command, m))){
								*(monitors + (monitorCurrent - monitorStart)) = m;
								m = monitorCurrent;
								flag = true;
								goto storeAdjacentMonitors1;
							}
						}
						if(!flag){
							goto revolveMonitorsEmergencyExit;
						}
						*farthest = m;
						command = command1;
						goto revolveMonitors;
					}
				}
				containerCurrent = containerStart;
				revolveMonitors:{
					current = getWindowMonitor((*containerCurrent).window);
					monitors += current;
					if(*monitors){
						if(hasContainerOption(*containerCurrent, Maximized)){
							if((*(maximizedContainerStart + current)).shouldChangeProperty){
								*commands = FullscreenCommand;
							}else{
								*commands = BigscreenCommand;
							}
							*offsets = *monitors - monitorStart;
							*containers = containerCurrent;
							unmaximizeContainer(focused, containerCurrent, maximizedContainerStart);
							++commands;
							++offsets;
							++containers;
							++wall;
						}
						switch(program.managementMode){
							case FloatingManagementMode:{
								if(hasContainerOption(*containerCurrent, InGrid)){
									goto revolveGriddingInGrid;
								}
								moveFloatingContainer((*containerCurrent).window, (*containerCurrent).subwindow, monitorStart + current, *monitors, option, gridWidth, gridHeight, floatingWindowDivisor, floatingMinimumWidth, floatingMinimumHeight);
								break;
							}
							case GriddingManagementMode:{
								revolveGriddingInGrid:{
									moveGriddingContainer(containerCurrent, *monitors, gridWidth, gridHeight);
								}
								break;
							}
							default:{
								/**/



								break;
							}
						}
					}
					monitors -= current;
					if(++containerCurrent < containerWall){
						goto revolveMonitors;
					}
				}
				commands = (Command *)(monitors + monitorAmount);
				offsets = (unsigned int *)(commands + monitorAmount);
				containers = (Container **)(offsets + monitorAmount);
				revolveMonitorsRemaximize:{
					if(containers < wall){
						maximizeContainer(*commands, monitorStart + *offsets, focused, *containers, maximizedContainerStart + *offsets);
						++commands;
						++offsets;
						++containers;
						goto revolveMonitorsRemaximize;
					}
				}
			}
			revolveMonitorsEmergencyExit:{
				free(genericPointer);
				xcb_unmap_window(connection, glass);
			}
			goto eventLoop;
		}
		moveResizeCommand:{
			if(!containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				goto eventLoop;
			}
			containerCurrent = containerStart + current;
			if(hasContainerOption(*containerCurrent, Maximized)){
				goto eventLoop;
			}
			switch(command){
				case MoveCommand:{
					if(!(*(xcb_key_press_event_t *)event).child){
						goto eventLoop;
					}
					goto move;
				}
				case ResizeCommand:{
					if((*(xcb_key_press_event_t *)event).child){
						goto eventLoop;
					}
					goto resize;
				}
				default:{
					if((*(xcb_key_press_event_t *)event).child){
						move:{
							switch(program.managementMode){
								case FloatingManagementMode:{
									if(hasContainerOption(*containerCurrent, InGrid)){
										goto moveGriddingInGrid;
									}
									if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, genericWindow), NULL))){
										goto eventLoop;
									}
									x = (*(xcb_get_geometry_reply_t *)reply).x + shadow;
									y = (*(xcb_get_geometry_reply_t *)reply).y + shadow;
									width = (*(xcb_get_geometry_reply_t *)reply).width;
									height = (*(xcb_get_geometry_reply_t *)reply).height;
									free(reply);
									if(hasOption(FloatingMinimalMove)){
										attribute.a0 = program.colorMotionContainerMinimalMoveBackground;
										attribute.a1 = program.colorMotionContainerMinimalMoveBorder;
										xcb_change_window_attributes(connection, motionContainerMinimalWindow, XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL, &attribute);
										attribute.a0 = x - motionContainerMinimalMoveBorder;
										attribute.a1 = y - motionContainerMinimalMoveBorder;
										attribute.a2 = width;
										attribute.a3 = height;
										attribute.a4 = motionContainerMinimalMoveBorder;
										attribute.a5 = XCB_STACK_MODE_ABOVE;
										xcb_configure_window(connection, motionContainerMinimalWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT_BORDER_STACK, &attribute);
										xcb_map_window(connection, motionContainerMinimalWindow);
										motionContainerWindow = motionContainerMinimalWindow;
										motionContainerMinimalWindow = genericWindow;
										genericUnsignedInteger = shadow;
										shadow = motionContainerMinimalMoveBorder;
										motionContainerMinimalMoveBorder = genericUnsignedInteger;
									}else{
										motionContainerWindow = genericWindow;
									}
									motionContainerPreviousMonitor = getWindowMonitor(motionContainerWindow);
									pointerOffsetX = (*(xcb_key_press_event_t *)event).event_x + shadow;
									pointerOffsetY = (*(xcb_key_press_event_t *)event).event_y + shadow;
									setMotionOption(None);
									setMotionAction(Move);
									setMotionSubaction(None);
									genericPointer = &attribute;
									goto moveResizeExit;
								}
								case GriddingManagementMode:{
									moveGriddingInGrid:{
										/**/









									}
									goto moveResizeExit;
								}
								default:{
									/**/









									goto moveResizeExit;
								}
							}
						}
					}
					resize:{
						switch(program.managementMode){
							case FloatingManagementMode:{
								if(hasContainerOption(*containerCurrent, InGrid)){
									goto resizeGriddingInGrid;
								}
								if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, genericWindow), NULL))){
									goto eventLoop;
								}
								x = (*(xcb_get_geometry_reply_t *)reply).x;
								y = (*(xcb_get_geometry_reply_t *)reply).y;
								width = (*(xcb_get_geometry_reply_t *)reply).width;
								height = (*(xcb_get_geometry_reply_t *)reply).height;
								free(reply);
								if((*(xcb_key_press_event_t *)event).event_y < (int)borderUp){
									if((*(xcb_key_press_event_t *)event).event_x < (int)borderLeft){
										setMotionSubaction(UpLeftResize);
									}else if((*(xcb_key_press_event_t *)event).event_x < (int)(width - borderRight)){
										setMotionSubaction(UpResize);
									}else{
										setMotionSubaction(UpRightResize);
									}
								}else if((*(xcb_key_press_event_t *)event).event_y < (int)(height - borderDown)){
									if((*(xcb_key_press_event_t *)event).event_x < (int)borderLeft){
										setMotionSubaction(LeftResize);
									}else{
										setMotionSubaction(RightResize);
									}
								}else{
									if((*(xcb_key_press_event_t *)event).event_x < (int)borderLeft){
										setMotionSubaction(DownLeftResize);
									}else if((*(xcb_key_press_event_t *)event).event_x < (int)(width - borderRight)){
										setMotionSubaction(DownResize);
									}else{
										setMotionSubaction(DownRightResize);
									}
								}
								pointerOffsetX = (*(xcb_key_press_event_t *)event).event_x + shadow;
								pointerOffsetY = (*(xcb_key_press_event_t *)event).event_y + shadow;
								if(hasOption(FloatingMinimalResize)){
									attribute.a0 = program.colorMotionContainerMinimalResizeBackground;
									attribute.a1 = program.colorMotionContainerMinimalResizeBorder;
									xcb_change_window_attributes(connection, motionContainerMinimalWindow, XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL, &attribute);
									attribute.a0 = x + shadow - motionContainerMinimalMoveBorder;
									attribute.a1 = y + shadow - motionContainerMinimalMoveBorder;
									attribute.a2 = width;
									attribute.a3 = height;
									attribute.a4 = motionContainerMinimalResizeBorder;
									attribute.a5 = XCB_STACK_MODE_ABOVE;
									xcb_configure_window(connection, motionContainerMinimalWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT_BORDER_STACK, &attribute);
									xcb_map_window(connection, motionContainerMinimalWindow);
									motionContainerWindow = motionContainerMinimalWindow;
									motionContainerMinimalWindow = genericWindow;
									switch(motionContainerSubaction){
										case UpResizeMotionSubaction:
										case LeftResizeMotionSubaction:
										case RightResizeMotionSubaction:
										case UpLeftResizeMotionSubaction:{
											x += shadow - motionContainerMinimalMoveBorder;
											y += shadow - motionContainerMinimalMoveBorder;
											pointerOffsetX += motionContainerMinimalMoveBorder - shadow;
											pointerOffsetY += motionContainerMinimalMoveBorder - shadow;
											break;
										}
										case UpRightResizeMotionSubaction:{
											y += shadow - motionContainerMinimalMoveBorder;
											pointerOffsetY += motionContainerMinimalMoveBorder - shadow;
											break;
										}
										case DownLeftResizeMotionSubaction:{
											x += shadow - motionContainerMinimalMoveBorder;
											pointerOffsetX += motionContainerMinimalMoveBorder - shadow;
											break;
										}
										default:{
											break;
										}
									}
								}else{
									motionContainerWindow = genericWindow;
								}
								motionContainerSubwindow = (*containerCurrent).subwindow;
								setMotionAction(Resize);
								goto moveResizeExit;
							}
							case GriddingManagementMode:{
								resizeGriddingInGrid:{
									/**/









								}
								goto moveResizeExit;
							}
							default:{
								/**/









								goto moveResizeExit;
							}
						}
					}
				}
			}
			moveResizeExit:{
				attribute.a0 = XCB_STACK_MODE_ABOVE;
				xcb_configure_window(connection, motionContainerGlass, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
				xcb_map_window(connection, motionContainerGlass);
			}
			goto eventLoop;
		}
		moveToCommand:{
			if(!containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				goto eventLoop;
			}
			containerCurrent = containerStart + current;
			if(hasContainerOption(*containerCurrent, Maximized)){
				goto eventLoop;
			}
			switch(program.managementMode){
				case FloatingManagementMode:{
					if(hasContainerOption(*containerCurrent, InGrid)){
						goto moveToGriddingInGrid;
					}
					if(hasPointerInfo(MoveToFloating)){
						goto moveToCommandPointerMonitor;
					}else if(hasFlag(SnapInMonitor)){
						removeFlag(SnapInMonitor);
						moveToCommandPointerMonitor:{
							monitorCurrent = monitorStart + getPointerMonitor();
						}
					}else{
						monitorCurrent = monitorStart + getWindowMonitor(genericWindow);
					}
					if(hasOption(FloatingFollowGrid)){
						attribute.a2 = (*monitorCurrent).width / gridWidth;
						attribute.a3 = (*monitorCurrent).height / gridHeight;
					}else{
						attribute.a2 = (*monitorCurrent).width / floatingWindowDivisor;
						attribute.a3 = (*monitorCurrent).height / floatingWindowDivisor;
					}
					attribute.a0 = (*monitorCurrent).x - shadow;
					attribute.a1 = (*monitorCurrent).y - shadow;
					switch(command){
						case MoveTopCommand:{
							attribute.a2 = (*monitorCurrent).width;
							break;
						}
						case MoveBottomCommand:{
							attribute.a1 += (*monitorCurrent).height - attribute.a3;
							attribute.a2 = (*monitorCurrent).width;
							break;
						}
						case MoveLeftCommand:{
							attribute.a3 = (*monitorCurrent).height;
							break;
						}
						case MoveRightCommand:{
							attribute.a0 += (*monitorCurrent).width - attribute.a2;
							attribute.a3 = (*monitorCurrent).height;
							break;
						}
						case MoveTopRightCommand:{
							attribute.a0 += (*monitorCurrent).width - attribute.a2;
							break;
						}
						case MoveBottomLeftCommand:{
							attribute.a1 += (*monitorCurrent).height - attribute.a3;
							break;
						}
						case MoveBottomRightCommand:{
							attribute.a0 += (*monitorCurrent).width - attribute.a2;
							attribute.a1 += (*monitorCurrent).height - attribute.a3;
							break;
						}
						default:{
							break;
						}
					}
					xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
					attribute.a2 -= program.borderX;
					attribute.a3 -= program.borderY;
					xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
					goto eventLoop;
				}
				case GriddingManagementMode:{
					moveToGriddingInGrid:{
						Options followGrid;
						if(hasPointerInfo(MoveToInGrid)){
							monitorCurrent = monitorStart + getPointerMonitor();
						}else{
							monitorCurrent = monitorStart + getWindowMonitor(genericWindow);
						}
						if(isManagementMode(Gridding)){
							followGrid = hasOption(GriddingFollowGrid);
						}else{
							followGrid = hasOption(InGridFollowGrid);
						}
						switch(command){
							case MoveTopCommand:{
								if(followGrid){
									(*containerCurrent).gridHeight = 1;
								}else{
									(*containerCurrent).gridHeight = gridHeight / 2;
									if(!(*containerCurrent).gridHeight){
										(*containerCurrent).gridHeight = 1;
									}
								}
								(*containerCurrent).gridX = 0;
								(*containerCurrent).gridY = 0;
								(*containerCurrent).gridWidth = gridWidth;
								goto moveToInGrid;
							}
							case MoveBottomCommand:{
								if(followGrid){
									(*containerCurrent).gridY = gridHeight - 1;
									(*containerCurrent).gridHeight = 1;
								}else{
									(*containerCurrent).gridHeight = gridHeight / 2;
									if(!(*containerCurrent).gridHeight){
										(*containerCurrent).gridHeight = 1;
									}
									(*containerCurrent).gridY = gridHeight - (*containerCurrent).gridHeight;
								}
								(*containerCurrent).gridX = 0;
								(*containerCurrent).gridWidth = gridWidth;
								goto moveToInGrid;
							}
							case MoveLeftCommand:{
								if(followGrid){
									(*containerCurrent).gridWidth = 1;
								}else{
									(*containerCurrent).gridWidth = gridWidth / 2;
									if(!(*containerCurrent).gridWidth){
										(*containerCurrent).gridWidth = 1;
									}
								}
								(*containerCurrent).gridX = 0;
								(*containerCurrent).gridY = 0;
								(*containerCurrent).gridHeight = gridHeight;
								goto moveToInGrid;
							}
							case MoveRightCommand:{
								if(followGrid){
									(*containerCurrent).gridX = gridWidth - 1;
									(*containerCurrent).gridWidth = 1;
								}else{
									(*containerCurrent).gridWidth = gridWidth / 2;
									if(!(*containerCurrent).gridWidth){
										(*containerCurrent).gridWidth = 1;
									}
									(*containerCurrent).gridX = gridWidth - (*containerCurrent).gridWidth;
								}
								(*containerCurrent).gridY = 0;
								(*containerCurrent).gridHeight = gridHeight;
								goto moveToInGrid;
							}
							default:{
								if(followGrid){
									(*containerCurrent).gridWidth = 1;
									(*containerCurrent).gridHeight = 1;
								}else{
									(*containerCurrent).gridWidth = gridWidth / 2;
									(*containerCurrent).gridHeight = gridHeight / 2;
									if(!(*containerCurrent).gridWidth){
										(*containerCurrent).gridWidth = 1;
									}
									if(!(*containerCurrent).gridHeight){
										(*containerCurrent).gridHeight = 1;
									}
								}
								switch(command){
									case MoveTopLeftCommand:{
										(*containerCurrent).gridX = 0;
										(*containerCurrent).gridY = 0;
										break;
									}
									case MoveTopRightCommand:{
										(*containerCurrent).gridX = gridWidth - (*containerCurrent).gridWidth;
										(*containerCurrent).gridY = 0;
										break;
									}
									case MoveBottomLeftCommand:{
										(*containerCurrent).gridX = 0;
										(*containerCurrent).gridY = gridHeight - (*containerCurrent).gridHeight;
										break;
									}
									default:{
										(*containerCurrent).gridX = gridWidth - (*containerCurrent).gridWidth;
										(*containerCurrent).gridY = gridHeight - (*containerCurrent).gridHeight;
										break;
									}
								}
								moveToInGrid:{
									moveGriddingContainer(containerCurrent, monitorCurrent, gridWidth, gridHeight);
								}
							}
						}
					}
					goto eventLoop;
				}
				default:{
					if(containerAmount > 1){
						if(hasOption(TilingSlamWindows)){
							slamTo:{
								/**/









							}
						}else{
							Command command1 = NoCommand;
							if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, genericWindow), NULL))){
								goto eventLoop;
							}
							x = (*(xcb_get_geometry_reply_t *)reply).x;
							y = (*(xcb_get_geometry_reply_t *)reply).y;
							width = (*(xcb_get_geometry_reply_t *)reply).width;
							height = (*(xcb_get_geometry_reply_t *)reply).height;
							free(reply);
							monitorCurrent = monitorStart + getWindowMonitor(genericWindow);
							switch(command){
								case MoveTopCommand:{
									if(y > (*monitorCurrent).y + (int)gapsY){
										break;
									}
									goto tryToSlamY;
								}
								case MoveBottomCommand:{
									if(y + (int)height < (*monitorCurrent).y + (int)(*monitorCurrent).height - (int)gapsY){
										break;
									}
									tryToSlamY:{
										if(x > (*monitorCurrent).x + (int)gapsX || width < (*monitorCurrent).width - 2 * gapsX){
											goto slamTo;
										}
										if(hasOption(TilingFollowGrid)){
											genericUnsignedInteger = (*monitorCurrent).height / gridHeight;
										}else{
											genericUnsignedInteger = (*monitorCurrent).height / floatingWindowDivisor;
										}
										if(height != genericUnsignedInteger){
											goto slamTo;
										}
									}
									goto eventLoop;
								}
								case MoveLeftCommand:{
									if(x > (*monitorCurrent).x + (int)gapsX){
										break;
									}
									goto tryToSlamX;
								}
								case MoveRightCommand:{
									if(x + (int)width < (*monitorCurrent).x + (int)(*monitorCurrent).width - (int)gapsX){
										break;
									}
									tryToSlamX:{
										if(y > (*monitorCurrent).y + (int)gapsY || height < (*monitorCurrent).height - 2 * gapsY){
											goto slamTo;
										}
										if(hasOption(TilingFollowGrid)){
											genericUnsignedInteger = (*monitorCurrent).width / gridWidth;
										}else{
											genericUnsignedInteger = (*monitorCurrent).width / floatingWindowDivisor;
										}
										if(width != genericUnsignedInteger){
											goto slamTo;
										}
									}
									goto eventLoop;
								}
								case MoveTopLeftCommand:{
									const bool moveLeft = x > (*monitorCurrent).x + (int)gapsX;
									const TilingPrioritization prioritizeY = hasTilingPrioritization(MoveTopLeftY);
									if(y > (*monitorCurrent).y + (int)gapsY){
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
									const bool moveRight = x + (int)width < (*monitorCurrent).x + (int)(*monitorCurrent).width - (int)gapsX;
									const TilingPrioritization prioritizeY = hasTilingPrioritization(MoveTopRightY);
									if(y > (*monitorCurrent).y + (int)gapsY){
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
									const bool moveLeft = x > (*monitorCurrent).x + (int)gapsX;
									const TilingPrioritization prioritizeY = hasTilingPrioritization(MoveBottomLeftY);
									if(y + (int)height < (*monitorCurrent).y + (int)(*monitorCurrent).height - (int)gapsY){
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
									const bool moveRight = x + (int)width < (*monitorCurrent).x + (int)(*monitorCurrent).width - (int)gapsX;
									const TilingPrioritization prioritizeY = hasTilingPrioritization(MoveBottomRightY);
									if(y + (int)height < (*monitorCurrent).y + (int)(*monitorCurrent).height - (int)gapsY){
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
								const Container *const found = containerCurrent;
								const int *position00;
								const int *position01;
								const unsigned int *size00;
								const unsigned int *size01;
								const int *position10;
								const int *position11;
								const unsigned int *size10;
								const Container *containerToUse = containerWall;
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
												monitorSize = (*monitorCurrent).width - 2 * gapsX;
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
												monitorSize = (*monitorCurrent).height - 2 * gapsY;
											}
											break;
										}
									}
									if(hasOption(TilingUseSeparators)){
										spacing = 2 * (spacing + separatorBorder) + separatorWidth;
									}
									containerCurrent = containerStart;
									findWindowToMoveTo:{
										if(containerCurrent != found){
											if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent).window), NULL))){
												goto eventLoop;
											}
											x1 = (*(xcb_get_geometry_reply_t *)reply).x;
											y1 = (*(xcb_get_geometry_reply_t *)reply).y;
											width1 = (*(xcb_get_geometry_reply_t *)reply).width;
											height1 = (*(xcb_get_geometry_reply_t *)reply).height;
											free(reply);
											pixels = getAdjacentSurfaceSize(*position00, *position01, *size00 + spacing, *size01, *position10, *position11, *size10);
											if(pixels > mostPixels){
												containerToUse = containerCurrent;
												mostPixels = pixels;
												if(*size01 == monitorSize){
													goto moveToTilingLoopControl;
												}
											}
										}
										if(++containerCurrent < containerWall){
											goto findWindowToMoveTo;
										}
									}
									moveToTilingLoopControl:{
										if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerToUse).window), NULL))){
											goto eventLoop;
										}
										x1 = (*(xcb_get_geometry_reply_t *)reply).x;
										y1 = (*(xcb_get_geometry_reply_t *)reply).y;
										width1 = (*(xcb_get_geometry_reply_t *)reply).width;
										height1 = (*(xcb_get_geometry_reply_t *)reply).height;
										free(reply);
										attribute.a0 = x1 - shadow;
										attribute.a1 = y1 - shadow;
										attribute.a2 = width1;
										attribute.a3 = height1;
										xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
										attribute.a2 -= program.borderX;
										attribute.a3 -= program.borderY;
										xcb_configure_window(connection, (*found).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
										attribute.a0 = x;
										attribute.a1 = y;
										attribute.a2 = width;
										attribute.a3 = height;
										xcb_configure_window(connection, (*containerToUse).window, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
										attribute.a2 -= program.borderX;
										attribute.a3 -= program.borderY;
										xcb_configure_window(connection, (*containerToUse).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
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
			goto eventLoop;
		}
		moveCenterFullCommand:{
			if(isManagementMode(Tiling) || !containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				goto eventLoop;
			}
			containerCurrent = containerStart + current;
			if(hasContainerOption(*containerCurrent, Maximized)){
				goto eventLoop;
			}
			if(hasContainerOption(*containerCurrent, InGrid)){
				if(hasPointerInfo(MoveToInGrid)){
					goto moveCenterFullCommandInGridPointerMonitor;
				}else if(hasFlag(SnapInMonitor)){
					removeFlag(SnapInMonitor);
					moveCenterFullCommandInGridPointerMonitor:{
						monitorCurrent = monitorStart + getPointerMonitor();
					}
				}else{
					monitorCurrent = monitorStart + getWindowMonitor(genericWindow);
				}
				if(isCommand(MoveCenter)){
					(*containerCurrent).gridX = gridWidth / 2;
					(*containerCurrent).gridY = gridHeight / 2;
					(*containerCurrent).gridWidth = 1;
					(*containerCurrent).gridHeight = 1;
				}else{
					(*containerCurrent).gridX = 0;
					(*containerCurrent).gridY = 0;
					(*containerCurrent).gridWidth = gridWidth;
					(*containerCurrent).gridHeight = gridHeight;
				}
				moveGriddingContainer(containerCurrent, monitorCurrent, gridWidth, gridHeight);
				goto eventLoop;
			}
			if(hasPointerInfo(MoveToFloating)){
				goto moveCenterFullCommandPointerMonitor;
			}else if(hasFlag(SnapInMonitor)){
				removeFlag(SnapInMonitor);
				moveCenterFullCommandPointerMonitor:{
					monitorCurrent = monitorStart + getPointerMonitor();
				}
			}else{
				monitorCurrent = monitorStart + getWindowMonitor(genericWindow);
			}
			if(isCommand(MoveCenter)){
				if(hasOption(FloatingFollowGrid)){
					attribute.a2 = (*monitorCurrent).width / gridWidth;
					attribute.a3 = (*monitorCurrent).height / gridHeight;
				}else{
					attribute.a2 = (*monitorCurrent).width / floatingWindowDivisor;
					attribute.a3 = (*monitorCurrent).height / floatingWindowDivisor;
				}
				attribute.a0 = (*monitorCurrent).x + ((*monitorCurrent).width - attribute.a2) / 2 - shadow;
				attribute.a1 = (*monitorCurrent).y + ((*monitorCurrent).height - attribute.a3) / 2 - shadow;
			}else{
				attribute.a0 = (*monitorCurrent).x - shadow;
				attribute.a1 = (*monitorCurrent).y - shadow;
				attribute.a2 = (*monitorCurrent).width;
				attribute.a3 = (*monitorCurrent).height;
			}
			xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
			attribute.a2 -= program.borderX;
			attribute.a3 -= program.borderY;
			xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
			goto eventLoop;
		}
		moveMonitorCommand:{
			if(!containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current) || !(genericPointer = findMonitor(command - MoveNextMonitorCommand, monitorCurrent))){
				goto eventLoop;
			}
			{
				const ContainerOptions isMaximized = hasContainerOption(*containerCurrent, Maximized);
				containerCurrent = containerStart + current;
				if(hasPointerInfo(MoveToMonitor)){
					monitorCurrent = monitorStart + getPointerMonitor();
				}else{
					monitorCurrent = monitorStart + getWindowMonitor(genericWindow);
				}
				if(isMaximized){
					if((*(maximizedContainerStart + getWindowMonitor(genericWindow))).shouldChangeProperty){
						command = FullscreenCommand;
					}else{
						command = BigscreenCommand;
					}
					maximizedContainerCurrent = maximizedContainerStart + ((Monitor *)genericPointer - monitorStart);
					if((*maximizedContainerCurrent).window && findWindow((*maximizedContainerCurrent).window, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
						unmaximizeContainer(focused, containerStart + current, maximizedContainerStart);
					}
					unmaximizeContainer(focused, containerCurrent, maximizedContainerStart);
				}
				switch(program.managementMode){
					case FloatingManagementMode:{
						if(hasContainerOption(*containerCurrent, InGrid)){
							goto moveMonitorGriddingInGrid;
						}
						moveFloatingContainer(genericWindow, (*containerCurrent).subwindow, monitorCurrent, (Monitor *)genericPointer, option, gridWidth, gridHeight, floatingWindowDivisor, floatingMinimumWidth, floatingMinimumHeight);
						break;
					}
					case GriddingManagementMode:{
						moveMonitorGriddingInGrid:{
							moveGriddingContainer(containerCurrent, (Monitor *)genericPointer, gridWidth, gridHeight);
						}
						break;
					}
					default:{
						/*removeTiling();
						addTiling();*/
						break;
					}
				}
				if(isMaximized){
					maximizeContainer(FullscreenCommand, (Monitor *)genericPointer, focused, containerCurrent, maximizedContainerCurrent);
				}
			}
			goto eventLoop;
		}
		addRemoveToggleGridCommand:{
			if(!isManagementMode(Floating) || !containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				goto eventLoop;
			}
			containerCurrent = containerStart + current;
			if(hasContainerOption(*containerCurrent, Maximized)){
				goto eventLoop;
			}
			switch(command){
				case AddToGridCommand:{
					if(hasContainerOption(*containerCurrent, InGrid)){
						goto eventLoop;
					}
					goto addToGrid;
				}
				case RemoveFromGridCommand:{
					if(!hasContainerOption(*containerCurrent, InGrid)){
						goto eventLoop;
					}
					goto removeFromGrid;
				}
				default:{
					if(!hasContainerOption(*containerCurrent, InGrid)){
						addToGrid:{
							if(hasPointerInfo(AddToGrid)){
								monitorCurrent = monitorStart + getPointerMonitor();
							}else{
								monitorCurrent = monitorStart + getWindowMonitor(genericWindow);
							}
							switch(defaultGridPosition){
								case TopLeftDefaultGridPosition:{
									(*containerCurrent).gridX = 0;
									(*containerCurrent).gridY = 0;
									break;
								}
								case TopRightDefaultGridPosition:{
									(*containerCurrent).gridX = gridWidth - 1;
									(*containerCurrent).gridY = 0;
									break;
								}
								case BottomLeftDefaultGridPosition:{
									(*containerCurrent).gridX = 0;
									(*containerCurrent).gridY = gridHeight - 1;
									break;
								}
								case BottomRightDefaultGridPosition:{
									(*containerCurrent).gridX = gridWidth - 1;
									(*containerCurrent).gridY = gridHeight - 1;
									break;
								}
								default:{
									(*containerCurrent).gridX = gridWidth / 2;
									(*containerCurrent).gridY = gridHeight / 2;
									break;
								}
							}
							if(focused == containerCurrent){
								attribute.a0 = program.colorFocusedContainerBackgroundInGrid;
							}else{
								attribute.a0 = program.colorContainerBackgroundInGrid;
							}
							attribute.a1 = XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT;
							xcb_change_window_attributes(connection, genericWindow, XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK, &attribute);
							attribute.a0 = XCB_EVENT_MASK_STRUCTURE_NOTIFY;
							xcb_change_window_attributes(connection, (*containerCurrent).subwindow, XCB_CW_EVENT_MASK, &attribute);
							getGridSlotData((*monitorCurrent).width, (*monitorCurrent).height, (*containerCurrent).gridX, (*containerCurrent).gridY, gridWidth, gridHeight, (int *)&attribute.a0, (int *)&attribute.a1, &attribute.a2, &attribute.a3);
							attribute.a0 += (*monitorCurrent).x;
							attribute.a1 += (*monitorCurrent).y;
							attribute.a4 = 0;
							(*containerCurrent).gridWidth = 1;
							(*containerCurrent).gridHeight = 1;
							addContainerOption(*containerCurrent, InGrid);
							goto addRemoveGrid;
						}
					}
					removeFromGrid:{
						if(hasPointerInfo(RemoveFromGrid)){
							monitorCurrent = monitorStart + getPointerMonitor();
						}else{
							monitorCurrent = monitorStart + getWindowMonitor(genericWindow);
						}
						if(hasOption(FloatingFollowGrid)){
							attribute.a2 = (*monitorCurrent).width / gridWidth;
							attribute.a3 = (*monitorCurrent).height / gridHeight;
						}else{
							attribute.a2 = (*monitorCurrent).width / floatingWindowDivisor;
							attribute.a3 = (*monitorCurrent).height / floatingWindowDivisor;
						}
						if(focused == containerCurrent){
							attribute.a0 = program.colorFocusedContainerBackgroundFloating;
						}else{
							attribute.a0 = program.colorContainerBackgroundFloating;
						}
						attribute.a1 = XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT;
						xcb_change_window_attributes(connection, genericWindow, XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK, &attribute);
						attribute.a0 = XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY;
						xcb_change_window_attributes(connection, (*containerCurrent).subwindow, XCB_CW_EVENT_MASK, &attribute);
						attribute.a0 = (*monitorCurrent).x + ((*monitorCurrent).width - attribute.a2) / 2 - shadow;
						attribute.a1 = (*monitorCurrent).y + ((*monitorCurrent).height - attribute.a3) / 2 - shadow;
						attribute.a4 = shadow;
						removeContainerOption(*containerCurrent, InGrid);
						addRemoveGrid:{
							xcb_clear_area(connection, false, genericWindow, 0, 0, 0, 0);
							xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT_BORDER, &attribute);
							attribute.a2 -= program.borderX;
							attribute.a3 -= program.borderY;
							xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
						}
					}
					goto eventLoop;
				}
			}
			goto eventLoop;
		}
		moveInsideGridCommand:{
			if(!containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				goto eventLoop;
			}
			containerCurrent = containerStart + current;
			if(hasContainerOption(*containerCurrent, Maximized) || !hasContainerOption(*containerCurrent, InGrid)){
				goto eventLoop;
			}
			switch(command){
				case MoveUpGridCommand:{
					if(!(*containerCurrent).gridY){
						goto eventLoop;
					}
					--(*containerCurrent).gridY;
					goto moveInsideGrid;
				}
				case MoveDownGridCommand:{
					if((*containerCurrent).gridY + (*containerCurrent).gridHeight >= gridHeight){
						goto eventLoop;
					}
					++(*containerCurrent).gridY;
					goto moveInsideGrid;
				}
				case MoveLeftGridCommand:{
					if(!(*containerCurrent).gridX){
						goto eventLoop;
					}
					--(*containerCurrent).gridX;
					goto moveInsideGrid;
				}
				default:{
					if((*containerCurrent).gridX + (*containerCurrent).gridWidth >= gridWidth){
						goto eventLoop;
					}
					++(*containerCurrent).gridX;
					moveInsideGrid:{
						if(hasPointerInfo(MoveOnGrid)){
							current = getPointerMonitor();
						}else{
							current = getWindowMonitor((*containerCurrent).window);
						}
						moveGriddingContainer(containerCurrent, monitorStart + current, gridWidth, gridHeight);
					}
					goto eventLoop;
				}
			}
		}
		extendCommand:{
			if(!containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				goto eventLoop;
			}
			containerCurrent = containerStart + current;
			if(hasContainerOption(*containerCurrent, Maximized)){
				goto eventLoop;
			}
			switch(program.managementMode){
				case FloatingManagementMode:{
					if(hasContainerOption(*containerCurrent, InGrid)){
						goto extendGriddingInGrid;
					}
					if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, genericWindow), NULL))){
						goto eventLoop;
					}
					x = (*(xcb_get_geometry_reply_t *)reply).x;
					y = (*(xcb_get_geometry_reply_t *)reply).y;
					width = (*(xcb_get_geometry_reply_t *)reply).width;
					height = (*(xcb_get_geometry_reply_t *)reply).height;
					free(reply);
					switch(command){
						case ExtendUpCommand:
						case ExtendDownCommand:{
							if(height < floatingMaximumHeight){
								if(isCommand(ExtendUp)){
									y -= floatingExtendHeight;
								}
								height += floatingExtendHeight;
								if(height > floatingMaximumHeight){
									if(isCommand(ExtendUp)){
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
								if(isCommand(ExtendLeft)){
									x -= floatingExtendWidth;
								}
								width += floatingExtendWidth;
								if(width > floatingMaximumWidth){
									if(isCommand(ExtendLeft)){
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
									if(isCommand(ExtendUpLeft) || isCommand(ExtendDownLeft)){
										x -= floatingExtendWidth;
									}
									width += floatingExtendWidth;
									if(width > floatingMaximumWidth){
										if(isCommand(ExtendLeft)){
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
								if((*containerCurrent).gridY){
									--(*containerCurrent).gridY;
									++(*containerCurrent).gridHeight;
									goto extendInGrid;
								}
								goto eventLoop;
							}
							case ExtendDownCommand:{
								if((*containerCurrent).gridY + (*containerCurrent).gridHeight < gridHeight){
									++(*containerCurrent).gridHeight;
									goto extendInGrid;
								}
								goto eventLoop;
							}
							case ExtendLeftCommand:{
								if((*containerCurrent).gridX){
									--(*containerCurrent).gridX;
									++(*containerCurrent).gridWidth;
									goto extendInGrid;
								}
								goto eventLoop;
							}
							case ExtendRightCommand:{
								if((*containerCurrent).gridX + (*containerCurrent).gridWidth < gridWidth){
									++(*containerCurrent).gridWidth;
									goto extendInGrid;
								}
								goto eventLoop;
							}
							case ExtendUpLeftCommand:{
								if((*containerCurrent).gridY){
									--(*containerCurrent).gridY;
									++(*containerCurrent).gridHeight;
									if((*containerCurrent).gridX){
										--(*containerCurrent).gridX;
										++(*containerCurrent).gridWidth;
									}
									goto extendInGrid;
								}
								if((*containerCurrent).gridX){
									--(*containerCurrent).gridX;
									++(*containerCurrent).gridWidth;
									goto extendInGrid;
								}
								goto eventLoop;
							}
							case ExtendUpRightCommand:{
								if((*containerCurrent).gridY){
									--(*containerCurrent).gridY;
									++(*containerCurrent).gridHeight;
									if((*containerCurrent).gridX + (*containerCurrent).gridWidth < gridWidth){
										++(*containerCurrent).gridWidth;
									}
									goto extendInGrid;
								}
								if((*containerCurrent).gridX + (*containerCurrent).gridWidth < gridWidth){
									++(*containerCurrent).gridWidth;
									goto extendInGrid;
								}
								goto eventLoop;
							}
							case ExtendDownLeftCommand:{
								if((*containerCurrent).gridY + (*containerCurrent).gridHeight < gridHeight){
									++(*containerCurrent).gridHeight;
									if((*containerCurrent).gridX){
										--(*containerCurrent).gridX;
										++(*containerCurrent).gridWidth;
									}
									goto extendInGrid;
								}
								if((*containerCurrent).gridX){
									--(*containerCurrent).gridX;
									++(*containerCurrent).gridWidth;
									goto extendInGrid;
								}
								goto eventLoop;
							}
							default:{
								if((*containerCurrent).gridY + (*containerCurrent).gridHeight < gridHeight){
									++(*containerCurrent).gridHeight;
									if((*containerCurrent).gridX + (*containerCurrent).gridWidth < gridWidth){
										++(*containerCurrent).gridWidth;
									}
									goto extendInGrid;
								}
								if((*containerCurrent).gridX + (*containerCurrent).gridWidth < gridWidth){
									++(*containerCurrent).gridWidth;
									extendInGrid:{
										if(hasPointerInfo(ExtendInGrid)){
											monitorCurrent = monitorStart + getPointerMonitor();
										}else{
											monitorCurrent = monitorStart + getWindowMonitor(genericWindow);
										}
										moveGriddingContainer(containerCurrent, monitorCurrent, gridWidth, gridHeight);
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
						printError("not enough ram, could not resize tiling window");
						goto eventLoop;
					}
					if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, genericWindow), NULL))){
						goto extendTilingEmergencyExit;
					}
					x = (*(xcb_get_geometry_reply_t *)reply).x;
					y = (*(xcb_get_geometry_reply_t *)reply).y;
					width = (*(xcb_get_geometry_reply_t *)reply).width;
					height = (*(xcb_get_geometry_reply_t *)reply).height;
					free(reply);
					current = getWindowMonitor(genericWindow);
					monitorCurrent = monitorStart + current;
					switch(command){
						case ExtendUpCommand:{
							if(y > (*monitorCurrent).y + (int)gapsY){
								break;
							}
							goto extendTilingEmergencyExit;
						}
						case ExtendDownCommand:{
							if(y + (int)height < (*monitorCurrent).y + (int)((*monitorCurrent).height - gapsY)){
								break;
							}
							goto extendTilingEmergencyExit;
						}
						case ExtendLeftCommand:{
							if(x > (*monitorCurrent).x + (int)gapsX){
								break;
							}
							goto extendTilingEmergencyExit;
						}
						case ExtendRightCommand:{
							if(x + (int)width < (*monitorCurrent).x + (int)((*monitorCurrent).width - gapsX)){
								break;
							}
							goto extendTilingEmergencyExit;
						}
						case ExtendUpLeftCommand:{
							const bool extendLeft = x > (*monitorCurrent).x + (int)gapsX;
							if(y > (*monitorCurrent).y + (int)gapsY){
								if(extendLeft){
									if(hasTilingPrioritization(ExtendUpLeftY)){
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
							goto extendTilingEmergencyExit;
						}
						case ExtendUpRightCommand:{
							const bool extendRight = x + (int)width < (*monitorCurrent).x + (int)((*monitorCurrent).width - gapsX);
							if(y > (*monitorCurrent).y + (int)gapsY){
								if(extendRight){
									if(hasTilingPrioritization(ExtendUpRightY)){
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
							goto extendTilingEmergencyExit;
						}
						case ExtendDownLeftCommand:{
							const bool extendLeft = x > (*monitorCurrent).x + (int)gapsX;
							if(y + (int)height < (*monitorCurrent).y + (int)((*monitorCurrent).height - gapsY)){
								if(extendLeft){
									if(hasTilingPrioritization(ExtendUpLeftY)){
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
							goto extendTilingEmergencyExit;
						}
						default:{
							const bool extendRight = x + (int)width < (*monitorCurrent).x + (int)((*monitorCurrent).width - gapsX);
							if(y + (int)height < (*monitorCurrent).y + (int)((*monitorCurrent).height - gapsY)){
								if(extendRight){
									if(hasTilingPrioritization(ExtendUpRightY)){
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
							goto extendTilingEmergencyExit;
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
							if(hasOption(TilingUseSeparators)){
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
							containerCurrent = containerStart;
							addWindowToListExtend:{
								if(*resizeCurrent == NoTilingResize){
									if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent).window), NULL))){
										goto extendTilingEmergencyExit;
									}
									x1 = (*(xcb_get_geometry_reply_t *)reply).x;
									y1 = (*(xcb_get_geometry_reply_t *)reply).y;
									width1 = (*(xcb_get_geometry_reply_t *)reply).width;
									height1 = (*(xcb_get_geometry_reply_t *)reply).height;
									free(reply);
									if(*position0 == *position1 && getWindowMonitor((*containerCurrent).window) == current){
										resizeCurrent1 = resize;
										containerCurrent1 = containerStart;
										addOpposingWindowToListExtend:{
											if(*resizeCurrent1 == NoTilingResize){
												if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent1).window), NULL))){
													goto extendTilingEmergencyExit;
												}
												x2 = (*(xcb_get_geometry_reply_t *)reply).x;
												y2 = (*(xcb_get_geometry_reply_t *)reply).y;
												width2 = (*(xcb_get_geometry_reply_t *)reply).width;
												height2 = (*(xcb_get_geometry_reply_t *)reply).height;
												free(reply);
												if(*position2 == *position3 + (int)(*size0 + separationWidth)){
													if(closedOpenInterval(*position4, *position5, *position5 + (int)*size1) || closedOpenInterval(*position4 + (int)*size2, *position5, *position5 + (int)*size1) || closedOpenInterval(*position5, *position4, *position4 + (int)*size2)){
														if(getWindowMonitor((*containerCurrent1).window) == current){
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
									++containerCurrent;
									goto addWindowToListExtend;
								}
							}
							if(resizeAmount){
								resizeCurrent = resize;
								offset *= customExtend;
								currentResize = 0;
								resizeExtendWindowTiling:{
									if(*resizeCurrent != NoTilingResize){
										containerCurrent = containerStart + (resizeCurrent - resize);
										if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent).window), NULL))){
											goto extendTilingEmergencyExit;
										}
										x = (*(xcb_get_geometry_reply_t *)reply).x;
										y = (*(xcb_get_geometry_reply_t *)reply).y;
										width = (*(xcb_get_geometry_reply_t *)reply).width;
										height = (*(xcb_get_geometry_reply_t *)reply).height;
										free(reply);
										*position1 += *resizeCurrent / 2 * customExtend - offset;
										*size4 += customExtend - *resizeCurrent * customExtend;
										attribute.a0 = x;
										attribute.a1 = y;
										attribute.a2 = width;
										attribute.a3 = height;
										xcb_configure_window(connection, (*containerCurrent).window, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
										attribute.a2 -= program.borderX;
										attribute.a3 -= program.borderY;
										xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
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
					extendTilingEmergencyExit:{
						free(resize);
						goto eventLoop;
					}
				}
			}
			goto eventLoop;
		}
		shrinkCommand:{
			if(!containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				goto eventLoop;
			}
			containerCurrent = containerStart + current;
			if(hasContainerOption(*containerCurrent, Maximized)){
				goto eventLoop;
			}
			switch(program.managementMode){
				case FloatingManagementMode:{
					if(hasContainerOption(*containerCurrent, InGrid)){
						goto shrinkGriddingInGrid;
					}
					if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent).window), NULL))){
						goto eventLoop;
					}
					x = (*(xcb_get_geometry_reply_t *)reply).x;
					y = (*(xcb_get_geometry_reply_t *)reply).y;
					width = (*(xcb_get_geometry_reply_t *)reply).width;
					height = (*(xcb_get_geometry_reply_t *)reply).height;
					free(reply);
					switch(command){
						case ShrinkUpCommand:
						case ShrinkDownCommand:{
							if(height > floatingMinimumHeight){
								if(isCommand(ShrinkDown)){
									y += floatingShrinkHeight;
								}
								height -= floatingShrinkHeight;
								if((int)height < (int)floatingMinimumHeight){
									if(isCommand(ShrinkDown)){
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
								if(isCommand(ShrinkRight)){
									x += floatingShrinkWidth;
								}
								width -= floatingShrinkWidth;
								if((int)width < (int)floatingMinimumWidth){
									if(isCommand(ShrinkRight)){
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
									if(isCommand(ShrinkUpRight) || isCommand(ShrinkDownRight)){
										x += floatingShrinkWidth;
									}
									width -= floatingShrinkWidth;
									if((int)width < (int)floatingMinimumWidth){
										if(isCommand(ShrinkUpRight) || isCommand(ShrinkDownRight)){
											x -= floatingMinimumWidth - width;
										}
										width = floatingMinimumWidth;
									}
								}
								extendShrinkFloating:{
									attribute.a0 = x;
									attribute.a1 = y;
									attribute.a2 = width;
									attribute.a3 = height;
									xcb_configure_window(connection, (*containerCurrent).window, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
									attribute.a2 -= program.borderX;
									attribute.a3 -= program.borderY;
									xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
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
								if((*containerCurrent).gridHeight > 1){
									if(isCommand(ShrinkDown)){
										++(*containerCurrent).gridY;
									}
									--(*containerCurrent).gridHeight;
									goto shrinkInGrid;
								}
								goto eventLoop;
							}
							case ShrinkLeftCommand:
							case ShrinkRightCommand:{
								if((*containerCurrent).gridWidth > 1){
									if(isCommand(ShrinkRight)){
										++(*containerCurrent).gridX;
									}
									--(*containerCurrent).gridWidth;
									goto shrinkInGrid;
								}
								goto eventLoop;
							}
							default:{
								if((*containerCurrent).gridHeight > 1){
									if(command >= ShrinkDownLeftCommand){
										++(*containerCurrent).gridY;
									}
									--(*containerCurrent).gridHeight;
									if((*containerCurrent).gridWidth > 1){
										goto shrinkWidthInGrid;
									}
									goto shrinkInGrid;
								}
								if((*containerCurrent).gridWidth > 1){
									shrinkWidthInGrid:{
										if(isCommand(ShrinkUpRight) || isCommand(ShrinkDownRight)){
											++(*containerCurrent).gridX;
										}
										--(*containerCurrent).gridWidth;
									}
									shrinkInGrid:{
										if(hasPointerInfo(ShrinkInGrid)){
											monitorCurrent = monitorStart + getPointerMonitor();
										}else{
											monitorCurrent = monitorStart + getWindowMonitor(genericWindow);
										}
										moveGriddingContainer(containerCurrent, monitorCurrent, gridWidth, gridHeight);
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
						printError("not enough ram, could not resize tiling window");
						goto eventLoop;
					}
					if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, genericWindow), NULL))){
						goto shrinkTilingEmergencyExit;
					}
					x = (*(xcb_get_geometry_reply_t *)reply).x;
					y = (*(xcb_get_geometry_reply_t *)reply).y;
					width = (*(xcb_get_geometry_reply_t *)reply).width;
					height = (*(xcb_get_geometry_reply_t *)reply).height;
					free(reply);
					current = getWindowMonitor(genericWindow);
					monitorCurrent = monitorStart + current;
					switch(command){
						case ShrinkUpCommand:{
							if(y + (int)height < (*monitorCurrent).y + (int)((*monitorCurrent).height - gapsY) && height > tilingMinimumHeight){
								break;
							}
							goto shrinkTilingEmergencyExit;
						}
						case ShrinkDownCommand:{
							if(y > (*monitorCurrent).y + (int)gapsY && height > tilingMinimumHeight){
								break;
							}
							goto shrinkTilingEmergencyExit;
						}
						case ShrinkLeftCommand:{
							if(x + (int)width < (*monitorCurrent).x + (int)((*monitorCurrent).width - gapsX) && width > tilingMinimumWidth){
								break;
							}
							goto shrinkTilingEmergencyExit;
						}
						case ShrinkRightCommand:{
							if(x > (*monitorCurrent).x + (int)gapsX && width > tilingMinimumWidth){
								break;
							}
							goto shrinkTilingEmergencyExit;
						}
						case ShrinkUpLeftCommand:{
							const bool shrinkLeft = x > (*monitorCurrent).x + (int)gapsX && width > tilingMinimumWidth;
							if(y > (*monitorCurrent).y + (int)gapsY && height > tilingMinimumHeight){
								if(shrinkLeft){
									if(hasTilingPrioritization(ShrinkUpLeftY)){
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
							goto shrinkTilingEmergencyExit;
						}
						case ShrinkUpRightCommand:{
							const bool shrinkRight = x + (int)width < (*monitorCurrent).x + (int)((*monitorCurrent).width - gapsX) && width > tilingMinimumWidth;
							if(y > (*monitorCurrent).y + (int)gapsY && height > tilingMinimumHeight){
								if(shrinkRight){
									if(hasTilingPrioritization(ShrinkUpRightY)){
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
							goto shrinkTilingEmergencyExit;
						}
						case ShrinkDownLeftCommand:{
							const bool shrinkLeft = x > (*monitorCurrent).x + (int)gapsX && width > tilingMinimumWidth;
							if(y + (int)height < (*monitorCurrent).y + (int)((*monitorCurrent).height - gapsY) && height > tilingMinimumHeight){
								if(shrinkLeft){
									if(hasTilingPrioritization(ShrinkDownLeftY)){
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
							goto shrinkTilingEmergencyExit;
						}
						default:{
							const bool shrinkRight = x + (int)width < (*monitorCurrent).x + (int)((*monitorCurrent).width - gapsX) && width > tilingMinimumWidth;
							if(y + (int)height < (*monitorCurrent).y + (int)((*monitorCurrent).height - gapsY) && height > tilingMinimumHeight){
								if(shrinkRight){
									if(hasTilingPrioritization(ShrinkDownRightY)){
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
							goto shrinkTilingEmergencyExit;
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
							if(hasOption(TilingUseSeparators)){
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
							containerCurrent = containerStart;
							addWindowToListShrink:{
								if(*resizeCurrent == NoTilingResize){
									if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent).window), NULL))){
										goto shrinkTilingEmergencyExit;
									}
									x1 = (*(xcb_get_geometry_reply_t *)reply).x;
									y1 = (*(xcb_get_geometry_reply_t *)reply).y;
									width1 = (*(xcb_get_geometry_reply_t *)reply).width;
									height1 = (*(xcb_get_geometry_reply_t *)reply).height;
									free(reply);
									if(*position0 == *position1 && getWindowMonitor((*containerCurrent).window) == current){
										if(*size0 - customShrink < tilingMinimum){
											customShrink = *size0 - tilingMinimum;
											if(!customShrink){
												goto shrinkTilingLoopControl;
											}
										}
										resizeCurrent1 = resize;
										containerCurrent1 = containerStart;
										addOpposingWindowToListShrink:{
											if(*resizeCurrent1 == NoTilingResize){
												if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent1).window), NULL))){
													goto shrinkTilingEmergencyExit;
												}
												x2 = (*(xcb_get_geometry_reply_t *)reply).x;
												y2 = (*(xcb_get_geometry_reply_t *)reply).y;
												width2 = (*(xcb_get_geometry_reply_t *)reply).width;
												height2 = (*(xcb_get_geometry_reply_t *)reply).height;
												free(reply);
												if(*position2 == *position3 + (int)(*size1 + separationWidth)){
													if(closedOpenInterval(*position4, *position5, *position5 + (int)*size2) || closedOpenInterval(*position4 + (int)*size3, *position5, *position5 + (int)*size2) || closedOpenInterval(*position5, *position4, *position4 + (int)*size3)){
														if(getWindowMonitor((*containerCurrent1).window) == current){
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
									++containerCurrent;
									goto addWindowToListShrink;
								}
							}
							if(resizeAmount){
								resizeCurrent = resize;
								offset *= customShrink;
								currentResize = 0;
								resizeShrinkWindowTiling:{
									if(*resizeCurrent != NoTilingResize){
										containerCurrent = containerStart + (resizeCurrent - resize);
										if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, (*containerCurrent).window), NULL))){
											goto shrinkTilingEmergencyExit;
										}
										x = (*(xcb_get_geometry_reply_t *)reply).x;
										y = (*(xcb_get_geometry_reply_t *)reply).y;
										width = (*(xcb_get_geometry_reply_t *)reply).width;
										height = (*(xcb_get_geometry_reply_t *)reply).height;
										free(reply);
										*position1 += *resizeCurrent / 2 * customShrink - offset;
										*size0 += customShrink - *resizeCurrent * customShrink;
										attribute.a0 = x;
										attribute.a1 = y;
										attribute.a2 = width;
										attribute.a3 = height;
										xcb_configure_window(connection, (*containerCurrent).window, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
										attribute.a2 -= program.borderX;
										attribute.a3 -= program.borderY;
										xcb_configure_window(connection, (*containerCurrent).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
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
					shrinkTilingEmergencyExit:{
						free(resize);
						goto eventLoop;
					}
				}
			}
			goto eventLoop;
		}
		fullscreenBigscreenCommand:{
			if(!containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				goto eventLoop;
			}
			containerCurrent = containerStart + current;
			if(hasPointerInfo(Maximize)){
				current = getPointerMonitor();
			}else{
				current = getWindowMonitor(genericWindow);
			}
			maximizedContainerCurrent = maximizedContainerStart + current;
			if((*maximizedContainerCurrent).window){
				genericWindow = (*maximizedContainerCurrent).window;
				unmaximizeContainer(focused, containerCurrent, maximizedContainerStart);
				if(genericWindow == (*containerCurrent).window){
					goto eventLoop;
				}
			}
			maximizeContainer(command, monitorStart + current, focused, containerCurrent, maximizedContainerCurrent);
			goto eventLoop;
		}
		detachCommand:{
			if(!containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				goto eventLoop;
			}
			if(hasPointerInfo(Detach)){
				monitorCurrent = monitorStart + getPointerMonitor();
			}else{
				monitorCurrent = monitorStart + getWindowMonitor(genericWindow);
			}
			containerCurrent = containerStart + current;
			genericWindow = (*containerCurrent).subwindow;
			attribute.a0 = XCB_STACK_MODE_ABOVE;
			xcb_configure_window(connection, glass, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
			xcb_map_window(connection, glass);
			xcb_flush(connection);
			xcb_set_input_focus(connection, XCB_INPUT_FOCUS_POINTER_ROOT, (*screen).root, XCB_CURRENT_TIME);
			attribute.a0 = XCB_EVENT_MASK_NO_EVENT;
			xcb_change_window_attributes(connection, genericWindow, XCB_CW_EVENT_MASK, &attribute);
			attribute.a0 = (*monitorCurrent).width / floatingWindowDivisor;
			attribute.a1 = (*monitorCurrent).height / floatingWindowDivisor;
			xcb_reparent_window(connection, genericWindow, (*screen).root, (*monitorCurrent).x + ((*monitorCurrent).width - attribute.a0) / 2, (*monitorCurrent).y + ((*monitorCurrent).height - attribute.a1) / 2);
			xcb_configure_window(connection, genericWindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute);
			if(isManagementMode(Tiling)){
				/*removeTilingWindow();*/
			}
			if(containerCurrent == focused){
				focused = NULL;
			}
			xcb_unmap_window(connection, glass);
			goto destroyWindow;
		}
		closeCommand:{
			if(!containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				goto eventLoop;
			}
			{
				xcb_client_message_event_t e;
				e.response_type = XCB_CLIENT_MESSAGE;
				e.format = 32;
				e.sequence = xcb_no_operation(connection).sequence;
				e.window = (*(containerStart + current)).subwindow;
				e.type = program.WM_PROTOCOLS;
				*e.data.data32 = program.WM_DELETE_WINDOW;
				*(e.data.data32 + 1) = XCB_CURRENT_TIME;
				xcb_send_event(connection, false, e.window, XCB_EVENT_MASK_PROPERTY_CHANGE, (char *)&e);
			}
			goto eventLoop;
		}
		killCommand:{
			if(!containerAmount || !findWindow(genericWindow, &(*containerStart).window, sizeof(Container), containerAmount, &current)){
				goto eventLoop;
			}
			containerCurrent = containerStart + current;
			attribute.a0 = XCB_STACK_MODE_ABOVE;
			xcb_configure_window(connection, glass, XCB_CONFIG_WINDOW_STACK_MODE, &attribute);
			xcb_map_window(connection, glass);
			xcb_flush(connection);
			xcb_set_input_focus(connection, XCB_INPUT_FOCUS_POINTER_ROOT, (*screen).root, XCB_CURRENT_TIME);
			xcb_kill_client(connection, (*containerCurrent).subwindow);
			if(isManagementMode(Tiling)){
				/*removeTilingWindow();*/
			}
			if(containerCurrent == focused){
				focused = NULL;
			}
			xcb_unmap_window(connection, glass);
			removeContainerOption(*containerCurrent, Mapped);
			goto destroyWindow;
		}
	}
	eventLoopExit:{
		if(hasFlag(AllowCommandSending)){
			pthread_cancel(thread);
		}
		free(event);
		free(e);
		genericWindow = (*screen).root;
		if(isMode(Exit)){
			if(containerAmount){
				containerCurrent = containerStart;
				returnClient:{
					xcb_reparent_window(connection, (*containerCurrent).subwindow, genericWindow, 0, 0);
					xcb_destroy_window(connection, (*containerCurrent).window);
					if(++containerCurrent < containerWall){
						goto returnClient;
					}
				}
			}
			goto emergencyExit;
		}
		xcb_ungrab_key(connection, XCB_GRAB_ANY, genericWindow, XCB_MOD_MASK_ANY);
		xcb_ungrab_button(connection, XCB_BUTTON_INDEX_ANY, genericWindow, XCB_MOD_MASK_ANY);
		if(containerAmount){
			containerCurrent = containerStart;
			ungrabContainerWindow:{
				xcb_ungrab_key(connection, XCB_GRAB_ANY, (*containerCurrent).window, XCB_MOD_MASK_ANY);
				xcb_ungrab_button(connection, XCB_BUTTON_INDEX_ANY, (*containerCurrent).window, XCB_MOD_MASK_ANY);
				if(++containerCurrent < containerWall){
					goto ungrabContainerWindow;
				}
			}
		}
	}
	emergencyExit:{
		free(userData);
		if(isMode(Continue)){
			gridCurrent = gridStart;
			destroyGridWindows:{
				xcb_destroy_window(connection, *gridCurrent);
				if(++gridCurrent < gridWall){
					goto destroyGridWindows;
				}
			}
			goto readConfig;
		}
		free(containerData);
	}
	return;
}
FINDWINDOW_DEC{
	unsigned int c = 0;
	loop:{
		if(*location == w){
			*current = c;
			return true;
		}
		if(++c < amount){
			location = (xcb_window_t *)((uint8_t *)location + size);
			goto loop;
		}
	}
	return false;
}
GETADJACENTSURFACESIZE_DEC{
	if(position00 + size00 != position10){
		return 0;
	}
	if(closedOpenInterval(position01, position11, position11 + size10)){
		if(position01 + size01 < position11 + size10){
			return size01;
		}
		return position11 + size10 - position01;
	}
	if(closedOpenInterval(position01 + size01, position11, position11 + size10)){
		return position01 + size01 - position11;
	}
	if(closedOpenInterval(position11, position01, position01 + size01)){
		return size10;
	}
	return 0;
}
GETPOINTERMONITOR_DEC{
	if(monitorAmount <= 1 || !(reply = xcb_query_pointer_reply(connection, xcb_query_pointer_unchecked(connection, (*screen).root), NULL))){
		return 0;
	}
	{
		int x = (*(xcb_query_pointer_reply_t *)reply).root_x;
		int y = (*(xcb_query_pointer_reply_t *)reply).root_y;
		unsigned int current = 0;
		free(reply);
		loop:{
			if(!closedOpenInterval(x, (*monitor).x, (*monitor).x + (int)(*monitor).width) || !closedOpenInterval(y, (*monitor).y, (*monitor).y + (int)(*monitor).height)){
				if(++current < monitorAmount){
					++monitor;
					goto loop;
				}
				return 0;
			}
		}
		return current;
	}
}
GETWINDOWMONITOR_DEC{
	if(monitorAmount <= 1 || !(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, w), NULL))){
		return 0;
	}
	(*(xcb_get_geometry_reply_t *)reply).border_width *= 2;
	{
		const int x = (*(xcb_get_geometry_reply_t *)reply).x;
		const int width = (*(xcb_get_geometry_reply_t *)reply).width + (*(xcb_get_geometry_reply_t *)reply).border_width;
		const int y = (*(xcb_get_geometry_reply_t *)reply).y;
		const int height = (*(xcb_get_geometry_reply_t *)reply).height + (*(xcb_get_geometry_reply_t *)reply).border_width;
		free(reply);
		{
			int monitorX;
			int monitorY;
			int monitorWidth;
			int monitorHeight;
			unsigned int monitorToUse = 0;
			unsigned int pixels;
			unsigned int mostPixels = 0;
			unsigned int current = 0;
			loop:{
				monitorX = (*monitor).x;
				monitorY = (*monitor).y;
				monitorWidth = (*monitor).width;
				monitorHeight = (*monitor).height;
				if(monitorX > x + width || monitorX + monitorWidth <= x || monitorY > y + height || monitorY + monitorHeight <= y){
					goto loopControl;
				}
				if(monitorX + monitorWidth <= x + width){
					if(monitorX > x){
						pixels = monitorWidth;
					}else{
						pixels = monitorX + monitorWidth - x;
					}
				}else{
					if(monitorX > x){
						pixels = x + width - monitorX;
					}else{
						pixels = width;
					}
				}
				if(monitorY + monitorHeight <= y + height){
					if(monitorY > y){
						pixels *= monitorHeight;
					}else{
						pixels *= monitorY + monitorHeight - y;
					}
				}else{
					if(monitorY > y){
						pixels *= y + height - monitorY;
					}else{
						pixels *= height;
					}
				}
				if(pixels > mostPixels){
					mostPixels = pixels;
					monitorToUse = current;
				}
				loopControl:{
					if(++current < monitorAmount){
						++monitor;
						goto loop;
					}
				}
			}
			return monitorToUse;
		}
	}
}
FINDMONITOR_DEC{
	switch(adjacentMonitor){
		case NextAdjacentMonitor:{
			if(found + 1 >= wall){
				return NULL;
			}
			return (Monitor *)found + 1;
		}
		case PreviousAdjacentMonitor:{
			if(found <= start){
				return NULL;
			}
			return (Monitor *)found - 1;
		}
		case AboveAdjacentMonitor:{
			if(!(*found).y){
				return NULL;
			}
			goto findDirectionalMonitor;
		}
		case BelowAdjacentMonitor:{
			if((*found).y + (int)(*found).height >= (*screen).height_in_pixels){
				return NULL;
			}
			goto findDirectionalMonitor;
		}
		case LeftAdjacentMonitor:{
			if(!(*found).x){
				return NULL;
			}
			goto findDirectionalMonitor;
		}
		default:{
			if((*found).x + (int)(*found).width >= (*screen).width_in_pixels){
				return NULL;
			}
		}
	}
	findDirectionalMonitor:{
		const Monitor *current = start;
		const Monitor *newMonitor = NULL;
		unsigned int pixels;
		unsigned int mostPixels = 0;
		loop:{
			switch(adjacentMonitor){
				case AboveAdjacentMonitor:{
					pixels = getAdjacentSurfaceSize((*current).y, (*current).x, (int)(*current).height, (int)(*current).width, (*found).y, (*found).x, (int)(*found).width);
					break;
				}
				case BelowAdjacentMonitor:{
					pixels = getAdjacentSurfaceSize((*found).y, (*found).x, (int)(*found).height, (int)(*found).width, (*current).y, (*current).x, (int)(*current).width);
					break;
				}
				case LeftAdjacentMonitor:{
					pixels = getAdjacentSurfaceSize((*current).x, (*current).y, (int)(*current).width, (int)(*current).height, (*found).x, (*found).y, (int)(*found).height);
					break;
				}
				default:{
					pixels = getAdjacentSurfaceSize((*found).x, (*found).y, (int)(*found).width, (int)(*found).height, (*current).x, (*current).y, (int)(*current).height);
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
		}
		return (Monitor *)newMonitor;
	}
}
MOVEGRIDDINGCONTAINER_DEC{
	struct{
		WindowAttribute a0;
		WindowAttribute a1;
		WindowAttribute a2;
		WindowAttribute a3;
	} attribute;
	getGridSlotData((*m).width, (*m).height, (*c).gridX + (*c).gridWidth - 1, (*c).gridY + (*c).gridHeight - 1, gridWidth, gridHeight, (int *)&attribute.a0, (int *)&attribute.a1, &attribute.a2, &attribute.a3);
	attribute.a2 += attribute.a0;
	attribute.a3 += attribute.a1;
	getGridSlotData((*m).width, (*m).height, (*c).gridX, (*c).gridY, gridWidth, gridHeight, (int *)&attribute.a0, (int *)&attribute.a1, NULL, NULL);
	attribute.a2 -= attribute.a0;
	attribute.a3 -= attribute.a1;
	attribute.a0 += (*m).x;
	attribute.a1 += (*m).y;
	xcb_configure_window(connection, (*c).window, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
	attribute.a2 -= (*programData).borderX;
	attribute.a3 -= (*programData).borderY;
	xcb_configure_window(connection, (*c).subwindow, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
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
MOVEFLOATINGCONTAINER_DEC{
	struct{
		WindowAttribute a0;
		WindowAttribute a1;
		WindowAttribute a2;
		WindowAttribute a3;
	} attribute;
	if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, w), NULL))){
		return;
	}
	{
		unsigned int shadow = (*(xcb_get_geometry_reply_t *)reply).border_width;
		int x = (*(xcb_get_geometry_reply_t *)reply).x + shadow;
		int y = (*(xcb_get_geometry_reply_t *)reply).y + shadow;
		unsigned int width = (*(xcb_get_geometry_reply_t *)reply).width;
		unsigned int height = (*(xcb_get_geometry_reply_t *)reply).height;
		free(reply);
		{
			unsigned int sourceReducedWidth;
			unsigned int sourceReducedHeight;
			unsigned int destinationReducedWidth;
			unsigned int destinationReducedHeight;
			if(hasOption(FloatingFollowGrid)){
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
		if(width < minimumWidth){
			width = minimumWidth;
		}
		if(height < minimumHeight){
			height = minimumHeight;
		}
		attribute.a0 = x;
		attribute.a1 = y;
		attribute.a2 = width;
		attribute.a3 = height;
	}
	xcb_configure_window(connection, w, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT, &attribute);
	attribute.a2 -= (*programData).borderX;
	attribute.a3 -= (*programData).borderY;
	xcb_configure_window(connection, s, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
	return;
}
UNMAXIMIZECONTAINER_DEC{
	const xcb_window_t w = (*c).window;
	unsigned int currentMonitor;
	if(!findWindow((*c).window, &(*maximizedContainer).window, sizeof(MaximizedContainer), monitorAmount, &currentMonitor)){
		return;
	}
	maximizedContainer += currentMonitor;
	{
		const xcb_window_t s = (*c).subwindow;
		if((*maximizedContainer).shouldChangeProperty){









			unsigned int length;
			if(!(reply = xcb_get_property_reply(connection, xcb_get_property_unchecked(connection, false, s, (*programData)._NET_WM_STATE, XCB_ATOM_ATOM, 0, 0), NULL))){
				goto replyEmergencyExit;
			}
			length = (*(xcb_get_property_reply_t *)reply).value_len;
			if(!length){
				goto replyEmergencyExit;
			}
			{
				xcb_atom_t *property = xcb_get_property_value((xcb_get_property_reply_t *)reply);
				unsigned int currentProperty = 0;
				free(reply);
				if(!property){
					goto replyEmergencyExit;
				}
				reply = (xcb_generic_reply_t *)property;
				findStateFullscreen:{
					if(*property == (*programData)._NET_WM_STATE_FULLSCREEN){
						*property = *((xcb_atom_t *)reply + --length);



						/**((xcb_atom_t *)reply + length) = XCB_NONE;*/



					}else{
						if(++currentProperty < length){
							++property;
							goto findStateFullscreen;
						}
						free(reply);
						goto replyEmergencyExit;
					}
				}
			}
			if(!length){
				++length;
				*(xcb_atom_t *)reply = XCB_NONE;
			}
			changeProperties(w, s, XCB_PROP_MODE_REPLACE, (*programData)._NET_WM_STATE, XCB_ATOM_ATOM, 32, length, &reply);
			replyEmergencyExit:{}









			if(c == focused){
				length = 6;
			}else{
				length = 0;
			}
			xcb_change_window_attributes(connection, w, XCB_CW_BACK_PIXEL, (*maximizedContainer).oldBackgroundColor + length);
		}
		xcb_clear_area(connection, false, w, 0, 0, 0, 0);
		{
			struct{
				WindowAttribute a0;
				WindowAttribute a1;
				WindowAttribute a2;
				WindowAttribute a3;
				WindowAttribute a4;
				WindowAttribute a5;
			} attribute;
			attribute.a0 = (*maximizedContainer).oldX;
			attribute.a1 = (*maximizedContainer).oldY;
			attribute.a2 = (*maximizedContainer).oldWidth;
			attribute.a3 = (*maximizedContainer).oldHeight;
			attribute.a4 = (*maximizedContainer).oldBorder;
			attribute.a5 = XCB_STACK_MODE_ABOVE;
			xcb_configure_window(connection, w, XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT_BORDER_STACK, &attribute);
			attribute.a2 -= (*programData).borderX;
			attribute.a3 -= (*programData).borderY;
			xcb_configure_window(connection, s, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
		}
		(*maximizedContainer).window = XCB_NONE;
		(*maximizedContainer).subwindow = XCB_NONE;
		removeContainerOption(*c, Maximized);
	}
	return;
}
DRAWGRID_DEC{
	const WindowAttribute color = 0x00000000;
	xcb_window_t window;
	unsigned int current = 0;
	unsigned int monitorWidth;
	unsigned int monitorHeight;
	unsigned int currentX;
	unsigned int currentY;
	int x;
	int y;
	unsigned int width;
	unsigned int height;
	setBackground:{
		window = *(grid + current);
		xcb_change_window_attributes(connection, window, XCB_CW_BACK_PIXEL, &(*programData).colorGridSubwindowBackground);
		xcb_clear_area(connection, false, window, 0, 0, 0, 0);
		xcb_change_window_attributes(connection, window, XCB_CW_BACK_PIXEL, &(*programData).colorGridSubwindowBorder);
		if(++current < monitorAmount){
			goto setBackground;
		}
	}
	currentY = 0;
	current = 0;
	drawGridWindows:{
		monitorWidth = (*monitor).width;
		monitorHeight = (*monitor).height;
		currentX = 0;
		window = *(grid + current);
		drawHorizontalLines:{
			getGridSlotData(monitorWidth, monitorHeight, currentX, currentY, gridWidth, gridHeight, &x, &y, &width, &height);
			xcb_clear_area(connection, false, window, x, y, monitorWidth, 1);
			xcb_clear_area(connection, false, window, x, y + height - 1, monitorWidth, 1);
			if(++currentY < gridHeight){
				goto drawHorizontalLines;
			}
		}
		currentY = 0;
		drawVerticalLines:{
			getGridSlotData(monitorWidth, monitorHeight, currentX, currentY, gridWidth, gridHeight, &x, &y, &width, &height);
			xcb_clear_area(connection, false, window, x, y, 1, monitorHeight);
			xcb_clear_area(connection, false, window, x + width - 1, y, 1, monitorHeight);
			if(++currentX < gridWidth){
				goto drawVerticalLines;
			}
		}
		xcb_change_window_attributes(connection, window, XCB_CW_BACK_PIXEL, &color);
		if(++current < monitorAmount){
			++monitor;
			goto drawGridWindows;
		}
	}
	return;
}
MAXIMIZECONTAINER_DEC{
	const xcb_window_t w = (*c).window;
	const xcb_window_t s = (*c).subwindow;
	if(!(reply = xcb_get_geometry_reply(connection, xcb_get_geometry_unchecked(connection, w), NULL))){
		return;
	}
	switch((*programData).managementMode){
		case FloatingManagementMode:{
			if(hasContainerOption(*c, InGrid)){
				(*mc).oldBackgroundColor = &(*programData).colorContainerBackgroundInGrid;
				break;
			}
			(*mc).oldBackgroundColor = &(*programData).colorContainerBackgroundFloating;
			break;
		}
		case GriddingManagementMode:{
			(*mc).oldBackgroundColor = &(*programData).colorContainerBackgroundGridding;
			break;
		}
		default:{
			(*mc).oldBackgroundColor = &(*programData).colorContainerBackgroundTiling;
			break;
		}
	}
	(*mc).window = w;
	(*mc).subwindow = s;
	(*mc).oldX = (*(xcb_get_geometry_reply_t *)reply).x;
	(*mc).oldY = (*(xcb_get_geometry_reply_t *)reply).y;
	(*mc).oldWidth = (*(xcb_get_geometry_reply_t *)reply).width;
	(*mc).oldHeight = (*(xcb_get_geometry_reply_t *)reply).height;
	(*mc).oldBorder = (*(xcb_get_geometry_reply_t *)reply).border_width;
	addContainerOption(*c, Maximized);
	free(reply);
	{
		WindowAttribute color;
		if(focused && (*focused).window == w){
			if(isCommand(Fullscreen)){
				color = (*programData).colorFocusedContainerBackgroundFullscreen;
				goto fullscreenCommand;
			}else{
				color = (*programData).colorFocusedContainerBackgroundBigscreen;
				goto bigscreenCommand;
			}
		}else{
			if(isCommand(Fullscreen)){
				color = (*programData).colorContainerBackgroundFullscreen;
				fullscreenCommand:{



					changeProperties(w, s, XCB_PROP_MODE_APPEND, (*programData)._NET_WM_STATE, XCB_ATOM_ATOM, 32, 1, &(*programData)._NET_WM_STATE_FULLSCREEN);



					(*mc).shouldChangeProperty = 1;
				}
			}else{
				color = (*programData).colorContainerBackgroundBigscreen;
				bigscreenCommand:{
					(*mc).shouldChangeProperty = 0;
				}
			}
		}
		xcb_change_window_attributes(connection, w, XCB_CW_BACK_PIXEL, &color);
	}
	xcb_clear_area(connection, false, w, 0, 0, 0, 0);
	{
		AttributeMasks masks = XCB_CONFIG_WINDOW_X_Y_WIDTH_HEIGHT_STACK;
		struct{
			WindowAttribute a0;
			WindowAttribute a1;
			WindowAttribute a2;
			WindowAttribute a3;
			WindowAttribute a4;
			WindowAttribute a5;
		} attribute;
		if(hasContainerOption(*c, InGrid)){
			attribute.a4 = XCB_STACK_MODE_ABOVE;
		}else{
			attribute.a4 = 0;
			attribute.a5 = XCB_STACK_MODE_ABOVE;
			masks |= XCB_CONFIG_WINDOW_BORDER_WIDTH;
		}
		attribute.a0 = (*monitor).x;
		attribute.a1 = (*monitor).y;
		attribute.a2 = (*monitor).width;
		attribute.a3 = (*monitor).height;
		xcb_configure_window(connection, w, masks, &attribute);
		attribute.a2 -= (*programData).borderX;
		attribute.a3 -= (*programData).borderY;
		xcb_configure_window(connection, s, XCB_CONFIG_WINDOW_WIDTH_HEIGHT, &attribute.a2);
	}
	return;
}
PRINTUNEXPECTEDEVENT_DEC{
	fprintf(errorStream, "%s: unexpected event (%u), ignored\n", programName, event);
	return;
}



























static void signalHandler(const int sig){
	UnusedVariable(sig);
	return;
}
COMMANDSERVER_DEC{
	/*xcb_generic_error_t *error;*/
	xcb_client_message_event_t e;
	sigset_t signalSet;
	unsigned int length;
	char *buffer = NULL;
	/*unsigned int number;*/
	xcb_generic_reply_t *reply;
	unsigned int current;
	e.response_type = XCB_CLIENT_MESSAGE;
	e.type = (*programData).COMMAND;
	sigemptyset(&signalSet);
	sigaddset(&signalSet, SIGUSR1);
	signal(SIGUSR1, signalHandler);
	waitForCommand:{
		sigwaitinfo(&signalSet, NULL);
		if((reply = xcb_get_input_focus_reply(connection, xcb_get_input_focus(connection), NULL))){
			if(!findWindow((*(xcb_get_input_focus_reply_t *)reply).focus, &(*(Container *)containerStart).window, sizeof(Container), containerAmount, &current)){
				e.window = XCB_NONE;
			}else{
				e.window = (*((Container *)containerStart + current)).window;
			}
			free(reply);
		}
		length = 3;
		switch(length){
			case 3:{
				/**/
				break;
			}
			case 4:{
				if(compareStrings("Exit", buffer)){
					e.type = ExitCommand;
					xcb_send_event(connection, false, receiver, XCB_EVENT_MASK_NO_EVENT, (char *)&e);
					goto waitForCommand;
				}
				/*
				Move
				Kill
				*/
				break;
			}
			case 5:{
				/*
				Close
				*/
				break;
			}
			case 6:{
				/*
				Attach
				Resize
				Detach
				*/
				break;
			}
			case 7:{
				/*
				Execute
				Cascade
				Restart
				MoveTop
				*/
				break;
			}
			case 8:{
				/*
				ShowGrid
				HideGrid
				MoveLeft
				MoveFull
				ExtendUp
				ShrinkUp
				*/
				break;
			}
			case 9:{
				/*
				MoveRight
				AddToGrid
				Bigscreen
				*/
				break;
			}
			case 10:{
				/*
				TilingMode
				ToggleGaps
				MoveResize
				MoveBottom
				MoveCenter
				MoveUpGrid
				ExtendDown
				ExtendLeft
				ShrinkDown
				ShrinkLeft
				Fullscreen
				*/
				break;
			}
			case 11:{
				/*
				ShrinkGridX
				ShrinkGridY
				MoveTopLeft
				ExtendRight
				ShrinkRight
				*/
				break;
			}
			case 12:{
				/*
				FloatingMode
				GriddingMode
				EnlargeGridX
				EnlargeGridY
				MoveTopRight
				MoveDownGrid
				MoveLeftGrid
				ExtendUpLeft
				ShrinkUpLeft
				*/
				break;
			}
			case 13:{
				/*
				MoveRightGrid
				ExtendUpRight
				ShrinkUpRight
				*/
				break;
			}
			case 14:{
				/*
				ShrinkGridBoth
				MoveBottomLeft
				RemoveFromGrid
				ExtendDownLeft
				ShrinkDownLeft
				*/
				break;
			}
			case 15:{
				/*
				EnlargeGridBoth
				SwapNextMonitor
				SwapLeftMonitor
				MoveBottomRight
				MoveNextMonitor
				MoveLeftMonitor
				ExtendDownRight
				ShrinkDownRight
				*/
				break;
			}
			case 16:{
				/*
				CancelMoveResize
				ShrinkGridEither
				SwapAboveMonitor
				SwapBelowMonitor
				SwapRightMonitor
				MoveAboveMonitor
				MoveBelowMonitor
				MoveRightMonitor
				*/
				break;
			}
			case 17:{
				/*
				EnlargeGridEither
				*/
				break;
			}
			case 19:{
				/*
				SwapPreviousMonitor
				RevolveMonitorsNext
				RevolveMonitorsLeft
				MovePreviousMonitor
				ToggleAddRemoveGrid
				*/
				break;
			}
			case 20:{
				/*
				ToggleGridVisibility
				RevolveMonitorsAbove
				RevolveMonitorsBelow
				RevolveMonitorsRight
				*/
				break;
			}
			case 23:{
				if(compareStrings("RevolveMonitorsPrevious", buffer)){
					/**/



					goto waitForCommand;
				}
				break;
			}
			default:{
				break;
			}
		}
		printError("invalid command sent to server");
		goto waitForCommand;
	}
	return NULL;
}
