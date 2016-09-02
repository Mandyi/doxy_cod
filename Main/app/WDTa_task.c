/******************************************************************************/
/* @PROJECT : MOWER */
/* @SW_RELEASE : 0100 */
/* @NAME : WDTa_task.c */
/* @PURPOSE : init WDT task */
/* @CREATED_BY : A. Kukharenko */
/* @CREATION_DATE : December 6 2009 */
/* @CREATION_SITE : Aidoss */
/* @LANGUAGE : 'C' */
/* @MPROC_TYPE : Independent */
/* ******************************************************************* */
/* @REVISION_BY :  */
/* @SW_RELEASE :  */
/* @CHANGES :  */
/* @CREATION_DATE :  */
/* @CREATION_SITE :  */
/***************************** (C) Copyright Algodue Elettronica *******************/

#include "FreeRTOS.h"
#include "task.h" 

#include "WDTa_task.h"
#include "WDTd_driver.h"

#define wdtSTACK_SIZE		configMINIMAL_STACK_SIZE 
#define wdtTASK_DELAY		500 /*at Datasheet on TPS3823 timeout WDT - min 900ms*/

void vWDTTask ( void *pvParameters )
{
	for(;;)
	{
	 vTaskDelay( wdtTASK_DELAY );
	 
	 Reset_HW_WDT();
	  
	}	
}	

void vStartWDTTasks( unsigned portBASE_TYPE uxPriority )
{
   xTaskCreate( vWDTTask, "WDT", wdtSTACK_SIZE, NULL , uxPriority, ( xTaskHandle * ) NULL );
}	
