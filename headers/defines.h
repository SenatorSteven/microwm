/* defines.h

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

#ifndef DEFINES_H
#define DEFINES_H

/* # /user-defined constants start # # # */
#define Tab /*---------------------------*/ "    "
#define DefaultCharactersCount /*--------*/ 255
#define DefaultLinesCount /*-------------*/ 150
/* # /user-defined constants end # # # # */

#define ContinueMode /*------------------*/ 0
#define RestartMode /*-------------------*/ 1
#define ExitMode /*----------------------*/ 2

#define NoOptions /*---------------------*/ 0
#define FloatingFollowGrid /*------------*/ (1 << 0)
#define GridPrioritizeYOption /*---------*/ (1 << 1)
#define GridAllowBoundaryBreakXOption /*-*/ (1 << 2)
#define GridAllowBoundaryBreakYOption /*-*/ (1 << 3)
#define Tiling-----------------Option /*-*/ (1 << 4)

#define FloatingManagementMode /*--------*/ 1
#define GridManagementMode /*------------*/ 2
#define TilingManagementMode /*----------*/ 3

#define NoCommand /*---------------------*/ 0
#define SystemCommand /*-----------------*/ 1
#define FloatingModeCommand /*-----------*/ 2
#define GridModeCommand /*---------------*/ 3
#define TilingModeCommand /*-------------*/ 4
#define ShowGridCommand /*---------------*/ 5
#define EnlargeGridCommand /*------------*/ 6
#define ShrinkGridCommand /*-------------*/ 7
#define RecascadeCommand /*--------------*/ 8
#define RestartCommand /*----------------*/ 9
#define ExitCommand /*-------------------*/ 10
#define MoveCommand /*-------------------*/ 11
#define MoveTopCommand /*----------------*/ 12
#define MoveBottomCommand /*-------------*/ 13
#define MoveLeftCommand /*---------------*/ 14
#define MoveRightCommand /*--------------*/ 15
#define MoveCenterCommand /*-------------*/ 16
#define MoveTopLeftCommand /*------------*/ 17
#define MoveTopRightCommand /*-----------*/ 18
#define MoveBottomLeftCommand /*---------*/ 19
#define MoveBottomRightCommand /*--------*/ 20
#define MoveNextMonitorCommand /*--------*/ 21
#define MovePreviousMonitorCommand /*----*/ 22
#define AddWindowToGridCommand /*--------*/ 23
#define RemoveWindowFromGridCommand /*---*/ 24
#define ToggleWindowGridCommand /*-------*/ 25
#define MoveFirstGridSlotCommand /*------*/ 26
#define MoveLastGridSlotCommand /*-------*/ 27
#define MoveAboveGridSlotCommand /*------*/ 28
#define MoveBelowGridSlotCommand /*------*/ 29
#define MoveNextGridSlotCommand /*-------*/ 30
#define MovePreviousGridSlotCommand /*---*/ 31
#define ExtendWindowUpCommand /*---------*/ 32
#define ExtendWindowDownCommand /*-------*/ 33
#define ExtendWindowLeftCommand /*-------*/ 34
#define ExtendWindowRightCommand /*------*/ 35
#define ExtendWindowUpLeftCommand /*-----*/ 36
#define ExtendWindowUpRightCommand /*----*/ 37
#define ExtendWindowDownLeftCommand /*---*/ 38
#define ExtendWindowDownRightCommand /*--*/ 39
#define ShrinkWindowUpCommand /*---------*/ 40
#define ShrinkWindowDownCommand /*-------*/ 41
#define ShrinkWindowLeftCommand /*-------*/ 42
#define ShrinkWindowRightCommand /*------*/ 43
#define ShrinkWindowUpLeftCommand /*-----*/ 44
#define ShrinkWindowUpRightCommand /*----*/ 45
#define ShrinkWindowDownLeftCommand /*---*/ 46
#define ShrinkWindowDownRightCommand /*--*/ 47
#define FullscreenCommand /*-------------*/ 48
#define BigscreenCommand /*--------------*/ 49
#define CloseCommand /*------------------*/ 50
#define KillCommand /*-------------------*/ 51

#define FocusCommand /*------------------*/ 52

#define RootCommandCeiling /*------------*/ ExitCommand

typedef uint8_t bool;
typedef uint8_t Mode;
typedef uint32_t ARGB;
typedef uint8_t ManagementMode;
typedef uint8_t Command;
typedef uint8_t Options;

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

#endif
