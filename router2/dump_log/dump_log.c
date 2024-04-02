#include "dump_log.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <fcntl.h> 

#include <time.h>


int constructLogcontent(char *content) {
    LogData *logContent;
    int rc;
    int loop;
    struct tm tLocaltime;
    struct tm *pLocaltime = &tLocaltime;
    char timeBuf[50];
    int file_desc;
    /* Foxconn add start, Max Ding, 07/07/2009 */
    int iLen = 0;
    int iTimeLen = 0;
    int iLenRight = 0;
    char tmpBuf[MAX_MESSAGE_LEN_FOR_LOG+2] = "";
    char logEntry[MAX_MESSAGE_LEN_FOR_LOG+2] = "";
    /* Foxconn add end, Max Ding, 07/07/2009 */

    file_desc = open("/dev/aglog", O_RDWR);
    if (file_desc < 0) {
        printf("Can't open device file: /dev/aglog\n");
        return -1;
    }

    logContent = (LogData *) (calloc(1, sizeof(LogData) * MAX_LOG_NUM));
    if (logContent == NULL) {
        close(file_desc);
        printf("Can't open device file: /dev/aglog\n");
        return -1	;
    }

    rc = read(file_desc, logContent, sizeof(LogData) * MAX_LOG_NUM);
	

   
	memset (content,0,LOG_ENTRY_SIZE * MAX_LOG_NUM);
    for (loop = 0; loop <= rc; loop++) {
        localtime_r(&((logContent+loop)->tv.tv_sec), pLocaltime);
        snprintf(timeBuf, sizeof(timeBuf), " %s, %s %02d,%04d %02d:%02d:%02d",  
                 (!pLocaltime->tm_wday) ? "Sunday" :
                 (pLocaltime->tm_wday == 1) ? "Monday" :
                 (pLocaltime->tm_wday == 2) ? "Tuesday" :
                 (pLocaltime->tm_wday == 3) ? "Wednesday" :
                 (pLocaltime->tm_wday == 4) ? "Thursday" :
                 (pLocaltime->tm_wday == 5) ? "Friday" : "Saturday",
                 (!pLocaltime->tm_mon) ? "Jan" :
                 (pLocaltime->tm_mon == 1) ? "Feb" :
                 (pLocaltime->tm_mon == 2) ? "Mar" :
                 (pLocaltime->tm_mon == 3) ? "Apr" :
                 (pLocaltime->tm_mon == 4) ? "May" :
                 (pLocaltime->tm_mon == 5) ? "Jun" :
                 (pLocaltime->tm_mon == 6) ? "Jul" :
                 (pLocaltime->tm_mon == 7) ? "Aug" :
                 (pLocaltime->tm_mon == 8) ? "Sep" :
                 (pLocaltime->tm_mon == 9) ? "Oct" :
                 (pLocaltime->tm_mon == 10) ? "Nov" : "Dec",
                 pLocaltime->tm_mday,
                 pLocaltime->tm_year + 1900,
                 pLocaltime->tm_hour, pLocaltime->tm_min, pLocaltime->tm_sec);

      
        strncpy(logEntry, (logContent+loop)->pBuffer, MAX_MESSAGE_LEN_FOR_LOG - 1);
        logEntry[MAX_MESSAGE_LEN_FOR_LOG] = '\0';
        iLen = strlen(logEntry);
        iTimeLen = strlen(timeBuf);
 

       
        if (time(0) > 0x47302D4E) {
            if (iLen + iTimeLen > MAX_MESSAGE_LEN_FOR_LOG) {
            
#define DDNS_HOSTNAME_KEYWORD " registration"
                char *pTemp = NULL;
                if (((0 == strncmp("[Site", logEntry, sizeof("[Site") - 1))
                        && (NULL != (pTemp = strrchr(logEntry, ']'))))
                        || ((0 == strncmp("[Dynamic DNS]", logEntry, sizeof("[Dynamic DNS]") - 1))
                            && (NULL != (pTemp = strstr(logEntry, DDNS_HOSTNAME_KEYWORD))))
                   )
                  
                {
                    strcpy(tmpBuf, pTemp);
                    iLenRight = strlen(tmpBuf);
                    logEntry[MAX_MESSAGE_LEN_FOR_LOG-iTimeLen-iLenRight-3] = '\0';
                    strcat(logEntry, "...");
                    strcat(logEntry, tmpBuf);
                } else{
                    logEntry[MAX_MESSAGE_LEN_FOR_LOG-iTimeLen] = '\0';
				
				}
            }
		
			if (strlen (logEntry)<=0)
			{
				continue;
			}
            strcat(content, logEntry);
            strcat(content, timeBuf);
            strcat(content, "\n");
        } else {
            if (iLen > 0) {
                if (*(logEntry+iLen-1) == ',') {
                    *(logEntry+iLen-1) = '.';
                    strcat(logEntry, "\n");
                } else
                    strcat(logEntry, "\n");
            }
            strcat(content, logEntry);
        }
       
    }

    close(file_desc);
    free(logContent);

    return 1;
}
int main(int argc, char* argv[])
{
    char* content = NULL;
    
    content = (char *)calloc(1, LOG_ENTRY_SIZE * MAX_LOG_NUM);
    constructLogcontent(content);
    printf(content);
    free(content);

    return 0;
}