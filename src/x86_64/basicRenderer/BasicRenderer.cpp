#include "../../kernel/interfaces/BasicRenderer/BasicRenderer.h"

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char *buffer = (struct Char *)0xb8000;
size_t col = 0;
size_t row = 0;


struct Char
{
    uint8_t character;
    uint8_t color;
};

BasicRenderer::BasicRenderer(uint8_t foreground, uint8_t background)
{
    Color = foreground + (background << 4);
}

void BasicRenderer::Print(const char *string)
{
    uint16_t i = CursorPosition;

    for (i = 0; 1; i++) {
        char character = (uint8_t) string[i];

        if (character == '\0') {
            return;
        }

        PutChar(character);
    }
}

void BasicRenderer::PutChar(char character)
{
    if (character == '\n')
    {
        print_newline();
        return;
    }

    if (col >= NUM_COLS)
    {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char){
        character : (uint8_t)character,
        color : Color,
    };

    col++;
    SetCursorPosition(col);
}

void BasicRenderer::SetCursorPosition(uint16_t Pos)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(Pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((Pos >> 8) & 0xFF));

    if (Pos > 2000)
        Pos = 0;
    if (Pos < 0)
        Pos = 2000;

    CursorPosition = Pos;
}

void BasicRenderer::clear_row(size_t row)
{
    struct Char empty = (struct Char){
        character : ' ',
        color : Color,
    };

    for (size_t col = 0; col < NUM_COLS; col++)
    {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void BasicRenderer::ClearScreen()
{
    for (size_t i = 0; i < NUM_ROWS; i++)
    {
        clear_row(i);
    }
    SetCursorPosition(0);
}

void BasicRenderer::print_newline()
{
    col = 0;

    if (row < NUM_ROWS - 1)
    {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++)
    {
        for (size_t col = 0; col < NUM_COLS; col++)
        {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_ROWS - 1);
}
