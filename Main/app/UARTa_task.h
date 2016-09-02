#ifndef UART_TASK
#define UART_TASK


#define uartSTACK_SIZE		configMINIMAL_STACK_SIZE
#define uartTASK_DELAY		2 
#define uartTICK_RATE		configTICK_RATE_HZ/gsmTASK_DELAY
#define uartSIZE_QUEUE      300
xQueueHandle UART_coada_RX , UART_coada_TX;

void vUARTTask ( void *pvParameters );
void vStartUARTTasks( unsigned portBASE_TYPE uxPriority );


#endif

