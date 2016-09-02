//PROJECT DETAILS
/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0001 */
/* @NAME : KEYS_driver.h */
/* @PURPOSE :  */
/* @CREATED_BY : R. CHISIU */
/* @CREATION_DATE : July 05 2016 */
/* @CREATION_SITE : NTT Data Romania */
/* @LANGUAGE : 'C' */
/* @MPROC_TYPE : Independent */
/* ******************************************************************* */
/* @REVISION_BY :  */
/* @SW_RELEASE :  */
/* @CHANGES :  */
/* @CREATION_DATE :  */
/* @CREATION_SITE :  */
/***************************** (C) Copyright NTT Data Romania *******************/ 
#ifndef KEYS_DRIVER_H
#define	KEYS_DRIVER_H

//INCLUDES
#include "p24FJ128GB106.h"
#include "FreeRTOSConfig.h"

//MACROS
//PIN SETUP
#define B1_INT_PIN        TRISEbits.TRISE0
#define B2_INT_PIN        TRISEbits.TRISE1

//PULL-UP RESISTOR
#define B1_PULL_UP        CNPU4bits.CN58PUE
#define B2_PULL_UP        CNPU4bits.CN59PUE

//CHANGE NOTIFICATION ENABLE
#define B1_CN_EN          CNEN4bits.CN58IE
#define B2_CN_EN          CNEN4bits.CN59IE

//FLAGS - CHANGE NOTIFICATION
#define FLAG_CN          IFS1bits.CNIF

// INTERRUPT CONTROL - CHANGE NOTIFICATION - EN
#define INTERR_CONTROL_CN IEC1bits.CNIE

//PIN STATE
#define B1_S              PORTEbits.RE0
#define B2_S              LPORT3bits.RE1
//DECLARATION

struct KEYS_AMessege
{   
	unsigned long B_ID; 
	unsigned long B1_DOWN_TIME;
    unsigned long B1_UP_TIME;
	unsigned long B2_DOWN_TIME;
	unsigned long B2_UP_TIME;  //portTickType
};


//FUNCTIONS PROTOTIPES
void INT_KEYS_DRIVER();
/*END OF KEYS_DRIVER_H */ 
#endif

