#include "../include/list.h"

void list_init(list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "list_init: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    lst->end = (lnode *)malloc(sizeof(lnode));
    if (!lst->end)
    {
        fprintf(stderr, "bad alloc");
        exit(EXIT_FAILURE);
    }
    lst->head = lst->end;
    lst->end->prev = NULL;
    lst->end->next = NULL;
    lst->size = 0;
}

void list_destroy(list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "list_destroy: a null pointer was received as an argument");
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
        fprintf(stderr, "lpush_back: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (lst->size == 0)
    {
        lst->head = (lnode *)malloc(sizeof(lnode));
        if (!lst->head)
        {
            fprintf(stderr, "bad alloc");
            exit(EXIT_FAILURE);
        }
        lst->head->elem = elem;
        lst->head->prev = NULL;
        lst->head->next = lst->end;
        lst->end->prev = lst->head;
    }
    else
    {
        lnode *new_elem = (lnode *)malloc(sizeof(lnode));
        if (!new_elem)
        {
            fprintf(stderr, "bad alloc");
            exit(EXIT_FAILURE);
        }
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
        fprintf(stderr, "lpush_front: a null pointer was received as an argument");
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
        if (!new_head)
        {
            fprintf(stderr, "bad alloc");
            exit(EXIT_FAILURE);
        }
        new_head->elem = elem;
        new_head->prev = NULL;
        new_head->next = lst->head;
        lst->head->prev = new_head;
        lst->head = new_head;
    }
    lst->size++;
}

void linsert(list *lst, const list_iterator it, int elem)
{
    if (!lst || !it)
    {
        fprintf(stderr, "linsert: a null pointer was received as an argument");
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
        if (!new_elem)
        {
            fprintf(stderr, "bad alloc");
            exit(EXIT_FAILURE);
        }
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
        fprintf(stderr, "lpop_back: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (lst->size == 0)
    {
        fprintf(stderr, "lpop_back: list is empty");
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
        fprintf(stderr, "lpop_front: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (lst->size == 0)
    {
        fprintf(stderr, "lpop_front: list is empty");
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
        fprintf(stderr, "lerase: a null pointer was received as an argument");
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

void lresize(list *lst, size_t new_size)
{
    if (!lst)
    {
        fprintf(stderr, "lresize: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    size_t i;
    size_t old_size;
    old_size = lst->size;
    if (new_size > old_size) 
    {
        for (i = 0; i < new_size - old_size; ++i) {
            lpush_back(lst,0);
        }
    }
    else if (new_size < old_size)
    {
        size_t i;
        for (i = 0; i < old_size - new_size; ++i) {
            lpop_back(lst);
        }
    }
}

void lclear(list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "lclear: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    size_t i;
    for (i = 0; i < lst->size; ++i) {
        lpop_back(lst);
    }
}

int lfront(list *lst)
{
    check_null_pointers("lfront: a null pointer was " 
        "received as an argument", 1, lst);

    if (lempty(lst)) 
    {
        fprintf(stderr, "lfront: list is empty");
        exit(EXIT_FAILURE);
    }

    return lderef(lbegin(lst));
}

int lback(list *lst)
{
    check_null_pointers("lback: a null pointer was " 
        "received as an argument", 1, lst);

    if (lempty(lst)) 
    {
        fprintf(stderr, "lback: list is empty");
        exit(EXIT_FAILURE);
    }

    list_iterator it = lend(lst);
    ladvance(&it,-1);

    return lderef(it);
}

void lset(list_iterator it, int new_val)
{
    if (!it)
    {
        fprintf(stderr, "lset: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    it->elem = new_val;
}

void lassign_single(list *lst, size_t count, int elem)
{
    if (!lst)
    {
        fprintf(stderr, "lassign_single: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    size_t i, list_size;
    list_iterator it;

    if (count >= lst->size)
    {
        for (it = lbegin(lst); it != lend(lst); ladvance(&it,1)) {
            lset(it, elem);
        }
        for (i = 0, list_size = lsize(lst); i < count - list_size; ++i) {
            lpush_back(lst,elem);
        }
    }
    else
    {
        for (i = 0, list_size = lsize(lst); i < list_size - count; ++i) {
            lpop_back(lst);
        }
        for (it = lbegin(lst); it != lend(lst); ladvance(&it,1)) {
            lset(it, elem);
        }
    }
}

void lassign_range(list *lst, const list_iterator begin, const list_iterator end)
{
    check_null_pointers("lassign_range: a null pointer was "
        "received as an argument", 3, lst, begin, end);

    /* lit is a begin iterator for the list to be filled */
    /* b is a copy of the begin iterator from the half-open range */
    /* the copy is needed because the iterator from the arguments is */
    /* constant and we cannot apply ladvance to it */
    list_iterator lit, b; 
    lit = lbegin(lst);
    b = begin;

    /* Number of elements in a half-open range begin-end */
    size_t elems_count;
    elems_count = 0;

    while (b != end)
    {
        if (lit == lend(lst)) {
            lpush_back(lst,lderef(b));
        }
        else {
            lset(lit,lderef(b));
        }
        if (lit != lend(lst)) {
            ladvance(&lit,1);
        }
        ladvance(&b,1);
        elems_count++;
    }
    if (lsize(lst) > elems_count)
    {
        size_t i, ls;
        i = 0;
        ls = lsize(lst);

        for (i = 0; i < ls - elems_count; ++i) {
            lpop_back(lst);
        }
    }
}

list_iterator lbegin(const list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "lbegin: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return lst->head;
}

list_iterator lend(const list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "lend: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return lst->end;
}

void ladvance(list_iterator *it, int count)
{
    if (!it)
    {
        fprintf(stderr, "ladvance: a null pointer was received as an argument");
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

int lderef(const list_iterator it)
{
    if (!it)
    {
        fprintf(stderr, "lderef: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return it->elem;
}

size_t lsize(const list *lst)
{
    if (!lst)
    {
        fprintf(stderr, "lsize: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return lst->size;
}

unsigned lempty(const list *lst)
{
    check_null_pointers("lempty: a null pointer was "
        "received as an argument", 1, lst);

    return (lst->head == lst->end);
}

void lsort(list *lst)
{
    check_null_pointers("lsort: a null pointer was "
        "received as an argument", 1, lst);

    if (lst->size == 0) { 
        return; 
    }
    /* "drop" the end for correct operation of functions */
    lst->end->prev->next = NULL;
    lst->head = merge_sort(lst->head);

    lnode *curr = lst->head;
    while (curr->next)
    {
        curr->next->prev = curr;
        curr = curr->next;
    }
    curr->next = lst->end;
    lst->end->prev = curr;
    lst->head->prev = NULL;
}

static lnode *merge_sort(lnode *head)
{
    lnode *first_half_end = get_middle(head);

    if (first_half_end->next == NULL) {
        return merge(head, NULL);
    }
    else
    {
        lnode *first_half = head;
        lnode *second_half = first_half_end->next;
        /* "break" the list */
        first_half_end->next = NULL;

        lnode *left = merge_sort(first_half);
        lnode *right = merge_sort(second_half);
        return merge(left,right);
    }
}

static lnode *merge(lnode *first_head, lnode *second_head)
{
    lnode *head, *prev, *curr;
    head = NULL;
    while (first_head || second_head)
    {
        if (first_head)
        {
            if (second_head)
            {
                if (first_head->elem < second_head->elem) 
                {
                    curr = first_head;
                    first_head = first_head->next;
                }
                else 
                {
                    curr = second_head;
                    second_head = second_head->next;
                }
            }
            else 
            {
                curr = first_head;
                if (head == NULL)
                {
                    head = curr;
                    break;
                }
                else
                {
                    prev->next = curr;
                    break;
                }
            }
        }
        else
        {
            curr = second_head;
            if (head == NULL)
            {
                head = curr;
                break;
            }
            else
            {
                prev->next = curr;
                break;
            }
        }
        
        if (head == NULL) 
        {
            head = curr;
            prev = head;
        }
        else
        {
            prev->next = curr;
            prev = prev->next;
        }
    }

    return head;
}

static lnode *get_middle(lnode *head)
{
    lnode *slow, *fast;
    slow = head;
    fast = head;

    while (fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
