#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char* readline(void);
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);
void miniMaxSum(int arr_count, int* arr) {
    long long total_sum = 0;
    for (int i = 0; i < arr_count; i++) {
        total_sum += arr[i];
    }

     long long smallest_sum = total_sum - arr[0];
    long long largest_sum  = total_sum - arr[0];

    for (int i = 1; i < arr_count; i++) {
        long long current_sum = total_sum - arr[i];
        if (current_sum < smallest_sum) smallest_sum = current_sum;
        if (current_sum > largest_sum)  largest_sum = current_sum;
    }


    printf("%lld %lld\n", smallest_sum, largest_sum);
}
int main(void) {
    char** arr_strs = split_string(rtrim(readline()));
    int* arr = malloc(5 * sizeof(int));

    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        arr[i] = parse_int(arr_strs[i]);
    }
    miniMaxSum(5, arr);
    free(arr);
    free(arr_strs);
    return 0;
}
char* readline(void) {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    if (!data) return NULL;

    while (1) {
        char* cursor = data + data_length;
        if (!fgets(cursor, alloc_length - data_length, stdin)) break;

        data_length += strlen(cursor);
        if (data[data_length - 1] == '\n') {
            data[data_length - 1] = '\0';
            break;
        }

        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) return NULL;
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) return NULL;
    while (*str && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return NULL;
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    int spaces = 0;
    char* token = strtok(str, " ");

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) return NULL;
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') exit(EXIT_FAILURE);
    return value;
}
