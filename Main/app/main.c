/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME :main.c */
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

#include "LEDd_driver.h"
#include "POWERd_driver.h"
#include "ADCd_driver.h"
#include "ADCa_task.h"
#include "WDTd_driver.h"
#include "WDTa_task.h"
#include "SPId_driver.h"
#include "RTCCd_driver.h"
#include "EEPROM25d_driver.h"
#include "FRAMd_driver.h"
#include "UARTa_task.h"
#include "MSd_driver.h"
#include "at45d_driver.h"

/*_____LOCAL-DEFINE___________________________________________________________*/

#define PRIORITATE 5 /* toate task-urile vor avea aceeasi prioritate */

/*_____LOCAL-TYPES____________________________________________________________*/
/*_____GLOBAL-DATA____________________________________________________________*/
/*_____LOCAL-DATA_____________________________________________________________*/
/*_____LOCAL-MACROS___________________________________________________________*/
/*_____LOCAL-FUNCTIONS-PROTOTYPES_____________________________________________*/
/*_____GLOBAL-FUNCTIONS_______________________________________________________*/




#ifdef __PIC24FJ128GB106__ //Defined by MPLAB when using 24FJ256GB106 device
 
//        _CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2) 
//        _CONFIG2( 0xF7FF & IESO_ON & FCKSM_CSECME & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV5 & IOL1WAY_OFF)
#ifdef INTERNAL_WDT
     	_CONFIG1( JTAGEN_OFF & GCP_ON & GWRP_OFF & COE_OFF & FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS1024 & ICS_PGx2) 
#else
		_CONFIG1( JTAGEN_OFF & GCP_ON & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2) 
#endif
        _CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSECME & OSCIOFNC_OFF & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV5 & IOL1WAY_OFF)
	 	_CONFIG3( 0xFFFF)

#else
        #error No MCU difined
#endif

int main(void)
{

	/* Finally start the scheduler. */
	INTCON1bits.NSTDIS=1;
	CRCCONbits.CSIDL=1;//Disable crc module
	//Init_HW_WDT();
	//LEDd_init_port();
	//POWERd_init_port();
	ADCd_Init();
	//SPId_Init();
	//Stop_HW_WDT();	
	UARTd_Init();	
	//FRAMd_UpdateLocalVariablesFromFRAM();
	//if(!RCFGCALbits.RTCEN)
	{
		/*
		The RCFGCAL and ALCFGRPT registers are only reset on a POR. Once the device exits the
		POR state, the clock registers should be reloaded with the desired values.
		Don't reset the RTC only if the RTCEN is 0 => Power on reset
		*/
	//	RTCC_Time.Sec=0x00;
	//	RTCC_Time.Min=0x00;
	//	RTCC_Time.Hour=0x00;
	//	RTCC_Time.Day=0x01;
	//	RTCC_Time.Month=0x01;
	//	RTCCd_Init(0);
	//	RTCC_Time=RTCCd_Get();		
	}
		
	//vStartADCTasks(( tskIDLE_PRIORITY+1 ));	
	vStartUARTTasks(( PRIORITATE ));
	vTaskStartScheduler();
	/* Will only reach here if there is insufficient heap available to start
	the scheduler. */
	return 0;
}
void vApplicationIdleHook( void )
{
	/* Schedule the co-routines from within the idle task hook. */
	vCoRoutineSchedule();
	Idle();
}

	