#include <stdio.h>

void print_arrays(int ages[], char *names[], int count)
{
    int i = 0;
    for (i = count - 1; i >= 0; i--) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }
}

void print_with_pointer_arithmetic(int *ages, char **names, int count)
{
    int i = 0;
    for (i = count - 1; i >= 0; i--) {
        printf("%s is %d years old.\n",
                *(names + i), *(ages + i));
    }
}

void print_pointers_as_arrays(int *ages, char **names, int count)
{
    int i = 0;
    for (i = count - 1; i >= 0; i--) {
        printf("%s is %d years old again.\n", names[i], ages[i]);
    }
}

void print_weird_pointers(int *ages, char **names, int count)
{
    char **cur_name = names;
    int *cur_age = ages;
    for (cur_name = names + count - 1, cur_age = ages + count - 1;
            (cur_age - ages) >= 0; cur_name--, cur_age--) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }
}

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    print_arrays(ages, names, count);

    printf("---\n");

    // set up the pointers to the start of the arrays
    int *ages_ptr = ages;
    char **names_ptr = names;

    // second way using pointers
    print_with_pointer_arithmetic(ages_ptr, names_ptr, count);

    printf("---\n");

    // third way, pointers are just arrays
    print_pointers_as_arrays(ages_ptr, names_ptr, count);

    printf("---\n");

    // fourth way with pointers in a stupid complex way
    print_weird_pointers(ages_ptr, names_ptr, count);

    printf("---\n");

    // Print addresses rather than values
    for (i = count - 1; i >= 0; i--) {
        printf("cur_name address: %p cur_age address: %p\n", &names[i], &ages[i]);
    }

    return 0;
}
