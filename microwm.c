/* microwm.c

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
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include "headers/defines.h"
#include "headers/getParameters.h"
#include "headers/eventLoop.h"

extern const char *programName;
extern Mode mode;
extern Display *display;

static void setRootProperties(void);

int main(const int argumentCount, const char *const *const argumentVector){
	if(getParameters((unsigned int)argumentCount, argumentVector)){
		for(;;){
			mode = ContinueMode;
			if((display = XOpenDisplay(NULL))){
				setRootProperties();
				eventLoop();
				XCloseDisplay(display);
			}else{
				fprintf(stderr, "%s: could not connect to server\n", programName);
				break;
			}
			if(mode == ExitMode){
				break;
			}
		}
	}
	return 0;
}
static void setRootProperties(void){
	// WM_STATE

	// _NET_CLIENT_LIST
	// _NET_NUMBER_OF_DESKTOPS
	// _NET_DESKTOP_GEOMETRY
	// _NET_DESKTOP_VIEWPORT
	// _NET_CURRENT_DESKTOP
	// _NET_DESKTOP_NAMES
	// _NET_ACTIVE_WINDOW
	// _NET_WORKAREA
	// _NET_SUPPORTING_WM_CHECK
	// _NET_VIRTUAL_ROOTS
	// _NET_DESKTOP_LAYOUT
	// _NET_SHOWING_DESKTOP

	// _NET_CLOSE_WINDOW
	// _NET_MOVERESIZE_WINDOW
	// _NET_WM_MOVERESIZE
	// _NET_RESTACK_WINDOW
	// _NET_REQUEST_FRAME_EXTENTS

	// _NET_WM_PING
	// _NET_WM_SYNC_REQUEST

	// _NET_WM_NAME
	// _NET_WM_VISIBLE_NAME
	// _NET_WM_ICON_NAME
	// _NET_WM_VISIBLE_ICON_NAME
	// _NET_WM_DESKTOP
	// _NET_WM_WINDOW_TYPE

	// _NET_WM_STATE
		// _NET_WM_STATE_MODAL
		// _NET_WM_STATE_STICKY
		// _NET_WM_STATE_MAXIMIZED_VERT
		// _NET_WM_STATE_MAXIMIZED_HORZ
		// _NET_WM_STATE_SHADED
		// _NET_WM_STATE_SKIP_TASKBAR
		// _NET_WM_STATE_SKIP_PAGER
		// _NET_WM_STATE_HIDDEN
		// _NET_WM_STATE_FULLSCREEN
		// _NET_WM_STATE_ABOVE
		// _NET_WM_STATE_BELOW
		// _NET_WM_STATE_DEMANDS_ATTENTION

	// _NET_WM_ALLOWED_ACTIONS
		// _NET_WM_ACTION_MOVE
		// _NET_WM_ACTION_RESIZE
		// _NET_WM_ACTION_MINIMIZE
		// _NET_WM_ACTION_SHADE
		// _NET_WM_ACTION_STICK
		// _NET_WM_ACTION_MAXIMIZE_HORZ
		// _NET_WM_ACTION_MAXIMIZE_VERT
		// _NET_WM_ACTION_FULLSCREEN
		// _NET_WM_ACTION_CHANGE_DESKTOP
		// _NET_WM_ACTION_CLOSE

	// _NET_WM_STRUT
	// _NET_WM_STRUT_PARTIAL
	// _NET_WM_PID
	// _NET_WM_USER_TIME
	// _NET_FRAME_EXTENTS



	const unsigned char properties[1] = {
		XInternAtom(display, "_NET_SUPPORTED", False)

		// _NET_CLIENT_LIST
			// _NET_CLIENT_LIST_STACKING

		// _NET_NUMBER_OF_DESKTOPS
		// _NET_DESKTOP_GEOMETRY
		// _NET_DESKTOP_VIEWPORT
		// _NET_CURRENT_DESKTOP
		// _NET_DESKTOP_NAMES
		// _NET_ACTIVE_WINDOW
		// _NET_WORKAREA
		// _NET_SUPPORTING_WM_CHECK
		// _NET_VIRTUAL_ROOTS
		// _NET_DESKTOP_LAYOUT
		// _NET_SHOWING_DESKTOP

		// _NET_CLOSE_WINDOW
		// _NET_MOVERESIZE_WINDOW

		// _NET_WM_MOVERESIZE
			// _NET_WM_MOVERESIZE_SIZE_TOPLEFT
			// _NET_WM_MOVERESIZE_SIZE_TOP
			// _NET_WM_MOVERESIZE_SIZE_TOPRIGHT
			// _NET_WM_MOVERESIZE_SIZE_RIGHT
			// _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT
			// _NET_WM_MOVERESIZE_SIZE_BOTTOM
			// _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT
			// _NET_WM_MOVERESIZE_SIZE_LEFT
			// _NET_WM_MOVERESIZE_MOVE
			// _NET_WM_MOVERESIZE_SIZE_KEYBOARD
			// _NET_WM_MOVERESIZE_MOVE_KEYBOARD

		// _NET_RESTACK_WINDOW
		// _NET_REQUEST_FRAME_EXTENTS

		// _NET_WM_PING
		// _NET_WM_SYNC_REQUEST
	};



	XChangeProperty(display, XDefaultRootWindow(display), XInternAtom(display, "_NET_SUPPORTED", False), XA_ATOM, 32, PropModeReplace, properties, 1);









	return;
}
