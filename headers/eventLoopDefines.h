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
	shortcut[currentShortcut].command = GridingModeCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 14; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = TilingModeCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 42; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = ShowGridCommand; \
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
	shortcut[currentShortcut].keycode = 10; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = MoveFirstGridSlotCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 11; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = MoveLastGridSlotCommand; \
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
separatorAmount = 2 * containerAmount; \
Container container[containerAmount]; \
Window separator[separatorAmount]; \
{ \
	const Window rootWindow = XDefaultRootWindow(display); \
	XSelectInput(display, rootWindow, SubstructureRedirectMask); \
	{ \
		XVisualInfo visualInfo; \
		XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo); \
		const uint16_t windowAttributesMasks = CWBackPixel | CWBorderPixel | CWColormap; \
		XSetWindowAttributes windowAttributes = { \
			.background_pixel = separatorBackgroundColor, \
			.border_pixel = separatorBorderColor, \
			.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone) \
		}; \
		unsigned int currentBorder; \
		if(managementMode == FloatingManagementMode){ \
			currentBorder = border; \
			windowAttributes.background_pixel = floatingContainerBackgroundColor; \
		}else if(managementMode == GridingManagementMode){ \
			currentBorder = 0; \
			windowAttributes.background_pixel = gridingContainerBackgroundColor; \
		}else{ \
			for(unsigned int currentSeparator = 0; currentSeparator < separatorAmount; ++currentSeparator){ \
				separator[currentSeparator] = XCreateWindow(display, rootWindow, 0, 0, 1, 1, separatorBorder, visualInfo.depth, InputOutput, visualInfo.visual, windowAttributesMasks, &windowAttributes); \
			} \
			separatorsExist = 1; \
			currentBorder = 0; \
			windowAttributes.background_pixel = tilingContainerBackgroundColor; \
		} \
		windowAttributes.border_pixel = containerBorderColor; \
		Window w; \
		for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){ \
			w = XCreateWindow(display, rootWindow, 0, 0, 1, 1, currentBorder, visualInfo.depth, InputOutput, visualInfo.visual, windowAttributesMasks, &windowAttributes); \
			grabContainerKeysButtons(w, shortcutAmount, shortcut, buttonAmount, button); \
			container[currentContainer].window = w; \
			container[currentContainer].subwindow = None; \
		} \
	} \
}
#define REALLOCATE_SUBWINDOWS \
if(allocatedContainerAmount){ \
	FILE *file = fopen(subwindowsPath, "r"); \
	if(file){ \
		{ \
			char c; \
			Window subwindow; \
			bool negative; \
			int x; \
			int y; \
			unsigned int width; \
			unsigned int height; \
			uint32_t windowMasks; \
			uint32_t subwindowMasks; \
			ContainerOption option; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				subwindow = 0; \
				for(;;){ \
					if((c = fgetc(file)) != ' '){ \
						subwindow = subwindow * 10 + c - 48; \
					}else{ \
						break; \
					} \
				} \
				negative = 0; \
				x = 0; \
				for(;;){ \
					if((c = fgetc(file)) != ' '){ \
						if(c == '-'){ \
							negative = 1; \
						}else{ \
							x = x * 10 + c - 48; \
						} \
					}else{ \
						break; \
					} \
				} \
				if(negative){ \
					x = -x; \
				} \
				negative = 0; \
				y = 0; \
				for(;;){ \
					if((c = fgetc(file)) != ' '){ \
						if(c == '-'){ \
							negative = 1; \
						}else{ \
							y = y * 10 + c - 48; \
						} \
					}else{ \
						break; \
					} \
				} \
				if(negative){ \
					y = -y; \
				} \
				width = 0; \
				for(;;){ \
					if((c = fgetc(file)) != ' '){ \
						width = width * 10 + c - 48; \
					}else{ \
						break; \
					} \
				} \
				height = 0; \
				for(;;){ \
					if((c = fgetc(file)) != ' '){ \
						height = height * 10 + c - 48; \
					}else{ \
						break; \
					} \
				} \
				option = NoContainerOptions; \
				for(;;){ \
					if((c = fgetc(file)) != '\n'){ \
						option = option * 10 + c - 48; \
					}else{ \
						break; \
					} \
				} \
				if(option & InGridContainerOption){ \
					windowMasks = EnterWindowMask; \
					subwindowMasks = StructureNotifyMask; \
					XSetWindowBorderWidth(display, container[currentContainer].window, 0); \
					if(managementMode == FloatingManagementMode){ \
						XSetWindowBackground(display, container[currentContainer].window, inGridContainerBackgroundColor); \
					} \
				}else{ \
					if(managementMode == FloatingManagementMode){ \
						windowMasks = ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask; \
						subwindowMasks = ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask; \
					}else{ \
						windowMasks = EnterWindowMask; \
						subwindowMasks = StructureNotifyMask; \
					} \
				} \
				XSelectInput(display, container[currentContainer].window, windowMasks); \
				XSelectInput(display, subwindow, subwindowMasks); \
				XReparentWindow(display, subwindow, container[currentContainer].window, innerBorder, innerBorder); \
				XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
				XResizeWindow(display, subwindow, width - innerBorders, height - innerBorders); \
				container[currentContainer].subwindow = subwindow; \
				container[currentContainer].option = option; \
			} \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				XMapWindow(display, container[currentContainer].window); \
				XMapWindow(display, container[currentContainer].subwindow); \
			} \
		} \
		fclose(file); \
	} \
	lastCreatedContainer.window = container[allocatedContainerAmount - 1].window; \
	lastCreatedContainer.option = container[allocatedContainerAmount - 1].option; \
}
#define KEYPRESS \
for(unsigned int currentShortcut = 0; currentShortcut < shortcutAmount; ++currentShortcut){ \
	if(shortcut[currentShortcut].keycode == event.xkey.keycode && shortcut[currentShortcut].masks == event.xkey.state){ \
		const Command c = shortcut[currentShortcut].command; \
		if(c){ \
			if(c <= RootCommandCeiling){ \
				if(c == SystemCommand){ \
					goto system; \
				}else if(c == FloatingModeCommand){ \
					goto changeToFloatingMode; \
				}else if(c == GridingModeCommand){ \
					goto changeToGridingMode; \
				}else if(c == TilingModeCommand){ \
					goto changeToTilingMode; \
				}else if(c == ShowGridCommand){ \
					goto showGrid; \
				}else if(c == EnlargeGridCommand){ \
					goto englargeGrid; \
				}else if(c == ShrinkGridCommand){ \
					goto shrinkGrid; \
				}else if(c == RecascadeCommand){ \
					goto recascade; \
				}else if(c == RestartCommand){ \
					mode = RestartMode; \
				}else{ \
					mode = ExitMode; \
				} \
			}else{ \
				if(c == MoveCommand){ \
					goto move; \
				}else if(c == MoveTopCommand){ \
					goto moveTop; \
				}else if(c == MoveBottomCommand){ \
					goto moveBottom; \
				}else if(c == MoveLeftCommand){ \
					goto moveLeft; \
				}else if(c == MoveRightCommand){ \
					goto moveRight; \
				}else if(c == MoveCenterCommand){ \
					goto moveCenter; \
				}else if(c == MoveTopLeftCommand){ \
					goto moveTopLeft; \
				}else if(c == MoveTopRightCommand){ \
					goto moveTopRight; \
				}else if(c == MoveBottomLeftCommand){ \
					goto moveBottomLeft; \
				}else if(c == MoveBottomRightCommand){ \
					goto moveBottomRight; \
				}else if(c == MoveNextMonitorCommand || c == MovePreviousMonitorCommand){ \
					MOVENEXTPREVIOUSMONITOR_KEYPRESS \
				}else if(c == MoveAboveMonitorCommand){ \
					goto moveAboveMonitor; \
				}else if(c == MoveBelowMonitorCommand){ \
					goto moveBelowMonitor; \
				}else if(c == MoveLeftMonitorCommand){ \
					goto moveLeftMonitor; \
				}else if(c == MoveRightMonitorCommand){ \
					goto moveRightMonitor; \
				}else if(c == AddWindowToGridCommand){ \
					goto addWindowToGridSlot; \
				}else if(c == RemoveWindowFromGridCommand){ \
					goto removeWindowFromGrid; \
				}else if(c == ToggleWindowGridCommand){ \
					goto toggleWindowGrid; \
				}else if(c == MoveFirstGridSlotCommand){ \
					goto moveFirstGridSlot; \
				}else if(c == MoveLastGridSlotCommand){ \
					goto moveLastGridSlot; \
				}else if(c == MoveAboveGridSlotCommand){ \
					goto moveAboveGridSlot; \
				}else if(c == MoveBelowGridSlotCommand){ \
					goto moveBelowGridSlot; \
				}else if(c == MoveNextGridSlotCommand){ \
					goto moveNextGridSlot; \
				}else if(c == MovePreviousGridSlotCommand){ \
					goto movePreviousGridSlot; \
				}else if(c == MoveUpOnGridCommand){ \
					goto moveUpOnGrid; \
				}else if(c == MoveDownOnGridCommand){ \
					goto moveDownOnGrid; \
				}else if(c == MoveLeftOnGridCommand){ \
					goto moveLeftOnGrid; \
				}else if(c == MoveRightOnGridCommand){ \
					goto moveRightOnGrid; \
				}else if(c == ExtendWindowUpCommand){ \
					goto extendWindowUp; \
				}else if(c == ExtendWindowDownCommand){ \
					goto extendWindowDown; \
				}else if(c == ExtendWindowLeftCommand){ \
					goto extendWindowLeft; \
				}else if(c == ExtendWindowRightCommand){ \
					goto extendWindowRight; \
				}else if(c == ExtendWindowUpLeftCommand){ \
					goto extendWindowUpLeft; \
				}else if(c == ExtendWindowUpRightCommand){ \
					goto extendWindowUpRight; \
				}else if(c == ExtendWindowDownLeftCommand){ \
					goto extendWindowDownLeft; \
				}else if(c == ExtendWindowDownRightCommand){ \
					goto extendWindowDownRight; \
				}else if(c == ShrinkWindowUpCommand){ \
					goto shrinkWindowUp; \
				}else if(c == ShrinkWindowDownCommand){ \
					goto shrinkWindowDown; \
				}else if(c == ShrinkWindowLeftCommand){ \
					goto shrinkWindowLeft; \
				}else if(c == ShrinkWindowRightCommand){ \
					goto shrinkWindowRight; \
				}else if(c == ShrinkWindowUpLeftCommand){ \
					goto shrinkWindowUpLeft; \
				}else if(c == ShrinkWindowUpRightCommand){ \
					goto shrinkWindowUpRight; \
				}else if(c == ShrinkWindowDownLeftCommand){ \
					goto shrinkWindowDownLeft; \
				}else if(c == ShrinkWindowDownRightCommand){ \
					goto shrinkWindowDownRight; \
				}else if(c == FullscreenCommand){ \
					goto fullscreen; \
				}else if(c == BigscreenCommand){ \
					goto bigscreen; \
				}else if(c == CloseCommand){ \
					goto close; \
				}else{ \
					goto kill; \
				} \
			} \
		} \
		break; \
	} \
} \
if(mode != ContinueMode){ \
	break; \
}
#define BUTTONPRESS \
for(unsigned int currentButton = 0; currentButton < buttonAmount; ++currentButton){ \
	if(button[currentButton].button == event.xbutton.button && button[currentButton].masks == event.xbutton.state){ \
		const Command c = button[currentButton].command; \
		if(c){ \
			if(c <= RootCommandCeiling){ \
				if(c == SystemCommand){ \
					SYSTEM_KEYPRESS \
				}else if(c == FloatingModeCommand){ \
					FLOATINGMODE_KEYPRESS \
				}else if(c == GridingModeCommand){ \
					GRIDINGMODE_KEYPRESS \
				}else if(c == TilingModeCommand){ \
					TILINGMODE_KEYPRESS \
				}else if(c == ShowGridCommand){ \
					SHOWGRID_KEYPRESS \
				}else if(c == EnlargeGridCommand){ \
					ENLARGEGRID_KEYPRESS \
				}else if(c == ShrinkGridCommand){ \
					SHRINKGRID_KEYPRESS \
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
				}else if(c == MoveTopCommand){ \
					MOVETOP_KEYPRESS \
				}else if(c == MoveBottomCommand){ \
					MOVEBOTTOM_KEYPRESS \
				}else if(c == MoveLeftCommand){ \
					MOVELEFT_KEYPRESS \
				}else if(c == MoveRightCommand){ \
					MOVERIGHT_KEYPRESS \
				}else if(c == MoveCenterCommand){ \
					MOVECENTER_KEYPRESS \
				}else if(c == MoveTopLeftCommand){ \
					MOVETOPLEFT_KEYPRESS \
				}else if(c == MoveTopRightCommand){ \
					MOVETOPRIGHT_KEYPRESS \
				}else if(c == MoveBottomLeftCommand){ \
					MOVEBOTTOMLEFT_KEYPRESS \
				}else if(c == MoveBottomRightCommand){ \
					MOVEBOTTOMRIGHT_KEYPRESS \
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
				}else if(c == AddWindowToGridCommand){ \
					ADDWINDOWTOGRID_KEYPRESS \
				}else if(c == RemoveWindowFromGridCommand){ \
					REMOVEWINDOWFROMGRID_KEYPRESS \
				}else if(c == ToggleWindowGridCommand){ \
					TOGGLEWINDOWGRID_KEYPRESS \
				}else if(c == MoveFirstGridSlotCommand){ \
					MOVEFIRSTGRIDSLOT_KEYPRESS \
				}else if(c == MoveLastGridSlotCommand){ \
					MOVELASTGRIDSLOT_KEYPRESS \
				}else if(c == MoveAboveGridSlotCommand){ \
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
				}else if(c == MoveRightOnGridCommand){ \
					MOVERIGHTONGRID_KEYPRESS \
				}else if(c == ExtendWindowUpCommand){ \
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
				}else if(c == ShrinkWindowDownRightCommand){ \
					SHRINKWINDOWDOWNRIGHT_KEYPRESS \
				}else if(c == FullscreenCommand){ \
					FULLSCREEN_KEYPRESS \
				}else if(c == BigscreenCommand){ \
					BIGSCREEN_KEYPRESS \
				}else if(c == CloseCommand){ \
					CLOSE_KEYPRESS \
				}else{ \
					KILL_KEYPRESS \
				} \
			} \
		} \
		break; \
	} \
} \
if(mode != ContinueMode){ \
	break; \
}
#define SYSTEM_KEYPRESS \
system:{ \
	\
}
#define FLOATINGMODE_KEYPRESS \
changeToFloatingMode:{ \
	if(managementMode != FloatingManagementMode){ \
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
				Window window; \
				const uint32_t windowMasks = ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask; \
				const uint32_t subwindowMasks = ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask; \
				for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
					if(container[currentContainer].option & InGridContainerOption){ \
						window = container[currentContainer].window; \
						XSelectInput(display, window, windowMasks); \
						XSelectInput(display, container[currentContainer].subwindow, subwindowMasks); \
						XSetWindowBorderWidth(display, window, border); \
						XSetWindowBackground(display, window, floatingContainerBackgroundColor); \
						XUnmapWindow(display, window); \
						XMapWindow(display, window); \
						container[currentContainer].option ^= InGridContainerOption; \
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
				x = monitorInfo.x + (monitorInfo.width - width) / 2 - border; \
				y = monitorInfo.y + (monitorInfo.height - height) / 2 - border; \
				subwindowWidth = width - innerBorders; \
				subwindowHeight = height - innerBorders; \
				for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
					XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, subwindowWidth, subwindowHeight); \
					x += cascade.offsetX; \
					y += cascade.offsetY; \
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
					subwindowWidth = width - innerBorders; \
					subwindowHeight = height - innerBorders; \
					if(cascade.overrideGridWindows){ \
						for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
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
	} \
}
#define GRIDINGMODE_KEYPRESS \
changeToGridingMode:{ \
	if(managementMode != GridingManagementMode){ \
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
			XRRMonitorInfo monitorInfo; \
			Window window; \
			const uint32_t windowMasks = EnterWindowMask | SubstructureRedirectMask; \
			unsigned int gridX = 0; \
			unsigned int gridY = 0; \
			int x; \
			int y; \
			unsigned int width; \
			unsigned int height; \
			if(pointerInfo & ChangeToGridingPointerInfo){ \
				monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
			} \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				window = container[currentContainer].window; \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
					XSelectInput(display, window, windowMasks); \
					XSelectInput(display, container[currentContainer].subwindow, StructureNotifyMask); \
					XSetWindowBorderWidth(display, window, 0); \
					container[currentContainer].option |= InGridContainerOption; \
				} \
				XSetWindowBackground(display, window, gridingContainerBackgroundColor); \
				XUnmapWindow(display, window); \
				XMapWindow(display, window); \
				if(!(pointerInfo & ChangeToGridingPointerInfo)){ \
					monitorInfo = getWindowMonitorInfo(window, monitors, monitorAmount); \
				} \
				getGridSlotData(monitorInfo, gridX, gridY, gridWidth, gridHeight, &x, &y, &width, &height); \
				XMoveResizeWindow(display, window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
				XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
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
		managementMode = GridingManagementMode; \
	} \
}
#define TILINGMODE_KEYPRESS \
changeToTilingMode:{ \
	if(managementMode != TilingManagementMode){ \
		unsigned int currentSeparator; \
		{ \
			const Window rootWindow = XDefaultRootWindow(display);\
			XVisualInfo visualInfo; \
			XMatchVisualInfo(display, XDefaultScreen(display), 32, TrueColor, &visualInfo); \
			const uint16_t windowAttributesMasks = CWBackPixel | CWBorderPixel | CWColormap; \
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
			XRRMonitorInfo monitorInfo; \
			Window window; \
			Window subwindow; \
			const uint32_t windowMasks = EnterWindowMask | SubstructureRedirectMask; \
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
			const unsigned int totalSeparatorWidth = separatorWidth + separatorBorders; \
			const unsigned int totalSeparatorWidthGaps = totalSeparatorWidth + tilingGapsX; \
			if(pointerInfo & ChangeToTilingPointerInfo){ \
				monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
				middleX = allocatedContainerAmount / 2; \
				x = monitorInfo.x + tilingGapsX; \
				y = monitorInfo.y + tilingGapsY; \
				separatorAmount = allocatedContainerAmount - 1; \
				if(option & TilingUseSeparatorsOption){ \
					reservedSpace = 2 * allocatedContainerAmount * tilingGapsX + (allocatedContainerAmount - 1) * totalSeparatorWidth; \
				}else{ \
					reservedSpace = (allocatedContainerAmount + 1) * tilingGapsX; \
				} \
				normalWidth = (monitorInfo.width - reservedSpace) / allocatedContainerAmount; \
				abnormalWidth = (monitorInfo.width - reservedSpace) - (allocatedContainerAmount - 1) * normalWidth; \
				height = monitorInfo.height - 2 * tilingGapsY; \
				subwindowAbnormalWidth = normalWidth - innerBorders; \
				subwindowHeight = height - innerBorders; \
				abnormalWidthGaps = abnormalWidth + tilingGapsX; \
				subwindowNormalWidth = abnormalWidth - innerBorders; \
				normalWidthGaps = normalWidth + tilingGapsX; \
				separatorHeight = height - separatorBorders; \
				for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
					window = container[currentContainer].window; \
					subwindow = container[currentContainer].subwindow; \
					if(!(container[currentContainer].option & InGridContainerOption)){ \
						XSelectInput(display, window, windowMasks); \
						XSelectInput(display, subwindow, StructureNotifyMask); \
						XSetWindowBorderWidth(display, window, 0); \
						container[currentContainer].option |= InGridContainerOption; \
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
						x = monitors[currentMonitor].x + tilingGapsX; \
						y = monitors[currentMonitor].y + tilingGapsY; \
						separatorAmount = windowsAssigned - 1; \
						if(option & TilingUseSeparatorsOption){ \
							reservedSpace = 2 * windowsAssigned * tilingGapsX + separatorAmount * totalSeparatorWidth; \
						}else{ \
							reservedSpace = (windowsAssigned + 1) * tilingGapsX; \
						} \
						normalWidth = (monitors[currentMonitor].width - reservedSpace) / windowsAssigned; \
						abnormalWidth = (monitors[currentMonitor].width - reservedSpace) - separatorAmount * normalWidth; \
						height = monitors[currentMonitor].height - 2 * tilingGapsY; \
						subwindowAbnormalWidth = normalWidth - innerBorders; \
						subwindowHeight = height - innerBorders; \
						abnormalWidthGaps = abnormalWidth + tilingGapsX; \
						subwindowNormalWidth = abnormalWidth - innerBorders; \
						normalWidthGaps = normalWidth + tilingGapsX; \
						separatorHeight = height - separatorBorders; \
						for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
							monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
							if(monitorCompare(monitorInfo, monitors[currentMonitor])){ \
								window = container[currentContainer].window; \
								subwindow = container[currentContainer].subwindow; \
								if(!(container[currentContainer].option & InGridContainerOption)){ \
									XSelectInput(display, window, windowMasks); \
									XSelectInput(display, subwindow, StructureNotifyMask); \
									XSetWindowBorderWidth(display, window, 0); \
									container[currentContainer].option |= InGridContainerOption; \
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
	} \
}
#define SHOWGRID_KEYPRESS \
showGrid:{ \
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
	} \
}
#define ENLARGEGRID_KEYPRESS \
englargeGrid:{ \
	if(gridWidth < maxGridWidth || gridHeight < maxGridHeight){ \
		if(gridWidth < maxGridWidth){ \
			++gridWidth; \
		} \
		if(gridHeight < maxGridHeight){ \
			++gridHeight; \
		} \
		goto deleteGrid; \
	} \
}
#define SHRINKGRID_KEYPRESS \
shrinkGrid:{ \
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
				for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
					if(container[currentContainer].option & InGridContainerOption){ \
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
						XMoveResizeWindow(display, container[currentContainer].window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
						XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
					} \
				} \
			} \
		} \
	} \
}
#define RECASCADE_KEYPRESS \
recascade:{ \
	if(managementMode == FloatingManagementMode){ \
		if(allocatedContainerAmount){ \
			unsigned int width; \
			unsigned int height; \
			if(pointerInfo & RecascadePointerInfo){ \
				const XRRMonitorInfo monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
				if(option & FloatingFollowGrid){ \
					width = monitorInfo.width / gridWidth; \
					height = monitorInfo.height / gridHeight; \
				}else{ \
					width = monitorInfo.width / 2; \
					height = monitorInfo.height / 2; \
				} \
				int x = monitorInfo.x + (monitorInfo.width - width) / 2 - border; \
				int y = monitorInfo.y + (monitorInfo.height - height) / 2 - border; \
				if(cascade.overrideGridWindows){ \
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
						if(container[currentContainer].option & InGridContainerOption){ \
							XSetWindowBorderWidth(display, container[currentContainer].window, border); \
							XSetWindowBackground(display, container[currentContainer].window, floatingContainerBackgroundColor); \
							container[currentContainer].option ^= InGridContainerOption; \
						} \
						XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
						XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
						x += cascade.offsetX; \
						y += cascade.offsetY; \
					} \
				}else{ \
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
						if(!(container[currentContainer].option & InGridContainerOption)){ \
							XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
							XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
							x += cascade.offsetX; \
							y += cascade.offsetY; \
						} \
					} \
				} \
			}else{ \
				XRRMonitorInfo monitorInfo; \
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
					x = mi.x + (mi.width - width) / 2 - border; \
					y = mi.y + (mi.height - height) / 2 - border; \
					if(cascade.overrideGridWindows){ \
						for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
							monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
							if(monitorCompare(monitorInfo, mi)){ \
								if(container[currentContainer].option & InGridContainerOption){ \
									XSetWindowBorderWidth(display, container[currentContainer].window, border); \
									XSetWindowBackground(display, container[currentContainer].window, floatingContainerBackgroundColor); \
									container[currentContainer].option ^= InGridContainerOption; \
								} \
								XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
								XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
								x += cascade.offsetX; \
								y += cascade.offsetY; \
							} \
						} \
					}else{ \
						for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
							if(container[currentContainer].option & InGridContainerOption){ \
								monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
								if(monitorCompare(monitorInfo, mi)){ \
									XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
									XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
									x += cascade.offsetX; \
									y += cascade.offsetY; \
								} \
							} \
						} \
					} \
				} \
			} \
		} \
	} \
}
#define MOVE_KEYPRESS \
move:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
					XSelectInput(display, XDefaultRootWindow(display), ButtonReleaseMask | ButtonMotionMask | SubstructureRedirectMask); \
					XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
					if(event.xbutton.subwindow){ \
						if(option & FloatingMinimalMoveOption){ \
							motionContainer.x = windowAttributes.x + border - moveResizeWindowBorder; \
							motionContainer.y = windowAttributes.y + border - moveResizeWindowBorder; \
							XMoveResizeWindow(display, moveResizeWindow, motionContainer.x, motionContainer.y, windowAttributes.width, windowAttributes.height); \
							XMapRaised(display, moveResizeWindow); \
							motionContainer.window = moveResizeWindow; \
							moveResizeWindow = event.xany.window; \
							const unsigned int b = border; \
							border = moveResizeWindowBorder; \
							moveResizeWindowBorder = b; \
						}else{ \
							motionContainer.window = event.xany.window; \
							motionContainer.x = windowAttributes.x; \
							motionContainer.y = windowAttributes.y; \
						} \
						motionContainer.width = windowAttributes.width; \
						motionContainer.height = windowAttributes.height; \
						motionContainer.pointerOffsetX = event.xbutton.x + border; \
						motionContainer.pointerOffsetY = event.xbutton.y + border; \
						motionContainer.action = MoveMotionAction; \
					}else{ \
						motionContainer.subwindow = container[currentContainer].subwindow; \
						if(option & FloatingMinimalResizeOption){ \
							XSelectInput(display, motionContainer.subwindow, ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask); \
							motionContainer.x = windowAttributes.x - moveResizeWindowBorder; \
							motionContainer.y = windowAttributes.y - moveResizeWindowBorder; \
							XMoveResizeWindow(display, moveResizeWindow, motionContainer.x + border, motionContainer.y + border, windowAttributes.width, windowAttributes.height); \
							XMapRaised(display, moveResizeWindow); \
							motionContainer.window = moveResizeWindow; \
							moveResizeWindow = event.xany.window; \
							motionContainer.pointerOffsetX = event.xbutton.x + border + moveResizeWindowBorder; \
							motionContainer.pointerOffsetY = event.xbutton.y + border + moveResizeWindowBorder; \
							motionContainer.positionOffset = border; \
						}else{ \
							motionContainer.window = event.xany.window; \
							motionContainer.x = windowAttributes.x; \
							motionContainer.y = windowAttributes.y; \
							motionContainer.pointerOffsetX = event.xbutton.x + border; \
							motionContainer.pointerOffsetY = event.xbutton.y + border; \
							motionContainer.positionOffset = 0; \
						} \
						motionContainer.width = windowAttributes.width; \
						motionContainer.height = windowAttributes.height; \
						motionContainer.action = ResizeMotionAction; \
						if(event.xbutton.y < (int)innerBorder){ \
							if(event.xbutton.x < (int)innerBorder){ \
								motionContainer.subaction = UpLeftResizeMotionSubaction; \
							}else if(event.xbutton.x < windowAttributes.width - (int)innerBorder){ \
								motionContainer.subaction = UpResizeMotionSubaction; \
							}else{ \
								motionContainer.subaction = UpRightResizeMotionSubaction; \
							} \
						}else if(event.xbutton.y < windowAttributes.height - (int)innerBorder){ \
							if(event.xbutton.x < (int)innerBorder){ \
								motionContainer.subaction = LeftResizeMotionSubaction; \
							}else{ \
								motionContainer.subaction = RightResizeMotionSubaction; \
							} \
						}else{ \
							if(event.xbutton.x < (int)innerBorder){ \
								motionContainer.subaction = DownLeftResizeMotionSubaction; \
							}else if(event.xbutton.x < windowAttributes.width - (int)innerBorder){ \
								motionContainer.subaction = DownResizeMotionSubaction; \
							}else{ \
								motionContainer.subaction = DownRightResizeMotionSubaction; \
							} \
						} \
					} \
					motionContainer.options = CanActOption; \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVETOP_KEYPRESS \
moveTop:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
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
						XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y - border, width, height); \
					} \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVEBOTTOM_KEYPRESS \
moveBottom:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
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
						XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y + monitorInfo.height - height - border, width, height); \
					} \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVELEFT_KEYPRESS \
moveLeft:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
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
						XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y - border, width, height); \
					} \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVERIGHT_KEYPRESS \
moveRight:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
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
						XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - border, monitorInfo.y - border, width, height); \
					} \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVECENTER_KEYPRESS \
moveCenter:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
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
						XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - width) / 2 - border, monitorInfo.y + (monitorInfo.height - height) / 2 - border, width, height); \
					} \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVETOPLEFT_KEYPRESS \
moveTopLeft:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
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
						XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y - border, width, height); \
					} \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVETOPRIGHT_KEYPRESS \
moveTopRight:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
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
						XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - border, monitorInfo.y - border, width, height); \
					} \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVEBOTTOMLEFT_KEYPRESS \
moveBottomLeft:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
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
						XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y + monitorInfo.height - height - border, width, height); \
					} \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVEBOTTOMRIGHT_KEYPRESS \
moveBottomRight:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
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
						XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - border, monitorInfo.y + monitorInfo.height - height - border, width, height); \
					} \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVENEXTPREVIOUSMONITOR_KEYPRESS \
if(managementMode == FloatingManagementMode){ \
	bool next; \
	if(c == MoveNextMonitorCommand){ \
		next = 1; \
	}else{ \
		next = 0; \
	} \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			if(!(container[currentContainer].option & InGridContainerOption)){ \
				XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
				for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
					if(monitorCompare(monitors[currentMonitor], monitorInfo)){ \
						if(next){ \
							if(++currentMonitor < monitorAmount){ \
								monitorInfo = monitors[currentMonitor]; \
								unsigned int width; \
								unsigned int height; \
								if(option & FloatingFollowGrid){ \
									width = monitorInfo.width / gridWidth; \
									height = monitorInfo.height / gridHeight; \
								}else{ \
									width = monitorInfo.width / 2; \
									height = monitorInfo.height / 2; \
								} \
								XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - width) / 2 - border, monitorInfo.y + (monitorInfo.height - height) / 2 - border, width, height); \
								XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
							} \
						}else{ \
							if((int)--currentMonitor >= 0){ \
								monitorInfo = monitors[currentMonitor]; \
								unsigned int width; \
								unsigned int height; \
								if(option & FloatingFollowGrid){ \
									width = monitorInfo.width / gridWidth; \
									height = monitorInfo.height / gridHeight; \
								}else{ \
									width = monitorInfo.width / 2; \
									height = monitorInfo.height / 2; \
								} \
								XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - width) / 2 - border, monitorInfo.y + (monitorInfo.height - height) / 2 - border, width, height); \
								XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
							} \
						} \
						break; \
					} \
				} \
			} \
			break; \
		} \
	} \
}
#define MOVEABOVEMONITOR_KEYPRESS \
moveAboveMonitor:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(monitorInfo.y){ \
				for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
					if(monitorInfo.x == monitors[currentMonitor].x && monitorInfo.y == monitors[currentMonitor].y + monitors[currentMonitor].height){ \
						if(managementMode == TilingManagementMode){ \
\
\
\
							\
\
\
\
						}else if(managementMode == GridingManagementMode || container[currentContainer].option & InGridContainerOption){ \
							moveInGridContainerToMonitor(monitors[currentMonitor], container[currentContainer], gridWidth, gridHeight, innerBorders); \
						}else{ \
							moveContainerToMonitor(monitorInfo, monitors[currentMonitor], container[currentContainer].window, container[currentContainer].subwindow, border, innerBorders); \
						} \
						break; \
					} \
				} \
			} \
			break; \
		} \
	} \
}
#define MOVEBELOWMONITOR_KEYPRESS \
moveBelowMonitor:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(monitorInfo.y + monitorInfo.height < XDisplayHeight(display, XDefaultScreen(display))){ \
				for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
					if(monitorInfo.x == monitors[currentMonitor].x && monitorInfo.y + monitorInfo.height == monitors[currentMonitor].y){ \
						if(managementMode == TilingManagementMode){ \
\
\
\
							\
\
\
\
						}else if(managementMode == GridingManagementMode || container[currentContainer].option & InGridContainerOption){ \
							moveInGridContainerToMonitor(monitors[currentMonitor], container[currentContainer], gridWidth, gridHeight, innerBorders); \
						}else{ \
							moveContainerToMonitor(monitorInfo, monitors[currentMonitor], container[currentContainer].window, container[currentContainer].subwindow, border, innerBorders); \
						} \
						break; \
					} \
				} \
			} \
			break; \
		} \
	} \
}
#define MOVELEFTMONITOR_KEYPRESS \
moveLeftMonitor:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(monitorInfo.x){ \
				for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
					if(monitorInfo.x == monitors[currentMonitor].x + monitors[currentMonitor].width && monitorInfo.y == monitors[currentMonitor].y){ \
						if(managementMode == TilingManagementMode){ \
\
\
\
							\
\
\
\
						}else if(managementMode == GridingManagementMode || container[currentContainer].option & InGridContainerOption){ \
							moveInGridContainerToMonitor(monitors[currentMonitor], container[currentContainer], gridWidth, gridHeight, innerBorders); \
						}else{ \
							moveContainerToMonitor(monitorInfo, monitors[currentMonitor], container[currentContainer].window, container[currentContainer].subwindow, border, innerBorders); \
						} \
						break; \
					} \
				} \
			} \
			break; \
		} \
	} \
}
#define MOVERIGHTMONITOR_KEYPRESS \
moveRightMonitor:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			if(monitorInfo.x + monitorInfo.width < XDisplayWidth(display, XDefaultScreen(display))){ \
				for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
					if(monitorInfo.x + monitorInfo.width == monitors[currentMonitor].x && monitorInfo.y == monitors[currentMonitor].y){ \
						if(managementMode == TilingManagementMode){ \
\
\
\
							\
\
\
\
						}else if(managementMode == GridingManagementMode || container[currentContainer].option & InGridContainerOption){ \
							moveInGridContainerToMonitor(monitors[currentMonitor], container[currentContainer], gridWidth, gridHeight, innerBorders); \
						}else{ \
							moveContainerToMonitor(monitorInfo, monitors[currentMonitor], container[currentContainer].window, container[currentContainer].subwindow, border, innerBorders); \
						} \
						break; \
					} \
				} \
			} \
			break; \
		} \
	} \
}
#define ADDWINDOWTOGRID_KEYPRESS \
addWindowToGridSlot:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
					goto addToGrid; \
				} \
				break; \
			} \
		} \
	} \
}
#define REMOVEWINDOWFROMGRID_KEYPRESS \
removeWindowFromGrid:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].option & InGridContainerOption){ \
					goto removeFromGrid; \
				} \
				break; \
			} \
		} \
	} \
}
#define TOGGLEWINDOWGRID_KEYPRESS \
toggleWindowGrid:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!(container[currentContainer].option & InGridContainerOption)){ \
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
									monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
								} \
								if(option & FloatingFollowGrid){ \
									if(defaultGridPosition == TopLeftDefaultGridPosition){ \
										positionX = 0; \
										positionY = 0; \
									}else if(defaultGridPosition == TopRightDefaultGridPosition){ \
										positionX = gridWidth - 1; \
										positionY = 0; \
									}else if(defaultGridPosition == BottomLeftDefaultGridPosition){ \
										positionX = 0; \
										positionY = gridHeight - 1; \
									}else if(defaultGridPosition == BottomRightDefaultGridPosition){ \
										positionX = gridWidth - 1; \
										positionY = gridHeight - 1; \
									}else{ \
										positionX = gridWidth / 2; \
										positionY = gridHeight / 2; \
									} \
								}else{ \
									positionX = 0; \
									positionY = 0; \
								} \
								getGridSlotData(monitorInfo, positionX, positionY, gridWidth, gridHeight, &x, &y, &width, &height); \
								XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
							} \
							XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
						} \
						container[currentContainer].option |= InGridContainerOption; \
						container[currentContainer].gridX = positionX; \
						container[currentContainer].gridY = positionY; \
						container[currentContainer].gridWidth = 1; \
						container[currentContainer].gridHeight = 1; \
					} \
				}else{ \
					removeFromGrid:{ \
						XSelectInput(display, event.xany.window, ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask); \
						XSelectInput(display, container[currentContainer].subwindow, ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask); \
						XSetWindowBorderWidth(display, event.xany.window, border); \
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
								XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - width) / 2 - border, monitorInfo.y + (monitorInfo.height - height) / 2 - border, width, height); \
							} \
							XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
						} \
						container[currentContainer].option ^= InGridContainerOption; \
					} \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVEFIRSTGRIDSLOT_KEYPRESS \
moveFirstGridSlot:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].option & InGridContainerOption){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						int x; \
						int y; \
						const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
						getGridSlotData(monitorInfo, 0, 0, gridWidth, gridHeight, &x, &y, &width, &height); \
						XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
					} \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
					container[currentContainer].gridX = 0; \
					container[currentContainer].gridY = 0; \
					container[currentContainer].gridWidth = 1; \
					container[currentContainer].gridHeight = 1; \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVELASTGRIDSLOT_KEYPRESS \
moveLastGridSlot:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].option & InGridContainerOption){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						int x; \
						int y; \
						const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
						getGridSlotData(monitorInfo, gridWidth - 1, gridHeight - 1, gridWidth, gridHeight, &x, &y, &width, &height); \
						XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
					} \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
					container[currentContainer].gridX = gridWidth - 1; \
					container[currentContainer].gridY = gridHeight - 1; \
					container[currentContainer].gridWidth = 1; \
					container[currentContainer].gridHeight = 1; \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVEABOVEGRIDSLOT_KEYPRESS \
moveAboveGridSlot:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].option & InGridContainerOption){ \
					if(container[currentContainer].gridX || container[currentContainer].gridY){ \
						if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
							if(container[currentContainer].gridY){ \
								--container[currentContainer].gridY; \
							}else{ \
								if(option & GridingAllowBoundaryBreakYOption){ \
									--container[currentContainer].gridX; \
									container[currentContainer].gridY = gridHeight - 1; \
								}else{ \
									break; \
								} \
							} \
							goto moveGridSlot; \
						} \
					} \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVEBELOWGRIDSLOT_KEYPRESS \
moveBelowGridSlot:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].option & InGridContainerOption){ \
					if(container[currentContainer].gridX < gridWidth - 1 || container[currentContainer].gridY < gridHeight - 1){ \
						if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
							if(container[currentContainer].gridY < gridHeight - 1){ \
								++container[currentContainer].gridY; \
							}else{ \
								if(option & GridingAllowBoundaryBreakYOption){ \
									++container[currentContainer].gridX; \
									container[currentContainer].gridY = 0; \
								}else{ \
									break; \
								} \
							} \
							goto moveGridSlot; \
						} \
					} \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVENEXTGRIDSLOT_KEYPRESS \
moveNextGridSlot:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].option & InGridContainerOption){ \
					if(container[currentContainer].gridX < gridWidth - 1 || container[currentContainer].gridY < gridHeight - 1){ \
						if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
							if(container[currentContainer].gridX < gridWidth - 1){ \
								++container[currentContainer].gridX; \
							}else{ \
								if(option & GridingAllowBoundaryBreakXOption){ \
									container[currentContainer].gridX = 0; \
									++container[currentContainer].gridY; \
								}else{ \
									break; \
								} \
							} \
							goto moveGridSlot; \
						} \
					} \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVEPREVIOUSGRIDSLOT_KEYPRESS \
movePreviousGridSlot:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].option & InGridContainerOption){ \
					if(container[currentContainer].gridX || container[currentContainer].gridY){ \
						if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
							if(container[currentContainer].gridX){ \
								--container[currentContainer].gridX; \
							}else{ \
								if(option & GridingAllowBoundaryBreakXOption){ \
									container[currentContainer].gridX = gridWidth - 1; \
									--container[currentContainer].gridY; \
								}else{ \
									break; \
								} \
							} \
							moveGridSlot:{ \
								int x; \
								int y; \
								unsigned int width; \
								unsigned int height; \
								const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
								getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, &width, &height); \
								XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
								XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
							} \
						} \
					} \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVEUPONGRID_KEYPRESS \
moveUpOnGrid:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].option & InGridContainerOption && container[currentContainer].gridY){ \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					int x; \
					int y; \
					unsigned int width; \
					unsigned int height; \
					{ \
						int x1; \
						int y1; \
						getGridSlotData(monitorInfo, container[currentContainer].gridX, --container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, NULL, NULL); \
						getGridSlotData(monitorInfo, container[currentContainer].gridX + container[currentContainer].gridWidth - 1, container[currentContainer].gridY + container[currentContainer].gridHeight - 1, gridWidth, gridHeight, &x1, &y1, &width, &height); \
						width += x1 - x; \
						height += y1 - y; \
					} \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVEDOWNONGRID_KEYPRESS \
moveDownOnGrid:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].option & InGridContainerOption && container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					int x; \
					int y; \
					unsigned int width; \
					unsigned int height; \
					{ \
						int x1; \
						int y1; \
						getGridSlotData(monitorInfo, container[currentContainer].gridX, ++container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, NULL, NULL); \
						getGridSlotData(monitorInfo, container[currentContainer].gridX + container[currentContainer].gridWidth - 1, container[currentContainer].gridY + container[currentContainer].gridHeight - 1, gridWidth, gridHeight, &x1, &y1, &width, &height); \
						width += x1 - x; \
						height += y1 - y; \
					} \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVELEFTONGRID_KEYPRESS \
moveLeftOnGrid:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].option & InGridContainerOption && container[currentContainer].gridX){ \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					int x; \
					int y; \
					unsigned int width; \
					unsigned int height; \
					{ \
						int x1; \
						int y1; \
						getGridSlotData(monitorInfo, --container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, NULL, NULL); \
						getGridSlotData(monitorInfo, container[currentContainer].gridX + container[currentContainer].gridWidth - 1, container[currentContainer].gridY + container[currentContainer].gridHeight - 1, gridWidth, gridHeight, &x1, &y1, &width, &height); \
						width += x1 - x; \
						height += y1 - y; \
					} \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define MOVERIGHTONGRID_KEYPRESS \
moveRightOnGrid:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].option & InGridContainerOption && container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth){ \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					int x; \
					int y; \
					unsigned int width; \
					unsigned int height; \
					{ \
						int x1; \
						int y1; \
						getGridSlotData(monitorInfo, ++container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, NULL, NULL); \
						getGridSlotData(monitorInfo, container[currentContainer].gridX + container[currentContainer].gridWidth - 1, container[currentContainer].gridY + container[currentContainer].gridHeight - 1, gridWidth, gridHeight, &x1, &y1, &width, &height); \
						width += x1 - x; \
						height += y1 - y; \
					} \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
}
#define EXTENDWINDOWUP_KEYPRESS \
extendWindowUp:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int y; \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(!container[currentContainer].gridY){ \
					break; \
				} \
				const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
				getGridSlotData(monitorInfo, container[currentContainer].gridX, --container[currentContainer].gridY, gridWidth, gridHeight, NULL, &y, NULL, &height); \
				++container[currentContainer].gridHeight; \
				y += monitorInfo.y; \
				height += windowAttributes.height; \
			}else{ \
				y = windowAttributes.y - floatingExtendHeight; \
				height = windowAttributes.height + floatingExtendHeight; \
			} \
			XMoveResizeWindow(display, event.xany.window, windowAttributes.x, y, windowAttributes.width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define EXTENDWINDOWDOWN_KEYPRESS \
extendWindowDown:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridY + container[currentContainer].gridHeight == gridHeight){ \
					break; \
				} \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
				++container[currentContainer].gridHeight; \
				height += windowAttributes.height; \
			}else{ \
				height = windowAttributes.height + floatingExtendHeight; \
			} \
			XResizeWindow(display, event.xany.window, windowAttributes.width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define EXTENDWINDOWLEFT_KEYPRESS \
extendWindowLeft:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int x; \
			unsigned int width; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(!container[currentContainer].gridX){ \
					break; \
				} \
				const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
				getGridSlotData(monitorInfo, --container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, NULL, &width, NULL); \
				++container[currentContainer].gridWidth; \
				x += monitorInfo.x; \
				width += windowAttributes.width; \
			}else{ \
				x = windowAttributes.x - floatingExtendWidth; \
				width = windowAttributes.width + floatingExtendWidth; \
			} \
			XMoveResizeWindow(display, event.xany.window, x, windowAttributes.y, width, windowAttributes.height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, windowAttributes.height - innerBorders); \
			break; \
		} \
	} \
}
#define EXTENDWINDOWRIGHT_KEYPRESS \
extendWindowRight:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			unsigned int width; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridX + container[currentContainer].gridWidth == gridWidth){ \
					break; \
				} \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX + container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
				++container[currentContainer].gridWidth; \
				width += windowAttributes.width; \
			}else{ \
				width = windowAttributes.width + floatingExtendWidth; \
			} \
			XResizeWindow(display, event.xany.window, width, windowAttributes.height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, windowAttributes.height - innerBorders); \
			break; \
		} \
	} \
}
#define EXTENDWINDOWUPLEFT_KEYPRESS \
extendWindowUpLeft:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int x; \
			int y; \
			unsigned int width; \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridY){ \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					getGridSlotData(monitorInfo, container[currentContainer].gridX, --container[currentContainer].gridY, gridWidth, gridHeight, NULL, &y, NULL, &height); \
					++container[currentContainer].gridHeight; \
					y += monitorInfo.y; \
					height += windowAttributes.height; \
				}else{ \
					y = windowAttributes.y; \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridX){ \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					getGridSlotData(monitorInfo, --container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, NULL, &width, NULL); \
					++container[currentContainer].gridWidth; \
					x += monitorInfo.x; \
					width += windowAttributes.width; \
				}else{ \
					x = windowAttributes.x; \
					width = windowAttributes.width; \
				} \
				if(width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				x = windowAttributes.x - floatingExtendWidth; \
				y = windowAttributes.y - floatingExtendHeight; \
				width = windowAttributes.width + floatingExtendWidth; \
				height = windowAttributes.height + floatingExtendHeight; \
			} \
			XMoveResizeWindow(display, event.xany.window, x, y, width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define EXTENDWINDOWUPRIGHT_KEYPRESS \
extendWindowUpRight:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int y; \
			unsigned int width; \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridY){ \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					getGridSlotData(monitorInfo, container[currentContainer].gridX, --container[currentContainer].gridY, gridWidth, gridHeight, NULL, &y, NULL, &height); \
					++container[currentContainer].gridHeight; \
					y += monitorInfo.y; \
					height += windowAttributes.height; \
				}else{ \
					y = windowAttributes.y; \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX + container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
					++container[currentContainer].gridWidth; \
					width += windowAttributes.width; \
				}else{ \
					width = windowAttributes.width; \
				} \
				if(width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				y = windowAttributes.y - floatingExtendHeight; \
				width = windowAttributes.width + floatingExtendWidth; \
				height = windowAttributes.height + floatingExtendHeight; \
			} \
			XMoveResizeWindow(display, event.xany.window, windowAttributes.x, y, width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define EXTENDWINDOWDOWNLEFT_KEYPRESS \
extendWindowDownLeft:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int x; \
			unsigned int width; \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
					++container[currentContainer].gridHeight; \
					height += windowAttributes.height; \
				}else{ \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridX){ \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount); \
					getGridSlotData(monitorInfo, --container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, NULL, &width, NULL); \
					++container[currentContainer].gridWidth; \
					x += monitorInfo.x; \
					width += windowAttributes.width; \
				}else{ \
					x = windowAttributes.x; \
					width = windowAttributes.width; \
				} \
				if(width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				x = windowAttributes.x - floatingExtendWidth; \
				width = windowAttributes.width + floatingExtendWidth; \
				height = windowAttributes.height + floatingExtendHeight; \
			} \
			XMoveResizeWindow(display, event.xany.window, x, windowAttributes.y, width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define EXTENDWINDOWDOWNRIGHT_KEYPRESS \
extendWindowDownRight:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			unsigned int width; \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
					++container[currentContainer].gridHeight; \
					height += windowAttributes.height; \
				}else{ \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX + container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
					++container[currentContainer].gridWidth; \
					width += windowAttributes.width; \
				}else{ \
					width = windowAttributes.width; \
				} \
				if(width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				width = windowAttributes.width + floatingExtendWidth; \
				height = windowAttributes.height + floatingExtendHeight; \
			} \
			XResizeWindow(display, event.xany.window, width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define SHRINKWINDOWUP_KEYPRESS \
shrinkWindowUp:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridHeight == 1){ \
					break; \
				} \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY + --container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
				height = windowAttributes.height - height; \
			}else{ \
				height = windowAttributes.height - floatingShrinkHeight; \
			} \
			XResizeWindow(display, event.xany.window, windowAttributes.width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define SHRINKWINDOWDOWN_KEYPRESS \
shrinkWindowDown:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int y; \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridHeight == 1){ \
					break; \
				} \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
				++container[currentContainer].gridY; \
				--container[currentContainer].gridHeight; \
				y = windowAttributes.y + height; \
				height = windowAttributes.height - height; \
			}else{ \
				y = windowAttributes.y + floatingShrinkHeight; \
				height = windowAttributes.height - floatingShrinkHeight; \
			} \
			XMoveResizeWindow(display, event.xany.window, windowAttributes.x, y, windowAttributes.width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define SHRINKWINDOWLEFT_KEYPRESS \
shrinkWindowLeft:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			unsigned int width; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridWidth == 1){ \
					break; \
				} \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX + --container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
				width = windowAttributes.width - width; \
			}else{ \
				width = windowAttributes.width - floatingShrinkWidth; \
			} \
			XResizeWindow(display, event.xany.window, width, windowAttributes.height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, windowAttributes.height - innerBorders); \
			break; \
		} \
	} \
}
#define SHRINKWINDOWRIGHT_KEYPRESS \
shrinkWindowRight:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int x; \
			unsigned int width; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridWidth == 1){ \
					break; \
				} \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
				++container[currentContainer].gridX; \
				--container[currentContainer].gridWidth; \
				x = windowAttributes.x + width; \
				width = windowAttributes.width - width; \
			}else{ \
				x = windowAttributes.x + floatingShrinkWidth; \
				width = windowAttributes.width - floatingShrinkWidth; \
			} \
			XMoveResizeWindow(display, event.xany.window, x, windowAttributes.y, width, windowAttributes.height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, windowAttributes.height - innerBorders); \
			break; \
		} \
	} \
}
#define SHRINKWINDOWUPLEFT_KEYPRESS \
shrinkWindowUpLeft:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			unsigned int width; \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridHeight > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY + --container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
					height = windowAttributes.height - height; \
				}else{ \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridWidth > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX + --container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
					width = windowAttributes.width - width; \
				}else{ \
					width = windowAttributes.width; \
				} \
				if(width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				width = windowAttributes.width - floatingShrinkWidth; \
				height = windowAttributes.height - floatingShrinkHeight; \
			} \
			XResizeWindow(display, event.xany.window, width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define SHRINKWINDOWUPRIGHT_KEYPRESS \
shrinkWindowUpRight:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int x; \
			unsigned int width; \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridHeight > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY + --container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
					height = windowAttributes.height - height; \
				}else{ \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridWidth > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
					++container[currentContainer].gridX; \
					--container[currentContainer].gridWidth; \
					x = windowAttributes.x + width; \
					width = windowAttributes.width - width; \
				}else{ \
					x = windowAttributes.x; \
					width = windowAttributes.width; \
				} \
				if(width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				x = windowAttributes.x + floatingShrinkWidth; \
				width = windowAttributes.width - floatingShrinkWidth; \
				height = windowAttributes.height - floatingShrinkHeight; \
			} \
			XMoveResizeWindow(display, event.xany.window, x, windowAttributes.y, width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define SHRINKWINDOWDOWNLEFT_KEYPRESS \
shrinkWindowDownLeft:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int y; \
			unsigned int width; \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridHeight > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
					++container[currentContainer].gridY; \
					--container[currentContainer].gridHeight; \
					y = windowAttributes.y + height; \
					height = windowAttributes.height - height; \
				}else{ \
					y = windowAttributes.y; \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridWidth > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX + --container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
					width = windowAttributes.width - width; \
				}else{ \
					width = windowAttributes.width; \
				} \
				if(width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				y = windowAttributes.y + floatingShrinkHeight; \
				width = windowAttributes.width - floatingShrinkWidth; \
				height = windowAttributes.height - floatingShrinkHeight; \
			} \
			XMoveResizeWindow(display, event.xany.window, windowAttributes.x, y, width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define SHRINKWINDOWDOWNRIGHT_KEYPRESS \
shrinkWindowDownRight:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int x; \
			int y; \
			unsigned int width; \
			unsigned int height; \
			if(container[currentContainer].option & InGridContainerOption){ \
				if(container[currentContainer].gridHeight > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
					++container[currentContainer].gridY; \
					--container[currentContainer].gridHeight; \
					y = windowAttributes.y + height; \
					height = windowAttributes.height - height; \
				}else{ \
					y = windowAttributes.y; \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridWidth > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window, monitors, monitorAmount), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
					++container[currentContainer].gridX; \
					--container[currentContainer].gridWidth; \
					x = windowAttributes.x + width; \
					width = windowAttributes.width - width; \
				}else{ \
					x = windowAttributes.x; \
					width = windowAttributes.width; \
				} \
				if(width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				x = windowAttributes.x + floatingShrinkWidth; \
				y = windowAttributes.y + floatingShrinkHeight; \
				width = windowAttributes.width - floatingShrinkWidth; \
				height = windowAttributes.height - floatingShrinkHeight; \
			} \
			XMoveResizeWindow(display, event.xany.window, x, y, width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define FULLSCREEN_KEYPRESS \
fullscreen:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
			if(!(container[currentContainer].option & InGridContainerOption)){ \
				monitorInfo.x -= border; \
				monitorInfo.y -= border; \
			} \
			if(windowAttributes.x == monitorInfo.x && windowAttributes.y == monitorInfo.y && windowAttributes.width == monitorInfo.width && windowAttributes.height == monitorInfo.height){ \
				{ \
					XEvent e = { \
						.xclient = { \
							.type = ClientMessage, \
							.send_event = False, \
							.display = display, \
							.window = container[currentContainer].subwindow, \
							.message_type = XInternAtom(display, "_NET_WM_STATE", False), \
							.format = 32, \
							.data = { \
								.l[0] = XInternAtom(display, "_NET_WM_STATE_REMOVE", False), \
								.l[1] = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False), \
								.l[2] = 0, \
								.l[3] = 0 \
							} \
						} \
					}; \
					XSendEvent(display, e.xclient.window, False, PropertyChangeMask, &e); \
				} \
				if(managementMode == TilingManagementMode){ \
\
\
\
					\
\
\
\
				}else if(managementMode == GridingManagementMode || container[currentContainer].option & InGridContainerOption){ \
					int x1; \
					int y1; \
					getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &windowAttributes.x, &windowAttributes.y, NULL, NULL); \
					getGridSlotData(monitorInfo, container[currentContainer].gridX + container[currentContainer].gridWidth - 1, container[currentContainer].gridY + container[currentContainer].gridHeight - 1, gridWidth, gridHeight, &x1, &y1, (unsigned int *)&windowAttributes.width, (unsigned int *)&windowAttributes.height); \
					windowAttributes.width += x1 - windowAttributes.x; \
					windowAttributes.height += y1 - windowAttributes.y; \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + windowAttributes.x, monitorInfo.y + windowAttributes.y, windowAttributes.width, windowAttributes.height); \
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - innerBorders, windowAttributes.height - innerBorders); \
				}else{ \
					monitorInfo.x += border; \
					monitorInfo.y += border; \
					if(pointerInfo & FullscreenPointerInfo){ \
						monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
					} \
					if(option & FloatingFollowGrid){ \
						windowAttributes.width = monitorInfo.width / gridWidth; \
						windowAttributes.height = monitorInfo.height / gridHeight; \
					}else{ \
						windowAttributes.width = monitorInfo.width / 2; \
						windowAttributes.height = monitorInfo.height / 2; \
					} \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - windowAttributes.width) / 2 - border, monitorInfo.y + (monitorInfo.height - windowAttributes.height) / 2 - border, windowAttributes.width, windowAttributes.height); \
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - innerBorders, windowAttributes.height - innerBorders); \
				} \
			}else{ \
				{ \
					XEvent e = { \
						.xclient = { \
							.type = ClientMessage, \
							.send_event = False, \
							.display = display, \
							.window = container[currentContainer].subwindow, \
							.message_type = XInternAtom(display, "_NET_WM_STATE", False), \
							.format = 32, \
							.data = { \
								.l[0] = XInternAtom(display, "_NET_WM_STATE_ADD", False), \
								.l[1] = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False), \
								.l[2] = 0, \
								.l[3] = 0 \
							} \
						} \
					}; \
					XSendEvent(display, e.xclient.window, False, PropertyChangeMask, &e); \
\
\
\
					/*Atom type;
					int format;
					unsigned long int itemAmount;
					unsigned long int bytesAfter;
					unsigned char *data;
					const long int size = sizeof(Atom);
					XChangeProperty(display, destination, property[current], type, format, PropModeReplace, data, itemAmount);*/ \
\
\
\
				} \
				XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
				XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - innerBorders, monitorInfo.height - innerBorders); \
			} \
			break; \
		} \
	} \
}
#define BIGSCREEN_KEYPRESS \
bigscreen:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window, monitors, monitorAmount); \
			XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
			if(!(container[currentContainer].option & InGridContainerOption)){ \
				monitorInfo.x -= border; \
				monitorInfo.y -= border; \
			} \
			if(windowAttributes.x == monitorInfo.x && windowAttributes.y == monitorInfo.y && windowAttributes.width == monitorInfo.width && windowAttributes.height == monitorInfo.height){ \
				if(managementMode == TilingManagementMode){ \
\
\
\
					\
\
\
\
				}else if(managementMode == GridingManagementMode || container[currentContainer].option & InGridContainerOption){ \
					int x1; \
					int y1; \
					getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &windowAttributes.x, &windowAttributes.y, NULL, NULL); \
					getGridSlotData(monitorInfo, container[currentContainer].gridX + container[currentContainer].gridWidth - 1, container[currentContainer].gridY + container[currentContainer].gridHeight - 1, gridWidth, gridHeight, &x1, &y1, (unsigned int *)&windowAttributes.width, (unsigned int *)&windowAttributes.height); \
					windowAttributes.width += x1 - windowAttributes.x; \
					windowAttributes.height += y1 - windowAttributes.y; \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + windowAttributes.x, monitorInfo.y + windowAttributes.y, windowAttributes.width, windowAttributes.height); \
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - innerBorders, windowAttributes.height - innerBorders); \
				}else{ \
					monitorInfo.x += border; \
					monitorInfo.y += border; \
					if(pointerInfo & BigscreenPointerInfo){ \
						monitorInfo = getPointerMonitorInfo(monitors, monitorAmount); \
					} \
					if(option & FloatingFollowGrid){ \
						windowAttributes.width = monitorInfo.width / gridWidth; \
						windowAttributes.height = monitorInfo.height / gridHeight; \
					}else{ \
						windowAttributes.width = monitorInfo.width / 2; \
						windowAttributes.height = monitorInfo.height / 2; \
					} \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - windowAttributes.width) / 2 - border, monitorInfo.y + (monitorInfo.height - windowAttributes.height) / 2 - border, windowAttributes.width, windowAttributes.height); \
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - innerBorders, windowAttributes.height - innerBorders); \
				} \
			}else{ \
				XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
				XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - innerBorders, monitorInfo.height - innerBorders); \
			} \
			break; \
		} \
	} \
}
#define CLOSE_KEYPRESS \
close:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
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
			break; \
		} \
	} \
}
#define KILL_KEYPRESS \
kill:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XUnmapWindow(display, container[currentContainer].subwindow); \
			XDestroyWindow(display, container[currentContainer].subwindow); \
			goto unmapWindow; \
		} \
	} \
}
#define BUTTONRELEASE \
if(motionContainer.action){ \
	XSelectInput(display, XDefaultRootWindow(display), SubstructureRedirectMask); \
	if(option & FloatingMinimalMoveOption && motionContainer.action == MoveMotionAction){ \
		XUnmapWindow(display, motionContainer.window); \
		{ \
			const Window w = motionContainer.window; \
			motionContainer.window = moveResizeWindow; \
			moveResizeWindow = w; \
		} \
		{ \
			const unsigned int b = border; \
			border = moveResizeWindowBorder; \
			moveResizeWindowBorder = b; \
		} \
		XMoveWindow(display, motionContainer.window, motionContainer.x + moveResizeWindowBorder - border - motionContainer.positionOffset, motionContainer.y + moveResizeWindowBorder - border - motionContainer.positionOffset); \
	}else if(option & FloatingMinimalResizeOption && motionContainer.action == ResizeMotionAction){ \
		XUnmapWindow(display, motionContainer.window); \
		{ \
			const Window w = motionContainer.window; \
			motionContainer.window = moveResizeWindow; \
			moveResizeWindow = w; \
		} \
		XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset + moveResizeWindowBorder - border, motionContainer.y + motionContainer.positionOffset + moveResizeWindowBorder - border, motionContainer.width, motionContainer.height); \
		XResizeWindow(display, motionContainer.subwindow, motionContainer.width - innerBorders, motionContainer.height - innerBorders); \
		XSelectInput(display, motionContainer.subwindow, ButtonMotionMask | StructureNotifyMask); \
	} \
	motionContainer.options = NoMotionOptions; \
	motionContainer.action = NoMotionAction; \
}
#define MOTIONNOTIFY \
if(motionContainer.options & CanActOption){ \
	if(motionContainer.action == MoveMotionAction){ \
		if(option & FloatingAllowStickingOption){ \
			const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(motionContainer.window, monitors, monitorAmount); \
			if(motionContainer.x + (int)border >= monitorInfo.x && motionContainer.x + (int)border <= monitorInfo.x + floatingStickyThresholdX){ \
				if(!(motionContainer.options & HasLockedXOption)){ \
					motionContainer.x = monitorInfo.x - border; \
					XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
					motionContainer.movementBorderX = event.xmotion.x_root + floatingDistanceToTravelX; \
					motionContainer.options |= HasLockedXOption; \
				}else{ \
					if(event.xmotion.x_root >= motionContainer.movementBorderX){ \
						motionContainer.options ^= HasLockedXOption; \
					} \
				} \
			}else if(motionContainer.x + (int)(motionContainer.width + border) >= monitorInfo.x + monitorInfo.width && motionContainer.x + (int)(motionContainer.width + border) <= monitorInfo.x + monitorInfo.width + floatingStickyThresholdX){ \
				if(!(motionContainer.options & HasLockedXOption)){ \
					motionContainer.x = monitorInfo.x + monitorInfo.width - motionContainer.width - border; \
					XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
					motionContainer.movementBorderX = event.xmotion.x_root - floatingDistanceToTravelX; \
					motionContainer.options |= HasLockedXOption; \
				}else{ \
					if(event.xmotion.x_root <= motionContainer.movementBorderX){ \
						motionContainer.options ^= HasLockedXOption; \
					} \
				} \
			} \
			if(motionContainer.y + (int)border >= monitorInfo.y && motionContainer.y + (int)border <= monitorInfo.y + floatingStickyThresholdY){ \
				if(!(motionContainer.options & HasLockedYOption)){ \
					motionContainer.y = monitorInfo.y - border; \
					XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
					motionContainer.movementBorderY = event.xmotion.y_root + floatingDistanceToTravelY; \
					motionContainer.options |= HasLockedYOption; \
				}else{ \
					if(event.xmotion.y_root >= motionContainer.movementBorderY){ \
						motionContainer.options ^= HasLockedYOption; \
					} \
				} \
			}else if(motionContainer.y + (int)(motionContainer.height + border) >= monitorInfo.y + monitorInfo.height && motionContainer.y + (int)(motionContainer.height + border) <= monitorInfo.y + monitorInfo.height + floatingStickyThresholdY){ \
				if(!(motionContainer.options & HasLockedYOption)){ \
					motionContainer.y = monitorInfo.y + monitorInfo.height - motionContainer.height - border; \
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
			if((int)motionContainer.height <= (int)innerBorders){ \
				motionContainer.height = innerBorders + 1; \
			}else{ \
				motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == DownResizeMotionSubaction){ \
			motionContainer.height -= motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.height <= (int)innerBorders){ \
				motionContainer.height = innerBorders + 1; \
			}else{ \
				motionContainer.pointerOffsetY = event.xmotion.y_root - motionContainer.y; \
			} \
			XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == LeftResizeMotionSubaction){ \
			motionContainer.width += motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			if((int)motionContainer.width <= (int)innerBorders){ \
				motionContainer.width = innerBorders + 1; \
			}else{ \
				motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == RightResizeMotionSubaction){ \
			motionContainer.width -= motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			if((int)motionContainer.width <= (int)innerBorders){ \
				motionContainer.width = innerBorders + 1; \
			}else{ \
				motionContainer.pointerOffsetX = event.xmotion.x_root - motionContainer.x; \
			} \
			XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == UpLeftResizeMotionSubaction){ \
			motionContainer.width += motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			motionContainer.height += motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.width <= (int)innerBorders){ \
				motionContainer.width = innerBorders + 1; \
			}else{ \
				motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX; \
			} \
			if((int)motionContainer.height <= (int)innerBorders){ \
				motionContainer.height = innerBorders + 1; \
			}else{ \
				motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == UpRightResizeMotionSubaction){ \
			motionContainer.width -= motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			motionContainer.height += motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.width <= (int)innerBorders){ \
				motionContainer.width = innerBorders + 1; \
			}else{ \
				motionContainer.pointerOffsetX = event.xmotion.x_root - motionContainer.x; \
			} \
			if((int)motionContainer.height <= (int)innerBorders){ \
				motionContainer.height = innerBorders + 1; \
			}else{ \
				motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == DownLeftResizeMotionSubaction){ \
			motionContainer.width += motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			motionContainer.height -= motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.width <= (int)innerBorders){ \
				motionContainer.width = innerBorders + 1; \
			}else{ \
				motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX; \
			} \
			if((int)motionContainer.height <= (int)innerBorders){ \
				motionContainer.height = innerBorders + 1; \
			}else{ \
				motionContainer.pointerOffsetY = event.xmotion.y_root - motionContainer.y; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else{ \
			motionContainer.width += event.xmotion.x_root - motionContainer.x - motionContainer.pointerOffsetX; \
			motionContainer.height += event.xmotion.y_root - motionContainer.y - motionContainer.pointerOffsetY; \
			if((int)motionContainer.width <= (int)innerBorders){ \
				motionContainer.width = innerBorders + 1; \
			}else{ \
				 motionContainer.pointerOffsetX = event.xmotion.x_root - motionContainer.x; \
			} \
			if((int)motionContainer.height <= (int)innerBorders){ \
				motionContainer.height = innerBorders + 1; \
			}else{ \
				motionContainer.pointerOffsetY = event.xmotion.y_root - motionContainer.y; \
			} \
			XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height); \
		} \
		if(!(option & FloatingMinimalResizeOption)){ \
			XResizeWindow(display, motionContainer.subwindow, motionContainer.width - innerBorders, motionContainer.height - innerBorders); \
		} \
	} \
	motionContainer.options ^= CanActOption; \
}else{ \
	if(!XPending(display)){ \
		motionContainer.options |= CanActOption; \
	} \
}
#define ENTERNOTIFY \
for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
	if(container[currentContainer].window == event.xcrossing.window){ \
		if(!motionContainer.action){ \
			XRaiseWindow(display, event.xcrossing.window); \
			XSetInputFocus(display, container[currentContainer].subwindow, RevertToPointerRoot, CurrentTime); \
\
\
\
			/*XPeekEvent(display, &event); \
			if(event.type == EnterNotify){ \
				XNextEvent(display, &event); \
			}*/ \
\
\
\
		} \
		break; \
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
			unsigned int currentContainer1; \
			const unsigned int containerAmount1 = containerAmount - 1; \
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
			if(lastCreatedWindowNumber != containerAmount){ \
				lastCreatedContainer.window = container[lastCreatedWindowNumber].window; \
				lastCreatedContainer.option = container[lastCreatedWindowNumber].option; \
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
					containerInMonitorMap[allocatedContainerAmount] = 1; \
					unsigned int normalWidth; \
					unsigned int abnormalWidth; \
					const unsigned int totalSeparatorWidth = separatorWidth + separatorBorders; \
					{ \
						unsigned int reservedSpace; \
						if(option & TilingUseSeparatorsOption){ \
							reservedSpace = 2 * monitorContainerAmount * tilingGapsX + (monitorContainerAmount - 1) * totalSeparatorWidth; \
						}else{ \
							reservedSpace = (monitorContainerAmount + 1) * tilingGapsX; \
						} \
						normalWidth = (monitorInfo.width - reservedSpace) / monitorContainerAmount; \
						abnormalWidth = (monitorInfo.width - reservedSpace) - (monitorContainerAmount - 1) * normalWidth; \
					} \
					const unsigned int middleX = monitorContainerAmount / 2; \
					unsigned int counter = 0; \
					int x = monitorInfo.x + tilingGapsX; \
					const int y = monitorInfo.y + tilingGapsY; \
					unsigned int width = normalWidth; \
					const unsigned int height = monitorInfo.height - 2 * tilingGapsY; \
					unsigned int currentSeparator = 0; \
					const unsigned int subwindowHeight = height - innerBorders; \
					const unsigned int separatorHeight = height - separatorBorders; \
					const unsigned int separatorWidthGaps = totalSeparatorWidth + tilingGapsX; \
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
						if(containerInMonitorMap[currentContainer]){ \
							XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
							XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, subwindowHeight); \
							if(++counter == monitorContainerAmount){ \
								break; \
							} \
							x += width + tilingGapsX; \
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
			if(allocatedContainerAmount == containerAmount - containerIncrementDecrementAmount - 1){ \
				containerDirective = DecreaseContainerDirective; \
				goto saveOpenClients; \
			} \
			break; \
		} \
	} \
}
#define CONFIGUREREQUEST \
bool new = 1; \
for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
	if(container[currentContainer].subwindow == event.xconfigurerequest.window){ \
		XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
		if(canConfigurePosition){ \
			if(!(container[currentContainer].option & InGridContainerOption)){ \
				if((event.xconfigurerequest.value_mask & CWX || event.xconfigurerequest.value_mask & CWY)){ \
					if(event.xconfigurerequest.value_mask & CWX){ \
						windowAttributes.x += event.xconfigurerequest.x - windowAttributes.x - innerBorder; \
					} \
					if(event.xconfigurerequest.value_mask & CWY){ \
						windowAttributes.y += event.xconfigurerequest.y - windowAttributes.y - innerBorder; \
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
				XResizeWindow(display, event.xconfigurerequest.window, windowAttributes.width - innerBorders, windowAttributes.height - innerBorders); \
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
	XMoveResizeWindow(display, event.xconfigurerequest.window, monitorInfo.x, monitorInfo.y, monitorInfo.width / gridWidth - innerBorders, monitorInfo.height / gridHeight - innerBorders); \
}
#define END_OF_LOOP \
{ \
	const Window rootWindow = XDefaultRootWindow(display); \
	Window w; \
	Window s; \
	XSelectInput(display, rootWindow, NoEventMask); \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		w = container[currentContainer].window; \
		s = container[currentContainer].subwindow; \
		ungrabContainerKeysButtons(w, shortcutAmount, shortcut, buttonAmount, button); \
		XSelectInput(display, s, NoEventMask); \
		XSelectInput(display, w, NoEventMask); \
		XUnmapWindow(display, s); \
		XUnmapWindow(display, w); \
		XReparentWindow(display, s, rootWindow, 0, 0); \
		XDestroyWindow(display, w); \
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
if(containerDirective == IncreaseContainerDirective){ \
	containerAmount += containerIncrementDecrementAmount; \
	containerDirective = NoContainerDirective; \
}else if(containerDirective == DecreaseContainerDirective){ \
	containerAmount -= containerIncrementDecrementAmount; \
	containerDirective = NoContainerDirective; \
}
#endif
