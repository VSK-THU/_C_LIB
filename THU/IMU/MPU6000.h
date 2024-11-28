//*******************************************************************
//
//  File:   MPU6000.h
//  Author: stuber
//
//  Created on 04. Nov 2013
//  Modified    Oct. 2014 VSK
//              Oct. 2015 VSK
//
//*******************************************************************

#ifndef MPU_6000_H
#define	MPU_6000_H

#include "global_def.h"

//## Pins define them in "global_def.h" ----------------------------------------
//#define CS_SPI          LATCbits.LATC2    // -> global_def.h
//...

typedef enum {
    REG_WR          = 0x00,
    SELF_TEST_X     = 0x0D,
    SELF_TEST_Y,
    SELF_TEST_Z,
    SELF_TEST_A,
    SMPLRT_DIV       = 0x19,
    CONFIG,
    CFG_GYRO,
    CFG_ACC,
    MOT_THR         = 0x1F,
    INT_PIN_CFG     = 0x37,
    INT_EN          = 0x38,
    ACC_XH          = 0x3B,
    ACC_XL,
    ACC_YH,
    ACC_YL,
    ACC_ZH,
    ACC_ZL,
    TEMP_H          = 0x41,
    TEMP_L,
    GYRO_XH         = 0x43,
    GYRO_XL,
    GYRO_YH,
    GYRO_YL,
    GYRO_ZH,
    GYRO_ZL         = 0x48,
    USER_CTRL       = 0x6A,
    PWR_MGMT_1,
    PWR_MGMT_2,
    FIFO_CNT_H      = 0x72,
    FIFO_CNT_L,
    FIFO_RW,
    WHO_AM_I,
    REG_RD          = 0x80
}TYPE_MPU6000_REG;

typedef enum {  // 4.2 Register 25 ? Sample Rate Divider
    SMPLRT_1000     = 0x00,
    SMPLRT_500,
    SMPLRT_333,
    SMPLRT_250,
    SMPLRT_200,
    SMPLRT_166      = 0x05,
    SMPLRT_125      = 0x07,
    SMPLRT_100      = 0x09,
    SMPLRT_66       = 0x0E,
    SMPLRT_50       = 0x13,
    SMPLRT_25       = 39,
    SMPLRT_10       = 99
}TYPE_SMPLRT_DIV;

typedef enum {  // 4.3 Register 26 ? Configuration
    LP_260_HZ   = 0x00, // DLPF_CFG[2:0]
    LP_184_HZ,
    LP_94_HZ,
    LP_44_HZ,
    LP_21_HZ,
    LP_10_HZ,
    LP_5_HZ,
    LP_RESERVED // 7
    // EXT_FSYNC_SET[2:0] -->> NYI
}TYPE_CONFIG;

typedef enum {  // 4.4 Register 27 ? Gyroscope Configuration
    GYROpm250       = 0x00,     // range [°/sec] -> bit3..bit4
    GYROpm500       = 0x08,
    GYROpm1000      = 0x10,
    GYROpm2000      = 0x18,
    GYRO_ST_Z       = 0x20,     // bit5 self test
    GYRO_ST_Y       = 0x40,     // bit6
    GYRO_ST_X       = 0x80      // bit7
}TYPE_CFG_GYRO;

typedef enum {  // 4.5 Register 28 ? Accelerometer Configuration
    ACCpm2G         = 0x00,     // range [+-xG]-> bit3..bit4
    ACCpm4G         = 0x08,
    ACCpm8G         = 0x10,
    ACCpm16G        = 0x18,
    ACC_ST_Z        = 0x20,     // bit5 self test
    ACC_ST_Y        = 0x40,     // bit6
    ACC_ST_X        = 0x80      // bit7
}TYPE_CFG_ACC;

typedef enum {  // 4.15 Register 55 ? INT Pin / Bypass Enable Configuration
    FSYNC_INT_LEVEL_LO  = 0x00, // (not hi level)
    I2C_BYPASS_EN       = 0x02,
    FSYNC_INT_EN        = 0x04,
    FSYNC_INT_LEVEL_HI  = 0x08,
    INT_ALL_RD_CLR      = 0x10, // all read clears (or INT_STATUS only)
    LATCH_INT_EN        = 0x20, // latched (or 50us pulse)
    INT_OPEN_DRAIN      = 0x40, // open drain
    INT_LEVEL_LOW       = 0x80  // active high/low
}TYPE_INT_PIN_CFG;

typedef enum {  // 4.16 Register 56 ? Interrupt Enable
    NO_IR_EN            = 0x00,
    DATA_READY_EN       = 0x01, // all sensor data updated interrupt enable
    I2C_MST_INT_EN      = 0x80, // I2C master interrupt sources enable
    FIFO_OFLOW_EN       = 0x10, // FIFO buffer overflow interrupt enable
    MOT_EN              = 0x40  // motion detection interrupt enable
}TYPE_INT_EN;


//typedef enum {
//
//}TYPE_PWR_MGMT_1;
//
//typedef enum {
//
//}TYPE_PWR_MGMT_2;

#define SPI_WR_ADDR(a,d)    WriteSPI1(REG_WR | a); WriteSPI1(d)
#define SPI_RD_ADDR(a)      WriteSPI1(REG_RD | a)
#define SPI_WR_NEXT(d)      WriteSPI1( d )
#define SPI_RD_NEXT()       ReadSPI1()




//extern unsigned char data[20];
//extern unsigned char MPU_ADDR;

extern void initMPU6000(TYPE_CFG_ACC cfgAcc, TYPE_CFG_GYRO cfgGyro,
                        TYPE_SMPLRT_DIV smplRT, TYPE_CONFIG lowPass);
extern void enMPU6000ir(TYPE_INT_EN inEn, TYPE_INT_PIN_CFG pinCfg);

extern void readMPU6000_LE(unsigned char *pntData); // little/big endian version
extern void readMPU6000_BE(unsigned char *pntData);
extern void readACC_LE(unsigned char *pntData);
extern void readACC_BE(unsigned char *pntData);
extern void readACC_X(unsigned char *pntData );
extern void readACC_Y(unsigned char *pntData );
extern void readACC_Z(unsigned char *pntData );
extern void readGYRO_LE(unsigned char *pntData);
//extern char InitMPU6000_I2C(void);
//extern void ReadMPU6000Data_I2C(unsigned char* buffer);

#endif	/* MPU_6000_H */
