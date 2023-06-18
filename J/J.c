#include <stdio.h>

int matrix[100][100];  // Матрица смежности графа
int checked[100];  // Список посещенных вершин
int N;

// Функция обхода в глубину
void dfs(int top) {
    checked[top] = 1;  // Помечаем вершину как посещенную
    
    for (int i = 0; i < N; i++) {
        // Если есть ребро между текущей вершиной и вершиной i и вершина i не была посещена ранее, вызываем dfs для вершины i
        if (matrix[top][i] == 1 && checked[i] == 0) dfs(i);
    }
}

// Функция для подсчета количества вершин в компоненте связности
int countConnectedVertices(int startTop) {
    int count = 0;
    dfs(startTop - 1);  // Индексация вершин начинается с 0
    
    for (int i = 0; i < N; i++) if (checked[i] == 1) count++;
    
    return count;
}

int main() 
{
    int S;
    scanf("%d %d", &N, &S);
    
    // Ввод матрицы смежности графа
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    // Вычисление количества вершин в компоненте связности
    printf("%d\n", countConnectedVertices(S));
    
    return 0;
}
