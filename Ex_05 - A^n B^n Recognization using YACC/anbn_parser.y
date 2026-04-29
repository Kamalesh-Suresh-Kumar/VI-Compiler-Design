%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token A B

%%

S : A S B
  | A B
  ;

%%

int main()
{
    printf("Enter the string: ");
    
    if(yyparse() == 0)
        printf("Valid String...\n");
    
    return 0;
}

void yyerror(const char *s)
{
    printf("Invalid String...\n");
}

int yywrap()
{
    return 1;
}