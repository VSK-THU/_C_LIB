/*!
 *  @LTR390UV.h
 *
 * 	I2C Driver for LTR390 UV and light sensor
 *
 * 	This is a library for the Adafruit LTR390 breakout:
 * 	http://www.adafruit.com/
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *
 *	BSD license (see license.txt)
 */

#ifndef LTR390UV_H
#define LTR390UV_H

#include <xc.h>
#include <stdint.h>
#include "PLIB/plib.h"

//#define LTR390_I2CADDR_DEFAULT 0x53 ///< I2C address
#define LTR390_WR     0xA6
#define LTR390_RD     0xA7

typedef enum {
  LTR390_MAIN_CTRL      = 0x00, ///< Main control register
  LTR390_MEAS_RATE      = 0x04, ///< Resolution and data rate
  LTR390_GAIN           = 0x05, ///< ALS and UVS gain range
  LTR390_PART_ID        = 0x06, ///< Part id/revision register
  LTR390_MAIN_STATUS    = 0x07, ///< Main status register
  LTR390_ALSDATA        = 0x0D, ///< ALS data lowest byte
  LTR390_UVSDATA        = 0x10, ///< UVS data lowest byte
  LTR390_INT_CFG        = 0x19, ///< Interrupt configuration
  LTR390_INT_PST        = 0x1A, ///< Interrupt persistance config
  LTR390_THRESH_UP      = 0x21, ///< Upper threshold, low byte
  LTR390_THRESH_LOW     = 0x24  ///< Lower threshold, low byte
} ltr390_reg_t;

#define LTT390_PID  0xB2

/*!    @brief  Whether we are measuring ambient or UV light  */
typedef enum {
  LTR390_MODE_ALS,
  LTR390_MODE_UVS,
} ltr390_mode_t;

/*!    @brief  Sensor gain for UV or ALS  */
typedef enum {
  LTR390_GAIN_1 = 0,
  LTR390_GAIN_3,
  LTR390_GAIN_6,
  LTR390_GAIN_9,
  LTR390_GAIN_18,
} ltr390_gain_t;

/*!    @brief Measurement resolution (higher res means slower reads!)  */
typedef enum {
  LTR390_RESOLUTION_20BIT,
  LTR390_RESOLUTION_19BIT,
  LTR390_RESOLUTION_18BIT,
  LTR390_RESOLUTION_17BIT,
  LTR390_RESOLUTION_16BIT,
  LTR390_RESOLUTION_13BIT,
} ltr390_resolution_t;


extern void initLTR390(ltr390_reg_t mode);
extern void wrLTR390(ltr390_reg_t cmd);
extern void rdLTR390(uint8_t *pntData);
extern uint8_t findLTR390(void);

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            LTR390 UV Sensor
 */

/*
class Adafruit_LTR390 {
public:
  Adafruit_LTR390();
  bool begin(TwoWire *theWire = &Wire);
  bool reset(void);

  void enable(bool en);
  bool enabled(void);

  void setMode(ltr390_mode_t mode);
  ltr390_mode_t getMode(void);

  void setGain(ltr390_gain_t gain);
  ltr390_gain_t getGain(void);

  void setResolution(ltr390_resolution_t res);
  ltr390_resolution_t getResolution(void);

  void setThresholds(uint32_t lower, uint32_t higher);

  void configInterrupt(bool enable, ltr390_mode_t source,
                       uint8_t persistance = 0);

  bool newDataAvailable(void);
  uint32_t readUVS(void);
  uint32_t readALS(void);

private:
  Adafruit_I2CRegister *StatusReg;
  Adafruit_I2CRegisterBits *DataReadyBit;

  Adafruit_I2CDevice *i2c_dev;
};

 */
#endif
