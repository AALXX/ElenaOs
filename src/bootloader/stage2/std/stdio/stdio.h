#pragma once
#include "../stdint.h"
#include "text/TextColorModeCodes.h"
#include "IO.h"

////////////////////////////////////////////
//              Cursor functions          //
////////////////////////////////////////////
void SetCursorPosition(uint16_t position);
uint16_t PositionFromCoords(uint16_t x, uint16_t y);

////////////////////////////////////////////
//           Print Text functions         //
////////////////////////////////////////////
// void putc(char c, uint8_t color = BACKGROUND_BLACK | FOREGROUND_WHITE);
// void puts(const char *str, uint8_t color = BACKGROUND_BLACK | FOREGROUND_WHITE);

