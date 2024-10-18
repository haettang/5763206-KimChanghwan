#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100  // 그래프에서 최대 정점 수
#define MAX_SIZE 100      // 큐에서 최대 크기

// 그래프 구조체 정의
typedef struct {
    int n;  // 정점의 수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];  // 인접 행렬
} GraphMatType;

// 큐 구조체 정의
typedef struct {
    int data[MAX_SIZE];  // 큐의 데이터 저장 배열
    int front, rear;     // 큐의 앞과 뒤 인덱스
} Queue;

// 큐 초기화 함수
void init_queue(Queue* q) {
    q->front = q->rear = 0;  // front와 rear를 0으로 초기화
}

// 큐가 비어 있는지 확인하는 함수
int is_empty_queue(Queue* q) {
    return (q->front == q->rear);  // front와 rear가 같으면 큐가 비어 있음
}

// 큐가 가득 차 있는지 확인하는 함수
int is_full_queue(Queue* q) {
    return ((q->rear + 1) % MAX_SIZE == q->front);  // rear가 front의 앞쪽이면 큐가 가득 참
}

// 큐에 아이템을 추가하는 함수
void enqueue(Queue* q, int item) {
    if (is_full_queue(q)) {
        fprintf(stderr, "Queue is full\n");  // 큐가 가득 차면 에러 메시지 출력
        return;
    }
    q->data[q->rear] = item;  // rear 위치에 아이템 추가
    q->rear = (q->rear + 1) % MAX_SIZE;  // rear 인덱스 업데이트
}

// 큐에서 아이템을 제거하는 함수
int dequeue(Queue* q) {
    if (is_empty_queue(q)) {
        fprintf(stderr, "Queue is empty\n");  // 큐가 비어 있으면 에러 메시지 출력
        return -1;  // 실패를 나타내기 위해 -1 반환
    }
    int item = q->data[q->front];  // front 위치의 아이템을 가져옴
    q->front = (q->front + 1) % MAX_SIZE;  // front 인덱스 업데이트
    return item;  // 제거한 아이템 반환
}

// 그래프 생성 함수
GraphMatType* create_mat_graph() {
    return (GraphMatType*)malloc(sizeof(GraphMatType));  // 그래프 구조체 메모리 할당
}

// 그래프 메모리 해제 함수
void destroy_mat_graph(GraphMatType* g) {
    free(g);  // 그래프 구조체 메모리 해제
}

// 그래프 초기화 함수
void init_mat_graph(GraphMatType* g) {
    g->n = 0;  // 정점 수를 0으로 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0;  // 인접 행렬을 0으로 초기화
        }
    }
}

// 정점 추가 함수
void insert_vertex_mat_graph(GraphMatType* g) {
    if (g->n >= MAX_VERTICES) {
        fprintf(stderr, "Over number of vertex\n");  // 최대 정점 수 초과시 에러 메시지
        return;
    }
    g->n++;  // 정점 수 증가
}

// 엣지 추가 함수
void insert_edge_mat_graph(GraphMatType* g, int s, int e) {
    if (s >= g->n || e >= g->n) {
        fprintf(stderr, "Vertex number error\n");  // 잘못된 정점 번호 입력시 에러 메시지
        return;
    }
    if (g->adj_mat[s][e] == 0) {
        g->adj_mat[s][e] = 1;  // 엣지 추가
        g->adj_mat[e][s] = 1;  // 무향 그래프이므로 양쪽 모두 설정
    }
}

// 그래프 생성 함수
void Generate_mat_graph(GraphMatType* g) {
    for (int i = 0; i <= 10; i++) {
        insert_vertex_mat_graph(g);  // 정점 추가
    }
    // 엣지 추가
    insert_edge_mat_graph(g, 0, 2);
    insert_edge_mat_graph(g, 0, 4);
    insert_edge_mat_graph(g, 0, 5);
    insert_edge_mat_graph(g, 0, 6);
    insert_edge_mat_graph(g, 0, 9);
    insert_edge_mat_graph(g, 1, 4);
    insert_edge_mat_graph(g, 1, 5);
    insert_edge_mat_graph(g, 1, 7);
    insert_edge_mat_graph(g, 1, 10);
    insert_edge_mat_graph(g, 2, 3);
    insert_edge_mat_graph(g, 2, 4);
    insert_edge_mat_graph(g, 3, 4);
    insert_edge_mat_graph(g, 3, 5);
    insert_edge_mat_graph(g, 4, 5);
    insert_edge_mat_graph(g, 4, 6);
    insert_edge_mat_graph(g, 4, 7);
    insert_edge_mat_graph(g, 6, 7);
    insert_edge_mat_graph(g, 6, 8);
    insert_edge_mat_graph(g, 7, 10);
    insert_edge_mat_graph(g, 8, 9);
    insert_edge_mat_graph(g, 8, 10);
}

// 이웃 정점을 정렬하는 함수
void sort_neighbors(int* neighbors, int num_neighbors) {
    for (int i = 0; i < num_neighbors - 1; i++) {
        for (int j = i + 1; j < num_neighbors; j++) {
            if (neighbors[i] > neighbors[j]) {
                // 인접 정점 정렬
                int temp = neighbors[i];
                neighbors[i] = neighbors[j];
                neighbors[j] = temp;
            }
        }
    }
}

// 깊이 우선 탐색 함수
void DFS(GraphMatType* g, int v, int search, int* visited, int* found, int* visited_count) {
    visited[v] = 1;  // 현재 정점을 방문한 것으로 표시
    (*visited_count)++;  // 방문한 정점 수 증가
    printf("%d ", v);  // 현재 방문한 정점 출력

    if (v == search) {
        *found = 1;  // 탐색 성공
        return;
    }

    int* neighbors = (int*)malloc(g->n * sizeof(int));  // 이웃 정점을 저장할 배열
    int num_neighbors = 0;

    // 현재 정점의 이웃 정점 찾기
    for (int i = 0; i < g->n; i++) {
        if (g->adj_mat[v][i] && !visited[i]) {
            neighbors[num_neighbors++] = i;  // 방문하지 않은 이웃 정점 추가
        }
    }

    // 이웃 정점 정렬
    sort_neighbors(neighbors, num_neighbors);

    // 이웃 정점에 대해 DFS 재귀 호출
    for (int i = 0; i < num_neighbors; i++) {
        if (!visited[neighbors[i]]) {
            DFS(g, neighbors[i], search, visited, found, visited_count);
            if (*found) {
                free(neighbors);  // 성공적으로 탐색한 경우 메모리 해제
                return;
            }
        }
    }

    visited[v] = 0;  // 백트래킹을 위해 방문 표시 해제
    free(neighbors);  // 메모리 해제
}

// 깊이 우선 탐색 실행 함수
void execute_dfs(GraphMatType* g, int start, int search) {
    int visited[MAX_VERTICES] = { 0 };  // 방문한 정점 배열 초기화
    int found = 0;  // 탐색 성공 여부 플래그
    int visited_count_dfs = 0;  // 방문한 정점 수

    // DFS 호출
    DFS(g, start, search, visited, &found, &visited_count_dfs);

    // 탐색 결과 출력
    if (found) {
        printf("\n탐색 성공: %d\n", search);
    }
    else {
        printf("\n모든 노드를 탐색했습니다. 탐색 실패: %d\n", search);
    }
    printf("방문한 노드 수: %d\n\n", visited_count_dfs);
}

// 넓이 우선 탐색 함수
void BFS(GraphMatType* g, int start, int search) {
    int* visited = (int*)calloc(g->n, sizeof(int));  // 방문한 정점 배열 동적 할당
    Queue q;
    init_queue(&q);  // 큐 초기화
    int found = 0;  // 탐색 성공 여부 플래그
    int visited_count = 0;  // 방문한 정점 수

    enqueue(&q, start);  // 시작 정점을 큐에 추가
    visited[start] = 1;  // 시작 정점 방문 표시

    // BFS 루프
    while (!is_empty_queue(&q)) {
        int v = dequeue(&q);  // 큐에서 정점 제거
        visited_count++;  // 방문한 정점 수 증가
        printf("%d ", v);  // 현재 방문한 정점 출력

        if (v == search) {
            found = 1;  // 탐색 성공
            break;  // 탐색 종료
        }

        // 이웃 정점 찾기
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] && !visited[i]) {
                enqueue(&q, i);  // 방문하지 않은 이웃 정점을 큐에 추가
                visited[i] = 1;  // 방문 표시
            }
        }
    }

    // 탐색 결과 출력
    if (found) {
        printf("\n탐색 성공: %d\n", search);
    }
    else {
        printf("\n모든 노드를 탐색했습니다. 탐색 실패: %d\n", search);
    }
    printf("방문한 노드 수: %d\n\n", visited_count);

    free(visited);  // 메모리 해제
}

// 사용자 인터페이스 함수
void UserInterface(GraphMatType* g) {
    int start, search;
    int choice;
    printf("------------------\n");
    printf("1 : 깊이 우선 탐색\n");
    printf("2 : 넓이 우선 탐색\n");
    printf("3 : 종료\n");
    printf("------------------\n");

    while (1) {
        
        printf("메뉴 입력: ");
        scanf("%d", &choice);  // 사용자 선택 입력

        switch (choice) {
        case 1:
            printf("시작 번호와 탐색할 값 입력: ");
            scanf("%d", &start);  // 시작 정점 입력
            scanf("%d", &search);  // 탐색할 정점 입력
            // 입력된 정점 번호 유효성 검사
            if (start < 0 || start >= g->n || search < 0 || search >= g->n) {
                printf("잘못된 입력입니다. 정점 번호를 확인하세요.\n\n");
                break;
            }
            execute_dfs(g, start, search);  // DFS 실행
            break;
        case 2:
            printf("시작 번호와 탐색할 값 입력: ");
            scanf("%d", &start);  // 시작 정점 입력
            scanf("%d", &search);  // 탐색할 정점 입력
            // 입력된 정점 번호 유효성 검사
            if (start < 0 || start >= g->n || search < 0 || search >= g->n) {
                printf("잘못된 입력입니다. 정점 번호를 확인하세요.\n\n");
                break;
            }
            BFS(g, start, search);  // BFS 실행
            printf("\n");
            break;
        case 3:
            printf("프로그램을 종료합니다.\n");
            return;  // 프로그램 종료
        default:
            printf("잘못된 선택입니다.\n\n");
            break;
        }
    }
}

// 메인 함수
int main() {
    GraphMatType* g = create_mat_graph();  // 그래프 생성
    init_mat_graph(g);  // 그래프 초기화
    Generate_mat_graph(g);  // 그래프 생성
    UserInterface(g);  // 사용자 인터페이스 실행
    destroy_mat_graph(g);  // 그래프 메모리 해제
    return 0;  // 프로그램 종료
}
