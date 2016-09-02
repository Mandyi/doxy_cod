//PROJECT DETAILS
/******************************************************************************/
/* @PROJECT : Demo */
/* @SW_RELEASE : 0001 */
/* @NAME : KEYS_task.h */
/* @PURPOSE :  */
/* @CREATED_BY : R. CHISIU */
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

#ifndef KEYS_TASK_H
#define	KEYS_TASK_H


struct KEYS_RXMessege
{
	unsigned long B_ID;
	unsigned long B1_DOWN_TIME;
	unsigned long B1_UP_TIME;
	unsigned long B2_DOWN_TIME;
	unsigned long B2_UP_TIME;  //portTickType
};

struct B1_RXMessege
{   
	unsigned int DONE : 1;
	unsigned long D_TIME;
	unsigned long U_TIME;  //portTickType
};
struct B2_RXMessege
{  
	unsigned int DONE : 1;
	unsigned long D_TIME;
	unsigned long U_TIME;  //portTickType
};




#endif

