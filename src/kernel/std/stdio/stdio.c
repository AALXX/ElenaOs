#include "stdio.h"

const unsigned SCREEN_WIDTH = 80;
const unsigned SCREEN_HEIGHT = 25;

uint16_t *g_ScreenBuffer = (uint16_t *)0xb8000;
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

uint16_t PositionFromCoords(int16_t x, uint16_t y)
{
    return y * SCREEN_WIDTH + x;
}

void putchr(int x, int y, char c)
{
    g_ScreenBuffer[2 * (y * SCREEN_WIDTH + x)] = c;
}

void putc(char c)
{
    switch (c)
    {
    case '\n':
        g_ScreenX = 0;
        g_ScreenY++;
        break;

    case '\t':
        for (int i = 0; i < 4 - (g_ScreenX % 4); i++)
            putc(' ');
        break;

    case '\r':
        g_ScreenX = 0;
        break;

    default:
        putchr(g_ScreenX, g_ScreenY, c);
        g_ScreenX++;
        break;
    }

    if (g_ScreenX >= SCREEN_WIDTH)
    {
        g_ScreenY++;
        g_ScreenX = 0;
    }
}

void puts(const char *str)
{
    while (*str)
    {
        putc(*str);
        str++;
    }
}