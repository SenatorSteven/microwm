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
#include <X11/Xlib.h>
#include "headers/printEvent.h"

PRINTEVENT_DEC{
	fprintf(stdout, "event.type: ");
	if(event.type < 10){
		fprintf(stdout, " ");
	}
	fprintf(stdout, "%u, ", event.type);
	if(event.type == KeyPress){
		fprintf(stdout, "KeyPress\n");
	}else if(event.type == KeyRelease){
		fprintf(stdout, "KeyRelease\n");
	}else if(event.type == ButtonPress){
		fprintf(stdout, "ButtonPress\n");
	}else if(event.type == ButtonRelease){
		fprintf(stdout, "ButtonRelease\n");
	}else if(event.type == MotionNotify){
		fprintf(stdout, "MotionNotify\n");
	}else if(event.type == EnterNotify){
		fprintf(stdout, "EnterNotify\n");
	}else if(event.type == LeaveNotify){
		fprintf(stdout, "LeaveNotify\n");
	}else if(event.type == FocusIn){
		fprintf(stdout, "FocusIn\n");
	}else if(event.type == FocusOut){
		fprintf(stdout, "FocusOut\n");
	}else if(event.type == KeymapNotify){
		fprintf(stdout, "KeymapNotify\n");
	}else if(event.type == Expose){
		fprintf(stdout, "Expose\n");
	}else if(event.type == GraphicsExpose){
		fprintf(stdout, "GraphicsExpose\n");
	}else if(event.type == NoExpose){
		fprintf(stdout, "NoExpose\n");
	}else if(event.type == VisibilityNotify){
		fprintf(stdout, "VisibilityNotify\n");
	}else if(event.type == CreateNotify){
		fprintf(stdout, "CreateNotify\n");
	}else if(event.type == DestroyNotify){
		fprintf(stdout, "DestroyNotify\n");
	}else if(event.type == UnmapNotify){
		fprintf(stdout, "UnmapNotify\n");
	}else if(event.type == MapNotify){
		fprintf(stdout, "MapNotify\n");
	}else if(event.type == MapRequest){
		fprintf(stdout, "MapRequest\n");
	}else if(event.type == ReparentNotify){
		fprintf(stdout, "ReparentNotify\n");
	}else if(event.type == ConfigureNotify){
		fprintf(stdout, "ConfigureNotify\n");
	}else if(event.type == ConfigureRequest){
		fprintf(stdout, "ConfigureRequest\n");
	}else if(event.type == GravityNotify){
		fprintf(stdout, "GravityNotify\n");
	}else if(event.type == ResizeRequest){
		fprintf(stdout, "ResizeRequest\n");
	}else if(event.type == CirculateNotify){
		fprintf(stdout, "CirculateNotify\n");
	}else if(event.type == CirculateRequest){
		fprintf(stdout, "CirculateRequest\n");
	}else if(event.type == PropertyNotify){
		fprintf(stdout, "PropertyNotify\n");
	}else if(event.type == SelectionClear){
		fprintf(stdout, "SelectionClear\n");
	}else if(event.type == SelectionRequest){
		fprintf(stdout, "SelectionRequest\n");
	}else if(event.type == SelectionNotify){
		fprintf(stdout, "SelectionNotify\n");
	}else if(event.type == ColormapNotify){
		fprintf(stdout, "ColormapNotify\n");
	}else if(event.type == ClientMessage){
		fprintf(stdout, "ClientMessage\n");
	}else if(event.type == MappingNotify){
		fprintf(stdout, "MappingNotify\n");
	}else if(event.type == GenericEvent){
		fprintf(stdout, "GenericEvent\n");
	}else if(event.type == LASTEvent){
		fprintf(stdout, "LASTEvent\n");
	}else{
		fprintf(stdout, "\n");
	}
	return;
}
