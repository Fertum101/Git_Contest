#include <stdio.h>

int matrix[100][100]; 
int checked[100];  
int N;

void dfs(int top) {
    checked[top] = 1;
    
    for (int i = 0; i < N; i++) {
        if (matrix[top][i] == 1 && checked[i] == 0) dfs(i);
    }
}

int countConnectedVertices(int startTop) {
    int count = 0;
    dfs(startTop - 1);
    
    for (int i = 0; i < N; i++) if (checked[i] == 1) count++;
    
    return count;
}

int main() 
{
    int S;
    scanf("%d %d", &N, &S);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    printf("%d\n", countConnectedVertices(S));
    
    return 0;
}
