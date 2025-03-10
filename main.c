#include "include/vector.h"
#include "include/list.h"
#include "include/map.h"

int main(int argc, char *argv[])
{
    map *my_map = (map *)malloc(sizeof(map));
    map_init(my_map);

    printf("%d\n", (mbegin(my_map) == mend(my_map)));
    minsert(my_map, (pair){1,2});
    minsert(my_map, (pair){2,3});
    minsert(my_map, (pair){3,4});
    printf("%d\n", (mbegin(my_map) == mend(my_map)));
    merase(my_map, mfind(my_map,1));
    merase(my_map, mfind(my_map,2));
    merase(my_map, mfind(my_map,3));
    printf("%d\n", (mbegin(my_map) == mend(my_map)));

    map_destroy(my_map);
    free(my_map);
    return EXIT_SUCCESS;
}
