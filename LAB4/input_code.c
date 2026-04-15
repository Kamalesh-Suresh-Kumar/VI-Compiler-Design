/* 
    Write a C program to generate Fibonacci series up to n terms.
        Input: n (number of terms to generate)
        Output: Fibonacci series up to n terms
*/

#include <stdio.h>

int main() {
    int n, t1 = 0, t2 = 1, nextTerm;

    printf("Enter the number of terms: ");
    scanf("%d", &n); // Read the number of terms to generate

    printf("Fibonacci Series: ");

    // Loop to generate Fibonacci series up to n terms
    for (int i = 1; i <= n; ++i) {
        printf("%d ", t1);
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }

    return 0;
}