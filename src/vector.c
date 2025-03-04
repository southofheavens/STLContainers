#include "../include/vector.h"

void vector_init(vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "vector_init: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    vec->elems = NULL;
    vec->capacity = 0;
    vec->size = 0;
}

void vector_destroy(vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "vector_destroy: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (vec->elems) {
        free(vec->elems);
    }
}

void vpush_back(vector *vec, int el)
{
    if (!vec)
    {
        fprintf(stderr, "vpush_back: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (!(vec->elems))
    {
        vec->capacity = VEC_INIT_CAPACITY;
        vec->elems = (int *)calloc(vec->capacity, sizeof(int));
        if (!vec->elems)
        {
            fprintf(stderr, "bad alloc");
            exit(EXIT_FAILURE);
        }
        vec->elems[vec->size] = el;
        vec->size += 1;
    }
    else
    {
        if (vec->size + 1 == vec->capacity)
        {
            vec->capacity *= 2;
            vrealloc(vec, vec->capacity);
        }

        vec->elems[vec->size] = el;
        vec->size += 1;
    }
}

void vinsert(vector *vec, const vec_iterator it, int elem)
{
    if (!vec || !it)
    {
        fprintf(stderr, "vinsert: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (it < vbegin(vec) || it > vend(vec))
    {
        fprintf(stderr, "vinsert: invalid iterator");
        exit(EXIT_FAILURE);
    }
    if (it == vend(vec))
    {
        vpush_back(vec, elem);
        return;
    }

    if (vec->size + 1 == vec->capacity)
    {
        vec->capacity *= 2;
        vrealloc(vec, vec->capacity);
    }

    size_t i;
    for (i = vec->size; i > it - vec->elems; --i) {
        vec->elems[i] = vec->elems[i-1];
    }

    *it = elem;
    vec->size++;
}

void vpop_back(vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "vpop_back: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (vec->size > 0) {        
        vec->size--;
    }
    else
    {
        fprintf(stderr, "vpop_back: vector is empty");
        exit(EXIT_FAILURE);
    }
}

void verase(vector *vec, vec_iterator it)
{
    if (!vec || !it)
    {
        fprintf(stderr, "verase: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (it < vbegin(vec) || it >= vend(vec))
    {
        fprintf(stderr, "verase: invalid iterator");
        exit(EXIT_FAILURE);
    }       

    size_t i;
    for (i = it - vec->elems; i < vec->size - 1; ++i) {
        vec->elems[i] = vec->elems[i+1];
    }
    vec->size--;
}

void vresize(vector *vec, size_t newSize)
{
    if (!vec)
    {
        fprintf(stderr, "vresize: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (newSize > vec->capacity)
    {
        vec->capacity = newSize;
        vrealloc(vec, vec->capacity);
    }
    size_t i;
    for (i = vec->size; i < newSize; ++i) {
        vec->elems[i] = 0;
    }
    vec->size = newSize;
}

void vclear(vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "vclear: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    vec->size = 0;
}

void reserve(vector *vec, size_t elems)
{
    if (!vec)
    {
        fprintf(stderr, "reserve: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (elems > vec->capacity)
    {
        vec->capacity = elems;
        vrealloc(vec, vec->capacity);
    }
}

int *data(const vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "data: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return vec->elems;
}

void vassign_single(vector *vec, size_t count, int elem)
{
    if (!vec)
    {
        fprintf(stderr, "vassign_single: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    size_t i;
    for (i = 0; i < count; ++i) {
        vec->elems[i] = elem;
    }
    vec->size = count;
}

void vassign_range(vector *vec, const vec_iterator begin, const vec_iterator end)
{
    if (!vec || !begin || !end)
    {
        fprintf(stderr, "vassign_range: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    vec->size = end - begin;
    vresize(vec,vec->size);

    size_t i = 0;
    vec_iterator b;
    for (b = begin; b < end; ++b) {
        vec->elems[i++] = *b;
    }
}

size_t vsize(const vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "vsize: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return vec->size;
}

unsigned vempty(const vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "vempty: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return (vec->size == 0 ? 1 : 0);
}

size_t capacity(const vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "capacity: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return vec->capacity;
}

void vswap(vector *vec1, vector *vec2) 
{
    if (!vec1 || !vec2) 
    {
        fprintf(stderr, "swap: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    vector temp = *vec1;
    *vec1 = *vec2;
    *vec2 = temp;
}
   
int vat(const vector *vec, size_t index)
{
    if (!vec)
    {
        fprintf(stderr, "vat: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (!(vec->elems) || index >= vec->size)
    {
        fprintf(stderr, "vat: index out of range");
        exit(EXIT_FAILURE);
    }

    return (vec->elems)[index];
}

void vset(vector *vec, size_t index, int elem)
{
    if (!vec)
    {
        fprintf(stderr, "vset: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (!(vec->elems) || index >= vec->size)
    {
        fprintf(stderr, "vset: index out of range");
        exit(EXIT_FAILURE);
    }

    vec->elems[index] = elem;
}

void vsort(vector *vec, int (*comp)(const void *, const void *))
{
    if (!vec || !comp)
    {
        fprintf(stderr, "vsort: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (vec->elems) {
        qsort(vec->elems,vec->size,sizeof(int),comp);
    }
}

vec_iterator vfind(const vector *vec, int elem)
{
    if (!vec)
    {
        fprintf(stderr, "vfind: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    vec_iterator it;
    for (it = vbegin(vec); it != vend(vec); ++it)
    {
        if (*it == elem) {
            return it;
        }
    }
    return it;
}

vec_iterator vbegin(const vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "vbegin: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return vec->elems;
}

vec_iterator vend(const vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "vend: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    return vec->elems + vec->size;
}

int vfront(const vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "vfront: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (!(vec->elems) || vec->size == 0)
    {
        fprintf(stderr, "vfront: vector is empty");
        exit(EXIT_FAILURE);
    }

    return vec->elems[0];
}

int vback(const vector *vec)
{
    if (!vec)
    {
        fprintf(stderr, "vback: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    if (!(vec->elems) || vec->size == 0)
    {
        fprintf(stderr, "vback: vector is empty");
        exit(EXIT_FAILURE);
    }

    return vec->elems[vec->size - 1];
}

static void vrealloc(vector *vec, size_t new_capacity)
{
    if (!vec)
    {
        fprintf(stderr, "vrealloc: a null pointer was received as an argument");
        exit(EXIT_FAILURE);
    }
    vec->capacity = new_capacity;
    vec->elems = (int *)realloc(vec->elems, sizeof(int) * vec->capacity);
    if (!vec->elems)
    {
        fprintf(stderr, "bad alloc");
        exit(EXIT_FAILURE);
    }
    int i;
    for (i = vec->size + 1; i < vec->capacity; ++i) {
        vec->elems[i] = 0;
    }
}
