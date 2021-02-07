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
#include <stdlib.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include "headers/defines.h"
#include "headers/getParameters.h"
#include "headers/eventLoop.h"

extern const char *programName;
extern Mode mode;
extern Display *display;
extern FILE *errorStream;
extern void *containerData;
extern unsigned int containerAmount;

static void setRootProperties(void);

int main(const int argumentCount, const char *const *const argumentVector){
	errorStream = stderr;
	if(getParameters((unsigned int)argumentCount, argumentVector)){
		if((display = XOpenDisplay(NULL))){
			mode = ContinueMode;
			containerData = NULL;
			containerAmount = 0;
			setRootProperties();
			eventLoop:{
				eventLoop();
				if(!mode(Exit)){
					goto eventLoop;
				}
			}
			free(containerData);
			XCloseDisplay(display);
		}else{
			fprintf(errorStream, "%s: could not connect to server\n", programName);
		}
	}
	return 0;
}
static void setRootProperties(void){
	const Atom _NET_SUPPORTED = XInternAtom(display, "_NET_SUPPORTED", False);
	unsigned char property[3];
	property[0] = _NET_SUPPORTED;
	property[1] = XInternAtom(display, "_NET_WM_STATE", False);
	property[2] = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);
	XChangeProperty(display, XDefaultRootWindow(display), _NET_SUPPORTED, XA_ATOM, 32, PropModeReplace, property, 3);
	return;
}
