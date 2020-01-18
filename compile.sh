#!/bin/bash
if [ ! -d "output" ]; then
	mkdir output
fi
gcc -Wall -Wextra -pedantic microwm.c printEvent.c -lX11 -lXrandr -o output/truemicrowm
exit 0
