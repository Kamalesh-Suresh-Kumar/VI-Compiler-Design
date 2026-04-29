#include <stdio.h>
void main() {
    char str[100];
    size_t length = 0;
    printf("Enter string: ");
    fgets(str, sizeof(str), stdin);   
    for (; str[length] != '\0'; length++);   
    if (str[length-1] == '\n')   
        length--;
    printf("Length of string without strlen() function: %zu...\n", length);
}