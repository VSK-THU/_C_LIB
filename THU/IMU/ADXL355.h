/*
 * File:   ADXL355.h
 * Author: VSK
 *
 * Created on 17. Juli 2017
 */



#ifndef ADXL355_H
#define ADXL355_H



#define READ_FLAG   1
#define WRITE_FLAG  0

/*************************
    *  MPU Register map
    **************************/

    typedef enum {   //3  Registermap for GYRO and ACCEL
        A355_DEVID_AD       = 0x00,
        A355_DEVID_MST      = 0x01,
        ADXL355_PARTID      = 0x02,
        A355_REV_ID         = 0x03, 
        A355_STATUS         = 0x04,
        A355_FIFO_ENTRIES   = 0x05,
        A355_TEMP2          = 0x06,
        A355_TEMP1          = 0x07,
        A355_XDATA3         = 0x08,
        A355_XDATA2,
        A355_XDATA1,
        A355_YDATA3,
        A355_YDATA2,
        A355_YDATA1,
        A355_ZDATA3,
        A355_ZDATA2,
        A355_ZDATA1,
        A355_FIFO_DATA      = 0x11,
        A355_OFFSET_X_H     = 0x1E,
        A355_OFFSET_X_L,
        A355_OFFSET_Y_H,
        A355_OFFSET_Y_L,
        A355_OFFSET_Z_H,
        A355_OFFSET_Z_L,
        A355_ACT_EN         = 0x24,
        A355_ACT_TRESH_H    = 0x25,
        A355_ACT_TRESH_L    = 0x26,
        A355_ACT_COUNT      = 0x27,
        A355_ODR_FILTER     = 0x28,
        A355_FIFO_SAMPLES   = 0x29,
        A355_INT_MAP        = 0x2A,
        A355_SYNC           = 0x2B,
        A355_RANGE          = 0x2C,
        A355_POWER_CTRL     = 0x2D,
        A355_SELF_TEST      = 0x2E,
        A355_RESET          = 0x2F
    }TYPE_A355_REG;

    /*************************
    *  REGISTER VALUES
    **************************/
    #define DEVID_AD_DEFAULT_VAL    0xAD
    #define DEVID_MST_DEFAULT_VAL   0x1D
    #define PARTID_DEFAULT_VAL      0xED

    typedef enum {
        NVM_BUSY    = 0x40,
        ACTIVITY    = 0x08,
        FIO_OVR     = 0x04,
        FIFO_FULL   = 0x02,
        DATA_RDY    = 0x01        
    }TYPE_STATUS_BITS;              // 0x04

    typedef enum {
        ACT_EN_Z    = 0x04,
        ACT_EN_Y    = 0x02,
        ACT_EN_X    = 0x01        
    }TYPE_ACT_EN_BITS;              // 0x24
    
    typedef enum {
        HPF_CORNER_ODR_420k = 0x60,
        HPF_CORNER_ODR_105k = 0x50,
        HPF_CORNER_ODR_25k9 = 0x40,
        HPF_CORNER_ODR_6k43 = 0x30,
        HPF_CORNER_ODR_1k61 = 0x20,
        HPF_CORNER_ODR_k405 = 0x10,
        HPF_CORNER_OFF      = 0x00,
        ODR_4LPF_3_91       = 0x0A,
        ODR_4LPF_7_81       = 0x09,
        ODR_4LPF_15_6       = 0x08,
        ODR_4LPF_31_3       = 0x07,
        ODR_4LPF_62_5       = 0x06,
        ODR_4LPF_125        = 0x05,
        ODR_4LPF_250        = 0x04,
        ODR_4LPF_500        = 0x03,
        ODR_4LPF_1000       = 0x02,
        ODR_4LPF_2000       = 0x01,
        ODR_4LPF_4000       = 0x00,
    }TYPE_ODR_FILTER_BITS;          //0x28

    typedef enum {
        ACT_EN2     = 0x80,
        OVR_EN2     = 0x40,
        FULL_EN2    = 0x20,
        RDY_EN2     = 0x10,
        ACT_EN1     = 0x08,
        OVR_EN1     = 0x04,
        FULL_EN1    = 0x02,
        RDY_EN1     = 0x01
    }TYPE_INT_MAP_BITS;             // 0x2A

    typedef enum {
        EXT_CLK     = 0x04
//                ,
//                    = 0x03,
//                    = 0x02,
//                    = 0x01
    }TYPE_SYNC_BITS;                // 0x2B

    typedef enum {
        I2C_HS          = 0x08,
        INT_POL_1       = 0x40,
        RANGE_8G        = 0x03,
        RANGE_4G        = 0x02,
        RANGE_2G        = 0x01
    }TYPE_I2CSPD_INTP_RANGE;        // 0x2C

    typedef enum {
        DATA_RDY_OFF    = 0x03,
        TEMP_OFF        = 0x02,
        STANDBY         = 0x01,
        ONLINE          = 0x00
    }TYPE_POWER;                    // 0x2D
  
    typedef enum {
        SELFTEST_FORCE  = 0x02,
        SELFTEST_MODE   = 0x01
    }TYPE_SETF_TEST;                // 0x2D
    
    typedef enum {
        RESET_CODE      = 0x52
    }TYPE_RESET;                    // 0x2F


    /*************************
    *  MPU prototypes
    **************************/
    extern unsigned char ADXL355_rdReg(TYPE_A355_REG regAddr);
    extern void ADXL355_wrReg(TYPE_A355_REG regAddr, unsigned char value);
    extern unsigned char ADXL355_init(void);
    extern unsigned char ADXL355_getAccelFullScale(void);
    extern void ADXL355_readTempData(unsigned char * buffer);
    extern void ADXL355_readAccelData(unsigned char * buffer);
    
#endif        /* ADXL355_H */
