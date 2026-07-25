// Online C compiler to run C program online
#include <stdio.h>
int ispresent(int arr[],int size, int num ){
    for (int i=0;i<size;i++){
        if (arr[i]==num){
            return 1;
        }
    }
    return 0;
}

void accept(int arr[],int size){
    printf("\nenter the elements of set one by one");
    int i=0;
    while (i<size){
        int k=0;
        scanf("%d",&k);
        int result=ispresent(arr,size,k);
        if (result==1){
            printf("Already present,enter different element\n");
        }
        else{
            arr[i]=k;
            i++;
        }}

    
}

void display(int arr[],int size){
    for (int i=0;i<size;i++){
        printf("%d\t",arr[i]);
    }
}

void uni(int arr1[],int size1,int arr2[],int size2){
    int unionarr[size1+size2];
    for (int i=0;i<size1;i++){
        unionarr[i]=arr1[i];
    }
    int k=size1;
    for (int j=0;j<size2;j++){
        int result=ispresent(unionarr,k,arr2[j]);
        if (result==0){
            unionarr[k]=arr2[j];
            k++;
        }
    }
    printf("\nUnion of two sets is:\n");
    display(unionarr,k);
}

int main() {
    int n1=0,n2=0;
    printf("enter the size of first set:");
    scanf("%d",&n1);
    int set1[n1];
    accept(set1,n1);
    display(set1,n1);
    printf("enter the size of second set:");
    scanf("%d",&n2);
    int set2[n2];
    accept(set2,n2);
    display(set2,n2);

    uni(set1,n1,set2,n2);
    
    
}
    
