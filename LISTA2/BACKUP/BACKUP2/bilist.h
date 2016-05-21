#ifndef _BILIST_H_
#  define _BILIST_H_

#define BILIST_Init(x)         {(x)->pnext=(x)->pprev=(x);     }
#define BILIST_IsEmpty(x)      ((x)->pnext==(x)                )

/* insert y after x     */
#define BILIST_Insert(x,y)     {((y)->pnext=(x)->pnext)->pprev=(y);\
                                 ((x)->pnext=(y))->pprev=(x);   }

/* insert y B4 x        */
#define BILIST_InsertB4(x,y)   {((y)->pprev=(x)->pprev)->pnext=(y);\
                                 ((x)->pprev=(y))->pnext=(x);   }

/* exclude x from list  */
#define BILIST_Exclude(x)      {((x)->pprev)->pnext=(x)->pnext;\
                                 ((x)->pnext)->pprev=(x)->pprev;}

#define for_BILIST_Elements(x,y) for( y = (x)->pnext; y != (x); y = (y)->pnext)
#define for_BILIST_ElementsSafe(x,y,z) for(y=(x)->pnext,z=(y)->pnext;y!=(x);y=z,z=(y)->pnext)


int test();


#define TRUE    1
#define FALSE   0

typedef int bool;

#endif /* _BILIST_H_ */
