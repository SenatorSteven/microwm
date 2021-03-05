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

#include <X11/Xatom.h>

/* # /user-defined constants start # # # */
#define Tab /*--------------------*/ "    "
#define DefaultCharactersCount /*-*/ 255
#define DefaultLinesCount /*------*/ 100
#define StandardErrorStream /*----*/ stderr
/* # /user-defined constants end # # # # */

#define ContinueMode /*-----------*/ 0
#define ExitMode /*---------------*/ 1

#define NoManagementMode /*-------*/ 0
#define FloatingManagementMode /*-*/ 1
#define GriddingManagementMode /*-*/ 2
#define TilingManagementMode /*---*/ 3

#define PRINTERROR_DEC /*---------*/ void printError(const char *const string)

#define atom(s) /*----------------*/ XInternAtom(display, s, False)

#define mode(m) /*----------------*/ (mode == m##Mode)

typedef uint8_t bool;
typedef uint8_t Mode;
typedef uint8_t ManagementMode;
typedef uint32_t ARGB;

typedef struct{
	FILE *stream;
	char *path;
	bool mustOpenStream;
} ErrorData;

typedef struct{
	ARGB floating;
	ARGB gridding;
	ARGB tiling;
	ARGB inGrid;
	ARGB fullscreen;
	ARGB bigscreen;
} ContainerBackground;

typedef struct{
	unsigned int up;
	unsigned int down;
	unsigned int left;
	unsigned int right;
	unsigned int x;
	unsigned int y;
} DirectionAxis;

typedef struct{
	struct{
		Atom PROTOCOLS;
		Atom DELETE_WINDOW;
	} WM;
	struct{
		struct{
			struct{
				Atom this;
				Atom FULLSCREEN;
			} STATE;
		} WM;
	} _NET;
	struct{
		ARGB containerShadow;
		ARGB gridSubwindowBorder;
		ARGB gridSubwindowBackground;
		ARGB separatorBorder;
		ARGB separatorBackground;
		ContainerBackground containerBackground;
		ContainerBackground focusedContainerBackground;
		struct{
			ARGB glassBorder;
			ARGB glassBackground;
			ARGB minimalMoveBorder;
			ARGB minimalMoveBackground;
			ARGB minimalResizeBorder;
			ARGB minimalResizeBackground;
			ARGB snappingBackground;
			ARGB snappingBorder;
		} motionContainer;
	} color;
	unsigned int displayWidth;
	unsigned int displayHeight;
	DirectionAxis border;
} ProgramData;

PRINTERROR_DEC;

#endif
