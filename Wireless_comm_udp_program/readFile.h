/*************************************** READFILE.H ****************************************/

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#include "spanningTree.h"
#include "log.h"

//------------------------------------------------------------------------------------------

#define SPAN_TREE_MESG_TYPE 0
#define QURY_TEMP_MESG_TYPE 1
#define RPLY_TEMP_MESG_TYPE 2
#define NODE_TERM_MESG_TYPE 3

#define QURY_MIN_TEMP "MIN"
#define QURY_AVG_TEMP "AVG"
#define QURY_MAX_TEMP "MAX"
#define TERM_MESG "EXIT"

//------------------------------------------------------------------------------------------

struct nodeDetails
{
   char nodeName;
   int  X;
   int  Y;
   char ipAddress[50];
   int  port;
   int  temp;
   int  radius;
   int  isSink;
} ; 

struct mesgStruct
{
    int  mesgType;
    char sourceNodeName;
    char message[200];
};

const char * rProgramIdentity = "readFile";

const char * nodeDelimeter = "|";
const char * childDelimeter = ":";

int    maxSize       ;
int    childCount    ;
int    neighborCount ;
int    gSocketDescriptor;


char   myParent              ;
char * childArray            ;
char * neighborArray         ;
char   spanningTreeMesg[200] ;
char   replyMode[10]         ;
char   printText[200]        ;

bool spanningTreeCalculation = false;

struct nodeDetails *  myNode    ;
struct nodeDetails ** nodeArray ;

void fileRead( char * fileName );

void calcAdjacencyMatrix( int ** adjMatrix );

int  dist( struct nodeDetails * a
          ,struct nodeDetails * b );

bool getNode( struct nodeDetails * inNode );

void getSpanningTreeMesg( int ** graph
                         ,int * parent );

void processTreeInfo( char input[]
                     ,char myNodeName
                     ,char * output
                     ,bool isFirstNode );

void calcNeighbourNode( int ** adjMatrix );

void startConnection( void );

void broadcastMessage( char * inputMessage
                      ,int mesgType);

void startReciever( void );

void showMenu( void );

bool isChild( char inNodeName );

bool isPresent( struct mesgStruct * mesgArray
               ,int  mesgCount
               ,const char nodeName );

void calcTemperature( struct mesgStruct mesgArr[]
                     ,char * output);

void throwError( const char * iProgramIdentity
                ,const char * iErrorDescription ) ;


//------------------------------------------------------------------------------------------

