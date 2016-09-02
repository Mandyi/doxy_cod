/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME : FRAMd_driver.c */
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
#include "Gas_driver"
#include "RTCCd_driver.h"
#include "SPId_driver.h"
#include "FRAMd_driver.h"
#include "EEPROM25d_driver.h"
#include "MSd_driver.h"
#include "ADCa_task.h"
/*_____LOCAL-DEFINE___________________________________________________________*/
#define MAX 4
/*_____LOCAL-TYPES____________________________________________________________*/
/*_____GLOBAL-DATA____________________________________________________________*/
char Transm[MAX]={0};
//char var=2;
/*_____LOCAL-DATA_____________________________________________________________*/
/*_____LOCAL-MACROS___________________________________________________________*/
/*_____LOCAL-FUNCTIONS-PROTOTYPES_____________________________________________*/
/*_____GLOBAL-FUNCTIONS_______________________________________________________*/
void WriteByte(char Op_code, short int Addr,char Data)
{
short int temp=Addr;
Transm[0]=Op_code;
temp=Addr>>8;
Transm[1]=(char)temp;
Transm[2]=(char)Addr;
Transm[3]=Data;
}
long int ReadByte()
{
long int temp=0;
temp=Transm[0];
temp<<=8;
temp|=Transm[1];
temp<<=8;
temp|=Transm[2];
return temp;
}
RTCTime Dates;
Dates= getRTCTime();
short int address=0x00;
while(address<0x3E8)
{
if(Semaph_FRAM==1+
){
WriteByte(WRITE,address,FIRE_ALARM);
SPI_SEND(0,Transm,4);
++address;
WriteByte(WRITE,address,Dates.year);
SPI_SEND(0,Transm,4);
++address;
WriteByte(WRITE,address,Dates.month);
SPI_SEND(0,Transm,4);
++address;
WriteByte(WRITE,address,Dates.day);
SPI_SEND(0,Transm,4);
++address;
WriteByte(WRITE,address,Dates.weekday);
SPI_SEND(0,Transm,4);
++address;
WriteByte(WRITE,address,Dates.hour);
SPI_SEND(0,Transm,4);
++address;
WriteByte(WRITE,address,Dates.minute);
SPI_SEND(0,Transm,4);
++address;
WriteByte(WRITE,address,Dates.second);
SPI_SEND(0,Transm,4);
++address;
}
}
