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
#define Tab /*----------------------*/ "    "
#define DefaultCharactersCount /*---*/ 255
#define DefaultLinesCount /*--------*/ 100
#define StandardErrorStream /*------*/ stderr
/* # /user-defined constants end # # # # */

#define DEBUG /*--------------------*/ true

#define false /*--------------------*/ 0
#define true /*---------------------*/ 1

#define ContinueMode /*-------------*/ 0
#define ExitMode /*-----------------*/ 1

#define UnusedVariable(v) /*--------*/ (void)(v)

#define xcb_intern_atom_reply /*----*/ (void *)xcb_intern_atom_reply

#define PRINTERROR_DEC /*-----------*/ void printError(const char *const string)
#define PRINTXCBERROR_DEC /*--------*/ void printXCBError(void)
#define PRINTCONNECTIONERROR_DEC /*-*/ bool printConnectionError(void)
#define COMPARESTRINGS_DEC /*-------*/ bool compareStrings(const char *buffer0, const char *buffer1)

#define setMode(m) /*---------------*/ (mode = m##Mode)
#define isMode(m) /*----------------*/ (mode == m##Mode)

typedef uint8_t bool;
typedef uint8_t Mode;
typedef uint32_t ARGB;
typedef uint32_t WindowAttributes;

typedef struct{
	unsigned int borderX;
	unsigned int borderY;
	xcb_atom_t COMMAND;
	xcb_atom_t WM_PROTOCOLS;
	xcb_atom_t WM_DELETE_WINDOW;
	xcb_atom_t _NET_WM_STATE;
	xcb_atom_t _NET_WM_STATE_FULLSCREEN;
	ARGB colorContainerShadow;
	ARGB colorGridSubwindowBorder;
	ARGB colorGridSubwindowBackground;
	ARGB colorSeparatorBorder;
	ARGB colorSeparatorBackground;
	ARGB colorContainerBackgroundFloating;
	ARGB colorContainerBackgroundGridding;
	ARGB colorContainerBackgroundTiling;
	ARGB colorContainerBackgroundInGrid;
	ARGB colorContainerBackgroundFullscreen;
	ARGB colorContainerBackgroundBigscreen;
	ARGB colorFocusedContainerBackgroundFloating;
	ARGB colorFocusedContainerBackgroundGridding;
	ARGB colorFocusedContainerBackgroundTiling;
	ARGB colorFocusedContainerBackgroundInGrid;
	ARGB colorFocusedContainerBackgroundFullscreen;
	ARGB colorFocusedContainerBackgroundBigscreen;
	ARGB colorMotionContainerGlassBorder;
	ARGB colorMotionContainerGlassBackground;
	ARGB colorMotionContainerMinimalMoveBorder;
	ARGB colorMotionContainerMinimalMoveBackground;
	ARGB colorMotionContainerMinimalResizeBorder;
	ARGB colorMotionContainerMinimalResizeBackground;
	ARGB colorMotionContainerSnappingBackground;
	ARGB colorMotionContainerSnappingBorder;
	uint8_t managementMode;
} ProgramData;

PRINTERROR_DEC;
PRINTXCBERROR_DEC;
PRINTCONNECTIONERROR_DEC;
COMPARESTRINGS_DEC;

#endif
