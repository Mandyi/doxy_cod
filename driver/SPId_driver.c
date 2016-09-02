/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE :  */
/* @NAME : SPId_driver.c */
/* @PURPOSE :  */
/* @CREATED_BY : T. Claudiu */
/* @CREATION_DATE :  */
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
#include "p24FJ128GB106.h"
#include "SPId_driver.h"
/*_____LOCAL-DEFINE___________________________________________________________*/
/*_____LOCAL-TYPES____________________________________________________________*/
/*_____GLOBAL-DATA____________________________________________________________*/
/*_____LOCAL-DATA_____________________________________________________________*/
/*_____LOCAL-MACROS___________________________________________________________*/
/*_____LOCAL-FUNCTIONS-PROTOTYPES_____________________________________________*/
/*_____GLOBAL-FUNCTIONS_______________________________________________________*/


/*function to set or reset a bit in a register*/
/*
void reg_setup(short int reg,unsigned char value,unsigned char bitval)
{
	switch(vaule)
	{
	case 0:
		reg &= ~(1<<bitval);
		break;
	case 1:
		reg |= 1<<bitval;
		break;
	default:
		break;
}
*/
/**/


/***!

** ![](C:\Users\claudiu.timoce\Desktop\asdasda)
** Alo

***/
void SPId_Init(void)
{	
	RESET_SPI;			//reset spi
	CLEAR_BUFFER;		//clear buffer
	CLEAR_IFLAG;		//Clear the Interrupt Flag
 	DISABLE_INTERRUPT;	//Disable the Interrupt
	MASTER_ENABLE_ON;	//master mode
	PRI_PRESCAL_16_1;	//16:1 primary prescale;  1M
    SEC_PRESCAL_8_1;	//8:1 secondary prescale;  125k			
    CLK_POL_ACTIVE_HIGH;//clock active high (CKP = 0)
    SPI_CKE;			//out changes inactive to active (CKE=0)
    SPI_MODE8_ON;		//8-bit mode
	CLEAR_IFLAG;		//Clear the Interrupt Flag
 	ENABLE_INTERRUPT;	//Enable the Interrupt
	ENABLE_SPI;			//enable SPI mode

  	CONFIG_SLAVE1_ENABLE();	//Set pin SS1
  	SLAVE1_DISABLE();		//ss1 low
  	CONFIG_SLAVE2_ENABLE();	//Set pin SS2
  	SLAVE2_DISABLE();		//ss2 low
  	CONFIG_MISO_ENABLE();	//Set pin MISO
  	CONFIG_MOSI_ENABLE();	//Set pin MOSI
  	CONFIG_SCLK_ENABLE();	//Set pin SCLK

}

/*Function transmit/recive byte to(from) SPI*/
/*Input data - byte  transmit				*/
/*Output - recived byte						*/
unsigned char SPId_TXRX(unsigned char data)
{
  unsigned int temp;			//
  while(SPI1STATbits.SPITBF);	//transm buffer not empty
  SPI1BUF = data; 				//send data
  while(!SPI1STATbits.SPIRBF);	//rec buffer not full
  temp = (SPI1BUF & 0xFF);		//rec data
  return (char)temp;			//
}

/**/
void SPI_write(unsigned char slave,unsigned char *data,unsigned char length) 
{
  switch(slave)
  {
	case 0:
		SLAVE1_ENABLE();		//select slave1
		break;
	case 1:
		SLAVE2_ENABLE();		//select slave2
		break;
	default:
		break;
  }
	unsigned char i=0;
	for(i=0;i<length;i++)
	{
		SPId_TXRX(*data);	//send data
		data++;				//move to next data
	}
switch(slave)
  {
	case 0:
		SLAVE1_DISABLE();	//deselect slave1
		break;
	case 1:
		SLAVE2_DISABLE();	//deselect slave2
		break;
	default:
		break;
  }
}

/**/
void SPI_read(unsigned char slave,unsigned char *data,unsigned char length) 
{
  switch(slave)
  {
	case 0:
		SLAVE1_ENABLE();		//select slave1
		break;
	case 1:
		SLAVE2_ENABLE();		//select slave2
		break;
	default:
		break;
  }
	unsigned char i=0;
	for(i=0;i<length;i++)
	{
		*data=SPId_TXRX(0x00);	//receive data
		data++;					//move to next address
	}
switch(slave)
  {
	case 0:
		SLAVE1_DISABLE();	//deselect slave1
		break;
	case 1:
		SLAVE2_DISABLE();	//deselect slave2
		break;
	default:
		break;
  }
}
