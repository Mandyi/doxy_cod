#include "GPIO_INITd_driver.h"
#include "p24FJ128GB106.h"

#define pinSS1		11
#define pinSS2		12
#define pinMISO		13
#define pinMOSI		14
#define pinSCLK		15

#define CONFIG_SLAVE1_ENABLE()	SET_PIN_MODE(pinSS1,ePORTB,GPIO,OUTPUT)
#define CONFIG_SLAVE2_ENABLE()	SET_PIN_MODE(pinSS2,ePORTB,GPIO,OUTPUT)
#define CONFIG_MISO_ENABLE() 	SET_PIN_MODE(pinMISO,ePORTB,GPIO,INPUT)
#define CONFIG_MOSI_ENABLE() 	SET_PIN_MODE(pinMOSI,ePORTB,GPIO,OUTPUT)
#define CONFIG_SCLK_ENABLE() 	SET_PIN_MODE(pinSCLK,ePORTB,GPIO,INPUT)

#define SLAVE1_ENABLE()		SET_IO_PIN(pinSS1,ePORTB,0)
#define SLAVE1_DISABLE()	SET_IO_PIN(pinSS1,ePORTB,1)
#define SLAVE2_ENABLE()		SET_IO_PIN(pinSS2,ePORTB,0)
#define SLAVE2_DISABLE()	SET_IO_PIN(pinSS2,ePORTB,1)

#define SPI_MODE8_ON			SPI1CON1bits.MODE16=0
#define SPI_CKE					SPI1CON1bits.CKE=0
#define CLK_POL_ACTIVE_HIGH		SPI1CON1bits.CKP=0
#define MASTER_ENABLE_ON		SPI1CON1bits.MSTEN=1
#define PRI_PRESCAL_16_1		SPI1CON1bits.PPRE=1
#define SEC_PRESCAL_8_1			SPI1CON1bits.SPRE=0
#define ENABLE_SPI				SPI1STATbits.SPIEN =1
#define CLEAR_BUFFER			SPI1STATbits.SPIROV=0
#define RESET_SPI				SPI1STAT=0
#define CLEAR_IFLAG				IFS0bits.SPI1IF = 0
#define DISABLE_INTERRUPT		IEC0bits.SPI1IE = 0
#define ENABLE_INTERRUPT		IEC0bits.SPI1IE = 1

/*
#define SPI_MODE8_ON			SPI1CON1bits.MODE16=0b0
#define SPI_CKE					SPI1CON1bits.CKE=0b0
#define CLK_POL_ACTIVE_HIGH		SPI1CON1bits.CKP=0b0
#define MASTER_ENABLE_ON		SPI1CON1bits.MSTEN=0b1
#define PRI_PRESCAL_16_1		SPI1CON1bits.PPRE=0b01
#define SEC_PRESCAL_8_1			SPI1CON1bits.SPRE=0b000
#define ENABLE_SPI				SPI1STATbits.SPIEN =0b1
#define CLEAR_BUFFER			SPI1STATbits.SPIROV=0b0
#define RESET_SPI				SPI1STAT=0b0000000000000000
#define CLEAR_IFLAG				IFS0bits.SPI1IF = 0b0
#define DISABLE_INTERRUPT		IEC0bits.SPI1IE = 0b0
#define ENABLE_INTERRUPT		IEC0bits.SPI1IE = 0b1

#define SPI_MODE8_ON			SPI1CON1 =(SPI1CON1 & 0xfbff)
#define SPI_CKE					SPI1CON1 =(SPI1CON1 & 0xfeff)
#define CLK_POL_ACTIVE_HIGH		SPI1CON1 =(SPI1CON1 & 0xffbf)
#define MASTER_ENABLE_ON		SPI1CON1 =(SPI1CON1 | 0x0020)
#define PRI_PRESCAL_16_1		SPI1CON1bits.PPRE =0b01       
#define SEC_PRESCAL_8_1			SPI1CON1 =(SPI1CON1 & 0xfff8)
#define ENABLE_SPI				SPI1STAT =(SPI1STAT | 0x8000)
#define CLEAR_BUFFER			SPI1STAT =(SPI1STAT & 0xffdf)
#define RESET_SPI				SPI1STAT =(SPI1STAT & 0x0000) 
#define CLEAR_IFLAG				IFS0 =(IFS0 & 0xfbff)
#define DISABLE_INTERRUPT		IEC0 =(IEC0 & 0xfbff)
#define ENABLE_INTERRUPT		IEC0 =(IEC0 | 0x0400)

#define SPI_MODE8_ON			SPI1CON1 &= ~(1<<10)
#define SPI_CKE					SPI1CON1 &= ~(1<<8)
#define CLK_POL_ACTIVE_HIGH		SPI1CON1 &= ~(1<<6)
#define MASTER_ENABLE_ON		SPI1CON1 |= 1<<5
#define PRI_PRESCAL_16_1		SPI1CON1 &= ~(1<<10)//
#define SEC_PRESCAL_8_1			SPI1CON1 &= ~(1<<10)//
#define ENABLE_SPI				SPI1STAT |= 1<<15
#define CLEAR_BUFFER			SPI1STAT &= ~(1<<6)
#define RESET_SPI				SPI1STAT &= ~(1<<10)//
#define CLEAR_IFLAG				IFS0 &= ~(1<<10)
#define DISABLE_INTERRUPT		IEC0 &= ~(1<<10)
#define ENABLE_INTERRUPT		IEC0 |= 1<<10
*/


/*init mod SPI*/
void SPId_Init(void);
/*write/read to/from a slave (slave=0/1 FLASH/FRAM) data (*data) of a certain length (length)*/
void SPI_write(unsigned char slave,unsigned char *data,unsigned char length);
void SPI_read(unsigned char slave,unsigned char *data,unsigned char length);
