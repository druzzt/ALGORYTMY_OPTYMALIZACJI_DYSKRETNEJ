#include "bilist.h"
#include "structs.h"
#include <stdio.h>
int test(){
	return 666;
}

#define MAXINT  100007

int parent[MAXV];               /* discovery relation */



int dijkstra(graph *g, int start)		/* WAS prim(g,start) */
{
	int i,j;			/* counters */
	bool intree[MAXV];		/* is the vertex in the tree yet? */
	int distance[MAXV];		/* distance vertex is from start */
	int v;				/* current vertex to process */
	int w;				/* candidate next vertex */
	int weight;			/* edge weight */
	int dist;			/* best current distance from start */

	for (i=1; i<=g->nvertices; i++) {
		intree[i] = FALSE;
		distance[i] = MAXINT;
		parent[i] = -1;
	}

	distance[start] = 0;
	v = start;

	while (intree[v] == FALSE) {
		intree[v] = TRUE;
		for (i=0; i<g->degree[v]; i++) {
			w = g->edges[v][i].v;
			weight = g->edges[v][i].weight;
/* CHANGED */		if (distance[w] > (distance[v]+weight)) {
/* CHANGED */			distance[w] = distance[v]+weight;
/* CHANGED */			parent[w] = v;
			}
		}

		v = 1;
		dist = MAXINT;
		for (i=1; i<=g->nvertices; i++) 
			if ((intree[i] == FALSE) && (dist > distance[i])) {
				dist = distance[i];
				v = i;
			}
	}
	return 666;
/*for (i=1; i<=g->nvertices; i++) printf("%d %d\n",i,distance[i]);*/
}

int test2(){

	graph g;
	int i;

	read_graph(&g,FALSE);
	dijkstra(&g,1);

        for (i=1; i<=g.nvertices; i++)
                find_path(1,i,parent);
        printf("\n");

	return 666;
}

























