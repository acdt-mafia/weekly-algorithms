#include <stdio.h>
#include <string.h>

int main()
{
    char str[101];
    scanf("%s", str);

    int len = strlen(str);

    int n = 0;

    for (int i = 0; i < len / 2; i++)
    {
        if (str[i] == str[len - i - 1])
            n++;
    }

    if (n == len / 2) // ㅋ 그냥 다르면 바로 for문 나오게 하고 싶었는데 생각이 안나서.. 이런 방법을 씀.
        printf("1");
    else
        printf("0");
}