#include "../include/list.h"

void list_init(list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    lst->end = (lnode *)malloc(sizeof(lnode));
    lst->head = lst->end;
    lst->end->prev = NULL;
    lst->end->next = NULL;
    lst->size = 0;
}

void list_destroy(list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (lst->head == lst->end) 
    {
        free(lst->head);
        return;
    }
    if (lst->end->prev) {
        lst->end->prev->next = NULL;
    }
    free(lst->end);
    lst->end = NULL;
    while (lst->head)
    {
        lnode *next = lst->head->next;
        free(lst->head);
        lst->head = next;
    }
}

void lpush_back(list *lst, int elem)
{
    if (!lst)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (lst->size == 0)
    {
        lst->head = (lnode *)malloc(sizeof(lnode));
        lst->head->elem = elem;
        lst->head->prev = NULL;
        lst->head->next = lst->end;
        lst->end->prev = lst->head;
    }
    else
    {
        lnode *new_elem = (lnode *)malloc(sizeof(lnode));
        new_elem->elem = elem;
        new_elem->prev = lst->end->prev;
        new_elem->next = lst->end;
        lst->end->prev->next = new_elem;
        lst->end->prev = new_elem;
    }
    lst->size++;
}

void lpush_front(list *lst, int elem)
{
    if (!lst)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (lst->size == 0)
    {
        lpush_back(lst,elem);
        return;
    }
    else
    {
        lnode *new_head = (lnode *)malloc(sizeof(lnode));
        new_head->elem = elem;
        new_head->prev = NULL;
        new_head->next = lst->head;
        lst->head->prev = new_head;
        lst->head = new_head;
    }
    lst->size++;
}

void linsert(list *lst, list_iterator it, int elem)
{
    if (!lst || !it)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (it == lst->head) {
        lpush_front(lst,elem);
    }
    else if (it == lst->end) {
        lpush_back(lst,elem);
    }
    else
    {
        lnode *new_elem = (lnode *)malloc(sizeof(lnode));
        new_elem->elem = elem;
        new_elem->prev = it->prev;
        new_elem->next = it;
        it->prev->next = new_elem;
        it->prev = new_elem;
        lst->size++;
    }
}

void lpop_back(list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (lst->size == 0)
    {
        fprintf(stderr, "lpop_back: error: list is empty");
        exit(EXIT_FAILURE);
    }
    lnode *del_prev = lst->end->prev->prev; 
    free(lst->end->prev);
    if (del_prev)
    {
        del_prev->next = lst->end;
        lst->end->prev = del_prev;
    }
    else 
    {
        lst->head = lst->end;
        lst->end->prev = NULL;
    }
    lst->size--;
}

void lpop_front(list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (lst->size == 0)
    {
        fprintf(stderr, "lpop_front: error: list is empty");
        exit(EXIT_FAILURE);
    }
    lnode *del_next = lst->head->next;
    free(lst->head);
    if (del_next != lst->end)
    {
        lst->head = del_next;
        lst->head->prev = NULL;
    }
    else 
    {
        lst->head = lst->end;
        lst->end->prev = NULL;
    }
    lst->size--;
}

void lerase(list *lst, list_iterator it)
{
    if (!lst || !it)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (it == lst->head) {
        lpop_front(lst);
    }
    else if (it == lst->end->prev) {
        lpop_back(lst);
    }
    else
    {
        lnode *del_prev = it->prev;
        del_prev->next = it->next;
        it->next->prev = del_prev;
        free(it);
        lst->size--;
    }
}

size_t lsize(const list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return lst->size;
}

list_iterator lbegin(const list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return lst->head;
}

list_iterator lend(const list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return lst->end;
}

void ladvance(list_iterator *it, int count)
{
    if (!it)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (count > 0)
    {
        for (; count > 0; --count) {
            *it = (*it)->next;
        }
    }
    else if (count < 0)
    {
        for (; count < 0; ++count) {
            *it = (*it)->prev;
        }
    }
}

int derefit(const list_iterator it)
{
    if (!it)
    {
        fprintf(stderr, "a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return it->elem;
}
