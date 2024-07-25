#include "../include/utils.h"

static int compare_field_int(const void *a, const void *b) {
    ARGUMENTS_ERROR(a, b);

    Record *x = (Record *)a;
    Record *y = (Record *)b;

    return x->field_int - y->field_int;
}

static int compare_field_str(const void *a, const void *b) {
    ARGUMENTS_ERROR(a, b);

    Record *x = (Record *)a;
    Record *y = (Record *)b;

    return strcmp(x->field_str, y->field_str);
}

static int compare_field_float(const void *a, const void *b) {
    ARGUMENTS_ERROR(a, b);

    Record *x = (Record *)a;
    Record *y = (Record *)b;

    return (x->field_fp > y->field_fp) - (x->field_fp < y->field_fp);
}

/**
 * @brief Counts the number of lines in a given file.
 * 
 * This function reads the given file line by line and counts the total number of lines.
 * It then resets the file position to the beginning of the file.
 * 
 * @param infile Pointer to the file to be read.
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
 * @brief Loads records from a given file.
 * 
 * This function reads the specified number of lines from the file and parses each line
 * into a Record structure. The records are stored in an array which is returned.
 * 
 * @param infile Pointer to the file to be read.
 * @param lines The number of lines to read from the file.
 * @return Pointer to an array of records.
 */
static Record *load_records(FILE *infile, size_t lines) {
    if (!infile) 
        GENERIC_ERROR("load_records: file not provided");
    
    Record *records = malloc(lines * sizeof(Record));
    if (!records) 
        GENERIC_ERROR("malloc: memory allocation failed");
    
    char buffer[BUFSIZ];
    for(size_t i = 0; fgets(buffer, sizeof(buffer), infile) && i < lines; i++) {
        Record temp_record = {
            atoi(strtok(buffer, ",")),
            strdup(strtok(NULL, ",")),
            atoi(strtok(NULL, ",")),
            atof(strtok(NULL, ","))
        };
        records[i] = temp_record; 
    }

    return records;
}

/**
 * @brief Saves records to a given file.
 * 
 * This function writes the specified number of records to the given file. Each record is written
 * in a comma-separated format.
 * 
 * @param outfile Pointer to the file to be written to.
 * @param saved_records Pointer to the array of records to be saved.
 * @param lines The number of records to write.
 */
static void save_records(FILE *outfile, Record *saved_records, size_t lines) {
    if (!outfile) 
        GENERIC_ERROR("save_records: outfile file not provided");

    for (size_t i = 0; i < lines; i++) {
        if (fprintf(outfile, "%d,%s,%d,%f\n",
                    saved_records[i].id,
                    saved_records[i].field_str,
                    saved_records[i].field_int,
                    saved_records[i].field_fp) < 0) {
            GENERIC_ERROR("fprintf: error writing to output file");
        }
    }
}

/**
 * @brief Sorts records from an input file and saves the sorted results to an output file.
 * 
 * This function reads records from the input file, sorts them based on the specified field
 * and sorting algorithm, and then saves the sorted records to the output file.
 * 
 * @param infile Pointer to the input file containing records to be sorted.
 * @param outfile Pointer to the output file where sorted records will be saved.
 * @param field The field number to sort by (1: string, 2: integer, 3: float).
 * @param algo The sorting algorithm to use (1: merge sort, 2: quicksort).
 */
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo) {
    if (!infile || !outfile) 
        GENERIC_ERROR("sort_records: file not provided");

    size_t lines = count_lines(infile);

    Record *records = load_records(infile, lines);
    
    int (*compar)(const void *, const void *);
    switch (field) {
        case 1:
            compar = compare_field_str;
            break;
        case 2:
            compar = compare_field_int;
            break;
        case 3:
            compar = compare_field_float;
            break;
        default:
            GENERIC_ERROR("Error: invalid field number");
    }

    switch (algo) {
        case 1:
            merge_sort(records, lines, sizeof(Record), compar);
            break;
        case 2:
            quick_sort(records, lines, sizeof(Record), compar);
            break;
        default:
            GENERIC_ERROR("Error: invalid algorithm id");
    }

    save_records(outfile, records, lines);
}

int main(int argc, char *argv[]) {
    if(argc != 5) 
        GENERIC_ERROR("Usage: bin/main_ex1 <input_csv> <output_csv> <field> <algo>");

    FILE *infile = fopen(argv[1], "r");
    if(!infile)
        GENERIC_ERROR("fopen: error opening input file");
    FILE *outfile = fopen(argv[2], "w+");
    if(!outfile)
        GENERIC_ERROR("fopen: error opening output file");

    size_t field = (size_t)atoi(argv[3]);
    size_t algo = (size_t)atoi(argv[4]);
    
    sort_records(infile, outfile, field, algo);


    fclose(infile);
    fclose(outfile);
}