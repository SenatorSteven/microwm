/* getParameters.c

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

#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <xcb/xcb.h>
#include "headers/defines.h"
#include "headers/getParameters.h"

#define ISANYARGUMENT_DEC /*----*/ static bool isAnyArgument(const char *const arg)
#define PRINTCUSTOMERROR_DEC /*-*/ static void printCustomError(const char *const customString, const char *const string)

extern const char *programName;
extern const char *connectionName;
extern const char *configPath;
extern const char *errorPath;
extern bool mustOpenErrorStream;
extern FILE *errorStream;

ISANYARGUMENT_DEC;
PRINTCUSTOMERROR_DEC;

GETPARAMETERS_DEC{
	const char *const *const argumentWall = argument + argumentAmount;
	const char *arg;
	DIR *dir;
	FILE *file;
	programName = *argument;
	configPath = NULL;
	connectionName = NULL;
	errorPath = NULL;
	mustOpenErrorStream = 0;
	errorStream = StandardErrorStream;
	if(argumentAmount == 1){
		goto noConfig;
	}
	++argument;
	matchArguments:{
		arg = *argument;
		if(!configPath && (compareStrings("-c", arg) || compareStrings("--config", arg))){
			if(++argument >= argumentWall){
				printError("no config value specified");
				return false;
			}
			arg = *argument;
			if(compareStrings("-h", arg) || compareStrings("--help", arg)){
				fprintf(stdout, "%s: usage: %s --config \"/path/to/file\"\n%sif the specified file doesn't exist it will be created\n%sand it will contain the hardcoded default configuration\n", programName, programName, Tab, Tab);
				return false;
			}
			if(isAnyArgument(arg)){
				printError("no config value specified");
				return false;
			}
			configPath = arg;
			if((dir = opendir(configPath))){
				closedir(dir);
				printCustomError(configPath, "config value is directory");
				return false;
			}
			if((file = fopen(configPath, "r"))){
				fclose(file);
				goto matchArgumentLoopControl;
			}
			if((file = fopen(configPath, "w"))){
				fclose(file);
				remove(configPath);
				goto matchArgumentLoopControl;
			}
			printError("could not create config file");
			return false;
		}
		if(!errorPath && (compareStrings("-e", arg) || compareStrings("--error", arg))){
			if(++argument >= argumentWall){
				printError("no error value specified");
				return false;
			}
			arg = *argument;
			if(compareStrings("-h", arg) || compareStrings("--help", arg)){
				fprintf(stdout, "%s: usage: %s --error \"/path/to/file\"\n%sif the specified file doesn't exist it will be created\n", programName, programName, Tab);
				return false;
			}
			if(isAnyArgument(arg)){
				printError("no error value specified");
				return false;
			}
			if(compareStrings("stdout", arg)){
				errorStream = stdout;
				goto matchArgumentLoopControl;
			}
			if(compareStrings("stderr", arg)){
				errorStream = stderr;
				goto matchArgumentLoopControl;
			}
			errorPath = arg;
			if((dir = opendir(errorPath))){
				closedir(dir);
				printCustomError(errorPath, "error value is directory");
				return false;
			}
			if((file = fopen(errorPath, "r"))){
				fclose(file);
				mustOpenErrorStream = 1;
				goto matchArgumentLoopControl;
			}
			if((file = fopen(errorPath, "w"))){
				fclose(file);
				remove(errorPath);
				mustOpenErrorStream = 1;
				goto matchArgumentLoopControl;
			}
			printError("could not create error file");
			return false;
		}
		if(!connectionName && (compareStrings("-s", arg) || compareStrings("--server", arg))){
			if(++argument >= argumentWall){
				printError("no server value specified");
				return false;
			}
			arg = *argument;
			if(compareStrings("-h", arg) || compareStrings("--help", arg)){
				fprintf(stdout, "%s: usage: %s --server \"name\"\n%sthe name of the server, if running, should be something like \":0\"\n%sit can be checked with the $DISPLAY variable on a running server (no tty)\n", programName, programName, Tab, Tab);
				return false;
			}
			if(isAnyArgument(arg)){
				printError("no server value specified");
				return false;
			}
			connectionName = arg;
			goto matchArgumentLoopControl;
		}
		if(compareStrings("-h", arg) || compareStrings("--help", arg)){
			fprintf(stdout, "%s: usage: %s [parameter] [value] or %s [parameter] [--help]\n%s[-h], [--help]  %sdisplay this message\n%s[-c], [--config]%spath to config file, necessary\n%s[-e], [--error] %spath to error file, optional\n%s[-s], [--server]%sx server connection, optional\n", programName, programName, programName, Tab, Tab, Tab, Tab, Tab, Tab, Tab, Tab);
			return false;
		}
		if(compareStrings("-c", arg) || compareStrings("--config", arg)){
			printError("the config parameter has already been specified");
			return false;
		}
		if(compareStrings("-e", arg) || compareStrings("--error", arg)){
			printError("the error parameter has already been specified");
			return false;
		}
		if(compareStrings("-s", arg) || compareStrings("--server", arg)){
			printError("the server parameter has already been specified");
			return false;
		}
		printCustomError(arg, "is not recognized as program parameter, check help? [-h]");
		return false;
		matchArgumentLoopControl:{
			if(++argument < argumentWall){
				goto matchArguments;
			}
		}
	}
	if(!configPath){
		noConfig:{
			printError("no config parameter specified");
			return false;
		}
	}
	if(errorPath && compareStrings(configPath, errorPath)){
		mustOpenErrorStream = 0;
		printError("config and error files are the same");
		return false;
	}
	return true;
}
ISANYARGUMENT_DEC{
	if(compareStrings("-c", arg) || compareStrings("--config", arg) || compareStrings("-e", arg) || compareStrings("--error", arg) || compareStrings("-s", arg) || compareStrings("--server", arg)){
		return true;
	}
	return false;
}
PRINTCUSTOMERROR_DEC{
	if(!mustOpenErrorStream || (errorStream = fopen(errorPath, "a"))){
		fprintf(errorStream, "%s: \"%s\" %s\n", programName, customString, string);
		if(mustOpenErrorStream){
			fclose(errorStream);
		}
	}
	return;
}
