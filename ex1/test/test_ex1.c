#include "../../lib/unity.h"
#include "../src/sorting_algorithms.c"

// compare functions
static int compare_int(const void *a, const void *b) { 
    return (*(const int *)a - *(const int *)b); 
}

static int compare_float(const void *a, const void *b) { 
    return (*(const float *)a > *(const float *)b) - (*(const float *)a < *(const float *)b); 
}

static int compare_string(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// merge sort tests
static void merge_sort_best_case_int() {
    int input[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int expected_output[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    merge_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_output, input, sizeof(int));
}

static void merge_sort_best_case_float() {
    float input[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    float expected_output[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

    merge_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_output, input, sizeof(float));
}

static void merge_sort_best_case_string() {
    const char *input[] = {"apple", "banana", "cherry", "date", "elderberry"};
    const char *expected_output[] = {"apple", "banana", "cherry", "date", "elderberry"};

    merge_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_string);
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_output, input, sizeof(input) / sizeof(const char *));
}

static void merge_sort_medium_case_int() {
    int input[] = {5, 2, 1, 7, 6, 3, 8, 4, 0, 9};
    int expected_output[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    merge_sort(input, sizeof(input) / sizeof(input[0]), sizeof(int), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_output, input, sizeof(input) / sizeof(int));
}

static void merge_sort_medium_case_float() {
    float input[] = {0.5, 0.1, 0.3, 0.9, 0.7, 0.2, 0.4, 0.6, 0.8, 0.0};
    float expected_output[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

    merge_sort(input, sizeof(input) / sizeof(input[0]), sizeof(float), compare_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_output, input, sizeof(input) / sizeof(float));
}

static void merge_sort_medium_case_string() {
    const char *input[] = {"date", "apple", "banana", "elderberry", "cherry"};
    const char *expected_output[] = {"apple", "banana", "cherry", "date", "elderberry"};

    merge_sort(input, sizeof(input) / sizeof(input[0]), sizeof(const char *), compare_string);
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_output, input, sizeof(input) / sizeof(const char *));
}

static void merge_sort_duplicate_elements_int() {
    int input[] = {3, 2, 1, 1, 3, 2, 1, 4, 0, 1};
    int expected_output[] = {0, 1, 1, 1, 1, 2, 2, 3, 3, 4};

    merge_sort(input, sizeof(input) / sizeof(input[0]), sizeof(int), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_output, input, sizeof(input) / sizeof(int));
}

static void merge_sort_duplicate_elements_float() {
    float input[] = {0.2, 0.1, 0.0, 0.0, 0.2, 0.0, 0.2, 0.1, 0.1, 0.0};
    float expected_output[] = {0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 0.1, 0.2, 0.2, 0.2};

    merge_sort(input, sizeof(input) / sizeof(input[0]), sizeof(float), compare_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_output, input, sizeof(input) / sizeof(float));
}

static void merge_sort_duplicate_elements_string() {
    const char *input[] = {"banana", "apple", "banana", "apple", "cherry"};
    const char *expected_output[] = {"apple", "apple", "banana", "banana", "cherry"};

    merge_sort(input, sizeof(input) / sizeof(input[0]), sizeof(const char *), compare_string);
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_output, input, sizeof(input) / sizeof(const char *));
}

// merge tests
static void test_merge_int() {
    int input[] = {3, 1, 5, 4, 2, 6};
    int expected_output[] = {3, 1, 4, 2, 5, 6};

    merge(input, 3, 3, sizeof(int), compare_int);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected_output, input, sizeof(input) / sizeof(int));
}

static void test_merge_float() {
    float input[] = {0.3, 0.1, 0.5, 0.4, 0.2, 0.6};
    float expected_output[] = {0.3, 0.1, 0.4, 0.2, 0.5, 0.6};

    merge(input, 3, 3, sizeof(float), compare_float);

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_output, input, sizeof(input) / sizeof(float));
}

static void test_merge_string() {
    const char *input[] = {"apple", "fig", "banana", "cherry", "elderberry", "date"};
    const char *expected_output[] = {"apple", "cherry", "elderberry", "date", "fig", "banana"};

    merge(input, 3, 3, sizeof(const char *), compare_string);

    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_output, input, sizeof(input) / sizeof(const char *));
}

// swap tests
static void test_swap_int() {
    int a = 1;
    int b = 2;

    swap(&a, &b, sizeof(int));

    TEST_ASSERT_EQUAL_INT(2, a);
    TEST_ASSERT_EQUAL_INT(1, b);
}

static void test_swap_float() {
    float a = 1.1;
    float b = 2.2;

    swap(&a, &b, sizeof(float));

    TEST_ASSERT_EQUAL_FLOAT(2.2, a);
    TEST_ASSERT_EQUAL_FLOAT(1.1, b);
}

static void test_swap_string() {
    const char *a = "Hello";
    const char *b = "World";

    swap(&a, &b, sizeof(const char *));

    TEST_ASSERT_EQUAL_STRING("World", a);
    TEST_ASSERT_EQUAL_STRING("Hello", b);
}

// partition tests
static void test_partition_int() {
    int array[] = {3, 1, 4, 5, 2};
    size_t nitems = sizeof(array) / sizeof(array[0]);

    void *pivot = partition(array, nitems, sizeof(int), compare_int);

    size_t pivot_index = ((int8_t *)pivot - (int8_t *)array) / sizeof(int);
    TEST_ASSERT_EQUAL_INT(1, pivot_index);

    for (size_t i = 0; i < pivot_index; i++) {
        TEST_ASSERT_TRUE(compare_int(&array[i], pivot) <= 0);
    }

    for (size_t i = pivot_index + 1; i < nitems; i++) {
        TEST_ASSERT_TRUE(compare_int(&array[i], pivot) > 0);
    }
}

static void test_partition_float() {
    float array[] = {0.3, 0.1, 0.4, 0.5, 0.2};
    size_t nitems = sizeof(array) / sizeof(array[0]);

    void *pivot = partition(array, nitems, sizeof(float), compare_float);

    size_t pivot_index = ((int8_t *)pivot - (int8_t *)array) / sizeof(float);
    TEST_ASSERT_EQUAL_INT(1, pivot_index);

    for (size_t i = 0; i < pivot_index; i++) {
        TEST_ASSERT_TRUE(compare_float(&array[i], pivot) <= 0);
    }

    for (size_t i = pivot_index + 1; i < 5; i++) {
        TEST_ASSERT_TRUE(compare_float(&array[i], pivot) > 0);
    }
}

static void test_partition_string() {
    const char *array[] = {"cherry", "banana", "elderberry", "apple", "date"};
    size_t nitems = sizeof(array) / sizeof(array[0]);

    void *pivot = partition(array, nitems, sizeof(const char *), compare_string);

    size_t pivot_index = ((int8_t *)pivot - (int8_t *)array) / sizeof(const char *);
    TEST_ASSERT_EQUAL_INT(3, pivot_index);

    for (size_t i = 0; i < pivot_index; i++) {
        TEST_ASSERT_TRUE(compare_string(&array[i], pivot) <= 0);
    }

    for (size_t i = pivot_index + 1; i < nitems; i++) {
        TEST_ASSERT_TRUE(compare_string(&array[i], pivot) > 0);
    }
}

// quick sort tests
static void quick_sort_worst_case_int() {
    int input[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int expected_output[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    quick_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_int);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_output, input, sizeof(int));
}

static void quick_sort_worst_case_float() {
    float input[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    float expected_output[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

    quick_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_float);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_output, input, sizeof(float));
}

static void quick_sort_worst_case_string() {
    const char *input[] = {"apple", "banana", "cherry", "date", "elderberry"};
    const char *expected_output[] = {"apple", "banana", "cherry", "date", "elderberry"};

    quick_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_string);
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_output, input, sizeof(input) / sizeof(const char *));
}

static void quick_sort_medium_case_int() {
    int input[] = {5, 3, 1, 7, 4, 2, 6, 9, 8, 0};
    int expected_output[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    quick_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_int);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected_output, input, sizeof(input) / sizeof(int));
}

static void quick_sort_medium_case_float() {
    float input[] = {0.7, 0.2, 0.4, 0.8, 0.1, 0.6, 0.3, 0.5, 0.9, 0.0};
    float expected_output[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

    quick_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_float);

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_output, input, sizeof(input) / sizeof(float));
}

static void quick_sort_medium_case_string() {
    const char *input[] = {"date", "banana", "cherry", "elderberry", "apple"};
    const char *expected_output[] = {"apple", "banana", "cherry", "date", "elderberry"};

    quick_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_string);

    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_output, input, sizeof(input) / sizeof(const char *));
}

static void quick_sort_duplicate_elements_int() {
    int input[] = {3, 2, 1, 1, 3, 2, 1, 4, 0, 1};
    int expected_output[] = {0, 1, 1, 1, 1, 2, 2, 3, 3, 4};

    quick_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_int);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected_output, input, sizeof(input) / sizeof(int));
}

static void quick_sort_duplicate_elements_float() {
    float input[] = {0.2, 0.1, 0.0, 0.0, 0.2, 0.0, 0.2, 0.1, 0.1, 0.0};
    float expected_output[] = {0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 0.1, 0.2, 0.2, 0.2};

    quick_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_float);

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_output, input, sizeof(input) / sizeof(float));
}

static void quick_sort_duplicate_elements_string() {
    const char *input[] = {"banana", "apple", "banana", "apple", "cherry"};
    const char *expected_output[] = {"apple", "apple", "banana", "banana", "cherry"};

    quick_sort(input, sizeof(input) / sizeof(input[0]), sizeof(input[0]), compare_string);

    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_output, input, sizeof(input) / sizeof(const char *));
}

int main(int argc, char *argv[]) {
    
    UNITY_BEGIN();

    RUN_TEST(test_merge_int);
    RUN_TEST(test_merge_float);
    RUN_TEST(test_merge_string);
    
    RUN_TEST(merge_sort_best_case_int);
    RUN_TEST(merge_sort_best_case_float);
    RUN_TEST(merge_sort_best_case_string);
    
    RUN_TEST(merge_sort_medium_case_int);
    RUN_TEST(merge_sort_medium_case_float);
    RUN_TEST(merge_sort_medium_case_string);

    RUN_TEST(merge_sort_duplicate_elements_int);
    RUN_TEST(merge_sort_duplicate_elements_float);
    RUN_TEST(merge_sort_duplicate_elements_string);

    RUN_TEST(test_swap_int);
    RUN_TEST(test_swap_float);
    RUN_TEST(test_swap_string);

    RUN_TEST(test_partition_int);
    RUN_TEST(test_partition_float);
    RUN_TEST(test_partition_string);

    RUN_TEST(quick_sort_worst_case_int);
    RUN_TEST(quick_sort_worst_case_float);
    RUN_TEST(quick_sort_worst_case_string);

    RUN_TEST(quick_sort_medium_case_int);
    RUN_TEST(quick_sort_medium_case_float);
    RUN_TEST(quick_sort_medium_case_string);

    RUN_TEST(quick_sort_duplicate_elements_int);
    RUN_TEST(quick_sort_duplicate_elements_float);
    RUN_TEST(quick_sort_duplicate_elements_string);

    return UNITY_END();
}