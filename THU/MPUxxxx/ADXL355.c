
#include "ADXL355.h"
#include "Globals.h"
#include "stdbool.h"

TYPE_I2CSPD_INTP_RANGE i2cSpeed_intP_range = RANGE_2G;

unsigned char ADXL355_rdReg(TYPE_A355_REG regAddr)
{
    //function for reading a byte from a register
    unsigned char retVal = 0;

    A355_ENABLE;
    WriteADXL355((regAddr << 1) | READ_FLAG);
    retVal = ReadADXL355();
    A355_DISABLE;
    return retVal;
}

void ADXL355_wrReg(TYPE_A355_REG regAddr, unsigned char value)
{
    //function for writing a byte to a register
    A355_ENABLE;
    WriteADXL355(regAddr << 1);
    WriteADXL355(value);
    A355_DISABLE;
}

unsigned char ADXL355_init(void)
{
    if(ADXL355_rdReg(ADXL355_PARTID ) != PARTID_DEFAULT_VAL) return 0;

    // inits for accel and gyro sensors ----------------------------------------

    ADXL355_wrReg(A355_RESET, RESET_CODE);
    __delay_ms(1);  // ???

    ADXL355_wrReg(A355_RANGE, i2cSpeed_intP_range);

    //A355_writeByte(A355_PWR_MGMT_1, A355_CLKSEL_BEST);

    return 1;
}

//------------------------------------------------------------------------------
unsigned char ADXL355_setAccelFullScale(TYPE_I2CSPD_INTP_RANGE newAccelFullScale)
{
    if((newAccelFullScale < RANGE_2G)|| (newAccelFullScale > RANGE_8G)){
            return false;
    }
    i2cSpeed_intP_range = (i2cSpeed_intP_range & 0xF8) | newAccelFullScale; 
    ADXL355_wrReg(A355_RANGE, newAccelFullScale << 3);

    if(ADXL355_getAccelFullScale() != i2cSpeed_intP_range)
        return  false;
    else
        return true;
}


//------------------------------------------------------------------------------
unsigned char ADXL355_getAccelFullScale(void)
{
    i2cSpeed_intP_range = ADXL355_rdReg(A355_RANGE);
    return ((i2cSpeed_intP_range & 0x7) << 1);
}


//void A355_setSleep()
//{
//    // Muss vor dem Eintritt des µC in den Sleep mode eingestellt werden.
//    // Der motion interrupt des MPU kann den µC dann wieder aufwecken
//    // Nach dem Aufwecken des µC muss der motion interrupt des MPU wieder ausgeschaltet werden
//    // vgl. MPU datasheet page 33
//
//    // power down mag
//    A355_writeByte(A355_I2C_SLV0_ADDR, A355_MAG_ADDRESS);
//    __delay_ms(1);
//    // slave 0 register to write = A355_MAG_CNTL2
//    A355_writeByte(A355_I2C_SLV0_REG, A355_MAG_CNTL);
//    __delay_ms(1);
//    // data to write = 0x00
//    A355_writeByte(A355_I2C_SLV0_DO, 0x00);
//    __delay_ms(1);
//    // enable slave 0
//    A355_writeByte(A355_I2C_SLV0_CTRL, 0x81);
//    __delay_ms(10);
//
//
//    // PWR_MGMT_1 0x6B
//    // cycle = 0, sleep = 0, CLKSEL = internal 8MHz oscillator
//    A355_writeByte(A355_PWR_MGMT_1, A355_CLKSEL_20MHZ);
//
//    // PWR_MGMT_2 0x6C
//    // accel running DIS_XA, DIS_YA, DIS_ZA = 0, gyro not running DIS_XG, DIS_YG, DIS_ZG = 1
//    A355_writeByte(A355_PWR_MGMT_2, A355_DISABLE_XYZG);
//
//    // ACCEL_CONFIG_2 0x1D
//    // accel LPF to 420 Hz bandwidth
//    // ACCEL_FCHOISE_B = 1, A_DLPFCFG = 1
//    A355_writeByte(A355_ACCEL_CONFIG2, A355_A_DLPF_CFG_460HZ);
//
//    // INT_ENABLE 0x38
//    //register address for INT_ENABLE
//    // data to register address: enable motion interrupt
//    A355_writeByte(A355_INT_ENABLE, A355_WOM_EN);
//
//    // MOT_DETECT_CTRL 0x69
//    // ACCEL_INTEL_EN = 1, ACCELINTEL_MODE = 1
//    A355_writeByte(A355_MOT_DETECT_CTRL, A355_ACCEL_INTEL_EN | A355_ACCEL_INTEL_MODE);
//
//    // WOM_THR 0x1F
//    //register address for MOT_THR
//    // data to register address: motion threshold, LSB = 4mg
//    // 0x7D = 125*0.004g = 0.5g
//    A355_writeByte(A355_WOM_THR, 0x7D);
//
//    // LP_ACCEL_ODR 0x1E
//    // Lposc_clksel = 0.24Hz to 500Hz frequency of wakeup = 0,98Hz
//    A355_writeByte(A355_LP_ACCEL_ODR, 0x02);
//
//    // PWR_MGMT_1 0x6B
//    //register address for PWR_MGMT_1
//    // data to register address: set cycle mode, cycle = 1 on bit 5 = 0x20
//    A355_writeByte(A355_PWR_MGMT_1, 0x20);
//}
//
//void A355_shutDown()
//{
////    #ifdef FOSC_PLL
////    OpenSPI1(SPI_FOSC_64, MODE_00, SMPMID);
////    #else
////    OpenSPI1(SPI_FOSC_16, MODE_00, SMPMID);
////    #endif
//
//    // power down mag
//    A355_writeByte(A355_I2C_SLV0_ADDR, A355_MAG_ADDRESS);
//    __delay_ms(1);
//    // slave 0 register to write = A355_MAG_CNTL2
//    A355_writeByte(A355_I2C_SLV0_REG, A355_MAG_CNTL);
//    __delay_ms(1);
//    // data to write = 0x00
//    A355_writeByte(A355_I2C_SLV0_DO, 0x00);
//    __delay_ms(1);
//    // enable slave 0
//    A355_writeByte(A355_I2C_SLV0_CTRL, 0x81);
//    __delay_ms(10);
//
//    //sleep mode 0x40
//    A355_writeByte(A355_PWR_MGMT_1, 0x40);
//    __delay_ms(10);
//}


void ADXL355_readTempData(unsigned char * buffer)
{
    A355_ENABLE;
    WriteADXL355(A355_TEMP2 << 1| READ_FLAG);
    buffer[1] = ReadADXL355();
    buffer[0] = ReadADXL355();
    A355_DISABLE;
}


typedef union{
    unsigned short long value;
    struct{
        unsigned char LB;
        unsigned char HB;
        unsigned char UB;
    };
}ADXL_VALUE_T;

void ADXL355_readAccelData(unsigned char * buffer)
{
    ADXL_VALUE_T value;
    
    A355_ENABLE;
    WriteADXL355(A355_XDATA3 << 1 | READ_FLAG);
    value.UB = ReadADXL355();  // ACC_XU
    value.HB = ReadADXL355();  // ACC_XH
    value.LB = ReadADXL355();  // ACC_XL
    value.value = value.value >> 4;
    *buffer++ = value.LB; *buffer++ = value.HB;
//    *buffer++ = value.HB; *buffer++ = value.UB;
    
    value.UB = ReadADXL355();  // ACC_YU
    value.HB = ReadADXL355();  // ACC_YH
    value.LB = ReadADXL355();  // ACC_YL
    value.value = value.value >> 4;
    *buffer++ = value.LB; *buffer++ = value.HB;
//    *buffer++ = value.HB; *buffer++ = value.UB;

    value.UB = ReadADXL355();  // ACC_ZU
    value.HB = ReadADXL355();  // ACC_ZH
    value.LB = ReadADXL355();  // ACC_ZL
    value.value = value.value >> 4;
    *buffer++ = value.LB; *buffer++ = value.HB;
//    *buffer++ = value.HB; *buffer++ = value.UB;
    
    A355_DISABLE;
}
//
//void A355_getAccelOffsetValues(int *valOffset)
//{
//    A355_ENABLE;
//    // 15 bit (!) offset values, 8 bits in high byte, 7 bits in low byte
//    WriteMPU(A355_XA_OFFSET_H | READ_FLAG);
//    valOffset[0] = (int)ReadMPU() << 8;
//    valOffset[0] = valOffset[0] | ReadMPU();
//    A355_DISABLE;
//
//    A355_ENABLE;
//    WriteMPU(A355_YA_OFFSET_H | READ_FLAG);
//    valOffset[1] = (int)ReadMPU() << 8;
//    valOffset[1] = valOffset[1] | ReadMPU();
//    A355_DISABLE;
//
//    A355_ENABLE;
//    WriteMPU(A355_ZA_OFFSET_H | READ_FLAG);
//    valOffset[2] = (int)ReadMPU() << 8;
//    valOffset[2] = valOffset[2] | ReadMPU();
//    A355_DISABLE;
//}
//
//void A355_setAccelOffsetValues(int *valOffset)
//{
//    // preserve bit 0 of factory value (for temperature compensation)
//    valOffset[0] = valOffset[0] & ~0x01;
//    valOffset[1] = valOffset[1] & ~0x01;
//    valOffset[2] = valOffset[2] & ~0x01;
//
//    // 15 bit (!) offset values, 8 bits in high byte, 7 bits in low byte
//    A355_ENABLE;
//    WriteMPU(A355_XA_OFFSET_H | 0);
//    WriteMPU((unsigned char)(valOffset[0] >> 8) & 0xFF);
//    A355_DISABLE;
//
//    A355_ENABLE;
//    WriteMPU(A355_YA_OFFSET_H | 0);
//    WriteMPU((unsigned char)(valOffset[1] >> 8) & 0xFF);
//    WriteMPU((unsigned char)(valOffset[1] & 0xFF));
//    A355_DISABLE;
//
//    A355_ENABLE;
//    WriteMPU(A355_ZA_OFFSET_H | 0);
//    WriteMPU((unsigned char)(valOffset[2] >> 8) & 0xFF);
//    WriteMPU((unsigned char)(valOffset[2] & 0xFF));
//    A355_DISABLE;
//
//    __delay_ms(1);
//}
