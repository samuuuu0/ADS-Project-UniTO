#include "../../lib/unity.h"
#include "../src/edit_distance.c"

// edit distance tests
static void edit_distance_one_delete() {
    const char *a = "casa";
    const char *b = "cassa";

    TEST_ASSERT_TRUE(edit_distance(a, b) == 1);
}

static void edit_distance_one_insertion() {
    const char *a = "casa";
    const char *b = "cas";

    TEST_ASSERT_TRUE(edit_distance(a, b) == 1);
}

static void edit_distance_one_delete_one_insertion() {
    const char *a = "casa";
    const char *b = "cara";

    TEST_ASSERT_TRUE(edit_distance(a, b) == 2);
}

static void edit_distance_two_insertion() {
    const char *a = "vinaio";
    const char *b = "vino";

    TEST_ASSERT_TRUE(edit_distance(a, b) == 2);
}

static void edit_distance_three_delete_one_insertion() {
    const char *a = "tassa";
    const char *b = "passato";

    TEST_ASSERT_TRUE(edit_distance(a, b) == 4);
}

static void edit_distance_zero() {
    const char *a = "pioppo";
    const char *b = "pioppo";

    TEST_ASSERT_TRUE(edit_distance(a, b) == 0);
}

static void edit_distance_s1() {
    const char *a = "example";
    const char *b = "";

    TEST_ASSERT_TRUE(edit_distance(a, b) == 7);
}

static void edit_distance_s2() {
    const char *a = "";
    const char *b = "example";

    TEST_ASSERT_TRUE(edit_distance(a, b) == 7);
}

// edit distance dynamic programming version tests
static void edit_distance_dyn_one_delete() {
    const char *a = "casa";
    const char *b = "cassa";

    TEST_ASSERT_TRUE(edit_distance_dyn(a, b) == 1);
}

static void edit_distance_dyn_one_insertion() {
    const char *a = "casa";
    const char *b = "cas";

    TEST_ASSERT_TRUE(edit_distance_dyn(a, b) == 1);
}

static void edit_distance_dyn_one_delete_one_insertion() {
    const char *a = "casa";
    const char *b = "cara";

    TEST_ASSERT_TRUE(edit_distance_dyn(a, b) == 2);
}

static void edit_distance_dyn_two_insertion() {
    const char *a = "vinaio";
    const char *b = "vino";

    TEST_ASSERT_TRUE(edit_distance_dyn(a, b) == 2);
}

static void edit_distance_dyn_three_delete_one_insertion() {
    const char *a = "tassa";
    const char *b = "passato";

    TEST_ASSERT_TRUE(edit_distance_dyn(a, b) == 4);
}

static void edit_distance_dyn_zero() {
    const char *a = "pioppo";
    const char *b = "pioppo";

    TEST_ASSERT_TRUE(edit_distance_dyn(a, b) == 0);
}

static void edit_distance_dyn_s1() {
    const char *a = "example";
    const char *b = "";

    TEST_ASSERT_TRUE(edit_distance_dyn(a, b) == 7);
}

static void edit_distance_dyn_s2() {
    const char *a = "";
    const char *b = "example";

    TEST_ASSERT_TRUE(edit_distance_dyn(a, b) == 7);
}

int main(int argc, char const *argv[]) {

    UNITY_BEGIN();

    RUN_TEST(edit_distance_one_delete);
    RUN_TEST(edit_distance_one_insertion);
    RUN_TEST(edit_distance_one_delete_one_insertion);
    RUN_TEST(edit_distance_two_insertion);
    RUN_TEST(edit_distance_three_delete_one_insertion);
    RUN_TEST(edit_distance_zero);
    RUN_TEST(edit_distance_s1);
    RUN_TEST(edit_distance_s2);

    RUN_TEST(edit_distance_dyn_one_delete);
    RUN_TEST(edit_distance_dyn_one_insertion);
    RUN_TEST(edit_distance_dyn_one_delete_one_insertion);
    RUN_TEST(edit_distance_dyn_two_insertion);
    RUN_TEST(edit_distance_dyn_three_delete_one_insertion);
    RUN_TEST(edit_distance_dyn_zero);
    RUN_TEST(edit_distance_dyn_s1);
    RUN_TEST(edit_distance_dyn_s2);
    
    return UNITY_END();
}