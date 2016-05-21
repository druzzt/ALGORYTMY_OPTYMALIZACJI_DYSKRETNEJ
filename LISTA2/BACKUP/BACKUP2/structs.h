#ifndef structs_h
#define structs_h

typedef struct Node {
    struct Node *prev; 
    struct Node *next; 
    void* data; // %llu
}node;


#define TRUE    1
#define FALSE   0

typedef int bool;

#define	MAXV		100		/* maximum number of vertices */
#define MAXDEGREE	50		/* maximum outdegree of a vertex */

typedef struct {
	int v;				/* neighboring vertex */
	int weight;			/* edge weight */
} edge;

typedef struct {
	edge edges[MAXV+1][MAXDEGREE];	/* adjacency info */
	int degree[MAXV+1];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
} graph;

#define QUEUESIZE       1000

typedef struct {
        int q[QUEUESIZE+1];		/* body of queue */
        int first;                      /* position of first element */
        int last;                       /* position of last element */
        int count;                      /* number of queue elements */
} queue;

#endif
