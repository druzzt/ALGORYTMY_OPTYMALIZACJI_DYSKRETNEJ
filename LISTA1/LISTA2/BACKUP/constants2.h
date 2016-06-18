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
#define INF (999999999)
//#define INF INF2
#define UNDEFINED 0
INTEGER qVerts = 0, qArcs = 0, qSources = 0, qPairs = 0, maxCost = 0;
typedef struct Vert Vert;
typedef struct Adjacent Adjacent;
typedef struct List List;
#define EMPTY 0
#define Q 1
#define S 2
struct Vert {
	INTEGER id;
	INTEGER d;
	INTEGER p;
	short inSet;
	Adjacent *adj;
};

struct Adjacent {
	INTEGER parentId;
	INTEGER cost;
	Vert *vert;
	Adjacent *nextAdj;
};

struct List {
	INTEGER minCost;
	Vert *vert;
	List *left;
	List *right;
};