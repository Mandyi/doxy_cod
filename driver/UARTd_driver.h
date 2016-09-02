#ifndef UARTD_DRIVER
#define UARTD_DRIVER


/*_____LOCAL-DEFINE___________________________________________________________*/

#define STOP 0x03
#define START 0x02
#define BUFF_MAX_SIZE 100

/*_____LOCAL-TYPES____________________________________________________________*/
typedef enum BAUD_VALUE {
    baud1=19200,
    baud2=38400,
    baud3=57600,
    baud4=115200
     };
typedef unsigned char u_char;
typedef unsigned int u_int;

/*_____LOCAL-FUNCTIONS____________________________________________________________*/

unsigned int baud_calc(enum BAUD_VALUE baud,unsigned int fcy);
void UARTd_Init(void);
void send_UART(u_char *buff, u_char size);
void recive_UART(u_char *buff, u_char size);


#endif
