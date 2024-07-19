#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin); // Reading input string from user

    // Removing newline character if present
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    int len = strlen(str);

    // Checking if the string has at least 10 characters
    if (len >= 10 && str[len - 10] == '1') {
        printf("The 10th symbol from the right end of the string is '1'.\n");
    } else {
        printf("The 10th symbol from the right end of the string is not '1'.\n");
    }

    return 0;
}
