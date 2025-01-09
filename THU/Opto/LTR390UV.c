//*******************************************************************
//
//  File:           LTR390UV.c
//  Author:         VSK
//
//  Created on      26. Nov 2019
//  Modified        26. Nov. 2019
//
//*******************************************************************

#include "LTR390UV.h"

#include <xc.h>
#include <stdint.h>
#include "PLIB/plib.h"

void initLTR390(ltr390_reg_t mode)
{
    OpenI2C1(MASTER, SLEW_ON);
    IdleI2C1();                             // 
    StartI2C1();                            // send start condition
    while(SSP1CON2bits.SEN){;}              // 
    WriteI2C1(LTR390_WR);                    // addressing 
    while(SSP1CON2bits.ACKSTAT){;}          // ACK-bit
    WriteI2C1(LTR390_MAIN_CTRL);             // command
    while(SSP1CON2bits.ACKSTAT){;}          // ACK-bit
    WriteI2C1(mode);                        // mode
    while(SSP1CON2bits.ACKSTAT){;}          // ACK-bit
    StopI2C1();
}

void rdLTR390(uint8_t *pntData)
{
    IdleI2C1();                             // 
    StartI2C1();                            // send start condition
    while(SSP1CON2bits.SEN){;}              // 
    WriteI2C1(LTR390_RD);                    // addressing 
    while(SSP1CON2bits.ACKSTAT){;}          // ACK from sensor
    pntData[0] = ReadI2C1();                // LSB
    NotAckI2C1();                           // NACK master
    StopI2C1();
}

uint8_t findLTR390(void)
{
    uint8_t PID;
    
    OpenI2C1(MASTER, SLEW_ON);
    IdleI2C1();                             // 
    StartI2C1();                            // send start condition
    while(SSP1CON2bits.SEN){;}              // 
    WriteI2C1(LTR390_WR);                   // addressing 
    while(SSP1CON2bits.ACKSTAT){;}          // ACK from sensor
    WriteI2C1(LTR390_PART_ID);              // 
    while(SSP1CON2bits.ACKSTAT){;}          // ACK from sensor
    RestartI2C1();
    WriteI2C1(LTR390_RD);
    while(SSP1CON2bits.ACKSTAT){;}          // ACK from sensor
    PID = ReadI2C1();                       //
    NotAckI2C1();                           // NACK master
    StopI2C1();
    if(PID == LTT390_PID)return 1;
      else return 0;
}
