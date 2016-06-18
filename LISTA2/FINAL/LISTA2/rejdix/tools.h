#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
// Queue Node
struct QueueNode
{
    int node_no;
    int bucket_no;
    struct QueueNode* next;
    struct QueueNode* prev; 
};

int radix(int begin_node, int end_node);
void reset_queue(struct QueueNode* queue);
void remove_from_bucket(struct QueueNode** b, struct QueueNode* n, int bucket_no);
void add_to_bucket(struct QueueNode** b, struct QueueNode* n, int bucket);

// Main function to test algorithm
char* algorithm_name;
void test_algorithm(int (*foo)(int, int));

// I/O Files
char* data_path;
char* input_path;
char* output_path;
FILE* data;
FILE* input;
FILE* output;

void prepare_tests (int argc, char* argv[]);
void release_resources ();


// Graph Node
struct GraphNode {
    int node_no;
    int cost;
    struct GraphNode* next;
};

// Graph
struct GraphNode* nodes;
struct GraphNode** graph;
int nodes_count;
int edges_count;
int cost_min;
int cost_max;

// Shortest Path
enum SPMode {SS, P2P};
enum SPMode sp_mode;
int sources_count;
int* sources;
int* outlets;


// External
//extern int getline1(char **lineptr, size_t *n, FILE *stream);

#endif