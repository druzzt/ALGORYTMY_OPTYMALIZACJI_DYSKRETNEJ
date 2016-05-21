#include "structs.h"
#include <stdio.h>
#include "constants.h"
//#include "headers.h"



struct node *front ( struct list *list )
{
  return list->head.next;
}
 
struct node *back ( struct list *list )
{
  return list->tail.prev;
}
 
int push_front( struct list *list, void *new_item)
{
	if(list == NULL || new_item == NULL) return 0;
	if(list->size == 0){
		list->head.next = malloc(sizeof *list->head.next);
		if(list->head.next== NULL) return 0;
		list->head.next->object = new_item;
		list->head.next->prev = &list->head;
		list->head.next->next = &list->tail;
		list->tail.prev = NULL;
		list->tail.next = NULL;
		list->tail.prev = list->head.next;
	}
	else{
		struct node *new_node;
		new_node = malloc(sizeof *new_node);
		if(new_node == NULL) return 0;
		new_node->object = new_item;
		new_node->next = list->head.next;
		new_node->prev = &list->head;
		list->head.next->prev = new_node;
		list->head.next = new_node;
	}
	list->size++;
	return 1;
}

int push_back ( struct list *list, void *new_item )
{
  if ( list == NULL || new_item == NULL )
    return 0;
  if ( list->size == 0 ) {
    list->head.next = malloc( sizeof *list->head.next );
    if ( list->head.next == NULL ) return 0;
    list->head.next->object = new_item;
    list->head.next->prev = &list->head;
    list->head.next->next = &list->tail;
    list->head.prev = NULL;
    list->tail.next = NULL;
    list->tail.prev = list->head.next;
  }
  else {
    struct node *new_node;
    new_node = malloc( sizeof *new_node );
    if ( new_node == NULL ) return 0;
    new_node->object = new_item;
    new_node->prev = list->tail.prev;
    new_node->next = &list->tail;
    list->tail.prev->next = new_node;
    list->tail.prev = new_node;
  }
  list->size++;
 
  return 1;
}


int insert_this ( struct list *list, struct node *it, void *new_item )
{
  struct node *new_node;
 
  if ( list == NULL || it == NULL )
    return 0;
  if ( list->size == 0 ) {
    if ( push_front ( list, new_item ) == 0 )
      return 0;
  	//if ( push_back ( list, new_item ) == 0 )
  		//return 0;
  }
  else {
    new_node = malloc( sizeof *new_node );
    if ( new_node == NULL )
      return 0;
    new_node->object = new_item;
    new_node->next = it;
    new_node->prev = it->prev;
    it->prev->next = new_node;
    it->next->prev = new_node;
  }
  list->size++;
 
  return 1;
}


int erase_item ( struct list *list, void *old_item
                ,int (*compare) ( const void *a, const void *b )
                ,void (*release) ( struct node * ) )
{
  struct node *walk;
 
  if ( list == NULL || old_item == NULL || list->size == 0 )
    return 0;
  for ( walk = list->head.next; walk != &list->tail; walk = walk->next) {
    if ( (*compare) ( walk->object, old_item ) == 0 ) {
      walk->next->prev = walk->prev;
      walk->prev->next = walk->next;
      (*release) ( walk );
      list->size--;
      return 1;
    }
  }
 
  return 0;
}

int erase_this ( struct list *list, struct node *it
                ,void (*release) ( struct node * ) )
{
  if ( it == NULL || list->size == 0 )
    return 0;
  it->next->prev = it->prev;
  it->prev->next = it->next;
  (*release) ( it );
  list->size--;
 
  return 1;
}


int traverse ( struct list *list, void (*action) ( struct node * ) )
{
  struct node *save;
  struct node *walk;
 
  if ( list == NULL )
    return 0;
  for ( walk = list->head.next; walk != &list->tail; walk = save ) {
    save = walk->next;
    (*action) ( walk );
  }
 
  return 1;
}



int rtraverse ( struct list *list, void (*action) ( struct node * ) )
{
  struct node *save;
  struct node *walk;
 
  if ( list == NULL )
    return 0;
  for ( walk = list->tail.prev; walk != &list->head; walk = save ) {
    save = walk->prev;
    (*action) ( walk );
  }
 
  return 1;
}





 

 
struct integer *make_integer ( int init )
{
  struct integer *rv;
 
  rv = malloc ( sizeof *rv );
  if ( rv == NULL )
    return NULL;
  rv->i = init;
 
  return rv;
}
 
void print_integer ( struct node *x )
{
  printf ( "%llu ", ( (struct integer *)x->object )->i );
}
 
void free_integer ( struct node *x )
{
  free ( x->object );
  free ( x );
}
 
int compare ( const void *a, const void *b )
{
  return ( (const struct integer *)a )->i - ( (const struct integer *)b )->i;
}






/* TESTING FRAMEWORK */
/*
#ifndef TESTING

int main()
{
  struct integer kill;
  struct list    ilist = {0};
  int            i;

  for ( i = 0; i < 4; i++ ) push_back ( &ilist, make_integer ( i ) );
  for ( i = 0; i < 4; i++ ) push_front ( &ilist, make_integer ( i ) );
  traverse ( &ilist, print_integer );
  kill.i = 1;
  printf ( "\n%llu\t%d\n\n",kill.i, erase_item ( &ilist, &kill, compare, free_integer ) );
  traverse ( &ilist, print_integer );
  kill.i = 2;
  printf ( "\n%llu\t%d\n\n",kill.i, erase_item ( &ilist, &kill, compare, free_integer ) );
  traverse ( &ilist, print_integer );
  kill.i = 3;
  printf ( "\n%llu\t%d\n\n",kill.i, erase_item ( &ilist, &kill, compare, free_integer ) );
  traverse ( &ilist, print_integer );
  kill.i = 4;
  printf ( "\n%llu\t%d\n\n",kill.i, erase_item ( &ilist, &kill, compare, free_integer ) );
  traverse ( &ilist, print_integer );
  printf ( "\n%llu\t%d\n\n",kill.i, erase_this ( &ilist, front ( &ilist )->next, free_integer ) );
  traverse ( &ilist, print_integer );
  printf ( "\n%llu\t%d\n\n",kill.i, erase_this ( &ilist, back ( &ilist )->prev, free_integer ) );
  traverse ( &ilist, print_integer );
  kill.i = 5;
  printf ( "\n%llu\t%d\n\n",kill.i, insert_this ( &ilist, front ( &ilist ), make_integer ( kill.i ) ) );
  traverse ( &ilist, print_integer );

  ///* // NIE DODAWAJ NA KONIEC LISTY tym sposobem
  kill.i = 6;
  printf("\nDodaj %d na koniec\n",kill.i);
  printf ( "\n%llu\t%d\n\n",kill.i, insert_this ( &ilist, back ( &ilist ), make_integer ( kill.i ) ) );
  traverse ( &ilist, print_integer );
  printf("\nDodano\n");
  // *//*

  kill.i = 7;
  printf ( "\n%llu\t%d\n\n",kill.i, insert_this ( &ilist, front ( &ilist ), make_integer ( kill.i ) ) );
  traverse ( &ilist, print_integer );
  traverse ( &ilist, free_integer );
 
  return 0;
}

#endif
// */












