// 스택
#include <stdio.h>
#include <string.h>

int stack[10000];
int top = -1; //-1은 아무것도 없다는 의미

int main()
{
    int N; // 주어질 명령 개수
    scanf("%d", &N);

    while (N--)
    {
        char cmd[10];
        scanf("%s", cmd);

        if (strcmp(cmd, "push") == 0)
        { // strcmp함수:문자열비교함수 문자열 같으면 결과 0, 다르면 !=0
            // x를 스택에 넣는 기능
            int x;
            scanf("%d", &x);
            stack[++top] = x;
        }
        else if (strcmp(cmd, "pop") == 0)
        {
            // 맨 위에 있는 값 꺼내기(없애기)
            if (top == -1)
                printf("-1\n");
            else
                printf("%d\n", stack[top--]);
        }
        else if (strcmp(cmd, "size") == 0)
        {
            // 개수 세기
            printf("%d\n", top + 1);
        }
        else if (strcmp(cmd, "empty") == 0)
        { // 비었으면 1 내놓는
            printf("%d\n", top == -1);
        }
        else if (strcmp(cmd, "top") == 0)
        { // 맨 위 값 보는
            if (top == -1)
                printf("-1\n");
            else
                printf("%d\n", stack[top]);
        }
    }
}
