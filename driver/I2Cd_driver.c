#include "FreeRTOS.h"
#include "task.h" 
#include "queue.h"
#include "semphr.h"

#include "SPId_driver.h"
#include "i2c.h"
#include "GPIO_INITd_driver.h"

#define DELAY          1
#define DELAY10U       0.01
#define DELAY1U        0.001
#define DELAY100U      0.1
#define RESETTIME      30

unsigned char i2cselected = 0;

void select_i2c(unsigned char i2c_select_value )   //selectarea i2c-ului
{
	if((i2c_select_value < 1) || (i2c_select_value > 3))
		return;
	else
		i2cselected = i2c_select_value;	
}

//i2cselected = ();

void i2c_init()
{
	switch (i2cselected)
	{
	case 1:   //i2c 1 selected
	{
			  SET_PIN_MODE(9, ePORTD, GPIO, 1);       //SDA1 input
			  SET_PIN_MODE(10, ePORTD, GPIO, 1);       //SCL1 input

			  I2C1CONbits.I2CEN = 0;	// Disable I2C Mode
			  vTaskDelay(DELAY10U);
			  I2C1CONbits.DISSLW = 1;	// Disable slew rate control
			  IFS1bits.MI2C1IF = 0;	    // Clear Interrupt
			  I2C1CONbits.I2CEN = 1;	// Enable I2C Mode
			  vTaskDelay(DELAY10U);
			  
			//  I2C1BRG = (int)((FCY / FSCL - FCY / 10000000) - 1); //Baud Rate Generator
			  
			  //Write zero in SCL and SDA for init
			  SET_IO_PIN(9, ePORTD, 0);   //SDA
			  SET_IO_PIN(10, ePORTD, 0);  //SCL

			  reset_i2c_bus();	 // set bus to idle
			  break;
	}
	case 2:    //i2c 2 selected
	{
			  SET_PIN_MODE(4, ePORTF, GPIO, 1);    //SDA2 input
			  SET_PIN_MODE(5, ePORTF, GPIO, 1);    //SCL2 input

			  I2C2CONbits.I2CEN = 0;	// Disable I2C Mode
			  vTaskDelay(DELAY10U);
			  I2C2CONbits.DISSLW = 1;	// Disable slew rate control
			  IFS1bits.MI2C1IF = 0;	 // Clear Interrupt
			  I2C2CONbits.I2CEN = 1;	// Enable I2C Mode
			  vTaskDelay(DELAY10U);
			 
		//	  I2C2BRG = (int)((FCY / FSCL - FCY / 10000000) - 1);  //baudrate generator register

			  //Write zero in SCL and SDA for init
			  SET_IO_PIN(4, ePORTF, 0);
			  SET_IO_PIN(5, ePORTF, 0);

			  reset_i2c_bus();	 // set bus to idle
			  break;
	}
	case 3:   //i2c 3 selected
	{
			  SET_PIN_MODE(6, ePORTE, GPIO, 1);   //SCL3 input
			  SET_PIN_MODE(7, ePORTE, GPIO, 1);   //SDA3 input

			
			  I2C3CONbits.I2CEN = 0;	// Disable I2C Mode
			  vTaskDelay(DELAY10U);
			  I2C3CONbits.DISSLW = 1;	// Disable slew rate control
			  IFS1bits.MI2C1IF = 0;	 // Clear Interrupt
			  I2C3CONbits.I2CEN = 1;	// Enable I2C Mode
			  vTaskDelay(DELAY10U);
			
		//	  I2C3BRG = (int)((FCY / FSCL - FCY / 10000000) - 1); //baudrate generator register

			  //Write zero in SCL and SDA for init
			  SET_IO_PIN(6, ePORTE, 0);
			  SET_IO_PIN(7, ePORTE, 0);

			  reset_i2c_bus();	 // set bus to idle
			  break;
	}
	default:  
			{
				break;
			}
	}
}

//Resets the I2C bus to Idle
void reset_i2c_bus()
{
    //clear buffers
	I2C2TRN = 0 ;                        
	I2C1RCV = 0 ; 
	
	switch (i2cselected)
	{
	case 1:
	{	
			  //initiate stop bit
			  I2C1CONbits.PEN = 1;

			  //wait for hardware clear of stop bit
			  vTaskDelay(DELAY10U);
			  vTaskDelay(DELAY10U);
			  I2C1CONbits.RCEN = 0;
			  IFS1bits.MI2C1IF = 0; // Clear Interrupt
			  I2C1STATbits.IWCOL = 0; //no collision
			  I2C1STATbits.BCL = 0;   //no collision has been detected
			  vTaskDelay(RESETTIME);
			  break;
	}
	case 2:
	{

			  //initiate stop bit
			  I2C2CONbits.PEN = 1;

			  //wait for hardware clear of stop bit
			  vTaskDelay(DELAY10U);
			  vTaskDelay(DELAY10U);
			  I2C2CONbits.RCEN = 0;
			  IFS1bits.MI2C1IF = 0; // Clear Interrupt
			  I2C2STATbits.IWCOL = 0; //no collision
			  I2C2STATbits.BCL = 0;   //no collision has been detected
			  vTaskDelay(RESETTIME);
			  break;
	}
	case 3:
	{
			  //initiate stop bit
			  I2C3CONbits.PEN = 1;

			  //wait for hardware clear of stop bit
			  vTaskDelay(DELAY10U);
			  vTaskDelay(DELAY10U);
			  I2C3CONbits.RCEN = 0;
			  IFS1bits.MI2C1IF = 0; // Clear Interrupt
			  I2C3STATbits.IWCOL = 0; //no collision
			  I2C3STATbits.BCL = 0;   //no collision has been detected
			  vTaskDelay(RESETTIME);
			  break;
	}
	default: 
			{
				break;
			}
	}
}

	void i2c_start()
	{
		switch (i2cselected)
		{
		case 1:
		{				 
				  I2C1CONbits.ACKDT = 0;	//Reset any previous Ack
				  vTaskDelay(DELAY);

				  I2C1CONbits.SEN = 1;	//Initiate Start condition
				  vTaskDelay(DELAY);
				  //the hardware will automatically clear Start Bit
				  //wait for automatic clear before proceding
				  vTaskDelay(DELAY10U);
				  vTaskDelay(DELAY10U);
				  break;
		}
		case 2:
		{				
				  I2C2CONbits.ACKDT = 0;	//Reset any previous Ack
				  vTaskDelay(DELAY);

				  I2C2CONbits.SEN = 1;	//Initiate Start condition
				  vTaskDelay(DELAY);
				  //the hardware will automatically clear Start Bit
				  //wait for automatic clear before proceding
				  vTaskDelay(DELAY10U);
				  vTaskDelay(DELAY10U);
				  break;
		}
		case 3:
		{
				  I2C3CONbits.ACKDT = 0;	//Reset any previous Ack
				  vTaskDelay(DELAY);

				  I2C3CONbits.SEN = 1;	//Initiate Start condition
				  vTaskDelay(1);
				  //the hardware will automatically clear Start Bit
				  //wait for automatic clear before proceding
				  vTaskDelay(DELAY10U);
				  vTaskDelay(DELAY10U);
				  break;
		}
		default: 
				{
					break;
				}
		}
	}

	void i2c_repStart()
{
		switch (i2cselected)
		{
		case 1:
		{
			  I2C1CONbits.ACKDT = 0;	//Reset any previous Ack
			  vTaskDelay(DELAY);

			  I2C1CONbits.RSEN = 1;	//Initiate Repeated Start condition
			  vTaskDelay(DELAY);
			  //the hardware will automatically clear Start Bit
			  //wait for automatic clear before proceding
			  vTaskDelay(DELAY10U);
			  vTaskDelay(DELAY10U);
			  break;
		}
		case 2:
		{
			  I2C2CONbits.ACKDT = 0;	//Reset any previous Ack
			  vTaskDelay(DELAY);

			  I2C2CONbits.RSEN = 1;	//Initiate Repeated Start condition
			  vTaskDelay(DELAY);
			  //the hardware will automatically clear Start Bit
			  //wait for automatic clear before proceding
			  vTaskDelay(DELAY10U);
			  vTaskDelay(DELAY10U);
			  break;
		}
		case 3:
		{
			  I2C3CONbits.ACKDT = 0;	//Reset any previous Ack
			  vTaskDelay(DELAY);

			  I2C3CONbits.RSEN = 1;	//Initiate Repeated Start condition
			  vTaskDelay(DELAY);
			  //the hardware will automatically clear Start Bit
			  //wait for automatic clear before proceding
			  vTaskDelay(DELAY10U);
			  vTaskDelay(DELAY10U);
			  break;
		}
		default: 
				{
					break;
				}
	}
}

	void i2c_stop()
	{
		switch (i2cselected)
		{
		case 1:
		{
				  I2C1CONbits.PEN = 1;  //Initiate Stop Condition
				  vTaskDelay(DELAY10U);     //wait for hardware clear of stop bit	
				  I2C1CONbits.RCEN = 0;     //Receive sequence is not in progress
				  IFS1bits.MI2C1IF = 0;     // Clear Interrupt
				  I2C1STATbits.IWCOL = 0;   //no collision
				  I2C1STATbits.BCL = 0;     //no bus collision
				  vTaskDelay(DELAY10U);
				  break;
		}
		case 2:
		{
				  I2C2CONbits.PEN = 1;  //Initiate Stop Condition
				  vTaskDelay(DELAY10U);     //wait for hardware clear of stop bit	
				  I2C2CONbits.RCEN = 0;     //Receive sequence is not in progress
				  IFS1bits.MI2C1IF = 0;     // Clear Interrupt
				  I2C2STATbits.IWCOL = 0;   //no collision
				  I2C2STATbits.BCL = 0;     //no bus collision
				  vTaskDelay(DELAY10U);
				  break;
		}
		case 3:
		{
				  I2C2CONbits.PEN = 1;  //Initiate Stop Condition
				  vTaskDelay(DELAY10U);     //wait for hardware clear of stop bit	
				  I2C2CONbits.RCEN = 0;     //Receive sequence is not in progress
				  IFS1bits.MI2C1IF = 0;     // Clear Interrupt
				  I2C3STATbits.IWCOL = 0;   //no collision
				  I2C3STATbits.BCL = 0;     //no bus collision
				  vTaskDelay(DELAY10U);
				  break;
		}
		default: 
				{
					break;
				}
		}
	}

	void send_i2c_byte(unsigned int data)
	{
		switch (i2cselected)
		{
		case 1:
		{
				  int i = 0;
				  while (I2C1STATbits.TBF)  {}   //wait for an completed transfer
				  IFS1bits.MI2C1IF = 0;           //clear interrupt
				  I2C1TRN = data;                  //load data byte in buffer

				  //wait for transmision
				  for (i = 0; i < 500; i++)
				  {
					  if (!I2C1STATbits.TRSTAT)   //master transmit is not in progress
						  break;
					  else  {}	
					  vTaskDelay(DELAY1U);
				  }
				  //check for acknowledge form slave,abort if not found
				  if (1 == I2C1STATbits.ACKSTAT)
					  i2c_stop();
				  else {}
				  vTaskDelay(DELAY1U);
				  vTaskDelay(DELAY1U);
				  break;
		}
		case 2:
		{
				  int i = 0;
				  while (I2C2STATbits.TBF)  {}   //wait for an completed transfer
				  IFS1bits.MI2C1IF = 0;           //clear interrupt
				  I2C2TRN = data;                  //load data byte in buffer

				  //wait for transmision
				  for (i = 0; i < 500; i++)
				  {
					  if (!I2C2STATbits.TRSTAT)   //master transmit is not in progress
						  break;
					  else {}	
					  vTaskDelay(DELAY1U);
				  }
				  //check for acknowledge form slave,abort if not found
				  if (1 == I2C2STATbits.ACKSTAT)
					  i2c_stop();
				  else {}	
				  vTaskDelay(DELAY1U);
				  vTaskDelay(DELAY1U);
				  break;
		}
		case 3:
		{
				  int i = 0;
				  while (I2C3STATbits.TBF)  {}   //wait for an completed transfer
				  IFS1bits.MI2C1IF = 0;           //clear interrupt
				  I2C3TRN = data;                  //load data byte in buffer

				  //wait for transmision
				  for (i = 0; i < 500; i++)
				  {
					  if (!I2C3STATbits.TRSTAT)   //master transmit is not in progress
						  break;
					  else {}	
					  vTaskDelay(DELAY1U);
				  }
				  //check for acknowledge form slave,abort if not found
				  if (1 == I2C3STATbits.ACKSTAT)
					  i2c_stop();
				  else {}
				  vTaskDelay(DELAY1U);
				  vTaskDelay(DELAY1U);
				  break;
		}
		default: 
				{
					break;
				}
		}
	}

	unsigned char read_i2c_byte()
	{
		unsigned char data = 0;
		switch (i2cselected)
		{
		case 1:
		{
				  int i = 0;
				  
				  //set I2C module to receive
				  I2C1CONbits.RCEN = 1;

				  //if no response, break
				  while (!I2C1STATbits.RBF)           //receive is not complete
				  {
					  i++;
					  if (i > 2000) break;
					  else {}
				  }
				  //get data from I2CRCV register
				  data = I2C1RCV;
				  //return data

				  break;
		}
		case 2:
		{
				  int i = 0;			
				  //set I2C module to receive
				  I2C2CONbits.RCEN = 1;

				  //if no response, break
				  while (!I2C2STATbits.RBF)           //receive is not complete
				  {
					  i++;
					  if (i > 2000) break;
					  else {}	
				  }
				  //get data from I2CRCV register
				  data = I2C2RCV;
				  //return data
				  break;
		}
		case 3:
		{
				  int i = 0;				 
				  //set I2C module to receive
				  I2C3CONbits.RCEN = 1;

				  //if no response, break
				  while (!I2C3STATbits.RBF)           //receive is not complete
				  {
					  i++;
					  if (i > 2000) break;
					  else {}	
				  }
				  //get data from I2CRCV register
				  data = I2C3RCV;
				  break;
		}
		default: 
				{
					break;
				}
		}
		return data;
	}

	void I2CWrite(unsigned char address, unsigned char i2cWriteData)
	{
		vTaskDelay(DELAY10U);
		send_i2c_byte(address);
		vTaskDelay(DELAY10U);
		send_i2c_byte(i2cWriteData);
		vTaskDelay(DELAY10U);
	//	reset_i2c_bus();

	}

	unsigned char I2CRead(unsigned char address, unsigned char ack)
	{
		unsigned char i2cReadData = 0;
		vTaskDelay(DELAY10U);
		send_i2c_byte(address);
		vTaskDelay(DELAY100U);
		i2cReadData = read_i2c_byte();
		vTaskDelay(DELAY10U);
		switch (i2cselected)
		{
		case 1:
		{
			  if (0 == ack)
			  {
				  I2C1CONbits.ACKDT = 0; //then transmit an ACK
			  }
			  else
			  {
				  I2C1CONbits.ACKDT = 1; //then transmit an NACK
			  }
			  break;
		}
		case 2:
		{
			  if (ack)
			  {
				  I2C2CONbits.ACKDT = 0; //then transmit an ACK
			  }
			  else
			  {
				  I2C2CONbits.ACKDT = 1; //then transmit an NACK
			  }
			  break;
		}
		case 3:
		{
			  if (ack)
			  {
				  I2C3CONbits.ACKDT = 0; //then transmit an ACK
			  }
			  else
			  {
				  I2C3CONbits.ACKDT = 1; //then transmit an NACK
			  }
			  break;
		}
		default: 
				{
					break;
				}
	}
		return i2cReadData;
	}
