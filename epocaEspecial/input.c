
#include "input.h"
#include <stdio.h>
#include <string.h>

#define INVALID_VALUE "The value entered is invalid."

/**
 * @brief This functions is responsible to clean the buffer made.
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * @brief This function checks if the integer provided is valid based on the range 
 * provided as well.
 * @param minValue The minimum value to be considered in the range.
 * @param maxValue The maximum integer to be considered in the range.
 * @param msg It prompts a custom message from the user.
 * @return The value provided if valid.
 */
int getInt(int minValue, int maxValue, char *msg) {
    int value;
    printf(msg);
    while (scanf("%d", &value) != 1 || value < minValue || value > maxValue) {
        puts(INVALID_VALUE);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return value;
}

/**
 * @brief This function stores a String provided if has less than size characteres, provided by the user.
 * @param string Where to store the string provided.
 * @param size The maximum characteres.
 * @param msg It prompts a custom message from the user.
 */
void readString(char *string, unsigned int size, char *msg) {

    int valid = 0;

    do {

        printf(msg);
        if (fgets(string, size, stdin) != NULL) {
            unsigned int len = strlen(string) - 1;
            if (string[len] == '\n') {
                string[len] = '\0';
            } else {
                cleanInputBuffer();
            }

            if (strlen(string) >= size - 1) {
                printf("TOO LONG!! Please enter less than %ul characters.\n", size);
            } else {
                valid = 1;
            }
        }
    } while(!valid);
}
