#!/bin/bash
if [ ! -d "output" ]; then
	mkdir output
fi
gcc -Wall -Wextra -pedantic microwm.c readConfig.c -lX11 -o output/microwm
exit 0
