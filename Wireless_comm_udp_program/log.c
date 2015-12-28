/************************************* LOG.C **************************************/

#include "log.h"

//------------------------------------------------------------------------------------------

void logInit(char * fileName)
{
    sprintf(outputFileName, fileName);
    bzero(buffer, sizeof(buffer));
}

//------------------------------------------------------------------------------------------

void logMesg(char * message, bool printTime)
{
    FILE * fp;
    
    fp = fopen(outputFileName,"a");
    
    if (fp == NULL)
    {
        printf("Error : '%s' - File cannot be opened \n", outputFileName);
        exit(0);
    }
    
    if (printTime)
        sprintf(buffer, "Timestamp : %s \n%s", getCurrentTime(), message);
    else
        sprintf(buffer, "%s", message);
        
    //puts(buffer);
    fputs(buffer, fp);
    fclose(fp);
    
}

//------------------------------------------------------------------------------------------

void logErr(char * err)
{
    FILE * fp;
    
    fp = fopen(outputFileName,"a");
    
    if (fp == NULL)
    {
        printf("Error : '%s' - File cannot be opened \n", outputFileName);
        exit(0);
    }
    //puts(err);
    fputs(err, fp);
    fclose(fp);
    
}


//------------------------------------------------------------------------------------------

char * getCurrentTime()
{
    bzero(strTime, sizeof(strTime));
    time_t currTime;
    struct tm *ltime;
    static struct timeval tVal;
    static struct timezone tZone;

    time(&currTime);
    ltime = (struct tm *) localtime(&currTime);
    gettimeofday(&tVal, &tZone);

    strftime(strTime,40,"%d-%b-%Y %H:%M:%S",ltime);
    sprintf(strTime, "%s.%d", strTime,(int)tVal.tv_usec);
    
    return strTime;
}

//------------------------------------------------------------------------------------------

void getFileName(char nodeName, char * outFile)
{
    bzero(strTime, sizeof(strTime));
    time_t currTime;
    struct tm *ltime;
    
    time(&currTime);
    ltime = (struct tm *) localtime(&currTime);
    
    strftime(strTime, 40 , "%d.%b.%Y.%H.%M.%S", ltime);
    
    sprintf(outFile, "%c_%s.txt", nodeName, strTime);
    
}

//------------------------------------------------------------------------------------------

