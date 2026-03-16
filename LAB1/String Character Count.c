#include <stdio.h>
void main() {
    char str[100];
    int i = 0;
    int digits = 0, alphabets = 0, special = 0;
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    while (str[i] != '\0') {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
          alphabets++;
        else if (str[i] >= '0' && str[i] <= '9')
          digits++;
        else if (str[i] != ' ' && str[i] != '\n')
          special++;
        i++;
    }
    printf("Number of Alphabets: %d\n", alphabets);
    printf("Number of Digits: %d\n", digits);
    printf("Number of Special Characters: %d\n", special);
}