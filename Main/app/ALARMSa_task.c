
/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME : ALARMa_task.c */
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
#include "Gas_driver.h"

/*_____LOCAL-DEFINE___________________________________________________________*/
/*_____LOCAL-TYPES____________________________________________________________*/
/*_____GLOBAL-DATA____________________________________________________________*/

xSemaphoreHandle Semaph_WD, Semaph_LED, Semaph_FRAM; // declarare variabila de tip semafor
xQueueHandle ADC_coada, LED_coada; // declarare variabila ADC de tip coada
unsigned char alarma,k=0;
short Sf_coada=-1;
unsigned short c[DimMax];
float sensor_value=0;

//xSemaphoreHandle Semaph_WD=0;
/*_____LOCAL-DATA_____________________________________________________________*/
/*_____LOCAL-MACROS___________________________________________________________*/
/*_____LOCAL-FUNCTIONS-PROTOTYPES_____________________________________________*/
/*_____GLOBAL-FUNCTIONS_______________________________________________________*/

void Create()
{
	
	vSemaphoreCreateBinary(Semaph_WD);
	vSemaphoreCreateBinary(Semaph_LED);
	vSemaphoreCreateBinary(Semaph_FRAM); // create semaphores
 	LED_coada=xQueueCreate(10,sizeof (unsigned short ));/*create queue for led
												 10=The maximum number of items the queue can hold at any one time., 
												 sizeof(unsigned short)=The size, in bytes, required to hold each item in the queue. */
	
}
void GAS_sensor()
	{	
		Create();
		for(;;)
		{	
		 if(ADC_coada != NULL)
			 {	
				 // Receive a message on the created queue.  Block for 10 ticks if a
		         // message is not immediately available.
					if (xQueueReceive(ADC_coada,&(c[Sf_coada++]),( portTickType ) 100 ))	//ADC_coada= 	The handle to the queue from which the item is to be received
														     		//&(c[Sf_coada++])= Pointer to the buffer into which the received item will be copied.
																	// ( portTickType ) 100 )= The maximum amount of time the task should block waiting for 
																	// an item to receive should the queue be empty at the time of the call. Setting xTicksToWait to 0 
																	//will cause the function to return immediately if the queue is empty. The time is defined in tick periods so the constant 
																	//portTICK_PERIOD_MS should be used to convert to real time if this is required.
					 {		
						k++;
					 }
				 	  else {}		
			  }
			else {}
		/* Calculate average */

		if (k==10)
		{
		 for(Sf_coada=0;Sf_coada<DimMax;Sf_coada++)
			{
				sensor_value=sensor_value+ c[Sf_coada];
			}
		sensor_value=sensor_value/DimMax;
		// sensor_volt= sensor_value/1024*5;
		/* send values to LED queue */

		if(LED_coada != NULL)
		{	
		xQueueSend(LED_coada,&(sensor_value),( portTickType ) 100);
		} 
		else {}
		/* */
		if (sensor_value >= VAL_PRAG)
		{
			//alarma=ON;

				xSemaphoreGive(Semaph_WD); 
				xSemaphoreGive(Semaph_LED);
				xSemaphoreGive(Semaph_FRAM);
		}	 
		 else
			  {
				/* There was insufficient FreeRTOS heap available for the semaphore to
				        be created successfully. */
			   }
		/* resete local queue*/
		Sf_coada=-1;
		sensor_value=0;
		k=0;
	 }			
	}
}
void StartGASTask( unsigned portBASE_TYPE uxPriority )
{
//	   BaseType_t xTaskCreate(    TaskFunction_t pvTaskCode,
//                            const char * const pcName,
//                            unsigned short usStackDepth,
//                           void *pvParameters,
//                           UBaseType_t uxPriority,
//                           TaskHandle_t *pxCreatedTask
//                          ); 
		xTaskCreate(GAS_sensor, "Receive_queue", gasSTACK_SIZE, NULL , 1, ( xTaskHandle * ) NULL );
}
