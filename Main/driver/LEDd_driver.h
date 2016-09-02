#ifndef LEDD_DRIVER
#define LEDD_DRIVER
//includ header-ul pentru preluarea functiilor de setare a pinilor
//#include "GPIO_INITd_driver.h"
//pin 0 LED Verde
#define PIN_LED_GREEN PIN0
//pin 1 LED Rosu
#define PIN_LED_RED PIN1
//valoare maxima ADC
#define ADC_MAX_VALUE 1023
//frecenta oscilator 8MHz
#define _XTAL_FREQ 8000000

//functie de preluat semafor
void ReceiveSemaphore_LED( void * pvParameters );
//functie de preluat coada
void vReceive_GAS_VALUE(void);
//functie de blink LED Rosu
unsigned char LED(unsigned short ADC_fum);


#endif


