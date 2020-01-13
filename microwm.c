#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#define WindowAmount 20

Display *display;
XEvent event;
XWindowAttributes windowAttributes;
Window focusedWindow;

static void printEvent(const XEvent *const event);
static void dealWithKeypress();

int main(void){
	display = XOpenDisplay(NULL);
	if(display){



		XSelectInput(display, XDefaultRootWindow(display), KeyPressMask | SubstructureRedirectMask | StructureNotifyMask);



		XGrabKey(display, 40, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 41, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 95, None, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 111, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 113, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 114, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 116, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);



		Window windowContainer = windowContainer = XCreateSimpleWindow(display, XDefaultRootWindow(display), (1920 - 500) / 2, (1080 - 500) / 2, 500, 500, 1, 0xFFFFFFFF, 0xFF000000);



		for(;;){
			XNextEvent(display, &event);
			printEvent(&event);
			if(event.type == KeyPress){
				dealWithKeypress();



			}else if(event.type == ConfigureRequest){
				fprintf(stdout, "configured\n");
				XResizeWindow(display, event.xconfigure.window, 500, 500);



			}else if(event.type == MapRequest){
				fprintf(stdout, "mapped\n");
				XReparentWindow(display, event.xmaprequest.window, windowContainer, 0, 0);
				XAddToSaveSet(display, event.xmaprequest.window);
				XMapWindow(display, windowContainer);
				XMapWindow(display, event.xmaprequest.window);



			}else if(event.type == UnmapNotify){
				if(event.xunmap.window != windowContainer){
					XUnmapWindow(display, windowContainer);
					// XReparentWindow(display, event.xunmap.window, XDefaultRootWindow(display), 0, 0);
					// XRemoveFromSaveSet(display, event.xunmap.window);
					XDestroyWindow(display, windowContainer);
				}



			}else if(event.type == DestroyNotify){
				fprintf(stdout, "destroyed\n");
			}
		}



		XCloseDisplay(display);
	}else{
		fprintf(stderr, "could not connect to server\n");
	}
	return 0;
}

static void dealWithKeypress(){
	if(event.xkey.keycode == 40 && event.xkey.state == Mod4Mask){
		system("dmenu_run -i -b -p \"DMenu | <MatrixCustom> | TheSenatorSteven\" -nb \"#000000\" -sb \"#1f1f1f\" -nf \"#00ff00\" -sf \"#00ff00\"");
	}else if(event.xkey.keycode == 41 && event.xkey.state == Mod4Mask){



		if(event.xbutton.subwindow != focusedWindow){
			focusedWindow = event.xbutton.subwindow;
			XRaiseWindow(display, focusedWindow);
			int revert;
			XSetInputFocus(display, focusedWindow, revert, CurrentTime);
		}



	}else if(event.xkey.keycode == 95 && event.xkey.state == None){
		if(event.xkey.subwindow != None){
			XGetWindowAttributes(display, event.xkey.subwindow, &windowAttributes);
			if(windowAttributes.x == 0 && windowAttributes.y == 0 && windowAttributes.width == XDisplayWidth(display, XDefaultScreen(display)) && windowAttributes.height == XDisplayHeight(display, XDefaultScreen(display))){
				XMoveResizeWindow(display, event.xkey.subwindow, XDisplayWidth(display, XDefaultScreen(display)) / 4, XDisplayHeight(display, XDefaultScreen(display)) / 4, XDisplayWidth(display, XDefaultScreen(display)) / 2, XDisplayHeight(display, XDefaultScreen(display)) / 2);
			}else{
				XMoveResizeWindow(display, event.xkey.subwindow, 0, 0, XDisplayWidth(display, XDefaultScreen(display)), XDisplayHeight(display, XDefaultScreen(display)));
			}
		}
	}else if(event.xkey.keycode == 111 && event.xkey.state == Mod4Mask){
		if(event.xkey.subwindow != None){
			XGetWindowAttributes(display, event.xkey.subwindow, &windowAttributes);
			XMoveResizeWindow(display, event.xkey.subwindow, windowAttributes.x, 0, XDisplayWidth(display, XDefaultScreen(display)) / 2, XDisplayHeight(display, XDefaultScreen(display)) / 2);
		}
	}else if(event.xkey.keycode == 113 && event.xkey.state == Mod4Mask){
		if(event.xkey.subwindow != None){
			XGetWindowAttributes(display, event.xkey.subwindow, &windowAttributes);
			XMoveResizeWindow(display, event.xkey.subwindow, 0, windowAttributes.y, XDisplayWidth(display, XDefaultScreen(display)) / 2, XDisplayHeight(display, XDefaultScreen(display)) / 2);
		}
	}else if(event.xkey.keycode == 114 && event.xkey.state == Mod4Mask){
		if(event.xkey.subwindow != None){
			XGetWindowAttributes(display, event.xkey.subwindow, &windowAttributes);
			XMoveResizeWindow(display, event.xkey.subwindow, XDisplayWidth(display, XDefaultScreen(display)) / 2, windowAttributes.y, XDisplayWidth(display, XDefaultScreen(display)) / 2, XDisplayHeight(display, XDefaultScreen(display)) / 2);
		}
	}else if(event.xkey.keycode == 116 && event.xkey.state == Mod4Mask){
		if(event.xkey.subwindow != None){
			XGetWindowAttributes(display, event.xkey.subwindow, &windowAttributes);
			XMoveResizeWindow(display, event.xkey.subwindow, windowAttributes.x, XDisplayHeight(display, XDefaultScreen(display)) / 2, XDisplayWidth(display, XDefaultScreen(display)) / 2, XDisplayHeight(display, XDefaultScreen(display)) / 2);
		}
	}
	return;
}

static void printEvent(const XEvent *const event){
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
