#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define VEC_INIT_CAPACITY 8

typedef struct
{
    int *elems;
    size_t capacity;
    size_t size;
} vector;

typedef int * vec_iterator;

/* --------------------------------------------- */
/*             Construct / destruct              */
/* --------------------------------------------- */

/* Initializes a vector */
void vector_init(vector *);

/* Cleans up resources */
void vector_destroy(vector *);

/* --------------------------------------------- */
/*                Adding elements                */
/* --------------------------------------------- */

/* Adds an element to the end of a vector */
void vpush_back(vector *, int);

/* Inserts an element into a vector before the iterator */
void vinsert(vector *, const vec_iterator, int);

/* --------------------------------------------- */
/*               Deleting elements               */
/* --------------------------------------------- */

/* Removes the last element of a vector */
void vpop_back(vector *);

/* Removes the vector element located at the iterator */
void verase(vector *, vec_iterator);

/* --------------------------------------------- */
/*            Changing the size/capacity         */
/* --------------------------------------------- */

/* Changes the size of a vector */
void vresize(vector *, size_t);

/* Clears the vector but does not change the capacity */
void vclear(vector *);

/* Reserves memory for vector elements */
void reserve(vector *, size_t);

/* --------------------------------------------- */
/*                Other functions                */
/* --------------------------------------------- */

/* Returns a pointer to the first element of the vector */
int *data(const vector *);

/* Replaces the contents of a vector with arg3, repeating it arg2 times */
void vassign_single(vector *, size_t, int);

/* Replaces the contents of a vector with elements from the range specified by iterators */
void vassign_range(vector *, const vec_iterator, const vec_iterator);

/* Returns the size of the vector */
size_t vsize(const vector *);

/* Returns a positive value if the vector is empty and zero otherwise */
unsigned vempty(const vector *);

/* Returns the capacity of a vector */
size_t capacity(const vector *);

/* Swaps the contents of two vectors */
void vswap(vector *, vector *);

/* Returns a value to a vector element at index */
int vat(const vector *, size_t);

/* Changes the value of a vector at an index */
void vset(vector *, size_t, int);

/* Sorts a vector */
void vsort(vector *, int (*)(const void *, const void *));

/* Searches for an element in a vector and returns an iterator pointing to the element */
vec_iterator vfind(const vector *, int);

/* Returns an iterator pointing to the first element of the vector */
vec_iterator vbegin(const vector *);

/* Returns an iterator pointing to the element following the last one */
vec_iterator vend(const vector *);

/* Returns the first element of the vector */
int vfront(const vector *);

/* Returns the last element of a vector */
int vback(const vector *);

/* Reallocates memory for int *elems */
/* Takes the new capacity of the vector as an argument */
static void vrealloc(vector *, size_t);

#endif