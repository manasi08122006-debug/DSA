#include <stdio.h>
#include <stdlib.h>

typedef struct pa{
    int pid;
    char pname[50];
    int prority;
    struct pa *next;

}pa;

pa *create(pa *head){
    int n=0;
    pa *tail=NULL;
    printf("Enter the number of patients:");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        pa *newpa=(pa *)malloc(sizeof(pa));
        newpa->next=NULL;
        printf("Enter the patient %d id:",i+1);
        scanf("%d",&newpa->pid);
        printf("Enter the patient %d name:",i+1);
        scanf("%s",newpa->pname);
        printf("Enter the patient %d prority:",i+1);
        scanf("%d",&newpa->prority);
        if (head ==NULL){
            head=newpa;
            tail=newpa;
        }else{
            tail->next=newpa;
            tail=newpa;
        }
    }
    return head;
}

pa *addatstart(pa *head){
    pa *newpa=(pa *)malloc(sizeof(pa));
    newpa->next=NULL;
    printf("Enter the patient id:");
    scan("%d",&newpa->pid);
    printf("Enter the patient nam:");
    scanf("%s",newpa->pname);
    printf("Enter the patient prority:");
    scanf("%d",&newpa->prority);
    newpa->next=head;
    head=newpa;
    return head;
}

pa *insertatany(pa *head){
    int count=0;
    pa *curr=NULL;
    curr=head;
    int pos=0;
    printf("Enter the position at which you want to insert:");
    scanf("%d",&pos);
    pa *newpa=(pa *)malloc(sizeof(pa));
    newpa->next=NULL;
    printf("Enter the patient id:");
    scanf("%d",&newpa->pid);
    printf("Enter the patient name:");
    scanf("%s",newpa->pname);
    printf("Enter the patient priority:");
    scanf("%d",&newpa->prority);
    
        if(pos==1){
            head=addatstart(head);
        }else{
            for (int i=1;i<pos-1 && curr!=NULL;i++){
                curr=curr->next;
            }
            newpa->next=curr->next;
            curr->next=newpa;

        }
        curr=curr->next;
    
    return head;
}

pa *remove(pa *head){
    pa *curr=NULL;
    pa *bef=NULL;
    pa *aft=NULL;
    int pos=0;
    printf("Enter the position at which you want to delete:");
    scanf("%d",&pos);
    if(pos==1){
        curr=head;
        head=head->next;
        free(curr);
    }else{
        bef=head;
        for(int i=1;i<pos-1 && bef!=NULL;i++){
            bef=bef->next;

    }
        curr=head;
        for(int i=1;i<pos && curr!=NULL;i++){
            
            curr=curr->next;
        }

    
        aft=head;
        for(int i=1;i<pos+1 && aft!=NULL;i++){
            aft =aft->next;

    }
    
        bef->next=aft;
        free(curr);
    }

    
    return head;
}

void display(pa *head){
    pa *curr=NULL;
    curr=head;  
    while(curr!=NULL){
        printf("\nPatient id:%d",curr->pid);
        printf("\nPatient name:%s",curr->pname);
        printf("\nPatient prority:%d",curr->prority);
        curr=curr->next;
    }
    
}


int main(){
    printf("Menu Driven");
    printf("\nPress 1 for creating patient list.");      
    printf("\nPress 2 to add patient at start.");
    printf("\nPress 3 to add patient at any position.");
    printf("\nPress 4 to delete patient at any position."); 
    printf("\nPress 5 to display patient list.");
    printf("\nPress 6 to exit.");
    pa *head=NULL;
    int choice=0;
    int ch=0;
    while(ch==0){
        printf("\nEnter your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                head=create(head);
                break;
            case 2:
                head=addatstart(head);
                break;
            case 3:
                head=insertatany(head);
                break;
            case 4:
                head=remove(head);
                break;
            case 5:
                display(head);
                break;
            case 6:
                ch=1;
                break;
            default:
                printf("Invalid choice");
        }
    }

}