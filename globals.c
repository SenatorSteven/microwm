/* globals.c

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
#include <X11/Xlib.h>
#include "headers/defines.h"

const char *programName;
const char *configPath;
ErrorData error;
Mode mode;
Display *display;
void *containerData;
unsigned int containerAmount;
ManagementMode managementMode;
ProgramData *programData;

PRINTERROR_DEC{
	if(error.mustOpenStream){
		if(!(error.stream = fopen(error.path, "w"))){
			goto emergencyExit;
		}
		fprintf(error.stream, "%s: %s\n", programName, string);
		fclose(error.stream);
		goto emergencyExit;
	}
	fprintf(error.stream, "%s: %s\n", programName, string);
	emergencyExit:{}
	return;
}
