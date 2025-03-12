#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

/*  Takes as arguments an error message and the number of pointers passed to  */
/*   the function that need to be checked for zero. If at least one pointer   */
/*        is zero, the error message passed to the function is printed        */
/*                to the error stream and the program terminates              */
void check_null_pointers(char *msg, size_t arg_count, ...);

#endif