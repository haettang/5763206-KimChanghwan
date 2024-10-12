#define _CRT_SECURE_NO_WARNINGS //비쥬얼 스튜디오 scanf 안정성 에러 해결용 define
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    int key; // 힙의 요소를 나타내는 키 값
} element;

typedef struct {
    element heap[MAX_SIZE]; // 최대 크기를 가진 힙 배열
    int heap_size; // 현재 힙의 크기
} TreeNode;

// 힙 생성 함수
TreeNode* create_heap() {
    return (TreeNode*)malloc(sizeof(TreeNode)); // TreeNode 구조체를 동적 할당
}

// 힙 초기화 함수
void init_heap(TreeNode* h) {
    h->heap_size = 0; // 힙 크기를 0으로 초기화
}

// 힙 메모리 해제 함수
void destroy_heap(TreeNode* h) {
    free(h); // 동적 할당된 메모리 해제
}

// 힙이 비어 있는지 확인하는 함수
int is_empty_heap(TreeNode* h) {
    return (h->heap_size == 0); // 힙 크기가 0이면 true
}

// 힙이 가득 찼는지 확인하는 함수
int is_full_heap(TreeNode* h) {
    return (h->heap_size == (MAX_SIZE - 1)); // 힙 크기가 최대 크기와 같으면 true
}

// 힙에 요소를 삽입하는 함수
void insert_heap(TreeNode* h, element item) {
    int i = ++(h->heap_size); // 힙 크기 증가 후 새로운 요소의 인덱스 설정

    // 부모 노드보다 큰 경우 노드 이동
    while (i > 1 && h->heap[i / 2].key < item.key) {
        h->heap[i] = h->heap[i / 2]; // 부모 노드 이동
        i /= 2; // 부모 노드 인덱스 업데이트
    }
    h->heap[i] = item; // 새 요소 삽입
}

// 최대 힙 트리 생성 함수
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* h = create_heap(); // 힙 생성
    init_heap(h); // 힙 초기화

    // 입력 데이터를 힙에 삽입
    for (int i = 0; i < size; i++) {
        element item;
        item.key = inputData[i];
        insert_heap(h, item); // 힙에 요소 삽입
    }

    return h; // 생성된 힙 반환
}

// 힙에서 요소를 삭제하고 중간 과정을 출력하는 함수
element delete_heap_verbose(TreeNode* h) {
    if (is_empty_heap(h)) {
        fprintf(stderr, "Heap is empty!\n"); // 힙이 비어 있을 경우 에러 메시지 출력
        exit(EXIT_FAILURE);
    }

    element item = h->heap[1]; // 삭제할 루트 요소 저장
    element temp = h->heap[h->heap_size--]; // 마지막 요소 저장 후 힙 크기 감소

    h->heap[1] = temp; // 루트에 마지막 요소 배치
    int move_count = 1; // 이동 횟수 카운트 초기화

    int parent = 1; // 부모 노드 초기화
    int child = 2; // 자식 노드 초기화

    // 현재 힙 상태 출력
    for (int i = 1; i <= h->heap_size + 1; i++) {
        if (i <= h->heap_size) {
            printf("%d ", h->heap[i].key);
        }
    }
    printf("\n");

    // 힙 정렬 과정
    while (child <= h->heap_size) {
        // 더 큰 자식 선택
        if (child + 1 <= h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
            child++;
        }

        // 부모가 자식보다 크면 정렬 완료
        if (temp.key >= h->heap[child].key) {
            break;
        }

        // 자식 노드를 부모로 이동
        h->heap[parent] = h->heap[child];
        parent = child; // 부모 인덱스 업데이트
        child *= 2; // 자식 인덱스 업데이트
        move_count++; // 이동 횟수 증가

        // 현재 힙 상태 출력
        for (int i = 1; i <= h->heap_size + 1; i++) {
            if (i == parent) {
                printf("%d ", temp.key); // 현재 부모 표시
            }
            else if (i <= h->heap_size) {
                printf("%d ", h->heap[i].key); // 나머지 노드 표시
            }
        }
        printf("\n");
    }

    h->heap[parent] = temp; // 정렬 후 최종 위치에 요소 배치

    printf("노드가 이동된 횟수: %d\n", move_count); // 이동 횟수 출력

    return item; // 삭제된 요소 반환
}

// 힙을 레벨별로 출력하는 함수
void display_heap(TreeNode* h) {
    int level = 1; // 현재 레벨
    int count = 0; // 레벨 내 요소 수 카운트

    printf("트리 레벨별 출력\n");
    for (int i = 1; i <= h->heap_size; i++) {
        if (count < (1 << (level - 1))) { // 현재 레벨의 최대 요소 수와 비교
            if (count == 0) {
                printf("[%d] ", level); // 레벨 출력
            }
            printf("%d ", h->heap[i].key); // 힙 요소 출력
            count++;
        }
        else {
            level++; // 다음 레벨로 이동
            count = 1; // 카운트 초기화
            printf("\n[%d] %d ", level, h->heap[i].key); // 새 레벨의 첫 요소 출력
        }
    }
    printf("\n");
}

// 자세한 노드 삽입 함수
void InsertMaxHeapTreeVerbose(TreeNode* h, element item) {
    int i = ++(h->heap_size); // 힙 크기 증가 후 새로운 요소 인덱스 설정
    int moveCount = 0; // 이동 횟수 초기화

    h->heap[i] = item; // 새 요소 삽입

    // 부모 노드와 비교하여 위치 조정
    while (i > 1 && h->heap[i / 2].key < h->heap[i].key) {
        for (int j = 1; j <= h->heap_size; j++) {
            printf("%d ", h->heap[j].key); // 현재 힙 상태 출력
        }
        printf("\n");

        // 부모와 자식 교환
        element temp = h->heap[i];
        h->heap[i] = h->heap[i / 2];
        h->heap[i / 2] = temp;

        i /= 2; // 부모 인덱스 업데이트
        moveCount++; // 이동 횟수 증가
    }

    for (int j = 1; j <= h->heap_size; j++) {
        printf("%d ", h->heap[j].key); // 최종 힙 상태 출력
    }
    printf("\n노드가 이동된 횟수: %d\n", moveCount); // 이동 횟수 출력
}

// 사용자 인터페이스 함수
void runUserInterface(TreeNode* h) {
    char command;
    printf("----------------------\n");
    printf("    i: 노드 추가\n    d: 노드 삭제\n    p: 레벨별 출력\n    c: 종료\n");
    printf("----------------------\n\n");

    while (1) {
        printf("\n메뉴 입력 : ");
        scanf(" %c", &command); // 사용자 명령 입력
        if (command == 'c') {
            break; // 종료 명령
        }
        else if (command == 'i') {
            element newElement;
            printf("추가할 값 입력: ");
            scanf("%d", &newElement.key); // 추가할 값 입력
            InsertMaxHeapTreeVerbose(h, newElement); // 힙에 추가
        }
        else if (command == 'd') {
            element deletedElement = delete_heap_verbose(h); // 힙에서 삭제
        }
        else if (command == 'p') {
            display_heap(h); // 힙 출력
        }
        else {
            printf("유효하지 않은 입력값입니다. 다시 입력하세요."); // 잘못된 입력 처리
        }
    }
}

// 메인 함수
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 }; // 입력 데이터
    int size = sizeof(inputData) / sizeof(inputData[0]); // 입력 데이터 크기 계산

    TreeNode* heap = generateMaxHeapTree(inputData, size); // 최대 힙 생성

    runUserInterface(heap); // 사용자 인터페이스 실행
    destroy_heap(heap); // 힙 메모리 해제
    return 0; // 프로그램 종료
}
