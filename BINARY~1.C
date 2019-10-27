/* BINARY TREE */
#include <stdio.h>
#include <conio.h>
#include <string.h>
#define OPEN -1
#define CLOSE 1
#define OPERAND 2
#define OPERATOR -2
struct NODE { char data; struct NODE *left, *right; };
typedef struct NODE NODE;
typedef struct { NODE *root; } TREE;
NODE *getNode(char);
void link(NODE *, NODE *, NODE *);
TREE *create(char *);
int character(char);
void infix(NODE *);
void prefix(NODE *);
void postfix(NODE *);
void main() {
TREE *tree;
char *expression; int choice;
clrscr(); printf("\nBINARY TREE : EXPRESSION TREE\n");
printf("\nEXPRESSION TREE\n");
printf("\nEnter the expression: (Infix Notation)\n");
scanf("%s", expression);
tree = create(expression);
printf("\nMAINMENU\n");
printf("\n1) Infix\t2) Prefix\t3) Postfix\t4) EXIT\n");
do {
printf("\nEnter the choice: ");
scanf("%d", &choice);
switch(choice) {
case 1: {
printf("\nInfix Notation:\n");
infix(tree->root);
break;}
case 2: {
printf("\nPrefix Notation:\n");
prefix(tree->root);
break;
}
case 3: {
printf("\nPostfix Notation:\n");
postfix(tree->root);
break;
}
case 4: {
printf("\nExitting...");
break;
}
default:
printf("\nWrong choice! Try again...");
}
}while(choice != 4);
getch();
}
NODE *getNode(char data) {
NODE *node = (NODE*)malloc(sizeof(NODE));
node->data = data; node->left = NULL; node->right = NULL;
return node;
}
void link(NODE *leftnode, NODE *thisnode, NODE *rightnode) {
if(thisnode) {
thisnode->left = leftnode;
thisnode->right = rightnode;
}
}
int character(char c) {
if(c=='(') return OPEN;
else if(c==')') return CLOSE;
else if(c=='+'||c=='-'||c=='*'||c=='/') return OPERATOR;
else if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')) return OPERAND;
else return 0;
}TREE *create(char *expression) {
TREE *tree = (TREE *)malloc(sizeof(TREE));
tree->root = NULL;
if(expression) {
NODE **stack = (NODE **)calloc(strlen(expression), sizeof(NODE *));
NODE *tempnode;
int index=-1, top=-1;
while(expression[++index]!='\0')
switch(character(expression[index])) {
case OPEN: {
stack[++top] = getNode(expression[index]);
break;
}
case OPERAND: {
if(character(stack[top]->data)==OPERATOR) {
tree->root = stack[top--];
link(stack[top--], tree->root, getNode(expression[index]));
stack[++top] = tree->root;
}
else
stack[++top] = getNode(expression[index]);
break;
}
case OPERATOR: {
stack[++top] = getNode(expression[index]);
break;
}
case CLOSE: {
tree->root = stack[top--];
free(stack[top--]);
stack[++top] = tree->root;
break;
}
}
while(top>0) {
tempnode = stack[top--];
tree->root = stack[top--];
link(stack[top--], tree->root, tempnode);
stack[++top] = tree->root;
}tree->root = stack[top--];
free(stack);
}
return tree;
}
void infix(NODE *root) {
if(root) {
infix(root->left);
printf("%c", root->data);
infix(root->right);
}
}
void prefix(NODE *root) {
if(root) {
printf("%c", root->data);
prefix(root->left);
prefix(root->right);
}
}
void postfix(NODE *root) {
if(root) {
postfix(root->left);
postfix(root->right);
printf("%c", root->data);
}
}
