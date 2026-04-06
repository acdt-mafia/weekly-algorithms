// 레알 너무너무너무 포기하고 싶은 거 간신히 참음요

// N개의 정점으로 이루어진 트리가 있다. 정점은 1번부터 N번까지 번호가 매겨져 있고, 간선은 1번부터 N-1번까지 번호가 매겨져 있다.
// 아래의 두 쿼리를 수행하는 프로그램을 작성하라
//  1 i c: i번 간선의 비용을 c로 바꾼다
//  2 u v: u에서 v로 가는 단순 경로에 존재하는 비용 중에서 가장 큰 것을 출력한다.

// HLD(Heavy Light Decomposition) 구현 문제라고 함. = 무거운, 가벼운 간선으로 분해한다.
// segment tree:
#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001
#define MAXE 200001
#define NEG_INF -1000000000

typedef struct EdgeNode
{
    int to;
    int w;
    int idx;
    int next;
} EdgeNode;

// 인접 리스트용 배열
EdgeNode edges[MAXE];
int headAdj[MAXN];
int edgeCnt = 0;

// 입력 간선 정보 저장
int edgeU[MAXN];
int edgeV[MAXN];
int edgeW[MAXN];

// 트리 정보
int parentArr[MAXN];
int depthArr[MAXN];
int sizeArr[MAXN];
int heavyChild[MAXN];

// HLD 정보
int chainHead[MAXN];
int posInBase[MAXN];
int currentPos = 0;

// 각 정점 x에 대해
// valueToParent[x] = parent[x] -- x 간선의 가중치
// 즉 간선 가중치가 정점 x에 저장된다고 생각하면 된다.
int valueToParent[MAXN];

// 세그먼트 트리의 바탕 배열
int baseArray[MAXN];

// 세그먼트 트리
int segTree[MAXN * 4];

// DFS에서 재귀 대신 반복을 사용하기 위한 스택
int stackNode[MAXN];
int stackParent[MAXN];
int stackState[MAXN];

// 간선 추가
void addEdge(int u, int v, int w, int idx)
{
    edges[edgeCnt].to = v;
    edges[edgeCnt].w = w;
    edges[edgeCnt].idx = idx;
    edges[edgeCnt].next = headAdj[u];
    headAdj[u] = edgeCnt++;
}

// 두 수의 최대값
int maxInt(int a, int b)
{
    return (a > b) ? a : b;
}

// 세그먼트 트리 구축
void buildSeg(int node, int start, int end)
{
    if (start == end)
    {
        segTree[node] = baseArray[start];
        return;
    }

    int mid = (start + end) / 2;
    buildSeg(node * 2, start, mid);
    buildSeg(node * 2 + 1, mid + 1, end);

    segTree[node] = maxInt(segTree[node * 2], segTree[node * 2 + 1]);
}

// 세그먼트 트리 점 업데이트
void updateSeg(int node, int start, int end, int idx, int value)
{
    if (start == end)
    {
        segTree[node] = value;
        return;
    }

    int mid = (start + end) / 2;

    if (idx <= mid)
    {
        updateSeg(node * 2, start, mid, idx, value);
    }
    else
    {
        updateSeg(node * 2 + 1, mid + 1, end, idx, value);
    }

    segTree[node] = maxInt(segTree[node * 2], segTree[node * 2 + 1]);
}

// 세그먼트 트리 구간 최대 질의
int querySeg(int node, int start, int end, int left, int right)
{
    if (right < start || end < left)
    {
        return NEG_INF;
    }

    if (left <= start && end <= right)
    {
        return segTree[node];
    }

    int mid = (start + end) / 2;
    int q1 = querySeg(node * 2, start, mid, left, right);
    int q2 = querySeg(node * 2 + 1, mid + 1, end, left, right);

    return maxInt(q1, q2);
}

void dfs1_iterative(int root)
{
    int top = 0;

    stackNode[top] = root;
    stackParent[top] = 0;
    stackState[top] = 0;
    top++;

    while (top > 0)
    {
        int node = stackNode[top - 1];
        int par = stackParent[top - 1];
        int state = stackState[top - 1];
        top--;

        if (state == 0)
        {
            // 처음 방문
            parentArr[node] = par;
            sizeArr[node] = 1;
            heavyChild[node] = -1;

            // 나중에 자식들 처리가 끝난 뒤 size 계산을 위해 다시 넣어 둔다.
            stackNode[top] = node;
            stackParent[top] = par;
            stackState[top] = 1;
            top++;

            // 자식 방문
            int e;
            for (e = headAdj[node]; e != -1; e = edges[e].next)
            {
                int nxt = edges[e].to;
                int w = edges[e].w;

                if (nxt == par)
                {
                    continue;
                }

                depthArr[nxt] = depthArr[node] + 1;
                valueToParent[nxt] = w;

                stackNode[top] = nxt;
                stackParent[top] = node;
                stackState[top] = 0;
                top++;
            }
        }
        else
        {
            // 자식들 모두 처리된 뒤
            int e;
            int maxSub = 0;

            for (e = headAdj[node]; e != -1; e = edges[e].next)
            {
                int nxt = edges[e].to;

                if (nxt == par)
                {
                    continue;
                }

                sizeArr[node] += sizeArr[nxt];

                if (sizeArr[nxt] > maxSub)
                {
                    maxSub = sizeArr[nxt];
                    heavyChild[node] = nxt;
                }
            }
        }
    }
}

void dfs2_iterative(int root)
{
    int stackN[MAXN];
    int stackH[MAXN];
    int top = 0;

    stackN[top] = root;
    stackH[top] = root;
    top++;

    while (top > 0)
    {
        int startNode = stackN[top - 1];
        int head = stackH[top - 1];
        top--;

        int cur = startNode;

        // heavy chain을 따라 쭉 내려가며 같은 head를 부여
        while (cur != -1)
        {
            chainHead[cur] = head;
            posInBase[cur] = ++currentPos;
            baseArray[currentPos] = valueToParent[cur];

            // light child들은 나중에 각각 새 체인으로 처리
            int e;
            for (e = headAdj[cur]; e != -1; e = edges[e].next)
            {
                int nxt = edges[e].to;

                if (nxt == parentArr[cur])
                {
                    continue;
                }

                if (nxt == heavyChild[cur])
                {
                    continue;
                }

                stackN[top] = nxt;
                stackH[top] = nxt;
                top++;
            }

            // heavy child는 같은 체인으로 계속 진행
            cur = heavyChild[cur];
        }
    }
}

int queryPath(int u, int v, int n)
{
    int result = NEG_INF;

    while (chainHead[u] != chainHead[v])
    {
        // 더 깊은 체인의 쪽을 u로 맞춘다.
        if (depthArr[chainHead[u]] < depthArr[chainHead[v]])
        {
            int temp = u;
            u = v;
            v = temp;
        }

        // chainHead[u] ~ u 구간은 하나의 연속 구간
        // 이 구간의 모든 정점은 해당 체인 위에 있고,
        // 각 정점은 부모와의 간선값을 저장한다.
        result = maxInt(result, querySeg(1, 1, n, posInBase[chainHead[u]], posInBase[u]));

        // 이 체인 전체를 처리했으므로 체인 head의 부모로 올라간다.
        u = parentArr[chainHead[u]];
    }

    // 이제 u, v는 같은 체인에 있다.
    if (u == v)
    {
        // 같은 정점이면 경로 간선이 없다.
        // 이 문제에서는 u != v 쿼리만 나오지만, 안전하게 처리
        return result;
    }

    // 더 위에 있는 정점을 u로 맞춘다.
    if (depthArr[u] > depthArr[v])
    {
        int temp = u;
        u = v;
        v = temp;
    }

    result = maxInt(result, querySeg(1, 1, n, posInBase[u] + 1, posInBase[v]));

    return result;
}

int main(void)
{
    int n;
    int i;

    scanf("%d", &n);

    // 인접 리스트 초기화
    for (i = 1; i <= n; i++)
    {
        headAdj[i] = -1;
        heavyChild[i] = -1;
        valueToParent[i] = 0;
    }

    // 트리는 N-1개 간선
    for (i = 1; i <= n - 1; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        edgeU[i] = u;
        edgeV[i] = v;
        edgeW[i] = w;

        addEdge(u, v, w, i);
        addEdge(v, u, w, i);
    }

    // 루트를 1로 잡는다.
    depthArr[1] = 0;
    valueToParent[1] = 0;

    dfs1_iterative(1);

    currentPos = 0;
    dfs2_iterative(1);

    buildSeg(1, 1, n);

    // 쿼리 수 입력
    int m;
    scanf("%d", &m);

    while (m--)
    {
        int type;
        scanf("%d", &type);

        if (type == 1)
        {
            // 1 i c
            // i번째 간선의 가중치를 c로 변경
            int idx, c;
            scanf("%d %d", &idx, &c);

            int u = edgeU[idx];
            int v = edgeV[idx];

            // 더 깊은 정점을 찾기. 간선 값은 더 깊은 정점 위치에 저장되어 있다.
            int deeper;
            if (depthArr[u] > depthArr[v])
            {
                deeper = u;
            }
            else
            {
                deeper = v;
            }

            // 세그먼트 트리에서 해당 위치 갱신
            updateSeg(1, 1, n, posInBase[deeper], c);
        }
        else
        {
            // 2 u v
            // u-v 경로의 최대 간선값 출력
            int u, v;
            scanf("%d %d", &u, &v);

            int ans = queryPath(u, v, n);
            printf("%d\n", ans);
        }
    }

    return 0;
}