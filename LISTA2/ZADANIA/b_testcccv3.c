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
/* ################   MODULE for TESTING   ################## */





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

el *tab2list(el *head, struct tablica *tablica, INTEGER E)
{
	el *lis, *elt;
	INTEGER i = 0;
	int count;
	printf("E=%llu\n",E);
	for(i=1; i<=E; i++){
		//printf("%llu. %llu %llu %llu %llu\n",i, tablica[i], INT(tablica[i].s),tablica[i].t,tablica[i].v);
		ARLOC(lis, el);
 		lis->tab.s = tablica[i].s;
 		lis->tab.t = tablica[i].t;
 		lis->tab.v = tablica[i].v;
 		PUSH_BACK(head,lis);
 	}
 	// DRUKUJE CALA LISTE
 	PRINT(head,elt,printf);
 	return head;
}

int test2(el *head, el3 *Q, struct tablica *tablica, INTEGER S, INTEGER V, INTEGER E)
{
	el *lis, *elt, *elt2, *tmp, etmp;
	el3 *sli, *sli2, *sli3, *sli4, *sliQ, slitmp;
	printf("\t{%llu,%llu}\n",V,E);
	head = tab2list(head,tablica,E);
	printf("....");
 	 INTEGER i;
 	for(i=1;i<=V;i++){
 		ARLOC(sli, el3);
 		VASSIGNP(sli->tab.dist,INF);
 		VASSIGNP(sli->tab.prev,UNDEFINED);
 		VASSIGNP(sli->tab.s,i);
 		if(i==1){sli->tab.dist = 0;}
 		PUSH_BACK(Q, sli);
 	}
 	PRINT(Q, sli2, printf);
 	
 	sliQ = Q;
 	INTEGER min = 0;
 	INTEGER tmin = 0;
 	INTEGER u =0;
 	while(sliQ){
 		sli3=Q;
 		while(sli3){
 			PASSIGNV(tmin,sli3->tab.dist);
 			if(min>=tmin){
 				min=tmin;
 				PASSIGNV(u,sli3->tab.s); 							
 				printf("new min: %llu\n",min);
 				sli4=sli3;
 				REMOVE(Q,sli4);
 			}
 			sli3=sli3->next;
 		}

 		Q_FOREACH(head, lis){

 		}
 		sliQ=sliQ->next;
 	}

	

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

struct tabtablica* loadData1(int argc, char *argv[])
{
	struct tabtablica itablica;
	int E,V;
 	INTEGER u, v, w;
 	FILE *fin = fopen(argv[1], "r");
	fscanf(fin, "%llu %llu", &itablica.V,&itablica.E);
   	printf("\t\t%llu %llu\n",INT(itablica.V),INT(itablica.E));
    INTEGER i;
    ARLOC_A(itablica.tab,INTEGER,itablica.E+1);
	for(i=1; i<=INT(itablica.E); i++){
 		fscanf(fin, "%llu%llu%llu", &u, &v, &w);	
        VASSIGNP(itablica.tab[i].s,u);
        VASSIGNP(itablica.tab[i].t,v);
        VASSIGNP(itablica.tab[i].v,w);
 		printf("%llu - %llu - %llu\n",u,v,w);
 	}
 	return &itablica;
}

int main(int argc, char *argv[])
{
	
	struct tabtablica *itab;
 	el *head = NULL;
	el3 *Q = NULL;
 	
    itab=loadData1(argc,argv);
    printf(">%llu<\t>%llu<",(INTEGER)itab->V,(INTEGER)itab->E);
 	INTEGER szukane = 1;
 	// ....
 	INTEGER x;
 	x = &itab->E;
 	printf("\n|||-|-|-|>|||||%llu\n",x);
 	//...
	test2(head,Q,itab->tab, szukane);
	return 0;
}
