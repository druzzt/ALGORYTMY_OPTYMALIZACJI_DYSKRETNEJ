#include "header.h"

// alg -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res
// alg -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res


void reset_queue (struct QueueNode* queue) 
{
    queue[0].node_no = 0;
    queue[0].next = &queue[1];
    queue[nodes_count-1].node_no = nodes_count-1;
    queue[nodes_count-1].prev = &queue[nodes_count-2];

    for (int i = 1; i < nodes_count-1; i++) {
        queue[i].node_no = i;
        queue[i].next = &queue[i+1];
        queue[i].prev = &queue[i-1];
    }
}

void remove_from_bucket(struct QueueNode** b, struct QueueNode* n, int bucket_no)
{
    if (bucket_no == -1)
        return;

    // printf("rm %d %d\n", n->node_no, bucket_no);

    if (*b == n)
        *b = n->next;

    if (n->next != NULL)
        n->next->prev = n->prev;

    if (n->prev != NULL)
        n->prev->next = n->next;
}

void add_to_bucket(struct QueueNode** b, struct QueueNode* n, int bucket_no)
{
    //printf("[addBel:%d],",bucket_no);
    n->bucket_no = bucket_no;
    n->next = *b;
    if (n->next)
        n->next->prev = n;
    n->prev = NULL;
    *b = n;
}
void test_algorithm(int (*algorithm)(int, int))
{
    clock_t startClock = clock();
    for(int i = 0; i < sources_count; ++i)
    {
        int outlet = (outlets)? outlets[i] : -1;
        //printf("%d %d\n",sources[i],outlets[i]);
        int cost = algorithm(sources[i], outlet);
        
        //printf("%4d [DONE]\n", i+1);

        if (sp_mode == P2P) {
            fprintf(output, "d %d %d %d\n", sources[i]+1, outlet+1, cost);
        }
    }
    clock_t endClock = clock();
    float time = (float)(endClock - startClock) / CLOCKS_PER_SEC;
    time = time / sources_count;
    time = time / 60.0;
    fprintf(output, "t %f\n", time);
}

void parse_args (int argc, char* argv[])
{
    if (argc != 7) {
        printf ("Usage: \n");
        printf ("\t%s -d <data> -ss <input> -oss <output>\n", argv[0]);
        printf ("\t%s -d <data> -p2p <input> -op2p <output>\n", argv[0]);
        exit(1);
    }

    for (int i = 1; i < argc; i += 2) {
        char* opt = argv[i];
        char* val = argv[i+1];

        if (strcmp ("-d", opt) == 0) {
            data = fopen(val, "r");
            data_path = val;
        } else if (strcmp("-ss", opt) == 0) {
            sp_mode = SS;
            input = fopen(val, "r");
            input_path = val;
        } else if (strcmp("-oss", opt) == 0) {
            output = fopen(val, "w+");
        } else if (strcmp("-p2p", opt) == 0) {
            sp_mode = P2P;
            input = fopen(val, "r");
            input_path = val;
        } else if (strcmp("-op2p", opt) == 0) {
            output = fopen(val, "w+");
        } else {
            printf ("Invalid argument %s\n", opt);
            exit(1);
        }
    }
}



void read_data ()
{
    int status;
    char* line = NULL;
    size_t length;

    int i;

    while ((status = getline (&line, &length, data)) != -1) {
        if (line[0] == 'a') {
            int from, to, cost;

            sscanf (&line[1], "%d %d %d", &from, &to, &cost);
            
            nodes[i].next = graph[from-1];
            graph[from-1] = &nodes[i];
            nodes[i].node_no = to-1;
            nodes[i].cost = cost;
            //printf("%d %d \n",nodes[i].node_no, nodes[i].cost);
            i += 1;

            if (cost > cost_max)
                cost_max = cost;
            if (cost < cost_min)
                cost_min = cost;
        } else if (line[0] == 'p') {
            char buff[8];

            sscanf (&line[1], "%s %d %d", buff, &nodes_count, &edges_count);

            i = 0;
            graph = calloc(nodes_count, sizeof(struct GraphNode*));
            nodes = calloc(edges_count, sizeof(struct GraphNode));


        }
    }
    free(line);
}


void read_input ()
{
    int status;
    char* line = NULL;
    size_t length;

    int i;

    while ((status = getline (&line, &length, input)) != -1) {
        if (line[0] == 's') {
            int source;
            sscanf (&line[1], "%d", &source);

            sources[i] = source-1;
            i += 1;
        } else if (line[0] == 'q') {
            int from, to;
            sscanf (&line[1], "%d %d", &from, &to);

            sources[i] = from-1;
            outlets[i] = to-1;
            i += 1;
        } else if (line[0] == 'p') {
            char b1[8], b2[8], b3[8];
            sscanf (&line[1], "%s %s %s %d", b1, b2, b3, &sources_count);

            i = 0;
            sources = calloc(sources_count, sizeof(int));
            if (strcmp(b3, "p2p") == 0) {
                outlets = calloc(sources_count, sizeof(int));
            }
        }
    }
    free(line);
}

void write_output ()
{
    char* mode = (sp_mode == SS)? "ss" : "p2p";

    fprintf(output, "p res sp %s %s\n", mode, algorithm_name);
    fprintf(output, "f %s %s\n", data_path, input_path);
    fprintf(output, "g %d %d %d %d\n", nodes_count, edges_count, cost_min, cost_max);      
}

void prepare_tests(int argc, char* argv[])
{
    parse_args(argc, argv);
    read_data ();
    read_input ();
    write_output ();
}

void release_resources ()
{
    fclose (data);
    fclose (input);
    fclose (output);

    free(nodes);
    free(graph);
    
    free(sources);
    free(outlets);
}