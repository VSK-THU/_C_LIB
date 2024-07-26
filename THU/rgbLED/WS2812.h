//*******************************************************************
//
//  File:   WS2812.h
//  Author: VSK
//
//  Created on  06. June2019
//
//  Modified
//
//*******************************************************************
#ifndef WS2812_H
#define	WS2812_H

#include "global_def.h"     // data pin localisation
#include <stdint.h>

void WS2812_wr(uint8_t * ptrColors, uint16_t size_of_LEDdata);

#endif //WS2812_H
