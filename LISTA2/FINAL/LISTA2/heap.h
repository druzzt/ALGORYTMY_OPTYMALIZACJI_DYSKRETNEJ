#define SIZE 100
// Used to create a heap.
Heap *initHeap();
Heap * initHeapfromArray(INTEGER* values, INTEGER length);
void heapify(Heap *h);

// Helper functions.
void percolateDown(Heap *h, INTEGER index);
void percolateUp(Heap *h, INTEGER index);
INTEGER insert(Heap *h, INTEGER value);

// Two key functions to implement priority queue.
INTEGER removeMin(Heap *h);
void prINTEGERHeap(Heap *h);

// More helper functions.
void swap(Heap *h, INTEGER index1, INTEGER index2);
INTEGER minimum(INTEGER a, INTEGER indexa, INTEGER b, INTEGER indexb);
void freeHeap(Heap *h);

// Runs a heap sort.
void sort(INTEGER values[], INTEGER length);



// Initialize an empty heap with a capacity of SIZE.
Heap* initHeap() {

    Heap* h;

    // Allocate space for the heap and set the size for an empty heap.
    h = (Heap*)(malloc(sizeof(Heap)));
    h->capacity = SIZE;
    h->heaparray = (INTEGER*)malloc((SIZE+1)*sizeof(INTEGER));
    h->size = 0;
    return h;
}

// Frees the struct pointed to by h.
void freeHeap(Heap *h) {
     free(h->heaparray);
     free(h);
}

// Initializes the heap using the first length number of items in the array
// values.
Heap * initHeapfromArray(INTEGER* values, INTEGER length) {

    INTEGER i;
    Heap* h;

    h = (Heap*)(malloc(sizeof(Heap)));
    // We allocate one extra slot, since slot 0 stays unused.
    h->heaparray = (INTEGER*)malloc(sizeof(INTEGER)*(length+1));

    // Just copy the values INTEGERo our array.
    for (i=1; i<=length; i++)
        h->heaparray[i] = values[i-1];

    // This is the number of values we copied.
    h->size = length;

    // This takes our random values and rearranges them into a heap.
    heapify(h);
    return h;
}

// h points to a heap structure that has values inside of it, but isn't yet
// organized into a heap and does exactly that.
void heapify(Heap *h) {

    INTEGER i;

    // We form a heap by just running percolateDown on the first half of the
    // elements, in reverse order.
    for (i=h->size/2; i>0; i--)
        percolateDown(h, i);

}

// Runs percolate down on the heap pointed to by h on the node stored in index.
void percolateDown(Heap *h, INTEGER index) {

    INTEGER min;

    // Only try to percolate down internal nodes.
    if ((2*index+1) <= h->size) {

        // Find the minimum value of the two children of this node.
        min = minimum(h->heaparray[2*index], 2*index, h->heaparray[2*index+1], 2*index+1);

      // If this value is less than the current value, then we need to move
      // our current value down the heap.
        if (h->heaparray[index] > h->heaparray[min]) {
            swap(h, index, min);

            // This part is recursive and allows us to continue percolating
            // down the element in question.
            percolateDown(h, min);
        }
    }

    // Case where our current element has exactly one child, a left child.
    else if (h->size == 2*index) {

        // Here we only compare the current item to its only child.
        // Clearly, no recursive call is needed since the child of this node
        // is a leaf.
        if (h->heaparray[index] > h->heaparray[2*index])
            swap(h, index, 2*index);
    }
}

// Runs percolate up on the heap pointed to by h on the node stored in index.
void percolateUp(Heap *h, INTEGER index) {

    // Can only percolate up if the node isn't the root.
    if (index > 1) {

        // See if our current node is smaller in value than its parent.
        if (h->heaparray[index/2] > h->heaparray[index]) {

            // Move our node up one level.
            swap(h, index, index/2);

            // See if it needs to be done again.
            percolateUp(h, index/2);
        }
    }
}

// Inserts value into the heap pointed to by h. Returns 1 if the insert was
// successful, 0 otherwise.
INTEGER insert(Heap *h, INTEGER value) {

    INTEGER* temp;
    INTEGER* throwaway;
    INTEGER i;

    // Our array is full, we need to allocate some new space!
    if (h->size == h->capacity) {

        // Allocate new space for an array.
        h->heaparray = (INTEGER*)realloc(h->heaparray, sizeof(INTEGER)*(2*h->capacity+1));

        // Realloc failed so we quit.
        if (h->heaparray == NULL) return 0;

        // Double the capacity.
        h->capacity *= 2;
    }

    // Adjust all the necessary components of h, and then move the inserted
    // item INTEGERo its appropriate location.
    h->size++;
    h->heaparray[h->size] = value;
    percolateUp(h, h->size);
    if(0) return 0;
    else return 1;
}

INTEGER removeMin(Heap *h) {

    INTEGER retval;

    // We can only remove an element, if one exists in the heap!
    if (h->size > 0) {

        // This is where the minimum is stored.
        retval = h->heaparray[1];

        // Copy the last value into this top slot.
        h->heaparray[1] = h->heaparray[h->size];

        // Our heap will have one fewer items.
        h->size--;

        // Need to let this value move down to its rightful spot in the heap.
        percolateDown(h, 1);

        // Now we can return our value.
        return retval;
    }

    // No value to return, indicate failure with a -1.
    else
        return -1;
}

// For debugging purposes, lets us see what's in the heap.
void printHeap(Heap *h) {
    INTEGER i;

    for (i=1; i<=h->size; i++)
        printf(" "I_FORMAT"", h->heaparray[i]);
    printf("\n");
}

// Swaps the values stored in the heap pointed to by h in index1 and index2.
void swap(Heap *h, INTEGER index1, INTEGER index2) {
    INTEGER temp = h->heaparray[index1];
    h->heaparray[index1] = h->heaparray[index2];
    h->heaparray[index2] = temp;
}

// Returns indexa if a < b, and returns indexb otherwise.
INTEGER minimum(INTEGER a, INTEGER indexa, INTEGER b, INTEGER indexb) {

    // Return the value associated with a.
    if (a < b)
        return indexa;

    // Return the value associated with b.
    else
        return indexb;
}

// Runs a heap sort by creating a heap out of the values in the array, and then
// extracting those values one-by-one from the heap back into the array in the
// proper order.
void sort(INTEGER values[], INTEGER length) {

     Heap *h;
     INTEGER i;

     // Create a heap from the array of values.
     h =  initHeapfromArray(values, length);
     length = h->size;

     // Remove these values from the heap one by one and store them back in the
     // original array.
     for (i=0; i<length; i++) {
         values[i] = removeMin(h);
     }
}