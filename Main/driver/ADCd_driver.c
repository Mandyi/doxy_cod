/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME : ADCd_driver.c */
/* @PURPOSE :  */
/* @CREATED_BY : C. Barbat */
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


/*_____INCLUDE-FILES__________________________________________________________*/

#include "FreeRTOS.h"
#include "task.h" 
#include "queue.h"
#include "semphr.h"


/*_____LOCAL-DEFINE___________________________________________________________*/
/*_____LOCAL-TYPES____________________________________________________________*/
/*_____GLOBAL-DATA____________________________________________________________*/
/*_____LOCAL-DATA_____________________________________________________________*/
/*_____LOCAL-MACROS___________________________________________________________*/
/*_____LOCAL-FUNCTIONS-PROTOTYPES_____________________________________________*/
/*_____GLOBAL-FUNCTIONS_______________________________________________________*/


#include "ADCd_driver.h"
xQueueHandle ADC_Que, ADCBattery_Que;
void ADCd_Init(void)
{

AD1PCFG = ADC_PINS;   // Configure pins as analog inputs ADC1 si ADC2
AD1CSSL = ADC_CHANNELS;   // Include  channels in scan ADC01 si adc02
AD1CON1 = ADC_SCAN; 	// SSRC bit = 111 implies internal
					// counter ends sampling
					// and starts converting.
AD1CHS = CH_SELECT;	
AD1CON3 = SAMPLE_TIME;
AD1CON2 = INT_SET;  
AD1CON1bits.ADON = ON; // turn ADC ON

ADC_Que = xQueueCreate(10,sizeof (unsigned int ));
ADCBattery_Que = xQueueCreate(10,sizeof (unsigned int));
}

void ADC_Start(void)
{
// start conversion

AD1CON1bits.SAMP = ON;				// start sampling
IFS0bits.AD1IF = OFF; 				// clear ADC interrupt flag
AD1CON1bits.ASAM = ON; 				// auto start sampling start
}

void __attribute__ ((__interrupt__)) _ADC1Interrupt(void)
{
IFS0bits.AD1IF = OFF;
/*
AD1CON1bits.ASAM = OFF; 				//then stop sample/convert
*/
storeADC();
} 	

void storeADC(void)
{
unsigned int ADCValue=0,ADCBatteryValue=0;
int *ADC16Ptr;
ADC16Ptr = &ADC1BUF0; // initialize ADC1BUF pointer

//read ADC buffer
ADCValue = *ADC16Ptr++;
ADCBatteryValue = *ADC16Ptr;

//send coada
if( ADC_Que != NULL )  //daca coada exista
{
	xQueueSend(ADC_Que,&ADCValue,500); 
}
else 
{
//dosomething
//Create Queue
}

if( ADCBattery_Que != NULL )
{
	xQueueSend(ADCBattery_Que,&ADCBatteryValue,500);
}
else 
{
//dosomething
//Create Queue
}
}


void vApplicationTickHook( void )   // set the tickHook bit in frtoscfg
{
static short var=10;
					//var used for 10ms adc start
if(var==0)
{
	ADC_Start();		//at every 10ms elapsed the ADC sampling and conversion starts
	var=10;
}
else
{
	var--;
}
}

	
