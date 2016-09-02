//PROJECT DETAILS
/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0001 */
/* @NAME : KEYS_driver.c */
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
//INCLUDES

#include "FreeRTOS.h"

#include "task.h" 
#include "semphr.h"
//#include "p24FJ128GB106.h"
#include"queue.h"
#include"KEYS_driver.h"

//DEFINES
//xQueueHandle KEYS_xQueue;

//BUTTON DECLARATION
void INT_KEYS_DRIVER()
{
// SET PINS 
//	B1_INT_PIN = 1;        //B1 PIN SET AS INPUT
//	B2_INT_PIN = 1;        //B2 PIN SET AS INPUT

//SET PULL-UPS
	B1_PULL_UP = 1;        // 1-ENABLE
	B2_PULL_UP = 1;

//ENABLE CHANGE NOTIFICATION
	B1_CN_EN = 1 ;          // 1-ENABLE
	B2_CN_EN = 1 ;

//ENABLE CHANGE NOTIFICATION INTERRUPT IN INTERRUPT CONTROL REGISTER
	INTERR_CONTROL_CN = 1; // 1 - ENABLE

//CLEAR FLAG FOR CHANGE NOTIFICATION
	FLAG_CN = 0 ;          // CLEAR FLAG

//CREATE QUEUE
	void vATask(void *pvParamet)
	{
	xQueueHandle KEYS_xQueue;

//Create a queue capable of containing 10 pointers to AMessage
//structures.  These are to be queued by pointers as they are
//relatively large structures. 
		KEYS_xQueue =  xQueueCreate( 10, sizeof( struct KEYS_AMessege * ) );
        KEYS_xQueue=0;
		if (KEYS_xQueue == NULL)
		{
		// Queue was not created and must not be used. 
		}

	 
	}//END OF CREATE QUEUE

}//END OF INT_KEYS_DRIVER

//CHANGE NOTIFICATION INTERRUPT FUNCTION

extern struct KEYS_AMessege KEYS_TIME;

void __attribute__((__interrupt__, auto_psv)) _CNInterrupt(void)
{ 
    extern xQueueHandle KEYS_xQueue;
	
    KEYS_TIME.B_ID = 0; 
	
//UPDATE BUTTONS PRESSED OR RELEASED TIME ON STRUCT
	if (1 != B1_S) //BUTONUL 1 = APASAT
	{
		KEYS_TIME.B1_DOWN_TIME = xTaskGetTickCount(); //rezolutie de 1ms
	}
	else if (0 == B1_S)//BUTONUL 1 = RIDICAT
	{ 
		KEYS_TIME.B2_UP_TIME = xTaskGetTickCount();
		KEYS_TIME.B_ID = 1;
	}
	else if (1 != B1_S) //BUTONUL 2 = APASAT
	{
		KEYS_TIME.B2_DOWN_TIME = xTaskGetTickCount();
	}
	else if (0 == B1_S)//BUTONUL 2 = RIDICAT
	{
		KEYS_TIME.B2_UP_TIME = xTaskGetTickCount();
		KEYS_TIME.B_ID = 2;
	}

//xQueueSendFromISR START
   

	if (0 != KEYS_TIME.B_ID) //SEND ON QUEUEL AFTER BUTTON PRESSED TIME WAS RECORDED IN STRUCT
	{
		
 short xHigherPriorityTaskWoken;

//We have not woken a task at the start of the ISR.

		xHigherPriorityTaskWoken = pdFALSE;

//SEND DATA ON QUEUE 
		xQueueSendFromISR(KEYS_xQueue, &KEYS_TIME, &xHigherPriorityTaskWoken);
		 
//Now the buffer is empty we can switch context if necessary.L 
		if (xHigherPriorityTaskWoken)
		{

//			taskYIELD_FROM_ISR();  //normal asi apela functia din task unde sa atribui valorile
		}

		
	}
//xQueueSendFromISR END

 FLAG_CN = 0; //END OF ISR CHANGE OF STATE 
}


