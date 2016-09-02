/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME : WDTd_driver.c */
/* @PURPOSE :  */
/* @CREATED_BY : A. Capatina */
/* @CREATION_DATE : July 21 2016 */
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
#include "WDTd_driver.h"
#include "p24FJ128GB106.h"
#include "Gas_driver.h"
#include "GPIO_INITd_driver.h"

/*_____LOCAL-DEFINE___________________________________________________________*/
/*_____LOCAL-TYPES____________________________________________________________*/
/*_____GLOBAL-DATA____________________________________________________________*/
/*_____LOCAL-DATA_____________________________________________________________*/
/*_____LOCAL-MACROS___________________________________________________________*/
/*_____LOCAL-FUNCTIONS-PROTOTYPES_____________________________________________*/
/*_____GLOBAL-FUNCTIONS_______________________________________________________*/

#include "FreeRTOS.h"
#include "task.h" 







void WDT_Function()
{		
		SET_PIN_MODE(46, ePORTD, GPIO, 0);       //	WDI setat ca output
		SET_IO_PIN(46, ePORTD, 0);  //Scriere 0 pe pinul de WDI 
		//xTaskCreate(vaTask_GAS,(signed char*)"task_Adi",1024,NULL,1,NULL);   //Trebuei adaugate task-uri si pentru celelalte semafoare
	while(1)
	{
	SET_IO_PIN(46, ePORTD, 1);  //setare WDI 1
		if(1 == vaTask_GAS())
		{
		   //daca toate semafoarele sunt verzi atunci watchdog-ul trebuie reset
    	Feed();
		}
		else
		{
		Reset();
		}
	}
}


/*Am nevoie de task-ul lui Adi pentru a fi creat si pus sub xTaskCreate-ul meu*/

int vaTask_GAS(void)
{

	while(1)
	{
		if(xSemaphoreTake(Semaph_WD,1000))    //Preluare semafor
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}




void Feed(void)
{

	SET_IO_PIN(46, ePORTD, 0);  //Setarea pinului de WDI pe 0
}

void Reset(void)
{
	RESET=1;        //Comanda pentru resetare uC

}
	