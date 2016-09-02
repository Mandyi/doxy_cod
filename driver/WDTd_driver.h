/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0100 */
/* @NAME : WDTd_driver.c */
/* @PURPOSE :  */
/* @CREATED_BY : A. Capatina */
/* @CREATION_DATE : July 21 2016 */
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



/*Definirea PIN-ULUI de RESET ca fiind PIN-ul SWR al registrului RCON*/
#define RESET RCONbits.SWR

/*Prototipul functiei pentru Resetarea watchdog-ului*/
void Feed(void);


/*Functie pentru resetarea Ucontrollerului*/
void Reset(void);

/*Prototipul functiei pentru preluare semafor Adi Pop*/
int vaTask_Adi(void);
 
/*Prototipul functiei de watchdog*/
void WDT_Function(void);