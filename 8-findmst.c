#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];
int rank[MAX_VERTICES];

// 간선 구조체 정의
struct Edge {
    int start, end, weight;
};

// 그래프 구조체 정의
typedef struct GraphType {
    int n;  // 총 정점 수
    struct Edge edges[2 * MAX_VERTICES];  // 간선 배열
} GraphType;

// MinHeap 정의 및 관련 함수들
typedef struct {
    struct Edge heap[MAX_VERTICES];
    int size;
} MinHeap;

// 유니온-파인드 초기화
void set_init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;  // 각 정점의 부모를 자기 자신으로 초기화
        rank[i] = 0;     // 각 정점의 순위를 0으로 초기화
    }
}

// 집합 찾기 함수 (경로 압축 포함)
int set_find(int a) {
    if (parent[a] != a) {
        parent[a] = set_find(parent[a]);  // 경로 압축
    }
    return parent[a];
}

// 두 집합을 합치는 함수 (랭크 기준)
void set_union(int a, int b) {
    int rootA = set_find(a);
    int rootB = set_find(b);

    if (rootA != rootB) {
        if (rank[rootA] > rank[rootB]) {
            parent[rootB] = rootA;
        }
        else if (rank[rootA] < rank[rootB]) {
            parent[rootA] = rootB;
        }
        else {
            parent[rootB] = rootA;
            rank[rootA]++;
        }
    }
}

// MinHeap 초기화 함수
void init_minheap(MinHeap* h) {
    h->size = 0;
}

// MinHeap에 간선 삽입 함수
void insert_minheap(MinHeap* h, struct Edge item) {
    int i = ++(h->size);
    while ((i != 1) && (item.weight < h->heap[i / 2].weight)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

// MinHeap에서 간선 삭제 함수
struct Edge delete_minheap(MinHeap* h) {
    if (h->size == 0) {
        printf("Heap이 비어 있습니다.\n");
        struct Edge empty = { 0, 0, 0 };  // 비어 있을 때 반환할 기본값
        return empty;
    }

    int parent = 1, child = 2;
    struct Edge item = h->heap[1];
    struct Edge temp = h->heap[h->size--];

    while (child <= h->size) {
        if ((child < h->size) && (h->heap[child].weight > h->heap[child + 1].weight)) {
            child++;
        }
        if (temp.weight <= h->heap[child].weight) {
            break;
        }
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = 0;
}

// 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

// 그래프 생성 함수
void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
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

// 간선 가중치 비교 함수 (Quickkruskal용)
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}

// Kruskal 알고리즘 (Quick 기반)
void Quickkruskal(GraphType* g) {
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;

    set_init(g->n);
    qsort(g->edges, g->n, sizeof(struct Edge), compare);

    printf("Quick Based Kruskal\n");
    int i = 0;
    while (edge_accepted < (g->n - 1) && i < g->n) {
        e = g->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) {
            printf("Edge (%d,%d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++;
    }
    printf("\n");
}

// MinHeap을 이용한 Kruskal 알고리즘
void MinHeapKruskal(GraphType* g) {
    MinHeap h;
    int edge_accepted = 0;  // 선택된 간선 개수
    int uset, vset;
    struct Edge e;

    // 유니온-파인드 초기화
    set_init(g->n);
    // MinHeap 초기화
    init_minheap(&h);

    // 모든 간선을 MinHeap에 삽입
    for (int i = 0; i < g->n; i++) {
        insert_minheap(&h, g->edges[i]);
    }

    printf("MinHeap Based Kruskal\n");

    // Kruskal 알고리즘 수행
    while (edge_accepted < (g->n - 1) && h.size > 0) {
        e = delete_minheap(&h);  // 가중치가 가장 작은 간선 삭제

        uset = set_find(e.start);
        vset = set_find(e.end);

        // 사이클이 생성되지 않으면 선택
        if (uset != vset) {
            printf("Edge (%d,%d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);  // 두 집합을 합침
        }
    }
    printf("\n");
}

// 메인 함수
int main() {
    GraphType g;
    graph_init(&g);
    GenerateGraph(&g);

    Quickkruskal(&g);
    MinHeapKruskal(&g);

    return 0;
}
