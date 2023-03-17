#include <stdint.h>

/**
 * kernel entry point
 * @param bootDrive
 */
void __attribute__((section(".entry"))) start(uint16_t bootDrive)
{

end:
    for (;;)
        ;
}