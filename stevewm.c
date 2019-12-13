// clear; cd $HOME/Downloads/stevewm/; gcc stevewm.c readConfig.c -lX11 -lXrandr -o output/stevewm; ./output/stevewm

#include <stdio.h>
#include <X11/Xlib.h>
#include "headers/defines.h"

#define ModeContinue /*-*/ ((unsigned int)0)
#define ModeRestart /*--*/ ((unsigned int)1)
#define ModeExit /*-----*/ ((unsigned int)2)

static void eventLoop(Display *const display, unsigned int *const mode);

int main(void){
	unsigned int mode = ModeContinue;
	Display *display;
	while(mode == ModeContinue || mode == ModeRestart){
		mode = ModeContinue;
		if((display = XOpenDisplay(NULL))){
			eventLoop(display, &mode);
			XCloseDisplay(display);
		}else{
			fprintf(stderr, "%s: could not connect to server\n", ProgramName);
			break;
		}
	}
	return 0;
}
static void eventLoop(Display *const display, unsigned int *const mode){
	XGrabKey(display, 9, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
	XEvent event;
	for(;;){
		XNextEvent(display, &event);
		if(event.type == KeyPress){
			*mode = ModeExit;
			break;
		}
	}
	return;
}
