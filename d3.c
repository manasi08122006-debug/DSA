#include <stdio.h>

int longest_chain(int arr[], int n) {
    int dp[n];
    int ans=1;
    for (int i=0;i<n;i++){
        dp[i]=1;

    }
    for(int i=1;i<n;i++){
        for(int j=0;j<n;j++){
            if(arr[j]<arr[i]){
                if (dp[i]<dp[j]+1){
                    dp[i]=dp[j]+1;
                }
            }
        }

        if(dp[i]>ans){
            ans=dp[i];
        }
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    int result = longest_chain(arr, n);
    printf("%d\n", result);
    return 0;
}
