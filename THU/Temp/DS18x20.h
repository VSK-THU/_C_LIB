//*******************************************************************
//
//  File:   DS18x20.h
//  Author: VSK
//
//  Created on  09. May 2019
//              Credits to Nicolas Pannwitz
//              https://pic-projekte.de/blog/ds18s20/
//  Modified
//
//*******************************************************************
#ifndef DS18X20_H
#define	DS18X20_H

#include "global_def.h"     // data pin localisation
#include <stdint.h>

typedef enum {
    CONV_T          = 0x44,
    RD_SCRATCH      = 0xBE,
    WR_SCRATCH      = 0x4E,
    COPY_SCRATCH    = 0x48,
    RECALL_EE       = 0xB8,
    RD_PWR_SUPLY    = 0xB4,
    SKIP_ROM        = 0xCC,
    FIND_ROM        = 0xF0,
    RD_ROM          = 0x33,
    MATCH_ROM       = 0x55,
    FIND_ALRM       = 0xEC
}DS18x20_Command_t;

typedef struct{
    uint8_t  t_dec;
    int8_t t_int;
}ds18x20_t;

extern ds18x20_t ds18x20;
extern uint8_t ds18x20_data[9];

//#define ds18x20_skip_rom()  ds18x20_wr(SKIP_ROM)
//#define ds18x20_convert_T()  ds18x20_wr(CONV_T)

uint8_t ds18x20_res(void);
void ds18x20_wr(uint8_t value);     // one byte
uint8_t ds18x20_rd(void);           // one byte
int8_t ds18x20_rdTemp(void);
//void ds18x20_(void);

#endif //DS18X20_H
