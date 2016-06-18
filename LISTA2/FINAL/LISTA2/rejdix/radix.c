#include "header.h"


int main(int argc, char* argv[])
{
    // Reading testcases
    prepare_tests(argc, argv);

    test_algorithm(radix);
    
    // Cleaning
    release_resources();

    return 0;
}

int radix(int begin_node, int end_node)
{
    printf("S:%d \tT: %d\n",begin_node,end_node);
    /* ----------- Initialization ----------- */
    struct QueueNode** b = calloc(32, sizeof(struct QueueNode*));
    struct QueueNode* q = calloc(nodes_count, sizeof(struct QueueNode));
    
    int* d = calloc(nodes_count, sizeof(int));
    int* p = calloc(nodes_count, sizeof(int));
    for (int i = 0; i < nodes_count; i++) {
        q[i].node_no = i;
        q[i].bucket_no = -1;
        d[i] = INT_MAX;
        p[i] = -1;
        printf("%d %d %d %d\n",q[i].node_no,q[i].bucket_no, d[i], p[i]);
    }
    
    int ranges[33];
    ranges[0] = 0;
    for (int i = 0; i < 31; i++) {
        ranges[i+1] = 1 << i;
        printf("%d %d %d %d\n",i,ranges[i+1],ranges[i],1<<i);
    }
    ranges[32] = INT_MAX;

    
    /* ---------- Searching for SP ---------- */
    add_to_bucket(&b[0], &q[begin_node], 0);
    printf("\t%d %d %d\n",b[0],q[begin_node],0);
    d[begin_node] = 0;
    int i = 0;
    int k;
    //for(k=0;k<=nodes_count;k++) printf("|%d=%d, %d;",k,d[k],p[k]);
    for (int labeled = 0; labeled < nodes_count; labeled++) {

        /* ------------ Node Selection ------------ */
       // printf("{labeled:%d; 1i:%d,",labeled,i);
        //for(k=0;k<32&&b[k]==NULL;k++) printf("\t%d %d,\n",k,b[k]);
        for (; i < 32 && b[i] == NULL; i++);
        if (i == 32)
            break;
        //printf("32; 2i:%d},",i);

        // Bucket redistribution
        if (! (i == 0 || ranges[i+1] - ranges[i] == 1 || b[i]->next == NULL)) {
            // Find minimal node from bucket
            int no = b[i]->node_no;
            int min = d[no];
            for (struct QueueNode* p = b[i]->next; p; p=p->next) {
                if (d[p->node_no] < min) {
                    no = p->node_no;
                    min = d[no];
                }
            }

            // Relabel ranges
            ranges[0] = min;
            for (int j = 0; j < i; j++) {
                ranges[j+1] = ranges[0] + (1 << j);
            }
            ranges[i] = INT_MAX;

            while (b[i] != NULL) {
                int n_no = b[i]->node_no;
                remove_from_bucket(&b[i], &q[n_no], i);

                int dest = i - 1;
                for(; dest >= 0 && d[n_no] < ranges[dest]; dest--);

                add_to_bucket(&b[dest], &q[n_no], dest);
            }

            // Minimum is now in first bucket
            i = 0;
        }

        struct QueueNode* minimal = b[i];
        int min_no = minimal->node_no;
        remove_from_bucket(&b[i], &q[min_no], i);

        /* -------- Neighbour Label Update -------- */
        for (struct GraphNode* n = graph[min_no]; n != NULL; n = n->next){
            int n_no = n->node_no;
            int cost = n->cost;
            int bucket_no = q[n_no].bucket_no;

            if (d[n_no] > d[min_no] + cost) {
                remove_from_bucket(&b[bucket_no], &q[n_no], bucket_no);

                d[n_no] = d[min_no] + cost;
                p[n_no] = min_no;

                int dest = (bucket_no == -1) ? 31 : bucket_no;
                for(; dest >= 0 && d[n_no] < ranges[dest]; dest--);

                add_to_bucket(&b[dest], &q[n_no], dest);
            }
        }

        if (min_no == end_node)
            break;
    }

     for (int i = 0; i < nodes_count; i++) {
         printf("%d %d %d\n", i, d[i], p[i]);
     }

    int total_cost = (end_node != -1)? d[end_node] : 0;

    /* -------------- Clean-up -------------- */
    
    free(b);
    free(d);
    free(p);
    free(q);

    return total_cost;
}

