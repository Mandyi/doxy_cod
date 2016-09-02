/******************************************************************************/
/*
 *  \brief     Doxygen test.
 *  \details   This demo is used to demonstrate a number of section commands.
 *  \author    Dan Naghi
 *  \version   1.0
 *  \date      2016
 *  \pre       First initialize the system.
 *  \warning   Improper use can crash your application
 *  \copyright Copyright by Continental Automotive GmbH 
 */
/***************************** (C) Copyright NTT Data Romania *******************/


typedef unsigned char u_char;
typedef unsigned int u_int;






/*!
***  To set the  state and the direction of a PIN call SET_PIN_MODE() with the next variables:   **
**        pin = PIN0 - PIN15 			The PIN you want to use				       				**
**		  port = ePORTA - ePORTE 		The PORT you want to use			  					**
**		  mode = GPIO					Set PIN as GPIO											**
**			   = Function				Set PIN as implicit function							**
**		  directon = INPUT 																		**
**				   = OUTPUT 																	***/
void SET_PIN_MODE(u_char pin, u_char port, u_char mode, u_char direction);



/*!
***  To set the  state and the direction of a PIN call SET_PIN_DIRECTION()
**	 This function does not need to be called.
**   Function is automatically called from: 		SET_PIN_MODE(u_char pin, u_char port, u_char mode, u_char direction)        
**        GPIO_pin = PIN0 - PIN15 					Pinul pe care doriti sa il folositi       			**
**		  GPIO_port = ePORTA - ePORTE 				Portul pe care doriti sa il folositi  				**
**		  directon = INPUT 																				**
**				   = OUTPUT 																			***/
void SET_IO_PIN_DIRECTION(u_char GPIO_pin, u_char GPIO_port, u_char GPIO_direction);



/*!
***  To check if the state of a PIN call GET_IO_PIN_STATE() with the next variables:
**        GPIO_pin = PIN0 - PIN15					The PIN you want to see							**
**		  GPIO_port = ePORTA - ePORTE 				The PORT you want to see  						**
**		  Function will return the valuea read on TRISx 											**
**		  IO_return_state 	= 1 					PIN IMPUT										**
**							= 0						PIN OUTPUT										***/
u_char GET_IO_PIN_STATE(u_char GPIO_pin, u_char GPIO_port);



/* !
*** 	To set the value on a PIN use SET_IO_PIN() with the next variables:
**\brief        GPIO_pin = PIN0 - PIN15					The PIN you want to set		**
**\brief		GPIO_port = ePORTA - ePORTE 			The PORT you want to set  	**
**\brief		GPIO_value = 1 							The value you want to set	**
**\brief		      = 0															***/
void SET_IO_PIN(u_char GPIO_pin, u_char GPIO_port, u_char GPIO_value);




/* !
*** To read the value from a PIN call GET_IO_PIN() using the next variables: 
**        GPIO_pin = PIN0 - PIN15					The PIN you want to set		**
**		  GPIO_port = ePORTA - ePORTE 				The PORT you want to set  	**
**
**
**		Function will return the value read on Rx
**		  IO_return_value 	= 1 					PIN value equal 1			**
**							= 0						PIN value equal 0			***/
u_char GET_IO_PIN(u_char GPIO_pin, u_char GPIO_port);



enum SELECT
{
	GPIO=0,
	Function=1,
};
enum IO_direction
{
	OUTPUT = 0,
	INPUT = 1,
};
enum PORTS
{
	ePORTA = 0,
	ePORTB = 1,
	ePORTC = 2,
	ePORTD = 3,
	ePORTE = 4,
	ePORTF = 5,
};
enum PINS
{
	PIN0 = 0,
	PIN1 = 1,
	PIN2 = 2,
	PIN3 = 3,
	PIN4 = 4,
	PIN5 = 5,
	PIN6 = 6,
	PIN7 = 7,
	PIN8 = 8,
	PIN9 = 9,
	PIN10 = 10,
	PIN11 = 11,
	PIN12 = 12,
	PIN13 = 13,
	PIN14 = 14,
	PIN15 = 15,
};
/*
enum PORT
{
	PORTA = 1,
	PORTB = 2,
	PORTC = 3,
};
enum UART_Modul
{
	UART1 = 1,
	UART2 = 2,
	UART3 = 3,
};

enum SPI_Modul
{
	SPI1 = 1,
	SPI2 = 2,
	SPI3 = 3,
};


enum I2C_Modul
{
	I2C1 = 1,
	I2C2 = 2,
	I2C3 = 3,

};
struct PORT_FLAG
{
	u_int PORT_Tx;
	u_int PORT_Rx;
};
struct UART_FLAG
{
	u_int UART_Rx;
	u_int UART_Tx;
};

struct SPI_FLAG
{
	u_int SPI_Freq;

};
struct I2C_FLAG
{
	u_int I2C_Freq;

};
*/
