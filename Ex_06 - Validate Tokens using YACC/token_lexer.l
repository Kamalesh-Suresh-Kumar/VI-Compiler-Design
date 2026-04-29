%{
#include "y.tab.h"
%}

letter [a-zA-Z_]
digit  [0-9]

%%

^[ \t]*\#.*                    ;

"//".*                         ;

"/*"([^*]|\n|(\*+([^*/]|\n)))*"*"+"/"     ;

\"([^\\\"\n]|\\.)*\"          ;

\'([^\\\'\n]|\\.)\'           ;

"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while" { return KEYWORD; }

"=="|"!="|"<="|">="|"++"|"--"|"&&"|"||"|"+"|"-"|"*"|"/"|"="|"%"|"<"|">" { return OPERATOR; }

{letter}({letter}|{digit})*   { return IDENTIFIER; }

[ \t\r\n]+                    ;

.                             ;

%%

int yywrap()
{
    return 1;
}