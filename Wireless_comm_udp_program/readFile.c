/*************************************** READFILE.C ****************************************/

#include "readFile.h"

//------------------------------------------------------------------------------------------

int main(int argc, char ** argv)
{
    int ** adjacencyMatrix;
    int i = 0;
    
    if (argc != 3)
    {
        printf("\nUsage : %s Node_Name File_Name\n", argv[0]);
        printf("Example : %s A Topology.txt\n\n", argv[0]);
        return 0;
    }
    
    myNode = (struct nodeDetails * )malloc(sizeof(struct nodeDetails));

    myNode->nodeName = argv[1][0];
    
    char * fileName = argv[2];
    
    char outFile[50];
    getFileName(myNode->nodeName, outFile);
    logInit(outFile);
    
    sprintf( printText
            ,"Node Name : %c\nFile Name : %s\n"
            ,myNode->nodeName
            ,outFile);
    
    logMesg(printText, false);

    //Pointer to a array of pointers and get the maximum size if array in an integer maxSize
    nodeArray = (struct nodeDetails ** )malloc(sizeof(struct nodeDetails *) * 50);
    
    fileRead(fileName);            //Read the file and populate Array
    
    sprintf(printText, "Size of Array populated is : %d\n",maxSize);
    logMesg(printText, false);
    
    childArray = (char *)malloc(sizeof(char) * maxSize);
    childCount = 0;
    
    neighborArray = (char *)malloc(sizeof(char) * maxSize);
    neighborCount = 0;
    
    adjacencyMatrix = (int **) malloc(sizeof(int *) * maxSize);
    for (i = 0; i < maxSize; i++)
        adjacencyMatrix[i] = (int *) malloc (sizeof(int) * maxSize);
    
    calcAdjacencyMatrix(adjacencyMatrix);
    
    sprintf(printText,"Adjacency Matrix Calculation done \n");
    logMesg(printText, false);
    
    if (getNode(myNode) == false)
    {
        throwError(rProgramIdentity, "Node not present in Array\n");
    }
    
    calcNeighbourNode(adjacencyMatrix);
    
    if (myNode->isSink == 1)
    {
        int * parentArray = (int *)malloc(sizeof(int) * maxSize);
        calcSpanningTree(adjacencyMatrix, maxSize, parentArray);
    
        getSpanningTreeMesg(adjacencyMatrix, parentArray);
        
        spanningTreeCalculation = true;
        
        free(parentArray);
    }
    
    startConnection();
    
    
    
    
    // Always at the end of main
    free(adjacencyMatrix);
    free(myNode);
    free(nodeArray);
    
    return 0;
}

//------------------------------------------------------------------------------------------

void fileRead(char * fileName)
{
    FILE * f1;
    char   read;
    int    i, y, count;
    
    f1 = fopen(fileName,"r");
    
    if (f1 == NULL)
    {
        sprintf(printText, "Error : '%s' - File cannot be read \n", fileName);
        logMesg(printText, false);
        exit(0);
    }
    
    struct nodeDetails * node = (struct nodeDetails * )malloc(sizeof(struct nodeDetails));
    
    char temp[50];
    i=0, y = 0, count = 0;
    
    while((read=getc(f1)) != EOF)
    {
        if (read == ',')
        {
            switch(i)
            {
                case 0:
                    node->nodeName = temp[0];
                    break;
                case 1:
                    node->X = atoi(temp);
                    break;
                case 2:
                    node->Y = atoi(temp);
                    break;
                case 3:
                {
                    char * p = strchr(temp, '/');
                    *p = '\0';
                    sprintf(node->ipAddress,temp+1);
                    node->port = atoi(p + 1);
                    break;
                }
                case 4:
                    node->temp = atoi(temp);
                    break;
                case 5:
                    node->radius = atoi(temp);
                    break;
                case 6:
                    node->isSink = atoi(temp);
                    break;
            }
            i++;
            bzero(temp, sizeof(temp));
            y = 0;
        }
        else if (read == '\r')
        {
            node->isSink = atoi(temp);
            read=getc(f1);
            if (read == '\n')
            {
                nodeArray[count] = node; //Array of nodes
                
                if ((node->isSink == 1) && (count != 0))
                {
                    nodeArray[count] = nodeArray[0];
                    nodeArray[0] = node;
                }

                count++;
                
                i = 0, y = 0;
                bzero(temp, sizeof(temp));
                node = (struct nodeDetails * )malloc(sizeof(struct nodeDetails));
            }
        }   
        else
        {
            temp[y] = read;
            y++;
        }
    }
    
    fclose(f1);
    maxSize = count;
    
    /** Printing the info populated in array
    for (i = 0; i < count; i++)
    {
        struct nodeDetails * n = nodeArray[i];
        
        printf("Node : %c, %d, %d, %s, %d, %d, %d, %d\n", 
                    n->nodeName, 
                    n->X, 
                    n->Y, 
                    n->ipAddress,
                    n->port,
                    n->temp, 
                    n->radius, 
                    n->isSink);
    }*/
}

//------------------------------------------------------------------------------------------

void calcAdjacencyMatrix(int ** adjMatrix)
{
    int i,j;
    struct nodeDetails * nodeA, * nodeB;

    for (i = 0; i < maxSize; i++)
    {
        nodeA = nodeArray[i];
        for (j = 0; j < maxSize; j++)
        {
            nodeB =  nodeArray[j];
            int val = dist(nodeA, nodeB);
            if (val > nodeA->radius)
                val = 0;
            adjMatrix[i][j] = val ;
        }
    }

    /** Printing the adjacency matrix
    for (i = 0; i < maxSize; i++)
    {
        for (j = 0; j < maxSize; j++)
        {
            printf("%d  ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\n\n==============================\n\n" );
    */
}

//------------------------------------------------------------------------------------------

int dist(struct nodeDetails * a, struct nodeDetails * b)
{
    return ceil(sqrt(pow(a->X - b->X,2) + pow(a->Y - b->Y,2)));
}

//------------------------------------------------------------------------------------------

bool getNode(struct nodeDetails * inNode)
{
    int count;
    bool result = false;
    for (count  = 0; count < maxSize; count++)
    {
        if (nodeArray[count]->nodeName == inNode->nodeName)
        {
            *inNode = *nodeArray[count];
            result = true;
            break;
        }
    }
    return result;
}


//------------------------------------------------------------------------------------------

void getSpanningTreeMesg(int ** graph, int * parent)
{
    int i,p,c;
    
    /** Printing Parent array and the Edge Weights
    printf("\n\nParents Are : ");
    for (i = 1; i < maxSize; i++)
    {
        printf("%c, ", nodeArray[parent[i]]->nodeName);
    }*/
    
    sprintf(printText, "\n\nEdge Weights of computed Spanning Tree: \n");
    logMesg(printText, false);
    
    bzero(printText, sizeof(printText));
    
    for (i = 1; i < maxSize; i++)
    {
        sprintf( printText
                ,"%s%c - %c\t%d \n"
                ,printText
                ,nodeArray[parent[i]]->nodeName
                ,nodeArray[i]->nodeName
                ,graph[i][parent[i]] );
    }
    
    logMesg(printText, false);
    
    sprintf(printText, "\n\nForming Data Dissemination message : \n");
    logMesg(printText, false);
    
    int count = 0;
    char in[200];
    char * input = in;
    char str[100];
    char * temp = str;
    bzero(input, sizeof(input));
    
    for (p = 1; p < maxSize; p++)
    {
         sprintf(temp, "%c,%c,", nodeArray[p]->nodeName, nodeArray[parent[p]]->nodeName);
         
        for (c = 1 ; c < maxSize; c++)
        {
            if ( nodeArray[p]->nodeName == nodeArray[parent[c]]->nodeName)
            {
                strncat(temp, &nodeArray[c]->nodeName, 1);
                strcat(temp, childDelimeter);
                count++;
            }
        }
        
        strncat(input, temp, strlen(temp)-1);
        
        strcat(input, nodeDelimeter);
        count = 0;
        bzero(temp, sizeof(temp));
    }
    
    sprintf(spanningTreeMesg, input);
    sprintf(printText, "%s\n", spanningTreeMesg);
    logMesg(printText, false);
    
}

//------------------------------------------------------------------------------------------

void processTreeInfo(char input[], char myNodeName, char * output, bool isFirstNode)
{
    int i,j,c = 0;
    char inputLine[200], child[maxSize];
    char * in, * token;
    
    sprintf(inputLine, input);
    in = inputLine;
    token = strchr(in, nodeDelimeter[0]);
    *token = '\0';
    
    while (token != NULL)
    {
        if (in[0] == myNodeName)
        {
            if (isFirstNode == true)
                myParent = in[2];
                
            for (i = 4; i < strlen(in); i++)
            {
                if (in[i] != childDelimeter[0])
                {
                    child[c] = in[i];
                    c++;
                }
            }
            
            if (isFirstNode == false)
            {
                strcat(output, in);
                strcat(output, nodeDelimeter);
            }
            break;
        }
        in = token + 1;
        token = strchr(in, nodeDelimeter[0]);
        if ( token != NULL )
            *token = '\0';
    }
    
    for ( j = 0; j < c; j++ )
    {
        if (isFirstNode == true)
        {
            childArray[j] = child[j];
            childCount = c;
        }
        /** Changed for topology file 3
        processTreeInfo(token + 1, child[j], output, false);
        */
        processTreeInfo(input, child[j], output, false);
    }
}

//------------------------------------------------------------------------------------------

void calcNeighbourNode(int ** adjMatrix)
{
    int i,j;
    
    for (i=0;i<maxSize; i++)
    {
        if (nodeArray[i]->nodeName == myNode->nodeName)
        {
            for (j=0;j<maxSize; j++)
            {
                if (adjMatrix[i][j] > 0)
                {
                    neighborArray[neighborCount] = nodeArray[j]->nodeName;
                    neighborCount++;
                    if (myNode->isSink == 1)
                    {
                        childArray[childCount] = nodeArray[j]->nodeName;
                        childCount++;
                    }
                }
            }
        }
    }
    
    sprintf(printText, "My Neighbours are : \n");
    logMesg(printText, false);
    bzero(printText, sizeof(printText));
    for (i=0; i< neighborCount;i++)
        sprintf(printText, "%s%c, ", printText, neighborArray[i]);
    
    logMesg(printText, false);
}

//------------------------------------------------------------------------------------------

void startConnection()
{
    int                 listenSocketDescriptor ;
    struct sockaddr_in  serverAddress         ;
    
    int  socketOptionYes = 1;
                        
    if ( (listenSocketDescriptor = socket(AF_INET, SOCK_DGRAM, 0) ) < 0 )
        throwError( rProgramIdentity, "Error -->> Socket creation") ;
    
    if ( setsockopt( listenSocketDescriptor
                  ,SOL_SOCKET 
                  ,SO_REUSEADDR
                  ,& socketOptionYes
                  ,sizeof(int)) < 0 )
        throwError(rProgramIdentity, "Error -->> Setting options for socket");
    
    /* Configuring Server Address Structure */
    bzero( & serverAddress, sizeof(serverAddress) )  ;

    serverAddress.sin_family      = AF_INET               ;
    serverAddress.sin_addr.s_addr = htonl( INADDR_ANY )   ;
    serverAddress.sin_port        = htons( myNode->port ) ;

    /* Binding the Socket to the given Service Port */
    if ( bind( listenSocketDescriptor
              ,(struct sockaddr*) & serverAddress
              ,sizeof(serverAddress) ) < 0 )
      throwError( rProgramIdentity, "Error -->> Binding port") ;

    logMesg("\nInitialization socket done...\n", false);
    
    gSocketDescriptor = listenSocketDescriptor;
    
    if (myNode->isSink == 1)
    {
        broadcastMessage(spanningTreeMesg, SPAN_TREE_MESG_TYPE);
        showMenu( );
    }
    else
        startReciever( );
    
}

//------------------------------------------------------------------------------------------

void broadcastMessage(char * inputMessage, int mesgType)
{
    struct sockaddr_in clientAddress       ;
    socklen_t          clientAddressLength ;
    
    int i;
    
    struct nodeDetails * tempNode = (struct nodeDetails *)malloc(sizeof(struct nodeDetails));
    struct mesgStruct  * outMesg  = (struct mesgStruct *)malloc(sizeof(struct mesgStruct));
    
    //logMesg("Sending data to neighbours....\n", false);
    
    clientAddressLength = sizeof(clientAddress);
    
    sprintf(printText, "Sending Broadcast Message....\nData : '%s'\n", inputMessage);
    logMesg(printText, false);
    
    for (i = 0; i < neighborCount; i++)
    {
        bzero(buffer, sizeof(buffer));
        tempNode->nodeName = neighborArray[i];
        if (getNode(tempNode) == false)
            throwError(rProgramIdentity, "Neighbour node does not exist");
        
        clientAddress.sin_family      = AF_INET                 ;
        clientAddress.sin_port        = htons( tempNode->port ) ;
        
        /** Check if the ip address is localhost then use INADDR_ANY */
        if (strcmp(tempNode->ipAddress, "localhost") == 0)
            clientAddress.sin_addr.s_addr = htonl( INADDR_ANY );
        else
            clientAddress.sin_addr.s_addr = inet_addr( tempNode->ipAddress ) ;
        
        /** Populate Message structure from the data*/
        outMesg->mesgType = mesgType;
        outMesg->sourceNodeName = myNode->nodeName;
        sprintf(outMesg->message, inputMessage);
        
        if ( sendto(gSocketDescriptor, 
                    outMesg, 
                    sizeof(*outMesg),
                    0,
                    (struct sockaddr *) & clientAddress,
                    clientAddressLength) < 0)
        {
            throwError(rProgramIdentity, "Error Sending data in broadcastMessage function");
        }
        else
        {
            sprintf(printText, "Broadcast sent to node '%c' with ip addr '%s:%d'\n\n"
                   ,tempNode->nodeName
                   ,tempNode->ipAddress
                   ,tempNode->port);
            logMesg(printText, true);
        }
    }
    
    free(tempNode);
    free(outMesg);
}

//------------------------------------------------------------------------------------------

void startReciever( )
{
    struct sockaddr_in clientAddress       ;
    socklen_t          clientAddressLength ;
    
    int recvCount = 0;
    char broadcastChildMesg[200];
    char buffer[200];
    char * nodePtr = NULL;
    struct mesgStruct * mesgArray;
    
    if (myNode->isSink == 1)
        mesgArray = (struct mesgStruct *)malloc(sizeof(struct mesgStruct) * childCount);
    
    bzero(broadcastChildMesg, sizeof(broadcastChildMesg));
    
    bzero(buffer, sizeof(buffer));
    
    struct mesgStruct * inMesg  = (struct mesgStruct *)malloc(sizeof(struct mesgStruct));
    
    clientAddressLength = sizeof(clientAddress);
    
    while(true)
    {
        sprintf(printText, "Waiting for message....\n\n");
        logMesg(printText, false);
        bzero(inMesg, sizeof(*inMesg));
        if ( recvfrom( gSocketDescriptor
                      ,inMesg
                      ,sizeof(*inMesg)
                      ,0
                      ,(struct sockaddr *) & clientAddress
                      ,& clientAddressLength ) < 0 )
        {
            throwError(rProgramIdentity, "Error Receiving data in startReciever function");
        }
        else
        {
            sprintf(printText, "Message Received -> Mesg_Type : %d\tSource : '%c'\tMessage : %s\n"
                    , inMesg->mesgType
                    , inMesg->sourceNodeName
                    , inMesg->message);
            logMesg(printText, true);
            
            if (inMesg->mesgType == SPAN_TREE_MESG_TYPE)
            {
                if (spanningTreeCalculation == true)
                {
                    sprintf(printText, "Message Status   -> Ignored(Spanning Tree computation is already over)\n\n");
                    logMesg(printText, false);
                    continue;
                }
                
                nodePtr = strchr(inMesg->message, myNode->nodeName);
                
                if (nodePtr != NULL)
                {
                    sprintf(printText, "Message Status   -> Processed\n\n");
                    logMesg(printText, false);
                    
                    processTreeInfo(inMesg->message, myNode->nodeName, broadcastChildMesg, true);
                    spanningTreeCalculation = true;
                    mesgArray = (struct mesgStruct *)malloc(sizeof(struct mesgStruct) * childCount);
                    if (childCount > 0)
                        broadcastMessage(broadcastChildMesg, SPAN_TREE_MESG_TYPE);
                }
            }
            else if (inMesg->mesgType == QURY_TEMP_MESG_TYPE)
            {
                if (inMesg->sourceNodeName != myParent)
                {
                    sprintf(printText, "Message Status   -> Ignored(Query Request not from Parent Node)\n\n");
                    logMesg(printText, false);
                    continue;
                }
                
                if (strcmp(replyMode, "") != 0)
                {
                    sprintf(printText, "Message Status   -> Ignored(Duplicate Query Request)\n\n");
                    logMesg(printText, false);
                    continue;
                }
                
                sprintf(printText, "Message Status   -> Processed\n\n");
                logMesg(printText, false);
                
                if (childCount > 0)
                {
                    broadcastMessage(inMesg->message, inMesg->mesgType);
                    
                    if (strcmp(inMesg->message,QURY_MIN_TEMP) == 0)
                        sprintf(replyMode, QURY_MIN_TEMP);
                    else if(strcmp(inMesg->message,QURY_AVG_TEMP) == 0)
                        sprintf(replyMode, QURY_AVG_TEMP);
                    else if(strcmp(inMesg->message,QURY_MAX_TEMP) == 0)
                        sprintf(replyMode, QURY_MAX_TEMP);
                }
                else
                {
                    calcTemperature(mesgArray, buffer);
                    broadcastMessage(buffer, RPLY_TEMP_MESG_TYPE);
                    bzero(replyMode, sizeof(replyMode));
                }
            }
            else if (inMesg->mesgType == RPLY_TEMP_MESG_TYPE)
            {
                if (strcmp(replyMode, "") == 0)
                {
                    sprintf(printText, "Message Status   -> Ignored(Reply not expected)\n\n");
                    logMesg(printText, false);
                    continue;
                }
                else if (isChild(inMesg->sourceNodeName))
                {
                    if (isPresent(mesgArray, recvCount, inMesg->sourceNodeName) == false)
                    {
                        mesgArray[recvCount] = *inMesg;
                        recvCount++;
                        
                        sprintf(printText, "Message Status   -> Processed\n\n");
                        logMesg(printText, false);
                    }
                    else
                    {
                        sprintf(printText, "Message Status   -> Ignored (Duplicate response)\n\n");
                        logMesg(printText, false);
                    }
                }
                else
                {
                    sprintf(printText, "Message Status   -> Ignored(Reply Source not a child)\n\n");
                    logMesg(printText, false);
                    continue;
                }

                if (recvCount == childCount)
                {
                    calcTemperature(mesgArray, buffer);
                    if (myNode->isSink == 0)
                        broadcastMessage(buffer, RPLY_TEMP_MESG_TYPE);
                    else
                    {
                        sprintf(printText, "\nThe output of %s temperature is : %s\n\n\n", replyMode, buffer);
                        printf("%s", printText);
                        logMesg(printText, true);
                    }
                    
                    bzero(replyMode, sizeof(replyMode));
                    recvCount = 0;
                    bzero(mesgArray, sizeof(mesgArray));
                    
                    if (myNode->isSink == 1)
                        break;
                }
            }
            else if (inMesg->mesgType == NODE_TERM_MESG_TYPE)
            {
                sprintf(printText, "Message Status   -> Processed\n\n");
                logMesg(printText, false);
                
                broadcastMessage(TERM_MESG, NODE_TERM_MESG_TYPE);
                
                if (mesgArray != NULL)
                    free(mesgArray);
                
                break;
            }
        }
    }
    
    free(inMesg);
}

//------------------------------------------------------------------------------------------

void showMenu( )
{
    bool finish = false;
    while (finish == false)
    {
        int option = 0;
        char opt[10];
        
        printf("**************************************************\n");
        printf("*************  Broadcast Query Menu  *************\n");
        printf("**************************************************\n\n");
        printf("1. Collect Minimum Temperature\n");
        printf("2. Collect Average Temperature\n");
        printf("3. Collect Maximum Temperature\n");
        printf("4. Resend Spanning Tree Message\n");
        printf("5. Exit & Send Exit to All other running nodes \n\n");
        printf("Enter Option : ");
        scanf("%s", opt);

        option = atoi(&opt[0]);
        
        switch (option)
        {
            case 1:
                broadcastMessage(QURY_MIN_TEMP, QURY_TEMP_MESG_TYPE);
                sprintf(replyMode, QURY_MIN_TEMP);
                startReciever( );
                break;
            case 2:
                broadcastMessage(QURY_AVG_TEMP, QURY_TEMP_MESG_TYPE);
                sprintf(replyMode, QURY_AVG_TEMP);
                startReciever( );
                break;
            case 3:
                broadcastMessage(QURY_MAX_TEMP, QURY_TEMP_MESG_TYPE);
                sprintf(replyMode, QURY_MAX_TEMP);
                startReciever( );
                break;
            case 4:
                broadcastMessage(spanningTreeMesg, SPAN_TREE_MESG_TYPE);
                printf("\n");
                break;
            case 5:
                broadcastMessage(TERM_MESG, NODE_TERM_MESG_TYPE);
                finish = true;
                break;
            default:
                printf("Incorrect option selected\n");
                break;
        }
    }
}

//------------------------------------------------------------------------------------------

bool isChild(char inNodeName)
{
    int i;
    bool result = false;
    
    for (i = 0; i < childCount; i++)
    {
        if (childArray[i] == inNodeName)
        {
            result = true;
            break;
        }
    }
    
    return result;
}

//------------------------------------------------------------------------------------------

bool isPresent(struct mesgStruct * mesgArray, int mesgCount, char nodeName)
{
    int i;
    bool result = false; 
    for ( i = 0; i < mesgCount; i++)
    {
        if ( mesgArray[i].sourceNodeName == nodeName )
        {
            printf("Duplicate message received from Node '%c'\n", nodeName);
            result = true;
            break;
        }
    }
    
    return result;
}

//------------------------------------------------------------------------------------------

void calcTemperature(struct mesgStruct mesgArr[], char * output)
{
    int i;
    char * p;
    double result = myNode->temp;
    double tempValue = 0;
    int mesgCount = 0;
    int count = 1;
    
    for (i = 0; i < childCount; i++)
    {
        p = strchr(mesgArr[i].message, ',');
        *p = '\0';
        tempValue = atof(mesgArr[i].message);
        mesgCount = atoi( p + 1 );
        
        if ( strcmp(replyMode, QURY_MIN_TEMP) == 0 )
        {
            if ( result > tempValue )
                result = tempValue;
            count += mesgCount; 
        }
        else if ( strcmp(replyMode, QURY_AVG_TEMP) == 0 )
        {
            result = ((result * count) + ( tempValue * mesgCount )) / (count + mesgCount) ; 
            count += mesgCount;
        }
        else if ( strcmp(replyMode, QURY_MAX_TEMP) == 0 )
        {
            if ( result < tempValue )
                result = tempValue;
            count += mesgCount;
        }
    }
    
    sprintf(output, "%f,%d", result, count);
}

//------------------------------------------------------------------------------------------

void throwError( const char * iProgramIdentity
                ,const char * iErrorDescription )
{
  sprintf(printText, "\n%s : %s\n", iProgramIdentity, iErrorDescription);
  logMesg(printText, true);
  exit(0) ;
}

//------------------------------------------------------------------------------------------


