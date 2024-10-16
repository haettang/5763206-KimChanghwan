#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    char character;
    int frequency;
    struct Node* left, * right;
} Node;

// 우선순위 큐를 위한 구조체
typedef struct MinHeap {
    int size;
    int capacity;
    Node** array;
} MinHeap;

// 새로운 노드 생성
Node* createNode(char character, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 새로운 MinHeap 생성
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node**)malloc(minHeap->capacity * sizeof(Node*));
    return minHeap;
}

// 두 노드를 교환
void swapNodes(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

// 힙 정렬을 유지하기 위한 헬퍼 함수
void minHeapify(MinHeap* minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != index) {
        swapNodes(&minHeap->array[smallest], &minHeap->array[index]);
        minHeapify(minHeap, smallest);
    }
}

// 우선순위 큐에서 최소 노드를 꺼내는 함수
Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

// 우선순위 큐에 노드를 삽입
void insertMinHeap(MinHeap* minHeap, Node* node) {
    minHeap->size++;
    int i = minHeap->size - 1;

    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// 배열을 오름차순으로 정렬하는 함수 (버블 정렬 사용)
void sortFrequencies(char characters[], int frequencies[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (frequencies[j] > frequencies[j + 1]) {
                // 빈도수 교환
                int tempFreq = frequencies[j];
                frequencies[j] = frequencies[j + 1];
                frequencies[j + 1] = tempFreq;

                // 문자 교환
                char tempChar = characters[j];
                characters[j] = characters[j + 1];
                characters[j + 1] = tempChar;
            }
        }
    }
}

// MinHeap을 생성하고 초기화하는 함수
MinHeap* buildMinHeap(char characters[], int frequencies[], int size) {
    // 빈도수 및 문자 배열을 오름차순으로 정렬
    sortFrequencies(characters, frequencies, size);

    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; i++) {
        minHeap->array[i] = createNode(characters[i], frequencies[i]);
        // 각 노드 삽입 후 힙 상태 출력
        minHeap->size++;
        for (int j = 0; j < minHeap->size; j++) {
            printf("%d ", minHeap->array[j]->frequency);
        }
        printf("\n");

        // MinHeap 정렬 유지
        for (int k = (minHeap->size - 1) / 2; k >= 0; k--) {
            minHeapify(minHeap, k);
        }
    }
    return minHeap;
}

// 허프만 트리 생성 함수
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node* left, * right, * top;

    MinHeap* minHeap = buildMinHeap(characters, frequencies, size);

    while (minHeap->size > 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);

        // 힙 상태 출력
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, top->frequency);
        for (int j = 0; j < minHeap->size; j++) {
            printf("%d ", minHeap->array[j]->frequency);
        }
        printf("\n");
    }

    return extractMin(minHeap);
}

// 허프만 코드 출력 함수
void printCodes(Node* root, int arr[], int top) {
    // 왼쪽 자식에 1 할당
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }

    // 오른쪽 자식에 0 할당
    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }

    // 리프 노드에 도달했을 때, 허프만 코드 출력
    if (!root->left && !root->right) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// 허프만 코드를 생성하는 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int arr[100], top = 0;
    printCodes(root, arr, top);
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    GenerateHuffmanCodes(characters, frequencies, size);

    return 0;
}
