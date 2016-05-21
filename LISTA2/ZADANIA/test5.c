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
#include "dlist.h"



el *head = NULL;
//el *S = NULL;
//el *T = NULL;

el3 *Q = NULL;

//
//
INTEGER *dist;
INTEGER *prev;
INTEGER *S;
INTEGER *path;


int loadData(struct tablica *tablica, INTEGER V,
				 INTEGER E, struct tablica search_elem){
	INTEGER noneleft= E;
	INTEGER i=0;
	el *Graph;
	el *lis, *lis2, *savelis, tlis;

	while(noneleft){
		printf("[%llu?<-\t", noneleft);
 		printf("%d\t%d\t%d",tablica[i].s,
 							  tablica[i].t,
 							  tablica[i].v);
 		ARLOC(Graph, el);
 		
 		Graph->tab.s = tablica[i].s;
 		printf("\t\t-> %llu",Graph->tab.s);
 		Graph->tab.t = tablica[i].t;
 		Graph->tab.v = tablica[i].v;
		PUSH_BACK(head, Graph); 		
 		i++;
 		--noneleft;
 		printf("\t->%llu!]\n", noneleft);
 	}
 	path = malloc(V+1 *sizeof(INTEGER));
 	if(path == NULL){
 		printf("error path");
 		return -1;
 	}
	S = malloc(V+1 * sizeof(INTEGER));
	if(S == NULL){
		printf("error S");
		return -1;
	}
 	dist = malloc(V+1*sizeof(INTEGER));
	if(dist==NULL){
		printf("error dist");
		return -1;
	}
	prev = malloc(V+1*sizeof(INTEGER));
	if(prev==NULL){
		printf("error prev");
		return -1;
	}

 	return 0;
}
 /*
 1  function Dijkstra(Graph, source):
 2
 3      create vertex set Q
 4
 5      for each vertex v in Graph:             // Initialization
 6          dist[v] ← INFINITY                  // Unknown distance from source to v
 7          prev[v] ← UNDEFINED                 // Previous node in optimal path from source
 8          add v to Q                          // All nodes initially in Q (unvisited nodes)
 9
10      dist[source] ← 0                        // Distance from source to source
11      
12      while Q is not empty:
13          u ← vertex in Q with min dist[u]    // Source node will be selected first
14          remove u from Q 
15          
16          for each neighbor v of u:           // where v is still in Q.
17              alt ← dist[u] + length(u, v)
18              if alt < dist[v]:               // A shorter path to v has been found
19                  dist[v] ← alt 
20                  prev[v] ← u 
21
22      return dist[], prev[]
*/

int dijkstra(INTEGER V, INTEGER E, INTEGER SEARCHED_ELEMENT)
{
	INTEGER i;
	el3 *sli, *sli2;
	for(i=1;i<=V;i++){
		dist[i] = INF;
		prev[i] = 0;
		ARLOC(sli, el3);
		sli->tab.s = i;
		sli->tab.dist = INF;
		sli->tab.prev = 0;
		PUSH_BACK(Q, sli);
		printf("%llu %llu %llu\n",sli->tab.s, sli->tab.dist, sli->tab.prev);
	}
	ARLOC(sli, el3);
	FOREACH(Q, sli) { printf("%llu->",sli2->tab.s); }
	/*sli = Q->prev->next;
	printf("%d\n",sli->tab.s );
	sli = sli->prev;
	printf("%d\n",sli->tab.s );
	sli = sli->prev->prev;
	printf("%d\n",sli->tab.s );
	return 0;*/

}


/*
initialize graph
initialize pq
pq.insertAll(graph.getVertices())

while (pq is not empty) {
  vertex = pq.remove()
  edges = vertex.getEdges()

  for all edges {
    destination = edge.getDestination()
    newDistance = edge.getLength() + vertex.getDistance()
    if (newDistance < destination.getDistance()) {
      destination.setShortestDistance(newDistance)
      pq.update(destination)
    }
  }
}
*/









int main()
{
	
	INTEGER V,E;
	INTEGER u,v,w;
	struct tablica SOURCE;
	SOURCE.s=1;
	INTEGER SEARCHED_ELEMENT = 1;
	INTEGER i;
    FILE *fin = fopen("dist.txt", "r");
	fscanf(fin, "%llu %llu",&V, &E);
	struct tablica *itablica;
	itablica = malloc((E+1) * sizeof *itablica);

	for(i=0; i<E; i++){
 		fscanf(fin, "%llu%llu%lu", &u, &v, &w);
 		itablica[i].s = u;
 		itablica[i].t = v;
 		itablica[i].v = w;
 		printf("%llu, %llu, %llu\n",u,v,w);
 	}
	loadData(itablica, V, E, SOURCE);
	printf(".\n");
	dijkstra(V, E, SEARCHED_ELEMENT);
 	return 0;
}



