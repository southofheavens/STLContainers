#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include "utility.h"

typedef struct snode snode;

struct snode
{
    int elem;
    snode *next;
};

typedef struct
{
    snode *top;
    size_t size;
} stack;

/* --------------------------------------------- */
/*             Construct / destruct              */
/* --------------------------------------------- */

/* Initializes a stack */
void stack_init(stack *);

/* Cleans up resources */
void stack_destroy(stack *);

/* --------------------------------------------- */
/*                Adding elements                */
/* --------------------------------------------- */

/* Adds an element to the stack */
void spush(stack *, int);

/* --------------------------------------------- */
/*               Deleting elements               */
/* --------------------------------------------- */

/* Removes an element from the stack */
void spop(stack *);

/* --------------------------------------------- */
/*               Access to elements              */
/* --------------------------------------------- */

/* Returns the element from the top of the stack */
int top(const stack *);

/* --------------------------------------------- */
/*               Changing elements               */
/* --------------------------------------------- */

/* Swaps the contents of two stacks */
void sswap(stack *, stack *);

/* --------------------------------------------- */
/*               Stack information               */
/* --------------------------------------------- */

/* Returns the size of the stack */
size_t ssize(const stack *);

/* Returns a positive value if the stack is empty and zero otherwise */
unsigned sempty(const stack *);

#endif