/* globals.c

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
#include <xcb/xcb.h>
#include "headers/defines.h"

#define _PRINTXCBERROR_DEC /*--------*/ static void _printXCBError(void)
#define _PRINTCONNECTIONERROR_DEC /*-*/ static void _printConnectionError(void)

const char *programName;
const char *configPath;
const char *connectionName;
const xcb_screen_t *screen;
const char *errorPath;
bool mustOpenErrorStream;
FILE *errorStream;
xcb_connection_t *connection;
xcb_generic_error_t *genericError;
xcb_generic_reply_t *reply;
Mode mode;
ProgramData *programData;

_PRINTXCBERROR_DEC;
_PRINTCONNECTIONERROR_DEC;

COMPARESTRINGS_DEC{
	char b0 = *buffer0;
	char b1 = *buffer1;
	loop:{
		if(b0 >= 'A' && b0 <= 'Z'){
			if(b0 != b1 && b0 != b1 - 32){
				return false;
			}
		}else if(b0 >= 'a' && b0 <= 'z'){
			if(b0 != b1 && b0 != b1 + 32){
				return false;
			}
		}else if(b0 != b1){
			return false;
		}
		b0 = *(++buffer0);
		b1 = *(++buffer1);
		if(!b0 && !b1){
			return true;
		}
		goto loop;
	}
}
PRINTERROR_DEC{
	if(!mustOpenErrorStream || (errorStream = fopen(errorPath, "a"))){
		fprintf(errorStream, "%s: %s\n", programName, string);
		if(mustOpenErrorStream){
			fclose(errorStream);
		}
	}
	return;
}
PRINTXCBERROR_DEC{
	if(!mustOpenErrorStream || (errorStream = fopen(errorPath, "a"))){
		_printXCBError();
		if(mustOpenErrorStream){
			fclose(errorStream);
		}
	}
	return;
}
_PRINTXCBERROR_DEC{
	const char *type;
	const char *operation;
	switch((*genericError).error_code){
		case XCB_REQUEST: /*--------*/ type = "request"; /*----------*/ break;
		case XCB_VALUE: /*----------*/ type = "value"; /*------------*/ break;
		case XCB_WINDOW: /*---------*/ type = "window"; /*-----------*/ break;
		case XCB_PIXMAP: /*---------*/ type = "pixmap"; /*-----------*/ break;
		case XCB_ATOM: /*-----------*/ type = "atom"; /*-------------*/ break;
		case XCB_CURSOR: /*---------*/ type = "cursor"; /*-----------*/ break;
		case XCB_FONT: /*-----------*/ type = "font"; /*-------------*/ break;
		case XCB_MATCH: /*----------*/ type = "match"; /*------------*/ break;
		case XCB_DRAWABLE: /*-------*/ type = "drawable"; /*---------*/ break;
		case XCB_ACCESS: /*---------*/ type = "access"; /*-----------*/ break;
		case XCB_ALLOC: /*----------*/ type = "allocation"; /*-------*/ break;
		case XCB_COLORMAP: /*-------*/ type = "colormap"; /*---------*/ break;
		case XCB_G_CONTEXT: /*------*/ type = "graphics context"; /*-*/ break;
		case XCB_ID_CHOICE: /*------*/ type = "id choice"; /*--------*/ break;
		case XCB_NAME: /*-----------*/ type = "name"; /*-------------*/ break;
		case XCB_LENGTH: /*---------*/ type = "length"; /*-----------*/ break;
		case XCB_IMPLEMENTATION: /*-*/ type = "implementation"; /*---*/ break;
		default: /*-----------------*/ type = "unrecognized"; /*-----*/ break;
	}
	switch((*genericError).major_code){
		case XCB_CREATE_WINDOW: /*--------------*/ operation = "create window"; /*--------------*/ break;
		case XCB_CHANGE_WINDOW_ATTRIBUTES: /*---*/ operation = "change window attributes"; /*---*/ break;
		case XCB_GET_WINDOW_ATTRIBUTES: /*------*/ operation = "get window attributes"; /*------*/ break;
		case XCB_DESTROY_WINDOW: /*-------------*/ operation = "destroy window"; /*-------------*/ break;
		case XCB_DESTROY_SUBWINDOWS: /*---------*/ operation = "destroy subwindows"; /*---------*/ break;
		case XCB_CHANGE_SAVE_SET: /*------------*/ operation = "change save set"; /*------------*/ break;
		case XCB_REPARENT_WINDOW: /*------------*/ operation = "reparent window"; /*------------*/ break;
		case XCB_MAP_WINDOW: /*-----------------*/ operation = "map window"; /*-----------------*/ break;
		case XCB_MAP_SUBWINDOWS: /*-------------*/ operation = "map subwindows"; /*-------------*/ break;
		case XCB_UNMAP_WINDOW: /*---------------*/ operation = "unmap window"; /*---------------*/ break;
		case XCB_UNMAP_SUBWINDOWS: /*-----------*/ operation = "unmap subwindows"; /*-----------*/ break;
		case XCB_CONFIGURE_WINDOW: /*-----------*/ operation = "configure window"; /*-----------*/ break;
		case XCB_CIRCULATE_WINDOW: /*-----------*/ operation = "circulate window"; /*-----------*/ break;
		case XCB_GET_GEOMETRY: /*---------------*/ operation = "get geometry"; /*---------------*/ break;
		case XCB_QUERY_TREE: /*-----------------*/ operation = "query tree"; /*-----------------*/ break;
		case XCB_INTERN_ATOM: /*----------------*/ operation = "intern atom"; /*----------------*/ break;
		case XCB_GET_ATOM_NAME: /*--------------*/ operation = "get atom name"; /*--------------*/ break;
		case XCB_CHANGE_PROPERTY: /*------------*/ operation = "change property"; /*------------*/ break;
		case XCB_DELETE_PROPERTY: /*------------*/ operation = "delete property"; /*------------*/ break;
		case XCB_GET_PROPERTY: /*---------------*/ operation = "get property"; /*---------------*/ break;
		case XCB_LIST_PROPERTIES: /*------------*/ operation = "list properties"; /*------------*/ break;
		case XCB_SET_SELECTION_OWNER: /*--------*/ operation = "set selection owner"; /*--------*/ break;
		case XCB_GET_SELECTION_OWNER: /*--------*/ operation = "get selection owner"; /*--------*/ break;
		case XCB_CONVERT_SELECTION: /*----------*/ operation = "convert selection"; /*----------*/ break;
		case XCB_SEND_EVENT: /*-----------------*/ operation = "send event"; /*-----------------*/ break;
		case XCB_GRAB_POINTER: /*---------------*/ operation = "grab pointer"; /*---------------*/ break;
		case XCB_UNGRAB_POINTER: /*-------------*/ operation = "ungrab pointer"; /*-------------*/ break;
		case XCB_GRAB_BUTTON: /*----------------*/ operation = "grab button"; /*----------------*/ break;
		case XCB_UNGRAB_BUTTON: /*--------------*/ operation = "ungrab button"; /*--------------*/ break;
		case XCB_CHANGE_ACTIVE_POINTER_GRAB: /*-*/ operation = "change active pointer grab"; /*-*/ break;
		case XCB_GRAB_KEYBOARD: /*--------------*/ operation = "grab keyboard"; /*--------------*/ break;
		case XCB_UNGRAB_KEYBOARD: /*------------*/ operation = "ungrab keyboard"; /*------------*/ break;
		case XCB_GRAB_KEY: /*-------------------*/ operation = "grab key"; /*-------------------*/ break;
		case XCB_UNGRAB_KEY: /*-----------------*/ operation = "ungrab key"; /*-----------------*/ break;
		case XCB_ALLOW_EVENTS: /*---------------*/ operation = "allow events"; /*---------------*/ break;
		case XCB_GRAB_SERVER: /*----------------*/ operation = "grab server"; /*----------------*/ break;
		case XCB_UNGRAB_SERVER: /*--------------*/ operation = "ungrab server"; /*--------------*/ break;
		case XCB_QUERY_POINTER: /*--------------*/ operation = "query pointer"; /*--------------*/ break;
		case XCB_GET_MOTION_EVENTS: /*----------*/ operation = "get motion events"; /*----------*/ break;
		case XCB_TRANSLATE_COORDINATES: /*------*/ operation = "translate coordinates"; /*------*/ break;
		case XCB_WARP_POINTER: /*---------------*/ operation = "warp pointer"; /*---------------*/ break;
		case XCB_SET_INPUT_FOCUS: /*------------*/ operation = "set input focus"; /*------------*/ break;
		case XCB_GET_INPUT_FOCUS: /*------------*/ operation = "get input focus"; /*------------*/ break;
		case XCB_QUERY_KEYMAP: /*---------------*/ operation = "query keymap"; /*---------------*/ break;
		case XCB_OPEN_FONT: /*------------------*/ operation = "open font"; /*------------------*/ break;
		case XCB_CLOSE_FONT: /*-----------------*/ operation = "close font"; /*-----------------*/ break;
		case XCB_QUERY_FONT: /*-----------------*/ operation = "query font"; /*-----------------*/ break;
		case XCB_QUERY_TEXT_EXTENTS: /*---------*/ operation = "query text extents"; /*---------*/ break;
		case XCB_LIST_FONTS: /*-----------------*/ operation = "list fonts"; /*-----------------*/ break;
		case XCB_LIST_FONTS_WITH_INFO: /*-------*/ operation = "list fonts with info"; /*-------*/ break;
		case XCB_SET_FONT_PATH: /*--------------*/ operation = "set font path"; /*--------------*/ break;
		case XCB_GET_FONT_PATH: /*--------------*/ operation = "get font path"; /*--------------*/ break;
		case XCB_CREATE_PIXMAP: /*--------------*/ operation = "create pixmap"; /*--------------*/ break;
		case XCB_FREE_PIXMAP: /*----------------*/ operation = "free pixmap"; /*----------------*/ break;
		case XCB_CREATE_GC: /*------------------*/ operation = "create graphics context"; /*----*/ break;
		case XCB_CHANGE_GC: /*------------------*/ operation = "change graphics context"; /*----*/ break;
		case XCB_COPY_GC: /*--------------------*/ operation = "copy graphics context"; /*------*/ break;
		case XCB_SET_DASHES: /*-----------------*/ operation = "set dashes"; /*-----------------*/ break;
		case XCB_SET_CLIP_RECTANGLES: /*--------*/ operation = "set clip rectangles"; /*--------*/ break;
		case XCB_FREE_GC: /*--------------------*/ operation = "free graphics context"; /*------*/ break;
		case XCB_CLEAR_AREA: /*-----------------*/ operation = "clear area"; /*-----------------*/ break;
		case XCB_COPY_AREA: /*------------------*/ operation = "copy area"; /*------------------*/ break;
		case XCB_COPY_PLANE: /*-----------------*/ operation = "copy plane"; /*-----------------*/ break;
		case XCB_POLY_POINT: /*-----------------*/ operation = "poly point"; /*-----------------*/ break;
		case XCB_POLY_LINE: /*------------------*/ operation = "poly line"; /*------------------*/ break;
		case XCB_POLY_SEGMENT: /*---------------*/ operation = "poly segment"; /*---------------*/ break;
		case XCB_POLY_RECTANGLE: /*-------------*/ operation = "poly rectangle"; /*-------------*/ break;
		case XCB_POLY_ARC: /*-------------------*/ operation = "poly arc"; /*-------------------*/ break;
		case XCB_FILL_POLY: /*------------------*/ operation = "fill poly"; /*------------------*/ break;
		case XCB_POLY_FILL_RECTANGLE: /*--------*/ operation = "poly fill rectangle"; /*--------*/ break;
		case XCB_POLY_FILL_ARC: /*--------------*/ operation = "poly fill arc"; /*--------------*/ break;
		case XCB_PUT_IMAGE: /*------------------*/ operation = "put image"; /*------------------*/ break;
		case XCB_GET_IMAGE: /*------------------*/ operation = "get image"; /*------------------*/ break;
		case XCB_POLY_TEXT_8: /*----------------*/ operation = "poly text (8)"; /*--------------*/ break;
		case XCB_POLY_TEXT_16: /*---------------*/ operation = "poly text (16)"; /*-------------*/ break;
		case XCB_IMAGE_TEXT_8: /*---------------*/ operation = "image text (8)"; /*-------------*/ break;
		case XCB_IMAGE_TEXT_16: /*--------------*/ operation = "image text (16)"; /*------------*/ break;
		case XCB_CREATE_COLORMAP: /*------------*/ operation = "create colormap"; /*------------*/ break;
		case XCB_FREE_COLORMAP: /*--------------*/ operation = "free colormap"; /*--------------*/ break;
		case XCB_COPY_COLORMAP_AND_FREE: /*-----*/ operation = "copy colormap and free"; /*-----*/ break;
		case XCB_INSTALL_COLORMAP: /*-----------*/ operation = "install colormap"; /*-----------*/ break;
		case XCB_UNINSTALL_COLORMAP: /*---------*/ operation = "uninstall colormap"; /*---------*/ break;
		case XCB_LIST_INSTALLED_COLORMAPS: /*---*/ operation = "list installed colormaps"; /*---*/ break;
		case XCB_ALLOC_COLOR: /*----------------*/ operation = "allocate color"; /*-------------*/ break;
		case XCB_ALLOC_NAMED_COLOR: /*----------*/ operation = "allocate named color"; /*-------*/ break;
		case XCB_ALLOC_COLOR_CELLS: /*----------*/ operation = "allocate color cells"; /*-------*/ break;
		case XCB_ALLOC_COLOR_PLANES: /*---------*/ operation = "allocate color planes"; /*------*/ break;
		case XCB_FREE_COLORS: /*----------------*/ operation = "free colors"; /*----------------*/ break;
		case XCB_STORE_COLORS: /*---------------*/ operation = "store colors"; /*---------------*/ break;
		case XCB_STORE_NAMED_COLOR: /*----------*/ operation = "store named color"; /*----------*/ break;
		case XCB_QUERY_COLORS: /*---------------*/ operation = "query colors"; /*---------------*/ break;
		case XCB_LOOKUP_COLOR: /*---------------*/ operation = "lookup color"; /*---------------*/ break;
		case XCB_CREATE_CURSOR: /*--------------*/ operation = "create cursor"; /*--------------*/ break;
		case XCB_CREATE_GLYPH_CURSOR: /*--------*/ operation = "create glyph cursor"; /*--------*/ break;
		case XCB_FREE_CURSOR: /*----------------*/ operation = "free cursor"; /*----------------*/ break;
		case XCB_RECOLOR_CURSOR: /*-------------*/ operation = "recolor cursor"; /*-------------*/ break;
		case XCB_QUERY_BEST_SIZE: /*------------*/ operation = "query best size"; /*------------*/ break;
		case XCB_QUERY_EXTENSION: /*------------*/ operation = "query extension"; /*------------*/ break;
		case XCB_LIST_EXTENSIONS: /*------------*/ operation = "list extensions"; /*------------*/ break;
		case XCB_CHANGE_KEYBOARD_MAPPING: /*----*/ operation = "change keyboard mapping"; /*----*/ break;
		case XCB_GET_KEYBOARD_MAPPING: /*-------*/ operation = "get keyboard mapping"; /*-------*/ break;
		case XCB_CHANGE_KEYBOARD_CONTROL: /*----*/ operation = "change keyboard control"; /*----*/ break;
		case XCB_GET_KEYBOARD_CONTROL: /*-------*/ operation = "get keyboard control"; /*-------*/ break;
		case XCB_BELL: /*-----------------------*/ operation = "bell"; /*-----------------------*/ break;
		case XCB_CHANGE_POINTER_CONTROL: /*-----*/ operation = "change pointer control"; /*-----*/ break;
		case XCB_GET_POINTER_CONTROL: /*--------*/ operation = "get pointer control"; /*--------*/ break;
		case XCB_SET_SCREEN_SAVER: /*-----------*/ operation = "set screen saver"; /*-----------*/ break;
		case XCB_GET_SCREEN_SAVER: /*-----------*/ operation = "get screen saver"; /*-----------*/ break;
		case XCB_CHANGE_HOSTS: /*---------------*/ operation = "change hosts"; /*---------------*/ break;
		case XCB_LIST_HOSTS: /*-----------------*/ operation = "list hosts"; /*-----------------*/ break;
		case XCB_SET_ACCESS_CONTROL: /*---------*/ operation = "set access control"; /*---------*/ break;
		case XCB_SET_CLOSE_DOWN_MODE: /*--------*/ operation = "set close down mode"; /*--------*/ break;
		case XCB_KILL_CLIENT: /*----------------*/ operation = "kill client"; /*----------------*/ break;
		case XCB_ROTATE_PROPERTIES: /*----------*/ operation = "rotate properties"; /*----------*/ break;
		case XCB_FORCE_SCREEN_SAVER: /*---------*/ operation = "force screen saver"; /*---------*/ break;
		case XCB_SET_POINTER_MAPPING: /*--------*/ operation = "set pointer mapping"; /*--------*/ break;
		case XCB_GET_POINTER_MAPPING: /*--------*/ operation = "get pointer mapping"; /*--------*/ break;
		case XCB_SET_MODIFIER_MAPPING: /*-------*/ operation = "set modifier mapping"; /*-------*/ break;
		case XCB_GET_MODIFIER_MAPPING: /*-------*/ operation = "get modifier mapping"; /*-------*/ break;
		case XCB_NO_OPERATION: /*---------------*/ operation = "no"; /*-------------------------*/ break;
		default: /*-----------------------------*/ operation = "unrecognized"; /*---------------*/ break;
	}
	fprintf(errorStream, "%s: %s error in %s operation with a minor of %u\n", programName, type, operation, (*genericError).minor_code);
	return;
}
PRINTCONNECTIONERROR_DEC{
	if(!xcb_connection_has_error(connection)){
		return 0;
	}
	_printConnectionError();
	return 1;
}
_PRINTCONNECTIONERROR_DEC{
	setMode(Exit);
	if(!mustOpenErrorStream || (errorStream = fopen(errorPath, "a"))){
		const char *string;
		switch(xcb_connection_has_error(connection)){
			case XCB_CONN_ERROR: /*-------------------*/ string = "socket / pipe / stream"; /*----*/ break;
			case XCB_CONN_CLOSED_EXT_NOTSUPPORTED: /*-*/ string = "extension not supported"; /*---*/ break;
			case XCB_CONN_CLOSED_MEM_INSUFFICIENT: /*-*/ string = "insufficient memory"; /*-------*/ break;
			case XCB_CONN_CLOSED_REQ_LEN_EXCEED: /*---*/ string = "exceeded request length"; /*---*/ break;
			case XCB_CONN_CLOSED_PARSE_ERR: /*--------*/ string = "parsing display string"; /*----*/ break;
			case XCB_CONN_CLOSED_INVALID_SCREEN: /*---*/ string = "screen - display mismatch"; /*-*/ break;
			default: /*-------------------------------*/ string = "unrecognized connection"; /*---*/ break;
		}
		fprintf(errorStream, "%s: fatal %s error, exiting\n", programName, string);
		if(mustOpenErrorStream){
			fclose(errorStream);
		}
	}
	return;
}
