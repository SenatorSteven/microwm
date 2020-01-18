#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include "headers/printEvent.h"

#define WindowAmount 20

Display *display;
XEvent event;
XWindowAttributes windowAttributes;
Window focusedWindow;

static void dealWithKeypress();

int main(void){
	if((display = XOpenDisplay(NULL))){



		XSelectInput(display, XDefaultRootWindow(display), KeyPressMask | SubstructureRedirectMask | StructureNotifyMask);



		XGrabKey(display, 40, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 41, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 95, None, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 111, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 113, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 114, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
		XGrabKey(display, 116, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);



		Window windowContainer;
		unsigned int currentWindow = 0;

		windowContainer = XCreateSimpleWindow(display, XDefaultRootWindow(display), (1920 - 500) / 2, (1080 - 500) / 2, 500, 500, 1, 0xFFFFFFFF, 0xFF000000);
		// XSelectInput(display, windowContainer, SubstructureNotifyMask);



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
				XMoveWindow(display, windowContainer, (currentWindow + 1) * 80, (currentWindow + 1) * 45);
				XReparentWindow(display, event.xmaprequest.window, windowContainer, 0, 0);
				XAddToSaveSet(display, event.xmaprequest.window);
				XMapWindow(display, windowContainer);
				XMapWindow(display, event.xmaprequest.window);
				XSetInputFocus(display, windowContainer, RevertToNone, CurrentTime);



				++currentWindow;
			}else if(event.type == UnmapNotify){
				fprintf(stdout, "unmapped\n");
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



		/*if(event.xbutton.subwindow != focusedWindow){
			focusedWindow = event.xbutton.subwindow;
			XRaiseWindow(display, focusedWindow);
			int revert = RevertToNone;
			XSetInputFocus(display, focusedWindow, revert, CurrentTime);
		}*/



	}else if(event.xkey.keycode == 95 && event.xkey.state == None){
		if(event.xkey.subwindow != None){
			XGetWindowAttributes(display, event.xkey.subwindow, &windowAttributes);
			if(windowAttributes.x == 0 && windowAttributes.y == 0 && windowAttributes.width == XDisplayWidth(display, XDefaultScreen(display)) && windowAttributes.height == XDisplayHeight(display, XDefaultScreen(display))){
				XMoveResizeWindow(display, event.xkey.subwindow, XDisplayWidth(display, XDefaultScreen(display)) / 4, XDisplayHeight(display, XDefaultScreen(display)) / 4, XDisplayWidth(display, XDefaultScreen(display)) / 2, XDisplayHeight(display, XDefaultScreen(display)) / 2);
			}else{
				XMoveResizeWindow(display, event.xkey.subwindow, 0, 0, XDisplayWidth(display, XDefaultScreen(display)), XDisplayHeight(display, XDefaultScreen(display)));
				XMapRaised(display, event.xkey.subwindow);
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
