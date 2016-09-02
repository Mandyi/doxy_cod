//PROJECT DETAILS
/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0001 */
/* @NAME : KEYS_task.c */
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
#include "p24FJ128GB106.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "semphr.h"

#include"KEYS_task.h"
#include"KEYS_driver.h"

//DEFINES
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define T_BETWEEN_B 150   //TIME (ms)BETWEEN BUTTONS TO TAKE THEM AS BOUTH PRESSED AT THE SAME TIME
#define T_PRESSED   5000  //TIME (ms)REQUIRED TO KEEP BOTH BUTTONS PRESSED 

 extern xQueueHandle KEYS_xQueue;


// Task to receive from the queue.

void vKEYS_RX_QUEUE_Task(void *pvParameters)
{
	char i = 0;

	struct KEYS_RXMessege RX_KEYS;
    extern struct B1_RXMessege	B1;
	extern struct B2_RXMessege B2;




	while(1)
	{
		for (i = 1; i <= 2; i++)
		{
			if (KEYS_xQueue != 0)
			{
				// Receive a message on the created queue.  Block for 10 ticks if a
				// message is not immediately available.

				if (xQueueReceive(KEYS_xQueue, &RX_KEYS, (portTickType)0))
				{
					// pcRxedMessage now points to the struct AMessage variable posted
					// by vATask.
					//DEPEND ON BUTTON ID WE CREATE COPYES TO PROTECT DATA
					if (1 == RX_KEYS.B_ID)
					{
						B1.DONE = 0;
						B1.D_TIME = RX_KEYS.B1_DOWN_TIME;
						B1.U_TIME = RX_KEYS.B1_UP_TIME;
					}
					else if (2 == RX_KEYS.B_ID)
					{
						B2.DONE = 0;
						B2.D_TIME = RX_KEYS.B2_DOWN_TIME;
						B2.U_TIME = RX_KEYS.B2_UP_TIME;
					}
				}
			}
		}
//IF WE HAVE NEW BUTTON VALUES THEN
		
			if ((MAX(B1.D_TIME, B2.D_TIME) - MIN(B1.D_TIME, B2.D_TIME) < T_BETWEEN_B) && ((MAX(B1.D_TIME, B1.U_TIME) - MIN(B1.D_TIME, B1.U_TIME)) > T_PRESSED) && (MAX(B2.D_TIME, B2.U_TIME) - MIN(B2.D_TIME, B2.U_TIME)) && (0 != B1.DONE) && (0 != B2.DONE))
			{
              //RESET TASK

            
				B1.DONE = 1;//BUTTONS TASK DONE
				B2.DONE = 1;
			}//END OF RESET 
			else if (B1.DONE == 0)
			{//SLEEP
				
			
				

				B1.DONE = 1;//BUTTONS TASK DONE
			}//END OF SLEEP
			else if (B2.DONE == 0)
			{//REFRESH SENSOR
				
			
				
			
				B2.DONE = 1;//BUTTONS TASK DONE
			}//END OF REFRESH SENSOR

	
	}

	// ... Rest of task code.
}
