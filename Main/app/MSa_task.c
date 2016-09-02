/******************************************************************************/
/* @PROJECT : Tracker */
/* @SW_RELEASE :  */
/* @NAME : MSa_task.c */
/* @PURPOSE :  */
/* @CREATED_BY : G. Cocis */
/* @CREATION_DATE : February 3 2010 */
/* @CREATION_SITE : Digisoft */
/* @LANGUAGE : 'C' */
/* @MPROC_TYPE :  */
/* ******************************************************************* */
/* @REVISION_BY :  */
/* @SW_RELEASE :  */
/* @CHANGES :  */
/* @CREATION_DATE :  */
/* @CREATION_SITE :  */
/***************************** (C) Copyright Digisoft *******************/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "MSd_driver.h"
#include "ALARMSa_task.h"

xSemaphoreHandle xMS_ISR_Semaphore;
#define msSTACK_SIZE configMINIMAL_STACK_SIZE
#define msTASK_DELAY 1000
unsigned int timeout_sec;
void vMSTask ( void *pvParameters )
{
	char tmp;

	char InMotion;
	for(;;)
	{
	  if(MotionSensor.Timeout&0x80)//is MotionSensor enabled?
	  {
		if(xMS_ISR_Semaphore!=NULL)		
			if(xSemaphoreTake(xMS_ISR_Semaphore,0))
			{				
				timeout_sec=0;
				if(!InMotion)
					ArmAlarm(MotionOn,NULL,SMS);
				InMotion=1;				
			}
		if(InMotion)
		{
			if(timeout_sec++>MotionSensor.Timeout*60)			
			{
				//MOTION OFF
				InMotion=0;
				//ArmAlarm(MotionOff,NULL,SMS);
			}
		}
	  }
		vTaskDelay(msTASK_DELAY);
	}	
	
}
void vStartMSTasks( unsigned portBASE_TYPE uxPriority )
{	
	vSemaphoreCreateBinary( xMS_ISR_Semaphore );
	xTaskCreate( vMSTask, "MS", msSTACK_SIZE, NULL , uxPriority, ( xTaskHandle * ) NULL );
}	

