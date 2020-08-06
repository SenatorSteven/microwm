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
#define Tab /*--------------------------*/ "    "
#define DefaultCharactersCount /*-------*/ 255
#define DefaultLinesCount /*------------*/ 150
/* # /user-defined constants end # # # # */

#define ContinueMode /*-----------------*/ 0
#define RestartMode /*------------------*/ 1
#define ExitMode /*---------------------*/ 2

#define NoCommand /*--------------------*/ 0
#define ShowGridCommand /*--------------*/ 1
#define EnlargeGridCommand /*-----------*/ 2
#define ShrinkGridCommand /*------------*/ 3
#define RecascadeCommand /*-------------*/ 4
#define RestartCommand /*---------------*/ 5
#define ExitCommand /*------------------*/ 6
#define MoveCommand /*------------------*/ 7
#define MoveTopCommand /*---------------*/ 8
#define MoveBottomCommand /*------------*/ 9
#define MoveLeftCommand /*--------------*/ 10
#define MoveRightCommand /*-------------*/ 11
#define MoveCenterCommand /*------------*/ 12
#define MoveTopLeftCommand /*-----------*/ 13
#define MoveTopRightCommand /*----------*/ 14
#define MoveBottomLeftCommand /*--------*/ 15
#define MoveBottomRightCommand /*-------*/ 16
#define MoveNextMonitorCommand /*-------*/ 17
#define MovePreviousMonitorCommand /*---*/ 18
#define AddWindowToGrid /*--------------*/ 19
#define RemoveWindowFromGrid /*---------*/ 20
#define MoveFirstGridSlotCommand /*-----*/ 21
#define MoveLastGridSlotCommand /*------*/ 22
#define ExtendWindowUpCommand /*--------*/ 23
#define ExtendWindowDownCommand /*------*/ 24
#define ExtendWindowLeftCommand /*------*/ 25
#define ExtendWindowRightCommand /*-----*/ 26
#define ExtendWindowUpLeftCommand /*----*/ 27
#define ExtendWindowUpRightCommand /*---*/ 28
#define ExtendWindowDownLeftCommand /*--*/ 29
#define ExtendWindowDownRightCommand /*-*/ 30
#define ShrinkWindowUpCommand /*--------*/ 31
#define ShrinkWindowDownCommand /*------*/ 32
#define ShrinkWindowLeftCommand /*------*/ 33
#define ShrinkWindowRightCommand /*-----*/ 34
#define ShrinkWindowUpLeftCommand /*----*/ 35
#define ShrinkWindowUpRightCommand /*---*/ 36
#define ShrinkWindowDownLeftCommand /*--*/ 37
#define ShrinkWindowDownRightCommand /*-*/ 38
#define FullscreenCommand /*------------*/ 39
#define BigscreenCommand /*-------------*/ 40
#define CloseCommand /*-----------------*/ 41

#define RootCommandCeiling /*-----------*/ ExitCommand

typedef uint8_t bool;
typedef uint8_t Mode;
typedef uint32_t ARGB;
typedef uint8_t Command;

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
