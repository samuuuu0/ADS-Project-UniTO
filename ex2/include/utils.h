#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define GENERIC_ERROR(message)                                        \
    do {                                                              \
        fprintf(stderr, "%s:%d: %s.\n", __FILE__, __LINE__, message); \
        exit(EXIT_FAILURE);                                           \
    } while(0)

extern int edit_distance(const char *s1, const char* s2);
extern int edit_distance_dyn(const char *s1, const char* s2);