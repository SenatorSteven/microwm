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
#include <xcb/xcb.h>
#include <xcb/randr.h>
#include "headers/defines.h"
#include "headers/getParameters.h"
#include "headers/eventLoop.h"

#define MaxRootPropertyAmount /*-*/ 3

extern const char *programName;
extern const char *connectionName;
extern const xcb_screen_t *screen;
extern const char *errorPath;
extern bool mustOpenErrorStream;
extern FILE *errorStream;
extern xcb_connection_t *connection;
extern xcb_generic_error_t *genericError;
extern xcb_generic_reply_t *reply;

int main(const int argumentAmount, const char *const *const argument){
	if(!getParameters((unsigned int)argumentAmount, argument)){
		return 0;
	}
	{
		int screenNumber = 0;
		connection = xcb_connect_to_display_with_auth_info(connectionName, NULL, &screenNumber);
		if(printConnectionError()){
			if(xcb_connection_has_error(connection) == XCB_CONN_CLOSED_PARSE_ERR){
				if(connectionName){
					printError("invalid server name");
				}else{
					printError("no server name");
				}
			}
			goto emergencyExit;
		}
		screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data + screenNumber;
	}
	{
		const WindowAttributes valueList = XCB_EVENT_MASK_FOCUS_CHANGE | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT;
		if((genericError = xcb_request_check(connection, xcb_change_window_attributes_checked(connection, (*screen).root, XCB_CW_EVENT_MASK, &valueList)))){
			printXCBError();
			if((*genericError).error_code == XCB_ACCESS){
				printError("another window manager is running");
			}
			free(genericError);
		}
	}
	xcb_randr_select_input(connection, (*screen).root, XCB_RANDR_NOTIFY_MASK_SCREEN_CHANGE);
	{
		unsigned int rootPropertyAmount = 0;
		struct{
			xcb_atom_t p0;
			xcb_atom_t p1;
			xcb_atom_t p2;
		} property;
		{
			xcb_intern_atom_cookie_t *c;
			xcb_atom_t *atom = &property.p0;
			unsigned int currentCookie = 0;
			struct{
				xcb_intern_atom_cookie_t c0;
				xcb_intern_atom_cookie_t c1;
				xcb_intern_atom_cookie_t c2;
			} cookie;
			c = &cookie.c0;
			cookie.c0 = xcb_intern_atom(connection, false, 14, "_NET_SUPPORTED");
			cookie.c1 = xcb_intern_atom(connection, false, 13, "_NET_WM_STATE");
			cookie.c2 = xcb_intern_atom(connection, false, 24, "_NET_WM_STATE_FULLSCREEN");
			getAtomReply:{
				if(!(reply = xcb_intern_atom_reply(connection, *c, &genericError))){
					printXCBError();
					free(genericError);
					if(!rootPropertyAmount){
						discardAtomReply:{
							if(++currentCookie < MaxRootPropertyAmount){
								xcb_discard_reply(connection, (*(++c)).sequence);
								goto discardAtomReply;
							}
						}
						goto rootPropertyEmergencyExit;
					}
				}else{
					*(atom + rootPropertyAmount) = (*(xcb_intern_atom_reply_t *)reply).atom;
					++rootPropertyAmount;
					free(reply);
				}
				if(++currentCookie < MaxRootPropertyAmount){
					++c;
					goto getAtomReply;
				}
			}
		}
		if((genericError = xcb_request_check(connection, xcb_change_property_checked(connection, XCB_PROP_MODE_REPLACE, (*screen).root, property.p0, XCB_ATOM_ATOM, 32, rootPropertyAmount, &property)))){
			printXCBError();
			free(genericError);
			rootPropertyEmergencyExit:{
				printError("could not set root properties");
			}
		}
	}
	eventLoop();
	emergencyExit:{
		xcb_disconnect(connection);
	}
	return 0;
}
