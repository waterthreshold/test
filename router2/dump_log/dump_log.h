#ifndef __DUMP_LOG__
#define __DUMP_LOG__

#define MAX_MESSAGE_LEN_FOR_LOG		128
#define LOG_ENTRY_SIZE      192
#define MAX_LOG_NUM             1024
#define MAX_LOG_LENGTH          128
#include <sys/time.h>

typedef struct _TAG_LogData {
    struct timeval tv;
    char pBuffer[MAX_LOG_LENGTH + 1];
    int jiff;  
    int timesynced;  
    int iSendingLog; 
} LogData;



#endif