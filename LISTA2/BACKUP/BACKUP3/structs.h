#ifndef STRUCTS_H
#define STRUCTS_H
#define FRONT(X) (return X->head.next)
#define BACK(X) (return X->head.prev)
#define SPACE(X) (malloc(X))
#include "constants.h"
#include <stddef.h>

struct node {
  void        *object;
  struct node *prev;
  struct node *next;
};
struct list {
  struct node head;
  struct node tail;
  size_t      size;
};
struct integer {
  INTEGER i;
};
struct node *front ( struct list *list );
struct node *back ( struct list *list );
int push_front( struct list *list, void *new_item);
int push_back ( struct list *list, void *new_item );
int insert_this ( struct list *list, struct node *it, void *new_item );
int erase_item ( struct list *list, void *old_item
                ,int (*compare) ( const void *a, const void *b )
                ,void (*release) ( struct node * ) );

int erase_this ( struct list *list, struct node *it
                ,void (*release) ( struct node * ) );
int traverse ( struct list *list, void (*action) ( struct node * ) );
int rtraverse ( struct list *list, void (*action) ( struct node * ) );
struct integer *make_integer ( int init );
void print_integer ( struct node *x );
void free_integer ( struct node *x );
int compare ( const void *a, const void *b );

#endif