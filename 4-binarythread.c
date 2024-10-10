#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
    int data;
    struct tree_node* left;
    struct tree_node* right;
} TreeNode;

typedef struct thread_node {
    int data;
    struct thread_node* left, * right;
    int is_thread;
} ThreadNode;

TreeNode* new_node(int key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL) {
        return new_node(key);
    }

    if (key < root->data) {
        root->left = insert_node(root->left, key);
    }
    else if (key > root->data) {
        root->right = insert_node(root->right, key);
    }

    return root;
}

TreeNode* GenerateBinaryTree(int InputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_node(root, InputData[i]);
    }
    return root;
}

void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

ThreadNode* find_successor(ThreadNode* node) {
    if (node->is_thread) {
        return node->right;
    }
    node = node->right;
    while (node != NULL && node->left != NULL) {
        node = (ThreadNode*)node->left;
    }
    return node;
}

ThreadNode* new_thread_node(int key) {
    ThreadNode* temp = (ThreadNode*)malloc(sizeof(ThreadNode));
    temp->data = key;
    temp->left = temp->right = NULL;
    temp->is_thread = 0;
    return temp;
}

void ConvertToThreaded(TreeNode* root, ThreadNode** prev, ThreadNode** new_root) {
    if (root == NULL) return;

    ConvertToThreaded(root->left, prev, new_root);

    ThreadNode* current = new_thread_node(root->data);

    if (*new_root == NULL) {
        *new_root = current;
    }

    if (*prev != NULL) {
        if ((*prev)->right == NULL) {
            (*prev)->right = current;
            (*prev)->is_thread = 1;
        }
    }
    *prev = current;

    ConvertToThreaded(root->right, prev, new_root);
}

ThreadNode* GenerateThreadTree(TreeNode* root) {
    ThreadNode* prev = NULL;
    ThreadNode* root = NULL;
    ConvertToThreaded(root, &prev, &root);
    return root;
}

void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;

    while (current != NULL && current->left != NULL) {
        current = (ThreadNode*)current->left;
    }

    while (current != NULL) {
        printf("%d ", current->data);

        current = find_successor(current);
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);

    ThreadNode* troot = GenerateThreadTree(root);
    printf("\nThread tree inorder: ");
    ThreadTreeInOrder(troot);

    free(root);
    free(troot);
    return 0;
}
