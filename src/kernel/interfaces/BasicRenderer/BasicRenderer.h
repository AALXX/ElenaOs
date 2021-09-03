#pragma once
#include "../IO.h"
#include "./cstr.h"

#include <stdint.h>
#include <stddef.h>

class BasicRenderer
{
public:
    BasicRenderer(uint8_t foreground = PRINT_COLOR_WHITE, uint8_t background = PRINT_COLOR_BLACK);
    
    uint16_t CursorPosition;
    uint8_t Color;
    void ClearScreen();
    void Print(const char *string);
    void PutChar(char character);
    void SetCursorPosition(uint16_t Pos);

    enum
    {
        PRINT_COLOR_BLACK = 0,
        PRINT_COLOR_BLUE = 1,
        PRINT_COLOR_GREEN = 2,
        PRINT_COLOR_CYAN = 3,
        PRINT_COLOR_RED = 4,
        PRINT_COLOR_MAGENTA = 5,
        PRINT_COLOR_BROWN = 6,
        PRINT_COLOR_LIGHT_GRAY = 7,
        PRINT_COLOR_DARK_GRAY = 8,
        PRINT_COLOR_LIGHT_BLUE = 9,
        PRINT_COLOR_LIGHT_GREEN = 10,
        PRINT_COLOR_LIGHT_CYAN = 11,
        PRINT_COLOR_LIGHT_RED = 12,
        PRINT_COLOR_PINK = 13,
        PRINT_COLOR_YELLOW = 14,
        PRINT_COLOR_WHITE = 15,
    };

private:
    void print_newline();
    void clear_row(size_t row);
};
