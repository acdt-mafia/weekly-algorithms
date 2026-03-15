// 가중치가 있는 트리에서, 아무 두 노드 사이 거리 중 가장 긴 것(트리 지름) 을 구하는 문제
// DFS 를 두 번 한다. 아무노드에서 가장 멀리 있는 노드 A 찾기. A에서 가장 멀리 있는 거리 찾기. 이게 지름.
/*
1단계: 트리를 저장해야 한다. 이진 트리가 아니므로 한 노드가 여러 노드와 연결 가능. 인접 리스트처럼 저장
2단계: 한 노드에서 연결된 모든 다음 노드로 이동해야 하므로 DFS 탐색
3단계: DFS할 때는 현재 노드 번호, 시작점부터 현재 노드까지의 누적 거리 두 개를 같이 들고 다녀야 한다.
4단계: DFS 중에 현재 거리가 지금까지 본 최대 거리보다 크면 최대 거리 갱신, 그 노드 번호도 저장.
5단계: 이 과정을 한 번은 1번 노드에서 하고, 한 번은 첫 DFS에서 찾은 가장 먼 노드에서 다시 한다.
*/

/*
DFS 함수에서 하는 일:
현재 노드 now, 현재까지 누적 거리 dist.
1. 현재 노드를 방문 처리한다 -> visited 배열 사용
2. dist가 최대 거리보다 크면 갱신한다
3. 현재 노드와 연결된 모든 이웃 노드를 본다
4. 아직 방문하지 않은 이웃이면 dist + 간선 가중치로 DFS를 재귀 호출한다
*/

#include <stdio.h>
#include <string.h> //memset() 배열 초기화 때 이용

#define MAX 10001

int head[MAX];       // 각 노드에서 시작하는 첫 간선의 인덱스
int to[MAX * 2];     // 각 간선이 도착하는 노드 번호 //*2인 이유는 무방향이라 저장 2번 해야 해서 배열 늘린 것.
int weight[MAX * 2]; // 각 간선의 가중치
int next[MAX * 2];   // 한 노드에서 이어진 간선들 저장. 다음 간선의 인덱스. next[2:현재 노드와 이어져있는 이번에 확인하고 있는 간선 번호] = 1: 현재 노드와 이어져 있는 다음에 볼 간선 번호; -1 되면 끝난다.
int visited[MAX];    // 방문 여부 확인용

int idx = 0;     // 현재 저장된 간선 개수. 간선 번호처럼 쓰임. 새 간선 추가할 때마다 idx++
int maxDist = 0; // DFS 중 찾은 최대 거리
int farNode = 0; // maxDist를 만들었던 노드 번호

void addEdge(int u, int v, int w)
{
    // u에서 v로 가는 가중치 w의 간선 하나를 저장하는 함수
    to[idx] = v;         // idx 간선이 도착하는 노드
    weight[idx] = w;     // idx 간선의 가중치
    next[idx] = head[u]; // 기존에 u에서 시작하던 첫 간선을 next로 연결
    head[u] = idx;       // 이제 idx번 간선이 u의 첫 간선이 됨.
    idx++;
}

void dfs(int now, int dist)
{
    visited[now] = 1; // 현재 노드 방문 처리

    if (dist > maxDist)
    {
        maxDist = dist;
        farNode = now;
    }
    for (int i = head[now]; i != -1; i = next[i])
    {
        // now(현재노드)에서 시작하는 간선들을 하나씩 따라가는 반복문.
        // head[now]에서 시작하고 next[i]로 넘어가면서 현재 노드와 연결된 모든 간선을 본다.
        int nxt = to[i];
        int w = weight[i];

        if (!visited[nxt])
        { // 방문 안 한 노드 재귀 호출
            dfs(nxt, dist + w);
        }
    }
}

int main()
{
    int n; // 노드 개수 입력 받기. 간선은 노드 개수-1
    scanf("%d", &n);

    memset(head, -1, sizeof(head)); // 초기화. 어떤 노드에도 연결된 간선 없다.

    for (int i = 0; i < n - 1; i++)
    { // 노드가 n개면 간선 n-1개
        int parent, child, w;
        scanf("%d %d %d", &parent, &child, &w);

        addEdge(parent, child, w);
        addEdge(child, parent, w); // 양방향 저장. 부모 자식 방향보다 연결 관계 자체가 중요
    }

    memset(visited, 0, sizeof(visited));
    maxDist = 0;
    farNode = 1;
    dfs(1, 0); // 첫 번째 DFS

    memset(visited, 0, sizeof(visited));
    maxDist = 0;
    dfs(farNode, 0);

    printf("%d\n", maxDist);

    return 0;
}