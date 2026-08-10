#include <stdio.h>

#include <stdlib.h>



typedef struct node{

	int data;

	struct node *next;

}node;



void sh(node *head){

	node *curr=NULL;

	curr=head;

	while(curr!=NULL){

		printf("%d\t",curr->data);

		curr=curr->next;

				}



}





node *create(node *head){

	node *tail=NULL;

	int n=0;

	printf("Enter the number of elements in link list:");

	scanf("%d",&n);

	for (int i=0;i<n;i++){

		node *newnode=(node *)malloc(sizeof(node));

		newnode->next=NULL;

		printf("Enter the %d element:",i+1);

		scanf("%d",&newnode->data);

		if (head==NULL){

			head=newnode;

			tail=newnode;

		}else{

			tail->next=newnode;

			tail=newnode;

		}

	}

	return head;



}



node *atstart(node *head){



	node *newnode=(node *)malloc(sizeof(node));

	newnode->next=NULL;

	printf("\nEnter the element you want to add at start:");

	scanf("%d",&newnode->data);

	newnode->next=head;

	head=newnode;



	return head;

}

node *atend(node *head){

	int count=0;

	node *mov=NULL;

	mov=head;

	while(mov!=NULL){

		mov=mov->next;

		count++;

		}

	mov=head;

	for (int i=1;i<count;i++){

		mov=mov->next;

	}





	node *newnode=(node *)malloc(sizeof(node));

	newnode->next=NULL;

	printf("\nEnter the element to add at the end:");

	scanf("%d",&newnode->data);

	mov->next=newnode;

	return head;

}



node *insert(node *head){

	node *mov=NULL;

	int pos=0;

	printf("\nEnter the position :");

	scanf("%d",&pos);

	node *newnode=(node *)malloc(sizeof(node));

	newnode->next=NULL;

	printf("\nEnter the value at %d position:",pos);

	scanf("%d",&newnode->data);





	if(pos==1){

		newnode->next=head;

		head=newnode;

	}else{

		mov=head;

		for(int i=1;i<pos-1;i++){

			mov=mov->next;



		}

		newnode->next=mov->next;

		mov->next=newnode;

	}



	return head;

}



node *deleteatend(node *head){

	node *mov=NULL;

	int count=0;

	node *end=NULL;

	end=head;

	mov=head;

	while(end!=NULL){

		end=end->next;

		count++;

	}





	for (int i=1;i<count-1;i++){

		mov=mov->next;

	}

	mov->next=NULL;

	free(end);



	return head;

}



node *deleteatstart(node *head){

	node *curr=NULL;

	curr=head;

	head=head->next;

	free(curr);



	return head;

}



node *deleteatany(node *head){

	node *aft=NULL;

	node *bef=NULL;

	int pos=0;

	int count=0;

	node *mov=NULL;

	mov=head;

	while(mov!=NULL){

		mov=mov->next;

		count++;

		}

	printf("\nEnter the position at which you want to delete:");

	scanf("%d",&pos);

	if (pos<1 || pos>count){

		return head;

	}else{

		if(pos==1){

			head=deleteatstart(head);

		}else if(pos==count){

			head=deleteatend(head);

		}else{

			bef=head;

			for(int i=1 ;i<pos-1 && bef!=NULL;i++){

				bef=bef->next;

			}

			mov=head;

			for(int i=1 ;i<pos && mov!=NULL;i++){

				mov=mov->next;

						}

			aft=head;

			for(int i=1 ;i<pos+1 && mov!=NULL;i++){

				aft=aft->next;

						}

			bef->next=aft;

			free(mov);

			}

	}





	return head;

}



void sear(node *head){

	int k=0;

	int found=0;

	printf("Enter the element to search");

	scanf("%d",&k);

	node *curr=NULL;

	curr=head;



	while(curr!=NULL){

		if(curr->data==k){

			found=1;

		}

		curr=curr->next;

	}

	if(found==1){

		printf("%d is present in the linked list",k);



	}else{

		printf("Not found");

	}



}







int main(void) {

	printf("Menu Drive");

	printf("\nPress 1 for creating linked list.");

	printf("\nPress 2 to add element at start.");

	printf("\nPress 3 to add at the end.");

	printf("\nPress 4 to insert an element anywhere in the linked list.");

	printf("\nPress 5 to delete element at the end");

	printf("\nPress 6 to delete element at the start");

	printf("\nPress 7 to delete element from any position ");

	printf("\nPress 8 to search ");

	printf("\nPress 9 to display linked list");

	printf("\nPress 10 to exit the program");

	node *head=NULL;



	int ch=0;

	int choice=0;

	while(ch==0){

		printf("\nEnter your choice:");

		scanf("%d",&choice);



		switch (choice){

		case 1:

			head=create(head);

			sh(head);



			break;

		case 2:

			head=atstart(head);

			sh(head);

			break;

		case 3:

			head=atend(head);

			sh(head);



			break;

		case 4:

			head=insert(head);

			sh(head);



			break;

		case 5:

			head=deleteatend(head);



			sh(head);



			break;

		case 6:

			head=deleteatstart(head);

			sh(head);

			break;

		case 7:

			head=deleteatany(head);

			sh(head);

			break;

		case 8:

			sear(head);

			break;

		case 9:

			sh(head);

			break;



		case 10:

			ch=1;

			printf("\nExiting the program");

			break;

		default:

			printf("\nInvalid choice");





		}

	}



}