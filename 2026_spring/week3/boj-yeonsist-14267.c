#include <stdio.h>
#include <string.h>

int parent[100001];
int praise[100001]; // i번 직원이 직접 받은 칭찬은 따로 작성해두는 게 나중에 값 불러오기 편하다
int result[100001]; // i번 직원의 최종 누적 칭찬

int head[100001];
int to[100001];
int next[100001]; // 각 직원의 부하를 저장하기 위한 인접 리스트 배열
int idx = 0;

void addChild(int boss, int child)
{
    to[idx] = child;
    next[idx] = head[boss];
    head[boss] = idx;
    idx++;
}

void dfs(int now) // 거리 누적 문제처럼 칭찬 누적해야 하므로 dfs를 쓴다.
{
    for (int i = head[now]; i != -1; i = next[i])
    {
        int child = to[i];
        result[child] = result[now] + praise[child];
        dfs(child);
    }
}
int main()
{
    int n, m; // n = 직원 수, m = i w 얼마나 넣을지
    scanf("%d %d", &n, &m);

    memset(parent, 0, sizeof(parent));
    memset(praise, 0, sizeof(praise));
    memset(result, 0, sizeof(result));
    memset(head, -1, sizeof(head));

    for (int i = 1; i < n + 1; i++)
    {
        int p;
        scanf("%d", &p);
        parent[i] += p; // i번 사람의 상사는 p

        if (p != -1)
            addChild(p, i);
    }

    for (int j = 0; j < m; j++)
    {
        int i, w; // i번 직원이 w만큼 칭찬을 받는다
        scanf("%d %d", &i, &w);
        praise[i] += w;
    }

    dfs(1);

    for (int i = 1; i <= n; i++)
    {
        printf("%d ", result[i]);
    }
}