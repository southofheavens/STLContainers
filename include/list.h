#ifndef LIST_H
#define LIST_H

#include <stdio.h>

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
void lpush_back(list *, const int);

/* Adds an element to the beginning of the list */
void lpush_front(list *, const int);

/* Inserts an element into a list before the iterator */
void linsert(list *, const list_iterator, const int);

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
/*               Changing the size               */
/* --------------------------------------------- */

/* Changes the size of a list */
void lresize(list *, const size_t);

/* Clears the list */
void lclear(list *);

/* --------------------------------------------- */
/*               Access to elements              */
/* --------------------------------------------- */

/* Returns the first element of the list */
int lfront(list *);

/* Returns the last element of the list */
int lback(list *);

/* --------------------------------------------- */
/*               Changing elements               */
/* --------------------------------------------- */

/* Replaces the value of the element pointed to by the iterator */
void lset(list_iterator, const int);

/* Replaces the contents of a list with arg3, repeating it arg2 times */
void lassign_single(list *, const size_t, const int);

/* Replaces the contents of a list with elements from a half-open range ("[a,b)") */
/* specified by iterators */
void lassign_range(list *, const list_iterator, const list_iterator);

/* Swaps the contents of two lists */
void lswap(list *, list *);

/* --------------------------------------------- */
/*             Working with iterators            */
/* --------------------------------------------- */

/* Returns an iterator pointing to the first element of the list */
list_iterator lbegin(const list *);

/* Returns an iterator pointing to the element following the last one */
list_iterator lend(const list *);

/* Moves the iterator by the specified number of elements */
void ladvance(list_iterator *, const int);

/* Returns the value of the element pointed to by the iterator (dereference iterator) */
int lderef(const list_iterator);

/* --------------------------------------------- */
/*               List information                */
/* --------------------------------------------- */

/* Returns the size of the list */
size_t lsize(const list *);

/* Returns a positive value if the vector is empty and zero otherwise */
unsigned lempty(const list *); 

/* --------------------------------------------- */
/*               Sorting / search                */
/* --------------------------------------------- */

/* Sorts a list */
void lsort(list *, const int (*)(const void *, const void *));

/* Searches for an element in a list and returns an iterator pointing to the first */
/* occurrence of the element */
list_iterator lfind(const list *, const int); 

/* --------------------------------------------- */
/*              Auxiliary functions              */
/* --------------------------------------------- */

/* Helper recursive function for sorting a list */
static lnode *merge_sort(lnode *, const int (*)(const void *, const void *));

/* Takes pointers to the beginning of lists and merges them into a single sorted list */
static lnode *merge(lnode *, lnode *, const int (*)(const void *, const void *));

/* Takes a pointer to the head of the list, returns a pointer to the center element */
static lnode *get_middle(lnode *);

#endif