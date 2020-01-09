#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

static void printEvent(const XEvent *const event);

int main(void){
	Display *display = XOpenDisplay(NULL);
	if(display){



		XSelectInput(display, XDefaultRootWindow(display), KeyPressMask | SubstructureNotifyMask);



		// XGrabKey(display, 40, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XEvent event;
		for(;;){
			XNextEvent(display, &event);
			printEvent(&event);
			if(event.type == KeyPress){
				if(event.xkey.keycode == 40 && event.xkey.state == Mod4Mask){
					system("dmenu_run -i -b -p \"DMenu | <MatrixCustom> | TheSenatorSteven\" -nb \"#000000\" -sb \"#1f1f1f\" -nf \"#00ff00\" -sf \"#00ff00\"");
				}
			}else if(event.type == MapNotify){
				fprintf(stdout, "                         ,         window: %lu\n", event.xmap.window);
				// XUnmapWindow(display, event.xmap.window);
				// XMoveResizeWindow(display, event.xmap.window, (1920 - 500) / 2, (1080 - 500) / 2, 500, 500);
			}
		}
		XCloseDisplay(display);
	}else{
		fprintf(stderr, "could not connect to server\n");
	}
	return 0;
}









#ifdef a
	#include "headers/defines.h"

	int main(void){
		Display *display = XOpenDisplay(NULL);
		if(display){
			// XSelectInput(display, XDefaultRootWindow(display), KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask | PointerMotionMask | PointerMotionHintMask | Button1MotionMask | Button2MotionMask | Button3MotionMask | Button4MotionMask | Button5MotionMask | ButtonMotionMask | KeymapStateMask | ExposureMask | VisibilityChangeMask | StructureNotifyMask | ResizeRedirectMask | SubstructureNotifyMask | SubstructureRedirectMask | FocusChangeMask | PropertyChangeMask | ColormapChangeMask | OwnerGrabButtonMask);
			// XSelectInput(display, XDefaultRootWindow(display), KeyPressMask | KeyReleaseMask | SubstructureNotifyMask | SubstructureRedirectMask);
			XSelectInput(display, XDefaultRootWindow(display), KeyPressMask | KeyReleaseMask | StructureNotifyMask);
			eventLoop(display);
			XCloseDisplay(display);
		}else{
			fprintf(stderr, "%s: could not connect to server\n", ProgramName);
		}
		return 0;
	}
	static void eventLoop(Display *const display){
		XGrabKey(display, 40, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 52, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 111, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 113, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 114, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 116, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 95, None, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XEvent event;
		unsigned int windowAmount;
		Window currentWindow;
		Window focusedWindow;
		XWindowChanges windowChanges;
		for(;;){
			XNextEvent(display, &event);
			printEvent(&event);
			if(event.type == KeyPress){
				if(event.xkey.keycode == 40){
					system("dmenu_run -i -b -p \"DMenu | <MatrixCustom> | TheSenatorSteven\" -nb \"#000000\" -sb \"#1f1f1f\" -nf \"#00ff00\" -sf \"#00ff00\"");
				}else if(event.xkey.keycode == 52){
					if(event.xkey.subwindow != None){
						currentWindow = event.xbutton.subwindow;
						// XReparentWindow(display, currentWindow, XDefaultRootWindow(display), 0, 0);
						XRaiseWindow(display, currentWindow);
						int revert;
						XGetInputFocus(display, &focusedWindow, &revert);
						if(currentWindow != focusedWindow){
							XSetInputFocus(display, currentWindow, revert, CurrentTime);
						}
					}
				}else if(event.xkey.keycode == 111){
					if(event.xkey.subwindow != None){
						windowChanges.y = 0;
						windowChanges.width = 1920 / 2;
						windowChanges.height = 1080 / 2;
						XConfigureWindow(display, event.xbutton.subwindow, CWY | CWWidth | CWHeight, &windowChanges);
					}
				}else if(event.xkey.keycode == 113){
					if(event.xkey.subwindow != None){
						windowChanges.x = 0;
						windowChanges.width = 1920 / 2;
						windowChanges.height = 1080 / 2;
						XConfigureWindow(display, event.xbutton.subwindow, CWX | CWWidth | CWHeight, &windowChanges);
					}
				}else if(event.xkey.keycode == 114){
					if(event.xkey.subwindow != None){
						windowChanges.x = 1920 / 2;
						windowChanges.width = 1920 / 2;
						windowChanges.height = 1080 / 2;
						XConfigureWindow(display, event.xbutton.subwindow, CWX | CWWidth | CWHeight, &windowChanges);
					}
				}else if(event.xkey.keycode == 116){
					if(event.xkey.subwindow != None){
						windowChanges.y = 1080 / 2;
						windowChanges.width = 1920 / 2;
						windowChanges.height = 1080 / 2;
						XConfigureWindow(display, event.xbutton.subwindow, CWY | CWWidth | CWHeight, &windowChanges);
					}
				}else if(event.xkey.keycode == 95){
					if(event.xkey.subwindow != None){
						windowChanges.x = 0;
						windowChanges.y = 0;
						windowChanges.width = 1920;
						windowChanges.height = 1080;
						XConfigureWindow(display, event.xbutton.subwindow, CWX | CWY | CWWidth | CWHeight, &windowChanges);
					}
				}
			}else if(event.type == CreateNotify){
	/*			windowChanges.x = 1920 / 2;
				windowChanges.y = 0;
				windowChanges.width = 1920 / 2;
				windowChanges.height = 1080;
				XConfigureWindow(display, event.xcreatewindow.window, CWX | CWY | CWWidth | CWHeight, &windowChanges);*/
			}else if(event.type == ConfigureRequest){
				
			}else if(event.type == MapRequest){
	//			XMapWindow(display, event.xmaprequest.window);
			}
		}
		return;
	}
#endif









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
