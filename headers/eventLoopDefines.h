/* eventLoopDefines.h

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

#ifndef EVENTLOOPDEFINES_H
#define EVENTLOOPDEFINES_H

#define SET_KEYS_BUTTONS \
unsigned int shortcutAmount = 54; \
Shortcut shortcut[shortcutAmount]; \
{ \
	unsigned int currentShortcut = 0; \
	shortcut[currentShortcut].keycode = 12; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = FloatingModeCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 13; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = GriddingModeCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 14; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = TilingModeCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 42; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = ShowGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 43; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = ToggleGapsCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 27; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = RecascadeCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 9; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = ExitCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 80; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = MoveTopCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 88; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = MoveBottomCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 83; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = MoveLeftCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 85; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = MoveRightCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 84; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = MoveCenterCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 79; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = MoveTopLeftCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 81; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = MoveTopRightCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 87; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = MoveBottomLeftCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 89; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = MoveBottomRightCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 58; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = MoveNextMonitorCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 58; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = MovePreviousMonitorCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 111; \
	shortcut[currentShortcut].masks = ControlMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveAboveMonitorCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 116; \
	shortcut[currentShortcut].masks = ControlMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveBelowMonitorCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 113; \
	shortcut[currentShortcut].masks = ControlMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveLeftMonitorCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 114; \
	shortcut[currentShortcut].masks = ControlMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveRightMonitorCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 39; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = AddWindowToGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 26; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = RemoveWindowFromGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 38; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = ToggleWindowGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 111; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveAboveGridSlotCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 116; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveBelowGridSlotCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 114; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveNextGridSlotCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 113; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = MovePreviousGridSlotCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 111; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveUpOnGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 116; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveDownOnGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 113; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveLeftOnGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 114; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveRightOnGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 80; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = ExtendWindowUpCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 88; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = ExtendWindowDownCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 83; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = ExtendWindowLeftCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 85; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = ExtendWindowRightCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 79; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = ExtendWindowUpLeftCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 81; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = ExtendWindowUpRightCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 87; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = ExtendWindowDownLeftCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 89; \
	shortcut[currentShortcut].masks = Mod1Mask | Mod4Mask; \
	shortcut[currentShortcut].command = ExtendWindowDownRightCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 80; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = ShrinkWindowUpCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 88; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = ShrinkWindowDownCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 83; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = ShrinkWindowLeftCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 85; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = ShrinkWindowRightCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 79; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = ShrinkWindowUpLeftCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 81; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = ShrinkWindowUpRightCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 87; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = ShrinkWindowDownLeftCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 89; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = ShrinkWindowDownRightCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 95; \
	shortcut[currentShortcut].masks = None; \
	shortcut[currentShortcut].command = FullscreenCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 95; \
	shortcut[currentShortcut].masks = ShiftMask; \
	shortcut[currentShortcut].command = BigscreenCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 24; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = CloseCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 45; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = KillCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 40; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = DetachWindowCommand; \
} \
unsigned int buttonAmount = 3; \
Button button[buttonAmount]; \
{ \
	unsigned int currentButton = 0; \
	button[currentButton].button = Button4; \
	button[currentButton].masks = Mod4Mask; \
	button[currentButton].command = EnlargeGridCommand; \
	++currentButton; \
	button[currentButton].button = Button5; \
	button[currentButton].masks = Mod4Mask; \
	button[currentButton].command = ShrinkGridCommand; \
	++currentButton; \
	button[currentButton].button = Button1; \
	button[currentButton].masks = Mod4Mask; \
	button[currentButton].command = MoveCommand; \
}
#define SETUP_CONTAINERS_SEPARATORS \
if(option & TilingUseSeparatorsOption){ \
	separatorAmount = 2 * containerAmount; \
} \
Container container[containerAmount]; \
Window separator[separatorAmount]; \
{ \
	const Window rootWindow = XDefaultRootWindow(display); \
	XSelectInput(display, rootWindow, SubstructureRedirectMask); \
	{ \
		const uint16_t windowAttributesMasks = CWBackPixel | CWBorderPixel | CWColormap; \
		XVisualInfo visualInfo; \
		XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo); \
		XSetWindowAttributes windowAttributes = { \
			.background_pixel = separatorBackgroundColor, \
			.border_pixel = separatorBorderColor, \
			.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone) \
		}; \
		unsigned int currentShadow; \
		if(managementMode == FloatingManagementMode){ \
			currentShadow = shadow; \
			windowAttributes.background_pixel = floatingContainerBackgroundColor; \
		}else if(managementMode == GriddingManagementMode){ \
			currentShadow = 0; \
			windowAttributes.background_pixel = griddingContainerBackgroundColor; \
		}else{ \
			for(unsigned int currentSeparator = 0; currentSeparator < separatorAmount; ++currentSeparator){ \
				separator[currentSeparator] = XCreateWindow(display, rootWindow, 0, 0, 1, 1, separatorBorder, visualInfo.depth, InputOutput, visualInfo.visual, windowAttributesMasks, &windowAttributes); \
			} \
			separatorsExist = 1; \
			currentShadow = 0; \
			windowAttributes.background_pixel = tilingContainerBackgroundColor; \
		} \
		windowAttributes.border_pixel = containerShadowColor; \
		Window w; \
		for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){ \
			w = XCreateWindow(display, rootWindow, 0, 0, 1, 1, currentShadow, visualInfo.depth, InputOutput, visualInfo.visual, windowAttributesMasks, &windowAttributes); \
			grabContainerKeysButtons(w, shortcutAmount, shortcut, buttonAmount, button); \
			container[currentContainer].window = w; \
			container[currentContainer].subwindow = None; \
		} \
	} \
} \
if(allocatedContainerAmount){ \
	FILE *file; \
	if((file = fopen(subwindowsPath, "r"))){ \
		{ \
			Window subwindow; \
			int x; \
			int y; \
			unsigned int width; \
			unsigned int height; \
			uint32_t windowMasks; \
			uint32_t subwindowMasks; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				subwindow = getUnsignedInteger(file, ' '); \
				x = getInteger(file, ' '); \
				y = getInteger(file, ' '); \
				width = getUnsignedInteger(file, ' '); \
				height = getUnsignedInteger(file, ' '); \
				container[currentContainer].option = getUnsignedInteger(file, '\n'); \
				if(container[currentContainer].option & InPlaceContainerOption){ \
					windowMasks = EnterWindowMask; \
					subwindowMasks = StructureNotifyMask; \
					XSetWindowBorderWidth(display, container[currentContainer].window, 0); \
					if(managementMode == FloatingManagementMode){ \
						XSetWindowBackground(display, container[currentContainer].window, inGridContainerBackgroundColor); \
					} \
				}else{ \
					windowMasks = ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask; \
					subwindowMasks = ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask; \
				} \
				XSelectInput(display, container[currentContainer].window, windowMasks); \
				XSelectInput(display, subwindow, subwindowMasks); \
				XReparentWindow(display, subwindow, container[currentContainer].window, borderLeft, borderUp); \
				XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
				XResizeWindow(display, subwindow, width - borderX, height - borderY); \
				container[currentContainer].subwindow = subwindow; \
			} \
		} \
		fclose(file); \
		if((file = fopen(maximizedWindowsPath, "r"))){ \
			{ \
				Window subwindow; \
				unsigned int width; \
				unsigned int height; \
				Window window; \
				for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
					subwindow = getUnsignedInteger(file, ' '); \
					maximizedContainer[currentMonitor].subwindow = subwindow; \
					maximizedContainer[currentMonitor].oldX = getInteger(file, ' '); \
					maximizedContainer[currentMonitor].oldY = getInteger(file, ' '); \
					maximizedContainer[currentMonitor].oldWidth = getUnsignedInteger(file, ' '); \
					maximizedContainer[currentMonitor].oldHeight = getUnsignedInteger(file, ' '); \
					maximizedContainer[currentMonitor].oldBackgroundColor = getUnsignedInteger(file, ' '); \
					maximizedContainer[currentMonitor].shouldChangeProperty = getUnsignedInteger(file, '\n'); \
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
						if(container[currentContainer].subwindow == subwindow){ \
							window = container[currentContainer].window; \
							XSetWindowBorderWidth(display, window, 0); \
							if(maximizedContainer[currentMonitor].shouldChangeProperty){ \
								XSetWindowBackground(display, window, fullscreenContainerBackgroundColor); \
							}else{ \
								XSetWindowBackground(display, window, bigscreenContainerBackgroundColor); \
							} \
							width = monitors[currentMonitor].width; \
							height = monitors[currentMonitor].height; \
							XMoveResizeWindow(display, window, monitors[currentMonitor].x, monitors[currentMonitor].y, width, height); \
							XResizeWindow(display, subwindow, width - borderX, height - borderY); \
							maximizedContainer[currentMonitor].window = window; \
							break; \
						} \
					} \
				} \
			} \
			fclose(file); \
		} \
	} \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		XMapWindow(display, container[currentContainer].window); \
		XMapWindow(display, container[currentContainer].subwindow); \
	} \
	lastCreatedWindow = container[allocatedContainerAmount - 1].window; \
	if(managementMode == TilingManagementMode && option & TilingUseSeparatorsOption){ \
		if((file = fopen(separatorsPath, "r"))){ \
			fclose(file); \
		} \
	} \
}
#define KEYBUTTONPRESS \
Command c = None; \
{ \
	unsigned int current; \
	if(event.type == KeyPress){ \
		for(current = 0; current < shortcutAmount; ++current){ \
			if(shortcut[current].keycode == event.xkey.keycode && shortcut[current].masks == event.xkey.state){ \
				c = shortcut[current].command; \
				break; \
			} \
		} \
	}else{ \
		for(current = 0; current < buttonAmount; ++current){ \
			if(button[current].button == event.xbutton.button && button[current].masks == event.xbutton.state){ \
				c = button[current].command; \
				break; \
			} \
		} \
	} \
} \
if(c){ \
	if(c <= RootCommandCeiling){ \
		if(c == SystemCommand){ \
			SYSTEM_KEYPRESS \
		}else if(c == FloatingModeCommand){ \
			FLOATINGMODE_KEYPRESS \
		}else if(c == GriddingModeCommand){ \
			GRIDDINGMODE_KEYPRESS \
		}else if(c == TilingModeCommand){ \
			TILINGMODE_KEYPRESS \
		}else if(c == ShowGridCommand){ \
			SHOWGRID_KEYPRESS \
		}else if(c == EnlargeGridXCommand){ \
			ENLARGEGRIDX_KEYPRESS \
		}else if(c == EnlargeGridYCommand){ \
			ENLARGEGRIDY_KEYPRESS \
		}else if(c == EnlargeGridCommand){ \
			ENLARGEGRID_KEYPRESS \
		}else if(c == ShrinkGridXCommand){ \
			SHRINKGRIDX_KEYPRESS \
		}else if(c == ShrinkGridYCommand){ \
			SHRINKGRIDY_KEYPRESS \
		}else if(c == ShrinkGridCommand){ \
			SHRINKGRID_KEYPRESS \
		}else if(c == ToggleGapsCommand){ \
			TOGGLEGAPS_KEYPRESS \
		}else if(c == RecascadeCommand){ \
			RECASCADE_KEYPRESS \
		}else if(c == RestartCommand){ \
			mode = RestartMode; \
		}else{ \
			mode = ExitMode; \
		} \
	}else{ \
		if(c == MoveCommand){ \
			MOVE_KEYPRESS \
		}else if(c == MoveCenterCommand){ \
			MOVECENTER_KEYPRESS \
		}else if(c >= MoveTopCommand && c <= MoveBottomRightCommand){ \
			if(!containerIsMaximized(event.xany.window, maximizedContainer, monitorAmount)){ \
				if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
					if(c == MoveTopCommand){ \
						MOVETOP_KEYPRESS \
					}else if(c == MoveBottomCommand){ \
						MOVEBOTTOM_KEYPRESS \
					}else if(c == MoveLeftCommand){ \
						MOVELEFT_KEYPRESS \
					}else if(c == MoveRightCommand){ \
						MOVERIGHT_KEYPRESS \
					}else if(c == MoveTopLeftCommand){ \
						MOVETOPLEFT_KEYPRESS \
					}else if(c == MoveTopRightCommand){ \
						MOVETOPRIGHT_KEYPRESS \
					}else if(c == MoveBottomLeftCommand){ \
						MOVEBOTTOMLEFT_KEYPRESS \
					}else{ \
						MOVEBOTTOMRIGHT_KEYPRESS \
					} \
				} \
			} \
		}else if(c == MoveNextMonitorCommand || c == MovePreviousMonitorCommand){ \
			MOVENEXTPREVIOUSMONITOR_KEYPRESS \
		}else if(c == MoveAboveMonitorCommand){ \
			MOVEABOVEMONITOR_KEYPRESS \
		}else if(c == MoveBelowMonitorCommand){ \
			MOVEBELOWMONITOR_KEYPRESS \
		}else if(c == MoveLeftMonitorCommand){ \
			MOVELEFTMONITOR_KEYPRESS \
		}else if(c == MoveRightMonitorCommand){ \
			MOVERIGHTMONITOR_KEYPRESS \
		}else if(c >= AddWindowToGridCommand && c <= ToggleWindowGridCommand){ \
			if(managementMode == FloatingManagementMode){ \
				if(!containerIsMaximized(event.xany.window, maximizedContainer, monitorAmount)){ \
					if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
						if(c == AddWindowToGridCommand){ \
							if(!(container[currentContainer].option & InPlaceContainerOption)){ \
								goto addToGrid; \
							} \
						}else if(c == RemoveWindowFromGridCommand){ \
							if(container[currentContainer].option & InPlaceContainerOption){ \
								goto removeFromGrid; \
							} \
						}else{ \
							TOGGLEWINDOWGRID_KEYPRESS \
						} \
					} \
				} \
			} \
		}else if(c >= MoveAboveGridSlotCommand && c <= MoveRightOnGridCommand){ \
			if(managementMode != TilingManagementMode){ \
				if(!containerIsMaximized(event.xany.window, maximizedContainer, monitorAmount)){ \
					if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
						if(container[currentContainer].option & InPlaceContainerOption){ \
							if(c == MoveAboveGridSlotCommand){ \
								MOVEABOVEGRIDSLOT_KEYPRESS; \
							}else if(c == MoveBelowGridSlotCommand){ \
								MOVEBELOWGRIDSLOT_KEYPRESS; \
							}else if(c == MoveNextGridSlotCommand){ \
								MOVENEXTGRIDSLOT_KEYPRESS \
							}else if(c == MovePreviousGridSlotCommand){ \
								MOVEPREVIOUSGRIDSLOT_KEYPRESS \
							}else if(c == MoveUpOnGridCommand){ \
								MOVEUPONGRID_KEYPRESS \
							}else if(c == MoveDownOnGridCommand){ \
								MOVEDOWNONGRID_KEYPRESS \
							}else if(c == MoveLeftOnGridCommand){ \
								MOVELEFTONGRID_KEYPRESS \
							}else{ \
								MOVERIGHTONGRID_KEYPRESS \
							} \
						} \
					} \
				} \
			} \
		}else if(c >= ExtendWindowUpCommand && c <= ShrinkWindowDownRightCommand){ \
			if(!containerIsMaximized(event.xany.window, maximizedContainer, monitorAmount)){ \
				if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
					if(c == ExtendWindowUpCommand){ \
						EXTENDWINDOWUP_KEYPRESS \
					}else if(c == ExtendWindowDownCommand){ \
						EXTENDWINDOWDOWN_KEYPRESS \
					}else if(c == ExtendWindowLeftCommand){ \
						EXTENDWINDOWLEFT_KEYPRESS \
					}else if(c == ExtendWindowRightCommand){ \
						EXTENDWINDOWRIGHT_KEYPRESS \
					}else if(c == ExtendWindowUpLeftCommand){ \
						EXTENDWINDOWUPLEFT_KEYPRESS \
					}else if(c == ExtendWindowUpRightCommand){ \
						EXTENDWINDOWUPRIGHT_KEYPRESS \
					}else if(c == ExtendWindowDownLeftCommand){ \
						EXTENDWINDOWDOWNLEFT_KEYPRESS \
					}else if(c == ExtendWindowDownRightCommand){ \
						EXTENDWINDOWDOWNRIGHT_KEYPRESS \
					}else if(c == ShrinkWindowUpCommand){ \
						SHRINKWINDOWUP_KEYPRESS \
					}else if(c == ShrinkWindowDownCommand){ \
						SHRINKWINDOWDOWN_KEYPRESS \
					}else if(c == ShrinkWindowLeftCommand){ \
						SHRINKWINDOWLEFT_KEYPRESS \
					}else if(c == ShrinkWindowRightCommand){ \
						SHRINKWINDOWRIGHT_KEYPRESS \
					}else if(c == ShrinkWindowUpLeftCommand){ \
						SHRINKWINDOWUPLEFT_KEYPRESS \
					}else if(c == ShrinkWindowUpRightCommand){ \
						SHRINKWINDOWUPRIGHT_KEYPRESS \
					}else if(c == ShrinkWindowDownLeftCommand){ \
						SHRINKWINDOWDOWNLEFT_KEYPRESS \
					}else{ \
						SHRINKWINDOWDOWNRIGHT_KEYPRESS \
					} \
					extendShrinkWindowEmergencyExit:{} \
				} \
			} \
		}else if(c == FullscreenCommand || c == BigscreenCommand){ \
			FULLSCREEN_BIGSCREEN_KEYPRESS \
		}else if(c == CloseCommand){ \
			CLOSE_KEYPRESS \
		}else if(c == KillCommand){ \
			KILL_KEYPRESS \
		}else{ \
			DETACHWINDOW_KEYPRESS \
		} \
	} \
}
#define SYSTEM_KEYPRESS
#define FLOATINGMODE_KEYPRESS \
if(managementMode != FloatingManagementMode){ \
	{ \
		const Atom atom = None; \
		for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
			if(maximizedContainer[currentMonitor].window){ \
				if(maximizedContainer[currentMonitor].shouldChangeProperty){ \
					XChangeProperty(display, container[currentContainer].subwindow, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1); \
				} \
				maximizedContainer[currentMonitor].window = None; \
			} \
		} \
	} \
	if(separatorsExist){ \
		unsigned int currentSeparator; \
		for(currentSeparator = 0; currentSeparator < mappedSeparatorAmount; ++currentSeparator){ \
			XUnmapWindow(display, separator[currentSeparator]); \
		} \
		for(currentSeparator = 0; currentSeparator < separatorAmount; ++currentSeparator){ \
			XDestroyWindow(display, separator[currentSeparator]); \
		} \
		mappedSeparatorAmount = 0; \
		separatorsExist = 0; \
	} \
	if(allocatedContainerAmount){ \
		{ \
			const uint32_t windowMasks = ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask; \
			const uint32_t subwindowMasks = ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask; \
			const Options portWindowsFromGridding = option & FloatingPortWindowsFromGriddingOption; \
			Window window; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				if(managementMode != GriddingManagementMode || !portWindowsFromGridding){ \
					window = container[currentContainer].window; \
					XSelectInput(display, window, windowMasks); \
					XSelectInput(display, container[currentContainer].subwindow, subwindowMasks); \
					XSetWindowBorderWidth(display, window, shadow); \
					XSetWindowBackground(display, window, floatingContainerBackgroundColor); \
					XUnmapWindow(display, window); \
					XMapWindow(display, window); \
					container[currentContainer].option ^= InPlaceContainerOption; \
				}else{ \
					window = container[currentContainer].window; \
					XSetWindowBackground(display, window, inGridContainerBackgroundColor); \
					XUnmapWindow(display, window); \
					XMapWindow(display, window); \
				} \
			} \
		} \
		XRRMonitorInfo monitorInfo; \
		unsigned int width; \
		unsigned int height; \
		int x; \
		int y; \
		unsigned int subwindowWidth; \
		unsigned int subwindowHeight; \
		if(pointerInfo & ChangeToFloatingPointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
			if(option & FloatingFollowGrid){ \
				width = monitorInfo.width / gridWidth; \
				height = monitorInfo.height / gridHeight; \
			}else{ \
				width = monitorInfo.width / 2; \
				height = monitorInfo.height / 2; \
			} \
			x = monitorInfo.x + (monitorInfo.width - width) / 2 - shadow; \
			y = monitorInfo.y + (monitorInfo.height - height) / 2 - shadow; \
			subwindowWidth = width - borderX; \
			subwindowHeight = height - borderY; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				if(!(container[currentContainer].option & InPlaceContainerOption)){ \
					XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, subwindowWidth, subwindowHeight); \
					x += cascade.offsetX; \
					y += cascade.offsetY; \
				} \
			} \
		}else{ \
			XRRMonitorInfo mi; \
			for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
				mi = monitors[currentMonitor]; \
				if(option & FloatingFollowGrid){ \
					width = mi.width / gridWidth; \
					height = mi.height / gridHeight; \
				}else{ \
					width = mi.width / 2; \
					height = mi.height / 2; \
				} \
				x = mi.x + (mi.width - width) / 2; \
				y = mi.y + (mi.height - height) / 2; \
				subwindowWidth = width - borderX; \
				subwindowHeight = height - borderY; \
				for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
					if(!(container[currentContainer].option & InPlaceContainerOption)){ \
						monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
						if(monitorCompare(monitorInfo, mi)){ \
							XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
							XResizeWindow(display, container[currentContainer].subwindow, subwindowWidth, subwindowHeight); \
							x += cascade.offsetX; \
							y += cascade.offsetY; \
						} \
					} \
				} \
			} \
		} \
	} \
	managementMode = FloatingManagementMode; \
}
#define GRIDDINGMODE_KEYPRESS \
if(managementMode != GriddingManagementMode){ \
	{ \
		const Atom atom = None; \
		for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
			if(maximizedContainer[currentMonitor].window){ \
				if(maximizedContainer[currentMonitor].shouldChangeProperty){ \
					XChangeProperty(display, container[currentContainer].subwindow, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1); \
				} \
				maximizedContainer[currentMonitor].window = None; \
			} \
		} \
	} \
	if(separatorsExist){ \
		unsigned int currentSeparator; \
		for(currentSeparator = 0; currentSeparator < mappedSeparatorAmount; ++currentSeparator){ \
			XUnmapWindow(display, separator[currentSeparator]); \
		} \
		for(currentSeparator = 0; currentSeparator < separatorAmount; ++currentSeparator){ \
			XDestroyWindow(display, separator[currentSeparator]); \
		} \
		mappedSeparatorAmount = 0; \
		separatorsExist = 0; \
	} \
	if(allocatedContainerAmount){ \
		const uint32_t windowMasks = EnterWindowMask | SubstructureRedirectMask; \
		const Options portWindowsFromFloating = option & GriddingPortWindowsFromFloatingOption; \
		XRRMonitorInfo monitorInfo; \
		Window window; \
		unsigned int gridX = 0; \
		unsigned int gridY = 0; \
		int x; \
		int y; \
		if(pointerInfo & ChangeToGriddingPointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
		} \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			window = container[currentContainer].window; \
			XSetWindowBackground(display, window, griddingContainerBackgroundColor); \
			XUnmapWindow(display, window); \
			XMapWindow(display, window); \
			if(managementMode == FloatingManagementMode && portWindowsFromFloating){ \
				if(!(container[currentContainer].option & InPlaceContainerOption)){ \
					XSetWindowBorderWidth(display, window, 0); \
					container[currentContainer].option |= InPlaceContainerOption; \
					goto putInGrid; \
				} \
			}else{ \
				if(!(container[currentContainer].option & InPlaceContainerOption)){ \
					XSelectInput(display, window, windowMasks); \
					XSelectInput(display, container[currentContainer].subwindow, StructureNotifyMask); \
					XSetWindowBorderWidth(display, window, 0); \
					container[currentContainer].option |= InPlaceContainerOption; \
				} \
				putInGrid:{ \
					if(!(pointerInfo & ChangeToGriddingPointerInfo)){ \
						monitorInfo = getWindowMonitorInfo(window, monitors, monitorAmount); \
					} \
					getGridSlotData(monitorInfo, gridX, gridY, gridWidth, gridHeight, &x, &y, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
					XMoveResizeWindow(display, window, monitorInfo.x + x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
					XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - borderX, monitorInfo.height - borderY); \
					container[currentContainer].gridX = gridX; \
					container[currentContainer].gridY = gridY; \
					container[currentContainer].gridWidth = 1; \
					container[currentContainer].gridHeight = 1; \
					if(++gridX == gridWidth){ \
						gridX = 0; \
						if(++gridY == gridHeight){ \
							gridY = 0; \
						} \
					} \
				} \
			} \
		} \
	} \
	managementMode = GriddingManagementMode; \
}
#define TILINGMODE_KEYPRESS \
if(managementMode != TilingManagementMode){ \
	{ \
		const Atom atom = None; \
		for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
			if(maximizedContainer[currentMonitor].window){ \
				if(maximizedContainer[currentMonitor].shouldChangeProperty){ \
					XChangeProperty(display, container[currentContainer].subwindow, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1); \
				} \
				maximizedContainer[currentMonitor].window = None; \
			} \
		} \
	} \
	unsigned int currentSeparator; \
	{ \
		const Window rootWindow = XDefaultRootWindow(display);\
		const uint16_t windowAttributesMasks = CWBackPixel | CWBorderPixel | CWColormap; \
		XVisualInfo visualInfo; \
		XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo); \
		XSetWindowAttributes windowAttributes = { \
			.background_pixel = separatorBackgroundColor, \
			.border_pixel = separatorBorderColor, \
			.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone) \
		}; \
		for(currentSeparator = 0; currentSeparator < separatorAmount; ++currentSeparator){ \
			separator[currentSeparator] = XCreateWindow(display, rootWindow, 0, 0, 1, 1, separatorBorder, visualInfo.depth, InputOutput, visualInfo.visual, windowAttributesMasks, &windowAttributes); \
		} \
		currentSeparator = 0; \
		separatorsExist = 1; \
	} \
	if(allocatedContainerAmount){ \
		const uint32_t windowMasks = EnterWindowMask | SubstructureRedirectMask; \
		const unsigned int totalSeparatorWidth = separatorWidth + separatorBorders; \
		const unsigned int totalSeparatorWidthGaps = totalSeparatorWidth + gapsX; \
		XRRMonitorInfo monitorInfo; \
		Window window; \
		Window subwindow; \
		unsigned int middleX; \
		int x; \
		int y; \
		unsigned int separatorAmount; \
		unsigned int reservedSpace; \
		unsigned int normalWidth; \
		unsigned int abnormalWidth; \
		unsigned int height; \
		unsigned int subwindowAbnormalWidth; \
		unsigned int subwindowHeight; \
		unsigned int abnormalWidthGaps; \
		unsigned int subwindowNormalWidth; \
		unsigned int normalWidthGaps; \
		unsigned int separatorHeight; \
		if(pointerInfo & ChangeToTilingPointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
			middleX = allocatedContainerAmount / 2; \
			x = monitorInfo.x + gapsX; \
			y = monitorInfo.y + gapsY; \
			separatorAmount = allocatedContainerAmount - 1; \
			if(option & TilingUseSeparatorsOption){ \
				reservedSpace = 2 * allocatedContainerAmount * gapsX + (allocatedContainerAmount - 1) * totalSeparatorWidth; \
			}else{ \
				reservedSpace = (allocatedContainerAmount + 1) * gapsX; \
			} \
			normalWidth = (monitorInfo.width - reservedSpace) / allocatedContainerAmount; \
			abnormalWidth = (monitorInfo.width - reservedSpace) - (allocatedContainerAmount - 1) * normalWidth; \
			height = monitorInfo.height - 2 * gapsY; \
			subwindowAbnormalWidth = normalWidth - borderX; \
			subwindowHeight = height - borderY; \
			abnormalWidthGaps = abnormalWidth + gapsX; \
			subwindowNormalWidth = abnormalWidth - borderX; \
			normalWidthGaps = normalWidth + gapsX; \
			separatorHeight = height - separatorBorders; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				window = container[currentContainer].window; \
				subwindow = container[currentContainer].subwindow; \
				if(!(container[currentContainer].option & InPlaceContainerOption)){ \
					XSelectInput(display, window, windowMasks); \
					XSelectInput(display, subwindow, StructureNotifyMask); \
					XSetWindowBorderWidth(display, window, 0); \
					container[currentContainer].option |= InPlaceContainerOption; \
				} \
				XSetWindowBackground(display, window, tilingContainerBackgroundColor); \
				XUnmapWindow(display, window); \
				XMapWindow(display, window); \
				if(currentContainer == middleX){ \
					XMoveResizeWindow(display, window, x, y, abnormalWidth, height); \
					XResizeWindow(display, subwindow, subwindowAbnormalWidth, subwindowHeight); \
					x += abnormalWidthGaps; \
				}else{ \
					XMoveResizeWindow(display, window, x, y, normalWidth, height); \
					XResizeWindow(display, subwindow, subwindowNormalWidth, subwindowHeight); \
					x += normalWidthGaps; \
				} \
				if(option & TilingUseSeparatorsOption && currentContainer < separatorAmount){ \
					XMoveResizeWindow(display, separator[currentSeparator], x, y, separatorWidth, separatorHeight); \
					XMapWindow(display, separator[currentSeparator]); \
					++mappedSeparatorAmount; \
					++currentSeparator; \
					x += totalSeparatorWidthGaps; \
				} \
			} \
		}else{ \
			unsigned int windowsAssigned; \
			unsigned int currentMonitorContainer; \
			for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
				windowsAssigned = 0; \
				for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
					monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					if(monitorCompare(monitorInfo, monitors[currentMonitor])){ \
						++windowsAssigned; \
					} \
				} \
				if(windowsAssigned){ \
					currentMonitorContainer = 0; \
					middleX = windowsAssigned / 2; \
					x = monitors[currentMonitor].x + gapsX; \
					y = monitors[currentMonitor].y + gapsY; \
					separatorAmount = windowsAssigned - 1; \
					if(option & TilingUseSeparatorsOption){ \
						reservedSpace = 2 * windowsAssigned * gapsX + separatorAmount * totalSeparatorWidth; \
					}else{ \
						reservedSpace = (windowsAssigned + 1) * gapsX; \
					} \
					normalWidth = (monitors[currentMonitor].width - reservedSpace) / windowsAssigned; \
					abnormalWidth = (monitors[currentMonitor].width - reservedSpace) - separatorAmount * normalWidth; \
					height = monitors[currentMonitor].height - 2 * gapsY; \
					subwindowAbnormalWidth = normalWidth - borderX; \
					subwindowHeight = height - borderY; \
					abnormalWidthGaps = abnormalWidth + gapsX; \
					subwindowNormalWidth = abnormalWidth - borderX; \
					normalWidthGaps = normalWidth + gapsX; \
					separatorHeight = height - separatorBorders; \
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
						monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
						if(monitorCompare(monitorInfo, monitors[currentMonitor])){ \
							window = container[currentContainer].window; \
							subwindow = container[currentContainer].subwindow; \
							if(!(container[currentContainer].option & InPlaceContainerOption)){ \
								XSelectInput(display, window, windowMasks); \
								XSelectInput(display, subwindow, StructureNotifyMask); \
								XSetWindowBorderWidth(display, window, 0); \
								container[currentContainer].option |= InPlaceContainerOption; \
							} \
							XSetWindowBackground(display, window, tilingContainerBackgroundColor); \
							XUnmapWindow(display, window); \
							XMapWindow(display, window); \
							if(currentMonitorContainer == middleX){ \
								XMoveResizeWindow(display, window, x, y, abnormalWidth, height); \
								XResizeWindow(display, subwindow, subwindowAbnormalWidth, subwindowHeight); \
								x += abnormalWidthGaps; \
							}else{ \
								XMoveResizeWindow(display, window, x, y, normalWidth, height); \
								XResizeWindow(display, subwindow, subwindowNormalWidth, subwindowHeight); \
								x += normalWidthGaps; \
							} \
							if(option & TilingUseSeparatorsOption && currentMonitorContainer < separatorAmount){ \
								XMoveResizeWindow(display, separator[currentSeparator], x, y, separatorWidth, separatorHeight); \
								XMapWindow(display, separator[currentSeparator]); \
								++mappedSeparatorAmount; \
								++currentSeparator; \
								x += totalSeparatorWidthGaps; \
							} \
							++currentMonitorContainer; \
						} \
					} \
				} \
			} \
		} \
	} \
	managementMode = TilingManagementMode; \
}
#define SHOWGRID_KEYPRESS \
if(gridMapped){ \
	for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
		XUnmapSubwindows(display, grid[currentMonitor]); \
		XUnmapWindow(display, grid[currentMonitor]); \
	} \
	gridMapped = 0; \
}else{ \
	if(!gridExists){ \
		createGrid(monitors, monitorAmount, gridWidth, gridHeight, gridSubwindowBorderColor, gridSubwindowBackgroundColor, grid); \
		gridExists = 1; \
	} \
	for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
		XLowerWindow(display, grid[currentMonitor]); \
		XMapWindow(display, grid[currentMonitor]); \
		XMapSubwindows(display, grid[currentMonitor]); \
	} \
	gridMapped = 1; \
}
#define ENLARGEGRIDX_KEYPRESS \
if(gridWidth < maxGridWidth){ \
	++gridWidth; \
	goto deleteGrid; \
}
#define ENLARGEGRIDY_KEYPRESS \
if(gridHeight < maxGridHeight){ \
	++gridHeight; \
	goto deleteGrid; \
}
#define ENLARGEGRID_KEYPRESS \
if(gridWidth < maxGridWidth || gridHeight < maxGridHeight){ \
	if(gridWidth < maxGridWidth){ \
		++gridWidth; \
	} \
	if(gridHeight < maxGridHeight){ \
		++gridHeight; \
	} \
	goto deleteGrid; \
}
#define SHRINKGRIDX_KEYPRESS \
if(gridWidth > 1){ \
	--gridWidth; \
	goto deleteGrid; \
}
#define SHRINKGRIDY_KEYPRESS \
if(gridHeight > 1){ \
	--gridHeight; \
	goto deleteGrid; \
}
#define SHRINKGRID_KEYPRESS \
if(gridWidth > 1 || gridHeight > 1){ \
	if(gridWidth > 1){ \
		--gridWidth; \
	} \
	if(gridHeight > 1){ \
		--gridHeight; \
	} \
	deleteGrid:{ \
		if(gridExists){ \
			{ \
				unsigned int currentMonitor; \
				if(gridMapped){ \
					for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
						XUnmapSubwindows(display, grid[currentMonitor]); \
						XUnmapWindow(display, grid[currentMonitor]); \
					} \
				} \
				for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
					XDestroySubwindows(display, grid[currentMonitor]); \
					XDestroyWindow(display, grid[currentMonitor]); \
				} \
			} \
			if(gridMapped){ \
				createGrid(monitors, monitorAmount, gridWidth, gridHeight, gridSubwindowBorderColor, gridSubwindowBackgroundColor, grid); \
				for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
					XLowerWindow(display, grid[currentMonitor]); \
					XMapWindow(display, grid[currentMonitor]); \
					XMapSubwindows(display, grid[currentMonitor]); \
				} \
				gridExists = 1; \
			}else{ \
				gridExists = 0; \
			} \
		} \
		if(managementMode != TilingManagementMode){ \
			XRRMonitorInfo monitorInfo; \
			int x; \
			int y; \
			int x1; \
			int y1; \
			unsigned int width; \
			unsigned int height; \
			unsigned int currentMonitor; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				if(container[currentContainer].option & InPlaceContainerOption){ \
					monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					if(container[currentContainer].gridX + container[currentContainer].gridWidth - 1 == gridWidth){ \
						if(!--container[currentContainer].gridWidth){ \
							--container[currentContainer].gridX; \
							++container[currentContainer].gridWidth; \
						} \
					} \
					if(container[currentContainer].gridY + container[currentContainer].gridHeight - 1 == gridHeight){ \
						if(!--container[currentContainer].gridHeight){ \
							--container[currentContainer].gridY; \
							++container[currentContainer].gridHeight; \
						} \
					} \
					getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, NULL, NULL); \
					getGridSlotData(monitorInfo, container[currentContainer].gridX + container[currentContainer].gridWidth - 1, container[currentContainer].gridY + container[currentContainer].gridHeight - 1, gridWidth, gridHeight, &x1, &y1, &width, &height); \
					width += x1 - x; \
					height += y1 - y; \
					for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
						if(maximizedContainer[currentMonitor].window == container[currentContainer].window){ \
							maximizedContainer[currentMonitor].oldX = monitorInfo.x + x; \
							maximizedContainer[currentMonitor].oldY = monitorInfo.y + y; \
							maximizedContainer[currentMonitor].oldWidth = width; \
							maximizedContainer[currentMonitor].oldHeight = height; \
							goto continueGridLoop; \
						} \
					} \
					XMoveResizeWindow(display, container[currentContainer].window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
					continueGridLoop:{} \
				} \
			} \
		} \
	} \
}
#define TOGGLEGAPS_KEYPRESS \
int offsetX; \
int offsetY; \
if(option & TilingUseGapsOption){ \
	offsetX = tilingGapsX; \
	offsetY = tilingGapsY; \
	gapsX = 0; \
	gapsY = 0; \
	option ^= TilingUseGapsOption; \
}else{ \
	offsetX = -tilingGapsX; \
	offsetY = -tilingGapsY; \
	gapsX = tilingGapsX; \
	gapsY = tilingGapsY; \
	option |= TilingUseGapsOption; \
} \
if(managementMode == TilingManagementMode){ \
	const int lastOffsetX = offsetX + gapsX; \
	const int lastOffsetY = offsetY + gapsY; \
	XRRMonitorInfo monitorInfo; \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
		monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
		if(windowAttributes.x + windowAttributes.width == monitorInfo.x + monitorInfo.width - lastOffsetX){ \
			windowAttributes.width += 2 * offsetX; \
		}else{ \
			windowAttributes.width += offsetX; \
		} \
		if(windowAttributes.y + windowAttributes.height == monitorInfo.y + monitorInfo.height - lastOffsetY){ \
			windowAttributes.height += 2 * offsetY; \
		}else{ \
			windowAttributes.height += offsetY; \
		} \
		XMoveResizeWindow(display, container[currentContainer].window, windowAttributes.x - offsetX, windowAttributes.y - offsetY, windowAttributes.width, windowAttributes.height); \
		XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
	} \
}
#define RECASCADE_KEYPRESS \
if(managementMode == FloatingManagementMode){ \
	if(allocatedContainerAmount){ \
		const CascadeOptions overrideGridWindows = cascade.options & OverrideGridWindowsCascadeOption; \
		const CascadeOptions overrideMaximizedWindows = cascade.options & OverrideMaximizedWindowsCascadeOption; \
		XRRMonitorInfo monitorInfo; \
		unsigned int width; \
		unsigned int height; \
		if(pointerInfo & RecascadePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
			if(option & FloatingFollowGrid){ \
				width = monitorInfo.width / gridWidth; \
				height = monitorInfo.height / gridHeight; \
			}else{ \
				width = monitorInfo.width / 2; \
				height = monitorInfo.height / 2; \
			} \
			int x = monitorInfo.x + (monitorInfo.width - width) / 2 - shadow; \
			int y = monitorInfo.y + (monitorInfo.height - height) / 2 - shadow; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				if(overrideGridWindows && container[currentContainer].option & InPlaceContainerOption){ \
					XSetWindowBorderWidth(display, container[currentContainer].window, shadow); \
					XSetWindowBackground(display, container[currentContainer].window, floatingContainerBackgroundColor); \
					XUnmapWindow(display, container[currentContainer].window); \
					XMapWindow(display, container[currentContainer].window); \
					XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
					container[currentContainer].option ^= InPlaceContainerOption; \
					x += cascade.offsetX; \
					y += cascade.offsetY; \
				}else if(overrideMaximizedWindows && containerIsMaximized(container[currentContainer].window, maximizedContainer, monitorAmount)){ \
					unmaximizeContainer(container[currentContainer].window, monitorAmount, floatingContainerBackgroundColor, shadow, borderX, borderY, maximizedContainer); \
					XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
					x += cascade.offsetX; \
					y += cascade.offsetY; \
				}else if(!(container[currentContainer].option & InPlaceContainerOption || containerIsMaximized(container[currentContainer].window, maximizedContainer, monitorAmount))){ \
					XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
					x += cascade.offsetX; \
					y += cascade.offsetY; \
				} \
			} \
		}else{ \
			XRRMonitorInfo mi; \
			int x; \
			int y; \
			for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
				mi = monitors[currentMonitor]; \
				if(option & FloatingFollowGrid){ \
					width = mi.width / gridWidth; \
					height = mi.height / gridHeight; \
				}else{ \
					width = mi.width / 2; \
					height = mi.height / 2; \
				} \
				x = mi.x + (mi.width - width) / 2 - shadow; \
				y = mi.y + (mi.height - height) / 2 - shadow; \
				for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
					monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					if(monitorCompare(monitorInfo, mi)){ \
						if(overrideGridWindows && container[currentContainer].option & InPlaceContainerOption){ \
							XSetWindowBorderWidth(display, container[currentContainer].window, shadow); \
							XSetWindowBackground(display, container[currentContainer].window, floatingContainerBackgroundColor); \
							XUnmapWindow(display, container[currentContainer].window); \
							XMapWindow(display, container[currentContainer].window); \
							XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
							XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
							container[currentContainer].option ^= InPlaceContainerOption; \
							x += cascade.offsetX; \
							y += cascade.offsetY; \
						}else if(overrideMaximizedWindows && containerIsMaximized(container[currentContainer].window, maximizedContainer, monitorAmount)){ \
							unmaximizeContainer(container[currentContainer].window, monitorAmount, floatingContainerBackgroundColor, shadow, borderX, borderY, maximizedContainer); \
							XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
							XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
							x += cascade.offsetX; \
							y += cascade.offsetY; \
						}else if(!(container[currentContainer].option & InPlaceContainerOption || containerIsMaximized(container[currentContainer].window, maximizedContainer, monitorAmount))){ \
							XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
							XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
							x += cascade.offsetX; \
							y += cascade.offsetY; \
						} \
					} \
				} \
			} \
		} \
	} \
}
#define MOVE_KEYPRESS \
if(managementMode == FloatingManagementMode){ \
	if(!containerIsMaximized(event.xany.window, maximizedContainer, monitorAmount)){ \
		if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
			if(!(container[currentContainer].option & InPlaceContainerOption)){ \
				XSelectInput(display, XDefaultRootWindow(display), ButtonReleaseMask | ButtonMotionMask | SubstructureRedirectMask); \
				XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
				if(event.xbutton.subwindow){ \
					if(option & FloatingMinimalMoveOption){ \
						motionContainer.x = windowAttributes.x + shadow - moveResizeWindowBorder; \
						motionContainer.y = windowAttributes.y + shadow - moveResizeWindowBorder; \
						XMoveResizeWindow(display, moveResizeWindow, motionContainer.x, motionContainer.y, windowAttributes.width, windowAttributes.height); \
						XMapRaised(display, moveResizeWindow); \
						motionContainer.window = moveResizeWindow; \
						moveResizeWindow = event.xany.window; \
						const unsigned int b = shadow; \
						shadow = moveResizeWindowBorder; \
						moveResizeWindowBorder = b; \
					}else{ \
						motionContainer.window = event.xany.window; \
						motionContainer.x = windowAttributes.x; \
						motionContainer.y = windowAttributes.y; \
					} \
					motionContainer.width = windowAttributes.width; \
					motionContainer.height = windowAttributes.height; \
					motionContainer.pointerOffsetX = event.xbutton.x + shadow; \
					motionContainer.pointerOffsetY = event.xbutton.y + shadow; \
					motionContainer.positionOffset = 0; \
					motionContainer.action = MoveMotionAction; \
				}else{ \
					motionContainer.subwindow = container[currentContainer].subwindow; \
					if(option & FloatingMinimalResizeOption){ \
						XSelectInput(display, motionContainer.subwindow, ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask); \
						motionContainer.x = windowAttributes.x - moveResizeWindowBorder; \
						motionContainer.y = windowAttributes.y - moveResizeWindowBorder; \
						XMoveResizeWindow(display, moveResizeWindow, motionContainer.x + shadow, motionContainer.y + shadow, windowAttributes.width, windowAttributes.height); \
						XMapRaised(display, moveResizeWindow); \
						motionContainer.window = moveResizeWindow; \
						moveResizeWindow = event.xany.window; \
						motionContainer.pointerOffsetX = event.xbutton.x + shadow + moveResizeWindowBorder; \
						motionContainer.pointerOffsetY = event.xbutton.y + shadow + moveResizeWindowBorder; \
						motionContainer.positionOffset = shadow; \
					}else{ \
						motionContainer.window = event.xany.window; \
						motionContainer.x = windowAttributes.x; \
						motionContainer.y = windowAttributes.y; \
						motionContainer.pointerOffsetX = event.xbutton.x + shadow; \
						motionContainer.pointerOffsetY = event.xbutton.y + shadow; \
						motionContainer.positionOffset = 0; \
					} \
					motionContainer.width = windowAttributes.width; \
					motionContainer.height = windowAttributes.height; \
					motionContainer.action = ResizeMotionAction; \
					if(event.xbutton.y < (int)borderUp){ \
						if(event.xbutton.x < (int)borderLeft){ \
							motionContainer.subaction = UpLeftResizeMotionSubaction; \
						}else if(event.xbutton.x < windowAttributes.width - (int)borderRight){ \
							motionContainer.subaction = UpResizeMotionSubaction; \
						}else{ \
							motionContainer.subaction = UpRightResizeMotionSubaction; \
						} \
					}else if(event.xbutton.y < windowAttributes.height - (int)borderDown){ \
						if(event.xbutton.x < (int)borderLeft){ \
							motionContainer.subaction = LeftResizeMotionSubaction; \
						}else{ \
							motionContainer.subaction = RightResizeMotionSubaction; \
						} \
					}else{ \
						if(event.xbutton.x < (int)borderLeft){ \
							motionContainer.subaction = DownLeftResizeMotionSubaction; \
						}else if(event.xbutton.x < windowAttributes.width - (int)borderRight){ \
							motionContainer.subaction = DownResizeMotionSubaction; \
						}else{ \
							motionContainer.subaction = DownRightResizeMotionSubaction; \
						} \
					} \
				} \
				motionContainer.options = CanActOption; \
			} \
		} \
	} \
}
#define MOVECENTER_KEYPRESS \
if(managementMode != TilingManagementMode){ \
	if(!containerIsMaximized(event.xany.window, maximizedContainer, monitorAmount)){ \
		if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
			if(container[currentContainer].option & InPlaceContainerOption){ \
				XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
				{ \
					int x; \
					int y; \
					getGridSlotData(monitorInfo, gridWidth / 2, gridHeight / 2, gridWidth, gridHeight, &x, &y, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
				} \
				XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - borderX, monitorInfo.height - borderY); \
				container[currentContainer].gridX = gridWidth / 2; \
				container[currentContainer].gridY = gridHeight / 2; \
				container[currentContainer].gridWidth = 1; \
				container[currentContainer].gridHeight = 1; \
			}else{ \
				unsigned int width; \
				unsigned int height; \
				{ \
					XRRMonitorInfo monitorInfo; \
					if(pointerInfo & MovePointerInfo){ \
						monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
					}else{ \
						monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
					} \
					if(option & FloatingFollowGrid){ \
						width = monitorInfo.width / gridWidth; \
						height = monitorInfo.height / gridHeight; \
					}else{ \
						width = monitorInfo.width / 2; \
						height = monitorInfo.height / 2; \
					} \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - width) / 2 - shadow, monitorInfo.y + (monitorInfo.height - height) / 2 - shadow, width, height); \
				} \
				XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
			} \
		} \
	} \
}
#define MOVETOP_KEYPRESS \
if(managementMode == TilingManagementMode){ \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	{ \
		int y; \
		getGridSlotData(monitorInfo, 0, 0, gridWidth, gridHeight, NULL, &y, NULL, (unsigned int *)&monitorInfo.height); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - borderX, monitorInfo.height - borderY); \
	container[currentContainer].gridX = 0; \
	container[currentContainer].gridY = 0; \
	container[currentContainer].gridWidth = gridWidth; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	unsigned int width; \
	unsigned int height; \
	{ \
		XRRMonitorInfo monitorInfo; \
		if(pointerInfo & MovePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
		}else{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
		} \
		width = monitorInfo.width; \
		if(option & FloatingFollowGrid){ \
			height = monitorInfo.height / gridHeight; \
		}else{ \
			height = monitorInfo.height / 2; \
		} \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x - shadow, monitorInfo.y - shadow, width, height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
}
#define MOVEBOTTOM_KEYPRESS \
if(managementMode == TilingManagementMode){ \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	{ \
		int y; \
		getGridSlotData(monitorInfo, 0, gridHeight - 1, gridWidth, gridHeight, NULL, &y, NULL, (unsigned int *)&monitorInfo.height); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - borderX, monitorInfo.height - borderY); \
	container[currentContainer].gridX = 0; \
	container[currentContainer].gridY = gridHeight - 1; \
	container[currentContainer].gridWidth = gridWidth; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	unsigned int width; \
	unsigned int height; \
	{ \
		XRRMonitorInfo monitorInfo; \
		if(pointerInfo & MovePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
		}else{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
		} \
		width = monitorInfo.width; \
		if(option & FloatingFollowGrid){ \
			height = monitorInfo.height / gridHeight; \
		}else{ \
			height = monitorInfo.height / 2; \
		} \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x - shadow, monitorInfo.y + monitorInfo.height - height - shadow, width, height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
}
#define MOVELEFT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	{ \
		int x; \
		getGridSlotData(monitorInfo, 0, 0, gridWidth, gridHeight, &x, NULL, (unsigned int *)&monitorInfo.width, NULL); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - borderX, monitorInfo.height - borderY); \
	container[currentContainer].gridX = 0; \
	container[currentContainer].gridY = 0; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = gridHeight; \
}else{ \
	unsigned int width; \
	unsigned int height; \
	{ \
		XRRMonitorInfo monitorInfo; \
		if(pointerInfo & MovePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
		}else{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
		} \
		if(option & FloatingFollowGrid){ \
			width = monitorInfo.width / gridWidth; \
		}else{ \
			width = monitorInfo.width / 2; \
		} \
		height = monitorInfo.height; \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x - shadow, monitorInfo.y - shadow, width, height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
}
#define MOVERIGHT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	{ \
		int x; \
		getGridSlotData(monitorInfo, gridWidth - 1, 0, gridWidth, gridHeight, &x, NULL, (unsigned int *)&monitorInfo.width, NULL); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - borderX, monitorInfo.height - borderY); \
	container[currentContainer].gridX = gridWidth - 1; \
	container[currentContainer].gridY = 0; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = gridHeight; \
}else{ \
	unsigned int width; \
	unsigned int height; \
	{ \
		XRRMonitorInfo monitorInfo; \
		if(pointerInfo & MovePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
		}else{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
		} \
		if(option & FloatingFollowGrid){ \
			width = monitorInfo.width / gridWidth; \
		}else{ \
			width = monitorInfo.width / 2; \
		} \
		height = monitorInfo.height; \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - shadow, monitorInfo.y - shadow, width, height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
}
#define MOVETOPLEFT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	getGridSlotData(monitorInfo, 0, 0, gridWidth, gridHeight, NULL, NULL, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - borderX, monitorInfo.height - borderY); \
	container[currentContainer].gridX = 0; \
	container[currentContainer].gridY = 0; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	unsigned int width; \
	unsigned int height; \
	{ \
		XRRMonitorInfo monitorInfo; \
		if(pointerInfo & MovePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
		}else{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
		} \
		if(option & FloatingFollowGrid){ \
			width = monitorInfo.width / gridWidth; \
			height = monitorInfo.height / gridHeight; \
		}else{ \
			width = monitorInfo.width / 2; \
			height = monitorInfo.height / 2; \
		} \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x - shadow, monitorInfo.y - shadow, width, height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
}
#define MOVETOPRIGHT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	{ \
		int x; \
		getGridSlotData(monitorInfo, gridWidth - 1, 0, gridWidth, gridHeight, &x, NULL, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - borderX, monitorInfo.height - borderY); \
	container[currentContainer].gridX = gridWidth - 1; \
	container[currentContainer].gridY = 0; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	unsigned int width; \
	unsigned int height; \
	{ \
		XRRMonitorInfo monitorInfo; \
		if(pointerInfo & MovePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
		}else{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
		} \
		if(option & FloatingFollowGrid){ \
			width = monitorInfo.width / gridWidth; \
			height = monitorInfo.height / gridHeight; \
		}else{ \
			width = monitorInfo.width / 2; \
			height = monitorInfo.height / 2; \
		} \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - shadow, monitorInfo.y - shadow, width, height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
}
#define MOVEBOTTOMLEFT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	{ \
		int y; \
		getGridSlotData(monitorInfo, 0, gridHeight - 1, gridWidth, gridHeight, NULL, &y, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - borderX, monitorInfo.height - borderY); \
	container[currentContainer].gridX = 0; \
	container[currentContainer].gridY = gridHeight - 1; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	unsigned int width; \
	unsigned int height; \
	{ \
		XRRMonitorInfo monitorInfo; \
		if(pointerInfo & MovePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
		}else{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
		} \
		if(option & FloatingFollowGrid){ \
			width = monitorInfo.width / gridWidth; \
			height = monitorInfo.height / gridHeight; \
		}else{ \
			width = monitorInfo.width / 2; \
			height = monitorInfo.height / 2; \
		} \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x - shadow, monitorInfo.y + monitorInfo.height - height - shadow, width, height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
}
#define MOVEBOTTOMRIGHT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	{ \
		int x; \
		int y; \
		getGridSlotData(monitorInfo, gridWidth - 1, gridHeight - 1, gridWidth, gridHeight, &x, &y, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - borderX, monitorInfo.height - borderY); \
	container[currentContainer].gridX = gridWidth - 1; \
	container[currentContainer].gridY = gridHeight - 1; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	unsigned int width; \
	unsigned int height; \
	{ \
		XRRMonitorInfo monitorInfo; \
		if(pointerInfo & MovePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
		}else{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
		} \
		if(option & FloatingFollowGrid){ \
			width = monitorInfo.width / gridWidth; \
			height = monitorInfo.height / gridHeight; \
		}else{ \
			width = monitorInfo.width / 2; \
			height = monitorInfo.height / 2; \
		} \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - shadow, monitorInfo.y + monitorInfo.height - height - shadow, width, height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
}
#define MOVENEXTPREVIOUSMONITOR_KEYPRESS \
if(!containerIsMaximized(event.xany.window, maximizedContainer, monitorAmount)){ \
	if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
		bool next; \
		if(c == MoveNextMonitorCommand){ \
			next = 1; \
		}else{ \
			next = 0; \
		} \
		const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
		for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
			if(monitorCompare(monitors[currentMonitor], monitorInfo)){ \
				if(next){ \
					if(++currentMonitor < monitorAmount){ \
						if(managementMode == TilingManagementMode){ \
\
\
\
							\
\
\
\
						}else if(container[currentContainer].option & InPlaceContainerOption){ \
							moveContainerToGridPosition(container[currentContainer], monitors[currentMonitor], gridWidth, gridHeight, borderX, borderY); \
						}else{ \
							unsigned int width; \
							unsigned int height; \
							if(option & FloatingFollowGrid){ \
								width = monitors[currentMonitor].width / gridWidth; \
								height = monitors[currentMonitor].height / gridHeight; \
							}else{ \
								width = monitors[currentMonitor].width / 2; \
								height = monitors[currentMonitor].height / 2; \
							} \
							XMoveResizeWindow(display, event.xany.window, monitors[currentMonitor].x + (monitors[currentMonitor].width - width) / 2 - shadow, monitors[currentMonitor].y + (monitors[currentMonitor].height - height) / 2 - shadow, width, height); \
							XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
						} \
					} \
				}else{ \
					if((int)--currentMonitor >= 0){ \
						if(managementMode == TilingManagementMode){ \
\
\
\
							\
\
\
\
						}else if(container[currentContainer].option & InPlaceContainerOption){ \
							moveContainerToGridPosition(container[currentContainer], monitors[currentMonitor], gridWidth, gridHeight, borderX, borderY); \
						}else{ \
							monitors[currentMonitor] = monitors[currentMonitor]; \
							unsigned int width; \
							unsigned int height; \
							if(option & FloatingFollowGrid){ \
								width = monitors[currentMonitor].width / gridWidth; \
								height = monitors[currentMonitor].height / gridHeight; \
							}else{ \
								width = monitors[currentMonitor].width / 2; \
								height = monitors[currentMonitor].height / 2; \
							} \
							XMoveResizeWindow(display, event.xany.window, monitors[currentMonitor].x + (monitors[currentMonitor].width - width) / 2 - shadow, monitors[currentMonitor].y + (monitors[currentMonitor].height - height) / 2 - shadow, width, height); \
							XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
						} \
					} \
				} \
			} \
		} \
	} \
}
#define MOVEABOVEMONITOR_KEYPRESS \
const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
if(monitorInfo.y){ \
	if(!containerIsMaximized(event.xany.window, maximizedContainer, monitorAmount)){ \
		if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
			for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
				if(monitors[currentMonitor].x == monitorInfo.x && monitors[currentMonitor].y + monitors[currentMonitor].height == monitorInfo.y){ \
					if(managementMode == TilingManagementMode){ \
\
\
\
						\
\
\
\
					}else if(container[currentContainer].option & InPlaceContainerOption){ \
						moveContainerToGridPosition(container[currentContainer], monitors[currentMonitor], gridWidth, gridHeight, borderX, borderY); \
					}else{ \
						moveContainerToMonitor(monitorInfo, monitors[currentMonitor], event.xany.window, container[currentContainer].subwindow, shadow, borderX, borderY); \
					} \
					break; \
				} \
			} \
		} \
	} \
}
#define MOVEBELOWMONITOR_KEYPRESS \
const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
if(monitorInfo.y + monitorInfo.height < XDisplayHeight(display, XDefaultScreen(display))){ \
	if(!containerIsMaximized(event.xany.window, maximizedContainer, monitorAmount)){ \
		if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
			for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
				if(monitors[currentMonitor].x == monitorInfo.x && monitors[currentMonitor].y == monitorInfo.y + monitorInfo.height){ \
					if(managementMode == TilingManagementMode){ \
\
\
\
						\
\
\
\
					}else if(container[currentContainer].option & InPlaceContainerOption){ \
						moveContainerToGridPosition(container[currentContainer], monitors[currentMonitor], gridWidth, gridHeight, borderX, borderY); \
					}else{ \
						moveContainerToMonitor(monitorInfo, monitors[currentMonitor], event.xany.window, container[currentContainer].subwindow, shadow, borderX, borderY); \
					} \
					break; \
				} \
			} \
		} \
	} \
}
#define MOVELEFTMONITOR_KEYPRESS \
const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
if(monitorInfo.x){ \
	if(!containerIsMaximized(event.xany.window, maximizedContainer, monitorAmount)){ \
		if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
			for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
				if(monitors[currentMonitor].x + monitors[currentMonitor].width == monitorInfo.x && monitors[currentMonitor].y == monitorInfo.y){ \
					if(managementMode == TilingManagementMode){ \
\
\
\
						\
\
\
\
					}else if(container[currentContainer].option & InPlaceContainerOption){ \
						moveContainerToGridPosition(container[currentContainer], monitors[currentMonitor], gridWidth, gridHeight, borderX, borderY); \
					}else{ \
						moveContainerToMonitor(monitorInfo, monitors[currentMonitor], event.xany.window, container[currentContainer].subwindow, shadow, borderX, borderY); \
					} \
					break; \
				} \
			} \
		} \
	} \
}
#define MOVERIGHTMONITOR_KEYPRESS \
const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
if(monitorInfo.x + monitorInfo.width < XDisplayWidth(display, XDefaultScreen(display))){ \
	if(!containerIsMaximized(event.xany.window, maximizedContainer, monitorAmount)){ \
		if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
			for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
				if(monitors[currentMonitor].x == monitorInfo.x + monitorInfo.width && monitors[currentMonitor].y == monitorInfo.y){ \
					if(managementMode == TilingManagementMode){ \
\
\
\
						\
\
\
\
					}else if(container[currentContainer].option & InPlaceContainerOption){ \
						moveContainerToGridPosition(container[currentContainer], monitors[currentMonitor], gridWidth, gridHeight, borderX, borderY); \
					}else{ \
						moveContainerToMonitor(monitorInfo, monitors[currentMonitor], event.xany.window, container[currentContainer].subwindow, shadow, borderX, borderY); \
					} \
					break; \
				} \
			} \
		} \
	} \
}
#define TOGGLEWINDOWGRID_KEYPRESS \
if(!(container[currentContainer].option & InPlaceContainerOption)){ \
	addToGrid:{ \
		XSelectInput(display, event.xany.window, EnterWindowMask | SubstructureRedirectMask); \
		XSelectInput(display, container[currentContainer].subwindow, StructureNotifyMask); \
		XSetWindowBorderWidth(display, event.xany.window, 0); \
		XSetWindowBackground(display, event.xany.window, inGridContainerBackgroundColor); \
		XUnmapWindow(display, event.xany.window); \
		XMapRaised(display, event.xany.window); \
		unsigned int positionX; \
		unsigned int positionY; \
		{ \
			unsigned int width; \
			unsigned int height; \
			{ \
				int x; \
				int y; \
				XRRMonitorInfo monitorInfo; \
				if(pointerInfo & AddToGridPointerInfo){ \
					monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
				}else{ \
					monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
				} \
				if(option & FloatingFollowGrid){ \
					if(defaultGridPosition == CenterDefaultGridPosition){ \
						positionX = gridWidth / 2; \
						positionY = gridHeight / 2; \
					}else if(defaultGridPosition == TopLeftDefaultGridPosition){ \
						positionX = 0; \
						positionY = 0; \
					}else if(defaultGridPosition == TopRightDefaultGridPosition){ \
						positionX = gridWidth - 1; \
						positionY = 0; \
					}else if(defaultGridPosition == BottomLeftDefaultGridPosition){ \
						positionX = 0; \
						positionY = gridHeight - 1; \
					}else{ \
						positionX = gridWidth - 1; \
						positionY = gridHeight - 1; \
					} \
				}else{ \
					positionX = 0; \
					positionY = 0; \
				} \
				getGridSlotData(monitorInfo, positionX, positionY, gridWidth, gridHeight, &x, &y, &width, &height); \
				XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
			} \
			XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
		} \
		container[currentContainer].option |= InPlaceContainerOption; \
		container[currentContainer].gridX = positionX; \
		container[currentContainer].gridY = positionY; \
		container[currentContainer].gridWidth = 1; \
		container[currentContainer].gridHeight = 1; \
	} \
}else{ \
	removeFromGrid:{ \
		XSelectInput(display, event.xany.window, ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask); \
		XSelectInput(display, container[currentContainer].subwindow, ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask); \
		XSetWindowBorderWidth(display, event.xany.window, shadow); \
		XSetWindowBackground(display, event.xany.window, floatingContainerBackgroundColor); \
		XUnmapWindow(display, event.xany.window); \
		XMapRaised(display, event.xany.window); \
		{ \
			unsigned int width; \
			unsigned int height; \
			{ \
				XRRMonitorInfo monitorInfo; \
				if(pointerInfo & RemoveFromGridPointerInfo){ \
					monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
				}else{ \
					monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
				} \
				if(option & FloatingFollowGrid){ \
					width = monitorInfo.width / gridWidth; \
					height = monitorInfo.height / gridHeight; \
				}else{ \
					width = monitorInfo.width / 2; \
					height = monitorInfo.height / 2; \
				} \
				XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - width) / 2 - shadow, monitorInfo.y + (monitorInfo.height - height) / 2 - shadow, width, height); \
			} \
			XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
		} \
		container[currentContainer].option ^= InPlaceContainerOption; \
	} \
}
#define MOVEABOVEGRIDSLOT_KEYPRESS \
if(container[currentContainer].gridX || container[currentContainer].gridY){ \
	if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
		if(container[currentContainer].gridY){ \
			--container[currentContainer].gridY; \
			goto moveGridSlot; \
		}else if(option & GriddingAllowBoundaryBreakYOption){ \
			--container[currentContainer].gridX; \
			container[currentContainer].gridY = gridHeight - 1; \
			goto moveGridSlot; \
		} \
	} \
}
#define MOVEBELOWGRIDSLOT_KEYPRESS \
if(container[currentContainer].gridX < gridWidth - 1 || container[currentContainer].gridY < gridHeight - 1){ \
	if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
		if(container[currentContainer].gridY < gridHeight - 1){ \
			++container[currentContainer].gridY; \
			goto moveGridSlot; \
		}else if(option & GriddingAllowBoundaryBreakYOption){ \
			++container[currentContainer].gridX; \
			container[currentContainer].gridY = 0; \
			goto moveGridSlot; \
		} \
	} \
}
#define MOVENEXTGRIDSLOT_KEYPRESS \
if(container[currentContainer].gridX < gridWidth - 1 || container[currentContainer].gridY < gridHeight - 1){ \
	if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
		if(container[currentContainer].gridX < gridWidth - 1){ \
			++container[currentContainer].gridX; \
			goto moveGridSlot; \
		}else if(option & GriddingAllowBoundaryBreakXOption){ \
			container[currentContainer].gridX = 0; \
			++container[currentContainer].gridY; \
			goto moveGridSlot; \
		} \
	} \
}
#define MOVEPREVIOUSGRIDSLOT_KEYPRESS \
if(container[currentContainer].gridX || container[currentContainer].gridY){ \
	if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
		if(container[currentContainer].gridX){ \
			--container[currentContainer].gridX; \
			goto moveGridSlot; \
		}else if(option & GriddingAllowBoundaryBreakXOption){ \
			container[currentContainer].gridX = gridWidth - 1; \
			--container[currentContainer].gridY; \
			moveGridSlot:{ \
				const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
				int x; \
				int y; \
				unsigned int width; \
				unsigned int height; \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, &width, &height); \
				XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
				XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
			} \
		} \
	} \
}
#define MOVEUPONGRID_KEYPRESS \
if(container[currentContainer].gridY){ \
	--container[currentContainer].gridY; \
	moveContainerToGridPosition(container[currentContainer], getWindowMonitorInfo(event.xany.window, monitors, monitorAmount), gridWidth, gridHeight, borderX, borderY); \
}
#define MOVEDOWNONGRID_KEYPRESS \
if(container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
	++container[currentContainer].gridY; \
	moveContainerToGridPosition(container[currentContainer], getWindowMonitorInfo(event.xany.window, monitors, monitorAmount), gridWidth, gridHeight, borderX, borderY); \
}
#define MOVELEFTONGRID_KEYPRESS \
if(container[currentContainer].gridX){ \
	--container[currentContainer].gridX; \
	moveContainerToGridPosition(container[currentContainer], getWindowMonitorInfo(event.xany.window, monitors, monitorAmount), gridWidth, gridHeight, borderX, borderY); \
}
#define MOVERIGHTONGRID_KEYPRESS \
if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth){ \
	++container[currentContainer].gridX; \
	moveContainerToGridPosition(container[currentContainer], getWindowMonitorInfo(event.xany.window, monitors, monitorAmount), gridWidth, gridHeight, borderX, borderY); \
}
#define EXTENDWINDOWUP_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	if(windowAttributes.y > monitorInfo.y + (int)gapsY){ \
		uint8_t changes[allocatedContainerAmount]; \
		unsigned int customExtendHeight = tilingExtendHeight; \
		unsigned int changesAmount = 0; \
		{ \
			XWindowAttributes windowAttributes1; \
			XRRMonitorInfo monitorInfo1; \
			unsigned int currentContainer1; \
			XWindowAttributes windowAttributes2; \
			unsigned int separationHeight; \
			if(option & TilingUseSeparatorsOption){ \
				separationHeight = 2 * gapsY + separatorWidth + separatorBorders; \
			}else{ \
				separationHeight = gapsY; \
			} \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				changes[currentContainer] = NoChanges; \
			} \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes1); \
				if(windowAttributes1.y == windowAttributes.y){ \
					monitorInfo1 = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					if(monitorCompare(monitorInfo1, monitorInfo)){ \
						for(currentContainer1 = 0; currentContainer1 < allocatedContainerAmount; ++currentContainer1){ \
							XGetWindowAttributes(display, container[currentContainer1].window, &windowAttributes2); \
							if(windowAttributes2.y + windowAttributes2.height + (int)separationHeight == windowAttributes1.y && ((windowAttributes2.x >= windowAttributes1.x && windowAttributes2.x <= windowAttributes1.x + windowAttributes1.width) || (windowAttributes2.x + windowAttributes2.width >= windowAttributes1.x && windowAttributes2.x + windowAttributes2.width <= windowAttributes1.x + windowAttributes1.width))){ \
								monitorInfo1 = getWindowMonitorInfo(container[currentContainer1].window, monitors, monitorAmount); \
								if(monitorCompare(monitorInfo1, monitorInfo)){ \
									if(windowAttributes2.height - customExtendHeight < tilingMinimumHeight){ \
										customExtendHeight -= tilingMinimumHeight - windowAttributes2.height + customExtendHeight; \
										if(!customExtendHeight){ \
											goto extendShrinkWindowEmergencyExit; \
										} \
									} \
									changes[currentContainer1] = ShrinkChange; \
									++changesAmount; \
								} \
							} \
						} \
						changes[currentContainer] = ExtendChange; \
						++changesAmount; \
					} \
				} \
			} \
		} \
		if(changesAmount){ \
			unsigned int currentChange = 0; \
			currentContainer = 0; \
			for(;;){ \
				if(changes[currentContainer] != NoChanges){ \
					XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
					windowAttributes.y -= customExtendHeight - changes[currentContainer] / 2 * customExtendHeight; \
					windowAttributes.height += customExtendHeight - changes[currentContainer] * customExtendHeight; \
					XMoveResizeWindow(display, container[currentContainer].window, windowAttributes.x, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
					if(++currentChange == changesAmount){ \
						break; \
					} \
				} \
				++currentContainer; \
			} \
		} \
	} \
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridY){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
		int y; \
		unsigned int height; \
		getGridSlotData(monitorInfo, container[currentContainer].gridX, --container[currentContainer].gridY, gridWidth, gridHeight, NULL, &y, NULL, &height); \
		++container[currentContainer].gridHeight; \
		height += windowAttributes.height; \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, y + monitorInfo.y, windowAttributes.width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.height += floatingExtendHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y - floatingExtendHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define EXTENDWINDOWDOWN_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	if(windowAttributes.y + windowAttributes.height < monitorInfo.y + monitorInfo.height - (int)gapsY){ \
		uint8_t changes[allocatedContainerAmount]; \
		unsigned int customExtendHeight = tilingExtendHeight; \
		unsigned int changesAmount = 0; \
		{ \
			XWindowAttributes windowAttributes1; \
			XRRMonitorInfo monitorInfo1; \
			unsigned int currentContainer1; \
			XWindowAttributes windowAttributes2; \
			unsigned int separationHeight; \
			if(option & TilingUseSeparatorsOption){ \
				separationHeight = 2 * gapsY + separatorWidth + separatorBorders; \
			}else{ \
				separationHeight = gapsY; \
			} \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				changes[currentContainer] = NoChanges; \
			} \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes1); \
				if(windowAttributes1.y == windowAttributes.y){ \
					monitorInfo1 = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					if(monitorCompare(monitorInfo1, monitorInfo)){ \
						for(currentContainer1 = 0; currentContainer1 < allocatedContainerAmount; ++currentContainer1){ \
							XGetWindowAttributes(display, container[currentContainer1].window, &windowAttributes2); \
							if(windowAttributes2.y == windowAttributes1.y + windowAttributes1.height + (int)separationHeight && ((windowAttributes2.x >= windowAttributes1.x && windowAttributes2.x <= windowAttributes1.x + windowAttributes1.width) || (windowAttributes2.x + windowAttributes2.width >= windowAttributes1.x && windowAttributes2.x + windowAttributes2.width <= windowAttributes1.x + windowAttributes1.width))){ \
								monitorInfo1 = getWindowMonitorInfo(container[currentContainer1].window, monitors, monitorAmount); \
								if(monitorCompare(monitorInfo1, monitorInfo)){ \
									if(windowAttributes2.height - customExtendHeight < tilingMinimumHeight){ \
										customExtendHeight -= tilingMinimumHeight - windowAttributes2.height + customExtendHeight; \
										if(!customExtendHeight){ \
											goto extendShrinkWindowEmergencyExit; \
										} \
									} \
									changes[currentContainer1] = ShrinkChange; \
									++changesAmount; \
								} \
							} \
						} \
						changes[currentContainer] = ExtendChange; \
						++changesAmount; \
					} \
				} \
			} \
		} \
		if(changesAmount){ \
			unsigned int currentChange = 0; \
			currentContainer = 0; \
			for(;;){ \
				if(changes[currentContainer] != NoChanges){ \
					XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
					windowAttributes.y += changes[currentContainer] / 2 * customExtendHeight; \
					windowAttributes.height += customExtendHeight - changes[currentContainer] * customExtendHeight; \
					XMoveResizeWindow(display, container[currentContainer].window, windowAttributes.x, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
					if(++currentChange == changesAmount){ \
						break; \
					} \
				} \
				++currentContainer; \
			} \
		} \
	} \
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int height; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
		++container[currentContainer].gridHeight; \
		height += windowAttributes.height; \
		XResizeWindow(display, event.xany.window, windowAttributes.width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.height += floatingExtendHeight; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define EXTENDWINDOWLEFT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	if(windowAttributes.x > monitorInfo.x + (int)gapsX){ \
		uint8_t changes[allocatedContainerAmount]; \
		unsigned int customExtendWidth = tilingExtendWidth; \
		unsigned int changesAmount = 0; \
		{ \
			XWindowAttributes windowAttributes1; \
			XRRMonitorInfo monitorInfo1; \
			unsigned int currentContainer1; \
			XWindowAttributes windowAttributes2; \
			unsigned int separationWidth; \
			if(option & TilingUseSeparatorsOption){ \
				separationWidth = 2 * gapsX + separatorWidth + separatorBorders; \
			}else{ \
				separationWidth = gapsX; \
			} \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				changes[currentContainer] = NoChanges; \
			} \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes1); \
				if(windowAttributes1.x == windowAttributes.x){ \
					monitorInfo1 = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					if(monitorCompare(monitorInfo1, monitorInfo)){ \
						for(currentContainer1 = 0; currentContainer1 < allocatedContainerAmount; ++currentContainer1){ \
							XGetWindowAttributes(display, container[currentContainer1].window, &windowAttributes2); \
							if(windowAttributes2.x + windowAttributes2.width + (int)separationWidth == windowAttributes1.x && ((windowAttributes2.y >= windowAttributes1.y && windowAttributes2.y <= windowAttributes1.y + windowAttributes1.height) || (windowAttributes2.y + windowAttributes2.height >= windowAttributes1.y && windowAttributes2.y + windowAttributes2.height <= windowAttributes1.y + windowAttributes1.height))){ \
								monitorInfo1 = getWindowMonitorInfo(container[currentContainer1].window, monitors, monitorAmount); \
								if(monitorCompare(monitorInfo1, monitorInfo)){ \
									if(windowAttributes2.width - customExtendWidth < tilingMinimumWidth){ \
										customExtendWidth -= tilingMinimumWidth - windowAttributes2.width + customExtendWidth; \
										if(!customExtendWidth){ \
											goto extendShrinkWindowEmergencyExit; \
										} \
									} \
									changes[currentContainer1] = ShrinkChange; \
									++changesAmount; \
								} \
							} \
						} \
						changes[currentContainer] = ExtendChange; \
						++changesAmount; \
					} \
				} \
			} \
		} \
		if(changesAmount){ \
			unsigned int currentChange = 0; \
			currentContainer = 0; \
			for(;;){ \
				if(changes[currentContainer] != NoChanges){ \
					XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
					windowAttributes.x -= customExtendWidth - changes[currentContainer] / 2 * customExtendWidth; \
					windowAttributes.width += customExtendWidth - changes[currentContainer] * customExtendWidth; \
					XMoveResizeWindow(display, container[currentContainer].window, windowAttributes.x, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
					if(++currentChange == changesAmount){ \
						break; \
					} \
				} \
				++currentContainer; \
			} \
		} \
	} \
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridX){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
		int x; \
		unsigned int width; \
		getGridSlotData(monitorInfo, --container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, NULL, &width, NULL); \
		++container[currentContainer].gridWidth; \
		width += windowAttributes.width; \
		XMoveResizeWindow(display, event.xany.window, x + monitorInfo.x, windowAttributes.y, width, windowAttributes.height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, windowAttributes.height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x - floatingExtendWidth, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define EXTENDWINDOWRIGHT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	if(windowAttributes.x + windowAttributes.width < monitorInfo.x + monitorInfo.width - (int)gapsX){ \
		uint8_t changes[allocatedContainerAmount]; \
		unsigned int customExtendWidth = tilingExtendWidth; \
		unsigned int changesAmount = 0; \
		{ \
			XWindowAttributes windowAttributes1; \
			XRRMonitorInfo monitorInfo1; \
			unsigned int currentContainer1; \
			XWindowAttributes windowAttributes2; \
			unsigned int separationWidth; \
			if(option & TilingUseSeparatorsOption){ \
				separationWidth = 2 * gapsX + separatorWidth + separatorBorders; \
			}else{ \
				separationWidth = gapsX; \
			} \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				changes[currentContainer] = NoChanges; \
			} \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes1); \
				if(windowAttributes1.x == windowAttributes.x){ \
					monitorInfo1 = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					if(monitorCompare(monitorInfo1, monitorInfo)){ \
						for(currentContainer1 = 0; currentContainer1 < allocatedContainerAmount; ++currentContainer1){ \
							XGetWindowAttributes(display, container[currentContainer1].window, &windowAttributes2); \
							if(windowAttributes2.x == windowAttributes1.x + windowAttributes1.width + (int)separationWidth && ((windowAttributes2.y >= windowAttributes1.y && windowAttributes2.y <= windowAttributes1.y + windowAttributes1.height) || (windowAttributes2.y + windowAttributes2.height >= windowAttributes1.y && windowAttributes2.y + windowAttributes2.height <= windowAttributes1.y + windowAttributes1.height))){ \
								monitorInfo1 = getWindowMonitorInfo(container[currentContainer1].window, monitors, monitorAmount); \
								if(monitorCompare(monitorInfo1, monitorInfo)){ \
									if(windowAttributes2.width - customExtendWidth < tilingMinimumWidth){ \
										customExtendWidth -= tilingMinimumWidth - windowAttributes2.width + customExtendWidth; \
										if(!customExtendWidth){ \
											goto extendShrinkWindowEmergencyExit; \
										} \
									} \
									changes[currentContainer1] = ShrinkChange; \
									++changesAmount; \
								} \
							} \
						} \
						changes[currentContainer] = ExtendChange; \
						++changesAmount; \
					} \
				} \
			} \
		} \
		if(changesAmount){ \
			unsigned int currentChange = 0; \
			currentContainer = 0; \
			for(;;){ \
				if(changes[currentContainer] != NoChanges){ \
					XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
					windowAttributes.x += changes[currentContainer] / 2 * customExtendWidth; \
					windowAttributes.width += customExtendWidth - changes[currentContainer] * customExtendWidth; \
					XMoveResizeWindow(display, container[currentContainer].window, windowAttributes.x, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
					if(++currentChange == changesAmount){ \
						break; \
					} \
				} \
				++currentContainer; \
			} \
		} \
	} \
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth){ \
		unsigned int width; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window, monitors, monitorAmount), container[currentContainer].gridX + container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
		++container[currentContainer].gridWidth; \
		width += windowAttributes.width; \
		XResizeWindow(display, event.xany.window, width, windowAttributes.height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, windowAttributes.height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define EXTENDWINDOWUPLEFT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridX || container[currentContainer].gridY){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int height; \
		unsigned int width; \
		{ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(container[currentContainer].gridY){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, --container[currentContainer].gridY, gridWidth, gridHeight, NULL, &windowAttributes.y, NULL, &height); \
				++container[currentContainer].gridHeight; \
				windowAttributes.y += monitorInfo.y; \
				height += windowAttributes.height; \
			}else{ \
				height = windowAttributes.height; \
			} \
			if(container[currentContainer].gridX){ \
				getGridSlotData(monitorInfo, --container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &windowAttributes.x, NULL, &width, NULL); \
				++container[currentContainer].gridWidth; \
				windowAttributes.x += monitorInfo.x; \
				width += windowAttributes.width; \
			}else{ \
				width = windowAttributes.width; \
			} \
		} \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y, width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	windowAttributes.height += floatingExtendHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x - floatingExtendWidth, windowAttributes.y - floatingExtendHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define EXTENDWINDOWUPRIGHT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth || container[currentContainer].gridY){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(container[currentContainer].gridY){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, --container[currentContainer].gridY, gridWidth, gridHeight, NULL, &windowAttributes.y, NULL, &height); \
				++container[currentContainer].gridHeight; \
				windowAttributes.y += monitorInfo.y; \
				height += windowAttributes.height; \
			}else{ \
				height = windowAttributes.height; \
			} \
			if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX + container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
				++container[currentContainer].gridWidth; \
				width += windowAttributes.width; \
			}else{ \
				width = windowAttributes.width; \
			} \
		} \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y, width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	windowAttributes.height += floatingExtendHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y - floatingExtendHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define EXTENDWINDOWDOWNLEFT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridX || container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
				++container[currentContainer].gridHeight; \
				height += windowAttributes.height; \
			}else{ \
				height = windowAttributes.height; \
			} \
			if(container[currentContainer].gridX){ \
				getGridSlotData(monitorInfo, --container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &windowAttributes.x, NULL, &width, NULL); \
				++container[currentContainer].gridWidth; \
				windowAttributes.x += monitorInfo.x; \
				width += windowAttributes.width; \
			}else{ \
				width = windowAttributes.width; \
			} \
		} \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y, width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	windowAttributes.height += floatingExtendHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x - floatingExtendWidth, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define EXTENDWINDOWDOWNRIGHT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth || container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
				++container[currentContainer].gridHeight; \
				height += windowAttributes.height; \
			}else{ \
				height = windowAttributes.height; \
			} \
			if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX + container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
				++container[currentContainer].gridWidth; \
				width += windowAttributes.width; \
			}else{ \
				width = windowAttributes.width; \
			} \
		} \
		XResizeWindow(display, event.xany.window, width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	windowAttributes.height += floatingExtendHeight; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define SHRINKWINDOWUP_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int height; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY + --container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
		height = windowAttributes.height - height; \
		XResizeWindow(display, event.xany.window, windowAttributes.width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.height -= floatingShrinkHeight; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define SHRINKWINDOWDOWN_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int height; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
		++container[currentContainer].gridY; \
		--container[currentContainer].gridHeight; \
		windowAttributes.y += height; \
		height = windowAttributes.height - height; \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y, windowAttributes.width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.height -= floatingShrinkHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y + floatingShrinkHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define SHRINKWINDOWLEFT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridWidth > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window, monitors, monitorAmount), container[currentContainer].gridX + --container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
		width = windowAttributes.width - width; \
		XResizeWindow(display, event.xany.window, width, windowAttributes.height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, windowAttributes.height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define SHRINKWINDOWRIGHT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridWidth > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
		++container[currentContainer].gridX; \
		--container[currentContainer].gridWidth; \
		windowAttributes.x += width; \
		width = windowAttributes.width - width; \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y, width, windowAttributes.height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, windowAttributes.height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x + floatingShrinkWidth, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define SHRINKWINDOWUPLEFT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridWidth > 1 || container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(container[currentContainer].gridHeight > 1){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY + --container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
				height = windowAttributes.height - height; \
			}else{ \
				height = windowAttributes.height; \
			} \
			if(container[currentContainer].gridWidth > 1){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX + --container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
				width = windowAttributes.width - width; \
			}else{ \
				width = windowAttributes.width; \
			} \
		} \
		XResizeWindow(display, event.xany.window, width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	windowAttributes.height -= floatingShrinkHeight; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define SHRINKWINDOWUPRIGHT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridWidth > 1 || container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(container[currentContainer].gridHeight > 1){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY + --container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
				height = windowAttributes.height - height; \
			}else{ \
				height = windowAttributes.height; \
			} \
			if(container[currentContainer].gridWidth > 1){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
				++container[currentContainer].gridX; \
				--container[currentContainer].gridWidth; \
				windowAttributes.x += width; \
				width = windowAttributes.width - width; \
			}else{ \
				width = windowAttributes.width; \
			} \
		} \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y, width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	windowAttributes.height -= floatingShrinkHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x + floatingShrinkWidth, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define SHRINKWINDOWDOWNLEFT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridWidth > 1 && container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(container[currentContainer].gridHeight > 1){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
				++container[currentContainer].gridY; \
				--container[currentContainer].gridHeight; \
				windowAttributes.y += height; \
				height = windowAttributes.height - height; \
			}else{ \
				height = windowAttributes.height; \
			} \
			if(container[currentContainer].gridWidth > 1){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX + --container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
				width = windowAttributes.width - width; \
			}else{ \
				width = windowAttributes.width; \
			} \
		} \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y, width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	windowAttributes.height -= floatingShrinkHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y + floatingShrinkHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define SHRINKWINDOWDOWNRIGHT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	\
\
\
\
}else if(container[currentContainer].option & InPlaceContainerOption){ \
	if(container[currentContainer].gridWidth > 1 && container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(container[currentContainer].gridHeight > 1){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
				++container[currentContainer].gridY; \
				--container[currentContainer].gridHeight; \
				windowAttributes.y += height; \
				height = windowAttributes.height - height; \
			}else{ \
				height = windowAttributes.height; \
			} \
			if(container[currentContainer].gridWidth > 1){ \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
				++container[currentContainer].gridX; \
				--container[currentContainer].gridWidth; \
				windowAttributes.x += width; \
				width = windowAttributes.width - width; \
			}else{ \
				width = windowAttributes.width; \
			} \
		} \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y, width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - borderX, height - borderY); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	windowAttributes.height -= floatingShrinkHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x + floatingShrinkWidth, windowAttributes.y + floatingShrinkHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - borderX, windowAttributes.height - borderY); \
}
#define FULLSCREEN_BIGSCREEN_KEYPRESS \
if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
	XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	unsigned int currentMonitor; \
	for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
		if(monitorCompare(monitors[currentMonitor], monitorInfo)){ \
			break; \
		} \
	} \
	if(!maximizedContainer[currentMonitor].window){ \
		fullscreenBigscreenInner:{ \
			XSetWindowBorderWidth(display, event.xany.window, 0); \
			if(c == FullscreenCommand){ \
				{ \
					const Atom atom = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False); \
					XChangeProperty(display, container[currentContainer].subwindow, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1); \
				} \
				maximizedContainer[currentMonitor].shouldChangeProperty = 1; \
				XSetWindowBackground(display, event.xany.window, fullscreenContainerBackgroundColor); \
			}else{ \
				maximizedContainer[currentMonitor].shouldChangeProperty = 0; \
				XSetWindowBackground(display, event.xany.window, bigscreenContainerBackgroundColor); \
			} \
			XUnmapWindow(display, event.xany.window); \
			XMapRaised(display, event.xany.window); \
			XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
			XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - borderX, monitorInfo.height - borderY); \
			maximizedContainer[currentMonitor].window = event.xany.window; \
			maximizedContainer[currentMonitor].subwindow = container[currentContainer].subwindow; \
			maximizedContainer[currentMonitor].oldX = windowAttributes.x; \
			maximizedContainer[currentMonitor].oldY = windowAttributes.y; \
			maximizedContainer[currentMonitor].oldWidth = windowAttributes.width; \
			maximizedContainer[currentMonitor].oldHeight = windowAttributes.height; \
			if(managementMode == TilingManagementMode){ \
				maximizedContainer[currentMonitor].oldBackgroundColor = tilingContainerBackgroundColor; \
			}else if(managementMode == GriddingManagementMode){ \
				maximizedContainer[currentMonitor].oldBackgroundColor = griddingContainerBackgroundColor; \
			}else if(container[currentContainer].option & InPlaceContainerOption){ \
				maximizedContainer[currentMonitor].oldBackgroundColor = inGridContainerBackgroundColor; \
			}else{ \
				maximizedContainer[currentMonitor].oldBackgroundColor = floatingContainerBackgroundColor; \
			} \
			commandedWindow = maximizedContainer[currentMonitor].subwindow; \
		} \
	}else{ \
		if(maximizedContainer[currentMonitor].shouldChangeProperty){ \
			const Atom atom = None; \
			XChangeProperty(display, maximizedContainer[currentMonitor].subwindow, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1); \
		} \
		if(maximizedContainer[currentMonitor].oldBackgroundColor == floatingContainerBackgroundColor){ \
			XSetWindowBorderWidth(display, maximizedContainer[currentMonitor].window, shadow); \
		} \
		XSetWindowBackground(display, maximizedContainer[currentMonitor].window, maximizedContainer[currentMonitor].oldBackgroundColor); \
		XUnmapWindow(display, maximizedContainer[currentMonitor].window); \
		XMapRaised(display, maximizedContainer[currentMonitor].window); \
		XMoveResizeWindow(display, maximizedContainer[currentMonitor].window, maximizedContainer[currentMonitor].oldX, maximizedContainer[currentMonitor].oldY, maximizedContainer[currentMonitor].oldWidth, maximizedContainer[currentMonitor].oldHeight); \
		XResizeWindow(display, maximizedContainer[currentMonitor].subwindow, maximizedContainer[currentMonitor].oldWidth - borderX, maximizedContainer[currentMonitor].oldHeight - borderY); \
		commandedWindow = maximizedContainer[currentMonitor].subwindow; \
		if(event.xany.window != maximizedContainer[currentMonitor].window){ \
			maximizedContainer[currentMonitor].window = None; \
			goto fullscreenBigscreenInner; \
		}else{ \
			maximizedContainer[currentMonitor].window = None; \
		} \
	} \
}
#define CLOSE_KEYPRESS \
if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
	XEvent e = { \
		.xclient = { \
			.type = ClientMessage, \
			.send_event = False, \
			.display = display, \
			.window = container[currentContainer].subwindow, \
			.message_type = XInternAtom(display, "WM_PROTOCOLS", False), \
			.format = 32, \
			.data = { \
				.l[0] = XInternAtom(display, "WM_DELETE_WINDOW", False), \
				.l[1] = CurrentTime \
			} \
		} \
	}; \
	XSendEvent(display, e.xclient.window, False, PropertyChangeMask, &e); \
}
#define KILL_KEYPRESS \
if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
	XUnmapWindow(display, container[currentContainer].subwindow); \
	XDestroyWindow(display, container[currentContainer].subwindow); \
	goto unmapWindow; \
}
#define DETACHWINDOW_KEYPRESS \
if(findContainer(event.xany.window, container, allocatedContainerAmount, &currentContainer)){ \
	const Window subwindow = container[currentContainer].subwindow; \
	const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
	XGetWindowAttributes(display, subwindow, &windowAttributes); \
	XReparentWindow(display, subwindow, XDefaultRootWindow(display), monitorInfo.x + (monitorInfo.width - windowAttributes.width) / 2, monitorInfo.y + (monitorInfo.height - windowAttributes.height) / 2); \
	XResizeWindow(display, subwindow, monitorInfo.width / 2, monitorInfo.height / 2); \
	goto unmapWindow; \
}
#define KEYBUTTONRELEASE \
if(motionContainer.action){ \
	XSelectInput(display, XDefaultRootWindow(display), SubstructureRedirectMask); \
	if(motionContainer.action == MoveMotionAction){ \
		if(option & FloatingMinimalMoveOption){ \
			XUnmapWindow(display, motionContainer.window); \
			{ \
				const unsigned int b = shadow; \
				shadow = moveResizeWindowBorder; \
				moveResizeWindowBorder = b; \
			} \
			XMoveWindow(display, moveResizeWindow, motionContainer.x + moveResizeWindowBorder - motionContainer.positionOffset - shadow, motionContainer.y + moveResizeWindowBorder - motionContainer.positionOffset - shadow); \
			goto flipMotionResizeWindows; \
		} \
	}else{ \
		if(option & FloatingMinimalResizeOption){ \
			XUnmapWindow(display, motionContainer.window); \
			XMoveResizeWindow(display, moveResizeWindow, motionContainer.x + motionContainer.positionOffset + moveResizeWindowBorder - shadow, motionContainer.y + motionContainer.positionOffset + moveResizeWindowBorder - shadow, motionContainer.width, motionContainer.height); \
			XResizeWindow(display, motionContainer.subwindow, motionContainer.width - borderX, motionContainer.height - borderY); \
			XSelectInput(display, motionContainer.subwindow, ButtonMotionMask | StructureNotifyMask); \
			flipMotionResizeWindows:{ \
				const Window w = motionContainer.window; \
				motionContainer.window = moveResizeWindow; \
				moveResizeWindow = w; \
			} \
		} \
	} \
	motionContainer.options = NoMotionOptions; \
	motionContainer.action = NoMotionAction; \
}
#define MOTIONNOTIFY \
if(motionContainer.options & CanActOption){ \
	if(motionContainer.action == MoveMotionAction){ \
		if(option & FloatingAllowStickingOption){ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(motionContainer.window, monitors, monitorAmount); \
			if(motionContainer.x + (int)shadow >= monitorInfo.x && motionContainer.x + (int)shadow <= monitorInfo.x + floatingStickyThresholdX){ \
				if(!(motionContainer.options & HasLockedXOption)){ \
					motionContainer.x = monitorInfo.x - shadow; \
					XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
					motionContainer.movementBorderX = event.xmotion.x_root + floatingDistanceToTravelX; \
					motionContainer.options |= HasLockedXOption; \
				}else{ \
					if(event.xmotion.x_root >= motionContainer.movementBorderX){ \
						motionContainer.options ^= HasLockedXOption; \
					} \
				} \
			}else if(motionContainer.x + (int)(motionContainer.width + shadow) >= monitorInfo.x + monitorInfo.width && motionContainer.x + (int)(motionContainer.width + shadow) <= monitorInfo.x + monitorInfo.width + floatingStickyThresholdX){ \
				if(!(motionContainer.options & HasLockedXOption)){ \
					motionContainer.x = monitorInfo.x + monitorInfo.width - motionContainer.width - shadow; \
					XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
					motionContainer.movementBorderX = event.xmotion.x_root - floatingDistanceToTravelX; \
					motionContainer.options |= HasLockedXOption; \
				}else{ \
					if(event.xmotion.x_root <= motionContainer.movementBorderX){ \
						motionContainer.options ^= HasLockedXOption; \
					} \
				} \
			} \
			if(motionContainer.y + (int)shadow >= monitorInfo.y && motionContainer.y + (int)shadow <= monitorInfo.y + floatingStickyThresholdY){ \
				if(!(motionContainer.options & HasLockedYOption)){ \
					motionContainer.y = monitorInfo.y - shadow; \
					XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
					motionContainer.movementBorderY = event.xmotion.y_root + floatingDistanceToTravelY; \
					motionContainer.options |= HasLockedYOption; \
				}else{ \
					if(event.xmotion.y_root >= motionContainer.movementBorderY){ \
						motionContainer.options ^= HasLockedYOption; \
					} \
				} \
			}else if(motionContainer.y + (int)(motionContainer.height + shadow) >= monitorInfo.y + monitorInfo.height && motionContainer.y + (int)(motionContainer.height + shadow) <= monitorInfo.y + monitorInfo.height + floatingStickyThresholdY){ \
				if(!(motionContainer.options & HasLockedYOption)){ \
					motionContainer.y = monitorInfo.y + monitorInfo.height - motionContainer.height - shadow; \
					XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
					motionContainer.movementBorderY = event.xmotion.y_root - floatingDistanceToTravelY; \
					motionContainer.options |= HasLockedYOption; \
				}else{ \
					if(event.xmotion.y_root <= motionContainer.movementBorderY){ \
						motionContainer.options ^= HasLockedYOption; \
					} \
				} \
			} \
			if(!(motionContainer.options & HasLockedXOption) || !(motionContainer.options & HasLockedYOption)){ \
				if(!(motionContainer.options & HasLockedXOption)){ \
					motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX; \
				} \
				if(!(motionContainer.options & HasLockedYOption)){ \
					motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY; \
				} \
				XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
			} \
		}else{ \
			XMoveWindow(display, motionContainer.window, event.xmotion.x_root - motionContainer.pointerOffsetX, event.xmotion.y_root - motionContainer.pointerOffsetY); \
		} \
	}else if(motionContainer.action == ResizeMotionAction){ \
		if(motionContainer.subaction == UpResizeMotionSubaction){ \
			motionContainer.height += motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.height <= (int)borderY){ \
				motionContainer.height = borderY + 1; \
			}else{ \
				motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == DownResizeMotionSubaction){ \
			motionContainer.height -= motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.height <= (int)borderY){ \
				motionContainer.height = borderY + 1; \
			}else{ \
				motionContainer.pointerOffsetY = event.xmotion.y_root - motionContainer.y; \
			} \
			XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == LeftResizeMotionSubaction){ \
			motionContainer.width += motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			if((int)motionContainer.width <= (int)borderX){ \
				motionContainer.width = borderX + 1; \
			}else{ \
				motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == RightResizeMotionSubaction){ \
			motionContainer.width -= motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			if((int)motionContainer.width <= (int)borderX){ \
				motionContainer.width = borderX + 1; \
			}else{ \
				motionContainer.pointerOffsetX = event.xmotion.x_root - motionContainer.x; \
			} \
			XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == UpLeftResizeMotionSubaction){ \
			motionContainer.width += motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			motionContainer.height += motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.width <= (int)borderX){ \
				motionContainer.width = borderX + 1; \
			}else{ \
				motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX; \
			} \
			if((int)motionContainer.height <= (int)borderY){ \
				motionContainer.height = borderY + 1; \
			}else{ \
				motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == UpRightResizeMotionSubaction){ \
			motionContainer.width -= motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			motionContainer.height += motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.width <= (int)borderX){ \
				motionContainer.width = borderX + 1; \
			}else{ \
				motionContainer.pointerOffsetX = event.xmotion.x_root - motionContainer.x; \
			} \
			if((int)motionContainer.height <= (int)borderY){ \
				motionContainer.height = borderY + 1; \
			}else{ \
				motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == DownLeftResizeMotionSubaction){ \
			motionContainer.width += motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			motionContainer.height -= motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.width <= (int)borderX){ \
				motionContainer.width = borderX + 1; \
			}else{ \
				motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX; \
			} \
			if((int)motionContainer.height <= (int)borderY){ \
				motionContainer.height = borderY + 1; \
			}else{ \
				motionContainer.pointerOffsetY = event.xmotion.y_root - motionContainer.y; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else{ \
			motionContainer.width += event.xmotion.x_root - motionContainer.x - motionContainer.pointerOffsetX; \
			motionContainer.height += event.xmotion.y_root - motionContainer.y - motionContainer.pointerOffsetY; \
			if((int)motionContainer.width <= (int)borderX){ \
				motionContainer.width = borderX + 1; \
			}else{ \
				 motionContainer.pointerOffsetX = event.xmotion.x_root - motionContainer.x; \
			} \
			if((int)motionContainer.height <= (int)borderY){ \
				motionContainer.height = borderY + 1; \
			}else{ \
				motionContainer.pointerOffsetY = event.xmotion.y_root - motionContainer.y; \
			} \
			XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height); \
		} \
		if(!(option & FloatingMinimalResizeOption)){ \
			XResizeWindow(display, motionContainer.subwindow, motionContainer.width - borderX, motionContainer.height - borderY); \
		} \
	} \
	motionContainer.options ^= CanActOption; \
}else{ \
	if(!XPending(display)){ \
		motionContainer.options |= CanActOption; \
	} \
}
#define ENTERNOTIFY \
if(!commandedWindow && findContainer(event.xcrossing.window, container, allocatedContainerAmount, &currentContainer)){ \
	if(!motionContainer.action){ \
		XRaiseWindow(display, event.xcrossing.window); \
		XSetInputFocus(display, container[currentContainer].subwindow, RevertToPointerRoot, CurrentTime); \
		if(XPending(display)){ \
			XPeekEvent(display, &event); \
			if(event.type == EnterNotify){ \
				XNextEvent(display, &event); \
			} \
		} \
	} \
}
#define UNMAPNOTIFY \
for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
	if(container[currentContainer].subwindow == event.xunmap.window){ \
		unmapWindow:{ \
			XRRMonitorInfo monitorInfo; \
			if(managementMode == TilingManagementMode){ \
				monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
			} \
			XUnmapWindow(display, container[currentContainer].window); \
			XSetInputFocus(display, XDefaultRootWindow(display), RevertToPointerRoot, CurrentTime); \
			clearWindowProperties(container[currentContainer].window); \
			container[currentContainer].subwindow = None; \
			--allocatedContainerAmount; \
			for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
				if(maximizedContainer[currentMonitor].window == container[currentContainer].window){ \
					maximizedContainer[currentMonitor].window = None; \
					break; \
				} \
			} \
			const unsigned int containerAmount1 = containerAmount - 1; \
			unsigned int currentContainer1; \
			Window w; \
			unsigned int lastCreatedWindowNumber = containerAmount; \
			for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){ \
				if(!container[currentContainer].subwindow){ \
					for(currentContainer1 = currentContainer; currentContainer1 < containerAmount1; ++currentContainer1){ \
						w = container[currentContainer1].window; \
						container[currentContainer1] = container[currentContainer1 + 1]; \
						container[currentContainer1 + 1].window = w; \
					} \
				}else{ \
					lastCreatedWindowNumber = currentContainer; \
				} \
			} \
			if(lastCreatedWindowNumber < containerAmount){ \
				lastCreatedWindow = container[lastCreatedWindowNumber].window; \
			}else{ \
				lastCreatedWindow = None; \
			} \
\
\
\
\
\
\
\
\
\
			if(managementMode == TilingManagementMode){ \
				bool containerInMonitorMap[allocatedContainerAmount + 1]; \
				unsigned int monitorContainerAmount = 0; \
				{ \
					XRRMonitorInfo mi; \
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
						mi = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
						if(monitorCompare(mi, monitorInfo)){ \
							containerInMonitorMap[currentContainer] = 1; \
							++monitorContainerAmount; \
						}else{ \
							containerInMonitorMap[currentContainer] = 0; \
						} \
					} \
				} \
				if(monitorContainerAmount){ \
					const unsigned int totalSeparatorWidth = separatorWidth + separatorBorders; \
					const unsigned int middleX = monitorContainerAmount / 2; \
					const int y = monitorInfo.y + gapsY; \
					const unsigned int height = monitorInfo.height - 2 * gapsY; \
					const unsigned int subwindowHeight = height - borderY; \
					const unsigned int separatorHeight = height - separatorBorders; \
					const unsigned int separatorWidthGaps = totalSeparatorWidth + gapsX; \
					containerInMonitorMap[allocatedContainerAmount] = 1; \
					unsigned int normalWidth; \
					unsigned int abnormalWidth; \
					{ \
						unsigned int reservedSpace; \
						if(option & TilingUseSeparatorsOption){ \
							reservedSpace = 2 * monitorContainerAmount * gapsX + (monitorContainerAmount - 1) * totalSeparatorWidth; \
						}else{ \
							reservedSpace = (monitorContainerAmount + 1) * gapsX; \
						} \
						normalWidth = (monitorInfo.width - reservedSpace) / monitorContainerAmount; \
						abnormalWidth = (monitorInfo.width - reservedSpace) - (monitorContainerAmount - 1) * normalWidth; \
					} \
					unsigned int counter = 0; \
					int x = monitorInfo.x + gapsX; \
					unsigned int width = normalWidth; \
					unsigned int currentSeparator = 0; \
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
						if(containerInMonitorMap[currentContainer]){ \
							XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
							XResizeWindow(display, container[currentContainer].subwindow, width - borderX, subwindowHeight); \
							if(++counter == monitorContainerAmount){ \
								break; \
							} \
							x += width + gapsX; \
							if(option & TilingUseSeparatorsOption){ \
								XMoveResizeWindow(display, separator[currentSeparator], x, y, separatorWidth, separatorHeight); \
								if(currentSeparator >= mappedSeparatorAmount){ \
									XMapWindow(display, separator[currentSeparator]); \
									++mappedSeparatorAmount; \
								} \
								x += separatorWidthGaps; \
								++currentSeparator; \
							} \
							if(counter == middleX){ \
								width = abnormalWidth; \
							}else{ \
								width = normalWidth; \
							} \
						} \
					} \
				} \
			} \
\
\
\
\
\
\
\
\
\
			if(containerAmount > defaultContainerAmount && allocatedContainerAmount == containerAmount - containerIncrementDecrementAmount - 1){ \
				containerDirective = DecreaseContainerDirective; \
				goto saveOpenClients; \
			} \
			break; \
		} \
	} \
}
#define CONFIGUREREQUEST \
for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
	if(maximizedContainer[currentMonitor].subwindow == event.xconfigurerequest.window){ \
		if(maximizedContainer[currentMonitor].window){ \
			goto configureRequestEmergencyExit; \
		} \
	} \
} \
bool new = 1; \
for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
	if(container[currentContainer].subwindow == event.xconfigurerequest.window){ \
		XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
		if(canConfigurePosition){ \
			if(!(container[currentContainer].option & InPlaceContainerOption)){ \
				if((event.xconfigurerequest.value_mask & CWX || event.xconfigurerequest.value_mask & CWY)){ \
					if(event.xconfigurerequest.value_mask & CWX){ \
						windowAttributes.x = event.xconfigurerequest.x - borderLeft; \
					} \
					if(event.xconfigurerequest.value_mask & CWY){ \
						windowAttributes.y = event.xconfigurerequest.y - borderUp; \
					} \
					XMoveWindow(display, container[currentContainer].window, windowAttributes.x, windowAttributes.y); \
				} \
				canConfigurePosition = 0; \
			} \
		}else{ \
			if(!XPending(display)){ \
				canConfigurePosition = 1; \
			} \
		} \
		{ \
			XWindowChanges windowChanges; \
			unsigned int masks = None; \
			if(event.xconfigurerequest.value_mask & CWWidth){ \
				windowChanges.width = event.xconfigurerequest.width; \
				masks |= CWWidth; \
			} \
			if(event.xconfigurerequest.value_mask & CWHeight){ \
				windowChanges.height = event.xconfigurerequest.height; \
				masks |= CWHeight; \
			} \
			if(event.xconfigurerequest.value_mask & CWBorderWidth){ \
				windowChanges.border_width = event.xconfigurerequest.border_width; \
				windowAttributes.width -= event.xconfigurerequest.border_width; \
				windowAttributes.height -= event.xconfigurerequest.border_width; \
				masks |= CWBorderWidth; \
			}else{ \
				XWindowAttributes wa; \
				XGetWindowAttributes(display, event.xconfigurerequest.window, &wa); \
				windowAttributes.width -= wa.border_width; \
				windowAttributes.height -= wa.border_width; \
			} \
			if(masks){ \
				XConfigureWindow(display, event.xconfigurerequest.window, masks, &windowChanges); \
				XResizeWindow(display, event.xconfigurerequest.window, windowAttributes.width - borderX, windowAttributes.height - borderY); \
			} \
		} \
		new = 0; \
		break; \
	} \
} \
if(new){ \
	const XRRMonitorInfo monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
	if(event.xconfigurerequest.value_mask){ \
		XWindowChanges windowChanges; \
		unsigned int masks = None; \
		if(event.xconfigurerequest.value_mask & CWX){ \
			windowChanges.x = event.xconfigurerequest.x; \
			masks |= CWX; \
		} \
		if(event.xconfigurerequest.value_mask & CWY){ \
			windowChanges.y = event.xconfigurerequest.y; \
			masks |= CWY; \
		} \
		if(event.xconfigurerequest.value_mask & CWWidth){ \
			windowChanges.width = event.xconfigurerequest.width; \
			masks |= CWWidth; \
		} \
		if(event.xconfigurerequest.value_mask & CWHeight){ \
			windowChanges.height = event.xconfigurerequest.height; \
			masks |= CWHeight; \
		} \
		if(event.xconfigurerequest.value_mask & CWBorderWidth){ \
			windowChanges.border_width = event.xconfigurerequest.border_width; \
			windowChanges.width -= windowChanges.border_width; \
			windowChanges.height -= windowChanges.border_width; \
			masks |= CWBorderWidth; \
		} \
		if(masks){ \
			XConfigureWindow(display, event.xconfigurerequest.window, masks, &windowChanges); \
		} \
	} \
	XMoveResizeWindow(display, event.xconfigurerequest.window, monitorInfo.x, monitorInfo.y, monitorInfo.width / gridWidth - borderX, monitorInfo.height / gridHeight - borderY); \
} \
configureRequestEmergencyExit:{}
#endif
