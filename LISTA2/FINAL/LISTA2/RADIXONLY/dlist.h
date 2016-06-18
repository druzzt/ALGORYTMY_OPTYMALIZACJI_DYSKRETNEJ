#pragma once
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
#define ARLOC(X, T)                                                                            \
      do{                                                                                      \
      if((X = malloc(sizeof(T))) == NULL)                                                      \
      /*exit(-1);*/NULL;                                                                       \
      } while(0)

#define ifContainsOnlyOneVertex(x,y,z,q)                                                       \
  if(!(x==0||y[x+1]-y[x]==1 || z[x]->q==NULL))

#define modificationOfBuckets8(INTEGER,n,gra,min_no,next,cost,nr,di,var1,pi,dest,ranges,b,q,a1,a2,a3,a4)\
    for(n=gra[min_no]; n!=NULL; n=n->next){                                                   \
        INTEGER var1 = n->idx;                                                                \
        INTEGER cost = n->cost;                                                               \
        INTEGER nr = q[var1].nr;                                                              \
        if(di[var1]>di[min_no]+cost){                                                         \
          a3(&b[nr],&q[var1],nr);                                                             \
          di[var1] = di[min_no]+cost;                                                         \
          pi[var1] = min_no;                                                                  \
          if(di[var1]<0){                                                                     \
            a1("!");                                                                          \
            a2(-1);                                                                           \
          }                                                                                   \
          INTEGER dest = (nr==-1) ? 31 :nr;                                                   \
          for(dest=dest; dest>=0&&di[var1]<ranges[dest];dest--);                              \
          a4(&b[dest],&q[var1],dest);                                                         \
        }                                                                                     \
    }

#define extractMinVertexFromBucket(tmp,bucket,iterator,idx,min,di,no,INT)                     \
    INT no = bucket[iterator]->idx;                                                           \
    INT min = di[no];                                                                         \
    for(tmp=bucket[iterator]->next;tmp;tmp=tmp->next){                                        \
      if(di[tmp->idx]<min){                                                                   \
        no=tmp->idx;                                                                          \
        min=di[no];                                                                           \
      }                                                                                       \
    }

#define initBuckets8(INT, d, p, q, SIZEV, INT_MAX) \
    do{\
    int i=0;\
    for(i=0;i<SIZEV;i++){\
      q[i].idx=i;\
      q[i].nr=-1;\
      d[i]=INT_MAX;\
      p[i]=-1;\
    }\
    }while(0);

#define continueTillNextNonEmptyBucket(i, b)\
    do{\
      for(;i<32&&b[i]==NULL;i++);\
        if(i==32) break;\
    }while(0);

#define relabelBuckets(ranges,i,INF,min)\
    do{\
      int j=0;\
      ranges[0]=min;\
      for(j=0;j<i;j++){\
        ranges[j+1]=ranges[0]+(1<<j);\
      }\
      ranges[i]=INF;\
    }while(0);

#define wipeWholeBucketAndPutToTheProper(b,delBel,q,i,d,ranges,addbel)\
    do{\
      while(b[i]!=NULL){\
        int n_no=b[i]->idx;\
        delBel(&b[i],&q[n_no],i);\
        int dest=i-1;\
        for(;dest>=0&&d[n_no]<ranges[dest];dest--);\
          addbel(&b[dest],&q[n_no],dest);\
      }\
      i=0;\
    }while(0);

#define getFirstVertex(minimal, b,i,delBel,q)\
    do{\
      minimal=b[i];\
      int min_idx=minimal->idx;\
      delBel(&b[i],&q[min_idx],i);\
    }while(0);

#define nonEmptyBucketFound(i,ranges,b)\
    if(!(i==0||ranges[i+1]-ranges[i]==1||b[i]->next==NULL))

#define whileAllVerticesNot(labeled,V)\
      for(labeled=0;labeled<V;labeled++)


#define extractMinVertex(no,min,b,d,i,p)\
      do{\
        no=b[i]->idx;\
        min=d[no];\
        for(p=b[i]->next;p;p=p->next){\
          if(d[p->idx]<min){\
            no=p->idx;\
            min=d[no];\
          }\
        }\
      }while(0);

#define ARLOC_A(X, T, MULTIPLIER)                                                              \
      do{                                                                                      \
      if((X = malloc(MULTIPLIER*sizeof(T))) == NULL)                                           \
      exit(-1);                                                                                \
      } while(0)

#define REARLOC_A(X, T, MULTIPLIER)                                                            \
      do{                                                                                      \
      if((X = realloc(X,MULTIPLIER*sizeof(T))) == NULL)                                        \
      exit(-1);                                                                                \
      } while(0)

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

#define updateAll(n,gra,d,min_idx,delBel,addBel,dest,ranges)\
  do{\
    for(n=gra[min_idx];n!=NULL;n=n->next){\
      int n_no = n->idx;\
      int cost = n->cost;\
      int nr = q[n_no].nr;\
      if(d[n_no]>d[min_idx]+cost){\
        delBel(&b[nr],&q[n_no],nr);\
        d[n_no]=d[min_idx]+cost;\
        p[n_no]=min_idx;\
        int dest=(nr==-1)?31:nr;\
        for(;dest>=0&&d[n_no]<ranges[dest];dest--);\
        addBel(&b[dest],&q[n_no],dest);\
      }\
    }\
  }while(0);

#define wipePointers(d,p,q,b)\
  do{\
    free(d);\
     free(p);\
      free(q);\
       free(b);\
  }while(0);

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
#define Q_FOREACH(head, el)                                                                    \
        for((el)=head; el ; el=(el)->next)

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
               if(((val3)+((out)->field2)) < val4[(TYPE)(out)->field1]){                       \
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

#define DELETE_ONE_PROT(head, elt, etmp,field)                                                  \
  do {                                                                                          \
    FOREACH(head, elt) {                                                                        \
      if(elt->field == etmp.field){                                                             \
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
#define DELETE_PROT_SEARCH(head, elt, tmp, free, val)                                           \
do {                                                                                            \
  FOREACH_SAFE(head,elt,tmp) {                                                                  \
    if(elt->tab.s == val){                                                                      \
      REMOVE(head,elt);                                                                         \
    }                                                                                           \
  }                                                                                             \
} while(0)                                                                                      \

#define DELETE_SEARCH   FREE_PROT_SEARCH

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




















