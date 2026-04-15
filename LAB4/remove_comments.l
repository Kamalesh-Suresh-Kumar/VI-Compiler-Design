%{
#include <stdio.h>

FILE *out;
int hasContent = 0;
%}

%x COMMENT

%%

"//".*              { }

"/*"                { BEGIN(COMMENT); }

<COMMENT>"*/"       { BEGIN(INITIAL); }
<COMMENT>.|\n       { }

\n                  { 
                        if(hasContent) {
                            fputc('\n', out);
                            hasContent = 0;
                        }
                    }

[ \t]+              { fputs(yytext, out); }

.                   { 
                        fputc(yytext[0], out);
                        hasContent = 1;
                    }

%%

int main() {
    FILE *in;

    in = fopen("input_code.c", "r");
    if (!in) {
        printf("Error opening input file\n");
        return 1;
    }

    out = fopen("output_code.c", "w");
    if (!out) {
        printf("Error opening output file\n");
        return 1;
    }

    yyin = in;
    yylex();

    fclose(in);
    fclose(out);

    printf("Comments removed. Check output_code.c\n");
    return 0;
}

int yywrap() {
    return 1;
}