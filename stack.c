#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node;

void displaystack(node *top){
    node *curr=top;
    while (curr!=NULL){
        printf("%d \t",curr->data);
        curr=curr->next;
    }
}

node *push(node *top,int data){
    node *newnode =(node *)malloc(sizeof(node));
    newnode->data=data;
    newnode->next=top;

    return newnode;
}

int pop(node **top){
    if (*top==NULL){
        return -1;
    }
    node *temp=*top;
    int popped=temp->data;
    *top=(*top)->next;
    free(temp);
    return popped;
}

int peek(node *top){
    if (top==NULL){
        return -1;
    }

    return top->data;
}

int main (){
    node *top=NULL;
    printf("Menu:\n1. Push\n2. Pop\n3. Peek\n4. Display Stack\n5. Exit\n");
    int choice=0;
    int ch=0;
    int data;
    while (ch==0){
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch (choice){
            case 1:{
                printf("Enter data to push: ");
                scanf("%d",&data);
                top=push(top,data);}
                break;
            case 2:
                data=pop(&top);
                if (data!=-1){
                    printf("Popped element: %d\n",data);
                }
                break;
            case 3:
                data=peek(top);
                if (data!=-1){
                    printf("Top element: %d\n",data);
                }
                break;
            case 4:
                displaystack(top);
                break;
            case 5:
                ch=1;
                break;
            default:
                printf("Invalid choice\n");
        }
    }

}