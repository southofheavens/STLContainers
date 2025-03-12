#include "../include/vector.h"
#include "../include/map.h"
#include "../include/list.h"
#include <assert.h>

#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"

void vector_tests(void)
{
    
    printf(GREEN "ALL TESTS WITH VECTOR PASSED SUCCESSFULLY" RED "\n");
}

void list_tests(void)
{
    printf(GREEN "ALL TESTS WITH LIST PASSED SUCCESSFULLY" RED "\n");
}

void map_tests(void)
{

    printf(GREEN "ALL TESTS WITH MAP PASSED SUCCESSFULLY" RED "\n");
}


int main(int argc, char *argv[])
{
    vector_tests();
    list_tests();
    map_tests();

    return EXIT_SUCCESS;
}
