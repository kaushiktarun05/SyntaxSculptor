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

    // Checking if the string ends with "11"
    if (len >= 2 && str[len - 2] == '1' && str[len - 1] == '1') {
        printf("String ends with '11'.\n");
    } else {
        printf("String does not end with '11'.\n");
    }

    return 0;
}
