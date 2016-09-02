 #ifndef 		ALARMSa_task
		#define ALARMSa_task
		#define MAX_ALARMS 15
		#include "GPSd_driver.h"
		enum
		{
			STOPPED ,
			ARMED,
			INTERRUPTED,
			SEND_DATA,
			WORKING 
		};
		enum
		{
			TRIGGER_ALARMS,
			TRIGGER_DELAYED_ANSWER,
			TRIGGER_PERIODIC,
			TRIGGER_GPRS_RECALL,
			TRIGGER_MOTION,
			TRIGGER_DATACALL_OUT
		};
		#define SMS 1 
		#define GPRS (1<<1)
		#define DATACALL (1<<2)
		extern xQueueHandle xALARMS_APPLICATIONS_Queue,xALARMS_GSM_Queue,xALARMS_GSM_BACK_Queue,
			   xALARMS_GPS_Queue;
		struct _ConnectionData 
		{
			char ConnectionType;
			char tel[15];
			char text[200];
			char SMSOutTo;
		};
		typedef struct _ConnectionData t_ConnectionData;
		void vStartALARMSTasks( unsigned portBASE_TYPE uxPriority );
		enum
		{
			NO_ALARM,
			MotionOn,
			MotionOff,
			GPSFixOn,
			GPSFixOff,
			GPRSCoverageOn,
			GPRSCoverageOff,
			LowBattery,
			EmptyBattery,
			PowerSaveEnter,
			PowerSaveExit,
			MemoryFull,
			GeofenceExit,
			GeofenceEnter,
			FaultCodeAlarm,
			NormalCodeAlarm,
			DELAYED_ANSWER,
			GPRS_RECALL,
			PERIODIC,
			DATACALL_RECALL
		};
		struct _ALARM_INFO
		{
			char AlarmIndex;
			unsigned int MowerStatusCode;
			char DateTime[5];
			GPS_Data_Type Position;
			char ConnectionType;	
		};
		struct _Alarms
		{
			unsigned char ConnectionType;
			unsigned char AlarmIndex;
			unsigned int MowerStatusCode;
			char DateTime[4];
		};
		typedef struct _Alarms ALARM_Type;
		extern struct _Alarms Alarms[];
		extern char Language;
		extern char EnabledAlarms[2];
		typedef struct _ALARM_INFO ALARM_INFO_Type;	
		void ArmAlarm(char,unsigned int,char);
		void EnableAlarm(char);
		void DisableAlarm(char);
		char IsAlarmEnabled(char);
#endif

