#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "constants2.h"
#include "heap.h"
#define MAD 10

typedef struct Verter{
	INTEGER s;
	INTEGER t;
	INTEGER v;
}Verter;


int main(int argc, char *argv[])
{
	INTEGER i=0;
	INTEGER get;
	INTEGER error;
	INTEGER array[MAD+1];
	Heap *radixheap;
	radixheap = initHeap();
	Heap *daneTestowe;
	daneTestowe = initHeap();

	Verter *vertice;
	vertice = malloc(MAD*sizeof(Verter));
	for(i=0; i<MAD;i++){
		vertice[i].s = i;
		vertice[i].t = i+1;
		vertice[i].v = i*i;
		error = insert(daneTestowe, vertice[i].v);
	}
	//for(i=0; i<MAD; i++) 	printf("%llu %llu %llu\n",vertice[i].s,vertice[i].t,vertice[i].v);




	
	for(i=0;i<MAD;i++)
	 error= insert(daneTestowe, i);

	for(i=0; i<MAD; i++){
		 get = removeMin(daneTestowe);
		error = insert(radixheap, get);	
	}

	for(i=0;i<MAD;i++){
		array[i]=removeMin(radixheap);
		printf("%llu ",array[i]);
	}
	return 0;
}