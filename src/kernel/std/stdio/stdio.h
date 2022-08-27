#pragma once
#include "../stdint.h"
#include "IO.h"

void putc(char c);
void puts(const char *str);
void printf(const char *fmt, ...);

void SetCursorPosition(uint16_t position);

uint16_t PositionFromCoords(uint16_t x, uint16_t y);