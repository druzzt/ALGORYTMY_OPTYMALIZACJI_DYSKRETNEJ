#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "constants.h"
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "dlist.h"
/* ################   MODULE for TESTING   ################## */
INTEGER V,E;



el *tab2list(el *head, Tablica *tablica)
{
	el *lis, *lis2, *elt;
	INTEGER i = 0;
	printf("E=" I_FORMAT "\n",E);
	ARLOC(lis, el);
	for(i=1; i<=E; i++){
		//printf("" I_FORMAT ". "  I_FORMAT" " I_FORMAT" " I_FORMAT "\n",i,
		INT(tablica[i].s),INT(tablica[i].t) ,INT(tablica[i].v) );
		if ( (lis = (el*)malloc(sizeof(el))) == NULL) exit(-1);
 		lis->tab.s = tablica[i].s;
 		lis->tab.t = tablica[i].t;
 		lis->tab.v = tablica[i].v;
 		PUSH_BACK(head,lis);
 	}
 	PRINT(head,elt,printf);
	free(tablica);
 	return head;
}

Tablica* loadData1(int argc, char *argv[])
{
 	INTEGER u, v, w;
 	FILE *fin = fopen(argv[1], "r");
	fscanf(fin, " "I_FORMAT I_FORMAT" ", &V,&E);
    INTEGER i;
    Tablica* itablica;
    ARLOC_A(itablica,Tablica,E+2);
	for(i=1; i<=INT(E); i++){
 		fscanf(fin, " "I_FORMAT I_FORMAT I_FORMAT " ", &u, &v, &w);
 		ARLOC_A(itablica[i].s,INTEGER,1);
        VASSIGNP(itablica[i].s,u);
        ARLOC_A(itablica[i].t,INTEGER,1);
        VASSIGNP(itablica[i].t,v);
        ARLOC_A(itablica[i].v,INTEGER,1);
        VASSIGNP(itablica[i].v,w);
 	}
 	return itablica;
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



int test2(el *head, el3 *Q, Tablica *tablica1, INTEGER S)
{
	el *lis, *elt, *elt2, *tmp, etmp;
	el3 *sli, *sli2, *sli3, *sli4, *sliQ, slitmp;
	INTEGER i;
	head = tab2list(head,tablica1);
 	for(i=1;i<=V;i++){
 		ARLOC(sli, el3);
 		VASSIGNP(sli->tab.dist,INF);
 		VASSIGNP(sli->tab.prev,UNDEFINED);
 		VASSIGNP(sli->tab.s,i);
 		if(i==S){VASSIGNP(sli->tab.dist,0);}
 		INTEGER j=1;
 		ARLOC_A(sli->tab.predecesors,INTEGER,2);
 		sli->tab.predecesors[0]=0;
 		FOREA(head,lis,j){
 			if(INT(lis->tab.t) == INT(i))
 				(sli->tab.predecesors[0]++,
 				 sli->tab.predecesors[j] = lis->tab.s,
 				 sli->tab.predecesors = realloc(sli->tab.predecesors,
 				  j+1*sizeof(INTEGER)));
 		}j=1;
 		ARLOC_A(sli->tab.neighbours,INTEGER,2);
 		sli->tab.neighbours[0]=0;
 		FOREA(head, lis,j){
 			if(INT(lis->tab.s) == INT(i))
 				(sli->tab.neighbours[0]++,
 				 sli->tab.neighbours[j] = lis->tab.t,
 				 sli->tab.neighbours = realloc(sli->tab.neighbours,
 				  j+1*sizeof(INTEGER)));
 		}j=0;
 		PUSH_BACK(Q, sli);
 	}
 	PRINT(Q, sli2, printf);

 	// NOW SEEK!
 	sliQ = Q;
 	INTEGER min = 0;
 	INTEGER tmin = 0;
 	INTEGER u =0;

 	while(sliQ){ // dopoki w queue cos jest	

 	}

    FREE(head,elt,tmp,free);
	return 0;
}



int main(int argc, char *argv[])
{
 	el *head = NULL;
	el3 *Q = NULL;
    Tablica **itab=loadData1(argc,argv);
 	INTEGER szukane = 1;
	test2(head,Q,itab,szukane);
	return 0;
}
