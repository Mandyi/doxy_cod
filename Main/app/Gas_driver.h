#ifndef GAS_TASK
#define GAS_TASK

#define gasSTACK_SIZE		configMINIMAL_STACK_SIZE
#define gasTASK_DELAY 2
#define ON 1
#define OFF 0
#define VAL_PRAG 500
#define DimMax 10

void Create();
void GAS_sensor();
void StartGASTask( unsigned portBASE_TYPE uxPriority ); 

#endif
