#include "include/vector.h"
#include "include/list.h"
#include "include/map.h"

int main(int argc, char *argv[])
{
    map *my_map = (map *)malloc(sizeof(map));
    map_init(my_map);

    minsert(my_map, (pair){-4, 3});
    minsert(my_map, (pair){15, 20});
    minsert(my_map, (pair){0, 7});
    minsert(my_map, (pair){100, -5});
    minsert(my_map, (pair){16, 24});
    minsert(my_map, (pair){-4000, 31});
    minsert(my_map, (pair){-980, 1});
    minsert(my_map, (pair){-2147000, 2147000});
    minsert(my_map, (pair){-1, -1});

    map_iterator it;
    for (it = mbegin(my_map); it != mend(my_map); madvance(&it,1)) {
        printf("%d - %d\n", mderef_key(it), mderef_val(it));
    }

    map_destroy(my_map);
    free(my_map);
    return EXIT_SUCCESS;
}
