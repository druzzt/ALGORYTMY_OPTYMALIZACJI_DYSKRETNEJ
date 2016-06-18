#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "constants2.h"
#include "heap.h"
#include <limits.h>


#define NUM_TEST_INSERTS 1000000
#define NUM_TOTAL_OPS 100000000

int *bucketRange(int Cost){
    int maxRange=1;
    while(Cost!=0) {Cost=Cost>>1; maxRange++;}
    maxRange++;
    int *r = malloc(maxRange*sizeof(int));
    int j;
    for(j=0;j<maxRange; j++) r[j+1]=1<<j;
        r[0]=UNDEFINED;
        r[maxRange-1]=INF;

    for(j=0;j<maxRange;j++){
        printf("%d,",r[j]);
    }

    
    return r;
}



int main() {

   
    int *range=bucketRange(INF);
    printf("\n");
    
    // Clean up.
    free(sorted);
    freeHeap(heapPtr);
    return 0;
}






/*
     // Set up heap and random number generator.
    srand(time(0));
    Heap *heapPtr;
    heapPtr = initHeap();

    // Insert a bunch of random items.
    INTEGER i;
    for (i=0; i<NUM_TEST_INSERTS; i++) {
        INTEGER x = 32768*rand()+rand();
        INTEGER outcome = insert(heapPtr, x);
         // this seg faults... wtf?
        if (!outcome) break;
    }
    insert(heapPtr, 1);
    printf("Worked inserting.");
    // Pull them out in sorted order.
    INTEGER* sorted = (INTEGER*)malloc(sizeof(INTEGER)*heapPtr->size);
    for (i=0; heapPtr->size>0; i++)
        sorted[i] = removeMin(heapPtr);

    // Check if it's really sorted.
    INTEGER isSorted = 1;
    for (i=0; i<NUM_TEST_INSERTS-1; i++)
        if (sorted[i] > sorted[i+1])
            isSorted = 0;
    if (isSorted) printf("Array is sorted!\n");


*/
/*** New Main #2: Tested with n = 10,000,000 and it didn't crash. Expected max heap size ~ 3,333,333.

int main() {

    // Set up heap and random number generator.
    srand(time(0));
    Heap *heapPtr;
    heapPtr = initHeap();

    // Do both inserts and deletes.
    int i;
    for (i=0; i<NUM_TOTAL_OPS; i++) {

        // So we can do some of both.
        int choice = rand()%3;

        // On average, we have more inserts.
        if (choice < 2) {
            int item = 32768*rand()+rand();
            int outcome = insert(heapPtr, item);
            if (!outcome) break;
            if (PRINT_DEBUG) printf("Just inserted %d\n", item);
        }

        // Process a remove.
        else {
            int item = removeMin(heapPtr);
            if (PRINT_DEBUG) {
                if (item > -1)
                    printf("Just removed the minimum %d.\n", item);
                else
                    printf("Sorry there was nothing to remove.\n");
            }
        }
    }

    // Clean up.
    freeHeap(heapPtr);
    return 0;
}
***/

/*** Old Main
int main() {

    int i;
    int vals[10];
    Heap *h;
    h = initHeap();

    // Test out individual inserts.
    insert(h, 7);
    insert(h, 3);
    insert(h, 5);
    insert(h, 12);
    insert(h, 2);
    insert(h, 8);
    insert(h, 4);
    insert(h, 9);
    insert(h, 1);
    printHeap(h);

    for (i=0; i<9; i++) {
        printf("Delete %d\n",removeMin(h));
        printHeap(h);
    }
    freeHeap(h);

    // Test out array initialization.
    vals[0] = 12, vals[1] = 3, vals[2] = 18, vals[3] = 14, vals[4] = 5;
    vals[5] = 9, vals[6] = 1, vals[7] = 7; vals[8] = 2, vals[9] = 13;

    sort(vals, 10);

    for (i=0; i<10; i++)
        printf("%d ", vals[i]);
    printf("\n");

    return 0;
}
***/
