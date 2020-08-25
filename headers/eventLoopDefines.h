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

#define REALLOCATE_SUBWINDOWS \
if(allocatedContainerAmount){ \
	FILE *file = fopen("/home/steven/.microwm/.subwindows", "r"); \
	if(file){ \
		{ \
			char c; \
			Window subwindow; \
			bool negative; \
			int x; \
			int y; \
			unsigned int width; \
			unsigned int height; \
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
					if((c = fgetc(file)) != '\n'){ \
						height = height * 10 + c - 48; \
					}else{ \
						break; \
					} \
				} \
				container[currentContainer].subwindow = subwindow; \
				XSelectInput(display, subwindow, ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | StructureNotifyMask); \
				XReparentWindow(display, subwindow, container[currentContainer].window, innerBorder, innerBorder); \
				XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
				XResizeWindow(display, subwindow, width - innerBorders, height - innerBorders); \
			} \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				XMapWindow(display, container[currentContainer].window); \
				XMapWindow(display, container[currentContainer].subwindow); \
			} \
		} \
		fclose(file); \
	} \
	lastCreatedWindow = container[allocatedContainerAmount - 1].window; \
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
				}else if(c == GridModeCommand){ \
					goto changeToGridMode; \
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
				}else if(c == GridModeCommand){ \
					GRIDMODE_KEYPRESS \
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
		if(allocatedContainerAmount){ \
			Window window; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				window = container[currentContainer].window; \
				XSelectInput(display, window, EnterWindowMask); \
				XSelectInput(display, container[currentContainer].subwindow, EnterWindowMask | StructureNotifyMask); \
				XSetWindowBorderWidth(display, window, border); \
				XSetWindowBackground(display, window, containerBackgroundColor); \
				XUnmapWindow(display, window); \
				XMapWindow(display, window); \
				container[currentContainer].inGrid = 0; \
			} \
			managementMode = FloatingManagementMode; \
			if(pointerInfo & ChangeModePointerInfo){ \
				goto recascadeOption0; \
			}else{ \
				goto recascadeOption1; \
			} \
		} \
	} \
}
#define GRIDMODE_KEYPRESS \
changeToGridMode:{ \
	if(managementMode != GridManagementMode){ \
		XRRMonitorInfo monitorInfo; \
		Window window; \
		unsigned int gridX; \
		unsigned int gridY; \
		int x; \
		int y; \
		unsigned int width; \
		unsigned int height; \
		if(pointerInfo & ChangeModePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(); \
		} \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			window = container[currentContainer].window; \
			if(!(pointerInfo & ChangeModePointerInfo)){ \
				monitorInfo = getWindowMonitorInfo(window); \
			} \
			getGridSlotData(monitorInfo, gridX, gridY, gridWidth, gridHeight, &x, &y, &width, &height); \
			XSelectInput(display, window, EnterWindowMask); \
			XSelectInput(display, container[currentContainer].subwindow, EnterWindowMask | StructureNotifyMask); \
			XSetWindowBorderWidth(display, window, 0); \
			XSetWindowBackground(display, window, inGridContainerBackgroundColor); \
			XUnmapWindow(display, window); \
			XMapWindow(display, window); \
			XMoveResizeWindow(display, window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
			container[currentContainer].inGrid = 1; \
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
		managementMode = GridManagementMode; \
	} \
}



























#define TILINGMODE_KEYPRESS \
changeToTilingMode:{ \
	if(managementMode != TilingManagementMode){ \
		unsigned int width = 1920 / allocatedContainerAmount; \
		unsigned int height = 1080; \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			XSelectInput(display, container[currentContainer].window, EnterWindowMask); \
			XSelectInput(display, container[currentContainer].subwindow, EnterWindowMask | StructureNotifyMask); \
\
\
\
			\
\
\
\
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
			createGrid(monitorAmount, gridWidth, gridHeight, gridSubwindowBorderColor, gridSubwindowBackgroundColor, grid); \
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
	if(gridWidth < maxGridWidth && gridHeight < maxGridHeight){ \
		++gridWidth; \
		++gridHeight; \
		goto deleteGrid; \
	} \
}
#define SHRINKGRID_KEYPRESS \
shrinkGrid:{ \
	if(gridWidth > 1 && gridHeight > 1){ \
		--gridWidth; \
		--gridHeight; \
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
					createGrid(monitorAmount, gridWidth, gridHeight, gridSubwindowBorderColor, gridSubwindowBackgroundColor, grid); \
					gridExists = 1; \
					for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
						XLowerWindow(display, grid[currentMonitor]); \
						XMapWindow(display, grid[currentMonitor]); \
						XMapSubwindows(display, grid[currentMonitor]); \
					} \
				}else{ \
					gridExists = 0; \
				} \
			} \
			if(managementMode != TilingManagementMode){ \
				XRRMonitorInfo monitorInfo; \
				int x0; \
				int y0; \
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
						getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x0, &y0, NULL, NULL); \
						getGridSlotData(monitorInfo, container[currentContainer].gridX + container[currentContainer].gridWidth - 1, container[currentContainer].gridY + container[currentContainer].gridHeight - 1, gridWidth, gridHeight, &x1, &y1, &width, &height); \
						width = x1 - x0 + width; \
						height = y1 - y0 + height; \
						XMoveResizeWindow(display, container[currentContainer].window, monitorInfo.x + x0, monitorInfo.y + y0, width, height); \
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
			if(pointerInfo & RecascadePointerInfo){ \
				recascadeOption0:{ \
					const XRRMonitorInfo monitorInfo = getPointerMonitorInfo(); \
					unsigned int width; \
					unsigned int height; \
					if(option & FloatingFollowGrid){ \
						width = monitorInfo.width / gridWidth; \
						height = monitorInfo.height / gridHeight; \
					}else{ \
						width = monitorInfo.width / 2; \
						height = monitorInfo.height / 2; \
					} \
					int x = monitorInfo.x + (monitorInfo.width - width) / 2; \
					int y = monitorInfo.y + (monitorInfo.height - height) / 2; \
					if(cascade.overrideGridWindows){ \
						for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
							XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
							XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
							x += cascade.offsetX; \
							y += cascade.offsetY; \
						} \
					}else{ \
						for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
							if(container[currentContainer].inGrid){ \
								XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
								XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
								x += cascade.offsetX; \
								y += cascade.offsetY; \
							} \
						} \
					} \
				} \
			}else{ \
				recascadeOption1:{ \
					unsigned int ma; \
					XRRMonitorInfo *const monitors = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&ma); \
					if(monitors){ \
						if(ma == monitorAmount){ \
							XRRMonitorInfo monitorInfo; \
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
								if(cascade.overrideGridWindows){ \
									for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
										monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
										if(monitorInfo.x == mi.x && monitorInfo.y == mi.y && monitorInfo.width == mi.width && monitorInfo.height == mi.height){ \
											XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
											XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
											x += cascade.offsetX; \
											y += cascade.offsetY; \
										} \
									} \
								}else{ \
									for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
										if(container[currentContainer].inGrid){ \
											monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
											if(monitorInfo.x == mi.x && monitorInfo.y == mi.y && monitorInfo.width == mi.width && monitorInfo.height == mi.height){ \
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
						XRRFreeMonitors(monitors); \
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
				if(!container[currentContainer].inGrid){ \
					if(event.xbutton.x > (int)innerBorder && event.xbutton.y > (int)innerBorder){ \
						XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
						if(event.xbutton.x_root < (int)(windowAttributes.x + windowAttributes.width + border - innerBorder) && event.xbutton.y_root < (int)(windowAttributes.y + windowAttributes.height + border - innerBorder)){ \
							motionContainer.window = event.xbutton.window; \
							XGetWindowAttributes(display, event.xbutton.subwindow, &windowAttributes); \
							x = event.xbutton.x - windowAttributes.x + border; \
							y = event.xbutton.y - windowAttributes.y + border; \
							action = MoveAction; \
						}else{ \
							/*goto setResize;*/ \
						} \
					}else{ \
						\
					} \
				} \
				break; \
			} \
		} \
	} \
}



/*
		setResize:{ \
			motionContainer.window = event.xbutton.window; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				if(container[currentContainer].window == motionContainer.window){ \
					motionContainer.subwindow = container[currentContainer].subwindow; \
					break; \
				} \
			} \
			XGetWindowAttributes(display, motionContainer.window, &windowAttributes); \
			x = event.xbutton.x + border; \
			y = event.xbutton.y + border; \
\
\
\
			xpos = windowAttributes.x; \
			ypos = windowAttributes.y; \
			width = windowAttributes.width; \
			height = windowAttributes.height; \
\
\
\
			action = ResizeAction; \
			if(x > xpos + (int)border || y > ypos + (int)border){ \
				subaction = ResizeSubaction; \
			}else{ \
				subaction = MoveResizeSubaction; \
			} \
		} \
*/



























#define MOVETOP_KEYPRESS \
moveTop:{ \
	if(managementMode == FloatingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!container[currentContainer].inGrid){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						XRRMonitorInfo monitorInfo; \
						if(pointerInfo & MovePointerInfo){ \
							monitorInfo = getPointerMonitorInfo(); \
						}else{ \
							monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
				if(!container[currentContainer].inGrid){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						XRRMonitorInfo monitorInfo; \
						if(pointerInfo & MovePointerInfo){ \
							monitorInfo = getPointerMonitorInfo(); \
						}else{ \
							monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
				if(!container[currentContainer].inGrid){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						XRRMonitorInfo monitorInfo; \
						if(pointerInfo & MovePointerInfo){ \
							monitorInfo = getPointerMonitorInfo(); \
						}else{ \
							monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
				if(!container[currentContainer].inGrid){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						XRRMonitorInfo monitorInfo; \
						if(pointerInfo & MovePointerInfo){ \
							monitorInfo = getPointerMonitorInfo(); \
						}else{ \
							monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
				if(!container[currentContainer].inGrid){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						XRRMonitorInfo monitorInfo; \
						if(pointerInfo & MovePointerInfo){ \
							monitorInfo = getPointerMonitorInfo(); \
						}else{ \
							monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
				if(!container[currentContainer].inGrid){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						XRRMonitorInfo monitorInfo; \
						if(pointerInfo & MovePointerInfo){ \
							monitorInfo = getPointerMonitorInfo(); \
						}else{ \
							monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
				if(!container[currentContainer].inGrid){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						XRRMonitorInfo monitorInfo; \
						if(pointerInfo & MovePointerInfo){ \
							monitorInfo = getPointerMonitorInfo(); \
						}else{ \
							monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
				if(!container[currentContainer].inGrid){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						XRRMonitorInfo monitorInfo; \
						if(pointerInfo & MovePointerInfo){ \
							monitorInfo = getPointerMonitorInfo(); \
						}else{ \
							monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
				if(!container[currentContainer].inGrid){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						XRRMonitorInfo monitorInfo; \
						if(pointerInfo & MovePointerInfo){ \
							monitorInfo = getPointerMonitorInfo(); \
						}else{ \
							monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
	unsigned int ma; \
	XRRMonitorInfo *const mi = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&ma); \
	if(mi){ \
		if(ma == monitorAmount){ \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				if(container[currentContainer].window == event.xany.window){ \
					if(!container[currentContainer].inGrid){ \
						XRRMonitorInfo monitorInfo = getWindowMonitorInfo(event.xany.window); \
						for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
							if(mi[currentMonitor].x == monitorInfo.x && mi[currentMonitor].y == monitorInfo.y && mi[currentMonitor].width == monitorInfo.width && mi[currentMonitor].height == monitorInfo.height){ \
								if(next){ \
									if(++currentMonitor < monitorAmount){ \
										monitorInfo = mi[currentMonitor]; \
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
										monitorInfo = mi[currentMonitor]; \
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
		} \
		XRRFreeMonitors(mi); \
	} \
}
#define ADDWINDOWTOGRID_KEYPRESS \
addWindowToGridSlot:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!container[currentContainer].inGrid){ \
					goto addToGrid; \
				} \
				break; \
			} \
		} \
	} \
}
#define REMOVEWINDOWFROMGRID_KEYPRESS \
removeWindowFromGrid:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(container[currentContainer].inGrid){ \
					goto removeFromGrid; \
				} \
				break; \
			} \
		} \
	} \
}
#define TOGGLEWINDOWGRID_KEYPRESS \
toggleWindowGrid:{ \
	if(managementMode != TilingManagementMode){ \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				if(!container[currentContainer].inGrid){ \
					addToGrid:{ \
						XSelectInput(display, event.xany.window, EnterWindowMask); \
						XSelectInput(display, container[currentContainer].subwindow, EnterWindowMask | StructureNotifyMask); \
						XSetWindowBorderWidth(display, event.xany.window, 0); \
						XSetWindowBackground(display, event.xany.window, inGridContainerBackgroundColor); \
						XUnmapWindow(display, event.xany.window); \
						XMapWindow(display, event.xany.window); \
						{ \
							unsigned int width; \
							unsigned int height; \
							{ \
								int x; \
								int y; \
								XRRMonitorInfo monitorInfo; \
								if(pointerInfo & AddToGridPointerInfo){ \
									monitorInfo = getPointerMonitorInfo(); \
								}else{ \
									monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
								} \
								getGridSlotData(monitorInfo, 0, 0, gridWidth, gridHeight, &x, &y, &width, &height); \
								XMoveResizeWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y, width, height); \
							} \
							XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
						} \
						container[currentContainer].inGrid = 1; \
						container[currentContainer].gridX = 0; \
						container[currentContainer].gridY = 0; \
						container[currentContainer].gridWidth = 1; \
						container[currentContainer].gridHeight = 1; \
					} \
				}else{ \
					removeFromGrid:{ \
						XSelectInput(display, event.xany.window, ButtonReleaseMask | EnterWindowMask | ButtonMotionMask); \
						XSelectInput(display, container[currentContainer].subwindow, ButtonReleaseMask | EnterWindowMask | ButtonMotionMask | StructureNotifyMask); \
						XSetWindowBorderWidth(display, event.xany.window, border); \
						XSetWindowBackground(display, event.xany.window, containerBackgroundColor); \
						XUnmapWindow(display, event.xany.window); \
						XMapWindow(display, event.xany.window); \
						{ \
							unsigned int width; \
							unsigned int height; \
							{ \
								XRRMonitorInfo monitorInfo; \
								if(pointerInfo & RemoveFromGridPointerInfo){ \
									monitorInfo = getPointerMonitorInfo(); \
								}else{ \
									monitorInfo = getWindowMonitorInfo(event.xany.window); \
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
						container[currentContainer].inGrid = 0; \
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
				if(container[currentContainer].inGrid){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						int x; \
						int y; \
						const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
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
				if(container[currentContainer].inGrid){ \
					unsigned int width; \
					unsigned int height; \
					{ \
						int x; \
						int y; \
						const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
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
				if(container[currentContainer].inGrid){ \
					if(container[currentContainer].gridX || container[currentContainer].gridY){ \
						if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
							if(container[currentContainer].gridY){ \
								--container[currentContainer].gridY; \
							}else{ \
								if(option & GridAllowBoundaryBreakYOption){ \
									--container[currentContainer].gridX; \
									container[currentContainer].gridY = gridHeight - 1; \
								}else{ \
									break; \
								} \
							} \
							int x; \
							int y; \
							const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
							getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, NULL, NULL); \
							XMoveWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y); \
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
				if(container[currentContainer].inGrid){ \
					if(container[currentContainer].gridX < gridWidth - 1 || container[currentContainer].gridY < gridHeight - 1){ \
						if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
							if(container[currentContainer].gridY < gridHeight - 1){ \
								++container[currentContainer].gridY; \
							}else{ \
								if(option & GridAllowBoundaryBreakYOption){ \
									++container[currentContainer].gridX; \
									container[currentContainer].gridY = 0; \
								}else{ \
									break; \
								} \
							} \
							int x; \
							int y; \
							const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
							getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, NULL, NULL); \
							XMoveWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y); \
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
				if(container[currentContainer].inGrid){ \
					if(container[currentContainer].gridX < gridWidth - 1 || container[currentContainer].gridY < gridHeight - 1){ \
						if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
							if(container[currentContainer].gridX < gridWidth - 1){ \
								++container[currentContainer].gridX; \
							}else{ \
								if(option & GridAllowBoundaryBreakXOption){ \
									container[currentContainer].gridX = 0; \
									++container[currentContainer].gridY; \
								}else{ \
									break; \
								} \
							} \
							int x; \
							int y; \
							const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
							getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, NULL, NULL); \
							XMoveWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y); \
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
				if(container[currentContainer].inGrid){ \
					if(container[currentContainer].gridX || container[currentContainer].gridY){ \
						if(container[currentContainer].gridWidth == 1 && container[currentContainer].gridHeight == 1){ \
							if(container[currentContainer].gridX){ \
								--container[currentContainer].gridX; \
							}else{ \
								if(option & GridAllowBoundaryBreakXOption){ \
									container[currentContainer].gridX = gridWidth - 1; \
									--container[currentContainer].gridY; \
								}else{ \
									break; \
								} \
							} \
							int x; \
							int y; \
							const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
							getGridSlotData(monitorInfo, container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, &y, NULL, NULL); \
							XMoveWindow(display, event.xany.window, monitorInfo.x + x, monitorInfo.y + y); \
						} \
					} \
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
			if(container[currentContainer].inGrid){ \
				if(!container[currentContainer].gridY){ \
					break; \
				} \
				++container[currentContainer].gridHeight; \
				{ \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
					getGridSlotData(monitorInfo, container[currentContainer].gridX, --container[currentContainer].gridY, gridWidth, gridHeight, NULL, &y, NULL, &height); \
					y += monitorInfo.y; \
				} \
				height += windowAttributes.height; \
			}else{ \
				y = windowAttributes.y - extendHeight; \
				height = windowAttributes.height + extendHeight; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridY + container[currentContainer].gridHeight == gridHeight){ \
					break; \
				} \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY + ++container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
				height += windowAttributes.height; \
			}else{ \
				height = windowAttributes.height + extendHeight; \
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
			if(container[currentContainer].inGrid){ \
				if(!container[currentContainer].gridX){ \
					break; \
				} \
				++container[currentContainer].gridWidth; \
				{ \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
					getGridSlotData(monitorInfo, --container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, NULL, &width, NULL); \
					x += monitorInfo.x; \
					width += windowAttributes.width; \
				} \
			}else{ \
				x = windowAttributes.x - extendWidth; \
				width = windowAttributes.width + extendWidth; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridX + container[currentContainer].gridWidth == gridWidth){ \
					break; \
				} \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX + ++container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
				width += windowAttributes.width; \
			}else{ \
				width = windowAttributes.width + extendWidth; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridY){ \
					++container[currentContainer].gridHeight; \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
					getGridSlotData(monitorInfo, container[currentContainer].gridX, --container[currentContainer].gridY, gridWidth, gridHeight, NULL, &y, NULL, &height); \
					y += monitorInfo.y; \
					height += windowAttributes.height; \
				}else{ \
					y = windowAttributes.y; \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridX){ \
					++container[currentContainer].gridWidth; \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
					getGridSlotData(monitorInfo, --container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, NULL, &width, NULL); \
					x += monitorInfo.x; \
					width += windowAttributes.width; \
				}else{ \
					x = windowAttributes.x; \
					width = windowAttributes.width; \
				} \
				if(x == windowAttributes.x && y == windowAttributes.y && width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				x = windowAttributes.x - extendWidth; \
				y = windowAttributes.y - extendHeight; \
				width = windowAttributes.width + extendHeight; \
				height = windowAttributes.height + extendHeight; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridY){ \
					++container[currentContainer].gridHeight; \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
					getGridSlotData(monitorInfo, container[currentContainer].gridX, --container[currentContainer].gridY, gridWidth, gridHeight, NULL, &y, NULL, &height); \
					y += monitorInfo.y; \
					height += windowAttributes.height; \
				}else{ \
					y = windowAttributes.y; \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX + ++container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
					width += windowAttributes.width; \
				}else{ \
					width = windowAttributes.width; \
				} \
				if(y == windowAttributes.y && width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				y = windowAttributes.y - extendHeight; \
				width = windowAttributes.width + extendHeight; \
				height = windowAttributes.height + extendHeight; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY + ++container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
					height += windowAttributes.height; \
				}else{ \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridX){ \
					++container[currentContainer].gridWidth; \
					const XRRMonitorInfo monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
					getGridSlotData(monitorInfo, --container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, NULL, &width, NULL); \
					x += monitorInfo.x; \
					width += windowAttributes.width; \
				}else{ \
					x = windowAttributes.x; \
					width = windowAttributes.width; \
				} \
				if(x == windowAttributes.x && width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				x = windowAttributes.x - extendWidth; \
				width = windowAttributes.width + extendHeight; \
				height = windowAttributes.height + extendHeight; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridY + container[currentContainer].gridHeight < gridHeight){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY + ++container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
					height += windowAttributes.height; \
				}else{ \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridX + container[currentContainer].gridWidth < gridWidth){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX + ++container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
					width += windowAttributes.width; \
				}else{ \
					width = windowAttributes.width; \
				} \
				if(width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				width = windowAttributes.width + extendHeight; \
				height = windowAttributes.height + extendHeight; \
			} \
			XMoveResizeWindow(display, event.xany.window, windowAttributes.x, windowAttributes.y, width, height); \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridHeight == 1){ \
					break; \
				} \
				--container[currentContainer].gridHeight; \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
				height = windowAttributes.height - height; \
			}else{ \
				height = windowAttributes.height - shrinkHeight; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridHeight == 1){ \
					break; \
				} \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, &y, NULL, &height); \
				++container[currentContainer].gridY; \
				--container[currentContainer].gridHeight; \
				y = windowAttributes.y + height; \
				height = windowAttributes.height - height; \
			}else{ \
				y = windowAttributes.y + shrinkHeight; \
				height = windowAttributes.height - shrinkHeight; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridWidth == 1){ \
					break; \
				} \
				--container[currentContainer].gridWidth; \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
				width = windowAttributes.width - width; \
			}else{ \
				width = windowAttributes.width - shrinkHeight; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridWidth == 1){ \
					break; \
				} \
				getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, NULL, &width, NULL); \
				++container[currentContainer].gridX; \
				--container[currentContainer].gridWidth; \
				x = windowAttributes.x + width; \
				width = windowAttributes.width - width; \
			}else{ \
				x = windowAttributes.x + shrinkWidth; \
				width = windowAttributes.width - shrinkWidth; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridHeight > 1){ \
					--container[currentContainer].gridHeight; \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
					height = windowAttributes.height - height; \
				}else{ \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridWidth > 1){ \
					--container[currentContainer].gridWidth; \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
					width = windowAttributes.width - width; \
				}else{ \
					width = windowAttributes.width; \
				} \
				if(width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				width = windowAttributes.width - shrinkWidth; \
				height = windowAttributes.height - shrinkHeight; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridHeight > 1){ \
					--container[currentContainer].gridHeight; \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, NULL, &height); \
					height = windowAttributes.height - height; \
				}else{ \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridWidth > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, NULL, &width, NULL); \
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
				x = windowAttributes.x + shrinkWidth; \
				width = windowAttributes.width - shrinkWidth; \
				height = windowAttributes.height - shrinkHeight; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridHeight > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, &y, NULL, &height); \
					++container[currentContainer].gridY; \
					--container[currentContainer].gridHeight; \
					y = windowAttributes.y + height; \
					height = windowAttributes.height - height; \
				}else{ \
					y = windowAttributes.y; \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridWidth > 1){ \
					--container[currentContainer].gridWidth; \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, NULL, &width, NULL); \
					width = windowAttributes.width - width; \
				}else{ \
					width = windowAttributes.width; \
				} \
				if(width == (unsigned int)windowAttributes.width && height == (unsigned int)windowAttributes.height){ \
					break; \
				} \
			}else{ \
				y = windowAttributes.y + shrinkHeight; \
				width = windowAttributes.width - shrinkWidth; \
				height = windowAttributes.height - shrinkHeight; \
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
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridHeight > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, NULL, &y, NULL, &height); \
					++container[currentContainer].gridY; \
					--container[currentContainer].gridHeight; \
					y = windowAttributes.y + height; \
					height = windowAttributes.height - height; \
				}else{ \
					y = windowAttributes.y; \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridWidth > 1){ \
					getGridSlotData(getWindowMonitorInfo(container[currentContainer].window), container[currentContainer].gridX, container[currentContainer].gridY, gridWidth, gridHeight, &x, NULL, &width, NULL); \
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
				x = windowAttributes.x + shrinkWidth; \
				y = windowAttributes.y + shrinkHeight; \
				width = windowAttributes.width - shrinkWidth; \
				height = windowAttributes.height - shrinkHeight; \
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
			if(!container[currentContainer].inGrid){ \
				XRRMonitorInfo monitorInfo; \
				if(pointerInfo & FullscreenPointerInfo){ \
					monitorInfo = getPointerMonitorInfo(); \
				}else{ \
					monitorInfo = getWindowMonitorInfo(event.xany.window); \
				} \
				XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
				if(windowAttributes.x == monitorInfo.x - (int)border && windowAttributes.y == monitorInfo.y - (int)border && windowAttributes.width == monitorInfo.width && windowAttributes.height == monitorInfo.height){ \
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
									.l[3] = 1 \
								} \
							} \
						}; \
						XSendEvent(display, e.xclient.window, False, PropertyChangeMask, &e); \
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
									.l[3] = 1 \
								} \
							} \
						}; \
						XSendEvent(display, e.xclient.window, False, PropertyChangeMask, &e); \
					} \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y - border, monitorInfo.width, monitorInfo.height); \
					XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - innerBorders, monitorInfo.height - innerBorders); \
				} \
			} \
			break; \
		} \
	} \
}



























#define BIGSCREEN_KEYPRESS \
bigscreen:{ \
	for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			if(!container[currentContainer].inGrid){ \
				XRRMonitorInfo monitorInfo; \
				if(pointerInfo & BigscreenPointerInfo){ \
					monitorInfo = getPointerMonitorInfo(); \
				}else{ \
					monitorInfo = getWindowMonitorInfo(event.xany.window); \
				} \
				XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
				if(windowAttributes.x == monitorInfo.x - (int)border && windowAttributes.y == monitorInfo.y - (int)border && windowAttributes.width == monitorInfo.width && windowAttributes.height == monitorInfo.height){ \
					if(option & FloatingFollowGrid){ \
						windowAttributes.width = monitorInfo.width / gridWidth; \
						windowAttributes.height = monitorInfo.height / gridHeight; \
					}else{ \
						windowAttributes.width = monitorInfo.width / 2; \
						windowAttributes.height = monitorInfo.height / 2; \
					} \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - windowAttributes.width) / 2 - border, monitorInfo.y + (monitorInfo.height - windowAttributes.height) / 2 - border, windowAttributes.width, windowAttributes.height); \
					XResizeWindow(display, container[currentContainer].subwindow, windowAttributes.width - innerBorders, windowAttributes.height - innerBorders); \
				}else{ \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y - border, monitorInfo.width, monitorInfo.height); \
					XResizeWindow(display, container[currentContainer].subwindow, monitorInfo.width - innerBorders, monitorInfo.height - innerBorders); \
				} \
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
			XUnmapWindow(display, event.xany.window); \
			XDestroyWindow(display, container[currentContainer].subwindow); \
			XSetInputFocus(display, XDefaultRootWindow(display), RevertToPointerRoot, CurrentTime); \
			clearWindowProperties(event.xany.window); \
			container[currentContainer].subwindow = None; \
			if(container[currentContainer].inGrid){ \
				XSelectInput(display, event.xany.window, ButtonReleaseMask | EnterWindowMask | ButtonMotionMask); \
				XSetWindowBorderWidth(display, event.xany.window, border); \
				XSetWindowBackground(display, container[currentContainer].window, containerBackgroundColor); \
				container[currentContainer].inGrid = 0; \
			} \
			--allocatedContainerAmount; \
			unsigned int currentContainer1; \
			Window tempWindow; \
			lastCreatedWindow = None; \
			for(currentContainer = 0; currentContainer < containerAmount; ++currentContainer){ \
				if(!container[currentContainer].subwindow){ \
					--containerAmount; \
					for(currentContainer1 = currentContainer; currentContainer1 < containerAmount; ++currentContainer1){ \
						tempWindow = container[currentContainer1 + 1].window; \
						container[currentContainer1 + 1].window = container[currentContainer1].window; \
						container[currentContainer1].window = tempWindow; \
						container[currentContainer1].subwindow = container[currentContainer1 + 1].subwindow; \
					} \
					++containerAmount; \
				}else{ \
					lastCreatedWindow = container[currentContainer].window; \
				} \
			} \
			break; \
		} \
	} \
}
#endif
