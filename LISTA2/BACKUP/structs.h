#ifndef structs_h
#define structs_h

typedef struct element {
    char *name;
    struct element *prev; 
    struct element *next; 

} element;
#endif
