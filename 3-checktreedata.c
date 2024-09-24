#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;
typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s) {
	s->top = NULL;
}

int is_empty(LinkedStackType* s) {
	return (s->top == NULL);
}

void push(LinkedStackType* s, element item) {
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

element pop(LinkedStackType* s) {
	StackNode* temp = s->top;
	element data = temp->data;
	s->top = temp->link;
	free(temp);
	return data;
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

int GetSumOfNodes(TreeNode* root) {
	LinkedStackType s;
	init(&s);
	int sum = 0;

	if (root == NULL) return 0;

	push(&s, root);

	while (!is_empty(&s)) {
		TreeNode* node = pop(&s);
		sum += node->data;

		if (node->right) push(&s, node->right);
		if (node->left) push(&s, node->left);
	}

	printf("Sum of nodes: %d\n", sum);
}

int GetNumberOfNodes(TreeNode* root) {
	LinkedStackType s;
	init(&s);
	int count = 0;

	if (root == NULL) return 0;

	push(&s, root);

	while (!is_empty(&s)) {
		TreeNode* node = pop(&s);
		count++;

		if (node->right) push(&s, node->right);
		if (node->left) push(&s, node->left);
	}

	printf("Number of nodes: %d\n", count);
}

int GetHeightOfTree(TreeNode* root) {
	if (root == NULL) return 0;

	LinkedStackType s;
	init(&s);
	push(&s, root);

	int height = 0;
	while (!is_empty(&s)) {
		int level_size = 0;
		LinkedStackType tempStack;
		init(&tempStack);

		while (!is_empty(&s)) {
			TreeNode* node = pop(&s);
			level_size++;

			if (node->left) push(&tempStack, node->left);
			if (node->right) push(&tempStack, node->right);
		}

		s = tempStack;
		height++;
	}

	printf("Height of Tree: %d\n", height);
}

int GetNumberOfLeafNodes(TreeNode* root) {
	LinkedStackType s;
	init(&s);
	int leafCount = 0;

	if (root == NULL) return 0;

	push(&s, root);

	while (!is_empty(&s)) {
		TreeNode* node = pop(&s);

		if (node->left == NULL && node->right == NULL) {
			leafCount++;
		}

		if (node->right) push(&s, node->right);
		if (node->left) push(&s, node->left);
	}

	printf("Number of leaf nodes: %d\n", leafCount);
}

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = NULL;
	root->right = NULL;

	GenerateLinkTree(root);

	GetSumOfNodes(root);
	GetNumberOfNodes(root);
	GetHeightOfTree(root);
	GetNumberOfLeafNodes(root);

	return 0;
}
