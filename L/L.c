#include <stdio.h>
#include <stdlib.h>

// Структура узла дерева
typedef struct Node {
    int data;            
    struct Node* left;   
    struct Node* right;   
} Node;

// Создание нового узла
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Вставка нового элемента в дерево
Node* insert(Node* root, int value) {
    if (root == NULL) return createNode(value);

    if (value < root->data) {
        root->left = insert(root->left, value); // Если значение меньше текущего узла, вставляем в левое поддерево
    } else if (value > root->data) {
        root->right = insert(root->right, value); // Если значение больше текущего узла, вставляем в правое поддерево
    }

    return root;
}

// Расчет высоты дерева
int maxHeight(Node* root) {
    if (root == NULL) return 0; 

    int leftHeight = maxHeight(root->left); // Рекурсивно вычисляем высоту левого поддерева
    int rightHeight = maxHeight(root->right); // Рекурсивно вычисляем высоту правого поддерева

    // Высота дерева - максимум из высот поддеревьев
    if (leftHeight > rightHeight) return(leftHeight + 1);
    else return(rightHeight + 1);  
}

int main() {
    int num;
    Node* root = NULL;

    while (1) {
        scanf("%d", &num);
        // Считывание чисел, пока не встретится 0
        if (num == 0) {
            break; 
        }
        root = insert(root, num);   
    }
    
    // Вычисление высоты дерева
    printf("%d\n", maxHeight(root));         

    return 0;
}