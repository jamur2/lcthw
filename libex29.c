#include <stdio.h>
#include <ctype.h>
#include "dbg.h"

int print_a_message(const char *msg, int len)
{
    printf("A STRING: %s\n", msg);

    return 0;
}

int uppercase(const char *msg, int len)
{
    int i = 0;

    for(i = 0; i < len && msg[i] != '\0'; i++) {
        printf("%c", toupper(msg[i]));
    }

    printf("\n");
    return 0;
}

int lowercase(const char *msg, int len)
{
    int i = 0;

    for(i = 0; i < len && msg[i] != '\0'; i++) {
        printf("%c", tolower(msg[i]));
    }

    printf("\n");

    return 0;
}

int fail_on_purpose(const char *msg, int len)
{
    return 1;
}
