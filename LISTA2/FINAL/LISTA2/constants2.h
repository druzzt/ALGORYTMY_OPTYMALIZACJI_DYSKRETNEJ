#pragma once
#ifndef CONSTANTS2_H
#define CONSTANTS2_H
// CONSTANTS : change the types depending on data you are working on: ###
#define INTEGER	 long long int // IS INTEGER TYPE FOR STORING DATA
#define I_FORMAT "%lld"                // IS TYPE FOR READING AND WRITING
// ######################################################################

#define VASSIGNP(X,Y)	((X)=(void*)(Y))
#define PASSIGNV(X,Y)	((X)=(INTEGER)(Y))
#define INT(X) ((INTEGER)(X))
#define INF (INT_MAX)
#define UNDEFINED 0
#define logC	32

#ifndef _CONSTANTS2_H
#define _CONSTANTS2_H
volatile INTEGER  V = 0,
		 E = 0, 
		 numOfSeeked = 0, 
		 numOfSourceP2P = 0, 
		 C = 0,
		 maxC = 0,
		 lastMin=0;
#endif

#define PRINT_DEBUG 0

typedef struct heapStruct Heap;
typedef struct Bucket Bucket;
typedef struct Buckets Buckets;
typedef struct Vector Vector;
typedef struct Vertex Vertex;
typedef struct Adjacent Adjacent;
typedef struct Node Node;
typedef struct List List;

#define EMPTY 0
#define Q 1
#define S 2
INTEGER* di;
INTEGER* pi;
int *ranges;
Node** gra;
Node* nodes;
INTEGER actually_searched_target;
INTEGER sum_cost=0;
struct Bucket {
	INTEGER idx;
	INTEGER nr;
	Bucket *next, *prev;
};
struct Buckets {
	Bucket *bucket;
	INTEGER size;
};

struct Vector {
	INTEGER first, second, size;
	Vector *next, *prev;
};

struct Vertex {
	short SET;
	INTEGER id;
	INTEGER d;
	INTEGER p;
	Adjacent *adj;
};

struct Adjacent {
	INTEGER parentId;
	INTEGER cost;
	Vertex *vert;
	Adjacent *nextAdj;
};

struct List {
	INTEGER minCost;
	Vertex *vert;
	INTEGER size;
	List *left;
	List *right;
};

struct Node{
	INTEGER idx;
	INTEGER cost;
	Node* next;
};

struct heapStruct {
    INTEGER* heaparray;
    INTEGER capacity;
    INTEGER size;
};

#endif