#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool containsThreeConsecutiveTwos(char *str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '2') {
            count++;
            if (count == 3) {
                return true;
            }
        } else {
            count = 0;
        }
    }
    return false;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin); // Reading input string from user

    // Removing newline character if present
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    if (containsThreeConsecutiveTwos(str)) {
        printf("The string contains three consecutive 2s.\n");
    } else {
        printf("The string does not contain three consecutive 2s.\n");
    }

    return 0;
}
