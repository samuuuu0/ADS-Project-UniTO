#include "../include/utils.h"

static const char *rest(const char *s) {
    return (s[0] == '\0') ? s : s + 1;
}

static int min(int a, int b) {
    return a < b ? a : b;
}

/**
 * @brief Computes the edit distance between two strings using a recursive approach.
 * 
 * Base Case: |s1| = 0, then edit_distance(s1,s2) = |s2|
 *            |s2| = 0, then edit_distance(s1,s2) = |s1|
 * The edit distance is the minimum number of operations (insertions, deletions, or substitutions)
 * required to transform one string into another.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The edit distance between the two strings.
 */
int edit_distance(const char *s1, const char* s2) {
    if(*s1 == '\0' || *s2 == '\0')
        return strlen(*s1 == '\0' ? s2 : s1);

    // no edit needed
    if(s1[0] == s2[0])
        return edit_distance(rest(s1), rest(s2));
    
    int d_canc = 1 + edit_distance(s1, rest(s2));
    int d_ins = 1 + edit_distance(rest(s1), s2);

    return min(d_canc, d_ins);
}

/**
 * @brief Helper function for computing the edit distance using dynamic programming.
 * 
 * Base Case: |s1| = 0, then edit_distance_dyn(s1,s2) = |s2|
 *            |s2| = 0, then edit_distance_dyn(s1,s2) = |s1|
 * This function uses memoization to store intermediate results and avoid redundant calculations.
 * It is called by the edit_distance_dyn function.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @param len_s1 The length of the first string.
 * @param len_s2 The length of the second string.
 * @param memo The memoization matrix.
 * @return The edit distance between the two strings.
 */
static int edit_distance_dyn_helper(const char *s1, const char *s2, int len_s1, int len_s2, int **memo) {
    if(len_s1 == 0 || len_s2 == 0)
        return len_s1 + len_s2;

    if(memo[len_s1][len_s2] != -1)
        return memo[len_s1][len_s2];

    // no edit needed
    if (s1[0] == s2[0])
        return memo[len_s1][len_s2] = edit_distance_dyn_helper(rest(s1), rest(s2), len_s1 - 1, len_s2 - 1, memo);

    int d_canc = 1 + edit_distance_dyn_helper(s1, rest(s2), len_s1, len_s2 - 1, memo);
    int d_ins = 1 + edit_distance_dyn_helper(rest(s1), s2,len_s1 - 1, len_s2,  memo);

    return memo[len_s1][len_s2] = min(d_canc, d_ins);
}

/**
 * @brief Computes the edit distance between two strings using dynamic programming.
 * 
 * This function initializes the memoization matrix and calls the helper function
 * to compute the edit distance. It then frees the allocated memory.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The edit distance between the two strings.
 */
int edit_distance_dyn(const char *s1, const char* s2) {    
    int len_s1 = strlen(s1);
    int len_s2 = strlen(s2);

    int **memo = (int **)malloc((len_s1 + 1) * sizeof(int *));
    for (int i = 0; i <= len_s1; i++) {
        memo[i] = (int *)malloc((len_s2 + 1) * sizeof(int));
        memset(memo[i], -1, (len_s2 + 1) * sizeof(int));
    }

    int result = edit_distance_dyn_helper(s1, s2, len_s1, len_s2, memo);

    for (int i = 0; i <= len_s1; i++)
        free(memo[i]);
    free(memo);

    return result;
}

// edit distance dynamic programming version (bottom-up)
/* int edit_distance_dyn(const char *s1, const char *s2) {
    int len_s1 = strlen(s1);
    int len_s2 = strlen(s2);

    // Base Case: |s1| = 0, than edit_distance(s1,s2) = |s2|
    //            |s2| = 0, than edit_distance(s1,s2) = |s1|
    if(len_s1 == 0 || len_s2 == 0)
        return len_s1 + len_s2;

    // allocate memory for memoization matrix
    int **memo = (int **)malloc((len_s1 + 1) * sizeof(int *));
    for (int i = 0; i <= len_s1; i++)
        memo[i] = (int *)malloc((len_s2 + 1) * sizeof(int));

    // memo initialization
    for (int i = 0; i <= len_s1; i++) {
        for (int j = 0; j <= len_s2; j++) {
            if (i == 0)
                memo[i][j] = j;
            else if (j == 0)
                memo[i][j] = i;
            // no edit needed
            else if (s1[i - 1] == s2[j - 1])
                memo[i][j] = memo[i - 1][j - 1];
            // characters do not matches
            else
                memo[i][j] = 1 + min(memo[i][j - 1], memo[i - 1][j]);
        }
    }

    // save the result
    int result = memo[len_s1][len_s2];

    // free allocated memory
    for (int i = 0; i <= len_s1; i++)
        free(memo[i]);
    free(memo);

    return result;

    // return the edit distance between s1 and s2
    return memo[len_s1][len_s2];
} */