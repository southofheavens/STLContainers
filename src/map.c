#include "../include/map.h"

void map_init(map *mp)
{
    if (!mp)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    mp->root = NULL;
}

void map_destroy(map *mp)
{
    if (!mp)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    remove_map_recoursive(mp->root);
}

void tnode_init(tnode *node, int key, int value)
{
    if (!node)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->color = RED; /* when inserting, paint the node red */
    node->kv.first = key;
    node->kv.second = value;
}

void minsert(map *mp, int key, int value)
{
    if (mp->root == NULL)
    {
        mp->root = (tnode *)malloc(sizeof(tnode));
        tnode_init(mp->root, key, value);
        mp->root->color = BLACK;
    }
    else
    {
        tnode *curr = mp->root;
        while (curr && curr->kv.first != key)
        {
            if (key < curr->kv.first && curr->left == NULL) /* move left */
            {
                curr->left = (tnode *)malloc(sizeof(tnode));
                tnode_init(curr->left, key, value);
                curr->left->parent = curr;
                curr = curr->left;
                rebalance_after_insert(mp, curr);
                return;
            }
            if (key > curr->kv.first && curr->right == NULL) /* move right */
            {
                curr->right = (tnode *)malloc(sizeof(tnode));
                tnode_init(curr->right, key, value);
                curr->right->parent = curr;
                curr = curr->right;
                rebalance_after_insert(mp, curr);
                return;
            }
            if (key < curr->kv.first)
            {
                curr->left->parent = curr;
                curr = curr->left;
            }
            else
            {
                curr->right->parent = curr;
                curr = curr->right;
            }
        }
    }
}

void merase(map *mp, tnode *node)
{
    if (node->left == NULL && node->right == NULL) /* if node has no children */
    {
        if (node->color == RED) {
            erase_case1(mp,node);
        }
        else if (node->color == BLACK && node != mp->root) {
            erase_case3(mp,node);
        }
        else
        {
            mp->root = NULL;
            free(mp->root);
        }
    }
    else if ((node->left == NULL && node->right != NULL) /* if node has one child */
        || (node->left != NULL && node->right == NULL))
    {
        erase_case4(mp,node);
    }
    else { /* if node has two children */
        erase_case2(mp,node);
    }
}

void print_tree(map *mp)
{
    print_tree_helper(mp->root,0);
    printf("\n");
}

tnode *mfind(map *mp, int key)
{
    tnode *node = mp->root;
    while (node && node->kv.first != key) /* look for the required element */
    {
        if (node->kv.first < key) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }
    return node;
}

int tnode_key(tnode *node)
{
    if (!node)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return node->kv.first;
}

int tnode_value(tnode *node)
{
    if (!node)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return node->kv.second;
}

static void remove_map_recoursive(tnode *root)
{
    if (root == NULL) {
        return;
    }
    remove_map_recoursive(root->left);
    remove_map_recoursive(root->right);
    free(root);
}

static void rebalance_after_insert(map *mp, tnode *node)
{
    if (!mp)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    tnode *curr = node;
    tnode *parent = node->parent;
    tnode *grandpa = parent->parent;
    tnode *uncle;

    while (parent->color == RED)
    {
        if (parent->kv.first < grandpa->kv.first) /* father - left child */
        {
            uncle = grandpa->right;
            if (uncle && uncle->color == RED) /* if there is an uncle he is red */
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandpa->color = RED;

                curr = grandpa;
                if (curr->parent) {
                    parent = curr->parent;
                }
                if (parent->parent) {
                    grandpa = parent->parent;
                }
            }
            else /* uncle nullptr or black */
            {
                if (curr->kv.first > parent->kv.first) /* if curr is the right child */
                {
                    curr = parent;
                    left_rotate(mp, curr);
                }
                parent = curr->parent;
                grandpa = parent->parent;
                parent->color = BLACK;
                grandpa->color = RED;
                right_rotate(mp, grandpa);
            }
        }
        else /* father - right child */ 
        {
            uncle = grandpa->left;
            if (uncle && uncle->color == RED) /* if there is an uncle and he is red */
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandpa->color = RED;

                curr = grandpa;
                if (curr->parent) {
                    parent = curr->parent;
                }
                if (parent->parent) {
                    grandpa = parent->parent;
                }
            }
            else /* uncle nullptr or black */
            {
                if (curr->kv.first < parent->kv.first) /* if curr is the left child */
                {
                    curr = parent;
                    right_rotate(mp, curr);
                }
                parent = curr->parent;
                grandpa = parent->parent;
                parent->color = BLACK;
                grandpa->color = RED;
                left_rotate(mp, grandpa);
            }
        }
    }
    mp->root->color = BLACK;
}

static void rebalance_after_erase(map *mp, tnode *node)
{
    if (node == mp->root) {
        return;
    }
    tnode *sibling = node; /* brother of the son of the deleted element */

    if (sibling->color == RED)
    {
        tnode_colors color = sibling->parent->color;
        sibling->parent->color = sibling->color;
        sibling->color = color;

        if (sibling->parent->left == sibling)
        {
            right_rotate(mp, sibling->parent);
            tnode *new_sibling = sibling->right->left;
            new_sibling->parent = sibling->right;
            rebalance_after_erase(mp, new_sibling);
            return;
        }
        else
        {
            left_rotate(mp, sibling->parent);
            tnode *new_sibling = sibling->left->right;
            new_sibling->parent = sibling->left;
            rebalance_after_erase(mp, new_sibling);
            return;
        }
    }

    if (sibling->parent->right == sibling) /* if sibling is the right son */
    {
        if ((sibling->left && sibling->right && sibling->left->color == BLACK && sibling->right->color == BLACK) /* if both brother's sons are black */
            || (sibling->left && sibling->left->color == BLACK && !(sibling->right))
            || (!(sibling->left) && sibling->right && sibling->right->color == BLACK)
            || (!(sibling->left) && !(sibling->right)))
        {
            sibling->color = RED;
            if (sibling->parent->color == RED) {
                sibling->parent->color = BLACK;
            }
            else
            {
                if (sibling->parent != mp->root)
                {
                    /* if the sibling`s father is the left son */
                    if (sibling->parent->parent->left == sibling->parent) {
                        rebalance_after_erase(mp, sibling->parent->parent->right);
                    }
                    else { /* if the sibling`s father is the right son */
                        rebalance_after_erase(mp, sibling->parent->parent->left);
                    }
                }
            }
        }
        else if (sibling->left && sibling->left->color == RED /* if the brother's left son is red and the brother's right son is black */
                && ((sibling->right && sibling->right->color == BLACK) || !(sibling->right)))
        {
            sibling->left->color = BLACK;
            sibling->color = RED;
            right_rotate(mp, sibling);
            
            /* now our brother`s right son is red */
            rebalance_after_erase(mp, sibling->parent);
        }
        else if (sibling->right->color == RED) /* if our brother`s right son is red */
        {
            tnode_colors color = sibling->parent->color;
            sibling->parent->color = sibling->color;
            sibling->color = color;
            sibling->right->color = BLACK;
            left_rotate(mp, sibling->parent);
        }
    }
    else /* if sibling is the left son */
    {
        if ((sibling->left && sibling->right && sibling->left->color == BLACK && sibling->right->color == BLACK) // if both brother's sons are black
            || (sibling->left && sibling->left->color == BLACK && !(sibling->right))
            || (!(sibling->left) && sibling->right && sibling->right->color == BLACK)
            || (!(sibling->left) && !(sibling->right)))
        {
            sibling->color = RED;
            if (sibling->parent->color == RED) {
                sibling->parent->color = BLACK;
            }
            else
            {
                if (sibling->parent != mp->root)
                {
                    /* if the sibling`s father is the left son */
                    if (sibling->parent->parent->left == sibling->parent) {
                        rebalance_after_erase(mp, sibling->parent->parent->right);
                    }
                    else { /* if the sibling`s father is the right son */
                        rebalance_after_erase(mp, sibling->parent->parent->left);
                    }
                }
            }
        }
        else if (sibling->right && sibling->right->color == RED /* if brother's right son is red and brother's left son is black */
            && ((sibling->left && sibling->left->color == BLACK) || !(sibling->left)))
        {
            sibling->right->color = BLACK;
            sibling->color = RED;
            left_rotate(mp, sibling);

            /* now our brother`s left son is red */
            rebalance_after_erase(mp, sibling->parent);
        }
        else if (sibling->left->color == RED) /* if our brother`s left son is red */
        {
            tnode_colors color = sibling->parent->color;
            sibling->parent->color = sibling->color;
            sibling->color = color;
            sibling->left->color = BLACK;
            right_rotate(mp, sibling->parent);
        }
    }

    mp->root->color = BLACK; /* restore the RB property of the tree */
}

static void erase_case1(map *mp, tnode *node)
{
    if (node->kv.first < node->parent->kv.first) { /* if node is the left child */
        node->parent->left = NULL;
    }
    else { /* if node is the right child */
        node->parent->right = NULL;
    }
    free(node);
}

static void erase_case2(map *mp, tnode *node)
{
    tnode *min_of_right = node->right;
    while (min_of_right->left != NULL) { /* look for the minimum element from the right subtree */
        min_of_right = min_of_right->left;
    }

    /* in the element to be deleted we put the value from the minimum element of the right subtree, now we delete it */
    node->kv = min_of_right->kv;

    if (min_of_right->left == NULL && min_of_right->right == NULL) /* if he has no children */
    {
        if (min_of_right->color == BLACK) {
            erase_case3(mp,min_of_right);
        }
        else {
            erase_case1(mp,min_of_right);
        }
    }
    else { /* he has one child */
        erase_case4(mp,min_of_right);
    }
}

static void erase_case3(map *mp, tnode *node)
{
    if (node == mp->root)
    {
        free(node);
        mp->root = NULL;
    }
    else
    {
        if (node->parent->right == node) /* if node is the right child */
        {
            tnode *sibling = node->parent->left;
            sibling->parent = node->parent;
            node->parent->right = NULL;
            free(node);
            rebalance_after_erase(mp,sibling);
        }
        else /* if node is the left child */
        {
            tnode *sibling = node->parent->right;
            sibling->parent = node->parent;
            node->parent->left = NULL;
            free(node);
            rebalance_after_erase(mp,sibling);
        }
    }
}

static void erase_case4(map *mp, tnode *node)
{
    if (node->parent && node->parent->right == node) /* if node is the right child */
    {
        if (node->left) /* if the child is on the left */
        {
            if (node->left->color == RED) /* if the child is red */
            {
                node->parent->right = node->right;
                node->parent->right->color = BLACK;
                node->left->parent = node->parent;
                free(node);
            }
            else /* if the child is black */
            {
                node->parent->right = node->left;
                tnode *son_of_deleted_el = node->left;
                node->left->parent = node->parent;
                free(node);
                rebalance_after_erase(mp, son_of_deleted_el->parent->right);
            }
        }
        else /* if the child is on the right */
        {
            if (node->right->color == RED) /* if the child is red */
            {
                node->parent->right = node->right;
                node->parent->right->color = BLACK;
                node->right->parent = node->parent;
                free(node);
            }
            else /* if the child is black */
            {
                node->parent->right = node->right;
                tnode *son_of_deleted_el = node->right;
                node->right->parent = node->parent;
                free(node);
                rebalance_after_erase(mp, son_of_deleted_el->parent->left);
            }
        }
    }
    else if (node->parent && node->parent->left == node) /* if node is the left child */
    {
        if (node->left) /* if the child is on the left */
        {
            if (node->left->color == RED) /* if the child is red */
            {
                node->parent->left = node->left;
                node->parent->left->color = BLACK;
                node->left->parent = node->parent;
                free(node);
            }
            else /* if the child is black */
            {
                node->parent->left = node->left;
                tnode *son_of_deleted_el = node->left;
                node->left->parent = node->parent;
                free(node);
                rebalance_after_erase(mp, son_of_deleted_el->parent->right);
            }
        }
        else /* if the child is on the right */
        {
            if (node->right->color == RED) /* if the child is red */
            {
                node->parent->left = node->right;
                node->parent->left->color = BLACK;
                node->right->parent = node->parent;
                free(node);
            }   
            else /* if the child is black */
            {
                node->parent->left = node->right;
                tnode *son_of_deleted_el = node->right;
                node->right->parent = node->parent;
                free(node);
                rebalance_after_erase(mp, son_of_deleted_el->parent->left);
            }
        }
    }
    else /* if node - root */
    {
        if (node->left) /* if the child is on the left */
        {
            node->kv = node->left->kv;
            node->left = NULL;
            free(node->left);
        }
        else /* if the child is on the right */
        {
            node->kv = node->right->kv;
            node->right = NULL;
            free(node->right);
        }
    }
}

static void left_rotate(map *mp, tnode *node)
{
    if (!mp)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    tnode *curr = node;
    tnode *right_son = curr->right;
    tnode *left_son_of_right_son = right_son->left;

    tnode *parent = curr->parent;
    if (parent)
    {
        if (curr->kv.first < parent->kv.first) {
            parent->left = right_son;
        }
        else {
            parent->right = right_son;
        }
    }
    if (curr == mp->root)
    {
        mp->root = right_son;
        right_son->parent = NULL;
    }
    else {
        right_son->parent = curr->parent;
    }

    curr->right = left_son_of_right_son;
    if (left_son_of_right_son) {
        left_son_of_right_son->parent = curr;
    }
    curr->parent = right_son;
    right_son->left = curr;
}

static void right_rotate(map *mp, tnode *node)
{
    if (!mp)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    tnode *curr = node;
    tnode *left_son = curr->left;
    tnode *right_son_of_left_son = left_son->right;

    tnode *parent = curr->parent;
    if (parent)
    {
        if (curr->kv.first < parent->kv.first) {
            parent->left = left_son;
        }
        else {
            parent->right = left_son;
        }
    }
    if (curr == mp->root)
    {
        mp->root = left_son;
        left_son->parent = NULL;
    }
    else {
        left_son->parent = curr->parent;
    }

    curr->left = right_son_of_left_son;
    if (right_son_of_left_son) {
        right_son_of_left_son->parent = curr;
    }
    curr->parent = left_son;
    left_son->right = curr;
}

static void print_tree_helper(tnode *node, unsigned depth)
{
    if (node)
    {
        print_tree_helper(node->right, depth+1);

        int i;
        for (i = 0; i < depth; ++i) {
            printf("    ");
        }
        printf("%d(%d)\n", node->kv.first, node->color);

        print_tree_helper(node->left, depth+1);
    }
}
