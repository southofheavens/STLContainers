#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    RED,
    BLACK
} tnode_colors;

typedef struct
{
    int first;
    int second;
} pair;

typedef struct tnode
{
    struct tnode *parent;   /* pointer to the parent */
    struct tnode *left;     /* pointer to the left child */
    struct tnode *right;    /* pointer to the right child */
    tnode_colors color;     /* node color */
    pair kv;                /* node storing key and value */
} tnode;

typedef struct
{
    tnode *root;
} map;

/* --------------------------------------------- */
/*             Construct / destruct              */
/* --------------------------------------------- */

/* Initializes a vector */
void map_init(map *);

/* Cleans up resources */
void map_destroy(map *);

/* Initializes a node */
void tnode_init(tnode *, int, int);

/* --------------------------------------------- */
/*             Interaction with tree             */
/* --------------------------------------------- */

/* Inserts a key-value pair into the tree */
void minsert(map *, int, int);

/* Removes a node from the tree */
void merase(map *, tnode *);

/* Prints a tree */
void print_tree(map *);

/* Searches the tree for a node corresponding to the specified key and returns it */
tnode *mfind(map *, int);

/* Gets the key from a node */
int tnode_key(tnode *);

/* Gets the value from a node */
int tnode_value(tnode *);

/* --------------------------------------------- */
/*              Auxiliary functions              */
/* --------------------------------------------- */

/* Helper function for cleaning resources occupied by tree elements */
static void remove_map_recoursive(tnode *);

/* Function to rebalance the tree after inserting an element */
static void rebalance_after_insert(map *, tnode *);

/* Function to rebalance the tree after erasing an element */
static void rebalance_after_erase(map *, tnode *);

/* Removing red node with 0 children */
static void erase_case1(map *, tnode *);

/* Removing a red or black node with 2 children */
static void erase_case2(map *, tnode *);

/* Removing a black node with 0 children */
static void erase_case3(map *, tnode *);

/* Removing a black node with 1 child */
static void erase_case4(map *, tnode *);

/* Left rotate of the tree */
static void left_rotate(map *, tnode *);

/* Right rotate of the tree */
static void right_rotate(map *, tnode *);

/* Helper function for prints a tree */
static void print_tree_helper(tnode *, unsigned);

#endif