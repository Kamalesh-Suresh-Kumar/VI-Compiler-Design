#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

const char Operators[6] = {'+','-','*','/','%','='};

const char Delimiters[20] = {
    ' ','+','-','*','/','%','=',',',';',
    '[',']','{','}','(',')','<','>','&','|','!'
};

/* multi-length operators */
const char* OtherOperators[] = {
    "==","!=","<=",">=","++","--","&&","||",
    "+=","-=","*=","/=","%=","&=","|=","^=",
    "<<=",">>=","->"
};

const char* keywords[] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if",
    "int","long","register","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile","while"
};

/* operator check */
bool isOperator(char ch){
    for(int i=0;i<6;i++)
        if(ch==Operators[i]) return true;
    return false;
}

/* delimiter check */
bool isDelimiter(char ch){
    for(int i=0;i<19;i++)
        if(ch==Delimiters[i]) return true;
    return false;
}

/* keyword check */
bool isKeyword(char *str){
    for(int i=0;i<32;i++)
        if(strcmp(str,keywords[i])==0) return true;
    return false;
}

/* identifier check */
bool isValidIdentifier(char *str){
    return (isalpha(str[0]) || str[0]=='_');
}

/* integer check */
bool isInteger(char *str){
    for(int i=0;str[i]!='\0';i++)
        if(!isdigit(str[i])) return false;
    return true;
}

/* float check */
bool isFloat(char *str){
    int dot=0;
    for(int i=0;str[i]!='\0';i++){
        if(str[i]=='.') dot++;
        else if(!isdigit(str[i])) return false;
    }
    return dot==1;
}

/* multi-operator check */
bool isOtherOperator(char *str){
    for(int i=0;i<19;i++){
        int len=strlen(OtherOperators[i]);
        if(strncmp(str,OtherOperators[i],len)==0)
            return true;
    }
    return false;
}

void analyzeCode(char *str){
    char token[200];
    int j=0;

    for(int i=0; str[i]!='\0'; i++){

        /* handle preprocessor */
        if(str[i]=='#'){
            printf("#include : Preprocessor Directive\n");
            break;
        }

        if(str[i] == '\n' || str[i] == '\t')
            continue;

        /* string literal */
        if(str[i]=='"'){
            j=0;
            token[j++]=str[i++];
            while(str[i] && (str[i]!='"' || str[i-1]=='\\'))
                token[j++]=str[i++];
            token[j++]='"';
            token[j]='\0';
            printf("%s : String Literal\n",token);
            j=0;
            continue;
        }

        /* char literal */
        if(str[i]=='\''){
            j=0;
            token[j++]=str[i++];
            while(str[i] && (str[i]!='\'' || str[i-1]=='\\'))
                token[j++]=str[i++];
            token[j++]='\'';
            token[j]='\0';
            printf("%s : Character Literal\n",token);
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
        if(isOtherOperator(&str[i])){
            for(int k=0;k<19;k++){
                int len=strlen(OtherOperators[k]);
                if(strncmp(&str[i],OtherOperators[k],len)==0){
                    printf("%s : Operator\n",OtherOperators[k]);
                    i+=len-1;
                    break;
                }
            }
            continue;
        }

        /* delimiter handling */
        if(isDelimiter(str[i])){
            if(j>0){
                token[j]='\0';

                if(strlen(token)==0){
                    j=0;
                    continue;
                }

                if(isKeyword(token))
                    printf("%s : Keyword\n",token);
                else if(isFloat(token))
                    printf("%s : Float\n",token);
                else if(isInteger(token))
                    printf("%s : Number\n",token);
                else if(isValidIdentifier(token))
                    printf("%s : Identifier\n",token);
                else
                    printf("%s : Invalid Identifier\n",token);

                j=0;
            }

            if(isOperator(str[i]))
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

        if(strlen(token)==0)
            return;

        if(isKeyword(token))
            printf("%s : Keyword\n",token);
        else if(isFloat(token))
            printf("%s : Float\n",token);
        else if(isInteger(token))
            printf("%s : Number\n",token);
        else if(isValidIdentifier(token))
            printf("%s : Identifier\n",token);
        else
            printf("%s : Invalid Identifier\n",token);
    }
}

int main()
{
    FILE* file = fopen("Input.txt", "r");
    char line[256];
    int i=1;

    if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            printf("\n--- Line %d ---\n", i++);
            analyzeCode(line);
        }
        fclose(file);
    }
    else {
        printf("Error: Unable to open file!\n");
    }

    return 0;
}