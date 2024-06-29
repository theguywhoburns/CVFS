#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

enum ConsoleColor {
	ConsoleColorBlack,
	ConsoleColorBlue,
	ConsoleColorGreen,
	ConsoleColorCyan,
	ConsoleColorRed,
	ConsoleColorPurple,
	ConsoleColorBrown,
	ConsoleColorLightGray,
	ConsoleColorDarkGray,
	ConsoleColorLightBlue,
	ConsoleColorLightGreen,
	ConsoleColorLightCyan,
	ConsoleColorLightRed,
	ConsoleColorLightPurple,
	ConsoleColorYellow,
	ConsoleColorWhite
};

enum AsciiAttribute {
	ConsoleAttributeNormal,
	ConsoleAttributeBold,
	ConsoleAttributeItalic,
	ConsoleAttributeUnderline
};

void SetConsoleColor(enum ConsoleColor bg_color, enum ConsoleColor fg_color, enum AsciiAttribute attribute);
void ResetConsoleColor();

struct vec2 {
	int x;
	int y;
};

void ConsoleSetCursorPos(int x, int y);
struct vec2 ConsoleGetCursorPos();
struct vec2 ConsoleGetWidthHeight();
