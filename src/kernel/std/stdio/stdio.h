#pragma once
#include "../stdint.h"
#include "IO.h"

void putchr(int x, int y, char c);
void putc(char c);
void puts(const char *str);

void SetCursorPosition(uint16_t position);

uint16_t PositionFromCoords(int16_t x, uint16_t y);