#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA 100

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int main(int argc, char *argv[])
{
    Person you = {.age = 0 };
    int i = 0;
    char in[MAX_DATA] = "";

    printf("What's your First Name? ");
    fgets(you.first_name, MAX_DATA - 1, stdin);
    check(you.first_name != NULL, "Failed to read first name.");
    you.first_name[strlen(you.first_name) - 1] = '\0';

    printf("What's your Last Name? ");
    fgets(you.last_name, MAX_DATA - 1, stdin);
    check(you.last_name != NULL, "Failed to read last name.");
    you.last_name[strlen(you.last_name) - 1] = '\0';

    printf("How old are you? ");
    fgets(in, MAX_DATA - 1, stdin);
    you.age = atoi(in);

    printf("What color are your eyes:\n");
    for (i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    fgets(in, MAX_DATA - 1, stdin);
    eyes = atoi(in);

    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES
            && you.eyes >= 0, "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    fgets(in, MAX_DATA - 1, stdin);
    you.income = atof(in);

    printf("----- RESULTS -----\n");

    printf("First Name: %s\n", you.first_name);
    printf("Last Name: %s\n", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;
error:

    return -1;
}
