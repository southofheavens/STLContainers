#include "include/vector.h"
#include "include/list.h"
#include "include/map.h"

int main(int argc, char *argv[])
{
    list lst;
    list_init(&lst);

    printf("%d\n",(lbegin(&lst) == lend(&lst)));

    list_destroy(&lst);

    return EXIT_SUCCESS;
}
