#include <stdio.h>
void reflectMatrix(int matrix[][100], int result[][100], int R, int C) {
    for (int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            result[i][j]=matrix[i][C-1-j];

        }
    }
    
}
int main() {
    int R, C;
    scanf("%d %d", &R, &C);
    int matrix[100][100];
    int result[100][100];
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    reflectMatrix(matrix, result, R, C);
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}
