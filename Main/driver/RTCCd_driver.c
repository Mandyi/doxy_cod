/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME : ADCa_task.c */
/* @PURPOSE :  */
/* @CREATED_BY : C. Barbat */
/* @CREATION_DATE : July 05 2016 */
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

#include "RTCCd_driver.h"
#include "POWERd_driver.h"
/*_____LOCAL-DEFINE___________________________________________________________*/
/*_____LOCAL-TYPES____________________________________________________________*/
/*_____GLOBAL-DATA____________________________________________________________*/
/*_____LOCAL-DATA_____________________________________________________________*/
/*_____LOCAL-MACROS___________________________________________________________*/
/*_____LOCAL-FUNCTIONS-PROTOTYPES_____________________________________________*/
/*_____GLOBAL-FUNCTIONS_______________________________________________________*/
	


unsigned short bin2bcd(unsigned short binary_value) //Transforming from binary to bcd format
{
  unsigned short temp;
  unsigned short retval;

  temp = binary_value;
  retval = 0;

  while(1)
  {
    if(temp >= 10)
    {
      temp -= 10;
      retval += 0x10;
    }
    else
    {
      retval += temp;
      break;
    }
  }
  return(retval);
}

// Input range - 00 to 99.
unsigned short bcd2bin(unsigned short bcd_value) //Transforming from bcd to binary format
{
  unsigned short temp;

  temp = bcd_value;

  temp >>= 1;

  temp &= 0x78;

  return(temp + (temp >> 2) + (bcd_value & 0x0f));
}

void setRTCTime(unsigned char year, unsigned char month, unsigned char day, unsigned char weekday, unsigned char hour, unsigned char minute, unsigned char second)
{

    //Clock set-up
    OSCCONbits.SOSCEN = 1;  //Sec. oscillator enable
    OSCCONbits.POSCEN = 1;  //Primary oscillator enabled while in SLEEP
    OSCCONbits.NOSC0 = 0;   //Set FRC as clock source
    OSCCONbits.NOSC1 = 0;
    OSCCONbits.NOSC2 = 0;
	RCFGCALbits.RTCWREN = 1;  //Registers can be written by user

	RCFGCALbits.RTCEN = 0;  //RTCC module is disabled

	RCFGCALbits.RTCPTR = 3;  //Decrements on each set/read
	RTCVAL = bin2bcd(year); 					// Set Year
	RTCVAL = (bin2bcd(month) << 8) + bin2bcd(day);// Set Month and Day
	RTCVAL = (bin2bcd(weekday) << 8) + bin2bcd(hour); 	// Set Weekday and Hour Weekday from 0 to 6
	RTCVAL = (bin2bcd(minute) << 8) + bin2bcd(second);  // Set Minute and Second

	RCFGCALbits.RTCEN = 1;  //RTCC module is enabled

	RCFGCALbits.RTCWREN = 0; //Registers are locked
}

RTCTime getRTCTime() // Get time from RTCC
{
	RTCTime retVal;

	while(RCFGCALbits.RTCSYNC==1);  //While data valid
	{

	RCFGCALbits.RTCPTR=3;

	retVal.year = bcd2bin(RTCVAL);

	unsigned int month_date=RTCVAL;
	retVal.month = bcd2bin(month_date >> 8);
	retVal.day = bcd2bin(month_date & 0xFF);

	unsigned int wday_hour=RTCVAL;
	retVal.weekday = bcd2bin(wday_hour >> 8);
	retVal.hour = bcd2bin(wday_hour & 0xFF);

	unsigned int min_sec=RTCVAL;
	retVal.minute = bcd2bin(min_sec >> 8);
	retVal.second = bcd2bin(min_sec & 0xFF);
	}

	return retVal;
}
