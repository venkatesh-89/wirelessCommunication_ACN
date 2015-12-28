/************************************* SPANNINGTREE.C **************************************/

#include "spanningTree.h"

//------------------------------------------------------------------------------------------

void calcSpanningTree(int ** graph, const int vertices, int * parent)
{
    V = vertices;
   
    primMST(graph, parent);
 
}

//------------------------------------------------------------------------------------------

void primMST(int ** graph, int * parent)
{
     int key[V];
     int i, v, count;
     bool mstSet[V];
 
     for (i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
     key[0] = 0;
     parent[0] = -1;
 
     for (count = 0; count < V-1; count++)
     {
        int u = minKey(key, mstSet);
 
        mstSet[u] = true;
 
        for (v = 0; v < V; v++)
        {
            if (   graph[u][v] 
                && mstSet[v] == false 
                && graph[u][v] <  key[v])
            {
                parent[v]  = u;
                key[v] = graph[u][v];
            }
        }
     }
}

//------------------------------------------------------------------------------------------

int minKey(int key[], bool mstSet[])
{
    int min = INT_MAX, min_index, v;
 
    for (v = 0; v < V; v++)
    {
        if (mstSet[v] == false && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }
    
    return min_index;
}


//------------------------------------------------------------------------------------------

