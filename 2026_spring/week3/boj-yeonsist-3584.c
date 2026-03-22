#include <stdio.h>
#include <string.h>

int parent[10001];
int visited[10001];

int main()
{
    int T; // test 케이스 개수
    scanf("%d", &T);

    while (T--)
    {
        int N; // 노드 몇 개 일지 정하기
        scanf("%d", &N);

        memset(parent, 0, sizeof(parent));
        memset(visited, 0, sizeof(visited));

        for (int i = 0; i < N - 1; i++)
        { // 부모 자식 관계 정하는 것이므로 노드 개수 아니고 간선 개수만큼 해야 함.
            int A, B;
            scanf("%d %d", &A, &B);
            parent[B] = A; // B의 부모는 A. 특정노드의 부모는 무조건 한 사람이므로 부모를 배열 라벨링에 넣어야.
        }

        // 확인할 두 노드 입력
        int x, y;
        scanf("%d %d", &x, &y);

        // x 조상 체크
        while (x != 0)
        { // root를 알 필요없다고 함. why? 루트의 부모는 0이라 생각하면 됨. 지정을 안했으니까! 처음에 0으로 초기화 했으니까.
            visited[x] = 1;
            x = parent[x]; // 부모로 업데이트 해서 쭉쭉 따라 올라가기
        }

        while (y != 0)
        {
            if (visited[y] == 1)
            { // x 부모들은 다 1로 표시가 되어 있음 그러다 y랑 젤 처음 부모 겹치는 곳에서의 y가 LCA.
                printf("%d\n", y);
                break;
            }
            y = parent[y];
        }
    }
}