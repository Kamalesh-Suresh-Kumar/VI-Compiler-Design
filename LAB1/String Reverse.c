#include <stdio.h>
void main() {
    char str[100], rev[100];
    int i = 0, j;
    printf("Enter string: ");
    fgets(str, sizeof(str), stdin);
    while (str[i] != '\0' && str[i] != '\n')
        i++;
    for (j = 0; j < i; j++)
        rev[j] = str[i - j - 1];
    rev[j] = '\0';
    printf("String Reverse without build-in function...\n");
    printf("Reversed string: %s\n", rev);
}