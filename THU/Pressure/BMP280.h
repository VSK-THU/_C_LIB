//*******************************************************************
//
//  File:   BMP280.h
//  Author: VSK
//
//  Created on  23. Jan 2019
//  Modified
//
//*******************************************************************


#ifndef BMP_280_H
#define	BMP_280_H

#include "global_def.h"

//## Pins - define them in "global_def.h" --------------------------------------
//#define CS_SPI          LATCbits.LATC2    // -> global_def.h
//...

#define WHO_AM_I_ID     0x58    // ID value read from device
#define RESET_ID        0xB6    // value written to reset device
typedef enum {
    WHO_AM_I    = 0xD0,
    RESET       = 0xE0,
    BMP_STATUS  = 0xF3,
    CTRL_MEAS,
    CONFIG,
    PRESS_MSB   = 0xF7,
    PRESS_LSB,
//...            
            
    REG_RD      = 0x80
}TYPE_BMP280_REG;

typedef enum {  // 4.3.3 Register 0xF3 status
    IM_UPDATE   = 0x01,
    MEASURING   = 0x08
}TYPE_STATUS;

typedef enum {  // 4.3.4 Register 0xF4 ctrl_meas
    MODE_SLEEP  = 0x00,
//...
    MODE_NORMAL = 0x03,
    OSRS_0      = 0x00,
    OSRS_P_1    = 0x04,
    OSRS_P_2    = 0x08,
    OSRS_P_4    = 0x0C,
    OSRS_P_8    = 0x10,
    OSRS_P_16   = 0x1C,
    OSRS_T_S    = 0x00,
//...
    OSRS_T_16   = 0xE0
}TYPE_CTRL_MEAS_REG;

//typedef enum {  // 4.3.5 Register 0xF5 config
//    SPI3W
//    IIR_
//    T_SB
//}TYPE_CONFIG_REG;

//#define SPI_WR_ADDR(a,d)    WriteSPI1(REG_WR | a); WriteSPI1(d)
#define SPI_RD_ADDR(a)      WriteSPI1(REG_RD | a)
#define SPI_WR_NEXT(d)      WriteSPI1( d )
#define SPI_RD_NEXT()       ReadSPI1()


unsigned char initBMP280(void);


#endif	/* BMP_280_H */
