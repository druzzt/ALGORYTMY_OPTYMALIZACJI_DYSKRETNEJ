#pragma once
#ifndef CONSTANTS2_H
#define CONSTANTS2_H
// CONSTANTS : change the types depending on data you are working on: ###
#define INTEGER	unsigned long long int // IS INTEGER TYPE FOR STORING DATA
#define I_FORMAT "%llu"                // IS TYPE FOR READING AND WRITING
// ######################################################################

#define VASSIGNP(X,Y)	((X)=(void*)(Y))
#define PASSIGNV(X,Y)	((X)=(INTEGER)(Y))
#define INT(X) ((INTEGER)(X))
#define INF (ULLONG_MAX)
#define UNDEFINED 0

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

typedef struct Bucket Bucket;
typedef struct Buckets Buckets;
typedef struct Vector Vector;
typedef struct Vertex Vertex;
typedef struct Adjacent Adjacent;
typedef struct List List;

#define EMPTY 0
#define Q 1
#define S 2

struct Bucket {
	INTEGER idx;
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
#endif