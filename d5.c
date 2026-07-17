#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int user_logic(int* dimensions, int n) {
  int dp[205][205];
  for (int i=1;i<=n;i++){
    dp[i][i]=0;
  }

  for (int len=2; len<=n; len++){
    for(int i=1; i<=n;i++){
        int j=i +len -1;
        dp[i][j]=INT_MAX;

        for(int k=i;k<j;k++){
            int cost = dp[i][k]+dp[k+1][j]+dimensions[i-1]*dimensions[k]*dimensions[j];
            if(cost < dp[i][j]){
                dp[i][j] = cost;
            }

        }
    }
  }
  return dp[1][n];
}

int main() {
    int n;
    scanf("%d", &n);
    int* dimensions = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n + 1; i++) {
        scanf("%d", &dimensions[i]);
    }
    int result = user_logic(dimensions, n);
    printf("%d\n", result);
    free(dimensions);
    return 0;
}
