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
unsigned int shortcutAmount = 51; \
unsigned int buttonAmount = 3; \
Shortcut shortcut[shortcutAmount]; \
Button button[buttonAmount]; \
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
	shortcut[currentShortcut].command = ToggleGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 43; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = ToggleGapsCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 38; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = AttachWindowCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 27; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = RecascadeCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 9; \
	shortcut[currentShortcut].masks = Mod4Mask; \
	shortcut[currentShortcut].command = ExitCommand; \
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
	shortcut[currentShortcut].keycode = 84; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = MoveCenterCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 80; \
	shortcut[currentShortcut].masks = ControlMask | Mod1Mask; \
	shortcut[currentShortcut].command = MoveFullCommand; \
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
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveUpGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 116; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveDownGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 113; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveLeftGridCommand; \
	++currentShortcut; \
	shortcut[currentShortcut].keycode = 114; \
	shortcut[currentShortcut].masks = ShiftMask | Mod4Mask; \
	shortcut[currentShortcut].command = MoveRightGridCommand; \
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
#define SETUP_CONTAINERS \
Container container[containerAmount]; \
XSelectInput(display, rootWindow, SubstructureRedirectMask); \
{ \
	const AttributesMasks masks = CWBackPixel | CWBorderPixel | CWColormap; \
	Window w; \
	unsigned int currentShadow; \
	XSetWindowAttributes windowAttributes = { \
		.border_pixel = color.containerShadow, \
		.colormap = XCreateColormap(display, rootWindow, visualInfo.visual, AllocNone) \
	}; \
	if(managementMode == FloatingManagementMode){ \
		currentShadow = shadow; \
		windowAttributes.background_pixel = color.containerBackground.floating; \
	}else{ \
		currentShadow = 0; \
		if(managementMode == GriddingManagementMode){ \
			windowAttributes.background_pixel = color.containerBackground.gridding; \
		}else{ \
			windowAttributes.background_pixel = color.containerBackground.tiling; \
		} \
	} \
	for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){ \
		w = XCreateWindow(display, rootWindow, 0, 0, 1, 1, currentShadow, visualInfo.depth, InputOutput, visualInfo.visual, masks, &windowAttributes); \
		grabContainerKeysButtons(w); \
		container[currentContainer].window = w; \
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
			InputMasks windowMasks; \
			InputMasks subwindowMasks; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				subwindow = getUnsignedInteger(' '); \
				x = getInteger(' '); \
				y = getInteger(' '); \
				width = getUnsignedInteger(' '); \
				height = getUnsignedInteger(' '); \
				container[currentContainer].inGrid = getUnsignedInteger(' '); \
				if(container[currentContainer].inGrid){ \
					container[currentContainer].gridX = getUnsignedInteger(' '); \
					container[currentContainer].gridY = getUnsignedInteger(' '); \
					container[currentContainer].gridWidth = getUnsignedInteger(' '); \
					container[currentContainer].gridHeight = getUnsignedInteger('\n'); \
				}else{ \
					getUnsignedInteger('\n'); \
				} \
				if(container[currentContainer].inGrid){ \
					windowMasks = EnterWindowMask | SubstructureRedirectMask; \
					subwindowMasks = StructureNotifyMask; \
					XSetWindowBorderWidth(display, container[currentContainer].window, 0); \
					if(managementMode == FloatingManagementMode){ \
						XSetWindowBackground(display, container[currentContainer].window, color.containerBackground.inGrid); \
					} \
				}else{ \
					windowMasks = ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask; \
					subwindowMasks = ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask; \
				} \
				XSelectInput(display, container[currentContainer].window, windowMasks); \
				XSelectInput(display, subwindow, subwindowMasks); \
				XReparentWindow(display, subwindow, container[currentContainer].window, border.left, border.up); \
				XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
				XResizeWindow(display, subwindow, width - border.axis.x, height - border.axis.y); \
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
				for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
					subwindow = getUnsignedInteger(' '); \
					maximizedContainer[currentMonitor].subwindow = subwindow; \
					maximizedContainer[currentMonitor].oldX = getInteger(' '); \
					maximizedContainer[currentMonitor].oldY = getInteger(' '); \
					maximizedContainer[currentMonitor].oldWidth = getUnsignedInteger(' '); \
					maximizedContainer[currentMonitor].oldHeight = getUnsignedInteger(' '); \
					maximizedContainer[currentMonitor].oldBackgroundColor = getUnsignedInteger(' '); \
					maximizedContainer[currentMonitor].shouldChangeProperty = getUnsignedInteger('\n'); \
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
						if(container[currentContainer].subwindow == subwindow){ \
							window = container[currentContainer].window; \
							XSetWindowBorderWidth(display, window, 0); \
							if(maximizedContainer[currentMonitor].shouldChangeProperty){ \
								XSetWindowBackground(display, window, color.containerBackground.fullscreen); \
							}else{ \
								XSetWindowBackground(display, window, color.containerBackground.bigscreen); \
							} \
							width = monitors[currentMonitor].width; \
							height = monitors[currentMonitor].height; \
							XMoveResizeWindow(display, window, monitors[currentMonitor].x, monitors[currentMonitor].y, width, height); \
							XResizeWindow(display, subwindow, width - border.axis.x, height - border.axis.y); \
							maximizedContainer[currentMonitor].window = window; \
							break; \
						} \
					} \
				} \
			} \
			fclose(file); \
		}else{ \
			fprintf(errorStream, "%s: could not read maximized windows\n", programName); \
		} \
	}else{ \
		fprintf(errorStream, "%s: could not read windows\n", programName); \
	} \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		XMapWindow(display, container[currentContainer].window); \
		XMapWindow(display, container[currentContainer].subwindow); \
	} \
}
#define KEYPRESS \
command = None; \
for(unsigned int currentKeycode = 0; currentKeycode < shortcutAmount; ++currentKeycode){ \
	if(shortcut[currentKeycode].keycode == event.xkey.keycode && shortcut[currentKeycode].masks == event.xkey.state){ \
		command = shortcut[currentKeycode].command; \
		goto executeCommand; \
	} \
}
#define BUTTONPRESS \
command = None; \
for(unsigned int currentButton = 0; currentButton < buttonAmount; ++currentButton){ \
	if(button[currentButton].button == event.xbutton.button && button[currentButton].masks == event.xbutton.state){ \
		command = button[currentButton].command; \
		goto executeCommand; \
	} \
} \
if(command){ \
	fprintf(errorStream, "%s: unrecognized command may have been executed\n", programName); \
	executeCommand:{ \
		if(command <= RootCommandCeiling){ \
			if(command == SystemCommand){ \
				SYSTEM_KEYPRESS \
			}else if(command == FloatingModeCommand){ \
				FLOATINGMODE_KEYPRESS \
			}else if(command == GriddingModeCommand){ \
				GRIDDINGMODE_KEYPRESS \
			}else if(command == TilingModeCommand){ \
				TILINGMODE_KEYPRESS \
			}else if(command == ToggleGridCommand){ \
				TOGGLEGRID_KEYPRESS \
			}else if(command == EnlargeGridXCommand){ \
				ENLARGEGRIDX_KEYPRESS \
			}else if(command == EnlargeGridYCommand){ \
				ENLARGEGRIDY_KEYPRESS \
			}else if(command == EnlargeGridCommand){ \
				ENLARGEGRID_KEYPRESS \
			}else if(command == ShrinkGridXCommand){ \
				SHRINKGRIDX_KEYPRESS \
			}else if(command == ShrinkGridYCommand){ \
				SHRINKGRIDY_KEYPRESS \
			}else if(command == ShrinkGridCommand){ \
				SHRINKGRID_KEYPRESS \
			}else if(command == ToggleGapsCommand){ \
				TOGGLEGAPS_KEYPRESS \
			}else if(command == RecascadeCommand){ \
				RECASCADE_KEYPRESS \
			}else if(command == AttachWindowCommand){ \
				ATTACHWINDOW_KEYPRESS \
			}else if(command == RestartCommand){ \
				mode = RestartMode; \
				break; \
			}else{ \
				mode = ExitMode; \
				break; \
			} \
		}else{ \
			if(command == MoveCommand){ \
				MOVE_KEYPRESS \
			}else{ \
				if(command <= MoveFullCommand){ \
					keyButtonPressSearchless:{ \
						if(command <= MoveBottomRightCommand){ \
							if(!containerIsMaximized(event.xany.window)){ \
								if(findContainer(event.xany.window)){ \
									if(command == MoveTopCommand){ \
										MOVETOP_KEYPRESS \
									}else if(command == MoveBottomCommand){ \
										MOVEBOTTOM_KEYPRESS \
									}else if(command == MoveLeftCommand){ \
										MOVELEFT_KEYPRESS \
									}else if(command == MoveRightCommand){ \
										MOVERIGHT_KEYPRESS \
									}else if(command == MoveTopLeftCommand){ \
										MOVETOPLEFT_KEYPRESS \
									}else if(command == MoveTopRightCommand){ \
										MOVETOPRIGHT_KEYPRESS \
									}else if(command == MoveBottomLeftCommand){ \
										MOVEBOTTOMLEFT_KEYPRESS \
									}else{ \
										MOVEBOTTOMRIGHT_KEYPRESS \
									} \
								} \
							} \
						}else{ \
							if(managementMode != TilingManagementMode){ \
								if(!containerIsMaximized(event.xany.window)){ \
									if(findContainer(event.xany.window)){ \
										if(command == MoveCenterCommand){ \
											MOVECENTER_KEYPRESS \
										}else{ \
											MOVEFULL_KEYPRESS \
										} \
									} \
								} \
							} \
						} \
					} \
				}else if(command <= MovePreviousMonitorCommand){ \
					MOVENEXTPREVIOUSMONITOR_KEYPRESS \
				}else if(command <= MoveRightMonitorCommand){ \
					monitorInfo = getWindowMonitorInfo(event.xany.window); \
					if(command == MoveAboveMonitorCommand){ \
						MOVEABOVEMONITOR_KEYPRESS \
					}else if(command == MoveBelowMonitorCommand){ \
						MOVEBELOWMONITOR_KEYPRESS \
					}else if(command == MoveLeftMonitorCommand){ \
						MOVELEFTMONITOR_KEYPRESS \
					}else{ \
						MOVERIGHTMONITOR_KEYPRESS \
					} \
				}else if(command <= ToggleWindowGridCommand){ \
					if(managementMode == FloatingManagementMode){ \
						if(!containerIsMaximized(event.xany.window)){ \
							if(findContainer(event.xany.window)){ \
								if(command == AddWindowToGridCommand){ \
									if(!container[currentContainer].inGrid){ \
										goto addToGrid; \
									} \
								}else if(command == RemoveWindowFromGridCommand){ \
									if(container[currentContainer].inGrid){ \
										goto removeFromGrid; \
									} \
								}else{ \
									TOGGLEWINDOWGRID_KEYPRESS \
								} \
							} \
						} \
					} \
				}else if(command <= MoveRightGridCommand){ \
					if(managementMode != TilingManagementMode){ \
						if(!containerIsMaximized(event.xany.window)){ \
							if(findContainer(event.xany.window)){ \
								if(container[currentContainer].inGrid){ \
									if(command == MoveUpGridCommand){ \
										MOVEUPGRID_KEYPRESS \
									}else if(command == MoveDownGridCommand){ \
										MOVEDOWNGRID_KEYPRESS \
									}else if(command == MoveLeftGridCommand){ \
										MOVELEFTGRID_KEYPRESS \
									}else{ \
										MOVERIGHTGRID_KEYPRESS \
									} \
								} \
							} \
						} \
					} \
				}else if(command <= ShrinkWindowDownRightCommand){ \
					if(!containerIsMaximized(event.xany.window)){ \
						if(findContainer(event.xany.window)){ \
							if(command == ExtendWindowUpCommand){ \
								EXTENDWINDOWUP_KEYPRESS \
							}else if(command == ExtendWindowDownCommand){ \
								EXTENDWINDOWDOWN_KEYPRESS \
							}else if(command == ExtendWindowLeftCommand){ \
								EXTENDWINDOWLEFT_KEYPRESS \
							}else if(command == ExtendWindowRightCommand){ \
								EXTENDWINDOWRIGHT_KEYPRESS \
							}else if(command == ExtendWindowUpLeftCommand){ \
								EXTENDWINDOWUPLEFT_KEYPRESS \
							}else if(command == ExtendWindowUpRightCommand){ \
								EXTENDWINDOWUPRIGHT_KEYPRESS \
							}else if(command == ExtendWindowDownLeftCommand){ \
								EXTENDWINDOWDOWNLEFT_KEYPRESS \
							}else if(command == ExtendWindowDownRightCommand){ \
								EXTENDWINDOWDOWNRIGHT_KEYPRESS \
							}else if(command == ShrinkWindowUpCommand){ \
								SHRINKWINDOWUP_KEYPRESS \
							}else if(command == ShrinkWindowDownCommand){ \
								SHRINKWINDOWDOWN_KEYPRESS \
							}else if(command == ShrinkWindowLeftCommand){ \
								SHRINKWINDOWLEFT_KEYPRESS \
							}else if(command == ShrinkWindowRightCommand){ \
								SHRINKWINDOWRIGHT_KEYPRESS \
							}else if(command == ShrinkWindowUpLeftCommand){ \
								SHRINKWINDOWUPLEFT_KEYPRESS \
							}else if(command == ShrinkWindowUpRightCommand){ \
								SHRINKWINDOWUPRIGHT_KEYPRESS \
							}else if(command == ShrinkWindowDownLeftCommand){ \
								SHRINKWINDOWDOWNLEFT_KEYPRESS \
							}else{ \
								SHRINKWINDOWDOWNRIGHT_KEYPRESS \
							} \
							extendShrinkWindowEmergencyExit:{} \
						} \
					} \
				}else if(command <= BigscreenCommand){ \
					FULLSCREEN_BIGSCREEN_KEYPRESS \
				}else if(command == CloseCommand){ \
					CLOSE_KEYPRESS \
				}else if(command == KillCommand){ \
					KILL_KEYPRESS \
				}else{ \
					DETACHWINDOW_KEYPRESS \
				} \
			} \
		} \
	} \
}
#define SYSTEM_KEYPRESS
#define FLOATINGMODE_KEYPRESS \
if(managementMode != FloatingManagementMode){ \
	{ \
		const Atom atom = None; \
		for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
			if(maximizedContainer[currentMonitor].window){ \
				if(maximizedContainer[currentMonitor].shouldChangeProperty){ \
					XChangeProperty(display, container[currentContainer].subwindow, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1); \
				} \
				maximizedContainer[currentMonitor].window = None; \
				maximizedContainer[currentMonitor].subwindow = None; \
			} \
		} \
	} \
	if(allocatedContainerAmount){ \
		{ \
			const Options portWindowsFromGridding = option & FloatingPortWindowsFromGriddingOption; \
			const InputMasks windowMasks = ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask; \
			const InputMasks subwindowMasks = ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask; \
			Window window; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				if(managementMode != GriddingManagementMode || !portWindowsFromGridding){ \
					window = container[currentContainer].window; \
					XSelectInput(display, window, windowMasks); \
					XSelectInput(display, container[currentContainer].subwindow, subwindowMasks); \
					XSetWindowBorderWidth(display, window, shadow); \
					XSetWindowBackground(display, window, color.containerBackground.floating); \
					XUnmapWindow(display, window); \
					XMapWindow(display, window); \
					container[currentContainer].inGrid = 0; \
				}else{ \
					window = container[currentContainer].window; \
					XSetWindowBackground(display, window, color.containerBackground.inGrid); \
					XUnmapWindow(display, window); \
					XMapWindow(display, window); \
				} \
			} \
		} \
		unsigned int width; \
		unsigned int height; \
		int x; \
		int y; \
		unsigned int subwindowWidth; \
		unsigned int subwindowHeight; \
		if(pointerInfo & ChangeToFloatingPointerInfo){ \
			monitorInfo = getPointerMonitorInfo(); \
			if(option & FloatingFollowGrid){ \
				width = monitorInfo.width / gridWidth; \
				height = monitorInfo.height / gridHeight; \
			}else{ \
				width = monitorInfo.width / 2; \
				height = monitorInfo.height / 2; \
			} \
			x = monitorInfo.x + (monitorInfo.width - width) / 2 - shadow; \
			y = monitorInfo.y + (monitorInfo.height - height) / 2 - shadow; \
			subwindowWidth = width - border.axis.x; \
			subwindowHeight = height - border.axis.y; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				if(!container[currentContainer].inGrid){ \
					XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
					XResizeWindow(display, container[currentContainer].subwindow, subwindowWidth, subwindowHeight); \
					x += cascade.offsetX; \
					y += cascade.offsetY; \
				} \
			} \
		}else{ \
			XRRMonitorInfo mi; \
			for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
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
				subwindowWidth = width - border.axis.x; \
				subwindowHeight = height - border.axis.y; \
				for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
					if(!container[currentContainer].inGrid){ \
						monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
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
		for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
			if(maximizedContainer[currentMonitor].window){ \
				if(maximizedContainer[currentMonitor].shouldChangeProperty){ \
					XChangeProperty(display, container[currentContainer].subwindow, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1); \
				} \
				maximizedContainer[currentMonitor].window = None; \
				maximizedContainer[currentMonitor].subwindow = None; \
			} \
		} \
	} \
	if(allocatedContainerAmount){ \
		const Options portWindowsFromFloating = option & GriddingPortWindowsFromFloatingOption; \
		const InputMasks windowMasks = EnterWindowMask | SubstructureRedirectMask; \
		Window window; \
		unsigned int gridX = 0; \
		unsigned int gridY = 0; \
		int x; \
		int y; \
		if(pointerInfo & ChangeToGriddingPointerInfo){ \
			monitorInfo = getPointerMonitorInfo(); \
		} \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			window = container[currentContainer].window; \
			XSetWindowBackground(display, window, color.containerBackground.gridding); \
			XUnmapWindow(display, window); \
			XMapWindow(display, window); \
			if(managementMode == FloatingManagementMode && portWindowsFromFloating){ \
				if(!container[currentContainer].inGrid){ \
					XSetWindowBorderWidth(display, window, 0); \
					container[currentContainer].inGrid = 1; \
					goto putInGrid; \
				} \
			}else{ \
				if(!container[currentContainer].inGrid){ \
					XSelectInput(display, window, windowMasks); \
					XSelectInput(display, container[currentContainer].subwindow, StructureNotifyMask); \
					XSetWindowBorderWidth(display, window, 0); \
					container[currentContainer].inGrid = 1; \
				} \
				putInGrid:{ \
					if(!(pointerInfo & ChangeToGriddingPointerInfo)){ \
						monitorInfo = getWindowMonitorInfo(window); \
					} \
					getGridSlotData(monitorInfo, gridX, gridY, gridWidth, gridHeight, &x, &y, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
					XMoveResizeWindow(display, window, monitorInfo.x + x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
					XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
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
		for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
			if(maximizedContainer[currentMonitor].window){ \
				if(maximizedContainer[currentMonitor].shouldChangeProperty){ \
					XChangeProperty(display, container[currentContainer].subwindow, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&atom, 1); \
				} \
				maximizedContainer[currentMonitor].window = None; \
				maximizedContainer[currentMonitor].subwindow = None; \
			} \
		} \
	} \
	if(allocatedContainerAmount){ \
		const InputMasks windowMasks = EnterWindowMask | SubstructureRedirectMask; \
		const unsigned int totalSeparatorWidth = separatorWidth + separatorBorders; \
		Window window; \
		Window subwindow; \
		unsigned int middleX; \
		int x; \
		int y; \
		unsigned int separatorAmount; \
		unsigned int availableSpace; \
		unsigned int normalWidth; \
		unsigned int abnormalWidth; \
		unsigned int height; \
		unsigned int subwindowAbnormalWidth; \
		unsigned int subwindowHeight; \
		unsigned int abnormalWidthGaps; \
		unsigned int subwindowNormalWidth; \
		unsigned int normalWidthGaps; \
		if(pointerInfo & ChangeToTilingPointerInfo){ \
			monitorInfo = getPointerMonitorInfo(); \
			middleX = allocatedContainerAmount / 2; \
			x = monitorInfo.x + gapsX; \
			y = monitorInfo.y + gapsY; \
			separatorAmount = allocatedContainerAmount - 1; \
			if(option & TilingUseSeparatorsOption){ \
				availableSpace = monitorInfo.width - (2 * allocatedContainerAmount * gapsX + (allocatedContainerAmount - 1) * totalSeparatorWidth); \
			}else{ \
				availableSpace = monitorInfo.width - (allocatedContainerAmount + 1) * gapsX; \
			} \
			normalWidth = availableSpace / allocatedContainerAmount; \
			abnormalWidth = availableSpace - (allocatedContainerAmount - 1) * normalWidth; \
			height = monitorInfo.height - 2 * gapsY; \
			subwindowAbnormalWidth = normalWidth - border.axis.x; \
			subwindowHeight = height - border.axis.y; \
			abnormalWidthGaps = abnormalWidth + gapsX; \
			subwindowNormalWidth = abnormalWidth - border.axis.x; \
			normalWidthGaps = normalWidth + gapsX; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				window = container[currentContainer].window; \
				subwindow = container[currentContainer].subwindow; \
				if(!container[currentContainer].inGrid){ \
					XSelectInput(display, window, windowMasks); \
					XSelectInput(display, subwindow, StructureNotifyMask); \
					XSetWindowBorderWidth(display, window, 0); \
					container[currentContainer].inGrid = 1; \
				} \
				XSetWindowBackground(display, window, color.containerBackground.tiling); \
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
			} \
		}else{ \
			unsigned int windowsAssigned; \
			unsigned int currentMonitorContainer; \
			for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
				windowsAssigned = 0; \
				for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
					monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
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
						availableSpace = monitors[currentMonitor].width - (2 * windowsAssigned * gapsX + separatorAmount * totalSeparatorWidth); \
					}else{ \
						availableSpace = monitors[currentMonitor].width - (windowsAssigned + 1) * gapsX; \
					} \
					normalWidth = availableSpace / windowsAssigned; \
					abnormalWidth = availableSpace - separatorAmount * normalWidth; \
					height = monitors[currentMonitor].height - 2 * gapsY; \
					subwindowAbnormalWidth = normalWidth - border.axis.x; \
					subwindowHeight = height - border.axis.y; \
					abnormalWidthGaps = abnormalWidth + gapsX; \
					subwindowNormalWidth = abnormalWidth - border.axis.x; \
					normalWidthGaps = normalWidth + gapsX; \
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
						monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
						if(monitorCompare(monitorInfo, monitors[currentMonitor])){ \
							window = container[currentContainer].window; \
							subwindow = container[currentContainer].subwindow; \
							if(!container[currentContainer].inGrid){ \
								XSelectInput(display, window, windowMasks); \
								XSelectInput(display, subwindow, StructureNotifyMask); \
								XSetWindowBorderWidth(display, window, 0); \
								container[currentContainer].inGrid = 1; \
							} \
							XSetWindowBackground(display, window, color.containerBackground.tiling); \
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
							++currentMonitorContainer; \
						} \
					} \
				} \
			} \
		} \
	} \
	managementMode = TilingManagementMode; \
}
#define TOGGLEGRID_KEYPRESS \
if(gridMapped){ \
	for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
		XUnmapSubwindows(display, grid[currentMonitor]); \
		XUnmapWindow(display, grid[currentMonitor]); \
	} \
	gridMapped = 0; \
}else{ \
	if(!gridExists){ \
		createGrid(); \
		gridExists = 1; \
	} \
	for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
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
			currentMonitor = 0; \
			if(gridMapped){ \
				while(currentMonitor < monitorAmount){ \
					XUnmapSubwindows(display, grid[currentMonitor]); \
					XDestroySubwindows(display, grid[currentMonitor]); \
					++currentMonitor; \
				} \
				createGrid(); \
				for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
					XLowerWindow(display, grid[currentMonitor]); \
					XMapSubwindows(display, grid[currentMonitor]); \
				} \
			}else{ \
				while(currentMonitor < monitorAmount){ \
					XDestroySubwindows(display, grid[currentMonitor]); \
					++currentMonitor; \
				} \
				gridExists = 0; \
			} \
		} \
		if(managementMode != TilingManagementMode){ \
			int x; \
			int y; \
			int x1; \
			int y1; \
			unsigned int width; \
			unsigned int height; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				if(container[currentContainer].inGrid){ \
					monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
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
					XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
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
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
		monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
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
		XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
	} \
}
#define RECASCADE_KEYPRESS \
if(managementMode == FloatingManagementMode){ \
	if(allocatedContainerAmount){ \
		const CascadeOptions overrideGridWindows = cascade.options & OverrideGridWindowsCascadeOption; \
		const CascadeOptions overrideMaximizedWindows = cascade.options & OverrideMaximizedWindowsCascadeOption; \
		int x; \
		int y; \
		unsigned int width; \
		unsigned int height; \
		if(pointerInfo & RecascadePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(); \
			if(option & FloatingFollowGrid){ \
				width = monitorInfo.width / gridWidth; \
				height = monitorInfo.height / gridHeight; \
			}else{ \
				width = monitorInfo.width / 2; \
				height = monitorInfo.height / 2; \
			} \
			x = monitorInfo.x + (monitorInfo.width - width) / 2 - shadow; \
			y = monitorInfo.y + (monitorInfo.height - height) / 2 - shadow; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				if(overrideGridWindows && container[currentContainer].inGrid){ \
					XSetWindowBorderWidth(display, container[currentContainer].window, shadow); \
					XSetWindowBackground(display, container[currentContainer].window, color.containerBackground.floating); \
					XUnmapWindow(display, container[currentContainer].window); \
					XMapWindow(display, container[currentContainer].window); \
					container[currentContainer].inGrid = 0; \
					goto recascadeWindow0; \
				}else if(overrideMaximizedWindows && containerIsMaximized(container[currentContainer].window)){ \
					unmaximizeContainer(container[currentContainer].window, shadow, color.containerBackground.floating); \
					goto recascadeWindow0; \
				}else if(!(container[currentContainer].inGrid || containerIsMaximized(container[currentContainer].window))){ \
					recascadeWindow0:{ \
						XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
						XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
						x += cascade.offsetX; \
						y += cascade.offsetY; \
					} \
				} \
			} \
		}else{ \
			XRRMonitorInfo mi; \
			for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
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
					monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
					if(monitorCompare(monitorInfo, mi)){ \
						if(overrideGridWindows && container[currentContainer].inGrid){ \
							XSetWindowBorderWidth(display, container[currentContainer].window, shadow); \
							XSetWindowBackground(display, container[currentContainer].window, color.containerBackground.floating); \
							XUnmapWindow(display, container[currentContainer].window); \
							XMapWindow(display, container[currentContainer].window); \
							container[currentContainer].inGrid = 0; \
							goto recascadeWindow1; \
						}else if(overrideMaximizedWindows && containerIsMaximized(container[currentContainer].window)){ \
							unmaximizeContainer(container[currentContainer].window, shadow, color.containerBackground.floating); \
							goto recascadeWindow1; \
						}else if(!(container[currentContainer].inGrid || containerIsMaximized(container[currentContainer].window))){ \
							recascadeWindow1:{ \
								XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
								XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
								x += cascade.offsetX; \
								y += cascade.offsetY; \
							} \
						} \
					} \
				} \
			} \
		} \
	} \
}
#define ATTACHWINDOW_KEYPRESS \
if(event.xkey.subwindow){ \
	monitorInfo = getPointerMonitorInfo(); \
	event.xmaprequest.window = event.xkey.subwindow; \
	goto mapWindow; \
}
#define MOVE_KEYPRESS \
if(!containerIsMaximized(event.xany.window)){ \
	if(findContainer(event.xany.window)){ \
		if(managementMode == TilingManagementMode){ \
\
\
\
			\
\
\
\
		}else if(container[currentContainer].inGrid){ \
\
\
\
			\
\
\
\
		}else{ \
			XSelectInput(display, rootWindow, ButtonReleaseMask | ButtonMotionMask | SubstructureRedirectMask); \
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
				motionContainer.subaction = NoMotionSubaction; \
			}else{ \
				motionContainer.subwindow = container[currentContainer].subwindow; \
				if(option & FloatingMinimalResizeOption){ \
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
				if(event.xbutton.y < (int)border.up){ \
					if(event.xbutton.x < (int)border.left){ \
						motionContainer.subaction = UpLeftResizeMotionSubaction; \
					}else if(event.xbutton.x < windowAttributes.width - (int)border.right){ \
						motionContainer.subaction = UpResizeMotionSubaction; \
					}else{ \
						motionContainer.subaction = UpRightResizeMotionSubaction; \
					} \
				}else if(event.xbutton.y < windowAttributes.height - (int)border.down){ \
					if(event.xbutton.x < (int)border.left){ \
						motionContainer.subaction = LeftResizeMotionSubaction; \
					}else{ \
						motionContainer.subaction = RightResizeMotionSubaction; \
					} \
				}else{ \
					if(event.xbutton.x < (int)border.left){ \
						motionContainer.subaction = DownLeftResizeMotionSubaction; \
					}else if(event.xbutton.x < windowAttributes.width - (int)border.right){ \
						motionContainer.subaction = DownResizeMotionSubaction; \
					}else{ \
						motionContainer.subaction = DownRightResizeMotionSubaction; \
					} \
				} \
			} \
			motionContainer.options = CanActMotionOption; \
		} \
	} \
}
#define MOVETOP_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	if(allocatedContainerAmount > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
		if(windowAttributes.y > monitorInfo.y + (int)gapsY){ \
			goto moveTopBottomLeftRight; \
		} \
	} \
}else if(container[currentContainer].inGrid){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	{ \
		int y; \
		getGridSlotData(monitorInfo, 0, 0, gridWidth, gridHeight, NULL, &y, NULL, (unsigned int *)&monitorInfo.height); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
	container[currentContainer].gridX = 0; \
	container[currentContainer].gridY = 0; \
	container[currentContainer].gridWidth = gridWidth; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	if(pointerInfo & MovePointerInfo){ \
		monitorInfo = getPointerMonitorInfo(); \
	}else{ \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
	} \
	unsigned int height; \
	if(option & FloatingFollowGrid){ \
		height = monitorInfo.height / gridHeight; \
	}else{ \
		height = monitorInfo.height / 2; \
	} \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x - shadow, monitorInfo.y - shadow, monitorInfo.width, height); \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, height - border.axis.y); \
}
#define MOVEBOTTOM_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	if(allocatedContainerAmount > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
		if(windowAttributes.y + windowAttributes.height < monitorInfo.y + monitorInfo.height - (int)gapsY){ \
			goto moveTopBottomLeftRight; \
		} \
	} \
}else if(container[currentContainer].inGrid){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	{ \
		int y; \
		getGridSlotData(monitorInfo, 0, gridHeight - 1, gridWidth, gridHeight, NULL, &y, NULL, (unsigned int *)&monitorInfo.height); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
	container[currentContainer].gridX = 0; \
	container[currentContainer].gridY = gridHeight - 1; \
	container[currentContainer].gridWidth = gridWidth; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	if(pointerInfo & MovePointerInfo){ \
		monitorInfo = getPointerMonitorInfo(); \
	}else{ \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
	} \
	unsigned int height; \
	if(option & FloatingFollowGrid){ \
		height = monitorInfo.height / gridHeight; \
	}else{ \
		height = monitorInfo.height / 2; \
	} \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x - shadow, monitorInfo.y + monitorInfo.height - height - shadow, monitorInfo.width, height); \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, height - border.axis.y); \
}
#define MOVELEFT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	if(allocatedContainerAmount > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
		if(windowAttributes.x > monitorInfo.x + (int)gapsX){ \
			goto moveTopBottomLeftRight; \
		} \
	} \
}else if(container[currentContainer].inGrid){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	{ \
		int x; \
		getGridSlotData(monitorInfo, 0, 0, gridWidth, gridHeight, &x, NULL, (unsigned int *)&monitorInfo.width, NULL); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
	container[currentContainer].gridX = 0; \
	container[currentContainer].gridY = 0; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = gridHeight; \
}else{ \
	if(pointerInfo & MovePointerInfo){ \
		monitorInfo = getPointerMonitorInfo(); \
	}else{ \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
	} \
	unsigned int width; \
	if(option & FloatingFollowGrid){ \
		width = monitorInfo.width / gridWidth; \
	}else{ \
		width = monitorInfo.width / 2; \
	} \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x - shadow, monitorInfo.y - shadow, width, monitorInfo.height); \
	XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, monitorInfo.height - border.axis.y); \
}
#define MOVERIGHT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	if(allocatedContainerAmount > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
		if(windowAttributes.x + windowAttributes.width < monitorInfo.x + monitorInfo.width - (int)gapsX){ \
			moveTopBottomLeftRight:{ \
				if(option & TilingSlamWindowsToDirectionOption){ \
\
\
\
					\
\
\
\
				}else{ \
					XWindowAttributes windowAttributes1; \
					unsigned int containerToUse = allocatedContainerAmount; \
					{ \
						int *position0; \
						int *position1; \
						int *size0; \
						unsigned int spacing; \
						unsigned int pixels = 0; \
						unsigned int mostPixels = 0; \
						int *size1; \
						int monitorSize; \
						int *position2; \
						int *position3; \
						int *size2; \
						if(command == MoveTopCommand){ \
							position0 = &windowAttributes.y; \
							position1 = &windowAttributes1.y; \
							size0 = &windowAttributes1.height; \
							goto verticalMove; \
						}else if(command == MoveBottomCommand){ \
							position0 = &windowAttributes1.y; \
							position1 = &windowAttributes.y; \
							size0 = &windowAttributes.height; \
							verticalMove:{ \
								spacing = gapsY; \
								size1 = &windowAttributes1.width; \
								monitorSize = monitorInfo.width - 2 * gapsX; \
								position2 = &windowAttributes1.x; \
								position3 = &windowAttributes.x; \
								size2 = &windowAttributes.width; \
							} \
						}else if(command == MoveLeftCommand){ \
							position0 = &windowAttributes.x; \
							position1 = &windowAttributes1.x; \
							size0 = &windowAttributes1.width; \
							goto horizontalMove; \
						}else{ \
							position0 = &windowAttributes1.x; \
							position1 = &windowAttributes.x; \
							size0 = &windowAttributes.width; \
							horizontalMove:{ \
								spacing = gapsX; \
								size1 = &windowAttributes1.height; \
								monitorSize = monitorInfo.height - 2 * gapsY; \
								position2 = &windowAttributes1.y; \
								position3 = &windowAttributes.y; \
								size2 = &windowAttributes.height; \
							} \
						} \
						if(option & TilingUseSeparatorsOption){ \
							spacing = 2 * spacing + separatorBorders + separatorWidth; \
						} \
						for(unsigned int currentContainer1 = 0; currentContainer1 < allocatedContainerAmount; ++currentContainer1){ \
							if(currentContainer1 != currentContainer){ \
								XGetWindowAttributes(display, container[currentContainer1].window, &windowAttributes1); \
								if(*position0 == *position1 + *size0 + (int)spacing){ \
									if(*size1 == monitorSize){ \
										containerToUse = currentContainer1; \
										break; \
									} \
									if(closedOpenInterval(*position2, *position3, *position3 + *size2)){ \
										if(*position2 + *size1 < *position3 + *size2){ \
											pixels = *size1; \
										}else{ \
											pixels = *position3 + *size2 - *position2; \
										} \
									}else if(closedOpenInterval(*position2 + *size1, *position3, *position3 + *size2)){ \
										if(*position2 > *position3){ \
											pixels = *size1; \
										}else{ \
											pixels = *position2 + *size1 - *position3; \
										} \
									}else{ \
										continue; \
									} \
									if(pixels > mostPixels){ \
										containerToUse = currentContainer1; \
										mostPixels = pixels; \
									} \
								} \
							} \
						} \
					} \
					if(containerToUse < allocatedContainerAmount){ \
						XGetWindowAttributes(display, container[containerToUse].window, &windowAttributes1); \
						XMoveResizeWindow(display, event.xany.window, windowAttributes1.x, windowAttributes1.y, windowAttributes1.width, windowAttributes1.height); \
						XResizeWindow(display, container[currentContainer].subwindow, windowAttributes1.width - border.axis.x, windowAttributes1.height - border.axis.y); \
						XMoveResizeWindow(display, container[containerToUse].window, windowAttributes.x, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
						XResizeWindow(display, container[containerToUse].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
					} \
				} \
			} \
		} \
	} \
}else if(container[currentContainer].inGrid){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	{ \
		int x; \
		getGridSlotData(monitorInfo, gridWidth - 1, 0, gridWidth, gridHeight, &x, NULL, (unsigned int *)&monitorInfo.width, NULL); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
	container[currentContainer].gridX = gridWidth - 1; \
	container[currentContainer].gridY = 0; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = gridHeight; \
}else{ \
	if(pointerInfo & MovePointerInfo){ \
		monitorInfo = getPointerMonitorInfo(); \
	}else{ \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
	} \
	unsigned int width; \
	if(option & FloatingFollowGrid){ \
		width = monitorInfo.width / gridWidth; \
	}else{ \
		width = monitorInfo.width / 2; \
	} \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - shadow, monitorInfo.y - shadow, width, monitorInfo.height); \
	XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, monitorInfo.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	getGridSlotData(monitorInfo, 0, 0, gridWidth, gridHeight, NULL, NULL, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
	container[currentContainer].gridX = 0; \
	container[currentContainer].gridY = 0; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	if(pointerInfo & MovePointerInfo){ \
		monitorInfo = getPointerMonitorInfo(); \
	}else{ \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
	} \
	unsigned int width; \
	unsigned int height; \
	if(option & FloatingFollowGrid){ \
		width = monitorInfo.width / gridWidth; \
		height = monitorInfo.height / gridHeight; \
	}else{ \
		width = monitorInfo.width / 2; \
		height = monitorInfo.height / 2; \
	} \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x - shadow, monitorInfo.y - shadow, width, height); \
	XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	{ \
		int x; \
		getGridSlotData(monitorInfo, gridWidth - 1, 0, gridWidth, gridHeight, &x, NULL, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
	container[currentContainer].gridX = gridWidth - 1; \
	container[currentContainer].gridY = 0; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	if(pointerInfo & MovePointerInfo){ \
		monitorInfo = getPointerMonitorInfo(); \
	}else{ \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
	} \
	unsigned int width; \
	unsigned int height; \
	if(option & FloatingFollowGrid){ \
		width = monitorInfo.width / gridWidth; \
		height = monitorInfo.height / gridHeight; \
	}else{ \
		width = monitorInfo.width / 2; \
		height = monitorInfo.height / 2; \
	} \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - shadow, monitorInfo.y - shadow, width, height); \
	XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	{ \
		int y; \
		getGridSlotData(monitorInfo, 0, gridHeight - 1, gridWidth, gridHeight, NULL, &y, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
	container[currentContainer].gridX = 0; \
	container[currentContainer].gridY = gridHeight - 1; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	if(pointerInfo & MovePointerInfo){ \
		monitorInfo = getPointerMonitorInfo(); \
	}else{ \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
	} \
	unsigned int width; \
	unsigned int height; \
	if(option & FloatingFollowGrid){ \
		width = monitorInfo.width / gridWidth; \
		height = monitorInfo.height / gridHeight; \
	}else{ \
		width = monitorInfo.width / 2; \
		height = monitorInfo.height / 2; \
	} \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x - shadow, monitorInfo.y + monitorInfo.height - height - shadow, width, height); \
	XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	{ \
		int x; \
		int y; \
		getGridSlotData(monitorInfo, gridWidth - 1, gridHeight - 1, gridWidth, gridHeight, &x, &y, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
	container[currentContainer].gridX = gridWidth - 1; \
	container[currentContainer].gridY = gridHeight - 1; \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	if(pointerInfo & MovePointerInfo){ \
		monitorInfo = getPointerMonitorInfo(); \
	}else{ \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
	} \
	unsigned int width; \
	unsigned int height; \
	if(option & FloatingFollowGrid){ \
		width = monitorInfo.width / gridWidth; \
		height = monitorInfo.height / gridHeight; \
	}else{ \
		width = monitorInfo.width / 2; \
		height = monitorInfo.height / 2; \
	} \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - shadow, monitorInfo.y + monitorInfo.height - height - shadow, width, height); \
	XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
}
#define MOVECENTER_KEYPRESS \
if(container[currentContainer].inGrid){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	container[currentContainer].gridX = gridWidth / 2; \
	container[currentContainer].gridY = gridHeight / 2; \
	{ \
		int x; \
		int y; \
		getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, (unsigned int *)&monitorInfo.width, (unsigned int *)&monitorInfo.height); \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, monitorInfo.width, monitorInfo.height); \
	} \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
	container[currentContainer].gridWidth = 1; \
	container[currentContainer].gridHeight = 1; \
}else{ \
	if(pointerInfo & MovePointerInfo){ \
		monitorInfo = getPointerMonitorInfo(); \
	}else{ \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
	} \
	unsigned int width; \
	unsigned int height; \
	if(option & FloatingFollowGrid){ \
		width = monitorInfo.width / gridWidth; \
		height = monitorInfo.height / gridHeight; \
	}else{ \
		width = monitorInfo.width / 2; \
		height = monitorInfo.height / 2; \
	} \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - width) / 2 - shadow, monitorInfo.y + (monitorInfo.height - height) / 2 - shadow, width, height); \
	XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
}
#define MOVEFULL_KEYPRESS \
if(container[currentContainer].inGrid){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x, monitorInfo.y, monitorInfo.width, monitorInfo.height); \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
	container[currentContainer].gridX = 0; \
	container[currentContainer].gridY = 0; \
	container[currentContainer].gridWidth = gridWidth; \
	container[currentContainer].gridHeight = gridHeight; \
}else{ \
	if(pointerInfo & MovePointerInfo){ \
		monitorInfo = getPointerMonitorInfo(); \
	}else{ \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
	} \
	XMoveResizeWindow(display, event.xany.window, monitorInfo.x - shadow, monitorInfo.y - shadow, monitorInfo.width, monitorInfo.height); \
	XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - border.axis.x, monitorInfo.height - border.axis.y); \
}
#define MOVENEXTPREVIOUSMONITOR_KEYPRESS \
if(findContainer(event.xany.window)){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
		if(monitorCompare(monitors[currentMonitor], monitorInfo)){ \
			if(command == MoveNextMonitorCommand){ \
				if(++currentMonitor < monitorAmount){ \
					if(containerIsMaximized(event.xany.window)){ \
						if(managementMode == TilingManagementMode){ \
\
\
\
							\
\
\
\
						}else if(container[currentContainer].inGrid){ \
\
\
\
							\
\
\
\
						}else{ \
\
\
\
							\
\
\
\
						} \
					}else{ \
						goto unmaximizedNextPreviousMonitor; \
					} \
				} \
			}else{ \
				if(currentMonitor){ \
					--currentMonitor; \
					if(containerIsMaximized(event.xany.window)){ \
						if(managementMode == TilingManagementMode){ \
\
\
\
							\
\
\
\
						}else if(container[currentContainer].inGrid){ \
\
\
\
							\
\
\
\
						}else{ \
\
\
\
							\
\
\
\
						} \
					}else{ \
						unmaximizedNextPreviousMonitor:{ \
							if(managementMode == TilingManagementMode){ \
\
\
\
								\
\
\
\
							}else if(container[currentContainer].inGrid){ \
								moveContainerToGridPosition(container[currentContainer], monitors[currentMonitor]); \
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
								XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
							} \
						} \
					} \
				} \
			} \
			break; \
		} \
	} \
}
#define MOVEABOVEMONITOR_KEYPRESS \
if(monitorInfo.y){ \
	if(findContainer(event.xany.window)){ \
		for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
			if(monitors[currentMonitor].x == monitorInfo.x && monitors[currentMonitor].y + monitors[currentMonitor].height == monitorInfo.y){ \
				goto moveToMonitor; \
			} \
		} \
	} \
}
#define MOVEBELOWMONITOR_KEYPRESS \
if(monitorInfo.y + monitorInfo.height < XDisplayHeight(display, XDefaultScreen(display))){ \
	if(findContainer(event.xany.window)){ \
		for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
			if(monitors[currentMonitor].x == monitorInfo.x && monitors[currentMonitor].y == monitorInfo.y + monitorInfo.height){ \
				goto moveToMonitor; \
			} \
		} \
	} \
}
#define MOVELEFTMONITOR_KEYPRESS \
if(monitorInfo.x){ \
	if(findContainer(event.xany.window)){ \
		for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
			if(monitors[currentMonitor].x + monitors[currentMonitor].width == monitorInfo.x && monitors[currentMonitor].y == monitorInfo.y){ \
				goto moveToMonitor; \
			} \
		} \
	} \
}
#define MOVERIGHTMONITOR_KEYPRESS \
if(monitorInfo.x + monitorInfo.width < XDisplayWidth(display, XDefaultScreen(display))){ \
	if(findContainer(event.xany.window)){ \
		for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
			if(monitors[currentMonitor].x == monitorInfo.x + monitorInfo.width && monitors[currentMonitor].y == monitorInfo.y){ \
				moveToMonitor:{ \
					if(containerIsMaximized(event.xany.window)){ \
						if(managementMode == TilingManagementMode){ \
\
\
\
							\
\
\
\
						}else{ \
							for(unsigned int currentMonitor1 = 0; currentMonitor1 < monitorAmount; ++currentMonitor1){ \
								if(maximizedContainer[currentMonitor1].window == event.xany.window){ \
									if(maximizedContainer[currentMonitor1].shouldChangeProperty){ \
										command = FullscreenCommand; \
									}else{ \
										command = BigscreenCommand; \
									} \
									break; \
								} \
							} \
							if(managementMode == GriddingManagementMode){ \
								unmaximizeContainer(event.xany.window, 0, color.containerBackground.gridding); \
							}else{ \
								unmaximizeContainer(event.xany.window, 0, color.containerBackground.inGrid); \
							} \
							if(container[currentContainer].inGrid){ \
								moveContainerToGridPosition(container[currentContainer], monitors[currentMonitor]); \
							}else{ \
								moveContainerToMonitor(event.xany.window, container[currentContainer].subwindow, monitorInfo, monitors[currentMonitor]); \
							} \
							maximizeContainer(event.xany.window, monitors[currentMonitor]); \
						} \
					}else{ \
						if(managementMode == TilingManagementMode){ \
\
\
\
							\
\
\
\
						}else if(container[currentContainer].inGrid){ \
							moveContainerToGridPosition(container[currentContainer], monitors[currentMonitor]); \
						}else{ \
							moveContainerToMonitor(event.xany.window, container[currentContainer].subwindow, monitorInfo, monitors[currentMonitor]); \
						} \
					} \
					break; \
				} \
			} \
		} \
	} \
}
#define TOGGLEWINDOWGRID_KEYPRESS \
if(!container[currentContainer].inGrid){ \
	addToGrid:{ \
		XSelectInput(display, event.xany.window, EnterWindowMask | SubstructureRedirectMask); \
		XSelectInput(display, container[currentContainer].subwindow, StructureNotifyMask); \
		XSetWindowBorderWidth(display, event.xany.window, 0); \
		XSetWindowBackground(display, event.xany.window, color.containerBackground.inGrid); \
		XUnmapWindow(display, event.xany.window); \
		XMapRaised(display, event.xany.window); \
		if(pointerInfo & AddToGridPointerInfo){ \
			monitorInfo = getPointerMonitorInfo(); \
		}else{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window); \
		} \
		if(option & FloatingFollowGrid || defaultGridPosition == TopLeftDefaultGridPosition){ \
			container[currentContainer].gridX = 0; \
			container[currentContainer].gridY = 0; \
		}else if(defaultGridPosition == TopRightDefaultGridPosition){ \
			container[currentContainer].gridX = gridWidth - 1; \
			container[currentContainer].gridY = 0; \
		}else if(defaultGridPosition == BottomLeftDefaultGridPosition){ \
			container[currentContainer].gridX = 0; \
			container[currentContainer].gridY = gridHeight - 1; \
		}else if(defaultGridPosition == BottomRightDefaultGridPosition){ \
			container[currentContainer].gridX = gridWidth - 1; \
			container[currentContainer].gridY = gridHeight - 1; \
		}else{ \
			container[currentContainer].gridX = gridWidth / 2; \
			container[currentContainer].gridY = gridHeight / 2; \
		} \
		unsigned int width; \
		unsigned int height; \
		{ \
			int x; \
			int y; \
			getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, &width, &height); \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
		} \
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
		container[currentContainer].inGrid = 1; \
		container[currentContainer].gridWidth = 1; \
		container[currentContainer].gridHeight = 1; \
	} \
}else{ \
	removeFromGrid:{ \
		XSelectInput(display, event.xany.window, ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | SubstructureRedirectMask); \
		XSelectInput(display, container[currentContainer].subwindow, ButtonReleaseMask | ButtonMotionMask | StructureNotifyMask); \
		XSetWindowBorderWidth(display, event.xany.window, shadow); \
		XSetWindowBackground(display, event.xany.window, color.containerBackground.floating); \
		XUnmapWindow(display, event.xany.window); \
		XMapRaised(display, event.xany.window); \
		if(pointerInfo & RemoveFromGridPointerInfo){ \
			monitorInfo = getPointerMonitorInfo(); \
		}else{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window); \
		} \
		unsigned int width; \
		unsigned int height; \
		if(option & FloatingFollowGrid){ \
			width = monitorInfo.width / gridWidth; \
			height = monitorInfo.height / gridHeight; \
		}else{ \
			width = monitorInfo.width / 2; \
			height = monitorInfo.height / 2; \
		} \
		XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - width) / 2 - shadow, monitorInfo.y + (monitorInfo.height - height) / 2 - shadow, width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
		container[currentContainer].inGrid = 0; \
	} \
}
#define MOVEUPGRID_KEYPRESS \
if(container[currentContainer].gridY){ \
	--container[currentContainer].gridY; \
	moveContainerToGridPosition(container[currentContainer], getWindowMonitorInfo(event.xany.window)); \
}
#define MOVEDOWNGRID_KEYPRESS \
if(container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
	++container[currentContainer].gridY; \
	moveContainerToGridPosition(container[currentContainer], getWindowMonitorInfo(event.xany.window)); \
}
#define MOVELEFTGRID_KEYPRESS \
if(container[currentContainer].gridX){ \
	--container[currentContainer].gridX; \
	moveContainerToGridPosition(container[currentContainer], getWindowMonitorInfo(event.xany.window)); \
}
#define MOVERIGHTGRID_KEYPRESS \
if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth){ \
	++container[currentContainer].gridX; \
	moveContainerToGridPosition(container[currentContainer], getWindowMonitorInfo(event.xany.window)); \
}
#define EXTENDWINDOWUP_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	if(windowAttributes.y > monitorInfo.y + (int)gapsY){ \
		Change changes[allocatedContainerAmount]; \
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
					monitorInfo1 = getWindowMonitorInfo(container[currentContainer].window); \
					if(monitorCompare(monitorInfo1, monitorInfo)){ \
						for(currentContainer1 = 0; currentContainer1 < allocatedContainerAmount; ++currentContainer1){ \
							XGetWindowAttributes(display, container[currentContainer1].window, &windowAttributes2); \
							if(windowAttributes2.y + windowAttributes2.height + (int)separationHeight == windowAttributes1.y && (closedOpenInterval(windowAttributes2.x, windowAttributes1.x, windowAttributes1.x + windowAttributes1.width) || closedOpenInterval(windowAttributes2.x + windowAttributes2.width, windowAttributes1.x, windowAttributes1.x + windowAttributes1.width))){ \
								monitorInfo1 = getWindowMonitorInfo(container[currentContainer1].window); \
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
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridY){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
		int y; \
		unsigned int height; \
		getGridSlotData(monitorInfo, container[currentContainer].gridX, --container[currentContainer].gridY, gridWidth, gridHeight, NULL, &y, NULL, &height); \
		++container[currentContainer].gridHeight; \
		height += windowAttributes.height; \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, y + monitorInfo.y, windowAttributes.width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.height += floatingExtendHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y - floatingExtendHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
}
#define EXTENDWINDOWDOWN_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	if(windowAttributes.y + windowAttributes.height < monitorInfo.y + monitorInfo.height - (int)gapsY){ \
		Change changes[allocatedContainerAmount]; \
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
					monitorInfo1 = getWindowMonitorInfo(container[currentContainer].window); \
					if(monitorCompare(monitorInfo1, monitorInfo)){ \
						for(currentContainer1 = 0; currentContainer1 < allocatedContainerAmount; ++currentContainer1){ \
							XGetWindowAttributes(display, container[currentContainer1].window, &windowAttributes2); \
							if(windowAttributes2.y == windowAttributes1.y + windowAttributes1.height + (int)separationHeight && (closedOpenInterval(windowAttributes2.x, windowAttributes1.x, windowAttributes1.x + windowAttributes1.width) || closedOpenInterval(windowAttributes2.x + windowAttributes2.width, windowAttributes1.x, windowAttributes1.x + windowAttributes1.width))){ \
								monitorInfo1 = getWindowMonitorInfo(container[currentContainer1].window); \
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
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int height; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
		++container[currentContainer].gridHeight; \
		height += windowAttributes.height; \
		XResizeWindow(display, event.xany.window, windowAttributes.width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.height += floatingExtendHeight; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
}
#define EXTENDWINDOWLEFT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	if(windowAttributes.x > monitorInfo.x + (int)gapsX){ \
		Change changes[allocatedContainerAmount]; \
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
					monitorInfo1 = getWindowMonitorInfo(container[currentContainer].window); \
					if(monitorCompare(monitorInfo1, monitorInfo)){ \
						for(currentContainer1 = 0; currentContainer1 < allocatedContainerAmount; ++currentContainer1){ \
							XGetWindowAttributes(display, container[currentContainer1].window, &windowAttributes2); \
							if(windowAttributes2.x + windowAttributes2.width + (int)separationWidth == windowAttributes1.x && (closedOpenInterval(windowAttributes2.y, windowAttributes1.y, windowAttributes1.y + windowAttributes1.height) || closedOpenInterval(windowAttributes2.y + windowAttributes2.height, windowAttributes1.y, windowAttributes1.y + windowAttributes1.height))){ \
								monitorInfo1 = getWindowMonitorInfo(container[currentContainer1].window); \
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
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridX){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		monitorInfo = getWindowMonitorInfo(event.xany.window); \
		int x; \
		unsigned int width; \
		getGridSlotData(monitorInfo, --container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, NULL, &width, NULL); \
		++container[currentContainer].gridWidth; \
		width += windowAttributes.width; \
		XMoveResizeWindow(display, event.xany.window, x + monitorInfo.x, windowAttributes.y, width, windowAttributes.height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, windowAttributes.height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x - floatingExtendWidth, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
}
#define EXTENDWINDOWRIGHT_KEYPRESS \
if(managementMode == TilingManagementMode){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
\
\
\
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	if(windowAttributes.x + windowAttributes.width < monitorInfo.x + monitorInfo.width - (int)gapsX){ \
		Change changes[allocatedContainerAmount]; \
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
					monitorInfo1 = getWindowMonitorInfo(container[currentContainer].window); \
					if(monitorCompare(monitorInfo1, monitorInfo)){ \
						for(currentContainer1 = 0; currentContainer1 < allocatedContainerAmount; ++currentContainer1){ \
							XGetWindowAttributes(display, container[currentContainer1].window, &windowAttributes2); \
							if(windowAttributes2.x == windowAttributes1.x + windowAttributes1.width + (int)separationWidth && (closedOpenInterval(windowAttributes2.y, windowAttributes1.y, windowAttributes1.y + windowAttributes1.height) || closedOpenInterval(windowAttributes2.y + windowAttributes2.height, windowAttributes1.y, windowAttributes1.y + windowAttributes1.height))){ \
								monitorInfo1 = getWindowMonitorInfo(container[currentContainer1].window); \
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
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth){ \
		unsigned int width; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window), container[currentContainer].gridX + container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
		++container[currentContainer].gridWidth; \
		width += windowAttributes.width; \
		XResizeWindow(display, event.xany.window, width, windowAttributes.height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, windowAttributes.height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridX || container[currentContainer].gridY){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int height; \
		unsigned int width; \
		{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	windowAttributes.height += floatingExtendHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x - floatingExtendWidth, windowAttributes.y - floatingExtendHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth || container[currentContainer].gridY){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	windowAttributes.height += floatingExtendHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y - floatingExtendHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridX || container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	windowAttributes.height += floatingExtendHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x - floatingExtendWidth, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth || container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width += floatingExtendWidth; \
	windowAttributes.height += floatingExtendHeight; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int height; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window), container[currentContainer].gridX, container[currentContainer].gridY + --container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
		height = windowAttributes.height - height; \
		XResizeWindow(display, event.xany.window, windowAttributes.width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.height -= floatingShrinkHeight; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int height; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
		++container[currentContainer].gridY; \
		--container[currentContainer].gridHeight; \
		windowAttributes.y += height; \
		height = windowAttributes.height - height; \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y, windowAttributes.width, height); \
		XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.height -= floatingShrinkHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y + floatingShrinkHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridWidth > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window), container[currentContainer].gridX + --container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
		width = windowAttributes.width - width; \
		XResizeWindow(display, event.xany.window, width, windowAttributes.height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, windowAttributes.height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridWidth > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		getGridSlotData(getWindowMonitorInfo(event.xany.window), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
		++container[currentContainer].gridX; \
		--container[currentContainer].gridWidth; \
		windowAttributes.x += width; \
		width = windowAttributes.width - width; \
		XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y, width, windowAttributes.height); \
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, windowAttributes.height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x + floatingShrinkWidth, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridWidth > 1 || container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	windowAttributes.height -= floatingShrinkHeight; \
	XResizeWindow(display, event.xany.window, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridWidth > 1 || container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	windowAttributes.height -= floatingShrinkHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x + floatingShrinkWidth, windowAttributes.y, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridWidth > 1 && container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	windowAttributes.height -= floatingShrinkHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y + floatingShrinkHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
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
}else if(container[currentContainer].inGrid){ \
	if(container[currentContainer].gridWidth > 1 && container[currentContainer].gridHeight > 1){ \
		XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
		unsigned int width; \
		unsigned int height; \
		{ \
			monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
		XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
	} \
}else{ \
	XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
	windowAttributes.width -= floatingShrinkWidth; \
	windowAttributes.height -= floatingShrinkHeight; \
	XMoveResizeWindow(display, event.xany.window, windowAttributes.x + floatingShrinkWidth, windowAttributes.y + floatingShrinkHeight, windowAttributes.width, windowAttributes.height); \
	XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
}
#define FULLSCREEN_BIGSCREEN_KEYPRESS \
if(findContainer(event.xany.window)){ \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
		if(monitorCompare(monitors[currentMonitor], monitorInfo)){ \
			break; \
		} \
	} \
	if(!maximizedContainer[currentMonitor].window){ \
		goFullscreenBigscreen:{ \
			maximizeContainer(event.xany.window, monitorInfo); \
		} \
	}else{ \
		const Window window = maximizedContainer[currentMonitor].window; \
		unmaximizeContainer(window, shadow, color.containerBackground.floating); \
		if(event.xany.window != window){ \
			goto goFullscreenBigscreen; \
		} \
	} \
}
#define DETACHWINDOW_KEYPRESS \
if(findContainer(event.xany.window)){ \
	const unsigned int width = monitorInfo.width / 2; \
	const unsigned int height = monitorInfo.height / 2; \
	monitorInfo = getWindowMonitorInfo(event.xany.window); \
	XReparentWindow(display, container[currentContainer].subwindow, rootWindow, monitorInfo.x + (monitorInfo.width - width) / 2, monitorInfo.y + (monitorInfo.height - height) / 2); \
	XResizeWindow(display, container[currentContainer].subwindow, width, height); \
	goto unmapWindow; \
}
#define CLOSE_KEYPRESS \
if(findContainer(event.xany.window)){ \
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
if(findContainer(event.xany.window)){ \
	XUnmapWindow(display, container[currentContainer].subwindow); \
	XDestroyWindow(display, container[currentContainer].subwindow); \
	goto unmapWindow; \
}
#define KEYRELEASE \
if(motionContainer.action){ \
	for(unsigned int current = 0; current < shortcutAmount; ++current){ \
		if(shortcut[current].command == MoveCommand && shortcut[current].keycode == event.xkey.keycode && shortcut[current].masks == event.xkey.state){ \
			goto keyButtonRelease; \
		} \
	} \
}
#define BUTTONRELEASE \
if(motionContainer.action){ \
	for(unsigned int current = 0; current < buttonAmount; ++current){ \
		if(button[current].command == MoveCommand){ \
			if(event.xbutton.state & Button1Mask){ \
				event.xbutton.state ^= Button1Mask; \
			} \
			if(event.xbutton.state & Button2Mask){ \
				event.xbutton.state ^= Button2Mask; \
			} \
			if(event.xbutton.state & Button3Mask){ \
				event.xbutton.state ^= Button3Mask; \
			} \
			if(event.xbutton.state & Button4Mask){ \
				event.xbutton.state ^= Button4Mask; \
			} \
			if(event.xbutton.state & Button5Mask){ \
				event.xbutton.state ^= Button5Mask; \
			} \
			if(button[current].button == event.xbutton.button && button[current].masks == event.xbutton.state){ \
				keyButtonRelease:{ \
					XSelectInput(display, rootWindow, SubstructureRedirectMask); \
					if(motionContainer.action == MoveMotionAction){ \
						if(motionContainer.subaction){ \
							if(directionOutlineWindowMapped){ \
								XUnmapWindow(display, directionOutlineWindow); \
								directionOutlineWindowMapped = 0; \
							} \
							command = motionContainer.direction[motionContainer.subaction - DirectionMotionSubactionOffset]; \
							if(command){ \
								if(option & FloatingMinimalMoveOption){ \
									XUnmapWindow(display, motionContainer.window); \
									{ \
										const unsigned int b = shadow; \
										shadow = moveResizeWindowBorder; \
										moveResizeWindowBorder = b; \
									} \
									const Window w = motionContainer.window; \
									motionContainer.window = moveResizeWindow; \
									moveResizeWindow = w; \
								} \
								event.xany.window = motionContainer.window; \
								motionContainer.options = NoMotionOptions; \
								motionContainer.action = NoMotionAction; \
								goto keyButtonPressSearchless; \
							}else{ \
								goto minimallyMoveWindow; \
							} \
						}else{ \
							minimallyMoveWindow:{ \
								if(option & FloatingMinimalMoveOption){ \
									XUnmapWindow(display, motionContainer.window); \
									{ \
										const unsigned int b = shadow; \
										shadow = moveResizeWindowBorder; \
										moveResizeWindowBorder = b; \
									} \
									XMoveWindow(display, moveResizeWindow, motionContainer.x + moveResizeWindowBorder - motionContainer.positionOffset - shadow, motionContainer.y + moveResizeWindowBorder - motionContainer.positionOffset - shadow); \
									goto switchMotionResizeWindows; \
								} \
							} \
						} \
					}else{ \
						if(option & FloatingMinimalResizeOption){ \
							XUnmapWindow(display, motionContainer.window); \
							XMoveResizeWindow(display, moveResizeWindow, motionContainer.x + motionContainer.positionOffset + moveResizeWindowBorder - shadow, motionContainer.y + motionContainer.positionOffset + moveResizeWindowBorder - shadow, motionContainer.width, motionContainer.height); \
							XResizeWindow(display, motionContainer.subwindow, motionContainer.width - border.axis.x, motionContainer.height - border.axis.y); \
							switchMotionResizeWindows:{ \
								const Window w = motionContainer.window; \
								motionContainer.window = moveResizeWindow; \
								moveResizeWindow = w; \
							} \
						} \
					} \
					motionContainer.options = NoMotionOptions; \
					motionContainer.action = NoMotionAction; \
				} \
			} \
		} \
	} \
}
#define MOTIONNOTIFY \
if(motionContainer.options & CanActMotionOption){ \
	if(motionContainer.action == MoveMotionAction){ \
		if(option & FloatingAllowStickingOption){ \
			monitorInfo = getWindowMonitorInfo(motionContainer.window); \
			if(closedOpenInterval(motionContainer.x + (int)shadow, monitorInfo.x, monitorInfo.x + floatingStickyThresholdX)){ \
				if(!(motionContainer.options & HasLockedXMotionOption)){ \
					motionContainer.x = monitorInfo.x - shadow; \
					XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
					motionContainer.movementBorderX = event.xmotion.x_root + floatingDistanceToTravelX; \
					motionContainer.options |= HasLockedXMotionOption; \
				}else{ \
					if(event.xmotion.x_root >= motionContainer.movementBorderX){ \
						motionContainer.options ^= HasLockedXMotionOption; \
					} \
				} \
			}else if(closedInterval(motionContainer.x + (int)(motionContainer.width + shadow), monitorInfo.x + monitorInfo.width - floatingStickyThresholdX, monitorInfo.x + monitorInfo.width)){ \
				if(!(motionContainer.options & HasLockedXMotionOption)){ \
					motionContainer.x = monitorInfo.x + monitorInfo.width - motionContainer.width - shadow; \
					XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
					motionContainer.movementBorderX = event.xmotion.x_root - floatingDistanceToTravelX; \
					motionContainer.options |= HasLockedXMotionOption; \
				}else{ \
					if(event.xmotion.x_root <= motionContainer.movementBorderX){ \
						motionContainer.options ^= HasLockedXMotionOption; \
					} \
				} \
			} \
			if(closedOpenInterval(motionContainer.y + (int)shadow, monitorInfo.y, monitorInfo.y + floatingStickyThresholdY)){ \
				if(!(motionContainer.options & HasLockedYMotionOption)){ \
					motionContainer.y = monitorInfo.y - shadow; \
					XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
					motionContainer.movementBorderY = event.xmotion.y_root + floatingDistanceToTravelY; \
					motionContainer.options |= HasLockedYMotionOption; \
				}else{ \
					if(event.xmotion.y_root >= motionContainer.movementBorderY){ \
						motionContainer.options ^= HasLockedYMotionOption; \
					} \
				} \
			}else if(closedInterval(motionContainer.y + (int)(motionContainer.height + shadow), monitorInfo.y + monitorInfo.height - floatingStickyThresholdY, monitorInfo.y + monitorInfo.height)){ \
				if(!(motionContainer.options & HasLockedYMotionOption)){ \
					motionContainer.y = monitorInfo.y + monitorInfo.height - motionContainer.height - shadow; \
					XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
					motionContainer.movementBorderY = event.xmotion.y_root - floatingDistanceToTravelY; \
					motionContainer.options |= HasLockedYMotionOption; \
				}else{ \
					if(event.xmotion.y_root <= motionContainer.movementBorderY){ \
						motionContainer.options ^= HasLockedYMotionOption; \
					} \
				} \
			} \
			if(!(motionContainer.options & HasLockedXMotionOption && motionContainer.options & HasLockedYMotionOption)){ \
				if(!(motionContainer.options & HasLockedXMotionOption)){ \
					motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX; \
				} \
				if(!(motionContainer.options & HasLockedYMotionOption)){ \
					motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY; \
				} \
				XMoveWindow(display, motionContainer.window, motionContainer.x, motionContainer.y); \
			} \
		}else{ \
			XMoveWindow(display, motionContainer.window, event.xmotion.x_root - motionContainer.pointerOffsetX, event.xmotion.y_root - motionContainer.pointerOffsetY); \
		} \
		if(option & FloatingAllowDirectionStickingOption){ \
			monitorInfo = getPointerMonitorInfo(); \
			if(closedOpenInterval(event.xmotion.y_root, monitorInfo.y, monitorInfo.y + floatingDirectionThreshold)){ \
				if(closedOpenInterval(event.xmotion.x_root, monitorInfo.x, monitorInfo.x + floatingDirectionThreshold)){ \
					if(motionContainer.subaction != TopLeftDirectionMotionSubaction){ \
						motionContainer.subaction = TopLeftDirectionMotionSubaction; \
						goto moveDirectionOutlineWindow; \
					} \
				}else if(closedOpenInterval(event.xmotion.x_root, monitorInfo.x + floatingDirectionThreshold, monitorInfo.x + monitorInfo.width - floatingDirectionThreshold)){ \
					if(motionContainer.subaction != TopDirectionMotionSubaction){ \
						motionContainer.subaction = TopDirectionMotionSubaction; \
						goto moveDirectionOutlineWindow; \
					} \
				}else if(closedOpenInterval(event.xmotion.x_root, monitorInfo.x + monitorInfo.width - floatingDirectionThreshold, monitorInfo.x + monitorInfo.width)){ \
					if(motionContainer.subaction != TopRightDirectionMotionSubaction){ \
						motionContainer.subaction = TopRightDirectionMotionSubaction; \
						goto moveDirectionOutlineWindow; \
					} \
				}else{ \
					goto unmapDirectionOutlineWindow; \
				} \
			}else if(closedOpenInterval(event.xmotion.y_root, monitorInfo.y + floatingDirectionThreshold, monitorInfo.y + monitorInfo.height - floatingDirectionThreshold)){ \
				if(closedOpenInterval(event.xmotion.x_root, monitorInfo.x, monitorInfo.x + floatingDirectionThreshold)){ \
					if(motionContainer.subaction != LeftDirectionMotionSubaction){ \
						motionContainer.subaction = LeftDirectionMotionSubaction; \
						goto moveDirectionOutlineWindow; \
					} \
				}else if(closedOpenInterval(event.xmotion.x_root, monitorInfo.x + monitorInfo.width - floatingDirectionThreshold, monitorInfo.x + monitorInfo.width)){ \
					if(motionContainer.subaction != RightDirectionMotionSubaction){ \
						motionContainer.subaction = RightDirectionMotionSubaction; \
						goto moveDirectionOutlineWindow; \
					} \
				}else{ \
					goto unmapDirectionOutlineWindow; \
				} \
			}else if(closedOpenInterval(event.xmotion.y_root, monitorInfo.y + monitorInfo.height - floatingDirectionThreshold, monitorInfo.y + monitorInfo.height)){ \
				if(closedOpenInterval(event.xmotion.x_root, monitorInfo.x, monitorInfo.x + floatingDirectionThreshold)){ \
					if(motionContainer.subaction != BottomLeftDirectionMotionSubaction){ \
						motionContainer.subaction = BottomLeftDirectionMotionSubaction; \
						goto moveDirectionOutlineWindow; \
					} \
				}else if(closedOpenInterval(event.xmotion.x_root, monitorInfo.x + floatingDirectionThreshold, monitorInfo.x + monitorInfo.width - floatingDirectionThreshold)){ \
					if(motionContainer.subaction != BottomDirectionMotionSubaction){ \
						motionContainer.subaction = BottomDirectionMotionSubaction; \
						goto moveDirectionOutlineWindow; \
					} \
				}else if(closedOpenInterval(event.xmotion.x_root, monitorInfo.x + monitorInfo.width - floatingDirectionThreshold, monitorInfo.x + monitorInfo.width)){ \
					if(motionContainer.subaction != BottomRightDirectionMotionSubaction){ \
						motionContainer.subaction = BottomRightDirectionMotionSubaction; \
						moveDirectionOutlineWindow:{ \
							if(directionOutlineWindow){ \
								command = motionContainer.direction[motionContainer.subaction - DirectionMotionSubactionOffset]; \
								if(command){ \
									if(command == MoveFullCommand){ \
										XMoveResizeWindow(display, directionOutlineWindow, monitorInfo.x - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetX, monitorInfo.y - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetY, monitorInfo.width - 2 * directionOutlineWindowEqualOffsetX, monitorInfo.height - 2 * directionOutlineWindowEqualOffsetY); \
									}else if(command == MoveCenterCommand){ \
										const unsigned int width = monitorInfo.width / 2; \
										const unsigned int height = monitorInfo.height / 2; \
										XMoveResizeWindow(display, directionOutlineWindow, monitorInfo.x + (monitorInfo.width - width) / 2 - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetX, monitorInfo.y + (monitorInfo.height - height) / 2 - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetY, width - 2 * directionOutlineWindowEqualOffsetX, height - 2 * directionOutlineWindowEqualOffsetY); \
									}else if(command == MoveTopCommand){ \
										XMoveResizeWindow(display, directionOutlineWindow, monitorInfo.x - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetX, monitorInfo.y - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetY, monitorInfo.width - 2 * directionOutlineWindowEqualOffsetX, monitorInfo.height / 2 - 2 * directionOutlineWindowEqualOffsetY); \
									}else if(command == MoveBottomCommand){ \
										XMoveResizeWindow(display, directionOutlineWindow, monitorInfo.x - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetX, monitorInfo.y + monitorInfo.height - monitorInfo.height / 2 - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetY, monitorInfo.width - 2 * directionOutlineWindowEqualOffsetX, monitorInfo.height / 2 - 2 * directionOutlineWindowEqualOffsetY); \
									}else if(command == MoveLeftCommand){ \
										XMoveResizeWindow(display, directionOutlineWindow, monitorInfo.x - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetX, monitorInfo.y - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetY, monitorInfo.width / 2 - 2 * directionOutlineWindowEqualOffsetX, monitorInfo.height - 2 * directionOutlineWindowEqualOffsetY); \
									}else if(command == MoveRightCommand){ \
										XMoveResizeWindow(display, directionOutlineWindow, monitorInfo.x + monitorInfo.width - monitorInfo.width / 2 - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetX, monitorInfo.y - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetY, monitorInfo.width / 2 - 2 * directionOutlineWindowEqualOffsetX, monitorInfo.height - 2 * directionOutlineWindowEqualOffsetY); \
									}else if(command == MoveTopLeftCommand){ \
										XMoveResizeWindow(display, directionOutlineWindow, monitorInfo.x - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetX, monitorInfo.y - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetY, monitorInfo.width / 2 - 2 * directionOutlineWindowEqualOffsetX, monitorInfo.height / 2 - 2 * directionOutlineWindowEqualOffsetY); \
									}else if(command == MoveTopRightCommand){ \
										XMoveResizeWindow(display, directionOutlineWindow, monitorInfo.x + monitorInfo.width - monitorInfo.width / 2 - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetX, monitorInfo.y - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetY, monitorInfo.width / 2 - 2 * directionOutlineWindowEqualOffsetX, monitorInfo.height / 2 - 2 * directionOutlineWindowEqualOffsetY); \
									}else if(command == MoveBottomLeftCommand){ \
										XMoveResizeWindow(display, directionOutlineWindow, monitorInfo.x - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetX, monitorInfo.y + monitorInfo.height - monitorInfo.height / 2 - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetY, monitorInfo.width / 2 - 2 * directionOutlineWindowEqualOffsetX, monitorInfo.height / 2 - 2 * directionOutlineWindowEqualOffsetY); \
									}else{ \
										XMoveResizeWindow(display, directionOutlineWindow, monitorInfo.x + monitorInfo.width - monitorInfo.width / 2 - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetX, monitorInfo.y + monitorInfo.height - monitorInfo.height / 2 - directionOutlineWindowBorder + directionOutlineWindowEqualOffsetY, monitorInfo.width / 2 - 2 * directionOutlineWindowEqualOffsetX, monitorInfo.height / 2 - 2 * directionOutlineWindowEqualOffsetY); \
									} \
									if(!directionOutlineWindowMapped){ \
										XLowerWindow(display, directionOutlineWindow); \
										if(gridMapped){ \
											for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
												XLowerWindow(display, grid[currentMonitor]); \
											} \
										} \
										XMapWindow(display, directionOutlineWindow); \
										directionOutlineWindowMapped = 1; \
									} \
								} \
							} \
						} \
					} \
				}else{ \
					goto unmapDirectionOutlineWindow; \
				} \
			}else{ \
				unmapDirectionOutlineWindow:{ \
					if(directionOutlineWindowMapped){ \
						XUnmapWindow(display, directionOutlineWindow); \
						directionOutlineWindowMapped = 0; \
					} \
					motionContainer.subaction = NoMotionSubaction; \
				} \
			} \
		} \
	}else if(motionContainer.action == ResizeMotionAction){ \
		if(motionContainer.subaction == UpResizeMotionSubaction){ \
			motionContainer.height += motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.height <= (int)border.axis.y){ \
				motionContainer.height = border.axis.y + 1; \
			}else{ \
				motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == DownResizeMotionSubaction){ \
			motionContainer.height -= motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.height <= (int)border.axis.y){ \
				motionContainer.height = border.axis.y + 1; \
			}else{ \
				motionContainer.pointerOffsetY = event.xmotion.y_root - motionContainer.y; \
			} \
			XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == LeftResizeMotionSubaction){ \
			motionContainer.width += motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			if((int)motionContainer.width <= (int)border.axis.x){ \
				motionContainer.width = border.axis.x + 1; \
			}else{ \
				motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == RightResizeMotionSubaction){ \
			motionContainer.width -= motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			if((int)motionContainer.width <= (int)border.axis.x){ \
				motionContainer.width = border.axis.x + 1; \
			}else{ \
				motionContainer.pointerOffsetX = event.xmotion.x_root - motionContainer.x; \
			} \
			XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == UpLeftResizeMotionSubaction){ \
			motionContainer.width += motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			motionContainer.height += motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.width <= (int)border.axis.x){ \
				motionContainer.width = border.axis.x + 1; \
			}else{ \
				motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX; \
			} \
			if((int)motionContainer.height <= (int)border.axis.y){ \
				motionContainer.height = border.axis.y + 1; \
			}else{ \
				motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == UpRightResizeMotionSubaction){ \
			motionContainer.width -= motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			motionContainer.height += motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.width <= (int)border.axis.x){ \
				motionContainer.width = border.axis.x + 1; \
			}else{ \
				motionContainer.pointerOffsetX = event.xmotion.x_root - motionContainer.x; \
			} \
			if((int)motionContainer.height <= (int)border.axis.y){ \
				motionContainer.height = border.axis.y + 1; \
			}else{ \
				motionContainer.y = event.xmotion.y_root - motionContainer.pointerOffsetY; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else if(motionContainer.subaction == DownLeftResizeMotionSubaction){ \
			motionContainer.width += motionContainer.pointerOffsetX + motionContainer.x - event.xmotion.x_root; \
			motionContainer.height -= motionContainer.pointerOffsetY + motionContainer.y - event.xmotion.y_root; \
			if((int)motionContainer.width <= (int)border.axis.x){ \
				motionContainer.width = border.axis.x + 1; \
			}else{ \
				motionContainer.x = event.xmotion.x_root - motionContainer.pointerOffsetX; \
			} \
			if((int)motionContainer.height <= (int)border.axis.y){ \
				motionContainer.height = border.axis.y + 1; \
			}else{ \
				motionContainer.pointerOffsetY = event.xmotion.y_root - motionContainer.y; \
			} \
			XMoveResizeWindow(display, motionContainer.window, motionContainer.x + motionContainer.positionOffset, motionContainer.y + motionContainer.positionOffset, motionContainer.width, motionContainer.height); \
		}else{ \
			motionContainer.width += event.xmotion.x_root - motionContainer.x - motionContainer.pointerOffsetX; \
			motionContainer.height += event.xmotion.y_root - motionContainer.y - motionContainer.pointerOffsetY; \
			if((int)motionContainer.width <= (int)border.axis.x){ \
				motionContainer.width = border.axis.x + 1; \
			}else{ \
				 motionContainer.pointerOffsetX = event.xmotion.x_root - motionContainer.x; \
			} \
			if((int)motionContainer.height <= (int)border.axis.y){ \
				motionContainer.height = border.axis.y + 1; \
			}else{ \
				motionContainer.pointerOffsetY = event.xmotion.y_root - motionContainer.y; \
			} \
			XResizeWindow(display, motionContainer.window, motionContainer.width, motionContainer.height); \
		} \
		if(!(option & FloatingMinimalResizeOption)){ \
			XResizeWindow(display, motionContainer.subwindow, motionContainer.width - border.axis.x, motionContainer.height - border.axis.y); \
		} \
	} \
	motionContainer.options ^= CanActMotionOption; \
}else{ \
	if(!XPending(display)){ \
		motionContainer.options |= CanActMotionOption; \
	} \
}
#define ENTERNOTIFY \
if(!commandedWindow && !motionContainer.action && findContainer(event.xcrossing.window)){ \
	XRaiseWindow(display, event.xcrossing.window); \
	XSetInputFocus(display, container[currentContainer].subwindow, RevertToPointerRoot, CurrentTime); \
}
#define UNMAPNOTIFY \
for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
	if(container[currentContainer].subwindow == event.xany.window){ \
		event.xany.window = container[currentContainer].window; \
		unmapWindow:{ \
			XUnmapWindow(display, event.xany.window); \
			XSetInputFocus(display, rootWindow, RevertToPointerRoot, CurrentTime); \
			clearWindowProperties(event.xany.window); \
			container[currentContainer].subwindow = None; \
			--allocatedContainerAmount; \
			for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
				if(maximizedContainer[currentMonitor].window == event.xany.window){ \
					maximizedContainer[currentMonitor].window = None; \
					maximizedContainer[currentMonitor].subwindow = None; \
					break; \
				} \
			} \
			if(allocatedContainerAmount){ \
				Window w; \
				while(currentContainer <= allocatedContainerAmount){ \
					w = container[currentContainer].window; \
					container[currentContainer] = container[currentContainer + 1]; \
					container[++currentContainer].window = w; \
				} \
			} \
			if(managementMode == TilingManagementMode && allocatedContainerAmount){ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
				bool containerInMonitorMap[allocatedContainerAmount]; \
				unsigned int monitorContainerAmount = 0; \
				{ \
					XRRMonitorInfo mi; \
					for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
						mi = getWindowMonitorInfo(container[currentContainer].window); \
						if(monitorCompare(mi, monitorInfo)){ \
							containerInMonitorMap[currentContainer] = 1; \
							++monitorContainerAmount; \
						}else{ \
							containerInMonitorMap[currentContainer] = 0; \
						} \
					} \
				} \
				if(monitorContainerAmount){ \
					const Options useSeparatorsOption = option & TilingUseSeparatorsOption; \
					if(tilingReplacingMode <= VerticalEqualTilingReplacingMode){ \
						int x = monitorInfo.x + gapsX; \
						int y = monitorInfo.y + gapsY; \
						unsigned int width; \
						unsigned int height; \
						unsigned int counter = 0; \
						int *position; \
						unsigned int *size; \
						unsigned int gaps; \
						unsigned int totalSeparatorWidth = separatorBorders + separatorWidth; \
						unsigned int abnormal; \
						unsigned int normal; \
						unsigned int currentContainerList[monitorContainerAmount]; \
						int *attribute; \
						{ \
							unsigned int monitorSize; \
							unsigned int availableSpace; \
							if(tilingReplacingMode == HorizontalEqualTilingReplacingMode){ \
								height = monitorInfo.height - 2 * gapsY; \
								position = &x; \
								size = &width; \
								gaps = gapsX; \
								monitorSize = monitorInfo.width; \
								attribute = &windowAttributes.x; \
							}else{ \
								width = monitorInfo.width - 2 * gapsX; \
								position = &y; \
								size = &height; \
								gaps = gapsY; \
								monitorSize = monitorInfo.height; \
								attribute = &windowAttributes.y; \
							} \
							if(useSeparatorsOption){ \
								availableSpace = monitorSize - (2 * monitorContainerAmount * gaps + (monitorContainerAmount - 1) * totalSeparatorWidth); \
							}else{ \
								availableSpace = monitorSize - (monitorContainerAmount + 1) * gaps; \
							} \
							normal = availableSpace / monitorContainerAmount; \
							abnormal = availableSpace - (monitorContainerAmount - 1) * normal; \
						} \
						*size = normal; \
						totalSeparatorWidth += gaps; \
						{ \
							int attributeList[monitorContainerAmount]; \
							currentContainer = 0; \
							for(;;){ \
								if(containerInMonitorMap[currentContainer]){ \
									XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
									currentContainerList[counter] = currentContainer; \
									attributeList[counter] = *attribute; \
									if(++counter == monitorContainerAmount){ \
										break; \
									} \
								} \
								++currentContainer; \
							} \
							const unsigned int monitorContainerAmount1 = monitorContainerAmount + 1; \
							unsigned int ccl; \
							int al; \
							for(currentContainer = 1; currentContainer < monitorContainerAmount; ++currentContainer){ \
								for(counter = 1; counter < monitorContainerAmount1 - currentContainer; ++counter){ \
									if(attributeList[counter - 1] > attributeList[counter]){ \
										ccl = currentContainerList[counter]; \
										currentContainerList[counter] = currentContainerList[counter - 1]; \
										currentContainerList[counter - 1] = ccl; \
										al = attributeList[counter]; \
										attributeList[counter] = attributeList[counter - 1]; \
										attributeList[counter - 1] = al; \
									} \
								} \
							} \
						} \
						{ \
							const unsigned int middle = monitorContainerAmount / 2; \
							counter = 0; \
							for(;;){ \
								currentContainer = currentContainerList[counter]; \
								XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
								XResizeWindow(display, container[currentContainer].subwindow, width - border.axis.x, height - border.axis.y); \
								if(++counter == monitorContainerAmount){ \
									break; \
								} \
								*position += *size + gaps; \
								if(useSeparatorsOption){ \
									*position += totalSeparatorWidth; \
								} \
								if(counter == middle){ \
									*size = abnormal; \
								}else{ \
									*size = normal; \
								} \
							} \
						} \
					}else{ \
\
\
\
						\
\
\
\
					} \
				} \
			} \
			if(containerAmount > defaultContainerAmount && allocatedContainerAmount == containerAmount - containerIncrementDecrementAmount - 1){ \
				containerChangeAmount = -containerIncrementDecrementAmount; \
				goto saveOpenClients; \
			} \
			break; \
		} \
	} \
}
#define CONFIGUREREQUEST \
for(currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
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
			if(!container[currentContainer].inGrid){ \
				if((event.xconfigurerequest.value_mask & CWX || event.xconfigurerequest.value_mask & CWY)){ \
					if(event.xconfigurerequest.value_mask & CWX){ \
						windowAttributes.x = event.xconfigurerequest.x - border.left; \
					} \
					if(event.xconfigurerequest.value_mask & CWY){ \
						windowAttributes.y = event.xconfigurerequest.y - border.up; \
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
				XResizeWindow(display, event.xconfigurerequest.window, windowAttributes.width - border.axis.x, windowAttributes.height - border.axis.y); \
			} \
		} \
		new = 0; \
		goto configureRequestEmergencyExit; \
	} \
} \
if(new){ \
	monitorInfo = getPointerMonitorInfo(); \
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
	XMoveResizeWindow(display, event.xconfigurerequest.window, monitorInfo.x, monitorInfo.y, monitorInfo.width / gridWidth - border.axis.x, monitorInfo.height / gridHeight - border.axis.y); \
} \
configureRequestEmergencyExit:{}

#endif
