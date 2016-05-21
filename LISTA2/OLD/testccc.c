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
//#include "structs.h"
#include "dlist.h"

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

el *head = NULL;

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
    //struct Graph* graph = createGraph(e);
   

	itablica = malloc((e+1) * sizeof *itablica);
    //addEdge(graph, 0, 1, 0);
	for(i=1; i<=e; i++){
 		fscanf(fin, "%llu%llu%lu", &u, &v, &w);
 		//addEdge(graph,u,v,w);
        itablica[i].s=u;
        itablica[i].t=v;
        itablica[i].v=w;
        if(i==e){ itablica[i].end=1;}
 		printf("%llu - %llu - %llu\n",u,v,w);
 	}
    
 	INTEGER szukane = 1;
    //dijkstra(graph, szukane);
    szukaj.s = (void*)1;
	test2(itablica, szukaj);
	return 0;
}
