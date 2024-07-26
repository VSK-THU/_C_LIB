//*******************************************************************
//
//  File:   WS2812.c
//  Author: VSK
//
//  Created on  06. June 2019
//  Modified
//
//*******************************************************************


#include "WS2812.h"

void WS2812_wr(uint8_t * ptrColors, uint16_t size_of_LEDdata)
{
    uint8_t color;

    for(uint16_t i=0; i<(size_of_LEDdata); i++){
        color = *ptrColors++;
/* bit 7 */
        if(!(color & 0x80)){        // (bit == 0)
            WS2812_DAT = 1; D0H();
            WS2812_DAT = 0; D0L();
        } else {                    // (bit == 1)
            WS2812_DAT = 1; D1H();
            WS2812_DAT = 0; D1L();
        }
/* 6 */ if(!(color & 0x40)){ WS2812_DAT = 1; D0H(); WS2812_DAT = 0; D0L(); }
          else { WS2812_DAT = 1; D1H(); WS2812_DAT = 0; D1L(); }
/* 5 */ if(!(color & 0x20)){ WS2812_DAT = 1; D0H(); WS2812_DAT = 0; D0L(); }
          else { WS2812_DAT = 1; D1H(); WS2812_DAT = 0; D1L(); }
/* 4 */ if(!(color & 0x10)){ WS2812_DAT = 1; D0H(); WS2812_DAT = 0; D0L(); }
          else { WS2812_DAT = 1; D1H(); WS2812_DAT = 0; D1L(); }
/* 3 */ if(!(color & 0x08)){ WS2812_DAT = 1; D0H(); WS2812_DAT = 0; D0L(); }
          else { WS2812_DAT = 1; D1H(); WS2812_DAT = 0; D1L(); }
/* 2 */ if(!(color & 0x04)){ WS2812_DAT = 1; D0H(); WS2812_DAT = 0; D0L(); }
          else { WS2812_DAT = 1; D1H(); WS2812_DAT = 0; D1L(); }
/* 1 */ if(!(color & 0x02)){ WS2812_DAT = 1; D0H(); WS2812_DAT = 0; D0L(); }
          else { WS2812_DAT = 1; D1H(); WS2812_DAT = 0; D1L(); }
/* 0 */ if(!(color & 0x01)){ WS2812_DAT = 1; D0H(); WS2812_DAT = 0; D0L(); }
          else { WS2812_DAT = 1; D1H(); WS2812_DAT = 0; D1L(); }
    }
}
