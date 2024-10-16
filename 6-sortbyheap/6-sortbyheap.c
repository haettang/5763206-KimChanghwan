#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType* create_heap() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init_heap(HeapType* h) {
    h->heap_size = 0;
}

void destroy_heap(HeapType* h) {
    free(h);
}

int is_empty_heap(HeapType* h) {
    return (h->heap_size == 0);
}

int is_full_heap(HeapType* h) {
    return (h->heap_size == (MAX_ELEMENT - 1));
}

// 힙의 상태를 출력하는 함수
void print_heap(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

void insert_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);

    while (i > 1 && h->heap[i / 2].key < item.key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;

    // 삽입 후 힙 상태 출력
    print_heap(h);
}

// 두 요소의 값을 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 주어진 배열을 힙으로 재구성하는 함수 (힙 재정렬)
void resortHeap(int inputData[], int n, int i) {
    int largest = i;   // 루트를 가장 큰 값으로 가정
    int left = 2 * i + 1;   // 왼쪽 자식
    int right = 2 * i + 2;  // 오른쪽 자식

    // 왼쪽 자식이 더 크면 largest를 업데이트
    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    // 오른쪽 자식이 더 크면 largest를 업데이트
    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    // largest가 현재 노드(i)가 아니면 교환하고 재귀적으로 힙 재구성
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

// Max Heap을 구축하는 함수
void BuildMaxHeap(int inputData[], int n) {
    // 첫 번째 비리프 노드에서부터 힙을 구성
    for (int i = (n / 2) - 1; i >= 0; i--) {
        resortHeap(inputData, n, i);
    }
}

// Max Heap을 정렬하면서 힙의 변화를 출력하는 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    HeapType* h = create_heap();
    init_heap(h);

    // 힙에 하나씩 삽입하고 상태 출력
    for (int i = 0; i < n; i++) {
        element item;
        item.key = inputData[i];
        insert_heap(h, item);
    }

    // Max Heap의 정렬 과정에서 힙의 변화를 출력
    for (int i = n - 1; i > 0; i--) {
        // 루트와 마지막 요소를 교환
        swap(&inputData[0], &inputData[i]);

        // 교환 후 힙 재정렬
        resortHeap(inputData, i, 0);

        // 힙 재정렬 후 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }

    destroy_heap(h);
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
