#pragma once

#include "constants.h"
#include "libraries.h"

void console_cursor(int x, int y);
void cursor_visible(bool show, short size);
void full_screen();
void console_header(const char* string);
void console_text_background_color();

void start();