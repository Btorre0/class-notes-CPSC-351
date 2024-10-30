#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void add_char_to_string(char *word, char c) {
    int len = strlen(word);  // because the string is null-terminated
    word[len] = c;
    word[len + 1] = '\0';
}

void break_into_words(char *input, char *words[], char break_on) {
    char *current_word = input;
    int word_count = 0;  // index into words array

    char word_so_far[1000];
    strcpy(word_so_far, "");

    while (*current_word != '\0') {
        if (*current_word == ' ') {
            words[word_count++] = strdup(word_so_far);
            word_so_far[0] = '\0';
        } else {
            add_char_to_string(word_so_far, *current_word);
        }
        current_word++;
    }
    words[word_count++] = strdup(word_so_far);

    words[word_count] = NULL;
}

// true id path is found, false otherwise
// if found, the path is copied to absalute_path
bool find_abselute_path(char *str, char *absalute_path, char *with_path) {
    char *directories[1000];
    break_into_words(getenv("PATH"), directories, ':');

    for (int ix = 0; ix < 1000 && directories[ix] != NULL; ix++) {
        if (directories[ix] == NULL) {
            break;
        }
        // char path[1000];
        strcpy(with_path, directories[ix]);
        strcat(with_path, "/");
        strcat(with_path, str);

        if (access(with_path, X_OK) == 0) {
            strcpy(absalute_path, with_path);
            return true;
        }
    }
    return false;
}

// takes one argument: splits the string to words
// and finds the first word in the abeslute PATH  variable
// and prints them out
int main(int argc, char *argv[]) {
    char *words[100];
    char absalute_path[1000];

    // printf("%s\n", argv[1]);

    break_into_words(argv[1], words, ' ');
    char with_path[1000];
    find_abselute_path(words[0], absalute_path, with_path);

    if (find_abselute_path(words[0], absalute_path, with_path) == false) {
        printf("Command not found\n");
        return 1;
    }

    // "wc -l" -> ["/usr/bin/wc", "-l", NULL]
    // ["wc", "-l"]

    printf(">%s<\n", argv[1]);
    printf("abs path >%s<\n", absalute_path);
    printf(">%s<\n", absalute_path);

    for (int ix = 0; ix < 100; ix++) {
        if (words[ix] == NULL) {
            break;
        }
        printf(">%s<\n", words[ix]);
    }

    execve(argv[1], argv + 1, NULL);
    printf("execve failed\n");
    return 0;
    // memory allocator - big chunk is heaping
    // command shell - big chunk is allocating
}