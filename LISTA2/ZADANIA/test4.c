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

el *lis, *lis2, *savelis, tlis;
el3 *sli, *sli2;
INTEGER *dist;
INTEGER *prev;
INTEGER *S;
INTEGER *path;


int loadData(struct tablica *tablica, INTEGER V,
				 INTEGER E, struct tablica search_elem){
	INTEGER noneleft= E;
	INTEGER i=0;
	el *Graph;
	

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






















int dijkstra(	 INTEGER V,
				 INTEGER E,
				 INTEGER SEARCHED_ELEMENT_FROM)
{
 	
	INTEGER min;
	INTEGER i=0;
	INTEGER j=0;
	INTEGER p=0;
	INTEGER k=0;
	el *iterator;
	ARLOC(iterator, el);

	for(i=1; i<=V; i++){
		S[i]=0;
		ARLOC(iterator, el);
		Q_FOREACH(head, iterator){
			if((INTEGER)iterator->tab.s == SEARCHED_ELEMENT_FROM &&
				(INTEGER)iterator->tab.t == i){
				dist[i]=(INTEGER)iterator->tab.v;
			printf("%llu = %llu %llu %llu\n", dist[i],
			 (INTEGER)iterator->tab.s,
			 (INTEGER)iterator->tab.t,
			 (INTEGER)iterator->tab.v);
			}
		}
	}
	path[++p]=SEARCHED_ELEMENT_FROM;
	S[SEARCHED_ELEMENT_FROM]=1;
	dist[SEARCHED_ELEMENT_FROM]=0;

	for(i=2;i<=V-1;i++){
		k=-1;
		min=INF;
		for(j=1;j<=V;j++){
			if(dist[j]<min && S[j]!=1){
				min=dist[j];
				k=j;
			}
		}
		ARLOC(iterator, el);
		Q_FOREACH(head, iterator){
			if(	(INTEGER)iterator->tab.t==k &&
				(INTEGER)iterator->tab.v<=dist[k]){
				p=1;
			}
		}
		path[++p]=k;
		S[k]=1;
		for(j=1;j<=V;j++){
			ARLOC(iterator, el);
			Q_FOREACH(head, iterator){
				if(	(INTEGER)iterator->tab.s == k &&
				 	(INTEGER)iterator->tab.t ==j &&
					(INTEGER)iterator->tab.v != INF && 
					dist[j]>= dist[k]+(INTEGER)iterator->tab.v &&
					S[j]!=1){
					dist[j]=dist[k]+(INTEGER)iterator->tab.v;
				}
			}
		}
	}

	for(i=1;i<=V;i++){
		printf("%llu => %llu\n",i,dist[i]);
	}

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
	printf(".\n");
	dijkstra(V, E, SEARCHED_ELEMENT);
 	return 0;
}






























int namecmp(el const *a, el const *b) {
    return (a->tab.s==b->tab.s) ? 0 : 1;
}



/*


int dijkstra(	 INTEGER V,
				 INTEGER E,
				 INTEGER SEARCHED_ELEMENT_FROM)
{
	el *Graph, tGraph;
	INTEGER i = 0;
	ARLOC(Graph, el);
	Graph->tab.s = 1;  // tylko S !
	PUSH_FRONT(S, Graph); // S:= {1}
	ARLOC(Graph, el);
	PRINT(S, Graph, printf);

	printf("...\n");
	ARLOC(Graph, el);
	for(i=2; i<=V; i++){
		ARLOC(Graph, el);
		Graph->tab.s = i;
		PUSH_BACK(T, Graph);
	}
	ARLOC(Graph, el);
	PRINT(T, Graph, printf);


	dist[1] = 0;
	prev[1] = 0;
	for(i=2;i<=V;i++){
		dist[i]=INF;
		printf("dist[%llu]>%llu\n",i,dist[i]);
	}
	dist[1]=0;
 	INTEGER min = dist[2];
 	printf("act min: %llu\n",min);
 	INTEGER idx = 0;
 	update(1);
 	
 	while(1){
 		ARLOC(Graph, el);
 		Q_FOREACH(T, Graph){
 			idx = (INTEGER)Graph->tab.s;
 			printf("d[%llu] = %llu\n",idx, dist[idx]);
 			if(min > dist[idx]){
 				min = dist[idx];
 				printf("min: %llu\n", min);
 			}
 			if(Graph->next == NULL){
 				tGraph.tab.s = idx;
 				sli->tab.s = tGraph.tab.s;
 				ARLOC(sli, el3);
 				PUSH_BACK(S, sli);
 				DELETE(T, Graph, tGraph);
 				break;
 			}
 		}
 	}
 	



	return 0;
}


*/
/*int update(INTEGER i){
	ARLOC(lis, el);

	Q_FOREACH(head, lis){

		if((INTEGER)lis->tab.s == i && dist[(INTEGER)lis->tab.t] > dist[(INTEGER)lis->tab.s] + (INTEGER)lis->tab.v){
			dist[(INTEGER)lis->tab.t] = dist[(INTEGER)lis->tab.s] + (INTEGER)lis->tab.v;
			prev[(INTEGER)lis->tab.t] = (INTEGER)lis->tab.s;
			printf("%llu, %llu\n", dist[(INTEGER)lis->tab.s], prev[(INTEGER)lis->tab.t]);
		}
	}
	ARLOC(lis, el);
	return 0;
}*/

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

/*
 	for(i=1;i<=V;i++){ ARLOC(sli, el3);
 		dist[i] = INF;
 		prev[i] = 0;
 		sli->tab.s = (void*)i;
 		PUSH_BACK(Q, sli);
 	}
*/
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


































