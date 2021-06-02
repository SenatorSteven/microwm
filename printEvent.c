/* printEvent.c

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

#include <stdio.h>
#include <xcb/xcb.h>
#include "headers/defines.h"
#include "headers/printEvent.h"

#if DEBUG == true
PRINTEVENT_DEC{
	const char *type;
	switch(event){
		case XCB_EVENT_MASK_NO_EVENT: /*-*/ return;
		case XCB_KEY_PRESS: /*-----------*/ type = "KeyPress"; /*---------*/ break;
		case XCB_KEY_RELEASE: /*---------*/ type = "KeyRelease"; /*-------*/ break;
		case XCB_BUTTON_PRESS: /*--------*/ type = "ButtonPress"; /*------*/ break;
		case XCB_BUTTON_RELEASE: /*------*/ type = "ButtonRelease"; /*----*/ break;
		case XCB_MOTION_NOTIFY: /*-------*/ type = "MotionNotify"; /*-----*/ break;
		case XCB_ENTER_NOTIFY: /*--------*/ type = "EnterNotify"; /*------*/ break;
		case XCB_LEAVE_NOTIFY: /*--------*/ type = "LeaveNotify"; /*------*/ break;
		case XCB_FOCUS_IN: /*------------*/ type = "FocusIn"; /*----------*/ break;
		case XCB_FOCUS_OUT: /*-----------*/ type = "FocusOut"; /*---------*/ break;
		case XCB_KEYMAP_NOTIFY: /*-------*/ type = "KeymapNotify"; /*-----*/ break;
		case XCB_EXPOSE: /*--------------*/ type = "Expose"; /*-----------*/ break;
		case XCB_GRAPHICS_EXPOSURE: /*---*/ type = "GraphicsExpose"; /*---*/ break;
		case XCB_NO_EXPOSURE: /*---------*/ type = "NoExpose"; /*---------*/ break;
		case XCB_VISIBILITY_NOTIFY: /*---*/ type = "VisibilityNotify"; /*-*/ break;
		case XCB_CREATE_NOTIFY: /*-------*/ type = "CreateNotify"; /*-----*/ break;
		case XCB_DESTROY_NOTIFY: /*------*/ type = "DestroyNotify"; /*----*/ break;
		case XCB_UNMAP_NOTIFY: /*--------*/ type = "UnmapNotify"; /*------*/ break;
		case XCB_MAP_NOTIFY: /*----------*/ type = "MapNotify"; /*--------*/ break;
		case XCB_MAP_REQUEST: /*---------*/ type = "MapRequest"; /*-------*/ break;
		case XCB_REPARENT_NOTIFY: /*-----*/ type = "ReparentNotify"; /*---*/ break;
		case XCB_CONFIGURE_NOTIFY: /*----*/ type = "ConfigureNotify"; /*--*/ break;
		case XCB_CONFIGURE_REQUEST: /*---*/ type = "ConfigureRequest"; /*-*/ break;
		case XCB_GRAVITY_NOTIFY: /*------*/ type = "GravityNotify"; /*----*/ break;
		case XCB_RESIZE_REQUEST: /*------*/ type = "ResizeRequest"; /*----*/ break;
		case XCB_CIRCULATE_NOTIFY: /*----*/ type = "CirculateNotify"; /*--*/ break;
		case XCB_CIRCULATE_REQUEST: /*---*/ type = "CirculateRequest"; /*-*/ break;
		case XCB_PROPERTY_NOTIFY: /*-----*/ type = "PropertyNotify"; /*---*/ break;
		case XCB_SELECTION_CLEAR: /*-----*/ type = "SelectionClear"; /*---*/ break;
		case XCB_SELECTION_REQUEST: /*---*/ type = "SelectionRequest"; /*-*/ break;
		case XCB_SELECTION_NOTIFY: /*----*/ type = "SelectionNotify"; /*--*/ break;
		case XCB_COLORMAP_NOTIFY: /*-----*/ type = "ColormapNotify"; /*---*/ break;
		case XCB_CLIENT_MESSAGE: /*------*/ type = "ClientMessage"; /*----*/ break;
		case XCB_MAPPING_NOTIFY: /*------*/ type = "MappingNotify"; /*----*/ break;
		case XCB_GE_GENERIC: /*----------*/ type = "GenericEvent"; /*-----*/ break;
		default: /*----------------------*/ type = "Unrecognized"; /*-----*/ break;
	}
	fprintf(stdout, "event: %s\n", type);
	return;
}
#endif
