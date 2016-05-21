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

#define INFINITY 999999999
#define UNDEFINED 0


el *head = NULL;
el3 *Q = NULL;

/* MODULE for TESTING */
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
int test2(struct tablica *tablica, INTEGER S, INTEGER V, INTEGER E)
{
	el *lis, *elt, *elt2, *tmp, etmp;
	int i = 0;
	int count;

	for(i=0; i<=E; i++){
 		//printf("%d\t%d\t%d\n",tablica[i].s,tablica[i].t,tablica[i].v);
 		 //if ( (lis = (el*)malloc(sizeof(el))) == NULL) exit(-1);
		ARLOC(lis, el);
 		lis->tab = tablica[i];
 		lis->tab.s = tablica[i].s;
 		lis->tab.t = tablica[i].t;
 		lis->tab.v = tablica[i].v;
 		PUSH_BACK(head,lis);
 	}

 	// DRUKUJE CALA LISTE
 	PRINT(head,elt,printf);
 		PRINT(head,elt,printf);
/*
 	// ZNAJDZ SZUKANY ELEMENT NA LISCIE
	etmp.tab.s = search_elem.s;
 	SEARCH(head,elt,&etmp,namecmp);
    
    if (elt) printf("found at least one occurence of: [%d]\n", elt->tab.s);
    
    DELETE_ONE(head, elt, etmp);
    PRINT(head,elt,printf);

    // USUN WSZYSTKIE JEGO WYSTAPIENIA
    DELETE(head,elt,etmp);
    PRINT(head,elt,printf);
*/
    // USUN I ZWOLNIJ MIEJSCE PO KAZDYM WYSTAPIENIU ELEMENTU
    FREE(head,elt,tmp,free);
    //PRINT(head,elt,printf);

	return 0;
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
	struct tablica *itablica;
	struct tablica szukaj;
 	
 	int i;
 	int start = 10;
 	int E,V;
 	INTEGER u, v, w;
 	FILE *fin = fopen("dist.txt", "r");
	fscanf(fin, "%d %d", &V,&E);
    //struct Graph* graph = createGraph(e);
   

	itablica = malloc((E+1) * sizeof *itablica);
    //addEdge(graph, 0, 1, 0);
	for(i=1; i<=E; i++){
 		fscanf(fin, "%llu%llu%lu", &u, &v, &w);
 		//addEdge(graph,u,v,w);
        itablica[i].s=u;
        itablica[i].t=v;
        itablica[i].v=w;
        if(i==E){ itablica[i].end=1;}
 		printf("%llu - %llu - %llu\n",u,v,w);
 	}
    
 	INTEGER szukane = 1;
    //dijkstra(graph, szukane);
    
	test2(itablica, szukane, V,E );
	return 0;
}
