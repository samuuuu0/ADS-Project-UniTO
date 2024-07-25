#include "../include/utils.h"

static void swap(void *x, void *y, size_t size) {
    void *temp = malloc(size);

    memmove(temp, x, size);
    memmove(x, y, size);
    memmove(y, temp, size);

    free(temp);
}

/**
 * @brief Merges two sorted subarrays into a single sorted array.
 * 
 * This function merges two contiguous subarrays, left and right, back into the
 * base array. The subarrays are assumed to be sorted.
 * 
 * @param base Pointer to the base of the array to be merged.
 * @param left_size The number of elements in the left subarray.
 * @param right_size The number of elements in the right subarray.
 * @param size The size of each element in the array.
 * @param compar Pointer to the comparison function used to compare elements.
*/
static void merge(void *base, size_t left_size, size_t right_size, size_t size, int (*compar)(const void*, const void*)) {
    void *left = malloc(left_size * size);
    void *right = malloc(right_size * size);

    memcpy(left, base, left_size * size);
    memcpy(right, (int8_t *)base + left_size * size, right_size * size);

    size_t i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) {
        if (compar(left + i * size, right + j * size) <= 0) {
            memcpy((int8_t *)base + k * size, left + i * size, size);
            i++;
        } else {
            memcpy((int8_t *)base + k * size, right + j * size, size);
            j++;
        }

        k++;
    }

    while (i < left_size) {
        memcpy((int8_t *)base + k * size, left + i * size, size);
        i++;
        k++;
    }
    while (j < right_size) {
        memcpy((int8_t *)base + k * size, right + j * size, size);
        j++;
        k++;
    }

    free(left);
    free(right);
}

/**
 * @brief Partitions the array around a pivot element for quicksort.
 * 
 * This function selects a pivot element and partitions the array such that all
 * elements less than or equal to the pivot are on its left, and all elements
 * greater than the pivot are on its right.
 * 
 * @param base Pointer to the base of the array to be partitioned.
 * @param nitems The number of elements in the array.
 * @param size The size of each element in the array.
 * @param compar Pointer to the comparison function used to compare elements.
 * @return Pointer to the pivot element's final position in the array.
*/
static void *partition(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    void *pivot = (int8_t *)base + (nitems - 1) * size;
    void *index = base;

    for(size_t j = 0; j < nitems - 1; j++) {
        void *curr = (int8_t *)base + j * size;
        
        if(compar(curr, pivot) <= 0) {
            swap(index, curr, size);
            index = (int8_t *)index + size;
        }
    }

    swap(index, pivot, size);
    
    return index;
}

/**
 * @brief Sorts an array using the merge sort algorithm.
 * 
 * This function sorts the given array by recursively dividing it into two halves,
 * sorting each half, and then merging the sorted halves back together.
 * 
 * @param base Pointer to the base of the array to be sorted.
 * @param nitems The number of elements in the array.
 * @param size The size of each element in the array.
 * @param compar Pointer to the comparison function used to compare elements.
*/
void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    ARGUMENTS_ERROR(base, compar);
    
    if (nitems <= 1)
        return ;

    size_t mid = nitems / 2;

    merge_sort(base, mid, size, compar);
    merge_sort(base + mid * size, nitems - mid, size, compar);

    merge(base, mid, nitems - mid, size, compar);
}

/**
 * @brief Sorts an array using the quicksort algorithm.
 * 
 * This function sorts the given array by selecting a pivot element, partitioning the array
 * around the pivot, and recursively sorting the subarrays on either side of the pivot.
 * 
 * @param base Pointer to the base of the array to be sorted.
 * @param nitems The number of elements in the array.
 * @param size The size of each element in the array.
 * @param compar Pointer to the comparison function used to compare elements.
*/
void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    ARGUMENTS_ERROR(base, compar);

    if(nitems <= 1)
        return ;

    void *pivot = partition(base, nitems, size, compar);

    size_t index = ((int8_t *)pivot - (int8_t *)base) / size;

    quick_sort(base, index, size, compar);
    quick_sort((int8_t *)pivot + size, nitems - index - 1, size, compar);
}