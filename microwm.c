#include <stdio.h>
#include <X11/Xlib.h>
#include "headers/defines.h"
#include "headers/getParameters.h"
#include "headers/readConfig.h"

#define ModeContinue /*---*/ ((unsigned int)0)
#define ModeRestart /*----*/ ((unsigned int)1)
#define ModeExit /*-------*/ ((unsigned int)2)

static void eventLoop(Display *const display, unsigned int *const mode);

int main(const int argumentCount, const char *const *const argumentVector){
	const char *configPath;
	if(getParameters((unsigned int *)&argumentCount, argumentVector, &configPath)){
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
	}
	return 0;
}
static void eventLoop(Display *const display, unsigned int *const mode){
	XGrabKey(display, 9, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
	XGrabKey(display, 39, Mod4Mask, XDefaultRootWindow(display), True, GrabModeAsync, GrabModeAsync);
	XEvent event;
	for(;;){
		XNextEvent(display, &event);
		if(event.type == KeyPress){
			if(event.xkey.keycode == 9){
				*mode = ModeExit;
				break;
			}else{
				fprintf(stdout, "keycode: %u\n", event.xkey.keycode);
			}
		}
	}
	return;
}
