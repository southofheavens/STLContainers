#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

typedef struct lnode lnode;

struct lnode    
{
    lnode *prev;
    lnode *next;
    int elem;
};

typedef struct
{
    lnode *head;
    lnode *end;  /* element that follows tail */
    size_t size;
} list;

typedef lnode * list_iterator;

/* --------------------------------------------- */
/*             Construct / destruct              */
/* --------------------------------------------- */

/* Initializes a list */
void list_init(list *);

/* Cleans up resources */
void list_destroy(list *);

/* --------------------------------------------- */
/*                Adding elements                */
/* --------------------------------------------- */

/* Adds an element to the end of the list */
void lpush_back(list *, int);

/* Adds an element to the beginning of the list */
void lpush_front(list *, int);

/* Inserts an element into a list before the iterator */
void linsert(list *, const list_iterator, int);

/* --------------------------------------------- */
/*               Deleting elements               */
/* --------------------------------------------- */

/* Removes the last element of a list */
void lpop_back(list *);

/* Removes the first element of a list */
void lpop_front(list *);

/* Removes the list element located at the iterator */
void lerase(list *, list_iterator);

/* --------------------------------------------- */
/*            Changing the size/capacity         */
/* --------------------------------------------- */

/* Changes the size of a list */
void lresize(list *, size_t);

/* Clears the list */
void lclear(list *);

/* --------------------------------------------- */
/*                Other functions                */
/* --------------------------------------------- */

/* Replaces the value of the element pointed to by the iterator */
void lset(list_iterator *, int);

/* Replaces the contents of a list with arg3, repeating it arg2 times */
void lassign_single(list *, size_t, int);

/* Replaces the contents of a list with elements from a half-open range ("[a,b)") specified by iterators */
void lassign_range(list *, const list_iterator, const list_iterator);

/* Returns the size of the list */
size_t lsize(const list *);

/* Returns an iterator pointing to the first element of the list */
list_iterator lbegin(const list *);

/* Returns an iterator pointing to the element following the last one */
list_iterator lend(const list *);

/* Moves the iterator by the specified number of elements */
void ladvance(list_iterator *, int);

/* Returns the value of the element pointed to by the iterator (dereference iterator) */
int lderef(const list_iterator);

#endif