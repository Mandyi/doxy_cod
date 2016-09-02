/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME : LEDd_driver.c */
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
xQueueHandle ALARM_coada; // declarare variabila ADC de tip coada
xSemaphoreHandle Semaph_LED;
/*_____LOCAL-DATA_____________________________________________________________*/
/*_____LOCAL-MACROS___________________________________________________________*/
/*_____LOCAL-FUNCTIONS-PROTOTYPES_____________________________________________*/
/*_____GLOBAL-FUNCTIONS_______________________________________________________*/


/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h" 
#include "LEDd_driver.h"
#include "SPId_driver.h"

#include "Gas_driver.h"

//structura pentru preluarea valorilor de la ALARM_coada
 struct GAS_VALUE
 {
    short GAS_Senzor_value;
 } xGAS_VALUE;

//functie de receptionare a semaforului in cazul in care alarma e pornita
//cat timp receptionez semaforul preiau datele de la ALARM_coada, iar LEDUL Rosu o sa faca blink proportional cu valorile din coada
//altfel LED Verde este aprins
void ReceiveSemaphore_LED( void * pvParameters )
{
    /* ... Do other things. */

    if( Semaph_LED != NULL )
    {
        /* See if we can obtain the semaphore.  If the semaphore is not
        available wait 10 ticks to see if it becomes free. */
        if( xSemaphoreTake( Semaph_LED, ( portTickType ) 10 ) == pdTRUE )
        {
            /* We were able to obtain the semaphore and can now access the
            shared resource. */

            /* ... */

            /* We have finished accessing the shared resource.  Release the
            semaphore. */
		//cand timp preiau semaforul de la ALARMSa_task receptionez date de la coada din ALARMSa_task(valori de la senzorul de fum/gaz)
	    while(Semaph_LED != NULL)
	    	{
			vReceive_GAS_VALUE();
	    	}
        //xSemaphoreGive( Semaph_LED );
        }
        else
        {	
	   // printf("Can't access the Semaphore_LED ");
	   // Cand nu preiau semaforul inseamna ca alarma nu este activa si totul e ok -> aprind LED Verde		
	   // LED GREEN ON - ALL OK		
	   SET_PIN_MODE(PIN_LED_GREEN, ePORTB, GPIO, OUTPUT);
	   SET_PIN_MODE(PIN_LED_RED, ePORTB, GPIO, OUTPUT);
	   SET_IO_PIN(PIN_LED_GREEN, ePORTB, 1);
	   SET_IO_PIN(PIN_LED_RED, ePORTB, 0);
            /* We could not obtain the semaphore and can therefore not access
            the shared resource safely. */
        }
    }
}

 // Task to receive from the queue.
 // Functie de receptionare a cozii de la ALARMSa_task
 // Odata receptionata coada se va apela functia LED() care va face blink(LED-ul Rosu) proportional cu valorile receptionate
 void vReceive_GAS_VALUE()
 {
 struct GAS_VALUE *pxRxedGAS_VALUE;

    if( ALARM_coada != 0 )
    {
        // Receive a message on the created queue.  Block for 100 ticks if a
        // message is not immediately available.
        if( xQueueReceive( ALARM_coada, &( pxRxedGAS_VALUE ), ( portTickType ) 100 ) )
        {
            // pcRxedMessage now points to the struct AMessage variable posted
            // by vATask.
		    LED(xGAS_VALUE.GAS_Senzor_value);
        }
    }

	// ... Rest of task code.
	
 }

//functie blink LED Rosu la preluarea semaforului Semaph_LED provenit de la ALARMSa_task
unsigned char LED( unsigned short GAS_VAL )
{
	//setez LED Rosusi Verde ca OUTPUT
	SET_PIN_MODE(PIN_LED_RED, ePORTB, GPIO, OUTPUT);
	SET_PIN_MODE(PIN_LED_GREEN, ePORTB, GPIO, OUTPUT);
	//LED Verde oprit
	SET_IO_PIN(PIN_LED_GREEN, ePORTB, 0);
	//LED ROSU blink
	//delay proportional in functie de valoarea masurata de senzor(valoare max ADC - valoare senzor)
	//LED ROSU pornit
	SET_IO_PIN(PIN_LED_RED, ePORTB, 1);
	//delay 
	__delay_ms(ADC_MAX_VALUE-xGAS_VALUE.GAS_Senzor_value);
	//LED ROSU oprit
	SET_IO_PIN(PIN_LED_RED, ePORTB, 0);
	//delay
	__delay_ms(ADC_MAX_VALUE-xGAS_VALUE.GAS_Senzor_value);
	
	return 0;
}
