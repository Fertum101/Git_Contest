#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) return createNode(value);

    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }

    return root;
}

int height(Node* root) {
    if (root == NULL) return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight) return(leftHeight + 1);
    else return(rightHeight + 1);  
}

int isBalanced(Node* root) {
    if (root == NULL) return 1;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) return 1;

    return 0;
}

int main() {
    int value;
    Node* root = NULL;

    scanf("%d", &value);
    while (value != 0) {
        root = insert(root, value);
        scanf("%d", &value);
    }

    if (isBalanced(root)) printf("YES\n");
    else printf("NO\n");

    return 0;
}
