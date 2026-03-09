// 스택을 배우고...
// 풀이 방법: 맨 위(top) 과 맨 아래(인덱스로 표현 가능)이 같다 다르다
// 22: 문자열을 한 글자씩 스택에 넣고 다시 하나씩 꺼내면 문자열의 역순이 된다.
#include <stdio.h>

int main()
{
    char str[10];
    char stack[101];
    int top = -1;

    scanf("%s", str);

    // 문자열 스택에 넣기
    for (int i = 0; str[i] != '\0'; i++)
    {
        stack[++top] = str[i];
    }

    // 스택에서 꺼내며 원래 문자열과 비교
    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = stack[top--];
        if (str[i] != ch)
        {
            printf("0\n");
            return 0;
        }
    }
    printf("1");
    return 0;
}