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
#define ARLOC(X, T) \
			do{ \
			if((X = (T*)malloc(sizeof(T))) == NULL) \
			exit(-1); \
			} while(0)

//#define INF 9223372036854775807
#define INF 999999

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

struct node {
	void *s;
	void *dist;
	void *prev;
};

typedef struct el3 {
	struct node tab;
    struct el3 *next, *prev;
} el3;




int namecmp(el const *a, el const *b) {
    return (a->tab.s==b->tab.s) ? 0 : 1;
}



el *head = NULL;
el3 *Q = NULL;

el *lis, *lis2, *savelis, tlis;
el3 *sli, *sli2;
//INTEGER *dist;
//INTEGER *prev;

/*
int update(INTEGER i){
	ARLOC(lis, el);

	Q_FOREACH(head, lis){

		if((INTEGER)lis->tab.s == i && dist[(INTEGER)lis->tab.t] > dist[(INTEGER)lis->tab.s] + (INTEGER)lis->tab.v){
			dist[(INTEGER)lis->tab.t] = dist[(INTEGER)lis->tab.s] + (INTEGER)lis->tab.v;
			prev[(INTEGER)lis->tab.t] = (INTEGER)lis->tab.s;
			//printf("%llu, %llu\n", dist[(INTEGER)lis->tab.s], prev[(INTEGER)lis->tab.t]);
		}
	}
	ARLOC(lis, el);
	return 0;
}
*/

int loadData(struct tablica *tablica, INTEGER V, INTEGER E, struct tablica search_elem){
	INTEGER noneleft= E+1;
	INTEGER i=0;
	el *Graph;
	

	do{
		printf("[%llu?<-\t", noneleft);
		--noneleft;
 		printf("%d\t%d\t%d",tablica[i].s,
 							  tablica[i].t,
 							  tablica[i].v);
 		ARLOC(Graph, el);
 		
 		Graph->tab.s = tablica[i].s;
 		Graph->tab.t = tablica[i].t;
 		Graph->tab.v = tablica[i].v;
		PUSH_BACK(head, Graph); 		
 		i++;
 		printf("\t->%llu!]\n", noneleft);
 	}while(noneleft);
 	printf("end.");
 	return 0;
}

int dijkstra(	 INTEGER V,
				 INTEGER E,
				 INTEGER SEARCHED_ELEMENT)
{
	INTEGER i = 0;
	*dist = malloc(V+1*sizeof(INTEGER));
	*prev = malloc(V+1*sizeof(INTEGER));

 	for(i=1;i<=V;i++){ ARLOC(sli, el3);
 		dist[i] = INF;
 		prev[i] = 0;
 		sli->tab.s = (void*)i;
 		PUSH_BACK(Q, sli);
 	}

 	PRINT(head, lis, printf);
 	PRINT(Q, sli, printf);
 	dist[1]=0;
 	INTEGER min = dist[1];
 	//update(1);
 	

/*
12      while Q is not empty:
13          u ← vertex in Q with min dist[u]    // Source node will be selected first
14          remove u from Q 
15
16 			for each neighbor v of u:           // where v is still in Q.
17              alt ← dist[u] + length(u, v)
18              if alt < dist[v]:               // A shorter path to v has been found
19                  dist[v] ← alt 
20                  prev[v] ← u 
21
*/

	return 0;
}

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
	printf(".");
	dijkstra(V, E, SEARCHED_ELEMENT);
 	return 0;
}











/*
Q_FOREACH(Q, sli){
 			if(min >= dist[(INTEGER)sli->tab.s]){
 				min = dist[(INTEGER)sli->tab.s];	
 				printf(">%llu\n",sli->tab.s);
 				REMOVE(Q, sli);
 			}
 		}
 		Q_FOREACH(head, lis){
			printf("%llu,= <%llu, %llu>\n", lis->tab.v, lis->tab.s, lis->tab.t);
			alt = dist[u] + lis->tab.v;
			if(alt < dist[v]){
				dist[v] = alt;
				prev[v] = u;
				//printf(">>>>>%llu, %llu\n",dist[v],prev[v]);
				savelis = lis;
			}
			if(min > dist[(INTEGER)lis->tab.s]){
				min = dist[(INTEGER)lis->tab.s];
			}
 		}
*/




/* //    (head, out, out2,    field, field1, field2, val, val2, val3,    val4, val5, TYPE,    X, Y,       Z,       action)
 		//SEAR(head, lis, savelis, tab.s, tab.t,  tab.v,  u,   min,  dist[u], dist, prev, INTEGER, v, dist[v], prev[v], printf);	
 		printf("%llu, %llu, %llu, %llu\n",dist[u], dist[v], prev[v], min);
*/


/*
 		sli->tab.s = Graph->tab.t;
 		sli->tab.dist = INF;
 		sli->tab.prev = 0;
 		PUSH_BACK(Q, sli);
		
 	PRINT(Q, sli, printf);
 	*/





/*
struct disttype
{
	INTEGER s;
	INTEGER v;
};
typedef struct el2{
	struct disttype tab;
	struct el2 *next, *prev;
} el2;
	
el2 *visited = NULL;
el2 *d = NULL;
el2 *prev = NULL;
el2 *sli, sli2;

for(i=0; i<=SIZE;i++){
 		if((sli = (el2*)malloc(sizeof(el2))) == NULL) exit(-1);
 		sli->tab.s = i;
 		sli->tab.v = INFINITY;
 		PUSH_BACK(d, sli);
 		sli->tab.v = NULL;
 		PUSH_BACK(prev, sli);
 		sli->tab.v = 0;
 		PUSH_BACK(visited, sli);
 	}
 	*/


































