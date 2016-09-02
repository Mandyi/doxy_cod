/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME : ADCa_task.c */
/* @PURPOSE :  */
/* @CREATED_BY : M. Ghetu */
/* @CREATION_DATE : July 22 2016 */
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
#include "UARTd_driver.h"
#include "UARTa_task.h"


/*_____LOCAL-DEFINE___________________________________________________________*/
/*_____LOCAL-TYPES____________________________________________________________*/
/*_____GLOBAL-DATA____________________________________________________________*/
extern u_char TX_buffer[BUFF_MAX_SIZE], RX_buffer[BUFF_MAX_SIZE];
/*_____LOCAL-DATA_____________________________________________________________*/
/*_____LOCAL-MACROS___________________________________________________________*/
/*_____LOCAL-FUNCTIONS-PROTOTYPES_____________________________________________*/
/*_____GLOBAL-FUNCTIONS_______________________________________________________*/





void vUARTTask ( void *pvParameters )
{
	for(;;)
	{
	 if( UART_coada_RX != NULL )
     {
         // Receive a message on the created queue.  Block for 10 ticks if a
         // message is not immediately available.
       do
       {
         if(xQueueReceive( UART_coada_RX, &RX_buffer, ( portTickType ) 100 ) )
         {
	 	}
       }while(uxQueueMessagesWaiting(UART_coada_RX));  
     }

if( UART_coada_TX != NULL )
     {
         // Send a message on the created queue.  Block for 10 ticks if a
         // message is not immediately available.
       do
       {
         if(xQueueSend( UART_coada_TX, &TX_buffer, ( portTickType ) 100 ) )
         {
	 	}
       }while(uxQueueMessagesWaiting(UART_coada_TX));  
     }



   	 vTaskDelay(uartTASK_DELAY);
	}
		
}
	
void vStartUARTTasks( unsigned portBASE_TYPE uxPriority )
{
    UART_coada_RX= xQueueCreate( uartSIZE_QUEUE, sizeof( u_char ) );
	UART_coada_TX = xQueueCreate( uartSIZE_QUEUE, sizeof( u_char ) );

   xTaskCreate( vUARTTask, "UART", uartSTACK_SIZE, NULL , uxPriority, ( xTaskHandle * ) NULL );
}	

