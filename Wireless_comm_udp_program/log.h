/************************************* LOG.H **************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

//------------------------------------------------------------------------------------------

char outputFileName[50];
char buffer[200];
char strTime[50];

void logInit( char * fileName );

void logMesg( char * message, bool printTime );

void logErr( char * err );

char * getCurrentTime( void );

void getFileName( char nodeName, char * outFile );

//------------------------------------------------------------------------------------------

