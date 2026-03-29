// 최소비용 구하기
//  그래프, 최소 거리 찾기.
//  1967 참고.. 하려 했으나! 포인터를 쓰는 인접 리스트로...해서 달라짐
//  DFS 문제가 아님. 최소 비용이면 다익스트라? 알고리즘.

#include <stdio.h>
#include <stdlib.h>
#define INF 1000000000 // 대충 무한대 이거 처음에 1000000정도로 했다가 틀림..당황슨

typedef struct Node
{
    int arrival; // 도착
    int cost;
    struct Node *next; // 같은 출발 도시에서 이어지는 다음 간선
} Node;

// 힙(우선순위 큐)에 넣을 원소: 다익스트라에서는 현재까지 비용이 가장 작은 도시를 먼저 꺼내야
typedef struct
{
    int arrival; // 도착
    int cost;
    struct Node *next; // 같은 출발 도시에서 이어지는 다음 간선
} HeapNode;

// 최소 힙 구조체
typedef struct
{
    HeapNode *arr; // 힙 배열
    int size;      // 현재 힙에 들어있는 원소 개수
} MinHeap;

void addEdge(Node *graph[], int from, int to, int cost)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->arrival = to;
    newNode->cost = cost;

    newNode->next = graph[from];
    graph[from] = newNode;
}

// 힙에서 두 원소 교환하는 함수 -> 어디다 필요 한건가요 push 할 때
void swap(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// 최소 힙 생성
MinHeap *createMinHeap(int capacity)
{
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->arr = (HeapNode *)malloc(sizeof(HeapNode) * (capacity + 1));
    heap->size = 0;
    return heap;
}

// 힙에 원소 삽입
void push(MinHeap *heap, int arrival, int cost)
{
    heap->size++;
    int idx = heap->size;

    // 일단 맨 뒤에 새 원소 삽입
    heap->arr[idx].arrival = arrival;
    heap->arr[idx].cost = cost;

    // 부모와 비교하면서 위로 올림 (heapify up)
    while (idx > 1)
    {
        int parent = idx / 2;

        // 부모가 더 작거나 같으면 최소 힙 조건 만족
        if (heap->arr[parent].cost <= heap->arr[idx].cost)
            break;

        // 부모가 더 크면 교환
        swap(&heap->arr[parent], &heap->arr[idx]);
        idx = parent;
    }
}

// 힙이 비어있는지 확인하는 함수
int isEmpty(MinHeap *heap)
{
    return heap->size == 0;
}

// 힙에서 최소 원소 꺼내기: 가장 작은 cost(루트)를 꺼낸 뒤 마지막 원소를 루트로 올리고 아래로 내려보낸다?
HeapNode pop(MinHeap *heap)
{
    HeapNode minNode = heap->arr[1];      // 루트가 최소값
    heap->arr[1] = heap->arr[heap->size]; // 마지막 원소를 루트로
    heap->size--;

    int idx = 1;

    while (1)
    {
        int left = idx * 2;
        int right = idx * 2 + 1;
        int smallest = idx;

        // 왼쪽 자식이 더 작으면 smallest 갱신
        if (left <= heap->size &&
            heap->arr[left].cost < heap->arr[smallest].cost)
        {
            smallest = left;
        }

        // 오른쪽 자식이 더 작으면 smallest 갱신
        if (right <= heap->size &&
            heap->arr[right].cost < heap->arr[smallest].cost)
        {
            smallest = right;
        }

        // 더 이상 내려갈 필요 없으면 종료
        if (smallest == idx)
            break;

        // 자식과 교환하고 계속 내려감
        swap(&heap->arr[idx], &heap->arr[smallest]);
        idx = smallest;
    }

    return minNode;
}

// 여기까지 힙. 우선순위 큐를 구현하는 방법 중 하나가 힙. 항상 루트(맨 위)가 최소값이 되도록
// 힙이 하는 일: push, 들어간 거 중 제일 작은 게 맨 위로 올라오게 조절, pop 해서 젤 작은 거 나오게

// 다익스트라 함수: graph: 인접리스트. n:도시개수. dist[]:최단거리 저장배열. dist[i]:시작 도시에서 i번 도시까지의 현재 최소 비용
void dijkstra(Node *graph[], int n, int start, int dist[], int heapCapacity)
{

    MinHeap *heap = createMinHeap(heapCapacity);

    // 모든 비용을 무한대로 초기화 -> 그래야 뭐가 들어와도 얘보단 작으니까 업데이트 될거임.
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INF;
    }

    // 시작 도시까지 가는 비용은 0으로 설정
    dist[start] = 0;

    // (시작 도시, 비용 0)을 힙에 넣고 시작
    push(heap, start, 0);

    while (!isEmpty(heap))
    {
        // 현재까지 비용이 가장 적은 도시를 꺼냄
        HeapNode current = pop(heap);

        int now = current.arrival;
        int currentCost = current.cost;

        /*
            힙에는 같은 도시가 여러 번 들어갈 수 있다.

            어떤 도시 3번이 처음엔 비용 10으로 들어갔다가 나중에 더 좋은 경로를 찾아 비용 5로 또 들어갈 수 있다.

            그러면 비용 10짜리 오래된 정보가 나중에 pop될 수 있는데,
            이미 dist[3]에는 5가 저장되어 있으므로 이 정보는 무시해야 한다.
        */
        if (currentCost > dist[now])
        {
            continue;
        }

        // now 도시에서 갈 수 있는 모든 다음 도시 탐색
        Node *temp = graph[now];
        while (temp != NULL)
        {
            int next = temp->arrival;
            int edgeCost = temp->cost;

            // 시작 -> now 까지 비용 + now -> next 비용
            int newCost = currentCost + edgeCost;

            // 더 싼 경로를 찾았다면 갱신
            if (newCost < dist[next])
            {
                dist[next] = newCost;
                push(heap, next, newCost);
            }

            temp = temp->next;
        }
    }

    free(heap->arr);
    free(heap);
}

int main()
{
    int n, m;
    scanf("%d", &n); // 도시 개수
    scanf("%d", &m); // 버스 개수

    // graph[i]는 i번 도시에서 출발하는 간선들의 연결 리스트의 시작 주소
    // 도시 번호가 1부터 시작하므로 n+1 크기로 만든다.

    Node **graph = (Node **)malloc(sizeof(Node *) * (n + 1));
    for (int i = 1; i <= n; i++)
    {
        graph[i] = NULL;
    }

    for (int i = 0; i < m; i++)
    {
        int from, to, cost;
        scanf("%d %d %d", &from, &to, &cost);
        addEdge(graph, from, to, cost);
    }

    int start, end;
    scanf("%d %d", &start, &end);

    // dist 배열: 시작 도시에서 각 도시까지의 최소 비용 저장
    int *dist = (int *)malloc(sizeof(int) * (n + 1));

    dijkstra(graph, n, start, dist, m * 2 + 10);

    printf("%d\n", dist[end]);

    // 인접 리스트 메모리 해제
    for (int i = 1; i <= n; i++)
    {
        Node *temp = graph[i];
        while (temp != NULL)
        {
            Node *toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }

    free(graph);
    free(dist);

    return 0;
}