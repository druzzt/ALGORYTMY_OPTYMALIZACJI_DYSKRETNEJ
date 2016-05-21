
#include "headers2.h"
/* PROTOTYPES */
List *newQElem(INTEGER minCost, Vertex *vert,
					 List *left, List *right);
List *delQElem(List *queue, Vertex *vert);
List *addQElem(List *queue, int minCost, Vertex *vert);
Vertex *extractMin(List *queue);
Vertex *initVertex(INTEGER id);
Adjacent *initAdjacent(INTEGER parentId, 
							INTEGER cost, 
							Vertex *vert);
Adjacent *addNewAdjacent(Adjacent *adjacent, 
							  Adjacent *newConnection);
Vertex **initAllVertices(Vertex **verts);
/*
argv[0] -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res
argv[0] -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res
*/

/* FORMAL SPECS *///#######################################
/** Const Complexity */
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
/** Const Complexity */
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


Vertex **dijkstra(Vertex **verts, INTEGER s)
{
	List *queue = NULL;
	verts[s-1]->d = 0;
	queue = addQElem(queue, verts[s-1]->d, verts[s-1]);
	while(queue != NULL) {
		Vertex *minCostVert = extractMin(queue);
		queue = delQElem(queue, minCostVert);
		minCostVert->inSet = S;
		Adjacent *adj = minCostVert->adj;
		while(adj != NULL) {
			Vertex *vert = adj->vert;
			if(vert->inSet != S) {
				if(vert->d > minCostVert->d + adj->cost) {
					if(vert->inSet == Q) queue = delQElem(queue, vert);
					vert->d = minCostVert->d + adj->cost;
					vert->p = minCostVert->id;
					queue = addQElem(queue, vert->d, vert);
					vert->inSet = Q;
				}
			}
			adj = adj->nextAdj;
		}
	}
	return verts;
}

Vertex **dijkstraP2P(Vertex **verts, INTEGER s, INTEGER t) {
	List *queue = NULL;
	verts[s-1]->d = 0;
	queue = addQElem(queue, verts[s-1]->d, verts[s-1]);
	while(queue != NULL) {
		Vertex *minCostVert = extractMin(queue);
		queue = delQElem(queue, minCostVert);
		if(minCostVert->id == t) return verts;
		minCostVert->inSet = S;
		Adjacent *adj = minCostVert->adj;
		while(adj != NULL) {
			Vertex *vert = adj->vert;
			if(vert->inSet != S) {
				if(vert->d > minCostVert->d + adj->cost) {
					if(vert->inSet == Q) queue = delQElem(queue, vert);
					vert->d = minCostVert->d + adj->cost;
					vert->p = minCostVert->id;
					queue = addQElem(queue, vert->d, vert);
					vert->inSet = Q;
				}
			}
			adj = adj->nextAdj;
		}
	}
	return verts;
}
Vertex **readFiles(char *dataFile) {
	INTEGER **graph, i = 0;
	Vertex **verts;
	FILE *file;
	char lineType, buffer[128];
   	if ((file=fopen(dataFile, "r"))==NULL) {
     		printf ("Cannot open data file!\n");
     		exit(1);
     	}
	i = 1;
   	while (fscanf(file, "%c", &lineType) != EOF)
	{
		if(lineType == 'c') fgets(buffer, sizeof(buffer), file);
		else if(lineType == 'p') {
			fscanf(file, " sp "I_FORMAT" "I_FORMAT"", &V, &E);
			graph = (INTEGER**)malloc(E*3*sizeof(INTEGER));
			verts = (Vertex**)malloc(V*sizeof(Vertex));
			int j;
			for(j = 0; j<V; j++) verts[j] = initVertex(j);
		}
		else if(lineType == 'a') {
			INTEGER a, b, cost;
			fscanf(file, " "I_FORMAT" "I_FORMAT" "I_FORMAT"", &a, &b, &cost);
			Adjacent *newConnection = initAdjacent(a, cost, verts[b-1]);
			if(cost > maxCost) maxCost = cost;
			verts[a-1]->adj = addNewAdjacent
		(verts[a-1]->adj, newConnection);
		}		
		else if(lineType != ' ' && lineType != '\t' && lineType != '\n') {
			printf("Incorrect data!\n");
		}
	}
   	fclose (file);
	return verts;
}

INTEGER **readPairs(char *dataFile) {
	INTEGER **pairs, i = 0;
	FILE *file;
	char lineType, buffer[128];
   	if ((file=fopen(dataFile, "r"))==NULL) {
     		printf ("Cannot open data file!\n");
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
     		printf ("Cannot open data file!\n");
     		exit(1);
     	}
	
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


int main(int argc, char *argv[])
{
    
	((errno = programnamechecker(argv)),	_ER_CHCK(errno));
	((errno = programchecker(argc, argv)),	_ER_CHCK(errno));
	
	time(&t1);
    printf("%s",_LOG_CTIME(t1));
	
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

			FILE *file;
		   	if ((file=fopen(resultsFile, "w"))==NULL) {
		     		printf ("Output data file cannot be open!\n");
		     		exit(1);
		     	}
			
			fprintf(file, "f %s %s\n", dataFile, sourcesFile);
			fprintf(file, "g "I_FORMAT" "I_FORMAT" %d "I_FORMAT"\n", V, E, 0, maxCost);

			for(i = 0; i < numOfSourceP2P; i++) {
				if(PATH_PROB==1)
				verts = dijkstraP2P(verts, pairs[i][0], pairs[i][1]);
				else if(PATH_PROB==2)
				 ;
				else if(PATH_PROB==3)
				 ;
				fprintf(file, "d "I_FORMAT" "I_FORMAT" "I_FORMAT"\n", 
					pairs[i][0], pairs[i][1], verts[pairs[i][1]-1]->d);
				verts = initAllVertices(verts);
			}
			fclose (file);
		}
		else {
			INTEGER *sources = readSources(sourcesFile);
			double avgTime;

			FILE *file;
		   	if ((file=fopen(resultsFile, "w"))==NULL) {
		     		printf ("Cannot create output data file!\n");
		     		exit(1);
		     	}
		     if(PATH_PROB==1)
			fprintf(file, "p res sp ss dijkstra's\n");
			else if(PATH_PROB==2)
			 ;
			else if(PATH_PROB==3)
			 ;
			fprintf(file, "f %s %s\n", dataFile, sourcesFile);
			fprintf(file, "g "I_FORMAT" "I_FORMAT"%d "I_FORMAT"\n", V, E, 0, maxCost);
			struct timeval stop, start;
			gettimeofday(&start, NULL);
			for(i = 1; i <= numOfSeeked; i++) {
				if(PATH_PROB==1)
				verts = dijkstra(verts, sources[i]);
				else if(PATH_PROB==2)
				 ;
				else if(PATH_PROB==3)
				 ;
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
	printf("%s",_LOG_CTIME(t2));
	double difference = difftime(t2, t1);
	if(verbose)
	(printf("%f with proc.clocks/s = %d\n",difference,CLOCKS_PER_SEC),
	printf("Clock's ticks in summary: %f\n", difference*CLOCKS_PER_SEC));
	return errno;
}








/* LIST INITIALIZERS *///#######################################
/** O(n) complexity */
List *newQElem(INTEGER minCost, Vertex *vert,
					 List *left, List *right) {
	List* queue;
	ARLOC_A((queue), List, 1);
	vert->inSet = Q;
	queue->minCost = minCost;
	queue->vert = vert;
	queue->left = left;
	queue->right = right;
	return queue;
}

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
}

List *addQElem(List *queue, int minCost, Vertex *vert) {
	List *currentPosition = queue;	
	if(vert->inSet != S) {
		// []
		if(queue == NULL) queue = 
			newQElem(minCost, vert, NULL, NULL);
		else {
			// () -> A
			if(currentPosition->minCost >= minCost) {
				List *newElement = 
				newQElem(minCost,
								 vert,
								 NULL, 
								 currentPosition);
				currentPosition->left = newElement;
				queue = newElement;	
			}
			else {
				while(currentPosition->right != NULL &&
				 currentPosition->minCost < minCost) {
					currentPosition = currentPosition->right;
				}
				// A -> ()
				if(currentPosition->minCost < minCost) {
					List *newElement = 
					newQElem(minCost, 
									vert, 
									currentPosition, 
									NULL);
					currentPosition->right = newElement;
				}
				// A -> () -> B 
				else {
					List *newElement = 
					newQElem(minCost, vert, 
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

Vertex *extractMin(List *queue) {
	Vertex *vert = NULL;
	if(queue) vert = queue->vert;
	return vert;
}

Vertex* initVertex(INTEGER id) {
	Vertex* vert;
	ARLOC_A(vert, Vertex,1);
	vert->id = id+1;
	vert->d = INF;
	vert->p = 0;
	vert->adj = NULL;
	return vert;
}


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

Adjacent *addNewAdjacent(Adjacent *adjacent, 
							  Adjacent *newConnection) {
	if(adjacent == NULL) return newConnection;
	else {
		adjacent->nextAdj = 
		addNewAdjacent(adjacent->nextAdj,newConnection);
		return adjacent;
	} 
}

Vertex **initAllVertices(Vertex **verts) {
	INTEGER i=0;
	for(i=0; i<V; i++) {
		verts[i]->d = INF;
		verts[i]->p = UNDEFINED;
		verts[i]->inSet = EMPTY;
	}
	return verts;
}





