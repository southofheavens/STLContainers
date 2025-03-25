#include "../include/vector.h"
#include <assert.h>
#include <math.h>

#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"

/* --------------------------------------------------------------------------- */

/* comparator for sorting (ascending) */
int comp_asc(const void *f, const void *s)
{
    return (*(int *)f - *(int *)s);
}

/* comparator for sorting (descending) */
int comp_desc(const void *f, const void *s)
{
    return (*(int *)s - *(int *)f);
}

/* --------------------------------------------------------------------------- */

int main(void)
{
    printf(GREEN "RUNNING VECTOR TESTS" RED "\n");

    /* --------------------------------------------- */

    vector *vec = (vector *)malloc(sizeof(vector));
    vector_init(vec);

    vpush_back(vec,3);
    vpush_back(vec,7);
    vpush_back(vec,9);

    assert(vat(vec,0) == 3);
    assert(vat(vec,1) == 7);
    assert(vat(vec,2) == 9);

    vec_iterator it;

    it = vbegin(vec);
    vinsert(vec, it, 1);

    it = vend(vec);
    vinsert(vec, it, 11);

    it = vfind(vec,7);
    if (it != vend(vec)) 
    /* it == vend(vec) means that the element was not found */
    {  
        vinsert(vec, it, 5);
    }

    assert(vfront(vec) == 1);
    assert(vat(vec,1) == 3);
    assert(vat(vec,2) == 5);
    assert(vat(vec,3) == 7);
    assert(vat(vec,4) == 9);
    assert(vback(vec) == 11);
    assert(vsize(vec) == 6);

    it = vfind(vec,3);
    if (it != vend(vec)) 
    /* it == vend(vec) means that the element was not found */
    {
        verase(vec,it);
    }

    it = vbegin(vec);
    verase(vec,it);

    vpop_back(vec);

    assert(vat(vec,0) == 5);
    assert(vat(vec,1) == 7);
    assert(vat(vec,2) == 9);
    assert(vsize(vec) == 3);

    vclear(vec);

    assert(vempty(vec));

    vector_destroy(vec);
    free(vec);

    /* --------------------------------------------- */

    vector *vec1 = (vector *)malloc(sizeof(vector));
    vector_init(vec1);
    vector *vec2 = (vector *)malloc(sizeof(vector));
    vector_init(vec2);

    reserve(vec1,10); 
    
    assert(capacity(vec1) == 10);

    vpush_back(vec1,3);   /* 0 */
    vpush_back(vec1,-4);  /* 1 */
    vpush_back(vec1,13);  /* 2 */
    vpush_back(vec1,41);  /* 3 */
    vpush_back(vec1,-9);  /* 4 */
    vpush_back(vec1,121); /* 5 */
    vpush_back(vec1,55);  /* 6 */
    vpush_back(vec1,-14); /* 7 */
    vpush_back(vec1,96);  /* 8 */
    vpush_back(vec1,0);   /* 9 */

    assert(capacity(vec1) == 10);

    vresize(vec2,5);

    vswap(vec1,vec2);

    assert(vsize(vec1) == 5);
    assert(vsize(vec2) == 10);

    vsort(vec2, comp_asc);

    size_t i;
    for (i = 0; i < vsize(vec2) - 1; ++i) {
        assert(vat(vec2,i) <= vat(vec2,i+1));
    }

    vsort(vec2, comp_desc);

    for (i = 0; i < vsize(vec2) - 1; ++i) {
        assert(vat(vec2,i) >= vat(vec2,i+1));
    }

    vector_destroy(vec2);
    free(vec2);
    vector_destroy(vec1);
    free(vec1);

    /* --------------------------------------------- */

    vector *vec3 = (vector *)malloc(sizeof(vector));
    vector_init(vec3);
    vector *vec4 = (vector *)malloc(sizeof(vector));
    vector_init(vec4);

    vassign_single(vec3,5,15);

    assert(vsize(vec3) == 5);
    
    for (i = 0; i < vsize(vec3); ++i) {
        assert(vat(vec3,i) == 15);
    }

    vresize(vec4,15);

    assert(vsize(vec4) == 15);

    for (i = 0; i < vsize(vec4); ++i) {
        assert(vat(vec4,i) == 0);
    }

    vassign_range(vec4,vbegin(vec3),vend(vec3));

    assert(vsize(vec4) == 5);
    
    for (i = 0; i < vsize(vec4); ++i) {
        assert(vat(vec4,i) == 15);
    }

    vassign_single(vec4,7,-5);

    assert(vsize(vec4) == 7);

    for (i = 0; i < vsize(vec4); ++i) {
        assert(vat(vec4,i) == -5);
    }

    vector_destroy(vec4);
    free(vec4);
    vector_destroy(vec3);
    free(vec3);

    /* --------------------------------------------- */

    vector *vec5 = (vector *)malloc(sizeof(vector));
    vector_init(vec5);

    for (i = 0; i < 15; ++i) {
        vpush_back(vec5,i);
    }

    vresize(vec5, 10);
    vresize(vec5, 15);

    for (i = 10; i < 15; ++i) {
        assert(vat(vec5,i) == 0);
    }

    vector_destroy(vec5);
    free(vec5);

    /* --------------------------------------------- */

    vector *vec6 = (vector *)malloc(sizeof(vector));
    vector_init(vec6);

    reserve(vec6,50);

    for (i = 0; i < 50; ++i) {
        vpush_back(vec6, pow(i,2));
    }

    /* vec_iterator */ it = vbegin(vec6);

    /* 0 1 4 9 16 25 36 49 64 81 100 ... */
    vadvance(&it,6);

    assert(vderef(it) == 36);

    vadvance(&it,-3);

    assert(vderef(it) == 9);

    i = 0;
    for (it = vbegin(vec6); it != vend(vec6); vadvance(&it,1)) {
        assert(vderef(it) == pow(i++,2));
    }

    vector_destroy(vec6);
    free(vec6);

    /* --------------------------------------------- */

    vector *vec7 = (vector *)malloc(sizeof(vector));
    vector_init(vec7);

    const size_t vec7_size = 15;
    vresize(vec7,vec7_size);

    for (i = 0; i < vec7_size; ++i) {
        vset(vec7, i, i);
    }

    int *vec_data = data(vec7);

    for (i = 0; i < vec7_size; ++i) {
        assert(vec_data[i] == i);
    }

    i = 0;
    for (it = vbegin(vec7); it != vend(vec7); vadvance(&it,1)) {
        vset_it(it,pow(i++,2));
    }

    i = 0;
    for (it = vbegin(vec7); it != vend(vec7); vadvance(&it,1)) {
        assert(vderef(it) == pow(i++,2));
    }

    vector_destroy(vec7);
    free(vec7);

    /* --------------------------------------------- */

    printf(GREEN "ALL TESTS WITH VECTOR PASSED SUCCESSFULLY" RED "\n");

    return EXIT_SUCCESS;
}
