//*******************************************************************
//
//  File:   DS18x20.c
//  Author: VSK
//
//  Created on  09. May 2019
//  Modified
//
//*******************************************************************
#pragma warning disable 520 // function never called
//#pragma warning disable 373 // implicit signed to unsigned conversion

#include "DS18x20.h"

ds18x20_t ds18x20;
uint8_t ds18x20_data[9];

uint8_t ds18x20_res(void)
{
    uint8_t rec;
    
    DS18X20_OUT = 0;    // set the (I)O to low level
    DS18X20_DIR = 0;    // config as output (-> low)
    __delay_us(480);    // reset pulse >=480 us
    DS18X20_DIR = 1;    // config as input (high-z -> pull up)
    __delay_us(80);
    rec = ~DS18X20_IN;  // read the level (if low, slave available)
    __delay_us(400);    // wait for end of slot
    return (rec);
}

void ds18x20_wr(uint8_t value)
{
    for(uint8_t i = 0; i < 8; i++){
        DS18X20_DIR = 0;
        __delay_us(1);
        if(value & 0x01){ DS18X20_DIR = 1; }
        __delay_us(60);
        DS18X20_DIR = 1;
        value = value >> 1;
    }
}

uint8_t ds18x20_rd(void)
{
    uint8_t value = 0;
    
    for(uint8_t i = 0; i < 8; i++){
        DS18X20_DIR = 0;
        __delay_us(1);
        DS18X20_DIR = 1;
        __delay_us(9);
        value |= DS18X20_IN << i;
        __delay_us(51);             // 60+1 us minimum
    }
    return value;
}

int8_t ds18x20_rdTemp(void)
{
        for(uint8_t i = 0; i < 9; i++){
            ds18x20_data[i] = ds18x20_rd();
        }
        ds18x20.t_int = *(int16_t *)&ds18x20_data[0] >> 4;
        ds18x20.t_dec = ((ds18x20_data[0] & 0x0F)*10) >> 4;
        if(ds18x20.t_int < 0)
            ds18x20.t_dec = 9 - ds18x20.t_dec;
        return ds18x20.t_int;
}
