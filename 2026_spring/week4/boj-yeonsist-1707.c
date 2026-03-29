// 이분 그래프인지 아닌지 판별
// 이분 그래프란 간선으로 이어진 정점은 같은 색이면 안됨.

#include <stdio.h>
#include <stdlib.h>

#define MAX_V 20001
#define MAX_E 400001 // 무방향이라 간선 2배

int head[MAX_V];     // 각 정점의 첫 간선 인덱스
int to[MAX_E];       // 간선이 향하는 정점
int nextEdge[MAX_E]; // 같은 시작점의 다음 간선 인덱스
int color[MAX_V];    // 0: 미방문, 1: 한 색, -1: 다른 색
int queue[MAX_V];    // BFS로 구현할거라 큐 필요

int edgeCount;

void addEdge(int u, int v)
{
    to[edgeCount] = v;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount;
    edgeCount++;
}

int bfs(int start)
{
    int front = 0;
    int rear = 0;

    queue[rear++] = start;
    color[start] = 1; // 시작 정점에 임의로 1번 색 부여

    while (front < rear)
    {
        int now = queue[front++];

        // now와 연결된 모든 정점을 확인
        for (int i = head[now]; i != -1; i = nextEdge[i])
        {
            int next = to[i];

            // 아직 색이 없으면 반대 색을 칠함
            if (color[next] == 0)
            {
                color[next] = -color[now];
                queue[rear++] = next;
            }
            // 이미 색이 있는데 현재 정점과 색이 같으면 이분 그래프 아님
            else if (color[next] == color[now])
            {
                return 0;
            }
        }
    }

    return 1;
}

int main(void)
{
    int K;
    scanf("%d", &K);

    while (K--)
    {
        int V, E;
        scanf("%d %d", &V, &E);

        for (int i = 1; i <= V; i++)
        {
            head[i] = -1;
            color[i] = 0;
        }
        edgeCount = 0;

        for (int i = 0; i < E; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);

            addEdge(u, v);
            addEdge(v, u);
        }

        int binary = 1;

        // 그래프가 다 연결이 아닐 수 있으므로 다른 정점에서도 확인
        for (int i = 1; i <= V; i++)
        {
            if (color[i] == 0)
            {
                if (!bfs(i))
                {
                    binary = 0;
                    break;
                }
            }
        }

        if (binary)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}