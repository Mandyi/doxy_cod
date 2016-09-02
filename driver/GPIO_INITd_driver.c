/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME : EEPROM25d_driver.c */
/* @PURPOSE :  */
/* @CREATED_BY : D. Naghi */
/* @CREATION_DATE : July 19 2016 */
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

#include "SPId_driver.h"
#include "EEPROM25d_driver.h"




#include "GPIO_INITd_driver.h"



/*Init a PIN as GPIO and set the state: INPUT/OUTPUT*/
void SET_PIN_MODE(u_char pin, u_char port, u_char mode, u_char direction)
{
	if (GPIO == mode)
	{
		SET_IO_PIN_DIRECTION(pin, port, direction);
	}
	else
	{
		if (Function == mode)
		{

		}
		else
		{

		}
	}

}
/*Set the PIN direction accesing TRISx register */

void SET_IO_PIN_DIRECTION(u_char GPIO_pin, u_char GPIO_port, u_char GPIO_direction)
{
	/* ---------------------------TRISAx = 1 sets PIN x from port PORTA as an input PIN------------------------*/
	/* ---------------------------TRISAx = 0 sets PIN x from port PORTA as an output PIN-----------------------*/
	/*
	if (ePORTA == GPIO_port)
	{
	switch (GPIO_pin)
	{
	case PIN0:
	{
	if (INPUT == GPIO_direction)
	{
	TRISAbits.TRISA0 = 1;
	}
	else
	{
	TRISAbits.TRISA0 = 0;
	}
	break;
	}
	case PIN1:
	{
	if (INPUT == GPIO_direction)
	{
	TRISAbits.TRISA1 = 1;
	}
	else
	{
	TRISAbits.TRISA1 = 0;
	}
	break;
	}
	default:
	{
	break;
	}
	}
	}
	else
	{
	}
	*/
	/* ---------------------------TRISBx = 1 sets PIN x from port PORTB as an input PIN------------------------*/
	/* ---------------------------TRISBx = 0 sets PIN x from port PORTB as an output PIN-----------------------*/
	if (ePORTB == GPIO_port)    	/*Selectarea port PORTB */
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (INPUT == GPIO_direction)
			{
				TRISBbits.TRISB0 = 1;
			}
			else
			{
				TRISBbits.TRISB0 = 0;
			}
			break;
		}
		case PIN1:
		{
			if (INPUT == GPIO_direction)
			{
				TRISBbits.TRISB1 = 1;
			}
			else
			{
				TRISBbits.TRISB1 = 0;
			}
			break;
		}
		case PIN11:
		{
			if (INPUT == GPIO_direction)
			{
				TRISBbits.TRISB11 = 1;
			}
			else
			{
				TRISBbits.TRISB11 = 0;
			}
			break;
		}
		case PIN12:
		{
			if (INPUT == GPIO_direction)
			{
				TRISBbits.TRISB12 = 1;
			}
			else
			{
				TRISBbits.TRISB12 = 0;
			}
			break;
		}
		case PIN13:
		{
			if (INPUT == GPIO_direction)
			{
				TRISBbits.TRISB13 = 1;
			}
			else
			{
				TRISBbits.TRISB13 = 0;
			}
			break;
		}
		case PIN14:
		{
			if (INPUT == GPIO_direction)
			{
				TRISBbits.TRISB14 = 1;
			}
			else
			{
				TRISBbits.TRISB14 = 0;
			}
			break;
		}
		case PIN15:
		{
			if (INPUT == GPIO_direction)
			{
				TRISBbits.TRISB15 = 1;
			}
			else
			{
				TRISBbits.TRISB15 = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}

	/* ---------------------------TRISCx = 1 sets PIN x from port PORTC as an input PIN------------------------*/
	/* ---------------------------TRISCx = 0 sets PIN x from port PORTC as an output PIN-----------------------*/
	if (ePORTC == GPIO_port)			/*Select port PORTC*/
	{
		switch (GPIO_pin)
		{
		case PIN12:
		{
			if (INPUT == GPIO_direction)
			{
				TRISCbits.TRISC12 = 1;
			}
			else
			{
				TRISCbits.TRISC12 = 0;
			}
			break;
		}
		case PIN13:
		{
			if (INPUT == GPIO_direction)
			{
				TRISCbits.TRISC13 = 1;
			}
			else
			{
				TRISCbits.TRISC13 = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}

	/* ---------------------------TRISDx = 1 sets PIN x from port PORTD as an input PIN------------------------*/
	/* ---------------------------TRISDx = 0 sets PIN x from port PORTD as an output PIN-----------------------*/
	if (ePORTD == GPIO_port)			/*Select port PORTD*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (INPUT == GPIO_direction)
			{
				TRISDbits.TRISD0 = 1;
			}
			else
			{
				TRISDbits.TRISD0 = 0;
			}
			break;
		}
		case PIN1:
		{
			if (INPUT == GPIO_direction)
			{
				TRISDbits.TRISD1 = 1;
			}
			else
			{
				TRISDbits.TRISD1 = 0;
			}
			break;
		}
		case PIN2:
		{
			if (INPUT == GPIO_direction)
			{
				TRISDbits.TRISD2 = 1;
			}
			else
			{
				TRISDbits.TRISD2 = 0;
			}
			break;
		}
		case PIN8:
		{
			if (INPUT == GPIO_direction)
			{
				TRISDbits.TRISD8 = 1;
			}
			else
			{
				TRISDbits.TRISD8 = 0;
			}
			break;
		}
		case PIN9:
		{
			if (INPUT == GPIO_direction)
			{
				TRISDbits.TRISD9 = 1;
			}
			else
			{
				TRISDbits.TRISD9 = 0;
			}
			break;
		}
		case PIN10:
		{
			if (INPUT == GPIO_direction)
			{
				TRISDbits.TRISD10 = 1;
			}
			else
			{
				TRISDbits.TRISD10 = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}

	/* ---------------------------TRISEx = 1 sets PIN x from port PORTE as an input PIN------------------------*/
	/* ---------------------------TRISEx = 0 sets PIN x from port PORTE as an output PIN-----------------------*/
	if (ePORTE == GPIO_port)			/*Select port PORTE*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (INPUT == GPIO_direction)
			{
				TRISEbits.TRISE0 = 1;
			}
			else
			{
				TRISEbits.TRISE0 = 0;
			}
			break;
		}
		case PIN1:
		{
			if (INPUT == GPIO_direction)
			{
				TRISEbits.TRISE1 = 1;
			}
			else
			{
				TRISEbits.TRISE1 = 0;
			}
			break;
		}
		case PIN2:
		{
			if (INPUT == GPIO_direction)
			{
				TRISEbits.TRISE2 = 1;
			}
			else
			{
				TRISEbits.TRISE2 = 0;
			}
			break;
		}
		case PIN6:
		{
			if (INPUT == GPIO_direction)
			{
				TRISEbits.TRISE6 = 1;
			}
			else
			{
				TRISEbits.TRISE6 = 0;
			}
			break;
		}
		case PIN7:
		{
			if (INPUT == GPIO_direction)
			{
				TRISEbits.TRISE7 = 1;
			}
			else
			{
				TRISEbits.TRISE7 = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	/* ---------------------------TRISFx = 1 sets PIN x from port PORTF as an input PIN------------------------*/
	/* ---------------------------TRISFx = 0 sets PIN x from port PORTF as an output PIN-----------------------*/

	if (ePORTF == GPIO_port)			/*Select port PORTF*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (INPUT == GPIO_direction)
			{
				TRISFbits.TRISF0 = 1;
			}
			else
			{
				TRISFbits.TRISF0 = 0;
			}
			break;
		}
		case PIN1:
		{
			if (INPUT == GPIO_direction)
			{
				TRISFbits.TRISF1 = 1;
			}
			else
			{
				TRISFbits.TRISF1 = 0;
			}
			break;
		}
		case PIN3:
		{
			if (INPUT == GPIO_direction)
			{
				TRISFbits.TRISF3 = 1;
			}
			else
			{
				TRISFbits.TRISF3 = 0;
			}
			break;
		}
		case PIN4:
		{
			if (INPUT == GPIO_direction)
			{
				TRISFbits.TRISF4 = 1;
			}
			else
			{
				TRISFbits.TRISF4 = 0;
			}
			break;
		}
		case PIN5:
		{
			if (INPUT == GPIO_direction)
			{
				TRISFbits.TRISF5 = 1;
			}
			else
			{
				TRISFbits.TRISF5 = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
}



/* This function returns if PIN is INPUT or OUTPUT*/

u_char GET_IO_PIN_STATE(u_char GPIO_pin, u_char GPIO_port)
{
	u_char IO_return_status = 0;
	/*
	if (ePORTA == GPIO_port)
	{
	switch (GPIO_pin)
	{
	case PIN0:
	{
	if (1 == TRISAbits.TRISA0)
	{
	IO_return_status = 1;
	}
	else
	{
	IO_return_status = 0;
	}
	break;
	}
	case PIN1:
	{
	if (1 == TRISAbits.TRISA1)
	{
	IO_return_status = 1;
	}
	else
	{
	IO_return_status = 0;
	}
	break;
	}
	default:
	{
	break;
	}
	}
	}
	else
	{
	}
	*/
	if (ePORTB == GPIO_port)    	/*Select port PORTB*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == TRISBbits.TRISB0)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == TRISBbits.TRISB1)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN11:
		{
			if (1 == TRISBbits.TRISB11)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN12:
		{
			if (1 == TRISBbits.TRISB12)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN13:
		{
			if (1 == TRISBbits.TRISB13)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN14:
		{
			if (1 == TRISBbits.TRISB14)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN15:
		{
			if (1 == TRISBbits.TRISB15)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTC == GPIO_port)			/*Select port PORTC*/
	{
		switch (GPIO_pin)
		{
		case PIN12:
		{
			if (1 == TRISCbits.TRISC12)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN13:
		{
			if (1 == TRISCbits.TRISC13)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTD == GPIO_port)			/*Select port PORTD*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == TRISDbits.TRISD0)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == TRISDbits.TRISD1)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN8:
		{
			if (1 == TRISDbits.TRISD8)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN9:
		{
			if (1 == TRISDbits.TRISD9)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN10:
		{
			if (1 == TRISDbits.TRISD10)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTE == GPIO_port)    	/*Select port PORTE*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == TRISEbits.TRISE0)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == TRISEbits.TRISE1)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN6:
		{
			if (1 == TRISEbits.TRISE6)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN7:
		{
			if (1 == TRISEbits.TRISE7)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTF == GPIO_port)    	/*Select port PORTF*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == TRISFbits.TRISF0)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == TRISFbits.TRISF1)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN4:
		{
			if (1 == TRISFbits.TRISF4)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		case PIN5:
		{
			if (1 == TRISFbits.TRISF5)
			{
				IO_return_status = 1;
			}
			else
			{
				IO_return_status = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	return IO_return_status;
}
/* This function sets a value on a PIN (1 or 0) */
void SET_IO_PIN(u_char GPIO_pin, u_char GPIO_port, u_char GPIO_value)
{
	/*
	if (ePORTA == GPIO_port)
	{
	switch (GPIO_pin)
	{
	case PIN0:
	{
	if (1 == GPIO_value)
	{
	PORTAbits.RA0 = 1;
	}
	else
	{
	PORTAbits.RA0 = 0;
	}
	break;
	}
	case PIN1:
	{
	if (1 == GPIO_value)
	{
	PORTAbits.RA1 = 1;
	}
	else
	{
	PORTAbits.RA1 = 0;
	}
	break;
	}
	default:
	{
	break;
	}
	}
	}
	else
	{
	}
	*/
	if (ePORTB == GPIO_port)			/*Select port PORTB*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == GPIO_value)
			{
				PORTBbits.RB0 = 1;
			}
			else
			{
				PORTBbits.RB0 = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == GPIO_value)
			{
				PORTBbits.RB1 = 1;
			}
			else
			{
				PORTBbits.RB1 = 0;
			}
			break;
		}

		case PIN11:
		{
			if (1 == GPIO_value)
			{
				PORTBbits.RB11 = 1;
			}
			else
			{
				PORTBbits.RB11 = 0;
			}
			break;
		}
		case PIN12:
		{
			if (1 == GPIO_value)
			{
				PORTBbits.RB12 = 1;
			}
			else
			{
				PORTBbits.RB12 = 0;
			}
			break;
		}
		case PIN13:
		{
			if (1 == GPIO_value)
			{
				PORTBbits.RB13 = 1;
			}
			else
			{
				PORTBbits.RB13 = 0;
			}
			break;
		}
		case PIN14:
		{
			if (1 == GPIO_value)
			{
				PORTBbits.RB14 = 1;
			}
			else
			{
				PORTBbits.RB14 = 0;
			}
			break;
		}
		case PIN15:
		{
			if (1 == GPIO_value)
			{
				PORTBbits.RB15 = 1;
			}
			else
			{
				PORTBbits.RB15 = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTC == GPIO_port)			/*Select port PORTC*/
	{
		switch (GPIO_pin)
		{
		case PIN12:
		{
			if (1 == GPIO_value)
			{
				PORTCbits.RC12 = 1;
			}
			else
			{
				PORTCbits.RC12 = 0;
			}
			break;
		}
		case PIN13:
		{
			if (1 == GPIO_value)
			{
				PORTCbits.RC13 = 1;
			}
			else
			{
				PORTCbits.RC13 = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTD == GPIO_port)			/*Select port PORTD*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == GPIO_value)
			{
				PORTDbits.RD0 = 1;
			}
			else
			{
				PORTDbits.RD0 = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == GPIO_value)
			{
				PORTDbits.RD1 = 1;
			}
			else
			{
				PORTDbits.RD1 = 0;
			}
			break;
		}
		case PIN8:
		{
			if (1 == GPIO_value)
			{
				PORTDbits.RD8 = 1;
			}
			else
			{
				PORTDbits.RD8 = 0;
			}
			break;
		}
		case PIN9:
		{
			if (1 == GPIO_value)
			{
				PORTDbits.RD9 = 1;
			}
			else
			{
				PORTDbits.RD9 = 0;
			}
			break;
		}
		case PIN10:
		{
			if (1 == GPIO_value)
			{
				PORTDbits.RD10 = 1;
			}
			else
			{
				PORTDbits.RD10 = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTE == GPIO_port)			/*Select port PORTE*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == GPIO_value)
			{
				PORTEbits.RE0 = 1;
			}
			else
			{
				PORTEbits.RE0 = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == GPIO_value)
			{
				PORTEbits.RE1 = 1;
			}
			else
			{
				PORTEbits.RE1 = 0;
			}
			break;
		}
		case PIN6:
		{
			if (1 == GPIO_value)
			{
				PORTEbits.RE6 = 1;
			}
			else
			{
				PORTEbits.RE6 = 0;
			}
			break;
		}
		case PIN7:
		{
			if (1 == GPIO_value)
			{
				PORTEbits.RE7 = 1;
			}
			else
			{
				PORTEbits.RE7 = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTF == GPIO_port)		/*Select port PORTF*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == GPIO_value)
			{
				PORTFbits.RF0 = 1;
			}
			else
			{
				PORTFbits.RF0 = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == GPIO_value)
			{
				PORTFbits.RF1 = 1;
			}
			else
			{
				PORTFbits.RF1 = 0;
			}
			break;
		}
		case PIN4:
		{
			if (1 == GPIO_value)
			{
				PORTFbits.RF4 = 1;
			}
			else
			{
				PORTFbits.RF4 = 0;
			}
			break;
		}
		case PIN5:
		{
			if (1 == GPIO_value)
			{
				PORTFbits.RF5 = 1;
			}
			else
			{
				PORTFbits.RF5 = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
}
/* This function returns the value from a PIN */
u_char GET_IO_PIN(u_char GPIO_pin, u_char GPIO_port)
{
	u_char IO_return_value = 0;
	/*
	if (ePORTA == GPIO_port)
	{
	switch (GPIO_pin)
	{
	case PIN0:
	{
	if (1 == PORTAbits.RA0)
	{
	IO_return_value = 1;
	}
	else
	{
	IO_return_value = 0;
	}
	break;
	}
	case PIN1:
	{
	if (1 == PORTAbits.RA1)
	{
	IO_return_value = 1;
	}
	else
	{
	IO_return_value = 0;
	}
	break;
	}
	default:
	{
	break;
	}
	}
	}
	else
	{
	}
	*/
	if (ePORTB == GPIO_port)    	/*Select port PORTB*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == PORTBbits.RB0)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == PORTBbits.RB1)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}

		case PIN11:
		{
			if (1 == PORTBbits.RB11)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN12:
		{
			if (1 == PORTBbits.RB12)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN13:
		{
			if (1 == PORTBbits.RB13)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN14:
		{
			if (1 == PORTBbits.RB14)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN15:
		{
			if (1 == PORTBbits.RB15)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTC == GPIO_port)			/*Select port PORTC*/
	{
		switch (GPIO_pin)
		{
		case PIN12:
		{
			if (1 == PORTCbits.RC12)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN13:
		{
			if (1 == PORTCbits.RC13)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTD == GPIO_port)			/*Select port PORTD*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == PORTDbits.RD0)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == PORTDbits.RD1)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN8:
		{
			if (1 == PORTDbits.RD8)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN9:
		{
			if (1 == PORTDbits.RD9)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN10:
		{
			if (1 == PORTDbits.RD10)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTE == GPIO_port)    /*Select port PORTE*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == PORTEbits.RE0)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == PORTEbits.RE1)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN6:
		{
			if (1 == PORTEbits.RE6)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN7:
		{
			if (1 == PORTEbits.RE7)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	if (ePORTF == GPIO_port)    /*Select port PORTF*/
	{
		switch (GPIO_pin)
		{
		case PIN0:
		{
			if (1 == PORTFbits.RF0)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN1:
		{
			if (1 == PORTFbits.RF1)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN4:
		{
			if (1 == PORTFbits.RF4)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		case PIN5:
		{
			if (1 == PORTFbits.RF5)
			{
				IO_return_value = 1;
			}
			else
			{
				IO_return_value = 0;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
	}
	return IO_return_value;
}
