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
	unsigned int currentContainer; \
	if(file){ \
		char line[DefaultCharactersCount + 1]; \
		int x[allocatedContainerAmount]; \
		int y[allocatedContainerAmount]; \
		unsigned int width[allocatedContainerAmount]; \
		unsigned int height[allocatedContainerAmount]; \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			unsigned int element = 0; \
			for(;;){ \
				line[element] = fgetc(file); \
				if(line[element] == '\n' || feof(file)){ \
					line[element] = '\0'; \
					break; \
				}else if(element < DefaultCharactersCount){ \
					++element; \
				} \
			} \
			if(feof(file)){ \
				break; \
			} \
			element = 0; \
			while(line[element] != ' '){ \
				if(line[element] >= '0' && line[element] <= '9'){ \
					container[currentContainer].subwindow *= 10; \
					container[currentContainer].subwindow += line[element]; \
					container[currentContainer].subwindow -= 48; \
					++element; \
				}else{ \
					container[currentContainer].subwindow = None; \
					while(line[element] != ' '){ \
						++element; \
					} \
					break; \
				} \
			} \
			++element; \
			{ \
				bool negative = 0; \
				x[currentContainer] = 0; \
				while(line[element] != ' '){ \
					if(line[element] >= '0' && line[element] <= '9'){ \
						x[currentContainer] *= 10; \
						x[currentContainer] += line[element]; \
						x[currentContainer] -= 48; \
						++element; \
					}else if(line[element] == '-'){ \
						negative = 1; \
						++element; \
					}else{ \
						x[currentContainer] = 0; \
						while(line[element] != ' '){ \
							++element; \
						} \
						break; \
					} \
				} \
				if(x[currentContainer] && negative){ \
					x[currentContainer] = -x[currentContainer]; \
				} \
				++element; \
				y[currentContainer] = 0; \
				negative = 0; \
				while(line[element] != ' '){ \
					if(line[element] >= '0' && line[element] <= '9'){ \
						y[currentContainer] *= 10; \
						y[currentContainer] += line[element]; \
						y[currentContainer] -= 48; \
						++element; \
					}else if(line[element] == '-'){ \
						negative = 1; \
						++element; \
					}else{ \
						y[currentContainer] = 0; \
						while(line[element] != ' '){ \
							++element; \
						} \
						break; \
					} \
				} \
				if(y[currentContainer] && negative){ \
					y[currentContainer] = -y[currentContainer]; \
				} \
			} \
			++element; \
			width[currentContainer] = 0; \
			while(line[element] != ' '){ \
				if(line[element] >= '0' && line[element] <= '9'){ \
					width[currentContainer] *= 10; \
					width[currentContainer] += line[element]; \
					width[currentContainer] -= 48; \
					++element; \
				}else{ \
					width[currentContainer] = 1; \
					while(line[element] != ' '){ \
						++element; \
					} \
					break; \
				} \
			} \
			++element; \
			height[currentContainer] = 0; \
			while(line[element]){ \
				if(line[element] >= '0' && line[element] <= '9'){ \
					height[currentContainer] *= 10; \
					height[currentContainer] += line[element]; \
					height[currentContainer] -= 48; \
					++element; \
				}else{ \
					height[currentContainer] = 1; \
					while(line[element] != ' '){ \
						++element; \
					} \
					break; \
				} \
			} \
		} \
		for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			XReparentWindow(display, container[currentContainer].subwindow, container[currentContainer].window, innerBorder, innerBorder); \
			XMapWindow(display, container[currentContainer].window); \
			XMapWindow(display, container[currentContainer].subwindow); \
			XMoveResizeWindow(display, container[currentContainer].window, x[currentContainer], y[currentContainer], width[currentContainer], height[currentContainer]); \
			XResizeWindow(display, container[currentContainer].subwindow, width[currentContainer] - innerBorders, height[currentContainer] - innerBorders); \
		} \
		fclose(file); \
	} \
}
#define KEYPRESS \
for(unsigned int currentShortcut = 0; currentShortcut < shortcutAmount; ++currentShortcut){ \
	if(event.xkey.keycode == shortcut[currentShortcut].keycode && event.xkey.state == shortcut[currentShortcut].masks){ \
		const Command c = shortcut[currentShortcut].command; \
		if(c){ \
			if(c <= RootCommandCeiling){ \
				if(c == ShowGridCommand){ \
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
				}else if(c == AddWindowToGrid){ \
					goto moveFirstGridSlot; \
				}else if(c == RemoveWindowFromGrid){ \
					goto removeWindowFromGrid; \
				}else if(c == MoveFirstGridSlotCommand){ \
					goto moveFirstGridSlot; \
				}else if(c == MoveLastGridSlotCommand){ \
					goto moveLastGridSlot; \
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
					goto extendWindowUp; \
				}else if(c == ShrinkWindowDownCommand){ \
					goto extendWindowDown; \
				}else if(c == ShrinkWindowLeftCommand){ \
					goto extendWindowLeft; \
				}else if(c == ShrinkWindowRightCommand){ \
					goto extendWindowRight; \
				}else if(c == ShrinkWindowUpLeftCommand){ \
					goto extendWindowUpLeft; \
				}else if(c == ShrinkWindowUpRightCommand){ \
					goto extendWindowUpRight; \
				}else if(c == ShrinkWindowDownLeftCommand){ \
					goto extendWindowDownLeft; \
				}else if(c == ShrinkWindowDownRightCommand){ \
					goto extendWindowDownRight; \
				}else if(c == FullscreenCommand){ \
					goto fullscreen; \
				}else if(c == BigscreenCommand){ \
					goto bigscreen; \
				}else{ \
					goto close; \
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
	if(event.xbutton.button == button[currentButton].button && event.xbutton.state == button[currentButton].masks){ \
		const Command c = button[currentButton].command; \
		if(c){ \
			if(c <= RootCommandCeiling){ \
				if(c == ShowGridCommand){ \
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
				}else if(c == AddWindowToGrid){ \
					goto moveFirstGridSlot; \
				}else if(c == RemoveWindowFromGrid){ \
					REMOVEWINDOWFROMGRID_KEYPRESS \
				}else if(c == MoveFirstGridSlotCommand){ \
					MOVEFIRSTGRIDSLOT_KEYPRESS \
				}else if(c == MoveLastGridSlotCommand){ \
					MOVELASTGRIDSLOT_KEYPRESS \
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
				}else{ \
					CLOSE_KEYPRESS \
				} \
			} \
		} \
		break; \
	} \
} \
if(mode != ContinueMode){ \
	break; \
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
			createGrid:{ \
				createGrid(monitorAmount, gridWidth, gridHeight, gridSubwindowBorderColor, gridSubwindowBackgroundColor, grid); \
				gridExists = 1; \
			} \
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
		gridSlotAmount = gridWidth * gridHeight; \
		goto deleteGrid; \
	} \
}
#define SHRINKGRID_KEYPRESS \
shrinkGrid:{ \
	if(gridWidth > 1 && gridHeight > 1){ \
		--gridWidth; \
		--gridHeight; \
		gridSlotAmount = gridWidth * gridHeight; \
		deleteGrid:{ \
			if(gridExists){ \
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
				gridExists = 0; \
				if(gridMapped){ \
					goto createGrid; \
				} \
			} \
		} \
	} \
}
#define RECASCADE_KEYPRESS \
recascade:{ \
	if(allocatedContainerAmount){ \
		XRRMonitorInfo monitorInfo; \
		unsigned int currentContainer; \
		if(pointerInfo & RecascadePointerInfo){ \
			monitorInfo = getPointerMonitorInfo(); \
			const unsigned int width = monitorInfo.width / gridWidth; \
			const unsigned int height = monitorInfo.height / gridHeight; \
			int x = monitorInfo.x + (monitorInfo.width - width) / 2; \
			int y = monitorInfo.y + (monitorInfo.height - height) / 2; \
			for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
				XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
				XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
				x += cascade.x; \
				y += cascade.y; \
			} \
		}else{ \
			unsigned int ma; \
			XRRMonitorInfo *const monitors = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&ma); \
			if(monitors){ \
				if(ma == monitorAmount){ \
					XRRMonitorInfo mi; \
					for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
						mi = monitors[currentMonitor]; \
						width = mi.width / gridWidth; \
						height = mi.height / gridHeight; \
						x = mi.x + (mi.width - width) / 2; \
						y = mi.y + (mi.height - height) / 2; \
						for(currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
							monitorInfo = getWindowMonitorInfo(container[currentContainer].window); \
							if(monitorInfo.x == mi.x && monitorInfo.y == mi.y && monitorInfo.width == mi.width && monitorInfo.height == mi.height){ \
								XMoveResizeWindow(display, container[currentContainer].window, x, y, width, height); \
								XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
								x += cascade.x; \
								y += cascade.y; \
							} \
						} \
					} \
				} \
				XRRFreeMonitors(monitors); \
			} \
		} \
	} \
}









#define MOVE_KEYPRESS \
move:{ \
	if(event.xbutton.x > (int)innerBorder && event.xbutton.y > (int)innerBorder){ \
		XGetWindowAttributes(display, event.xbutton.window, &windowAttributes); \
		if(event.xbutton.x_root < (int)(windowAttributes.x + windowAttributes.width + border - innerBorder) && event.xbutton.y_root < (int)(windowAttributes.y + windowAttributes.height + border - innerBorder)){ \
			motionContainer.window = event.xbutton.window; \
			XGetWindowAttributes(display, event.xbutton.subwindow, &windowAttributes); \
			x = event.xbutton.x - windowAttributes.x + border; \
			y = event.xbutton.y - windowAttributes.y + border; \
			action = MoveAction; \
		}else{ \
			goto setResize; \
		} \
	}else{ \
		setResize:{ \
			motionContainer.window = event.xbutton.window; \
			for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
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
	} \
}









#define MOVETOP_KEYPRESS \
moveTop:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width; \
			const unsigned int height = monitorInfo.height / gridHeight; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define MOVEBOTTOM_KEYPRESS \
moveBottom:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width; \
			const unsigned int height = monitorInfo.height / gridHeight; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y + monitorInfo.height - height - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define MOVELEFT_KEYPRESS \
moveLeft:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width / gridWidth; \
			const unsigned int height = monitorInfo.height; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define MOVERIGHT_KEYPRESS \
moveRight:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width / gridWidth; \
			const unsigned int height = monitorInfo.height; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - border, monitorInfo.y - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define MOVECENTER_KEYPRESS \
moveCenter:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width / gridWidth; \
			const unsigned int height = monitorInfo.height / gridHeight; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - width) / 2 - border, monitorInfo.y + (monitorInfo.height - height) / 2 - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define MOVETOPLEFT_KEYPRESS \
moveTopLeft:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width / gridWidth; \
			const unsigned int height = monitorInfo.height / gridHeight; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define MOVETOPRIGHT_KEYPRESS \
moveTopRight:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width / gridWidth; \
			const unsigned int height = monitorInfo.height / gridHeight; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - border, monitorInfo.y - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define MOVEBOTTOMLEFT_KEYPRESS \
moveBottomLeft:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width / gridWidth; \
			const unsigned int height = monitorInfo.height / gridHeight; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y + monitorInfo.height - height - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define MOVEBOTTOMRIGHT_KEYPRESS \
moveBottomRight:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width / gridWidth; \
			const unsigned int height = monitorInfo.height / gridHeight; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - border, monitorInfo.y + monitorInfo.height - height - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define MOVENEXTPREVIOUSMONITOR_KEYPRESS \
bool next; \
if(c == MoveNextMonitorCommand){ \
	next = 1; \
}else{ \
	next = 0; \
} \
unsigned int ma; \
XRRMonitorInfo *const monitors = XRRGetMonitors(display, XDefaultRootWindow(display), True, (int *)&ma); \
if(monitors){ \
	if(ma == monitorAmount){ \
		for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
			if(container[currentContainer].window == event.xany.window){ \
				XRRMonitorInfo monitorInfo; \
				if(pointerInfo & MoveMonitorPointerInfo){ \
					monitorInfo = getPointerMonitorInfo(); \
				}else{ \
					monitorInfo = getWindowMonitorInfo(event.xany.window); \
				} \
				bool exit = 1; \
				for(unsigned int currentMonitor = 0; currentMonitor < monitorAmount; ++currentMonitor){ \
					if(monitors[currentMonitor].x == monitorInfo.x && monitors[currentMonitor].y == monitorInfo.y && monitors[currentMonitor].width == monitorInfo.width && monitors[currentMonitor].height == monitorInfo.height){ \
						if(next){ \
							if(++currentMonitor < monitorAmount){ \
								monitorInfo = monitors[currentMonitor]; \
								exit = 0; \
							} \
						}else{ \
							if((int)--currentMonitor >= 0){ \
								monitorInfo = monitors[currentMonitor]; \
								exit = 0; \
							} \
						} \
						break; \
					} \
				} \
				if(!exit){ \
					const unsigned int width = monitorInfo.width / gridWidth; \
					const unsigned int height = monitorInfo.height / gridHeight; \
					XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - width) / 2 - border, monitorInfo.y + (monitorInfo.height - height) / 2 - border, width, height); \
					XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
				} \
				break; \
			} \
		} \
	} \
	XRRFreeMonitors(monitors); \
}
#define REMOVEWINDOWFROMGRID_KEYPRESS \
removeWindowFromGrid:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width / gridWidth; \
			const unsigned int height = monitorInfo.height / gridHeight; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - width) / 2 - border, monitorInfo.y + (monitorInfo.height - height) / 2 - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			container[currentContainer].inGrid = 0; \
			break; \
		} \
	} \
}
#define MOVEFIRSTGRIDSLOT_KEYPRESS \
moveFirstGridSlot:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width / gridWidth; \
			const unsigned int height = monitorInfo.height / gridHeight; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			container[currentContainer].inGrid = 1; \
			container[currentContainer].gridX = 0; \
			container[currentContainer].gridY = 0; \
			container[currentContainer].gridWidth = 1; \
			container[currentContainer].gridHeight = 1; \
			break; \
		} \
	} \
}
#define MOVELASTGRIDSLOT_KEYPRESS \
moveLastGridSlot:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			const unsigned int width = monitorInfo.width / gridWidth; \
			const unsigned int height = monitorInfo.height / gridHeight; \
			XMoveResizeWindow(display, event.xany.window, monitorInfo.x + monitorInfo.width - width - border, monitorInfo.y + monitorInfo.height - height - border, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			container[currentContainer].inGrid = 1; \
			container[currentContainer].gridX = gridWidth - 1; \
			container[currentContainer].gridY = gridHeight - 1; \
			container[currentContainer].gridWidth = 1; \
			container[currentContainer].gridHeight = 1; \
			break; \
		} \
	} \
}
#define EXTENDWINDOWUP_KEYPRESS \
extendWindowUp:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			const int x = windowAttributes.x; \
			int y; \
			const unsigned int width = windowAttributes.width; \
			unsigned int height; \
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridY + 1 - container[currentContainer].gridHeight == 0){ \
					break; \
				} \
				++container[currentContainer].gridHeight; \
				getGridSize(getPointerMonitorInfo(), container[currentContainer].gridX, container[currentContainer].gridY + 1 - container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, &height); \
				y = windowAttributes.y - height; \
				height += windowAttributes.height; \
			}else{ \
				y = windowAttributes.y - extendHeight; \
				height = windowAttributes.height + extendHeight; \
			} \
			XMoveResizeWindow(display, event.xany.window, x, y, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define EXTENDWINDOWDOWN_KEYPRESS \
extendWindowDown:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			const unsigned int width = windowAttributes.width; \
			unsigned int height; \
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridY + container[currentContainer].gridHeight - 1 == gridHeight - 1){ \
					break; \
				} \
				++container[currentContainer].gridHeight; \
				getGridSize(getPointerMonitorInfo(), container[currentContainer].gridX, container[currentContainer].gridY + container[currentContainer].gridHeight - 1, gridWidth, gridHeight, NULL, &height); \
				height += windowAttributes.height; \
			}else{ \
				height = windowAttributes.height + extendHeight; \
			} \
			XResizeWindow(display, event.xany.window, width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define EXTENDWINDOWLEFT_KEYPRESS \
extendWindowLeft:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int x; \
			const int y = windowAttributes.y; \
			unsigned int width; \
			const unsigned int height = windowAttributes.height; \
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridX + 1 - container[currentContainer].gridWidth == 0){ \
					break; \
				} \
				++container[currentContainer].gridWidth; \
				getGridSize(getPointerMonitorInfo(), container[currentContainer].gridX + 1 - container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, &width, NULL); \
				x = windowAttributes.x - width; \
				width += windowAttributes.width; \
			}else{ \
				x = windowAttributes.x - extendWidth; \
				width = windowAttributes.width + extendWidth; \
			} \
			XMoveResizeWindow(display, event.xany.window, x, y, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}
#define EXTENDWINDOWRIGHT_KEYPRESS \
extendWindowRight:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			unsigned int width; \
			const unsigned int height = windowAttributes.height; \
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridX + container[currentContainer].gridWidth - 1 == gridWidth - 1){ \
					break; \
				} \
				++container[currentContainer].gridWidth; \
				getGridSize(getPointerMonitorInfo(), container[currentContainer].gridX + container[currentContainer].gridWidth - 1, container[currentContainer].gridY, gridWidth, gridHeight, &width, NULL); \
				width += windowAttributes.width; \
			}else{ \
				width = windowAttributes.width + extendWidth; \
			} \
			XResizeWindow(display, event.xany.window, width, height); \
			XResizeWindow(display, container[currentContainer].subwindow, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}









#define EXTENDWINDOWUPLEFT_KEYPRESS \
extendWindowUpLeft:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XGetWindowAttributes(display, container[currentContainer].window, &windowAttributes); \
			int x; \
			int y; \
			unsigned int width; \
			unsigned int height; \
			if(container[currentContainer].inGrid){ \
				if(container[currentContainer].gridY + 1 - container[currentContainer].gridHeight != 0){ \
					++container[currentContainer].gridHeight; \
					getGridSize(getPointerMonitorInfo(), container[currentContainer].gridX, container[currentContainer].gridY + 1 - container[currentContainer].gridHeight, gridWidth, gridHeight, NULL, &height); \
					y = windowAttributes.y - height; \
					height += windowAttributes.height; \
				}else{ \
					y = windowAttributes.y; \
					height = windowAttributes.height; \
				} \
				if(container[currentContainer].gridX + 1 - container[currentContainer].gridWidth != 0){ \
					++container[currentContainer].gridWidth; \
					getGridSize(getPointerMonitorInfo(), container[currentContainer].gridX + 1 - container[currentContainer].gridWidth, container[currentContainer].gridY, gridWidth, gridHeight, &width, NULL); \
					x = windowAttributes.x - width; \
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
				width = windowAttributes.width + extendWidth; \
				height = windowAttributes.height + extendHeight; \
			} \
			XMoveResizeWindow(display, event.xany.window, x, y, width, height); \
			XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, width - innerBorders, height - innerBorders); \
			break; \
		} \
	} \
}



#define EXTENDWINDOWUPRIGHT_KEYPRESS \
extendWindowUpRight:{ \
	\
}



#define EXTENDWINDOWDOWNLEFT_KEYPRESS \
extendWindowDownLeft:{ \
	\
}



#define EXTENDWINDOWDOWNRIGHT_KEYPRESS \
extendWindowDownRight:{ \
	\
}









#define SHRINKWINDOWUP_KEYPRESS \
shrinkWindowUp:{ \
	\
}



#define SHRINKWINDOWDOWN_KEYPRESS \
shrinkWindowDown:{ \
	\
}



#define SHRINKWINDOWLEFT_KEYPRESS \
shrinkWindowLeft:{ \
	\
}



#define SHRINKWINDOWRIGHT_KEYPRESS \
shrinkWindowRight:{ \
	\
}



#define SHRINKWINDOWUPLEFT_KEYPRESS \
shrinkWindowUpLeft:{ \
	\
}



#define SHRINKWINDOWUPRIGHT_KEYPRESS \
shrinkWindowUpRight:{ \
	\
}



#define SHRINKWINDOWDOWNLEFT_KEYPRESS \
shrinkWindowDownLeft:{ \
	\
}



#define SHRINKWINDOWDOWNRIGHT_KEYPRESS \
shrinkWindowDownRight:{ \
	\
}









#define FULLSCREEN_KEYPRESS \
fullscreen:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
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
				windowAttributes.width = monitorInfo.width / gridWidth; \
				windowAttributes.height = monitorInfo.height / gridHeight; \
				XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - windowAttributes.width) / 2 - border, monitorInfo.y + (monitorInfo.height - windowAttributes.height) / 2 - border, windowAttributes.width, windowAttributes.height); \
				XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, windowAttributes.width - innerBorders, windowAttributes.height - innerBorders); \
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
				XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, monitorInfo.width - innerBorders, monitorInfo.height - innerBorders); \
			} \
			break; \
		} \
	} \
}
#define BIGSCREEN_KEYPRESS \
bigscreen:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
		if(container[currentContainer].window == event.xany.window){ \
			XRRMonitorInfo monitorInfo; \
			if(pointerInfo & MovePointerInfo){ \
				monitorInfo = getPointerMonitorInfo(); \
			}else{ \
				monitorInfo = getWindowMonitorInfo(event.xany.window); \
			} \
			XGetWindowAttributes(display, event.xany.window, &windowAttributes); \
			if(windowAttributes.x == monitorInfo.x - (int)border && windowAttributes.y == monitorInfo.y - (int)border && windowAttributes.width == monitorInfo.width && windowAttributes.height == monitorInfo.height){ \
				windowAttributes.width = monitorInfo.width / gridWidth; \
				windowAttributes.height = monitorInfo.height / gridHeight; \
				XMoveResizeWindow(display, event.xany.window, monitorInfo.x + (monitorInfo.width - windowAttributes.width) / 2 - border, monitorInfo.y + (monitorInfo.height - windowAttributes.height) / 2 - border, windowAttributes.width, windowAttributes.height); \
				XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, windowAttributes.width - innerBorders, windowAttributes.height - innerBorders); \
			}else{ \
				XMoveResizeWindow(display, event.xany.window, monitorInfo.x - border, monitorInfo.y - border, monitorInfo.width, monitorInfo.height); \
				XMoveResizeWindow(display, container[currentContainer].subwindow, innerBorder, innerBorder, monitorInfo.width - innerBorders, monitorInfo.height - innerBorders); \
			} \
			break; \
		} \
	} \
}
#define CLOSE_KEYPRESS \
close:{ \
	for(unsigned int currentContainer = 0; currentContainer < allocatedContainerAmount; ++currentContainer){ \
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
		} \
	} \
}
#endif
