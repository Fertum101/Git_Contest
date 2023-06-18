#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;            
    struct Node* left;   
    struct Node* right;   
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

int maxHeight(Node* root) {
    if (root == NULL) {
        return 0; 
    }

    int leftHeight = maxHeight(root->left);
    int rightHeight = maxHeight(root->right);   

    if (leftHeight > rightHeight) return(leftHeight + 1);
    else return(rightHeight + 1);  
}

int main() {
    int num;
    Node* root = NULL;

    while (1) {
        scanf("%d", &num);
        if (num == 0) {
            break;    
        }
        root = insert(root, num);   
    }

    int height = maxHeight(root);   
    printf("%d\n", height);         

    return 0;
}