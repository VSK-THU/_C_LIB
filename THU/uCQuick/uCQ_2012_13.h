//##############################################################################
//    	filename:     uCQ	hardware v12 modified to v13.h
//
//     	meaningful pin-names (signals) and macro definitions
//      for demo projects
//
//##############################################################################
//
//      Author:            	V.SchK
//      Company:        	HS-Ulm
//
//	Revision:        	1.0
// 	Date:         		July. 2012
//     	Assembled using         C18 3.41+ / XC8 1.01
//
//   	todo	- add comments ;-)
//             	-
//
//##############################################################################/*

#ifndef UCQ_V2012_13_H
#define	UCQ_V2012_13_H

#ifdef __XC8
    #include <xc.h>
//#elif defined __SDCC
//  #include <pic18fregs.h>
#else
    #include <p18cxxx.h>
#endif

//----------------------------------------------------------internal clock freq.
#if defined(__18F25K22) | defined(__18F24K22)
    #define IRCF_16MHZ  0b111
    #define IRCF_8MHZ   0b110
    #define IRCF_4MHZ   0b101
    #define IRCF_2MHZ   0b100
    #define IRCF_1MHZ   0b011
    #define IRCF_500KHZ 0b010
    #define IRCF_250KHZ 0b001
    #define IRCF_31KHZ  0b000
#endif

// ---------------------------------------------------------------pin directions
#define INPUT_PIN           1
#define OUTPUT_PIN          0
#define INPUT_REG           0xFF
#define OUTPUT_REG          0x00

// -----------------------------------------------------------------push buttons
#define BTN_L               PORTBbits.RB3               // left button
#define BTN_L_TRI           TRISBbits.TRISB3
#define BTN_M               PORTBbits.RB4
#define BTN_M_TRI           TRISBbits.TRISB4
#define BTN_R               PORTBbits.RB5               // right button
#define BTN_R_TRI           TRISBbits.TRISB5

#define BTN_ACTIVATED       0
#define mGET_BTN_L()        (BTN_L == BTN_ACTIVATED)
#define mGET_BTN_M()        (BTN_M == BTN_ACTIVATED)
#define mGET_BTN_R()        (BTN_R == BTN_ACTIVATED)

#define WAIT_BTN_CAP()      Nop();Nop();Nop();Nop();   // (fuer FOSC == 4MHz)

// -------------------------------------------------------------------------LEDs
#define LED_1               LATBbits.LATB2
#define LED_1_TRI           TRISBbits.TRISB2
#define LED_2               LATBbits.LATB3
#define LED_2_TRI           TRISBbits.TRISB3
#define LED_3               LATBbits.LATB4
#define LED_3_TRI           TRISBbits.TRISB4
#define LED_4               LATBbits.LATB5
#define LED_4_TRI           TRISBbits.TRISB5

#define LED_ON              0
#define LED_OFF             1
#define mSET_LED_1_ON()     LED_1 = LED_ON
#define mSET_LED_1_OFF()    LED_1 = LED_OFF
#define mTOG_LED_1()        LED_1 = !LED_1
#define mSET_LED_2_ON()     LED_2 = LED_ON
#define mSET_LED_2_OFF()    LED_2 = LED_OFF
#define mTOG_LED_2()        LED_2 = !LED_2
#define mSET_LED_3_ON()     LED_3 = LED_ON
#define mSET_LED_3_OFF()    LED_3 = LED_OFF
#define mTOG_LED_3()        LED_3 = !LED_3
#define mSET_LED_4_ON()     LED_4 = LED_ON
#define mSET_LED_4_OFF()    LED_4 = LED_OFF
#define mTOG_LED_4()        LED_4 = !LED_4

// ---------------------------------------------------------------digital inputs
#define TTL_IN          PORTAbits.RA0
#define TTL_IN_TRI      TRISAbits.TRISA0
#define ST_IN           PORTCbits.RC3
#define ST_IN_TRI       TRISCbits.TRISC3

// ---------------------------------------------------------------rotary encoder
#define ENC_BTN         PORTBbits.RB1
//PORTBbits.RB2
#define ENC_BTN_TRI     TRISBbits.TRISB1
//TRISBbits.TRISB2
#define mGET_ENC_BTN()  (ENC_BTN == BTN_ACTIVATED)

#define ENC_INT         PORTBbits.INT0
#define ENC_INT_TRI     TRISBbits.TRISB0
#define ENC_DIR         PORTAbits.RA2
#define ENC_DIR_TRI     TRISAbits.TRISA2
//#define ENC_DIR         PORTEbits.RE3
//#define ENC_DIR_TRI     TRISEbits.TRISE3

#define ENC_DIR_UP      0
#define ENC_DIR_DOWN    1

#define ENC_IR          INTCONbits.INT0IE && INTCONbits.INT0IF
#define mENC_IR_EN()    INTCON2bits.INTEDG0 = 1; INTCONbits.INT0IE = 1
#define mENC_IR_DIS()   INTCONbits.INT0IE = 0
#define mENC_IR_CLR()   INTCONbits.INT0IF = 0

// ----------------------------------------------------------analog input (poti)
#define POTI_TRI        LATAbits.LATA0
#define ADC_POTI        ADC_CH0
#define ADC_IR          PIE1bits.ADIE && PIR1bits.ADIF
#define mADC_IR_EN()    PIE1bits.ADIE = 1
#define mADC_IR_DIS()   PIE1bits.ADIE = 0
#define mADC_IR_CLR()   PIR1bits.ADIF = 0

// ----------------------------------------------------------------------speaker
#define SPEAKER         LATCbits.LATC2
#define SPEAKER_TRI     TRISCbits.TRISC2
#define mTOG_SPEAKER()  SPEAKER = !SPEAKER

// ------------------------------------------------------------------------RS232
#define TX_PIN          LATCbits.LATC6
#define RX_PIN          PORTCbits.RC7
#define TX_TRI          TRISCbits.TRISC6
#define RX_TRI          TRISCbits.TRISC7
#define TX_FREE         PIR1bits.TX1IF

// ------------------------------------------------------------------lcd display
#define	LCD_RW_PIN      LATCbits.LATC0
#define	LCD_RW_TRI      TRISCbits.TRISC0

// --------------------------------------------------------------Zeitmessung CCP
#define CAPTR_IR        PIE1bits.CCP1IE && PIR1bits.CCP1IF
#define mCAPTR_IR_EN()  PIE1bits.CCP1IE = 1
#define mCAPTR_IR_DIS() PIE1bits.CCP1IE = 0
#define mCAPTR_IR_CLR() PIR1bits.CCP1IF = 0

// ----------------------------------------------------------------------Uhr CCP
#define SEC_IR          PIE2bits.CCP2IE && PIR2bits.CCP2IF
#define mSEC_IR_EN()    PIE2bits.CCP2IE = 1
#define mSEC_IR_DIS()   PIE2bits.CCP2IE = 0
#define mSEC_IR_CLR()   PIR2bits.CCP2IF = 0

// ------------------------------------------------------------debug help signal
#define dbgSIGNAL       SPEAKER
#define dbgSIGNAL_TRI   SPEAKER_TRI
#define dbgPULSE()      mTOG_SPEAKER();mTOG_SPEAKER()

#ifdef __XC8
    #define mENCBTN_DEBUG_STOP()
  #elif defined __DEBUG
    #define mENCBTN_DEBUG_STOP()    if(mGET_ENC_BTN()){_asm TRAP _endasm}
  #else
    #define mENCBTN_DEBUG_STOP()
#endif

#endif	/* UCQ_V2012_13_H */

