#ifndef RTCCD_DRIVER
#define RTCCD_DRIVER

typedef struct _RTCTime
{
	unsigned char year;
	unsigned char month;
	unsigned char day;
	unsigned char weekday; // Monday is 0, Sunday is 6
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
} RTCTime;

void setRTCTime(unsigned char year, unsigned char month, unsigned char day, unsigned char weekday, unsigned char hour, unsigned char minute, unsigned char second);
RTCTime getRTCTime();


#endif

