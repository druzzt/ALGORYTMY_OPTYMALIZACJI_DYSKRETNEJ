#ifndef CONSTANTS2_H
#define CONSTANTS2_H
// CONSTANTS
#define INTEGER	unsigned long long int
//#define INTEGER int
#define I_FORMAT "%llu"
//#define INTEGER unsigned long int
#define SIZE 100
#define VASSIGNP(X,Y)	((X)=(void*)(Y))
#define PASSIGNV(X,Y)	((X)=(INTEGER)(Y))
//#define INF 9223372036854775807
//#define INF 999999
#define INT(X) ((INTEGER)(X))
#define INF (ULLONG_MAX)
//#define INF INF2
#define UNDEFINED 0

#ifndef _CONSTANTS2_H
#define _CONSTANTS2_H
volatile INTEGER  V = 0,
		 E = 0, 
		 numOfSeeked = 0, 
		 numOfSourceP2P = 0, 
		 C = 0,
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