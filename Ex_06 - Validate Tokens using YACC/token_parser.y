%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;

int yylex();
void yyerror(const char *s);

int keyword = 0, identifier = 0, operatorc = 0;
%}

%token KEYWORD IDENTIFIER OPERATOR

%%

program :
        program token
        |
        ;

token :
      KEYWORD     { keyword++; }
    | IDENTIFIER  { identifier++; }
    | OPERATOR    { operatorc++; }
    ;

%%

int main()
{
    yyin = fopen("sample.c", "r");

    if(yyin == NULL)
    {
        printf("File not found\n");
        return 0;
    }

    yyparse();

    printf("Keywords    = %d\n", keyword);
    printf("Identifiers = %d\n", identifier);
    printf("Operators   = %d\n", operatorc);

    fclose(yyin);
    return 0;
}

void yyerror(const char *s)
{
}