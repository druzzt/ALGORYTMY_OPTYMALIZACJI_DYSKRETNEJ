/** #######################################################
** * 	@Author: Arkadiusz Lewandowski
** *	@Course: Algorytmy optymalizacji dyskretnej
** *	@Subject: Dijkstra's, Dial's and Radix Heap
** *				implementations in C language.
** *				******************************
**  ####################################################*/

/** @file run: make
** 	@program runs:
**	* [dijkstra|dial|radixheap] -d plik_z_danymi.gr -ss zrodla.ss -oss  wyniki.ss.res
**	* [dijkstra|dial|radixheap] -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res
*/

#ifndef PROGRAMS2_C
#define PROGRAMS2_C

#include "headers2.h"
#include "constants2.h"
#include "heap.h"
#include "RadixHeapsINTRO.txt"
#include "MentorsBlessings.txt"
#ifndef INTERFACE
#define INTERFACE int
#endif
// 	#################################################################################
/** ####################################################################
** 	############# ALGORITHM PROTOTYPES #################################
** 	####################################################################
*/
extern Vertex **dijkstra(Vertex **verts, INTEGER s);
extern Vertex **dijkstraP2P(Vertex **verts, INTEGER s, INTEGER t);
extern Vertex **dials(Vertex **verts, INTEGER s);
extern Vertex **dialsP2P(Vertex **verts, INTEGER s, INTEGER t);
extern Vertex **radixheap(Vertex **verts, INTEGER s);
extern Vertex **radixheapP2P(Vertex **verts, INTEGER s, INTEGER t);

// 	#################################################################################
/** ####################################################################
** 	############# LIST OPERATION PROTOTYPES ############################
** 	####################################################################
*/
extern List *newQElem(INTEGER minCost, Vertex *vert,
			   List *left, List *right);
extern List *delQElem(List *queue, Vertex *vert);
extern List *addQElem(List *queue, INTEGER minCost, Vertex *vert);
extern Vertex *extractMin(List *queue);
extern Vertex *initVertex(INTEGER id);
extern Vertex **initAllVertices(Vertex **verts);
extern Adjacent *initAdjacent(INTEGER parentId, 
					   INTEGER cost, Vertex *vert);
extern Adjacent *addNewAdjacent(Adjacent *adjacent, 
						 Adjacent *newConnection);
extern List *newDQElem(Vertex *vert, List *left, List *right);
extern List *deleteListElem(List *list, Vertex *vert);
extern List **remDQElem(List **buckets, Vertex *vert);
extern List **addDQElem(List **buckets, INTEGER minCost, Vertex *vert);
extern Vertex *getMinElem(List **buckets);

// #################################################################################
/** ###################################################################
** ############# FILE OPERATION PROTOTYPES ############################
** ####################################################################
*/
int programnamechecker(char *argv[]);
int programchecker(int argc,char *argv[]);
INTEGER *readSources(char *dataFile);
INTEGER **readPairs(char *dataFile);
Vertex **readFiles(char *dataFile);


// #################################################################################
/** ######################################################################
** ################ LIST INITIALIZERS ####################################
** #######################################################################
*/

/** @complexity: Besides Malloc O(E)
*/
List *initBuckets(Vertex **verts){
	List *bucket; ARLOC_A(bucket, Buckets,(C*V+1));
	INTEGER i=0;
	for(i=0;i<V;i++){
		ARLOC_A(bucket[i].vert,Bucket,1);
		bucket[i].vert->d = UNDEFINED;
		bucket[i].vert->p = i;
		bucket[i].vert->id = i;
		bucket[i].size = 0;
	}
	return bucket;
}

/** @complexity: O(1) - takes first element of a Bucket
*/
List *pushBackQElem(List **bucket, INTEGER index, INTEGER value){
	return bucket[index];
}	

/** @complexity: Besides Malloc - O(1)
*/
List *newDQElem(Vertex *vert, List *left, List *right) {
	List* queue = (List*) malloc(sizeof(List));
	vert->SET = Q;
	queue->vert = vert;
	queue->left = left;
	queue->right = right;
	return queue;
}

/** @complexity: Since it is not NULL 
**					O(V) for each Vertex in List
*/
List *deleteListElem(List *list, Vertex *vert) {
	if(list==NULL) return NULL;
	else {
		if(list->vert->id != vert->id)
		 list->right = deleteListElem(list->right, vert);
		else {
			List *left = list->left;
			List *right = list->right;
			if(left != NULL) left->right = right;
			if(right != NULL) right->left = left;
			free(list);
			list = right;
		}
	}	
	return list;
}

/** @complexity: O(1)
*/
void addBel(Bucket **b, Bucket* n, int nr){
	n->nr = nr;
	n->next = *b;
	if(n->next){
		n->next->prev = n;
	}
	n->prev=NULL;
	*b=n;
}

/** @complexity: O(1)
*/
void delBel(Bucket **b, Bucket* n, int nr){
	if(nr>0){
		if(*b==n) *b=n->next;
		if(n->next != NULL) n->next->prev = n->prev;
		if(n->prev != NULL) n->prev->next = n->next;
	}
}

/** @complexity: O(V)
*/
int *bucketRange(int Cost){
	int maxRange=1;
	while(Cost!=0) {Cost=Cost>>1; maxRange++;}
	maxRange++;
	int *r = malloc(maxRange*sizeof(int));
	int j;
	for(j=0;j<=maxRange; j++) r[j+1]=1<<j;
		r[0]=UNDEFINED;
		r[maxRange-1]=INF;
	for(j=0;j<V;j++){
		di[j]=INF;
		pi[j]=0;
	}
	return r;
}

/* @complexity: O(logC)
*/
void relabel(INTEGER x, int min){
	ranges[0]=min;
	int j;
	for(j=0;j<x;j++){
		ranges[j+1]=ranges[0]+(1<<j);
	}
	ranges[x]=INF;
}

/** @complexity: O(V)
*/
Bucket *initBucketZ(Bucket *q){
	int i;
	q=malloc(V*sizeof(Bucket));
	for(i=0;i<V;i++){
		q[i].idx =i;
		q[i].nr = -1;
	}
	return q;
}

/** @complexity: O(logC)
*/
int selectNode(Bucket **b, int it){
	for(it=it;it<logC&&b[it]==NULL;it++)
		if(it==logC) break;
	return it;
}


/** @complexity: Queue for Dials Buckets
**				O(1) * O(V) since we iterate through
**				all the buckets
*/
List **remDQElem(List **buckets, Vertex *vert) {
	INTEGER minCost = vert->d;
	buckets[minCost] = deleteListElem(buckets[minCost], vert);
	return buckets;
}

/** @complexity: O(1) since we add element between given Vertices
**						It is a head or tail at once or
**						append it at the end to the tail
*/
List **addDQElem(List **buckets, INTEGER minCost, Vertex *vert) {
	if(vert->SET != S) {
		if(buckets[minCost] == NULL) 
			buckets[minCost] = newDQElem(vert, NULL, NULL);
		else {
			List *newElement = newDQElem(vert, NULL, buckets[minCost]);
			buckets[minCost]->left = newElement;
			buckets[minCost] = newElement;	
		}
	}
	return buckets;
}

/** @complexity: Search for first non-empty bucket
** 		Worst case is searching through all the buckets.
*/
Vertex *getMinElem(List **buckets) {
	INTEGER i;
	for(i = lastMin; i < C; i++) {
		if(buckets[i] != NULL) {
			lastMin = i;
			return buckets[i]->vert;
		}
	}
	lastMin = C+ 1;
	return NULL;
}

/** @complexity: Besides Malloc - O(1) for initializing element
**					for a Queue
*/
List *newQElem(INTEGER minCost, Vertex *vert,
					 List *left, List *right) {
	List* queue;
	ARLOC_A((queue), List, 1);
	vert->SET = Q;
	queue->minCost = minCost;
	queue->vert = vert;
	queue->left = left;
	queue->right = right;
	return queue;
}

/** @complexity: O(C)
*/
List *delQElem(List *queue, Vertex *vert) {
	INTEGER minCost = vert->d;
	if(queue==NULL) return NULL;
	else{
		if(queue->vert->id == vert->id){
			List *left = queue->left;
			List *right = queue->right;
			if(left != NULL) left->right = right;
			if(right != NULL) right->left = left;
			free(queue);
			queue = right;
		}
		else if(queue->minCost < minCost || queue->vert->id != vert->id)
			queue->right = delQElem(queue->right, vert);
		else{ printf("~");}
		return queue;
	}
}

/** @complexity: With worst Case O(C)
* /
List *delQElem(List *queue, Vertex *vert) {
	INTEGER minCost = vert->d;
	if(queue==NULL) return NULL;
	else {
		if(queue->minCost < minCost)
			queue->right = 
			delQElem(queue->right, vert);
		else {
			if(queue->vert->id != vert->id)
			 	queue->right = 
			 	delQElem(queue->right, vert);
			else {
				List *left = queue->left;
				List *right = queue->right;
				if(left != NULL) left->right = right;
				if(right != NULL) right->left = left;
				free(queue);
				queue = right;
			}
		}
	}
	return queue;
}*/

/** @complexity: O(V)
*/
List *addQElem(List *queue, INTEGER cost, Vertex *vert) {
	List *currentPosition = queue;	
	if(vert->SET != S) {
		if(queue == NULL) queue = 
			newQElem(cost, vert, NULL, NULL);
		else {
			if(currentPosition->minCost >= cost) {
				List *newElement = 
				newQElem(cost,
								 vert,
								 NULL, 
								 currentPosition);
				currentPosition->left = newElement;
				queue = newElement;	
			}
			else {
				while(currentPosition->right != NULL &&
				 currentPosition->minCost < cost) {
					currentPosition = currentPosition->right;
				}
				if(currentPosition->minCost < cost) {
					List *newElement = 
					newQElem(cost, 
									vert, 
									currentPosition, 
									NULL);
					currentPosition->right = newElement;
				}
				else {
					List *newElement = 
					newQElem(cost, vert, 
							currentPosition->left, 
							currentPosition);	
					currentPosition->left->right = newElement;
					currentPosition->left = newElement;
				}
			}
		}
	}
	return queue;
}

/** @complexity: O(1)
*/
Vertex *extractMin(List *queue) {
	Vertex *vert = NULL;
	if(queue) vert = queue->vert;
	return vert;
}

/** @complexity: O(1)
*/
Vertex* initVertex(INTEGER id) {
	Vertex* vert;
	ARLOC_A(vert, Vertex,1);
	vert->id = id+1;
	vert->d = INF;
	vert->p = UNDEFINED;
	vert->adj = NULL;
	return vert;
}

/** @complexity: O(V)
*/
Vertex **initAllVertices(Vertex **verts) {
	INTEGER i=0;
	for(i=0; i<V; i++) {
		verts[i]->SET = EMPTY;
		verts[i]->d = INF;
		verts[i]->p = UNDEFINED;
	}
	lastMin=0;
	return verts;
}

/** @complexity: O(1)
*/
Adjacent *initAdjacent(INTEGER parentId, 
							INTEGER cost, 
							Vertex *vert) {
	Adjacent* adj;
	ARLOC_A(adj, Adjacent,1);
	adj->parentId = parentId;
	adj->cost = cost;
	adj->vert = vert;
	adj->nextAdj = NULL;
	return adj;
}
/** @complexity: O(V) since it is appending only when it is
**					adjacent to other vertex
*/
Adjacent *addNewAdjacent(Adjacent *adjacent, 
							  Adjacent *newConnection) {
	if(adjacent == NULL) return newConnection;
	else {
		adjacent->nextAdj = 
		addNewAdjacent(adjacent->nextAdj,newConnection);
		return adjacent;
	} 
}




// #################################################################################
/** ###################################################################
** ############# PROGRAM BODY CLAUSES #################################
** ####################################################################
*/
// ####################### DIJKSTRAS ###############################################
/** DIJKSTRA'S ALGORITHM:
** * @complexity: For single source 					O(1)*
** * @complexity: create Queue consisting of vertexes ~ O(e)+
** * @complexity: while Queue is not empty 			~	O(v)*
** * @complexity: remove min element from Queue 	~	O(v)+
** * @complexity: while every min element has cheaper neighbours ~ O(v)
** * @complexity_SUM: O(1) * (O(e*O(1))+O(v)*O(v)) ~ O(e+v^2)
*/
Vertex **dijkstra(Vertex **verts, INTEGER s)
{
	List *queue = NULL;
	verts[s-1]->d = 0;
	queue = addQElem(queue, verts[s-1]->d, verts[s-1]);
	while(queue != NULL) {
		Vertex *minCostVert = extractMin(queue);
		queue = delQElem(queue, minCostVert);
		minCostVert->SET = S;
		Adjacent *adj = minCostVert->adj;
		while(adj != NULL) {
			Vertex *vert = adj->vert;
			if(vert->SET != S) {
				if(vert->d > minCostVert->d + adj->cost) {
					if(vert->SET == Q) queue = delQElem(queue, vert);
					vert->d = minCostVert->d + adj->cost;
					vert->p = minCostVert->id;
					queue = addQElem(queue, vert->d, vert);
					vert->SET = Q;
				}	
			}
			
			adj = adj->nextAdj;
		}
		free(adj);
		
	}
	free(queue);
	return verts;
}

/** DIJKSTRA'S ALGORITHM P2P:
** * @complexity: For single source 					O(1)*
** * @complexity: create Queue consisting of vertexes ~ O(e)+
** * @complexity: while Queue is not empty 			~	O(v)*
** * @complexity: remove min element from Queue 	~	O(v)+
** * @complexity: while every min element has cheaper neighbours ~ O(v)
** * @complexity_SUM: O(1) * (O(e*O(1))+O(v)*O(v)) ~ O(e+v^2)
** * With subject to that if Vertex with MinCost is a Target Vertex
** * algorithm ends with path to this vertex
*/
Vertex **dijkstraP2P(Vertex **verts, INTEGER s, INTEGER t) {
	List *queue = NULL;
	verts[s-1]->d = 0;
	queue = addQElem(queue, verts[s-1]->d, verts[s-1]);
	while(queue != NULL) {
		Vertex *minCostVert = extractMin(queue);
		queue = delQElem(queue, minCostVert);
		if(minCostVert->id == t) return verts;
		minCostVert->SET = S;
		Adjacent *adj = minCostVert->adj;
		while(adj != NULL) {
			Vertex *vert = adj->vert;
			if(vert->SET != S) {
				if(vert->d > minCostVert->d + adj->cost) {
					if(vert->SET == Q) queue = delQElem(queue, vert);
					vert->d = minCostVert->d + adj->cost;
					vert->p = minCostVert->id;
					queue = addQElem(queue, vert->d, vert);
					vert->SET = Q;
				}
			}
			adj = adj->nextAdj;
		}
	}
	return verts;
}

// ####################### DIALS ###################################################
/** DIAL'S ALGORITHM :
** * @complexity:   Significantly faster than casual Dijkstra's
** * @complexity: O(nC) + O(1) + O(E)
** * @complexity: Since when first getMinElem is done, next takes O(1)
** * @complexity: Since when first remDQElem is done, next takes O(1)
** * @complexity: Since when first addDQElem is done, next takes O(1)
** * @complexity: All together gives O(nC + O(E)) ~ O(E + nC)
*/
Vertex **dials(Vertex **verts, INTEGER s){
	List **buckets = malloc(C*sizeof(List));
	verts[s-1]->d = 0;
	buckets = addDQElem(buckets, verts[s-1]->d, verts[s-1]);
	while(getMinElem(buckets) != NULL) {
		Vertex *minCostVert = getMinElem(buckets);
		buckets = remDQElem(buckets, minCostVert);
		minCostVert->SET = S;
		Adjacent *adjacent = minCostVert->adj;
		while(adjacent != NULL) {
			Vertex *vert = adjacent->vert;
			if(vert->SET != S) {
				if(vert->d > minCostVert->d + adjacent->cost) {
					if(vert->SET == Q) buckets = remDQElem(buckets, vert);
					vert->d = minCostVert->d + adjacent->cost;
					vert->p = minCostVert->id;
					buckets = addDQElem(buckets, vert->d, vert);
					vert->SET = Q;
				}
			}
			adjacent = adjacent->nextAdj;
		}
		free(buckets);
	}
	return verts;
}
/** DIAL'S P2P ALGORITHM :
** * @complexity:   Significantly faster than casual Dijkstra's
** * @complexity: O(nC) + O(1) + 3*O(E)
** * @complexity: Since when first getMinElem is done, next takes O(1)
** * @complexity: Since when first remDQElem is done, next takes O(1)
** * @complexity: Since when first addDQElem is done, next takes O(1)
** * @complexity: All together gives O(nC + O(E)) ~ O(E + nC)
** * @complexity: it returns when Vertex's id with minimal cost 
** * 						is id of seeked Vertex.
*/
Vertex **dialsP2P(Vertex **verts, INTEGER s, INTEGER t){
	List **buckets = (List**)malloc(C*sizeof(List));
	verts[s-1]->d = 0;
	buckets = addDQElem(buckets, verts[s-1]->d, verts[s-1]);
	while(getMinElem(buckets) != NULL) {
		Vertex *minCostVert = getMinElem(buckets);
		buckets = remDQElem(buckets, minCostVert);
		if(minCostVert->id == t) return verts;
		minCostVert->SET = S;
		Adjacent *adjacent = minCostVert->adj;
		while(adjacent != NULL) {
			Vertex *vert = adjacent->vert;
			if(vert->SET != S) {
				if(vert->d > minCostVert->d + adjacent->cost) {
					if(vert->SET == Q) buckets = remDQElem(buckets, vert);
					vert->d = minCostVert->d + adjacent->cost;
					vert->p = minCostVert->id;
					buckets = addDQElem(buckets, vert->d, vert);
					vert->SET = Q;
				}
			}
			adjacent = adjacent->nextAdj;
		}
	}
	return verts;
}


// ####################### RADIX HEAPS #############################################
/** SHOULD USE The existence of an O(m + n log n) bound for arbitrary 
real-valued costs suggests the problem of obtaining a bound for integer
costs of the form O(m + nf(C)) for some function f of the number sizes,
with f growing as slowly as possible. An algorithm independently 
discovered by Dial [4] and Johnson [9] runs in O(m + nC) time. 
Based on the existence of the Van Emde Boas-Kaas- Zijlstra data structure,
one might hope for a bound of O(m + nlog log C). Obtaining such a bound is
an open problem. We shall develop a data structure that results in a bound
of O(m + log C). Our data structure, the radix heap, exploits special 
properties of the heap operations in Dijkstra's algorithm. The most 
important of these properties is that successive delete min operations
return vertices in nondecreasing order by tentative cost. The simplest 
form of the data structure, the one-level radix heap, was originally 
proposed by Johnson [10], who used it to obtain an 
O(m log log C + n log C log log C) 
time bound for Dijkstra's algorithm. By slightly changing the implementation,
we reduce the time to O(m + a log C). 


One-Level Radix Heaps
Radix heaps rely on the following properties of Dijkstra's algorithm:
(i) For any vertex v, if d(v) is finite, d(v) E [0 .. nC].'1
(ii) For any vertex v # s, if v is labeled, d(v) E [d(x) .. d(x) + C], where x is the
most recently scanned vertex.
Property (ii) implies in particular that successive delete min operations return
vertices in nondecreasing order by tentative cost.
A one-level radix heap is a collection of B = lg(C + 1)1 + 2 buckets, 
2 indexed from I through B. Each bucket has an associated size. 
The size of bucket i is denoted by size(i) and defined as follows:
size(l)= 1;
size(i)-=2'2 for 2 i B-;
size(B) = nC + 1.
Observe that the bucket sizes satisfy the following important inequality: j-
Z size(i) > min{size(j), C + 1} for 2 j < B. (1)
Each bucket also has a range that is an interval of integers. Initially the ranges 
of the buckets partition the interval [0 . . nC + ]. In general the ranges partition 
the interval [dmin .. nC + ], where dmin is the maximum label of a scanned node.
For each bucket i the upper bound u(i) of its interval is maintained; the range of 
bucket i is range(i) = [u(i - 1) + I .. u(i)], with the conventions that
u(0) = dmin - I and rnge(i) = 0 if u(i - ) Ž u(i). Whereas the sizes of all
buckets are fixed throughout the computation, the ranges change; for each 
bucket i, u(i) is a nondecreasing function of time.
Initiallyu(i)=2- - Ifor I i B- 1, u(B)=nC+ 1.Observethatthis implies
Irange(i) size(i). This inequality is maintained throughout the com- 
putation for each bucket. The labeled vertices are stored in the buckets,
with vertex v stored in bucket i if d(v) E range(i). Initially, vertex s is
inserted into bucket I. The range of bucket I is maintained so that every 
vertex v in bucket I has d(v) = tz(1); thus the effective range of bucket 
I contains only u(1).
Each bucket is represented by a doubly linked list of its vertices, to make 
insertion and deletion possible in constant time. In addition, stored with each
vertex is the index of the bucket containing it.
The three heap operations are implemented as follows. To insert a newly labeled
vertex v, examine values of i in decreasing order, starting with i = B, until 
finding the largest i such that u(i) < d(v); then insert v into bucket i + 1. 
To decrease the key of a vertex v, remove v from its current bucket, say bucket j.
Reduce the key of v. Proceed as in an insertion to reinsert v into the correct 
bucket, but begin with bucket i = j.
For a single vertex v, the time spent on insertion and all decrease 
operations is O(log C) plus O(1) per decrease, because the index of the bucket 
containing v can never increase. Thus, the total time for all such operations 
during a run of Dijkstra's algorithm is O(m + n log C).
The most complicated operation is delete min, which is performed as follows. If
bucket 1is nonempty, return any vertex in bucket . Otherwise, find the nonempty 
bucket of smallest index, say bucket j. By scanning through the items in bucket j,
find a vertex of smallest tentative cost, say v. Save v to return as the result 
of the delete min and distribute the remaining vertices in bucket j among buckets
of smaller index, as follows. Replace u(0) by d(v) - 1, u(l) by d(v), and 
for i running from 2 through] - 1, replace u(zi) by mintu(i - ) + size(i), (j)}.
Remove each vertex from bucketj and reinsert it as in decrease;do not reinsert v.
Property (ii) and inequality (1) guarantee that, ifj > 2 in a delete min, every 
vertex in bucket j will move to a bucket of strictly smaller index. It follows 
that the time spent on delete min operations is (log C) per delete min
plus (log C) per vertex, for a total of O(n log C) during 
a run of Dijkstra's algorithm. We conclude that the total running 
time of Dijkstra's algorithm with this implementation is O(m + n log C). 
The space required as O(m + log C). Johnson [10], using the same data structure,
obtained a bound worse by a factor of log log C because he used binary search 
instead of sequential scan to reinsert vertices into buckets.
      */



Vertex **radixheap(Vertex **verts, INTEGER s){
	Bucket **bucket = malloc(logC*sizeof(Bucket*));
	Bucket *queue; queue = initBucketZ(queue);
	printf(""); // bez tego printfa bedzie SEGFAULT :(
	addBel(&bucket[0], &queue[s], 0);
    di[s] = 0;
    INTEGER iterator = 0;
	INTEGER labeled = 0;
	for(labeled=0; labeled < V; labeled++){
		iterator = selectNode(bucket,iterator);
		ifContainsOnlyOneVertex(iterator,ranges,bucket,next){
			int no = bucket[iterator]->idx;
			int min = di[no];
			Bucket *tmp = bucket[iterator]->next;
			for(tmp=bucket[iterator]->next;tmp;tmp=tmp->next){
				if(di[tmp->idx] < min){
					no = tmp->idx;
					min=di[no];
				}
			}
			relabel(iterator,min);
			while(bucket[iterator]!=NULL){
				int vertex_nr = bucket[iterator]->idx;
				delBel(&bucket[iterator],&queue[vertex_nr],iterator);
				int dest= iterator-1;
				for(dest=dest; dest>=0 && di[vertex_nr] < ranges[dest]; dest--);
				addBel(&bucket[dest],&queue[vertex_nr],dest);
			}
			iterator=0;
		}

		Bucket* minimal = bucket[iterator];
		int min_no = minimal->idx;
		delBel(&bucket[iterator],&queue[min_no], iterator);
		//printf("1");
		//update neighbours
		Node* n;
		modificationOfBuckets8TheirRangesWithSubjectToHavingMinimalWageArcInFistBucket(INTEGER,
			n,gra,min_no,next,cost,nr,di,n_no,pi,dest,ranges,bucket,queue,printf,exit,delBel,addBel);
	
	}
	//free(b);
	//free(q);
	return verts;
}



Vertex **radixheapP2P(Vertex **verts, INTEGER s, INTEGER t){
Bucket **b = malloc(logC*sizeof(Bucket*));
	Bucket *q; q = initBucketZ(q);
	printf("radix");
	addBel(&b[0], &q[s], 0);
    di[s] = 0;
    INTEGER iterator = 0;
	INTEGER labeled = 0;
	for(labeled=0; labeled < V; labeled++){
		//printf(""I_FORMAT"\n",labeled);
		iterator = selectNode(b,iterator);
		if(!(iterator==0||ranges[iterator+1]-ranges[iterator]==1 || b[iterator]->next==NULL)){
			int no = b[iterator]->idx;
			int min = di[no];
			Bucket *tmp = b[iterator]->next;
			for(tmp=b[iterator]->next;tmp;tmp=tmp->next){
				if(di[tmp->idx] < min){
					no = tmp->idx;
					min=di[no];
				}
			}
			relabel(iterator,min);
			while(b[iterator]!=NULL){
				int n_no = b[iterator]->idx;
				delBel(&b[iterator],&q[n_no],iterator);
				int dest= iterator-1;
				for(dest=dest; dest>=0 && di[n_no] < ranges[dest]; dest--);
				addBel(&b[dest],&q[n_no],dest);
			}
			iterator=0;
		}

		Bucket* minimal = b[iterator];
		int min_no = minimal->idx;
		delBel(&b[iterator],&q[min_no], iterator);
		//printf("1");
		//update neighbours
		Node* n;
		modificationOfBuckets8TheirRangesWithSubjectToHavingMinimalWageArcInFistBucket(INTEGER,
			n,gra,min_no,next,cost,nr,di,n_no,pi,dest,ranges,b,q,printf,exit,delBel,addBel);
		if(min_no==actually_searched_target)
			break;
		
	}
	free(b);
	free(q);
	return verts;
}


// #################################################################################
/** #######################################################################
** #################### MAIN MODULE #######################################
** ########################################################################
*/
// 					EXTERN INTERFACE

INTERFACE shortest_path_problem(int argc, char *argv[])
{
    
	((errno = programnamechecker(argv)),	_ER_CHCK(errno));
	((errno = programchecker(argc, argv)),	_ER_CHCK(errno));
	if(errno!=SUCCESS) return FAILURE;

	time(&t1);
    printf("%s %s %s %s, Start:%s",argv[0],argv[2],argv[4],argv[6],_LOG_CTIME(t1));
	
	// SAVE OUTPUT
	INTEGER isP2PMethod = 0;
	INTEGER i = 0;
	char *dataFile, *sourcesFile, *resultsFile;
	if((argc-1)%2 == 0 &&  argc > 1) {
		for(i = 1; i<argc; i++) {
			if(strcmp(argv[i],"-d") == 0) {
				i++;
				dataFile = argv[i];
			} 
			else if(strcmp(argv[i], "-ss") == 0) {
				i++;
				sourcesFile = argv[i];
			}
			else if(strcmp(argv[i], "-p2p") == 0) {
				i++;
				isP2PMethod = 1;
				sourcesFile = argv[i];
			}
			else if(strcmp(argv[i], "-oss") == 0 || strcmp(argv[i], "-op2p") == 0) {
				i++;
				resultsFile = argv[i];
			}
			else {
				printf("Incorrect parameters: %s!\n", argv[i]);
				return 0;
			}
		}
		Vertex **verts = readFiles(dataFile);
		for(i=0; i<V; i++) {
			Adjacent *conn;
			conn = verts[i]->adj;
			while (conn != NULL) {
				conn = conn->nextAdj;
			}
		}
		if(isP2PMethod) {
			INTEGER **pairs = readPairs(sourcesFile);
			printf(".");
			FILE *file;
		   	if ((file=fopen(resultsFile, "w"))==NULL) {
		     		printf ("Output data file cannot be open!\n");
		     		exit(1);
		     	}
			
			fprintf(file, "f %s %s\n", dataFile, sourcesFile);
			fprintf(file, "g "I_FORMAT" "I_FORMAT" %d "I_FORMAT"\n", V, E, 0, maxC);
			printf("P2P");
			for(i = 0; i < numOfSourceP2P; i++) {
				if(PATH_PROB==1){ //printf("%d",PATH_PROB);
				verts = dijkstraP2P(verts, pairs[i][0], pairs[i][1]);}
				else if(PATH_PROB==2){ //printf("%d",PATH_PROB);
				verts = dialsP2P(verts, pairs[i][0], pairs[i][1]);}
				else if(PATH_PROB==3){ //printf("%d",PATH_PROB);
				actually_searched_target=pairs[i][1];
				verts = radixheapP2P(verts, pairs[i][0], pairs[i][1]);}

				fprintf(file, "d "I_FORMAT" "I_FORMAT" "I_FORMAT"\n", 
					pairs[i][0], pairs[i][1], verts[pairs[i][1]-1]->d);
				verts = initAllVertices(verts);
			}
			fclose (file);
		}
		else {
			INTEGER *sources = readSources(sourcesFile);
			printf(".");
			double avgTime;

			FILE *file;
		   	if ((file=fopen(resultsFile, "w"))==NULL) {
		     		printf ("Cannot create output data file!\n");
		     		exit(1);
		     	}
		    if(PATH_PROB==1){ //printf("%d",PATH_PROB);
			 fprintf(file, "p res sp ss dijkstra\n");}
			else if(PATH_PROB==2){ //printf("%d",PATH_PROB);
			 fprintf(file, "p res sp ss dial\n");}
			else if(PATH_PROB==3){ //printf("%d",PATH_PROB);
			 fprintf(file, "p res sp ss radixheap\n");}

			fprintf(file, "f %s %s\n", dataFile, sourcesFile);
			fprintf(file, "g "I_FORMAT" "I_FORMAT" %d "I_FORMAT"\n", V, E, 0, maxC);

			struct timeval stop, start;
			//printf("...\n");
			gettimeofday(&start, NULL);
			di=calloc(V,sizeof(INTEGER));
			pi=calloc(V,sizeof(INTEGER));
			ranges=bucketRange(INF);
			actually_searched_target=-1;
			for(i = 0; i < numOfSeeked; i++) {
				if(PATH_PROB==1){ //printf("%d",PATH_PROB);
					verts = dijkstra(verts, sources[i]);}
				else if(PATH_PROB==2){ //printf("%d",PATH_PROB);
					verts = dials(verts, sources[i]);}
				else if(PATH_PROB==3){ //printf("%d",PATH_PROB);
					verts = radixheap(verts, sources[i]);}

				verts = initAllVertices(verts);
			}
			gettimeofday(&stop, NULL);
			double secs = 
				((double)(stop.tv_usec - start.tv_usec) / 1000 +
			 	 (double)(stop.tv_sec - start.tv_sec) * 1000);
			fprintf(file, "t %lf", secs / (double)numOfSeeked);
			fclose (file);
		}
	}
	time(&t2);
	printf("%s %s %s %s, STOP:%s",argv[0],argv[2],argv[4],argv[6],_LOG_CTIME(t2));
	double difference = difftime(t2, t1);
	if(verbose)
	(/*printf("%f with proc.clocks/s = %d\n",difference,CLOCKS_PER_SEC)*/NULL,
	printf("In summary: %f\n", difference/CLOCKS_PER_SEC));
	return errno;
}


int main(int argc, char* argv[]){
	return (shortest_path_problem(argc, argv));
}

// #################################################################################
/** #########################################################################
**  ######### FILE PROCESSING OPERATIONS ####################################
**  #########################################################################
*/

Vertex **readFiles(char *dataFile) {
	INTEGER *graph, i = 0;
	Vertex **verts;
	FILE *file;

	char lineType, buffer[128];
   	if ((file=fopen(dataFile, "r"))==NULL) {
     		printf ("Cannot open data file! readFiles\n");
     		exit(1);
     	}
   	while (fscanf(file, "%c", &lineType) != EOF)
	{
		if(lineType == 'c') fgets(buffer, sizeof(buffer), file);
		else if(lineType == 'p') {
			fscanf(file, " sp "I_FORMAT" "I_FORMAT"", &V, &E);
			graph = malloc(V*sizeof(INTEGER));
			verts = malloc(V*sizeof(Vertex));
			gra = calloc(V,sizeof(Node*));
			nodes=calloc(E,sizeof(Node));
			INTEGER j;
			for(j = 0; j<V; j++){
			 verts[j] = initVertex(j);
			 graph[j] = 0;
			}
		}
		else if(lineType == 'a') {
			INTEGER a, b, cost;
			fscanf(file, " "I_FORMAT" "I_FORMAT" "I_FORMAT"", &a, &b, &cost);
			nodes[i].next = gra[a-1];
			gra[a-1]=&nodes[i];
			nodes[i].idx = b-1;
			nodes[i].cost = cost;
			Adjacent *newConnection = initAdjacent(a, cost, verts[b-1]);
			if(cost > maxC) maxC = cost;
			verts[a-1]->adj = addNewAdjacent(verts[a-1]->adj, newConnection);
			if(graph[b-1] < cost) graph[b-1]=cost;
			i++;
		}		
		else if(lineType != ' ' && lineType != '\t' && lineType != '\n') {
			printf("Incorrect data!\n");
		}
	}
   	fclose (file);
   	for(i=0; i<=V; i++) C+=graph[i];
	return verts;
}

INTEGER **readPairs(char *dataFile) {
	INTEGER **pairs, i = 0;
	FILE *file;
	char lineType, buffer[128];
   	if ((file=fopen(dataFile, "r"))==NULL) {
     		printf ("Cannot open data file! readPairs\n");
     		exit(1);
     	}
	i = 0;
   	while (fscanf(file, "%c", &lineType) != EOF)
	{
		if(lineType == 'c') fgets(buffer, sizeof(buffer), file);
		else if(lineType == 'p') {
			fscanf(file, " aux sp p2p "I_FORMAT"", &numOfSourceP2P);
			pairs = (INTEGER**)malloc(numOfSourceP2P*2*sizeof(INTEGER));
		}
		else if(lineType == 'q') {
			pairs[i] = (INTEGER*)malloc(2*sizeof(INTEGER));
			fscanf(file, " "I_FORMAT" "I_FORMAT"", &pairs[i][0], &pairs[i][1]);
			i++;
		}		
		else if(lineType != ' ' && lineType != '\t' && lineType != '\n') {
			printf("Incorrect data!\n");
		}
	}
   	fclose (file);
	return pairs;
}

INTEGER *readSources(char *dataFile) {
	INTEGER *sources, i = 0;
	FILE *file;
	char lineType, buffer[128];
   	if ((file=fopen(dataFile, "r"))==NULL) {
     		printf ("Cannot open data file! readSources\n");
     		exit(1);
     	}
	i=0;
   	while (fscanf(file, "%c", &lineType) != EOF)
	{
		if(lineType == 'c') fgets(buffer, sizeof(buffer), file);
		else if(lineType == 'p') {
			fscanf(file, " aux sp ss "I_FORMAT"", &numOfSeeked);
			sources = (INTEGER*)malloc(numOfSeeked*sizeof(INTEGER));
		}
		else if(lineType == 's') {
			fscanf(file, " "I_FORMAT"", &sources[i]);
			i++;
		}
		else if(lineType != ' ' && lineType != '\t' && lineType != '\n') {
			printf("Incorrect sources file!\n");
		}
	}
   	fclose (file);
	return sources;
}

// #################################################################################
/** #####################################################################
** ############ RUN  SPECS ##############################################
** ######################################################################
*/

int programchecker(int argc,char *argv[])
{
	if(argc	>	sizeofargc++ 		&&
	argc	<=	maxnumofargs){
	if(argc	>	sizeofargc++ 		&&
	argv[dflag][fletter] == d){
	if(argc	>	sizeofargc++ 		&&
	argv[grext][zletter] != eof){
	if(argc	>	sizeofargc++ 		&&
	((argv[ssflag][fletter] == s 	&&
	argv[ssflag][sletter] 	== s)	||
	(argv[p2pflag][fletter]	== p 	&&
	argv[p2pflag][sletter]	== two 	&&
	argv[p2pflag][tletter]  == p))){
	if(argc	>	sizeofargc++ 		&&
	argv[ssext][zletter] != eof){
	if(argc	>	sizeofargc++ 		&&
	((argv[ossflag][fletter] == o 	&&
	argv[ossflag][sletter]   == s 	&&
	argv[ossflag][tletter]   == s)	||
	(argv[op2pflag][fletter] == o 	&&
	argv[op2pflag][sletter]  == p 	&&
 	argv[op2pflag][tletter]  == two &&
 	argv[op2pflag][ftletter] == p))){
	if(argc	>	sizeofargc++ 		&&
	argv[ossext][zletter] != eof){
	_COM_ARGSOK();
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	}else{INFORM(argv[progflag],argc);}
	return (SUCCESS);
}

int programnamechecker(char *argv[])
{
	if(argv[progflag][sletter]== d)  {
	if(argv[progflag][tletter]== j  ||
	   argv[progflag][tletter]== ii)  {
	if(argv[progflag][ftletter]==ii  ||
	   argv[progflag][ftletter]==j)  {
	_COM_DJIKSTRA();
	PATH_PROB=1;
	}
	if(argv[progflag][ftletter]==a){
	_COM_DIAL();
	PATH_PROB=2;
	}}else{
	INFORM(argv[progflag],PATH_PROB);
	_COM_WRONGNAME();
	}}
	else if(argv[progflag][sletter]==r){
	_COM_RADIXHEAP();
	PATH_PROB=3;
	}else{
	INFORM(argv[progflag],PATH_PROB);
	_COM_WRONGNAME();
	}
	return (SUCCESS);
}


#endif





