#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

const int INF = 1000000000;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    /*
        graph[a] = { {b, cost}, {b2, cost2}, ... }

        의미:
        a번 도시에서 갈 수 있는 도시들과 그 비용을 저장
        pair의 first  = 도착 도시
        pair의 second = 비용
    */
    vector<vector<pair<int, int>>> graph(n + 1);

    for (int i = 0; i < m; i++)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        graph[from].push_back({to, cost});
    }

    int start, end;
    cin >> start >> end;

    /*
        dist[i] = 시작 도시에서 i번 도시까지의 현재 최소 비용
    */
    vector<int> dist(n + 1, INF);

    /*
        priority_queue는 기본적으로 "큰 값이 먼저 나오는 최대 힙"이다.
        그런데 우리는 "비용이 작은 것"이 먼저 나와야 하므로
        greater<> 를 써서 최소 힙으로 바꾼다.

        저장 형태:
        (현재까지 비용, 현재 도시 번호)
    */
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>>
        pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int currentCost = pq.top().first;
        int now = pq.top().second;
        pq.pop();

        /*
            이미 더 좋은 경로가 dist[now]에 저장되어 있으면
            지금 꺼낸 정보는 오래된 정보이므로 무시
        */
        if (currentCost > dist[now])
            continue;

        /*
            now 도시에서 갈 수 있는 모든 도시 확인
        */
        for (int i = 0; i < graph[now].size(); i++)
        {
            int next = graph[now][i].first;
            int edgeCost = graph[now][i].second;

            int newCost = currentCost + edgeCost;

            /*
                now를 거쳐 next로 가는 것이 더 싸면 갱신
            */
            if (newCost < dist[next])
            {
                dist[next] = newCost;
                pq.push({newCost, next});
            }
        }
    }

    cout << dist[end] << '\n';

    return 0;
}