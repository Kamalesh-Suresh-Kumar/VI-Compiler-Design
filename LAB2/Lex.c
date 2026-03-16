#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LENGTH 100
bool isDelimiter(char ch) {
    return (ch==' ' || ch=='+' || ch=='-' || ch=='*' || ch=='/' ||
            ch==',' || ch==';' || ch=='>' || ch=='<' || ch=='=' ||
            ch=='(' || ch==')' || ch=='{' || ch=='}' ||
            ch=='[' || ch==']');
}
bool isOperator(char ch) {
    return (ch=='+' || ch=='-' || ch=='*' || ch=='/' ||
            ch=='>' || ch=='<' || ch=='=');
}
bool isSpecialSymbol(char ch) {
    return (ch=='{' || ch=='}' || ch=='(' || ch==')' ||
            ch=='[' || ch==']' || ch==';' || ch==',');
}
bool isKeyword(char *str) {
    const char *keywords[] = {
        "auto","break","case","char","const","continue","default","do",
        "double","else","enum","extern","float","for","goto","if",
        "int","long","register","return","short","signed","sizeof","static",
        "struct","switch","typedef","union","unsigned","void","volatile","while"
    };
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for(int i=0;i<n;i++)
        if(strcmp(str,keywords[i])==0)
            return true;
    return false;
}
bool isIdentifier(char *str) {
    if(!isalpha(str[0]) && str[0] != '_')
        return false;
    for(int i=1; str[i]!='\0'; i++)
        if(!isalnum(str[i]) && str[i]!='_')
            return false;
    if(isKeyword(str))
        return false;
    return true;
}
char* getSubstring(char* str,int start,int end) {
    int len = end-start+1;
    char *sub = (char*)malloc(len+1);
    strncpy(sub,str+start,len);
    sub[len]='\0';
    return sub;
}
void lexicalAnalyzer(char *input) {
    int left=0,right=0;
    int len=strlen(input);
    while(right<=len && left<=right) {
        if(!isDelimiter(input[right]))
            right++;
        if(isDelimiter(input[right]) && left==right) {
            if(isOperator(input[right]))
                printf("Operator: %c\n",input[right]);
            else if(isSpecialSymbol(input[right]))
                printf("Special Symbol: %c\n",input[right]);
            right++;
            left=right;
        }
        else if((isDelimiter(input[right]) && left!=right) || (right==len && left!=right)) {
            char *sub = getSubstring(input,left,right-1);
            if(isKeyword(sub))
                printf("Keyword: %s\n",sub);
            else if(isIdentifier(sub))
                printf("Identifier: %s\n",sub);
            else
                printf("Unknown Token: %s\n",sub);
            free(sub);
            left=right;
        }
    }
}
int main() {
    FILE *fp;
    char input[MAX_LENGTH];
    fp = fopen("input.txt","r");
    if(fp==NULL) {
        printf("Error opening file\n");
        return 1;
    }
    printf("\nLexical Analysis Output\n\n");
    while(fgets(input,MAX_LENGTH,fp)) {
        input[strcspn(input,"\n")] = '\0';
        if(strlen(input)==0)
            continue;
        printf("For Expression: %s\n",input);
        lexicalAnalyzer(input);
        printf("\n");
    }
    fclose(fp);
    return 0;
}