#include <stdint.h>
#include "stdio.h"

extern "C" void __attribute__((cdecl)) start(uint16_t bootDrive)
{
    printf("CUM");
    // puts("test");
}