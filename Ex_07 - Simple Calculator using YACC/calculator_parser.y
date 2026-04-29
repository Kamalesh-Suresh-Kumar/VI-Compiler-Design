%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token NUMBER QUIT

%left '+' '-'
%left '*' '/'
%left UMINUS

%%

input:
        /* empty */
      | input line
      ;

line:
        expr '\n'   { printf("Result = %d\n", $1); printf("Enter Expression (q to quit): "); }
      | QUIT '\n'   { exit(0); }
      | '\n'        { printf("Enter Expression (q to quit): "); }
      ;

expr:
        expr '+' expr   { $$ = $1 + $3; }
      | expr '-' expr   { $$ = $1 - $3; }
      | expr '*' expr   { $$ = $1 * $3; }
      | expr '/' expr   { $$ = $1 / $3; }
      | '(' expr ')'    { $$ = $2; }
      | '-' expr %prec UMINUS { $$ = -$2; }
      | NUMBER          { $$ = $1; }
      ;

%%

int main()
{
    printf("Enter Expression (q to quit): ");
    yyparse();
    return 0;
}

void yyerror(const char *s)
{
    printf("Invalid Expression\n");
    printf("Enter Expression (q to quit): ");
    yyparse();
}