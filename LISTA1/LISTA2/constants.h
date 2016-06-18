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


typedef struct Tablica {
	void *s;
	void *t;
	void *v;
	//short end;
} Tablica;


typedef struct List {
	Tablica tab;
    struct List *next, *prev;
} List;

struct node {
	void *s;
	void *dist;
	void *prev;
	void **neighbours;
	void **predecesors;
};

typedef struct Queue {
	struct node tab;
    struct Queue *next, *prev;
} Queue;
