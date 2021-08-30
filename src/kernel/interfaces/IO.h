#pragma once
#include <stdint.h>
#include <stddef.h>

enum
{
    PIC1_COMMAND = 0x20,
    PIC1_DATA = 0x21,
    PIC2_COMMAND = 0xA0,
    PIC2_DATA = 0xA1,
    ICW1_INIT = 0x10,
    ICW1_ICW4 = 0x01,
    ICW4_8086 = 0x01,
};

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void RemapPic();