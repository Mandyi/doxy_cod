#include "I2Cd_driver.h"
#include "MCP9808d_driver.h"

#include "FreeRTOS.h"
#include "task.h" 
#include "queue.h"
#include "semphr.h"

#define ADDRESSREAD    0x31
#define ADDRESSWRITE   0x30

float ReadTemp()
{
	unsigned char UpperByte = 0;
	unsigned char LowerByte = 0;
	float temperature = 0;
	select_i2c(1);
	i2c_init();
	i2c_start();
	I2CWrite(ADDRESSWRITE, 0x05);  //write Temperature register 
	i2c_repStart();
	UpperByte = I2CRead(ADDRESSREAD, 0); //send acknowledge
	LowerByte = I2CRead(ADDRESSREAD, 1); //send non-acknowledge
	i2c_stop();

	UpperByte &= 0x1f;                //clear flag list
	if (0x10 == (UpperByte & 0x10))   //Temp < 0
	{
		UpperByte &= 0x0f;            //clear sign bit
		temperature = 256 - ((UpperByte * 16) + (LowerByte / 16));
	}
	else
		temperature = ((UpperByte * 16) + (LowerByte / 16));
	return temperature;
}

