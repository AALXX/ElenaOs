#include "std/stdint.h"
#include "std/stdio/stdio.h"

void __attribute((cdecl)) _start(uint16_t bootDrive)
{
    SetCursorPosition(PositionFromCoords(0, 0));
    puts("CUM and \n\rpiss");
    return;
}