#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include "headers/defines.h"

#define NoPositions /*-----------------------*/ 0
#define LinesPosition /*---------------------*/ (1 << 0)

#define NoOperation /*-----------------------*/ ((unsigned int)0)
#define OperationAddition /*-----------------*/ ((unsigned int)1)
#define OperationSubtraction /*--------------*/ ((unsigned int)2)
#define OperationMultiplication /*-----------*/ ((unsigned int)3)
#define OperationDivision /*-----------------*/ ((unsigned int)4)

static FILE *getConfigFile(const char *const pathArray);
static unsigned int pushSpaces(const char *const lineArray, unsigned int *const element);
static unsigned int isVariable(const char *const variableArray, const char *const lineArray, unsigned int *const element);
static unsigned int getUnsignedDecimalNumber(Display *const display, const unsigned int *const currentMonitor, const Window *const window, const char *const lineArray, unsigned int *const element);
static int getDecimalNumber(Display *const display, const unsigned int *const currentMonitor, const Window *const window, const char *const lineArray, unsigned int *const element);
static int getARGB(const char *const lineArray, unsigned int *const element);
static void getKeys(Display *const display, const unsigned int *const currentMonitor, const Window *const window, const char *const lineArray, unsigned int *const element, unsigned int *const key, int *const masks);
static char *getText(const char *const lineArray, unsigned int *const element);
static char *getCommand(const char *const lineArray, unsigned int *const element);
static unsigned int printLineError(const char *const lineArray, const unsigned int *const element, const unsigned int *const currentLine);

unsigned int readConfig(const char *const pathArray, const Window *const parentWindow){
	unsigned int value = 0;
	FILE *config = getConfigFile(pathArray);
	if(config){
		size_t characters = DefaultCharactersCount;
		char *line = (char *)malloc(characters * sizeof(char));
		if(line){
			unsigned int maxLinesCount = DefaultLinesCount;
			unsigned int element;
			int hasReadVariable = NoPositions;
			for(unsigned int currentLine = 0; currentLine < maxLinesCount; currentLine++){
				element = 0;
				getline(&line, &characters, config);
				pushSpaces(line, &element);
				if(!isVariable("#", line, &element)){
					
				}
			}
			free(line);
			value = 1;
		}else{
			fprintf(stderr, "%s: could not allocate space for config line\n", ProgramName);
		}
		fclose(config);
	}
	return value;
}
static FILE *getConfigFile(const char *const pathArray){
	FILE *config = fopen(pathArray, "r");
	if(!config){
		if((config = fopen(pathArray, "w"))){
			
			fclose(config);
			config = fopen(pathArray, "r");
		}else{
			fprintf(stderr, "%s: could not locate config file\n", ProgramName);
		}
	}
	return config;
}
static unsigned int pushSpaces(const char *const lineArray, unsigned int *const element){
	unsigned int dereferencedElement = *element;
	unsigned int value = 0;
	while(dereferencedElement < DefaultCharactersCount && (lineArray[dereferencedElement] == ' ' || lineArray[dereferencedElement] == 9)){
		dereferencedElement++;
	}
	if(dereferencedElement > *element){
		*element = dereferencedElement;
		value = 1;
	}
	return value;
}
static unsigned int isVariable(const char *const variable, const char *const lineArray, unsigned int *const element){
	unsigned int dereferencedElement = *element;
	unsigned int value = 0;
	unsigned int length = 0;
	while(variable[length] > '\0'){
		length++;
	}
	unsigned int currentCharacter = 0;
	while(currentCharacter < length){
		if(variable[currentCharacter] >= 'A' && variable[currentCharacter] <= 'Z'){
			if(!(lineArray[dereferencedElement] == variable[currentCharacter] || lineArray[dereferencedElement] == variable[currentCharacter] + 32)){
				break;
			}
		}else if(variable[currentCharacter] >= 'a' && variable[currentCharacter] <= 'z'){
			if(!(lineArray[dereferencedElement] == variable[currentCharacter] || lineArray[dereferencedElement] == variable[currentCharacter] - 32)){
				break;
			}
		}else{
			if(!(lineArray[dereferencedElement] == variable[currentCharacter])){
				break;
			}
		}
		dereferencedElement++;
		currentCharacter++;
	}
	if(currentCharacter == length){
		*element = dereferencedElement;
		value = 1;
	}
	return value;
}
static unsigned int getUnsignedDecimalNumber(Display *const display, const unsigned int *const currentMonitor, const Window *const parentWindow, const char *const lineArray, unsigned int *const element){
	unsigned int number = getDecimalNumber(display, currentMonitor, parentWindow, lineArray, element);
	if((int)number < 0){
		fprintf(stderr, "%s: %i is not an unsigned integer\n", ProgramName, (int)number);
		number = 0;
	}
	return number;
}
static int getDecimalNumber(Display *const display, const unsigned int *const currentMonitor, const Window *const parentWindow, const char *const lineArray, unsigned int *const element){
	unsigned int dereferencedElement = *element;
	int number = 0;
	int numberRead = 0;
	int numberOperatedOn = 0;
	unsigned int operation = NoOperation;
	unsigned int lastOperation = NoOperation;
	XWindowAttributes windowAttributes;
	XGetWindowAttributes(display, *parentWindow, &windowAttributes);
	if(*parentWindow == XDefaultRootWindow(display)){
		int monitorsAmount;
		XRRMonitorInfo *monitorInfo = XRRGetMonitors(display, XDefaultRootWindow(display), True, &monitorsAmount);
		windowAttributes.width = monitorInfo[*currentMonitor].width;
		windowAttributes.height = monitorInfo[*currentMonitor].height;
	}
	while(dereferencedElement < DefaultCharactersCount){
		pushSpaces(lineArray, &dereferencedElement);
		if(lineArray[dereferencedElement] >= '0' && lineArray[dereferencedElement] <= '9'){
			numberRead *= 10;
			numberRead += lineArray[dereferencedElement];
			numberRead -= 48;
			dereferencedElement++;
		}else if(isVariable("ParentWidth", lineArray, &dereferencedElement)){
			numberRead = windowAttributes.width;
		}else if(isVariable("ParentHeight", lineArray, &dereferencedElement)){
			numberRead = windowAttributes.height;
		}else if(lineArray[dereferencedElement] == '+' || lineArray[dereferencedElement] == '-' || lineArray[dereferencedElement] == '*' || lineArray[dereferencedElement] == '/'){
			if(number == 0 && numberRead == 0){
				if(lineArray[dereferencedElement] == '/'){
					break;
				}
			}
			if(operation == OperationAddition){
				if(lineArray[dereferencedElement] != '*' && lineArray[dereferencedElement] != '/'){
					if(numberOperatedOn == 0){
						number += numberRead;
					}else{
						if(lastOperation == OperationAddition){
							number += numberOperatedOn;
						}else if(lastOperation == OperationSubtraction){
							number -= numberOperatedOn;
						}
					}
				}else{
					numberOperatedOn = numberRead;
					lastOperation = operation;
				}
			}else if(operation == OperationSubtraction){
				if(lineArray[dereferencedElement] != '*' && lineArray[dereferencedElement] != '/'){
					if(numberOperatedOn == 0){
						number -= numberRead;
					}else{
						if(lastOperation == OperationAddition){
							number += numberOperatedOn;
						}else if(lastOperation == OperationSubtraction){
							number -= numberOperatedOn;
						}
					}
				}else{
					numberOperatedOn = numberRead;
					lastOperation = operation;
				}
			}else if(operation == OperationMultiplication){
				if(numberOperatedOn == 0){
					number *= numberRead;
				}else{
					numberOperatedOn *= numberRead;
				}
				if(lineArray[dereferencedElement] == '+' || lineArray[dereferencedElement] == '-'){
					if(lastOperation == OperationAddition){
						number += numberOperatedOn;
					}else if(lastOperation == OperationSubtraction){
						number -= numberOperatedOn;
					}
					numberOperatedOn = 0;
				}
			}else if(operation == OperationDivision){
				if(numberOperatedOn == 0){
					number /= numberRead;
				}else{
					numberOperatedOn /= numberRead;
				}
				if(lineArray[dereferencedElement] == '+' || lineArray[dereferencedElement] == '-'){
					if(lastOperation == OperationAddition){
						number += numberOperatedOn;
					}else if(lastOperation == OperationSubtraction){
						number -= numberOperatedOn;
					}
					numberOperatedOn = 0;
				}
			}else{
				if(number == 0){
					number = numberRead;
				}
			}
			if(lineArray[dereferencedElement] == '+'){
				operation = OperationAddition;
			}else if(lineArray[dereferencedElement] == '-'){
				operation = OperationSubtraction;
			}else if(lineArray[dereferencedElement] == '*'){
				operation = OperationMultiplication;
			}else if(lineArray[dereferencedElement] == '/'){
				operation = OperationDivision;
			}
			numberRead = 0;
			dereferencedElement++;
		}else{
			if(operation == OperationAddition){
				if(numberOperatedOn > 0){
					if(lastOperation == OperationAddition){
						number += numberOperatedOn;
					}else if(lastOperation == OperationSubtraction){
						number -= numberOperatedOn;
					}
				}
				number += numberRead;
			}else if(operation == OperationSubtraction){
				if(numberOperatedOn > 0){
					if(lastOperation == OperationAddition){
						number += numberOperatedOn;
					}else if(lastOperation == OperationSubtraction){
						number -= numberOperatedOn;
					}
				}
				number -= numberRead;
			}else if(operation == OperationMultiplication){
				if(numberOperatedOn == 0){
					number *= numberRead;
				}else{
					numberOperatedOn *= numberRead;
					if(lastOperation == OperationAddition){
						number += numberOperatedOn;
					}else if(lastOperation == OperationSubtraction){
						number -= numberOperatedOn;
					}
				}
			}else if(operation == OperationDivision){
				if(number > 0 || numberOperatedOn > 0){
					if(numberOperatedOn == 0){
						number /= numberRead;
					}else{
						numberOperatedOn /= numberRead;
						if(lastOperation == OperationAddition){
							number += numberOperatedOn;
						}else if(lastOperation == OperationSubtraction){
							number -= numberOperatedOn;
						}
					}
				}
			}else{
				if(number == 0){
					number = numberRead;
				}
			}
			break;
		}
	}
	*element = dereferencedElement;
	return number;
}
static int getARGB(const char *const lineArray, unsigned int *const element){
	unsigned int dereferencedElement = *element;
	int color = 0x00000000;
	if(lineArray[dereferencedElement] == '#'){
		dereferencedElement++;
	}
	unsigned int currentCharacter;
	for(currentCharacter = 0; currentCharacter < 8; currentCharacter++){
		color *= 16;
		if(lineArray[dereferencedElement] >= '0' && lineArray[dereferencedElement] <= '9'){
			color += lineArray[dereferencedElement];
			color -= 48;
		}else if(lineArray[dereferencedElement] >= 'A' && lineArray[dereferencedElement] <= 'F'){
			color += lineArray[dereferencedElement];
			color -= 55;
		}else if(lineArray[dereferencedElement] >= 'a' && lineArray[dereferencedElement] <= 'f'){
			color += lineArray[dereferencedElement];
			color -= 87;
		}else{
			fprintf(stderr, "%s: \'%c\' is not recognized as a hexadecimal number\n", ProgramName, lineArray[dereferencedElement]);
			color = 0x00000000;
			break;
		}
		dereferencedElement++;
	}
	if(currentCharacter == 8){
		*element = dereferencedElement;
	}
	return color;
}
static void getKeys(Display *const display, const unsigned int *const currentMonitor, const Window *const window, const char *const lineArray, unsigned int *const element, unsigned int *const key, int *const masks){
	unsigned int dereferencedElement = *element;
	*key = 0;
	int dereferencedMasks = 0;
	unsigned int lookingForValue = 1;
	while(dereferencedElement < DefaultCharactersCount){
		pushSpaces(lineArray, &dereferencedElement);
		if(lookingForValue){
			if(lineArray[dereferencedElement] >= '0' && lineArray[dereferencedElement] <= '9'){
				*key = getUnsignedDecimalNumber(display, currentMonitor, window, lineArray, &dereferencedElement);
				if((lineArray[dereferencedElement] >= 'A' && lineArray[dereferencedElement] <= 'Z') || (lineArray[dereferencedElement] >= 'a' && lineArray[dereferencedElement] <= 'z')){
					dereferencedElement--;
				}
			}else if(isVariable("Shift", lineArray, &dereferencedElement)){
				dereferencedMasks |= ShiftMask;
			}else if(isVariable("Lock", lineArray, &dereferencedElement)){
				dereferencedMasks |= LockMask;
			}else if(isVariable("Control", lineArray, &dereferencedElement)){
				dereferencedMasks |= ControlMask;
			}else if(isVariable("Mod1", lineArray, &dereferencedElement)){
				dereferencedMasks |= Mod1Mask;
			}else if(isVariable("Mod2", lineArray, &dereferencedElement)){
				dereferencedMasks |= Mod2Mask;
			}else if(isVariable("Mod3", lineArray, &dereferencedElement)){
				dereferencedMasks |= Mod3Mask;
			}else if(isVariable("Mod4", lineArray, &dereferencedElement)){
				dereferencedMasks |= Mod4Mask;
			}else if(isVariable("Mod5", lineArray, &dereferencedElement)){
				dereferencedMasks |= Mod5Mask;
			}else{
				break;
			}
			lookingForValue = 0;
		}else{
			if(lineArray[dereferencedElement] == '+'){
				dereferencedElement++;
				lookingForValue = 1;
			}else{
				break;
			}
		}
	}
	*element = dereferencedElement;
	*masks = dereferencedMasks;
	return;
}
static char *getText(const char *const lineArray, unsigned int *const element){
	unsigned int dereferencedElement = *element;
	char *text = NULL;
	unsigned int length = 0;
	{
		const char quotation = lineArray[dereferencedElement++];
		while(dereferencedElement < DefaultCharactersCount && lineArray[dereferencedElement + length] != quotation){
			length++;
		}
	}
	if(length > 0){
		if((text = (char *)malloc((length + 1) * sizeof(char)))){
			for(unsigned int currentCharacter = 0; currentCharacter < length; currentCharacter++){
				text[currentCharacter] = lineArray[dereferencedElement];
				dereferencedElement++;
			}
			dereferencedElement++;
			text[length] = '\0';
			*element = dereferencedElement;
		}else{
			fprintf(stderr, "%s: could not allocate space for text\n", ProgramName);
		}
	}
	return text;
}
static char *getCommand(const char *const lineArray, unsigned int *const element){
	unsigned int dereferencedElement = *element;
	char *command = NULL;
	unsigned int length = 0;
	{
		const char quotation = lineArray[dereferencedElement++];
		while(dereferencedElement < DefaultCharactersCount && lineArray[dereferencedElement + length] != quotation){
			length++;
		}
	}
	if(length > 0){
		if((command = (char *)malloc((length + 2) * sizeof(char)))){
			for(unsigned int currentCharacter = 0; currentCharacter < length; currentCharacter++){
				command[currentCharacter] = lineArray[dereferencedElement];
				dereferencedElement++;
			}
			dereferencedElement++;
			command[length++] = '&';
			command[length] = '\0';
			*element = dereferencedElement;
		}else{
			fprintf(stderr, "%s: could not allocate space for command\n", ProgramName);
		}
	}
	return command;
}
static unsigned int printLineError(const char *const lineArray, const unsigned int *const element, const unsigned int *const currentLine){
	unsigned int value = 0;
	if(lineArray[*element] != 10){
		unsigned int length = 0;
		while(lineArray[length] != 10){
			length++;
		}
		fprintf(stderr, "%s: line %u: \"", ProgramName, *currentLine + 1);
		for(unsigned int currentCharacter = 0; currentCharacter < length; currentCharacter++){
			fprintf(stderr, "%c", lineArray[currentCharacter]);
		}
		fprintf(stderr, "\" not recognized as an internal variable\n");
		value = 1;
	}
	return value;
}
