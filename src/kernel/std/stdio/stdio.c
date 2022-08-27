#include "stdio.h"
#define VGA_MEMORY (uint8_t *)0xb8000

const unsigned SCREEN_WIDTH = 80;
const unsigned SCREEN_HEIGHT = 25;

uint8_t *g_ScreenBuffer = (uint8_t *)0xb8000;
uint16_t CursorPosition;
int g_ScreenX = 0, g_ScreenY = 0;

// position is not with and height is an index from 0 to end of video memory
void SetCursorPosition(uint16_t position)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)(position >> 8) & 0xFF);

    if (CursorPosition > 2000)
        CursorPosition = 2000;

    if (CursorPosition > 2000)
        CursorPosition = 0;

    CursorPosition = position;
}

uint16_t PositionFromCoords(uint16_t x, uint16_t y)
{
    return y * SCREEN_WIDTH + x;
}

void putc(char c)
{
    uint16_t index = CursorPosition;

    switch (c)
    {
    case '\n':
        index += SCREEN_WIDTH;
        break;

    case '\r':
        index -= index % SCREEN_WIDTH;
        break;

    default:
        g_ScreenBuffer[CursorPosition * 2] = c;
        index++;
        break;
    }

    SetCursorPosition(index);
}

void puts(const char *str)
{
    while (*str)
    {
        putc(*str);
        str++;
    }
}