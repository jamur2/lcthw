#include <ctype.h>
#include <stdio.h>
#include <string.h>

// forward declarations
void print_letters(char arg[], int size);
void print_digits(char arg[], int size);

void print_arguments(int argc, char *argv[])
{
    int i = 0;

    for (i = 0; i < argc; i++) {
        print_letters(argv[i], strlen(argv[i]));
        print_digits(argv[i], strlen(argv[i]));
    }
}

void print_letters(char arg[], int size)
{
    int i = 0;

    for (i = 0; i < size; i++) {
        char ch = arg[i];

        if (isalpha(ch) || isblank(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

void print_digits(char arg[], int size)
{
    int i = 0;

    for (i = 0; i < size; i++) {
        char ch = arg[i];

        if (isdigit(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
