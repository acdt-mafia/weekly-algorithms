// DFS와 BFS: 그래프를 DFS로 탐색한 결과와 BFS로 탐색한 결과를 출력하는 프로그램을 작성하시오

// 인접 행렬로 풀기 -> 그래프를 2차원 배열로 표현하는 방법
#include <stdio.h>
#include <string.h>

int graph[1001][1001]; // graph[a][b] = 1 -> a랑 b 연결되어 있음. 0이면 연결 x
int visited[1001];
int queue[1001];

int n, m, v; // 정점의 개수 N(1 ≤ N ≤ 1,000), 간선의 개수 M(1 ≤ M ≤ 10,000), 탐색을 시작할 정점의 번호 V

void dfs(int now)
{
    visited[now] = 1;
    printf("%d ", now);

    for (int i = 1; i <= n; i++)
    {
        if (graph[now][i] == 1 && !visited[i]) // 즉, 이어져 있고, 안 가본 데라는 뜻
        {
            dfs(i);
        }
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

        for (int i = 1; i <= n; i++) // 꺼낸 정점의 이웃들 확인
        {
            if (graph[now][i] == 1 && !visited[i])
            {
                visited[i] = 1;
                queue[rear++] = i; // 아직 방문 안 한 이웃이면 큐에 넣는다!!
            }
        }
    }
}

int main()
{
    int m, v;
    scanf("%d %d %d", &n, &m, &v);

    memset(graph, 0, sizeof(graph));
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        graph[a][b] = 1;
        graph[b][a] = 1;
    }

    dfs(v);
    printf("\n");

    memset(visited, 0, sizeof(visited));
    bfs(v);

    return 0;
}
