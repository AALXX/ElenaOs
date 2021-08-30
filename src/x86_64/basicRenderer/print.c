#include "../../kernel/interfaces/print.h"

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;


void SetCursorPosition(uint16_t Pos){
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

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char volatile * buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
}

void print_newline() {
    col = 0;

    if (row < NUM_ROWS - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_ROWS - 1);
}

void print_char(char character) {
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col >= NUM_COLS) {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        color: color,
    };      

    col++;
    SetCursorPosition(col);

}

void print_string(char* str) {
    uint16_t i = CursorPosition;

    for (i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        print_char(character);
    }
}

void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}
