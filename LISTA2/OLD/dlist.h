#include <assert.h>
#define LDECLTYPE(x) char*
/*#define _SV(elt,list) _tmp = (char*)(list); {char **_alias = (char**)&(list); *_alias = (elt); }
#define _NEXT(elt,list,next) ((char*)((list)->next))
#define _NEXTASGN(elt,list,to,next) { char **_alias = (char**)&((list)->next); *_alias=(char*)(to); }
//*/
/* #define _PREV(elt,list,prev) ((char*)((list)->prev)) */
/*
#define _PREVASGN(elt,list,to,prev) { char **_alias = (char**)&((list)->prev); *_alias=(char*)(to); }
#define _RS(list) { char **_alias = (char**)&(list); *_alias=_tmp; }
#define _CASTASGN(a,b) { char **_alias = (char**)&(a); *_alias=(char*)(b); }
*/
#define _SV(elt,list)
#define _NEXT(elt,list,next) ((elt)->next)
#define _NEXTASGN(elt,list,to,next) ((elt)->next)=(to)
/* #define _PREV(elt,list,prev) ((elt)->prev) */
#define _PREVASGN(elt,list,to,prev) ((elt)->prev)=(to)
#define _RS(list)
#define _CASTASGN(a,b) (a)=(b)


#define PUSH_FRONT2(head,add,prev,next)                                                        \
do {                                                                                           \
 (add)->next = head;                                                                           \
 if (head) {                                                                                   \
   (add)->prev = (head)->prev;                                                                 \
   (head)->prev = (add);                                                                       \
 } else {                                                                                      \
   (add)->prev = (add);                                                                        \
 }                                                                                             \
 (head) = (add);                                                                               \
} while (0)
#define PUSH_FRONT(head,add)                                                                   \
    PUSH_FRONT2(head,add,prev,next)

#define PUSH_BACK(head,add)                                                                    \
    PUSH_BACK2(head,add,prev,next)

#define PUSH_BACK2(head,add,prev,next)                                                         \
do {                                                                                           \
  if (head) {                                                                                  \
      (add)->prev = (head)->prev;                                                              \
      (head)->prev->next = (add);                                                              \
      (head)->prev = (add);                                                                    \
      (add)->next = NULL;                                                                      \
  } else {                                                                                     \
      (head)=(add);                                                                            \
      (head)->prev = (head);                                                                   \
      (head)->next = NULL;                                                                     \
  }                                                                                            \
} while (0)

#define MERGE(head1,head2)                                                                     \
    MERGE2(head1,head2,prev,next)

#define MERGE2(head1,head2,prev,next)                                                          \
do {                                                                                           \
  LDECLTYPE(head1) _tmp;                                                                       \
  if (head2) {                                                                                 \
    if (head1) {                                                                               \
        _tmp = (head2)->prev;                                                                  \
        (head2)->prev = (head1)->prev;                                                         \
        (head1)->prev->next = (head2);                                                         \
        (head1)->prev = _tmp;                                                                  \
    } else {                                                                                   \
        (head1)=(head2);                                                                       \
    }                                                                                          \
  }                                                                                            \
} while (0)

#define REMOVE(head,del)                                                                       \
    REMOVE2(head,del,prev,next)

#define REMOVE2(head,del,prev,next)                                                            \
do {                                                                                           \
  assert((del)->prev != NULL);                                                                 \
  if ((del)->prev == (del)) {                                                                  \
      (head)=NULL;                                                                             \
  } else if ((del)==(head)) {                                                                  \
      (del)->next->prev = (del)->prev;                                                         \
      (head) = (del)->next;                                                                    \
  } else {                                                                                     \
      (del)->prev->next = (del)->next;                                                         \
      if ((del)->next) {                                                                       \
          (del)->next->prev = (del)->prev;                                                     \
      } else {                                                                                 \
          (head)->prev = (del)->prev;                                                          \
      }                                                                                        \
  }                                                                                            \
} while (0)

#define COUNT(head,el,counter)                                                                 \
    COUNT2(head,el,counter,next)                                                               \

#define COUNT2(head,el,counter,next)                                                           \
{                                                                                              \
    counter = 0;                                                                               \
    FOREACH2(head,el,next){ ++counter; }                                                       \
}
#define Q_FOREACH(head, el)                                                          \
        for((el)=head; el->next ; el=(el)->next)

#define LL_FOREACH(head,el)                                                                    \
    LL_FOREACH2(head,el,next)

#define LL_FOREACH2(head,el,next)                                                              \
    for(el=head;el;el=(el)->next)

#define LL_FOREACH_SAFE(head,el,tmp)                                                           \
    LL_FOREACH_SAFE2(head,el,tmp,next)

#define LL_FOREACH_SAFE2(head,el,tmp,next)                                                     \
  for((el)=(head);(el) && (tmp = (el)->next, 1); (el) = tmp)
//
    #define FOREA(head,el, iterator)                                                           \
    FOREA2(head,el,next, iterator)

#define FOREA2(head,el,next, iterator)                                                         \
    for(el=head;el;el=(el)->next,iterator++)
//
#define FOREACH(head,el)                                                                       \
    FOREACH2(head,el,next)

#define FOREACH2(head,el,next)                                                                 \
    for(el=head;el;el=(el)->next)

/* this version is safe for deleting the elements during iteration */
#define FOREACH_SAFE(head,el,tmp)                                                              \
    FOREACH_SAFE2(head,el,tmp,next)

#define FOREACH_SAFE2(head,el,tmp,next)                                                        \
  for((el)=(head);(el) && (tmp = (el)->next, 1); (el) = tmp)
/*
#define SEARCH_SCALAR_PROT(head, out, out2, field, field1, field2, val, val2, val3, val4, val5, TYPE, X, Y, Z, action)        \
      do {                                                                                     \
        LL_FOREACH2(head,out,next){                                                            \
          if((out)->field == (val)){                                                           \
            if((out)->field2 < (val2)){                                                        \
              val2 = (out)->field2;                                                            \
               if(((val3)+((out)->field2)) < val4[(TYPE)(out)->field1]){                                            \
                  X = (TYPE)((out)->field1);                                                   \
                  Y = val4[X] = (val3)+((out)->field2);                                        \
                  Z = val5[X] = (val);                                                         \
                  out2 = out;                                                                  \
                }                                                                              \
             }                                                                                 \
          }                                                                                    \
        }                                                                                      \
      } while(0)          
*/
#define SEARCH_S(head,out,field,val)                                                           \
    SEARCH_S2(head,out,field,val,next)

#define SEARCH_S2(head,out,field,val,next)                                                     \
do {                                                                                           \
    LL_FOREACH2(head,out,next) {                                                               \
      if ((out)->field == (val)) break;                                                        \
    }                                                                                          \
} while(0)

#define SEARCH_PROT(head,out,elt,cmp)                                                          \
    SEARCH_PROT2(head,out,elt,cmp,next)

#define SEARCH_PROT2(head,out,elt,cmp,next)                                                    \
do {                                                                                           \
    LL_FOREACH2(head,out,next) {                                                               \
      if ((cmp(out,elt))==0) break;                                                            \
    }                                                                                          \
} while(0)
/* these are identical to their singly-linked list counterparts */
//#define SEAR SEARCH_SCALAR_PROT
#define SEARCH_SCALAR SEARCH_S
#define SEARCH SEARCH_PROT
#define SEARCH_SCALAR2 SEARCH_S2
#define SEARCH2 SEARCH_PROT2

#define DELETE_ONE_PROT(head, elt, etmp)                                                        \
  do {                                                                                          \
    FOREACH(head, elt) {                                                                        \
      if(elt->tab.s == etmp.tab.s){                                                             \
        REMOVE(head, elt);   break;                                                             \
      }                                                                                         \
    }                                                                                           \
  } while(0)  

#define DELETE_ONE DELETE_ONE_PROT

#define DELETE_PROT(head, elt, etmp)                                                            \
  do {                                                                                          \
    FOREACH(head, elt) {                                                                        \
      if(elt->tab.s == etmp.tab.s){                                                             \
        REMOVE(head, elt);                                                                      \
      }                                                                                         \
    }                                                                                           \
  } while(0)                                                                                    \

#define DELETE DELETE_PROT

#define FREE_PROT(head, elt, tmp, free)                                                         \
do {                                                                                            \
  FOREACH_SAFE(head,elt,tmp) {                                                                  \
      REMOVE(head,elt);                                                                         \
      free(elt);                                                                                \
    }                                                                                           \
} while(0)                                                                                      \

#define FREE   FREE_PROT

#define PRINT_PROT(head, elt, action)                                                           \
  do {                                                                                          \
      FOREACH(head,elt) action("%llu->", (INTEGER)elt->tab.s);                                  \
    action("\n");                                                                               \
  } while(0)                                                                                    \


#define PRINT PRINT_PROT

#define REPLACE_E(head, el, add, prev, next)                                                   \
do {                                                                                           \
 assert(head != NULL);                                                                         \
 assert(el != NULL);                                                                           \
 assert(add != NULL);                                                                          \
 if ((head) == (el)) {                                                                         \
  (head) = (add);                                                                              \
  (add)->next = (el)->next;                                                                    \
  if ((el)->next == NULL) {                                                                    \
   (add)->prev = (add);                                                                        \
  } else {                                                                                     \
   (add)->prev = (el)->prev;                                                                   \
   (add)->next->prev = (add);                                                                  \
  }                                                                                            \
 } else {                                                                                      \
  (add)->next = (el)->next;                                                                    \
  (add)->prev = (el)->prev;                                                                    \
  (add)->prev->next = (add);                                                                   \
  if ((el)->next == NULL) {                                                                    \
   (head)->prev = (add);                                                                       \
  } else {                                                                                     \
   (add)->next->prev = (add);                                                                  \
  }                                                                                            \
 }                                                                                             \
} while (0)

#define REPLACE(head, el, add)                                                                 \
    REPLACE_E(head, el, add, prev, next)

#define PUSH_FRONT_ELEM2(head, el, add, prev, next)                                            \
do {                                                                                           \
 if((el)) {                                                                                    \
  assert(head != NULL);                                                                        \
  assert(add != NULL);                                                                         \
  (add)->next = (el);                                                                          \
  (add)->prev = (el)->prev;                                                                    \
  (el)->prev = (add);                                                                          \
  if ((head) == (el)) {                                                                        \
   (head) = (add);                                                                             \
  } else {                                                                                     \
   (add)->prev->next = (add);                                                                  \
  }                                                                                            \
 } else {                                                                                      \
  PUSH_BACK2(head, add, prev, next);                                                           \
 }                                                                                             \
} while (0)                                                                                    \

#define PUSH_FRONT_ELEM(head, el, add)                                                         \
    PUSH_FRONT_ELEM2(head, el, add, prev, next)

#define PUSH_BACK_ELEM2(head, el, add, prev, next)                                             \
do {                                                                                           \
 if((el)) {                                                                                    \
  assert(head != NULL);                                                                        \
  assert(add != NULL);                                                                         \
  (add)->next = (el)->next;                                                                    \
  (add)->prev = (el);                                                                          \
  (el)->next = (add);                                                                          \
  if ((add)->next) {                                                                           \
   (add)->next->prev = (add);                                                                  \
  } else {                                                                                     \
   (head)->prev = (add);                                                                       \
  }                                                                                            \
 } else {                                                                                      \
  PUSH_FRONT2(head, add, prev, next);                                                          \
 }                                                                                             \
} while (0)                                                                                    \

#define PUSH_BACK_ELEM(head, el, add)                                                          \
   PUSH_BACK_ELEM2(head, el, add, prev, next)