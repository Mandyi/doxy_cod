/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME : UARTd_driver.c */
/* @PURPOSE :  */
/* @CREATED_BY : M. Ghetu */
/* @CREATION_DATE : July 15 2016 */
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

/*_____LOCAL-DEFINE___________________________________________________________*/


/*_____LOCAL-TYPES____________________________________________________________*/


static long FCY=4000000; 
unsigned char TX_buffer[BUFF_MAX_SIZE], RX_buffer[BUFF_MAX_SIZE],TX_buffer_index=0, RX_buffer_index=0, TX_buffer_size=0, RX_buffer_size=0;
short RX_message_size=0;

/*_____GLOBAL-DATA____________________________________________________________*/
/*_____LOCAL-DATA_____________________________________________________________*/
/*_____LOCAL-MACROS___________________________________________________________*/
/*_____LOCAL-FUNCTIONS-PROTOTYPES_____________________________________________*/
/*_____GLOBAL-FUNCTIONS_______________________________________________________*/

	

	unsigned int baud_calc(enum BAUD_VALUE baud,unsigned int fcy)
   	 {
        return (unsigned int)((fcy/(baud))/16)-1;
	}



	void UARTd_Init(void)
	{	

		UART1.uxbrg = baud_calc(baud1, FCY );
		U1MODEbits.STSEL=0;     /* STSEL: Stop Bit Selection bit =0 => One Stop bit */
		U1MODEbits.PDSEL0=0;    /* PDSEL<1:0>: Parity and Data Selection bits =00 =>  8-bit data, no parity */
		U1MODEbits.PDSEL1=0;    
		U1MODEbits.BRGH=0;      /* BRGH: High Baud Rate Enable bit = 0 => Standard mode (baud clock generated from FCY/16) */
		U1MODEbits.RXINV=1;     /* RXINV: Receive Polarity Inv =1 => 1 = UxRX Idle state is 0 */
		U1MODEbits.ABAUD=0;     /* ABAUD: Auto-Baud Enable bit = 0 =>  Baud rate measurement disabled or completed */
		U1MODEbits.UARTEN=1;    /* UARTEN: UARTx Enable bit(1) = 1 => UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0> */
		// Interrupt after one RX character is recived
		IEC0bits.U1TXIE = 1; 	/* Enable UART RX interrupt */
		U1MODEbits.UARTEN = 1;  /* Enable UART */
		U1STAbits.URXISEL = 0;  /* Interrupt after one RX character is received; */
		U1STAbits.UTXEN = 1;	/* Enable UART TX */  

	}	
/* copiere din bufferul dat ca parametru in bufferul de TX */

void send_UART(unsigned char *buff, unsigned char size)
{
	unsigned char parcurgere_buffer=0;
	if (size<BUFF_MAX_SIZE)
	{
		TX_buffer[0]=0x02;
		for (parcurgere_buffer=1; parcurgere_buffer<=size; parcurgere_buffer++  )
		{
			TX_buffer[parcurgere_buffer]= buff[parcurgere_buffer];
		}
		TX_buffer[size+1]=0x03;
		TX_buffer_index=0;
		TX_buffer_size=size;
		//Enagle tx interrupt
		//Trigger tx interrupt
		IEC0bits.U1TXIE = 1;	/* Enable UART TX interrupt */
	} else 
		{
			/* do nothing */
			/* printf("Dimensiunea bufferului TX e mai mica decat a celui primit! "); */
			
		}
	
}

void recive_UART(unsigned char *buff, unsigned char size)
{
	unsigned char parcurgere_buffer=0;
	if (size<RX_message_size-1)
	{
		for (parcurgere_buffer=0; parcurgere_buffer<size; parcurgere_buffer++  )
		{
			buff[parcurgere_buffer]= RX_buffer[parcurgere_buffer];
		}
	
	} else 
		{
			/* do nothing */
			/* printf("Dimensiunea mesajului e mai mica decat size! "); */
			
		}
	
}


void __attribute__((__interrupt__)) _U1TXInterrupt(void )
{
	U1TXREG = TX_buffer[TX_buffer_index];
	TX_buffer_index++;
	if (TX_buffer_index> (BUFF_MAX_SIZE-1))
		{
			/* printf("Bufferul este plin"); */
			IEC0bits.U1TXIE = 0;	/* Disable UART TX interrupt */	
			 
		}
	IFS0bits.U1TXIF = 0; // Clear TX Interrupt flag
}


void __attribute__((__interrupt__)) _U1RXInterrupt(void )
{
	char ReceivedChar=0,trimite=0;

	/* Get the data */
	if(U1STAbits.URXDA == 1)
		{
			ReceivedChar = U1RXREG;
			if (ReceivedChar==0x02)
			{
				trimite=1;
				RX_buffer[0]=0x02;
				
			} else
			{
				if (ReceivedChar==0x03)
			{
				trimite=0;
				RX_buffer[RX_buffer_index]=0x03;
				RX_message_size=RX_buffer_index;
				RX_buffer_index=0;
				
				
			}  else
				{
					if (trimite==1)
					{
						RX_buffer[RX_buffer_index]=ReceivedChar;

					}
				}
			}
			RX_buffer_index++;
		}
	

	IFS0bits.U1RXIF = 0; // Clear RX Interrupt flag

}
