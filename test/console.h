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

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

void SetConsoleColor(enum ConsoleColor bg_color, enum ConsoleColor fg_color, enum ConsoleAttribute attribute) {
  WORD attributes = 0;

  switch (attribute) {
  case ConsoleAttributeNormal:
  case ConsoleAttributeItalic:
  case ConsoleAttributeUnderline:
      attributes = 0;
    break;
  case ConsoleAttributeBold:
      attributes = FOREGROUND_INTENSITY;
    break;
  default:
    break;
  }

  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(attributes | fg_color | (bg_color << 4)));
}

void ResetConsoleColor() {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void ConsoleSetCursorPos(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct vec2 ConsoleGetCursorPos() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  struct vec2 pos;
  pos.x = csbi.dwCursorPosition.X;
  pos.y = csbi.dwCursorPosition.Y;
  return pos;
}

struct vec2 ConsoleGetWidthHeight() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  struct vec2 size;
  size.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  size.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  return size;
}

#endif

#if defined(__linux__) || defined(__APPLE__)
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

void SetConsoleColor(enum ConsoleColor bg, enum ConsoleColor fg, enum ConsoleAttribute attribute) {
  int attrCode = 0;

  switch (attribute) {
  case Normal:
    attrCode = 0;
    break;
  case Bold:
    attrCode = 1;
    break;
  case Italic:
    attrCode = 3;
    break;
  case Underline:
    attrCode = 4;
    break;
  }

  printf("\033[%d;%dm", attrCode, fg + bg * 10);
}

void ResetConsoleColor() {
  printf("\033[0m");
}

void SetCursorPos(int x, int y) {
  printf("\033[%d;%dH", y + 1, x + 1);
}

struct CursorPos GetCursorPos() {
  struct CursorPos pos;
  printf("\033[6n");
  fflush(stdout);
  scanf("\033[%d;%dR", &pos.y, &pos.x);
  return pos;
}
struct vec2 ConsoleGetWidthHeight() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  struct vec2 size;
  size.x = w.ws_col;
  size.y = w.ws_row;
  return size;
}

#endif
