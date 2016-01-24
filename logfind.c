#include "dbg.h"
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LOGFIND_ENTRIES 100
#define MAX_PATTERNS 100
#define MAX_BUFFER_SIZE 1024

int get_globs(char *globs[])
{
    FILE *file = NULL;
    char *buff = NULL;
    size_t len = 0;
    int globs_size = 0;
    file = fopen("/home/jackie/.logfind", "r");
    check(file, "File not opened");
    while (getline(&buff, &len, file) != -1) {
        strtok(buff, "\n");
        globs[globs_size] = buff;
        globs_size += 1;
        buff = NULL;
    }
    free(buff);
    return globs_size;
error:
    log_err("Could not load allowed files from ~/.logfind");
    if(buff) {
        free(buff);
    }
    return 0;
}

int get_patterns(int argc, char *argv[], char *patterns[])
{
    int size = 0;
    for(int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-o", MAX_BUFFER_SIZE) != 0) {
            patterns[size] = argv[i];
            size++;
        }
    }
    return size;
}

int should_use_or(int argc, char *argv[])
{
    for(int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-o", MAX_BUFFER_SIZE) == 0) {
            return 1;
        }
    }
    return 0;
}

int does_line_match_patterns(char *str, int patterns_size, char *patterns[], int use_or) {
    if (use_or) {
        for(int i = 0; i < patterns_size; i++) {
            if (strstr(str, patterns[i]) != NULL) {
                return 1;
            }
        }
        return 0;
    } else {
        for(int i = 0; i < patterns_size; i++) {
            if (strstr(str, patterns[i]) == NULL) {
                return 0;
            }
        }
        return 1;
    }
}

void find_matches(int globs_size, char *globs[], int patterns_size, char *patterns[], int use_or)
{
    glob_t curr_glob;
    int ret;
    int append = 0;
    char *pattern = NULL;
    char *buff = NULL;
    FILE *file = NULL;
    size_t len = 0;
    int line = 0;
    for (int i = 0; i < globs_size; i++) {
        ret = glob(globs[i], append, NULL, &curr_glob);
        check(ret == 0, "Error in retrieving glob %s", globs[i]);
        append = GLOB_APPEND;
    }
    for (int i = 0; i < curr_glob.gl_pathc; i++) {
        file = fopen(curr_glob.gl_pathv[i], "r");
        check(file, "File not opened");
        line = 0;
        while (getline(&buff, &len, file) != -1) {
            line++;
            if (does_line_match_patterns(buff, patterns_size, patterns, use_or)) {
                printf("%s:%d %s", curr_glob.gl_pathv[i], line, buff);
            }
        }
        fclose(file);
    }
error:
    globfree(&curr_glob);
    if (pattern) free(pattern);
    if (buff) free(buff);
    return;
}

int main(int argc, char *argv[])
{
    char **globs = NULL;
    char **patterns = NULL;
    int use_or = 0;
    int globs_size = 0;
    int patterns_size = 0;

    patterns = calloc(MAX_PATTERNS, sizeof(char*));
    patterns_size = get_patterns(argc, argv, patterns);
    use_or = should_use_or(argc, argv);
    globs = calloc(MAX_LOGFIND_ENTRIES, sizeof(char*));
    check_mem(globs);
    globs_size = get_globs(globs);
    for (int i = 0; i < patterns_size; i++) {
    }
    find_matches(globs_size, globs, patterns_size, patterns, use_or);
    for (int i = 0; i < globs_size; i++) {
        free(globs[i]);
    }
    free(patterns);
    free(globs);
    return 0;
error:
    if(globs) {
        free(globs);
    }
    if(patterns) {
        free(patterns);
    }
    return -1;
}

