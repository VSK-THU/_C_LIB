//*******************************************************************
//
//  File:   APA102.c
//  Author: VSK
//
//  Created on  23. Julye 2024
//  Modified
//
//*******************************************************************


#include "APA102.h"

void initAPA102(void)
{
//    SCL_TRI = OUTPUT_PIN;
//    SCL_ANS = DIGITAL_PIN;
//    SDO_TRI = OUTPUT_PIN;
    
    OpenSPI1(SPI_FOSC_4, MODE_11, SMPMID);
}

void APA102_wr(uint8_t * ptrData, uint16_t size_of_LEDdata)
{
//    uint8_t global, colorB, colorG, colorR;

    WriteSPI1(0);WriteSPI1(0);WriteSPI1(0);WriteSPI1(0);    // Start Frame
    for(uint16_t i=0; i<(size_of_LEDdata); i++){
        WriteSPI1(*ptrData++);
    } 
    WriteSPI1(0xFF);WriteSPI1(0xFF);WriteSPI1(0xFF);WriteSPI1(0xFF);    // Stop
}
