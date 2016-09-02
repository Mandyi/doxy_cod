#ifndef I2C_DRIVER
#define I2C_DRIVER

void i2c_init(void);  //initialization function
void i2c_start(void); //start condition
void i2c_repStart(void); //repeat start condition
void i2c_stop(void);     //stop condition
void send_i2c_byte(unsigned int data);  //send a byte
unsigned char read_i2c_byte(void);            //read a byte
void I2CWrite(unsigned char address, unsigned char i2cWriteData);   //WRITE function
unsigned char I2CRead(unsigned char address, unsigned char ack);    //READ function
void reset_i2c_bus(void); //reset function
void select_i2c(unsigned char i2c_select_value );   //I2c selected function


enum I2C_Modul
{
	I2C1 = 1,
	I2C2 = 2,
	I2C3 = 3

}; 
enum ACK
{
	ack = 0,
	nack = 1
};


#endif
 
