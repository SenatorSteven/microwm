#!/bin/bash
if [ ! -d "output" ]; then
	mkdir output
fi
gcc -Wall -Wextra -pedantic microwm.c getParameters.c readConfig.c -lX11 -lXrandr -o output/microwm
exit 0
