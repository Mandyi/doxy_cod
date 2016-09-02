#ifndef ADCD_DRIVER
#define ADCD_DRIVER


void ADCd_Init(void); //init ADC
void ADC_Start(void); //sample and convert 2 Values from ADC
void vApplicationTickHook( void ); //tickHook 
void readADC(void);   //readADC values
#define ADC_PINS 0xFFFC  //pini actici adc=0
#define ADC_CHANNELS 0x0003 	//canalele incluse in scanare ADC
#define ADC_SCAN 0x00E0  // SSRC bit = 111 implies internal
				    	 // counter ends sampling
					     // and starts converting.
#define SAMPLE_TIME 0x0F00; 	// Sample time = 15Tad,
								// Tad = Tcy/2
#define CH_SELECT 0x0002 //channel select, any
#define INT_SET 0x0001   //Set AD1IF after every 2 samples,
					  	 //Interrupts at the completion of conversion for each 2nd sample/convert sequence
#define ON 1
#define OFF 0
#endif

