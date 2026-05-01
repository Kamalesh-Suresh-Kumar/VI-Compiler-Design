%{
#include "y.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
q           { return QUIT; }
[ \t]       ;
\n          return '\n';
.           { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}