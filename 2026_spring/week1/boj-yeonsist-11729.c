// 하노이탑
// 모르겠어요 와!

// 코딩에서 수학 점화식을 풀 줄이야!

// 근데 산넘어산으로 중간 과정을 넣어야 하는데 어떻게 출력해야 할지 감도 안 옴!

#include <stdio.h>
#include <math.h> //세상에나 제곱 연산자가 기본에 없음.

void hanoi(int n, int from, int via, int to)
{
    if (n == 1)
    {
        printf("%d %d\n", from, to);
        return;
    }
    hanoi(n - 1, from, to, via); // 맨 아래 가장 큰 거 옮기려면 그 위의 n-1개를 먼저 중간 고리로 옮겨야 함.
    printf("%d %d\n", from, to);
    hanoi(n - 1, via, from, to);
}

int main()
{
    int n;
    scanf("%d", &n);

    printf("%d\n", (int)pow(2, n) - 1); // pow 반환형은 double인데 %d로 받으면 오류남. 그래서 (int)씌워줌
    hanoi(n, 1, 2, 3);
}
