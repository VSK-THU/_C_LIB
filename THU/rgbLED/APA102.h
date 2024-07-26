//*******************************************************************
//
//  File:   APA102.h
//  Author: VSK
//
//  Created on  23. July 2024
//
//  Modified
//
//*******************************************************************
#ifndef APA102_H
#define	APA102_H

#include "global_def.h"     // data pin localisation
//#include <stdint.h>

void initAPA102(void);
void APA102_wr(uint8_t * ptrData, uint16_t size_of_LEDdata);

#endif //APA102_H
