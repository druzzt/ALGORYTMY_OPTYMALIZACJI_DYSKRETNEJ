#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "constants.h"
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "structs.h"
#include "dlist.h"
//#include "limits.h"
#define INFINITY 999999999
#define UNDEFINED 0

struct tablica {
	void *s;
	void *t;
	void *v;
	short end;
};
typedef struct el {
	struct tablica tab;
    struct el *next, *prev;
} el;

struct AdjListNode{
	void *dest;
	void *weight;
	struct AdjListNode* next;
	struct AdjListNode* prev;
};

struct  AdjList{
	struct AdjListNode *head;
};

struct Graph{
	void *V;
	struct AdjList* array;
};
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
};

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0 ; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
// Structure to represent a min heap node
struct MinHeapNode
{
    int  v;
    int dist;
};
 
// Structure to represent a min heap
struct MinHeap
{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
};
 
// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// A utility function to check if the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
 
// A utility function to check if a given vertex
// 'v' is in min heap or not
int isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return 1;
   return 0;
}
 
// A utility function used to print the solution
void printArr(int dist[], int n)
{
    //printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(struct Graph* graph, int src)
{
    int V = graph->V;// Get the number of vertices in graph
    printf(">>>%d\n",V);
    int *dist= malloc(V*sizeof(int));      // dist values used to pick minimum weight edge in cut
 
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
 	
    // Initialize min heap with all vertices. dist value of all vertices 
    for (int v = 0; v < V; ++v)
    {

        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
 
    // Make dist value of src vertex as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    // Initially size of min heap is equal to V
    minHeap->size = V;
 
    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap))
    {

        // Extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);

        int u = minHeapNode->v; // Store the extracted vertex number
 
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {

            int v = pCrawl->dest;
 printf(">>>%d\n",graph->array[u].head);
            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && 
                                          pCrawl->weight + dist[u] < dist[v])
            {

                dist[v] = dist[u] + pCrawl->weight;
 
                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 
    // print the calculated shortest distances
    printArr(dist, V);
}
 //*********************************************************************************
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
el *head = NULL;

//el *dist = NULL;


// POROWNYWACZ DLA LISTY
int namecmp(el const *a, el const *b) {
    return (a->tab.s==b->tab.s) ? 0 : 1;
}

/* MODULE for TESTING */
int test2(struct tablica *tablica, struct tablica search_elem)
{
	el *lis, *elt, *elt2, *tmp, etmp;
	int i = 0;
	int count;

	for(i=0; tablica[i].end!=1; i++){
 		//printf("%d\t%d\t%d\n",tablica[i].s,tablica[i].t,tablica[i].v);
 		 if ( (lis = (el*)malloc(sizeof(el))) == NULL) exit(-1);
 		lis->tab = tablica[i];
 		lis->tab.s = tablica[i].s;
 		lis->tab.t = tablica[i].t;
 		lis->tab.v = tablica[i].v;
 		PUSH_BACK(head,lis);
 	}

 	// DRUKUJE CALA LISTE
 	PRINT(head,elt,printf);

 	// ZNAJDZ SZUKANY ELEMENT NA LISCIE
	etmp.tab.s = search_elem.s;
 	SEARCH(head,elt,&etmp,namecmp);
    
    if (elt) printf("found at least one occurence of: [%d]\n", elt->tab.s);
    
    DELETE_ONE(head, elt, etmp);
    PRINT(head,elt,printf);

    // USUN WSZYSTKIE JEGO WYSTAPIENIA
    DELETE(head,elt,etmp);
    PRINT(head,elt,printf);

    // USUN I ZWOLNIJ MIEJSCE PO KAZDYM WYSTAPIENIU ELEMENTU
    FREE(head,elt,tmp,free);
    PRINT(head,elt,printf);

	return 0;
}

INTEGER* test4(struct tablica *tablica, struct tablica search_elem)
{
	el *Graph, *tdist, *S, *tmp, *tmp2, etmp; // temporary pointers
	
	INTEGER k;
	INTEGER i;
	INTEGER n;
	int min;
	i=0;
	do{
 		//printf("%d\t%d\t%d\n",tablica[i].s,tablica[i].t,tablica[i].v);
 		 if ( (Graph = (el*)malloc(sizeof(el))) == NULL) exit(-1);
 		Graph->tab = tablica[i];
 		Graph->tab.s = tablica[i].s;
 		Graph->tab.t = tablica[i].t;
 		Graph->tab.v = tablica[i].v;
 		PUSH_BACK(head, Graph);
 	}while(tablica[i++].end!=1);
 	
 	
 	INTEGER Vsize = i;
 	printf("Size of graph - nodes = %llu\n",Vsize);
 	
 	











/*
	INTEGER *dist = malloc(Vsize*sizeof(INTEGER));
 	int *prev = malloc(Vsize*sizeof(int));
 	INTEGER *visited = malloc(Vsize*sizeof(INTEGER));
	FOREACH(head, tdist){
		printf(">%llu\n",tdist->tab.t);
		dist[(INTEGER)tdist->tab.t] = INFINITY; //(set all other distances to infinity)
		prev[(INTEGER)tdist->tab.t] = -1;
		visited[(INTEGER)tdist->tab.t] = 0;
		//printf("%llu",tdist->tab.v);
		printf("{%llu}\tdist[]=%llu \t prev[]=%llu\tvisited[]=%llu\n",(INTEGER)tdist->tab.t,dist[(INTEGER)tdist->tab.t],prev[(INTEGER)tdist->tab.t],visited[(INTEGER)tdist->tab.t]);
	}

	//PRINT(head, tmp, printf);
	//(distance to source vertex is zero)
	//dist[(INTEGER)search_elem.s] = 0;

	FOREACH(head, tdist){
		min = -1;
		//printf("%llu\t", tdist->tab.t);
		FOREACH(head, tmp){
			//printf("{%llu}", tmp->tab.v);
			if(!visited[(INTEGER)tmp->tab.t] && ((min==-1) || (dist[(INTEGER)tmp->tab.t]<dist[min]))) {
				//printf("{%llu}\t", tdist->tab.t);
				printf("{%llu}\t", dist[(INTEGER)tmp->tab.t]);
				min = (INTEGER) tmp->tab.t;
			}
		}
		visited[min]=1;
		FOREACH(head, tmp){
			if((INTEGER)tmp->tab.t == min){
				//printf("%llu,",(INTEGER)tmp->tab.t);
				if(dist[min]+tmp->tab.v < dist[(INTEGER)tmp->tab.t]){
					dist[(INTEGER)tmp->tab.t] = dist[min] + tmp->tab.v;
					prev[(INTEGER)tmp->tab.t] = min;
				//	printf("%llu\n",min);
				}
			}
		}
	}
*/

	//(S, the set of visited vertices is initially empty)
	//(Q, the queue initially contains all vertices)
	//(while the queue is not empty)
	//(select the element of Q with the min. distance)
	//(add u to list of visited vertices)
	//(if new shortest path found)
	//(set new value of shortest path)
	//(if desired, add traceback code)

	//FOREA(head, tmp, i){
	//	printf(">\t=%llu,", dist[i]);
	//}
	//el *Graph, *tdist, *S, *tmp, *tmp2, etmp, *Q;
	FREE(head, tmp, tmp2, free);
	printf("\n");
	return tdist;
}


INTEGER* test3(struct tablica *tablica, struct tablica search_elem)
{
	el *Graph, *tdist, *S, *tmp, *tmp2, etmp; // temporary pointers
	
	INTEGER k;
	INTEGER i;
	INTEGER n;
	int min;
	i=0;
	do{
 		//printf("%d\t%d\t%d\n",tablica[i].s,tablica[i].t,tablica[i].v);
 		 if ( (Graph = (el*)malloc(sizeof(el))) == NULL) exit(-1);
 		Graph->tab = tablica[i];
 		Graph->tab.s = tablica[i].s;
 		Graph->tab.t = tablica[i].t;
 		Graph->tab.v = tablica[i].v;
 		PUSH_BACK(head, Graph);
 	}while(tablica[i++].end!=1);
 	
 	
 	INTEGER Vsize = i;
 	printf("Size of graph - nodes = %llu\n",Vsize);
 	
 	




	FREE(head, tmp, tmp2, free);
	printf("\n");
	return tdist;
}














//  DIJKSTRA MODULE
//	DONE.
//  DIAL MODULE 
// 	TO DO
//  RADIXHEAP MODULE 
// 	TO DO
//  MAIN MODULE 
int main()
{
	struct tablica *itablica;
	struct tablica szukaj;
 	
 	int i;
 	int start = 10;
 	int e;
 	INTEGER u, v, w;
 	FILE *fin = fopen("dist.txt", "r");
	fscanf(fin, "%d", &e);
    struct Graph* graph = createGraph(e);
	itablica = malloc((e+1) * sizeof *itablica);

	for(i=1; i<=e; i++){
 		fscanf(fin, "%llu%llu%lu", &u, &v, &w);
 		addEdge(graph,u,v,w);
 		
 	}
 	INTEGER szukane = 1;
    dijkstra(graph, szukane);

	//test3(itablica, szukaj);
	return 0;
}

















