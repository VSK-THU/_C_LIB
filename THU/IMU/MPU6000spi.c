//*******************************************************************
//
//  File:           MPU6000spi.c
//  Author:         stuber, VSK
//
//  Created on      04. Nov 2013
//  Modified        Nov. 2014 VSK
//                  Oct. 2015 VSK
//
//*******************************************************************
#pragma warning disable  520    // function never called
#pragma warning disable  373    // implicit signed to unsigned conversion
#pragma warning disable 1498    // pointer may have no targets

#include "MPU6000.h"

#define CS_SPI_ON()     CS_SPI = 0
#define CS_SPI_OFF()    CS_SPI = 1


void initMPU6000(TYPE_CFG_ACC cfgAcc, TYPE_CFG_GYRO cfgGyro,
                TYPE_SMPLRT_DIV smplRt, TYPE_CONFIG lowPass)
{
    if((lowPass == LP_RESERVED)||(lowPass == LP_260_HZ)){
        smplRt = (smplRt + 1)*8  -1;
    }                               //TODO sample rate <-> lowpass filter

    __delay_ms(100);  // power up ...

    CS_SPI_OFF();
    CS_SPI_TRI = OUTPUT_PIN;
    SCL_TRI = OUTPUT_PIN;
    SCL_ANS = DIGITAL_PIN;
    SDO_TRI = OUTPUT_PIN;
    SDI_ANS = DIGITAL_PIN;
    SDI_TRI = INPUT_PIN;

    // max. 1MHz SPI freq
    OpenSPI1(SPI_FOSC_16, MODE_00, SMPMID);
    __delay_ms(1);

    // disable I2C -mode  -----------------------------------------------
    // I2C_IF_DIS = 1 -> SPI-Mode enabled
    CS_SPI_ON();
    WriteSPI1(REG_WR | USER_CTRL);
    WriteSPI1(0x10);    //??????????????????????????????????????????????????????
    CS_SPI_OFF();

    __delay_ms(1);

    // Raus aus dem sleep mode --------------------------------------------
    // SLEEP = 0 -> raus aus dem sleep mode
    CS_SPI_ON();
    WriteSPI1(REG_WR | PWR_MGMT_1);
    WriteSPI1(0x00);    //??????????????????????????????????????????????????????
    CS_SPI_OFF();

    __delay_ms(1);

    CS_SPI_ON();
    WriteSPI1(REG_WR | CONFIG);
    WriteSPI1(lowPass);
    CS_SPI_OFF();

    __delay_ms(1);

    CS_SPI_ON();
    WriteSPI1(REG_WR | SMPLRT_DIV);
    WriteSPI1(smplRt);
    CS_SPI_OFF();

    __delay_ms(1);
    CS_SPI_ON();
    WriteSPI1(REG_WR| CFG_GYRO);
    WriteSPI1(cfgGyro);
    CS_SPI_OFF();

    __delay_ms(1);

    CS_SPI_ON();
    WriteSPI1(REG_WR| CFG_ACC);
    WriteSPI1(cfgAcc);
    CS_SPI_OFF();

}
void enMPU6000ir(TYPE_INT_EN inEn, TYPE_INT_PIN_CFG pinCfg)
{
    CS_SPI_ON();
    WriteSPI1(REG_WR | INT_PIN_CFG);
    WriteSPI1(pinCfg);
    CS_SPI_OFF();

    __delay_ms(1);

    CS_SPI_ON();
    WriteSPI1(REG_WR | INT_EN);
    WriteSPI1(inEn);
    CS_SPI_OFF();
}

void readACC_LE(unsigned char *pntData)
{
    CS_SPI_ON();
    WriteSPI(REG_RD | ACC_XH);
    while (!DataRdySPI());                  //VSK check this !!!
    pntData[1] = ReadSPI(); // ACC_XH
    pntData[0] = ReadSPI(); // ACC_XL
    pntData[3] = ReadSPI(); // ACC_YH
    pntData[2] = ReadSPI(); // ACC_YL
    pntData[5] = ReadSPI(); // ACC_ZH
    pntData[4] = ReadSPI(); // ACC_ZL
    CS_SPI_OFF();
}

void readGYRO_LE(unsigned char *pntData)
{
    CS_SPI_ON();
    WriteSPI(REG_RD | GYRO_XH);
    while (!DataRdySPI());                  //VSK check this !!!
    pntData[1] = ReadSPI(); // ACC_XH
    pntData[0] = ReadSPI(); // ACC_XL
    pntData[3] = ReadSPI(); // ACC_YH
    pntData[2] = ReadSPI(); // ACC_YL
    pntData[5] = ReadSPI(); // ACC_ZH
    pntData[4] = ReadSPI(); // ACC_ZL
    CS_SPI_OFF();
}

void readACC_BE(unsigned char *pntData)
{
    CS_SPI_ON();
    WriteSPI(REG_RD | ACC_XH);
    while (!DataRdySPI());                  //VSK check this !!!
    *pntData++ = ReadSPI(); // ACC_XH
    *pntData++ = ReadSPI(); // ACC_XL
    *pntData++ = ReadSPI(); // ACC_YH
    *pntData++ = ReadSPI(); // ACC_YL
    *pntData++ = ReadSPI(); // ACC_ZH
    *pntData++ = ReadSPI(); // ACC_ZL
    CS_SPI_OFF();
}

void readACC_X(unsigned char *pntData )
{
    CS_SPI_ON();
    WriteSPI(REG_RD | ACC_XH);
    while (!DataRdySPI());                  //VSK check this !!!
    pntData[1] = ReadSPI(); // ACC_XH
    pntData[0] = ReadSPI(); // ACC_XL
    CS_SPI_OFF();
}

void readACC_Y(unsigned char *pntData )
{
    CS_SPI_ON();
    WriteSPI(REG_RD | ACC_YH);
    while (!DataRdySPI());                  //VSK check this !!!
    pntData[1] = ReadSPI(); // ACC_YH
    pntData[0] = ReadSPI(); // ACC_YL
    CS_SPI_OFF();
}

void readACC_Z(unsigned char *pntData )
{
    CS_SPI_ON();
    WriteSPI(REG_RD | ACC_ZH);
    while (!DataRdySPI());                  //VSK check this !!!
    pntData[1] = ReadSPI(); // ACC_ZH
    pntData[0] = ReadSPI(); // ACC_ZL
    CS_SPI_OFF();
}

void readMPU6000_LE(unsigned char *pntData)
{
    CS_SPI_ON();
    WriteSPI(REG_RD | ACC_XH);
    while (!DataRdySPI());                  //VSK check this !!!
    pntData[1] = ReadSPI(); // ACC_XH
    pntData[0] = ReadSPI(); // ACC_XL
    pntData[3] = ReadSPI(); // ACC_YH
    pntData[2] = ReadSPI(); // ACC_YL
    pntData[5] = ReadSPI(); // ACC_ZH
    pntData[4] = ReadSPI(); // ACC_ZL
    CS_SPI_OFF();
// ?????????????????????????????????? read temperature ??????????????
    CS_SPI_ON();
    WriteSPI(REG_RD | GYRO_XH);
    while (!DataRdySPI());                  //VSK check this !!!
    pntData[7] = ReadSPI(); // GYRO_XH
    pntData[6] = ReadSPI(); // GYRO_XL
    pntData[9] = ReadSPI(); // GYRO_YH
    pntData[8] = ReadSPI(); // GYRO_YL
    pntData[11] = ReadSPI(); // GYRO_ZH
    pntData[10] = ReadSPI(); // GYRO_ZL
    CS_SPI_OFF();
}
 void readMPU6000_BE(unsigned char *pntData)
{
    CS_SPI_ON();
    WriteSPI(REG_RD | ACC_XH);
    while (!DataRdySPI());                  //VSK check this !!!
    *pntData++ = ReadSPI(); // ACC_XH
    *pntData++ = ReadSPI(); // ACC_XL
    *pntData++ = ReadSPI(); // ACC_YH
    *pntData++ = ReadSPI(); // ACC_YL
    *pntData++ = ReadSPI(); // ACC_ZH
    *pntData++ = ReadSPI(); // ACC_ZL
    CS_SPI_OFF();
// ?????????????????????????????????? read temperature ??????????????
    CS_SPI_ON();
    WriteSPI(REG_RD | GYRO_XH);
    while (!DataRdySPI());                  //VSK check this !!!
    *pntData++ = ReadSPI(); // GYRO_XH
    *pntData++ = ReadSPI(); // GYRO_XL
    *pntData++ = ReadSPI(); // GYRO_YH
    *pntData++ = ReadSPI(); // GYRO_YL
    *pntData++ = ReadSPI(); // GYRO_ZH
    *pntData++ = ReadSPI(); // GYRO_ZL
    CS_SPI_OFF();
}
