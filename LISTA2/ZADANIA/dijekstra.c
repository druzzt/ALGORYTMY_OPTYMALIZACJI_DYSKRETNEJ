#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>

int qVerts = 0, qArcs = 0, qSources = 0, qPairs = 0, maxCost = 0;
typedef struct Vert Vert;
typedef struct Connections Connections;
typedef struct List List;

enum inSet { NO, Q, S };

struct Vert {
	int id;
	int d;
	int p;
	enum inSet inSet;
	Connections *connection;
};

struct Connections {
	int parentId;
	int cost;
	Vert *vert;
	Connections *nextConnection;
};

struct List {
	int minCost;
	Vert *vert;
	List *left;
	List *right;
};

List *newQueueElement(int minCost, Vert *vert, List *left, List *right) {
	List* queue = (List*) malloc(sizeof(List));

	vert->inSet = Q;

	queue->minCost = minCost;
	queue->vert = vert;
	queue->left = left;
	queue->right = right;
	return queue;
}

List *removeFromQueue(List *queue, Vert *vert) {
	int minCost = vert->d;
	if(queue==NULL) return NULL;
	else {
		if(queue->minCost < minCost) {
			queue->right = removeFromQueue(queue->right, vert);
		}
		else {
			if(queue->vert->id != vert->id) queue->right = removeFromQueue(queue->right, vert);
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

List *addToQueue(List *queue, int minCost, Vert *vert) {
	List *currentPosition = queue;	
	if(vert->inSet != S) {
		// []
		if(queue == NULL) queue = newQueueElement(minCost, vert, NULL, NULL);
		else {
			// () -> A
			if(currentPosition->minCost >= minCost) {
				List *newElement = newQueueElement(minCost, vert, NULL, currentPosition);
				currentPosition->left = newElement;
				queue = newElement;	
			}
			else {
				while(currentPosition->right != NULL && currentPosition->minCost < minCost) {
					currentPosition = currentPosition->right;
				}
				// A -> ()
				if(currentPosition->minCost < minCost) {
					List *newElement = newQueueElement(minCost, vert, currentPosition, NULL);
					currentPosition->right = newElement;
				}
				// A -> () -> B 
				else {
					List *newElement = newQueueElement(minCost, vert, currentPosition->left, currentPosition);	
					currentPosition->left->right = newElement;
					currentPosition->left = newElement;
				}
			}
		}
	}
	return queue;
}

Vert *getMinimumElement(List *queue) {
	if(queue == NULL) return NULL;
	else {
		Vert* vert = queue->vert;
		return vert;
	}
}

Vert* initVert(int id)
{
	Vert* vert = (Vert*) malloc(sizeof(Vert));
	vert->id = id+1;
	vert->d = INT_MAX;
	vert->p = -1;
	vert->connection = NULL;
	return vert;
}


Connections *initConnection(int parentId, int cost, Vert *vert) {
	Connections* connection = (Connections*) malloc(sizeof(Connections));
	connection->parentId = parentId;
	connection->cost = cost;
	connection->vert = vert;
	connection->nextConnection = NULL;
	return connection;
}

Connections *addNewConnection(Connections *connections, Connections *newConnection) {
	if(connections == NULL) return newConnection;
	else {
		connections->nextConnection = addNewConnection(connections->nextConnection, newConnection);
		return connections;
	} 
}

Vert **clearVerts(Vert **verts) {
	int i=0;
	for(i=0; i<qVerts; i++) {
		verts[i]->d = INT_MAX;
		verts[i]->p = -1;
		verts[i]->inSet = NO;
	}
	return verts;
}


Vert **dijekstra(Vert **verts, int s) {
	List *queue = NULL;
	verts[s-1]->d = 0;
	queue = addToQueue(queue, verts[s-1]->d, verts[s-1]);
	while(queue != NULL) {
		Vert *minCostVert = getMinimumElement(queue);
		queue = removeFromQueue(queue, minCostVert);
		minCostVert->inSet = S;
		Connections *connection = minCostVert->connection;
		while(connection != NULL) {
			Vert *vert = connection->vert;
			if(vert->inSet != S) {
				if(vert->d > minCostVert->d + connection->cost) {
					if(vert->inSet == Q) queue = removeFromQueue(queue, vert);
					vert->d = minCostVert->d + connection->cost;
					vert->p = minCostVert->id;
					queue = addToQueue(queue, vert->d, vert);
					vert->inSet = Q;
				}
			}
			connection = connection->nextConnection;
		}
	}
	return verts;
}

Vert **dijekstraP2P(Vert **verts, int s, int t) {
	List *queue = NULL;
	verts[s-1]->d = 0;
	queue = addToQueue(queue, verts[s-1]->d, verts[s-1]);
	while(queue != NULL) {
		Vert *minCostVert = getMinimumElement(queue);
		queue = removeFromQueue(queue, minCostVert);
		if(minCostVert->id == t) return verts;
		minCostVert->inSet = S;
		Connections *connection = minCostVert->connection;
		while(connection != NULL) {
			Vert *vert = connection->vert;
			if(vert->inSet != S) {
				if(vert->d > minCostVert->d + connection->cost) {
					if(vert->inSet == Q) queue = removeFromQueue(queue, vert);
					vert->d = minCostVert->d + connection->cost;
					vert->p = minCostVert->id;
					queue = addToQueue(queue, vert->d, vert);
					vert->inSet = Q;
				}
			}
			connection = connection->nextConnection;
		}
	}
	return verts;
}

Vert **readData(char *dataFile) {
	int **graph, i = 0;
	Vert **verts;
	FILE *file;
	char lineType, buffer[128];
   	if ((file=fopen(dataFile, "r"))==NULL) {
     		printf ("Nie można otworzyć pliku z danymi!\n");
     		exit(1);
     	}
	i = 0;
   	while (fscanf(file, "%c", &lineType) != EOF)
	{
		if(lineType == 'c') fgets(buffer, sizeof(buffer), file);
		else if(lineType == 'p') {
			fscanf(file, " sp %d %d", &qVerts, &qArcs);
			graph = (int**)malloc(qArcs+3*sizeof(int));
			verts = (Vert**)malloc(qVerts*sizeof(Vert));
			int j;
			for(j = 0; j<qVerts; j++) verts[j] = initVert(j);
		}
		else if(lineType == 'a') {
			int a, b, cost;
			fscanf(file, " %d %d %d", &a, &b, &cost);
			Connections *newConnection = initConnection(a, cost, verts[b-1]);
			if(cost > maxCost) maxCost = cost;
			verts[a-1]->connection = addNewConnection(verts[a-1]->connection, newConnection);
		}		
		else if(lineType != ' ' && lineType != '\t' && lineType != '\n') {
			printf("Błędny plik z danymi!\n");
		}
	}
   	fclose (file);
	return verts;
}

int **readPairs(char *dataFile) {
	int **pairs, i = 0;
	FILE *file;
	char lineType, buffer[128];
   	if ((file=fopen(dataFile, "r"))==NULL) {
     		printf ("Nie można otworzyć pliku z danymi!\n");
     		exit(1);
     	}
	i = 0;
   	while (fscanf(file, "%c", &lineType) != EOF)
	{
		if(lineType == 'c') fgets(buffer, sizeof(buffer), file);
		else if(lineType == 'p') {
			fscanf(file, " aux sp p2p %d", &qPairs);
			pairs = (int**)malloc(qPairs*2*sizeof(int));
		}
		else if(lineType == 'q') {
			pairs[i] = (int*)malloc(2*sizeof(int));
			fscanf(file, " %d %d", &pairs[i][0], &pairs[i][1]);
			i++;
		}		
		else if(lineType != ' ' && lineType != '\t' && lineType != '\n') {
			printf("Błędny plik z parami!\n");
		}
	}
   	fclose (file);
	return pairs;
}

int *readSources(char *dataFile) {
	int *sources, i = 0;
	FILE *file;
	char lineType, buffer[128];
   	if ((file=fopen(dataFile, "r"))==NULL) {
     		printf ("Nie można otworzyć pliku z danymi!\n");
     		exit(1);
     	}
	i = 0;
   	while (fscanf(file, "%c", &lineType) != EOF)
	{
		if(lineType == 'c') fgets(buffer, sizeof(buffer), file);
		else if(lineType == 'p') {
			fscanf(file, " aux sp ss %d", &qSources);
			sources = (int*)malloc(qSources*sizeof(int));
		}
		else if(lineType == 's') {
			fscanf(file, " %d", &sources[i]);
			i++;
		}
		else if(lineType != ' ' && lineType != '\t' && lineType != '\n') {
			printf("Błędny plik ze źródłami!\n");
		}
	}
   	fclose (file);
	return sources;
}


int main(int argc, char *argv[])
{

	int isP2PMethod = 0;
	int i = 0;
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
				printf("Wprowadzone parametry są błędne: %s!\n", argv[i]);
				return 0;
			}
		}
		Vert **verts = readData(dataFile);
		for(i=0; i<qVerts; i++) {
			Connections *conn;
			conn = verts[i]->connection;
			while (conn != NULL) {
				conn = conn->nextConnection;
			}
		}
		if(isP2PMethod) {
			int **pairs = readPairs(sourcesFile);

			FILE *file;
		   	if ((file=fopen(resultsFile, "w"))==NULL) {
		     		printf ("Nie można utworzyć pliku wynikowego!\n");
		     		exit(1);
		     	}
			
			fprintf(file, "f %s %s\n", dataFile, sourcesFile);
			fprintf(file, "g %d %d %d %d\n", qVerts, qArcs, 0, maxCost);

			for(i = 0; i < qPairs; i++) {
				verts = dijekstraP2P(verts, pairs[i][0], pairs[i][1]);
				fprintf(file, "d %d %d %d\n", pairs[i][0], pairs[i][1], verts[pairs[i][1]-1]->d);
				verts = clearVerts(verts);
			}
			fclose (file);
		}
		else {
			int *sources = readSources(sourcesFile);
			double avgTime;

			FILE *file;
		   	if ((file=fopen(resultsFile, "w"))==NULL) {
		     		printf ("Nie można utworzyć pliku wynikowego!\n");
		     		exit(1);
		     	}
			fprintf(file, "p res sp ss dikstry\n");
			fprintf(file, "f %s %s\n", dataFile, sourcesFile);
			fprintf(file, "g %d %d %d %d\n", qVerts, qArcs, 0, maxCost);
			struct timeval stop, start;
			gettimeofday(&start, NULL);
			for(i = 0; i < qSources; i++) {
				verts = dijekstra(verts, sources[i]);
				verts = clearVerts(verts);
			}
			gettimeofday(&stop, NULL);
			double secs = (double)(stop.tv_usec - start.tv_usec) / 1000 + (double)(stop.tv_sec - start.tv_sec) * 1000;
			fprintf(file, "t %lf", secs / (double)qSources);
			fclose (file);
		}
	}
	else {
		printf("Błędna ilość parametrów!\n");
		return 0;
	}
	return 0;
}
