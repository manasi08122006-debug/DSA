#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{
    char data;
    struct node *next;
}node;

int isempty(node *top){
    return top==NULL;
}

node *push(node *top,char data){
    node *newnode =(node *)malloc(sizeof(node));
    newnode->data=data;
    newnode->next=top;

    return newnode;
}

char pop(node **top){
    node *temp=*top;
    char popped=temp->data;
    *top=(*top)->next;
    free(temp);
    return popped;
}

char peek(node *top){
    return top->data;
}

int isoperator(char c){
    return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^');
}

int precedence(char c){
    if (c=='^'){
        return 3;
    }
    else if (c=='*' || c=='/'){
        return 2;
    }
    else if (c=='+' || c=='-'){
        return 1;
    }
    else{
        return 0;
    }
}

int isrightassociative(char c){
    return c=='^';
}

void infixtopost(char infix[],char postfix[]){
    node *top=NULL;
    int i=0,j=0;
    char c;

    while (infix[i]!='\0'){
        c=infix[i];

        if (isalnum(c)){
            postfix[j++]=c;
        }
        else if (c=='('){
            top=push(top,c);
        }
        else if (c==')'){
            while (!isempty(top) && peek(top)!='('){
                postfix[j++]=pop(&top);
            }
            pop(&top);
        }
        else if (isoperator(c)){
            while (!isempty(top) && precedence(peek(top))>=precedence(c) && !isrightassociative(c)){
                postfix[j++]=pop(&top);
            }
            top=push(top,c);
        }
        i++;
    }

    while (!isempty(top)){
        postfix[j++]=pop(&top);
    }

    postfix[j]='\0';
}
int main(){
    char infix[100];
    char postfix[100];
    printf("Enter the infix expression: ");
    scanf("%s", infix);
    infixtopost(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}