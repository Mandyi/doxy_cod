
#ifndef FRAMD_DRIVER
#define FRAMD_DRIVER

#define WREN 0x06 \* Fujitsu MB85RS64V op codes*\
#define RDSR 0x05
#define READ 0x03
#define WRITE 0x02
#define FIRE_ALARM 1
#define SMOKE_ALARM 2
unsigned int WriteFram(int);
unsigned int ReadFram(int);
void WriteByte(char ,short int, char);
long int ReadByte();
#endif
