

#include "structs.h"


init_queue(queue *q)
{
        q->first = 0;
        q->last = QUEUESIZE-1;
        q->count = 0;
}

enqueue(queue *q, int x)
{
        if (q->count >= QUEUESIZE)
		printf("Warning: queue overflow enqueue x=%d\n",x);
        else {
                q->last = (q->last+1) % QUEUESIZE;
                q->q[ q->last ] = x;    
                q->count = q->count + 1;
        }
}

int dequeue(queue *q)
{
        int x;

        if (q->count <= 0) printf("Warning: empty queue dequeue.\n");
        else {
                x = q->q[ q->first ];
                q->first = (q->first+1) % QUEUESIZE;
                q->count = q->count - 1;
        }

        return(x);
}

int empty(queue *q)
{
        if (q->count <= 0) return (TRUE);
        else return (FALSE);
}

print_queue(queue *q)
{
        int i,j;

        i=q->first; 
        
        while (i != q->last) {
                printf("%c ",q->q[i]);
                i = (i+1) % QUEUESIZE;
        }

        printf("%2d ",q->q[i]);
        printf("\n");
}


initialize_graph(g)
graph *g;				/* graph to initialize */
{

	int i;				/* counter */

	g -> nvertices = 0;
	g -> nedges = 0;

	for (i=1; i<=MAXV; i++) g->degree[i] = 0;
}

read_graph(g,directed)
graph *g;                               /* graph to initialize */
bool directed;				/* is this graph directed? */
{
	int i;				/* counter */
	int m;				/* number of edges */
	int x,y,w;			/* placeholder for edge and weight */

	initialize_graph(g);

	scanf("%d %d\n",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
		scanf("%d %d %d\n",&x,&y,&w);
		insert_edge(g,x,y,directed,w);
	}
}

insert_edge(g,x,y,directed,w)
graph *g;                               /* graph to initialize */
int x, y;                       	/* placeholder for edge (x,y) */
bool directed;                          /* is this edge directed? */
int w;					/* edge weight */
{
	if (g->degree[x] > MAXDEGREE)
		printf("Warning: insertion(%d,%d) exceeds degree bound\n",x,y);

	g->edges[x][g->degree[x]].v = y;
	g->edges[x][g->degree[x]].weight = w;
	/*g->edges[x][g->degree[x]].in = FALSE;*/
	g->degree[x] ++;

	if (directed == FALSE)
		insert_edge(g,y,x,TRUE,w);
	else
		g->nedges ++;
}


delete_edge(g,x,y,directed)
graph *g;                               /* graph to initialize */
int x, y;                               /* placeholder for edge (x,y) */
bool directed;                          /* is this edge directed? */
{
	int i;				/* counter */

	for (i=0; i<g->degree[x]; i++) 
		if (g->edges[x][i].v == y) {
			g->degree[x] --;
			g->edges[x][i] = g->edges[x][g->degree[x]];

			if (directed == FALSE)
				delete_edge(g,y,x,TRUE);

			return FALSE;
		}

	printf("Warning: deletion(%d,%d) not found in g.\n",x,y);
}

print_graph(g)
graph *g;                               /* graph to print */
{
	int i,j;			/* counters */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		for (j=0; j<g->degree[i]; j++)
			printf(" %d",g->edges[i][j].v);
		printf("\n");
	}
}

bool processed[MAXV];		/* which vertices have been processed */
bool discovered[MAXV];          /* which vertices have been found */
int parent[MAXV];		/* discovery relation */


initialize_search(g)
graph *g;				/* graph to traverse */
{
        int i;                          /* counter */

        for (i=1; i<=g->nvertices; i++) {
                processed[i] = FALSE;
                discovered[i] = FALSE;
                parent[i] = -1;
        }
}


dfs(g,v)
graph *g;                               /* graph to traverse */
int v;					/* vertex to start searching from */
{
	int i;				/* counter */
	int y;				/* successor vertex */

	discovered[v] = TRUE;
	process_vertex(v);

	for (i=0; i<g->degree[v]; i++) {
		y = g->edges[v][i].v;
		if (discovered[y] == FALSE) {
			parent[y] = v;
			dfs(g,y);
		} else 
			if (processed[y] == FALSE)
				process_edge(v,y);
	}

	processed[v] = TRUE;
}

process_vertex(v)
int v;					/* vertex to process */
{
	printf(" %d",v);
}

process_edge(x,y)
int x,y;                                /* edge to process */
{
}




find_path(start,end,parents)
int start;				/* first vertex on path */
int end;				/* last vertex on path */
int parents[];				/* array of parent pointers */
{
	if ((start == end) || (end == -1))
		printf("\n%d",start);
	else {
		find_path(start,parents[end],parents);
		printf(" %d",end);
	}
}

connected_components(g)
graph *g;				/* graph to analyze */
{
	int c;				/* component number */
	int i;				/* counter */

	initialize_search(g);

	c = 0;
	for (i=1; i<=g->nvertices; i++)
		if (discovered[i] == FALSE) {
			c = c+1;
			printf("Component %d:",c);
			dfs(g,i);
			printf("\n");
		}
}