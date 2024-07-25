#include "../include/utils.h"

/**
 * @brief Counts the number of lines in a given file.
 * 
 * This function reads through the entire file to count the number of lines.
 * It then resets the file position to the beginning.
 * 
 * @param infile The file to count lines in.
 * @return The number of lines in the file.
 */
static size_t count_lines(FILE *infile) {
    if (!infile) 
        GENERIC_ERROR("count_lines: infile not provided");
    
    size_t count = 0; 
    char buffer[BUFSIZ];

    while(fgets(buffer, sizeof(buffer), infile))
        count++;

    if (fseek(infile, 0, SEEK_SET) != 0)
        GENERIC_ERROR("fseek: Error resetting file");
    
    return count;
}

/**
 * @brief Counts the number of words in a given file.
 * 
 * This function reads through the entire file to count the number of words,
 * considering words to be separated by spaces, punctuation, and newlines.
 * It then resets the file position to the beginning.
 * 
 * @param infile The file to count words in.
 * @return The number of words in the file.
 */
static size_t count_words(FILE *infile) {
    if (!infile) 
        GENERIC_ERROR("count_words: infile not provided");
    
    size_t count = 0; 
    char buffer[BUFSIZ];

    while (fgets(buffer, sizeof(buffer), infile) != NULL) {
        char *token = strtok(buffer, " ,.!?;\n\t");

        for (; token != NULL; token = strtok(NULL, " ,.!?;\n\t"))
            count++;
    }
        
    if (fseek(infile, 0, SEEK_SET) != 0)
        GENERIC_ERROR("fseek: Error resetting file");
    
    return count;
}

/**
 * @brief Saves the words from a dictionary file into an array.
 * 
 * This function reads lines from a dictionary file and stores each line as a word
 * in a dynamically allocated array of strings.
 * 
 * @param dictionary The file to read dictionary words from.
 * @param lines The number of lines (words) in the dictionary file.
 * @return A dynamically allocated array of strings containing the dictionary words.
 */
static char **save_dictionary(FILE *dictionary, size_t lines) {
    char **dictionary_words = malloc(lines * sizeof(char *));
    if (!dictionary_words)
        GENERIC_ERROR("malloc: memory allocation failed");

    char buffer[BUFSIZ];
    for (size_t i = 0; i < lines; i++) {
        if(!fgets(buffer, sizeof(buffer), dictionary))
            GENERIC_ERROR("fgets: error reading file");
        
        buffer[strlen(buffer) - 1] = '\0';

        dictionary_words[i] = strdup(buffer);
        if (!dictionary_words[i])
            GENERIC_ERROR("strdup: memory allocation failed");
    }
    
    return dictionary_words;
}

/**
 * @brief Saves the words from a file to be corrected into an array.
 * 
 * This function reads words from a file, splits them by delimiters, converts them to lowercase,
 * and stores them in a dynamically allocated array of strings.
 * 
 * @param correctme The file to read words from.
 * @param words The number of words to be read from the file.
 * @return A dynamically allocated array of strings containing the words to be corrected.
 */
static char **save_correctme(FILE *correctme, size_t words) {
    char **correctme_words = malloc(words * sizeof(char *));
    if (!correctme_words)
        GENERIC_ERROR("malloc: memory allocation failed");

    char buffer[BUFSIZ];
    
    // word index
    size_t i = 0;

    while (fgets(buffer, sizeof(buffer), correctme) != NULL && i < words) {
        char *token = strtok(buffer, " ,.!?;:\n\t");

        for (; token != NULL && i < words; token = strtok(NULL, " ,.!?;:\n\t")) {
            correctme_words[i] = strdup(token);
            if (correctme_words[i] == NULL)
                GENERIC_ERROR("strdup: error duplicating string");

            for (size_t j = 0; correctme_words[i][j]; j++)
                correctme_words[i][j] = tolower(correctme_words[i][j]);

            i++;
        }
    }

    return correctme_words;
}

/**
 * @brief Prints corrections for words based on the dictionary.
 * 
 * This function compares each word to be corrected with the words in the dictionary using
 * the edit distance algorithm, and prints possible corrections with the minimum edit distance.
 * 
 * @param dictionary An array of dictionary words.
 * @param correctme An array of words to be corrected.
 * @param lines The number of lines (words) in the dictionary.
 * @param words The number of words to be corrected.
 */
static void print_corrections(char **dictionary, char **correctme, size_t lines, size_t words) {
    for(size_t i = 0; i < words; i++) {
        int min = INT_MAX;

        printf("[%ld] word to correct: %s\n", i + 1, correctme[i]);

        int *array = malloc(lines * sizeof(int));
        for(size_t j = 0; j < lines; j++) {
            array[j] = edit_distance_dyn(correctme[i], dictionary[j]);

            if(array[j] < min)
                min = array[j];
        }

        // if(min == 0)
            // continue;

        if(min != 0) {
            printf("minimum edit distance: %d | possible fixes:", min);

            for(size_t j = 0; j < lines; j++) {
                if(array[j] == min)
                    printf(" %s", dictionary[j]);
            }
        } else
            printf("found in dictionary");
        printf("\n\n");

        free(array);
    }
}

int main(int argc, char const *argv[]) {
    if(argc != 3)
        GENERIC_ERROR("Usage: bin/main_ex2 <dictionary_txt> <correctme_txt>");

    FILE *dictionary = fopen(argv[1], "r");
    if(!dictionary)
        GENERIC_ERROR("fopen: error opening dictionary file");
    FILE *correctme = fopen(argv[2], "r");
    if(!correctme)
        GENERIC_ERROR("fopen: error opening correctme file");

    size_t lines = count_lines(dictionary);
    char **dictionary_words = save_dictionary(dictionary, lines);

    size_t words = count_words(correctme);
    char **correctme_words = save_correctme(correctme, words);

    print_corrections(dictionary_words, correctme_words, lines, words);

    fclose(dictionary);
    fclose(correctme);
}