#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct lnode    
{
    struct lnode *prev;
    struct lnode *next;
    int elem;
} lnode;

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
void linsert(list *, list_iterator, int);

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



/* --------------------------------------------- */
/*                Other functions                */
/* --------------------------------------------- */

/* Returns the size of the list */
size_t lsize(const list *);

/* Returns an iterator pointing to the first element of the list */
list_iterator lbegin(const list *);

/* Returns an iterator pointing to the element following the last one */
list_iterator lend(const list *);

/* Moves the iterator by the specified number of elements */
void ladvance(list_iterator *, int);

/* Returns the value of the element pointed to by the iterator (dereference iterator) */
int derefit(const list_iterator);

#endif