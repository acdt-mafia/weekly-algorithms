// DFS와 BFS: 그래프를 DFS로 탐색한 결과와 BFS로 탐색한 결과를 출력하는 프로그램을 작성하시오

// 인접 리스트로 풀기

#include <stdio.h>
#include <string.h>

int head[1001];  // 정점 u의 간선 목록 시작점
int to[10001];   // i번 간선이 가리키는 도착 정점
int next[10001]; // 같은 시작 노드에서 다음 간선 번호 //무방향이라서 이렇게 배열 크기 2배
int idx = 0;     // 현재까지 저장한 간선 수

int visited[1001];
int queue[1001];

void addEdge(int u, int v)
{
    to[idx] = v;
    next[idx] = head[u];
    head[u] = idx;
    idx++;
}
// 1260번은 작은 번호 먼저 방문해야만 함. addEdge만 하면 순서를 크기순으로 안 넣으면 순서 원하는 대로 안 될 수 있음
// 인접 리스트 만든 후 정렬... 샤갈 인접 행렬 쓰면 간단하다고 하지만 일단 해보자
// 허허 head to next로 쓰면 정렬을 할 수가 없음
// 포기 -> 순서 크기순 조건 빼고 걍 만들어 봄

void dfs(int now)
{
    visited[now] = 1;
    printf("%d ", now);

    for (int i = head[now]; i != -1; i = next[i])
    {
        int nxt = to[i];
        if (!visited[nxt])
            dfs(nxt);
    }
}

void bfs(int start)
{
    int front = 0, rear = 0;

    queue[rear++] = start; // 시작 정점을 큐에 넣는다.
    visited[start] = 1;

    while (front < rear) // 큐가 빌 때까지
    {
        int now = queue[front++]; // 큐에서 하나 꺼냄
        printf("%d ", now);

        for (int i = head[now]; i != -1; i = next[i]) // 꺼낸 정점의 이웃들 확인
        {
            int nxt = to[i];
            if (!visited[nxt])
            {
                visited[nxt] = 1;
                queue[rear++] = nxt; // 아직 방문 안 한 이웃이면 큐에 넣는다!!
            }
        }
    }
}

int main()
{
    int n, m, v;
    scanf("%d %d %d", &n, &m, &v);

    memset(head, -1, sizeof(head));
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        addEdge(a, b);
        addEdge(b, a); // 무방향!
    }

    dfs(v);
    printf("\n");

    memset(visited, 0, sizeof(visited));
    bfs(v);
    printf("\n");
}