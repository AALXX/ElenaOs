#include "IO.h"

uint8_t inb(uint16_t port)
{
    uint8_t returnVal;
    asm volatile("inb %1, %0"
                 : "=a"(returnVal)
                 : "Nd"(port));
    return returnVal;
}

void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(val), "Nd"(port));
}