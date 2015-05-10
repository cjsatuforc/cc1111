#include <stdint.h>
#include "delay.h"

void delay(uint16_t msec)
{
    while (msec--) {
        uint16_t n = 825;  // determined empirically
        while (n--)
            nop();
    }
}