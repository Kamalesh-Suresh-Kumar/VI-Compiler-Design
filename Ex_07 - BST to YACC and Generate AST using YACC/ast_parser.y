%{
#include <stdio.h>
#include <stdlib.h>

struct node
{
    char op;
    int val;
    struct node *left, *right;
};

struct node *root = NULL;

struct node* createNumNode(int val);
struct node* createOpNode(char op, struct node *l, struct node *r);
void preorder(struct node *t);
void inorder(struct node *t);

int yylex(void);
void yyerror(const char *s);
%}

%union
{
    int num;
    struct node *ptr;
}

%token <num> NUMBER
%type <ptr> expr

%left '+' '-'
%left '*' '/'

%%

input:
      expr '\n'
      {
          root = $1;
          printf("\nPreorder: ");
          preorder(root);

          printf("\nInorder: ");
          inorder(root);
          printf("\n");
          return 0;
      }
    ;

expr:
      expr '+' expr   { $$ = createOpNode('+', $1, $3); }
    | expr '-' expr   { $$ = createOpNode('-', $1, $3); }
    | expr '*' expr   { $$ = createOpNode('*', $1, $3); }
    | expr '/' expr   { $$ = createOpNode('/', $1, $3); }
    | '(' expr ')'    { $$ = $2; }
    | NUMBER          { $$ = createNumNode($1); }
    ;

%%

struct node* createNumNode(int val)
{
    struct node *t = malloc(sizeof(struct node));
    t->op = 'N';
    t->val = val;
    t->left = t->right = NULL;
    return t;
}

struct node* createOpNode(char op, struct node *l, struct node *r)
{
    struct node *t = malloc(sizeof(struct node));
    t->op = op;
    t->left = l;
    t->right = r;
    return t;
}

void preorder(struct node *t)
{
    if(t)
    {
        if(t->op == 'N') printf("%d ", t->val);
        else printf("%c ", t->op);

        preorder(t->left);
        preorder(t->right);
    }
}

void inorder(struct node *t)
{
    if(t)
    {
        inorder(t->left);

        if(t->op == 'N') printf("%d ", t->val);
        else printf("%c ", t->op);

        inorder(t->right);
    }
}

int main()
{
    printf("Enter expression: ");
    yyparse();
    return 0;
}

void yyerror(const char *s)
{
    printf("\nInvalid Expression\n");
}