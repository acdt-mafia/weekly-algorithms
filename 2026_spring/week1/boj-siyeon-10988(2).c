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
        if (str[i] != str[len - i - 1])
        {
            printf("0");
            return 0; // return 넣으면 바로 끝남!!
        }
    }

    printf("1");
    return 0;
}