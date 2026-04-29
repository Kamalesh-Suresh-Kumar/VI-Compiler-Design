#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

const char* keywords[] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if",
    "int","long","register","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile","while"
};

const char* OtherOperators[] = {
    "==","!=","<=",">=","++","--","&&","||",
    "+=","-=","*=","/=","%=","&=","|=","^=",
    "<<=",">>=","->"
};

/* keyword check */
bool isKeyword(char *str){
    for(int i=0;i<32;i++)
        if(strcmp(str,keywords[i])==0) return true;
    return false;
}

/* classify token */
int classify(char *str){
    int dot = 0;

    if(isKeyword(str)) return 1;

    for(int i=0; str[i]; i++){
        if(str[i]=='.') dot++;
        else if(!isdigit(str[i])){
            if(i==0 && (isalpha(str[i]) || str[i]=='_'))
                return 4;
            return 5;
        }
    }

    if(dot==1) return 3;
    if(dot==0) return 2;

    return 5;
}

/* match multi-char operators */
int matchOperator(char *str){
    for(int i=0;i<19;i++){
        int len = strlen(OtherOperators[i]);
        if(strncmp(str, OtherOperators[i], len)==0)
            return len;
    }
    return 0;
}

void printToken(char *token){
    if(strlen(token)==0) return;

    switch(classify(token)){
        case 1: printf("%s : Keyword\n",token); break;
        case 2: printf("%s : Number\n",token); break;
        case 3: printf("%s : Float\n",token); break;
        case 4: printf("%s : Identifier\n",token); break;
        default: printf("%s : Invalid Identifier\n",token);
    }
}

void analyzeCode(char *str){
    char token[200];
    int j=0;

    for(int i=0; str[i]; i++){

        /* preprocessor */
        if(str[i]=='#'){
            printf("#include : Preprocessor Directive\n");
            break;
        }

        if(str[i]=='\n' || str[i]=='\t') continue;

        /* string / char literal */
        if(str[i]=='"' || str[i]=='\''){
            char quote = str[i];
            j=0;
            token[j++]=str[i++];

            while(str[i] && (str[i]!=quote || str[i-1]=='\\'))
                token[j++]=str[i++];

            token[j++]=quote;
            token[j]='\0';

            printf("%s : %s Literal\n", token,
                   quote=='"' ? "String" : "Character");
            j=0;
            continue;
        }

        /* comments */
        if(str[i]=='/' && str[i+1]=='/'){
            printf("// : Single-line Comment\n");
            break;
        }

        if(str[i]=='/' && str[i+1]=='*'){
            printf("/* */ : Multi-line Comment\n");
            i+=2;
            while(str[i] && !(str[i]=='*' && str[i+1]=='/')) i++;
            i++;
            continue;
        }

        /* multi operators */
        int len = matchOperator(&str[i]);
        if(len){
            printf("%.*s : Operator\n", len, &str[i]);
            i += len - 1;
            continue;
        }

        /* delimiter */
        if(strchr(" +-*/%=,;[]{}()<> &|!", str[i])){
            if(j>0){
                token[j]='\0';
                printToken(token);
                j=0;
            }

            if(strchr("+-*/%=", str[i]))
                printf("%c : Operator\n",str[i]);
            else if(str[i]!=' ')
                printf("%c : Delimiter\n",str[i]);

            continue;
        }

        token[j++]=str[i];
    }

    /* last token */
    if(j>0){
        token[j]='\0';
        printToken(token);
    }
}

int main(){
    FILE* file = fopen("Input.txt", "r");
    char line[256];
    int i=1;

    if(file){
        while(fgets(line, sizeof(line), file)){
            printf("\n--- Line %d ---\n", i++);
            analyzeCode(line);
        }
        fclose(file);
    } else {
        printf("Error: Unable to open file!\n");
    }

    return 0;
}