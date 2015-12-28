/************************************* SPANNINGTREE.H **************************************/

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

//------------------------------------------------------------------------------------------

int V;      // Number of vertices in the graph

void calcSpanningTree( int ** graph
                      ,const int vertices
                      ,int * parent );
                      
int minKey( int key[]
           ,bool mstSet[] );
           
void primMST( int ** graph 
             ,int * parent );


//------------------------------------------------------------------------------------------

