#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10 // 정점의 수를 10으로 제한
#define INF 1000L // 무한대 값 설정

int selected[MAX_VERTICES]; // MST에 선택된 정점
int distance[MAX_VERTICES]; // 각 정점에 대한 최소 거리

// 간선 구조체 정의
struct Edge {
    int start, end, weight; // 시작 정점, 끝 정점, 가중치
};

typedef struct GraphType {
    int n; // 정점의 수
    struct Edge edges[MAX_VERTICES * (MAX_VERTICES - 1) / 2]; // 간선 리스트
} GraphType;

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = 0; // 정점 수 초기화
}

// 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    // 정점 번호가 유효한지 검사
    if (start < 1 || start > MAX_VERTICES || end < 1 || end > MAX_VERTICES) {
        printf("간선 추가 불가: 정점 번호는 1에서 %d 사이여야 합니다.\n", MAX_VERTICES);
        return;
    }

    // 최대 간선 수를 초과하는지 검사
    if (g->n >= (MAX_VERTICES * (MAX_VERTICES - 1) / 2)) {
        printf("간선 추가 불가: 최대 간선 수를 초과했습니다.\n");
        return;
    }

    // 간선을 리스트에 추가 (0-based index로 변환)
    g->edges[g->n].start = start - 1;
    g->edges[g->n].end = end - 1;
    g->edges[g->n].weight = w;
    g->n++; // 간선 수 증가
}

// 그래프 생성 함수
void GenerateGraph(GraphType* g) {
    // 간선 추가
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

// 최소 거리 정점 찾는 함수
int get_min_vertex(int n) {
    int v = -1; // 초기화
    for (int i = 0; i < n; i++) {
        // 선택되지 않은 정점 중 최소 거리를 가진 정점 찾기
        if (!selected[i]) {
            if (v == -1 || distance[i] < distance[v]) {
                v = i;
            }
        }
    }
    return v; // 최소 거리 정점 반환
}

// Prim 알고리즘을 이용하여 MST 찾기
void FindPrimMST(GraphType* g) {
    int u;

    // 거리 및 선택된 정점 초기화
    for (u = 0; u < MAX_VERTICES; u++) {
        distance[u] = INF; // 거리 초기화
        selected[u] = FALSE; // 모든 정점을 선택되지 않음으로 초기화
    }
    distance[0] = 0; // 시작 정점의 거리를 0으로 설정

    printf("Prim MST Algorithm\n");
    for (int count = 0; count < g->n; count++) {
        u = get_min_vertex(MAX_VERTICES); // 최소 거리 정점 선택
        if (u == -1) break; // 더 이상 선택할 정점이 없는 경우

        selected[u] = TRUE; // 정점 u를 MST에 포함

        // 정점 추가 출력
        printf("정점 %d 추가\n", u + 1); // 정점 번호를 1부터 시작하도록 출력

        // 인접 정점의 거리 업데이트
        for (int e = 0; e < g->n; e++) {
            if (g->edges[e].start == u || g->edges[e].end == u) {
                int v = (g->edges[e].start == u) ? g->edges[e].end : g->edges[e].start;
                if (!selected[v] && g->edges[e].weight < distance[v]) {
                    distance[v] = g->edges[e].weight; // 최소 거리 업데이트
                }
            }
        }
    }
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType)); // 그래프 구조체 동적 할당
    graph_init(g); // 그래프 초기화

    // 그래프를 생성하는 함수 호출
    GenerateGraph(g);
    FindPrimMST(g); // Prim을 이용해 MST를 찾음

    free(g); // 동적 할당한 메모리 해제
    return 0;
}
