#include <stdio.h>
#include <X11/Xlib.h>

void printEvent(const XEvent *const event){
	const XEvent dereferencedEvent = *event;
	fprintf(stdout, "event.type: %u, ", dereferencedEvent.type);
	if(dereferencedEvent.type == KeyPress){
		fprintf(stdout, "KeyPress\n");
	}else if(dereferencedEvent.type == KeyRelease){
		fprintf(stdout, "KeyRelease\n");
	}else if(dereferencedEvent.type == ButtonPress){
		fprintf(stdout, "ButtonPress\n");
	}else if(dereferencedEvent.type == ButtonRelease){
		fprintf(stdout, "ButtonRelease\n");
	}else if(dereferencedEvent.type == MotionNotify){
		fprintf(stdout, "MotionNotify\n");
	}else if(dereferencedEvent.type == EnterNotify){
		fprintf(stdout, "EnterNotify\n");
	}else if(dereferencedEvent.type == LeaveNotify){
		fprintf(stdout, "LeaveNotify\n");
	}else if(dereferencedEvent.type == FocusIn){
		fprintf(stdout, "FocusIn\n");
	}else if(dereferencedEvent.type == FocusOut){
		fprintf(stdout, "FocusOut\n");
	}else if(dereferencedEvent.type == KeymapNotify){
		fprintf(stdout, "KeymapNotify\n");
	}else if(dereferencedEvent.type == Expose){
		fprintf(stdout, "Expose\n");
	}else if(dereferencedEvent.type == GraphicsExpose){
		fprintf(stdout, "GraphicsExpose\n");
	}else if(dereferencedEvent.type == NoExpose){
		fprintf(stdout, "NoExpose\n");
	}else if(dereferencedEvent.type == VisibilityNotify){
		fprintf(stdout, "VisibilityNotify\n");
	}else if(dereferencedEvent.type == CreateNotify){
		fprintf(stdout, "CreateNotify\n");
	}else if(dereferencedEvent.type == DestroyNotify){
		fprintf(stdout, "DestroyNotify\n");
	}else if(dereferencedEvent.type == UnmapNotify){
		fprintf(stdout, "UnmapNotify\n");
	}else if(dereferencedEvent.type == MapNotify){
		fprintf(stdout, "MapNotify\n");
	}else if(dereferencedEvent.type == MapRequest){
		fprintf(stdout, "MapRequest\n");
	}else if(dereferencedEvent.type == ReparentNotify){
		fprintf(stdout, "ReparentNotify\n");
	}else if(dereferencedEvent.type == ConfigureNotify){
		fprintf(stdout, "ConfigureNotify\n");
	}else if(dereferencedEvent.type == ConfigureRequest){
		fprintf(stdout, "ConfigureRequest\n");
	}else if(dereferencedEvent.type == GravityNotify){
		fprintf(stdout, "GravityNotify\n");
	}else if(dereferencedEvent.type == ResizeRequest){
		fprintf(stdout, "ResizeRequest\n");
	}else if(dereferencedEvent.type == CirculateNotify){
		fprintf(stdout, "CirculateNotify\n");
	}else if(dereferencedEvent.type == CirculateRequest){
		fprintf(stdout, "CirculateRequest\n");
	}else if(dereferencedEvent.type == PropertyNotify){
		fprintf(stdout, "PropertyNotify\n");
	}else if(dereferencedEvent.type == SelectionClear){
		fprintf(stdout, "SelectionClear\n");
	}else if(dereferencedEvent.type == SelectionRequest){
		fprintf(stdout, "SelectionRequest\n");
	}else if(dereferencedEvent.type == SelectionNotify){
		fprintf(stdout, "SelectionNotify\n");
	}else if(dereferencedEvent.type == ColormapNotify){
		fprintf(stdout, "ColormapNotify\n");
	}else if(dereferencedEvent.type == ClientMessage){
		fprintf(stdout, "ClientMessage\n");
	}else if(dereferencedEvent.type == MappingNotify){
		fprintf(stdout, "MappingNotify\n");
	}else if(dereferencedEvent.type == GenericEvent){
		fprintf(stdout, "GenericEvent\n");
	}else if(dereferencedEvent.type == LASTEvent){
		fprintf(stdout, "LASTEvent\n");
	}
	return;
}
