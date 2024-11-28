//*******************************************************************
//
//  File:   BMP280.c
//  Author: VSK
//
//  Created on  23. Jan 2019
//  Modified
//
//*******************************************************************
#pragma warning disable 520 // function never called
#pragma warning disable 373 // implicit signed to unsigned conversion

#include <xc.h>
#include "BMP280.h"

#define CS_SPI_ON()     CS_SPI = 0
#define CS_SPI_OFF()    CS_SPI = 1

//
unsigned char initBMP280(void)
{
    unsigned char id;
    
    //Delay10KTCYx(100);  // power up ...
    __delay_ms(100);
    
    CS_SPI_OFF();
    CS_SPI_TRI = OUTPUT_PIN;
    SCL_TRI = OUTPUT_PIN;
    SDO_TRI = OUTPUT_PIN;
    
    // max. 1MHz SPI freq
    OpenSPI1(SPI_FOSC_16, MODE_00, SMPMID);
    __delay_ms(1);

    
    CS_SPI_ON();
    WriteSPI(REG_RD | WHO_AM_I);
    while (!DataRdySPI());                  //VSK check this !!!
    id = ReadSPI(); // P_MSB
    CS_SPI_OFF();
    
    if (id == WHO_AM_I_ID) return 0;
    else return -1;
}


void readPreassure_LE(unsigned char *pntData)
{
    CS_SPI_ON();
    WriteSPI(REG_RD | PRESS_MSB);
    while (!DataRdySPI());                  //VSK check this !!!
    pntData[1] = ReadSPI(); // P_MSB
    pntData[0] = ReadSPI(); // P_LSB
//    pntData[] = ReadSPI(); // P_XLSB
    CS_SPI_OFF();
}
//
//void readTemp_LE(unsigned char *pntData)
//{
//    CS_SPI_ON();
//    WriteSPI(REG_RD | GYRO_XH);
//    while (!DataRdySPI());                  //VSK check this !!!

//    CS_SPI_OFF();
//}
//
//void readPreassure_BE(unsigned char *pntData)
//{
//    CS_SPI_ON();
//    WriteSPI(REG_RD | ACC_XH);
//    while (!DataRdySPI());                  //VSK check this !!!
//    *pntData++ = ReadSPI(); // P_MSB
//    *pntData++ = ReadSPI(); // P_LSB
//    *pntData++ = ReadSPI(); // P_XLSB
//    CS_SPI_OFF();
//}
//
//void readTemp_LE(unsigned char *pntData)
//{
//    
//}



//void readMPU6000_LE(unsigned char *pntData)
//{
//    CS_SPI_ON();
//    WriteSPI(REG_RD | ACC_XH);
//    while (!DataRdySPI());                  //VSK check this !!!
//    pntData[1] = ReadSPI(); // ACC_XH
//    pntData[0] = ReadSPI(); // ACC_XL
//    pntData[3] = ReadSPI(); // ACC_YH
//    pntData[2] = ReadSPI(); // ACC_YL
//    pntData[5] = ReadSPI(); // ACC_ZH
//    pntData[4] = ReadSPI(); // ACC_ZL
//    CS_SPI_OFF();
//// ?????????????????????????????????? read temperature ??????????????
//    CS_SPI_ON();
//    WriteSPI(REG_RD | GYRO_XH);
//    while (!DataRdySPI());                  //VSK check this !!!
//    pntData[7] = ReadSPI(); // GYRO_XH
//    pntData[6] = ReadSPI(); // GYRO_XL
//    pntData[9] = ReadSPI(); // GYRO_YH
//    pntData[8] = ReadSPI(); // GYRO_YL
//    pntData[11] = ReadSPI(); // GYRO_ZH
//    pntData[10] = ReadSPI(); // GYRO_ZL
//    CS_SPI_OFF();
//}
// void readMPU6000_BE(unsigned char *pntData)
//{
//    CS_SPI_ON();
//    WriteSPI(REG_RD | ACC_XH);
//    while (!DataRdySPI());                  //VSK check this !!!
//    *pntData++ = ReadSPI(); // ACC_XH
//    *pntData++ = ReadSPI(); // ACC_XL
//    *pntData++ = ReadSPI(); // ACC_YH
//    *pntData++ = ReadSPI(); // ACC_YL
//    *pntData++ = ReadSPI(); // ACC_ZH
//    *pntData++ = ReadSPI(); // ACC_ZL
//    CS_SPI_OFF();
//// ?????????????????????????????????? read temperature ??????????????
//    CS_SPI_ON();
//    WriteSPI(REG_RD | GYRO_XH);
//    while (!DataRdySPI());                  //VSK check this !!!
//    *pntData++ = ReadSPI(); // GYRO_XH
//    *pntData++ = ReadSPI(); // GYRO_XL
//    *pntData++ = ReadSPI(); // GYRO_YH
//    *pntData++ = ReadSPI(); // GYRO_YL
//    *pntData++ = ReadSPI(); // GYRO_ZH
//    *pntData++ = ReadSPI(); // GYRO_ZL
//    CS_SPI_OFF();
//}
