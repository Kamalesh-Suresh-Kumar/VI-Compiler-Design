%{
#include "y.tab.h"
%}

%%
a       return A;
b       return B;
\n      return 0;
[ \t]   ;
.       return yytext[0];
%%