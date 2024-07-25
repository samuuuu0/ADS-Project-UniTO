#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int id;
    char *field_str;
    int field_int;
    // float field_fp;
    double field_fp;
} Record;

#define ARGUMENTS_ERROR(a, b)                                                \
    do {                                                                     \
        if ((a) == NULL || (b) == NULL) {                                    \
            fprintf(stderr, "%s:%d: NULL arguments.\n", __FILE__, __LINE__); \
            exit(EXIT_FAILURE);                                              \
        }                                                                    \
    } while (0)

#define GENERIC_ERROR(message)                                        \
    do {                                                              \
        fprintf(stderr, "%s:%d: %s.\n", __FILE__, __LINE__, message); \
        exit(EXIT_FAILURE);                                           \
    } while(0)

extern void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
extern void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));