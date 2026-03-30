%{
#include <stdio.h>

int id_count = 0;
int op_count = 0;
%}

%%

[0-9]+      { 
                printf("Identifier (Integer): %s\n", yytext);
                id_count++; 
            }

[+*]        { 
                printf("Operator: %s\n", yytext);
                op_count++; 
            }

[ \t\n]     { /* ignore spaces */ }

.           { printf("Invalid symbol: %s\n", yytext); }

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter arithmetic expression:\n");
    yylex();

    printf("\nTotal Identifiers (Integers): %d\n", id_count);
    printf("Total Operators (+, *): %d\n", op_count);

    return 0;
}
