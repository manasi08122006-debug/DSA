#include <stdio.h>
int se(int arr[], int higher, int lower,int search){
    int mid =(higher +lower)/2;
    if (higher < lower){
        return 0;
    }

    if (arr[mid]==search){
        return 1;

    }else if (arr[mid]>search){
        return se(arr,mid-1,lower,search);
    }else{
        return se(arr,higher,mid+1,search);
    }
}

int main(){
    int arr[] = {1, 2, 3, 4, 5};
    int search = 0;
    printf("Enter the element to search: ");
    scanf("%d", &search);
    int result = se(arr, 4, 0, search);
    if (result == 1) {
        printf("Element found\n");
    } else {
        printf("Element not found\n");
    }
    return 0;
}