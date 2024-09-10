#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

void GenerateArrayTree(int* tree) {
	int list[] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

	for (int i = 0; i < 15; i++) {
		tree[i] = list[i];
	}

	for (int i = 0; i < 15; i++) {
		printf("%d ", tree[i]);
	}
	printf("\n");
}

void ArrayPreOrder(int* tree, int index) {
	if (index < 15 && tree[index] != -1) {
		printf("%d ", tree[index]);
		ArrayPreOrder(tree, 2 * index + 1);
		ArrayPreOrder(tree, 2 * index + 2);
	}
}

void ArrayInOrder(int* tree, int index) {
	if (index < 15 && tree[index] != -1) {
		ArrayInOrder(tree, 2 * index + 1);
		printf("%d ", tree[index]);
		ArrayInOrder(tree, 2 * index + 2);
	}
}

void ArrayPostOrder(int* tree, int index) {
	if (index < 15 && tree[index] != -1) {
		ArrayPostOrder(tree, 2 * index + 1);
		ArrayPostOrder(tree, 2 * index + 2);
		printf("%d ", tree[index]);
	}
}

void ArrayOrders(int* tree) {
	ArrayPreOrder(tree, 0);
	printf("\n");
	ArrayInOrder(tree, 0);
	printf("\n");
	ArrayPostOrder(tree, 0);
	printf("\n");
}

void PlaceNode(TreeNode* node, int direction, int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	if (direction == 0) {
		node->left = newNode;
	}
	else {
		node->right = newNode;
	}
}

void GenerateLinkTree(TreeNode* root) {
	PlaceNode(root, 0, 2);
	PlaceNode(root, 1, 9);

	PlaceNode(root->left, 0, 3);
	PlaceNode(root->left, 1, 5);

	PlaceNode(root->right, 0, 10);
	PlaceNode(root->right, 1, 13);

	PlaceNode(root->left->left, 0, 4);
	PlaceNode(root->left->left, 1, 6);

	PlaceNode(root->left->right, 0, 7);
	PlaceNode(root->left->right, 1, 8);

	PlaceNode(root->right->left, 0, 11);
	PlaceNode(root->right->left, 1, 12);

	PlaceNode(root->right->right, 0, 14);
	PlaceNode(root->right->right, 1, 15);
}

void LinkPreOrder(TreeNode* np) {
	if (np != NULL) {
		printf("%d ", np->data);
		LinkPreOrder(np->left);
		LinkPreOrder(np->right);
	}
}

void LinkInOrder(TreeNode* np) {
	if (np != NULL) {
		LinkInOrder(np->left);
		printf("%d ", np->data);
		LinkInOrder(np->right);
	}
}

void LinkPostOrder(TreeNode* np) {
	if (np != NULL) {
		LinkPostOrder(np->left);
		LinkPostOrder(np->right);
		printf("%d ", np->data);
	}
}

void LinkOrders(TreeNode* root) {
	LinkPreOrder(root);
	printf("\n");
	LinkInOrder(root);
	printf("\n");
	LinkPostOrder(root);
	printf("\n");
}

int main() {
	int arr[16] = { -1 };
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = NULL;
	root->right = NULL;

	GenerateArrayTree(arr);
	GenerateLinkTree(root);
	printf("\n");

	ArrayOrders(arr);
	printf("\n");
	LinkOrders(root);
	printf("\n");

	return 0;
}
