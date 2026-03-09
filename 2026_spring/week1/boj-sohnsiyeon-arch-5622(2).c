// 다이얼 좀 더 똑똑하게 풀기
// 배열 매핑

#include <stdio.h>

int main()
{
    char str[16];
    scanf("%s", str);

    int dial[26] = {
        3, 3, 3,
        4, 4, 4,
        5, 5, 5,
        6, 6, 6,
        7, 7, 7,
        8, 8, 8, 8,
        9, 9, 9,
        10, 10, 10, 10};
    scanf("%s", str);

    int time = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        time += dial[str[i] - 'A'];
    }
    printf("%d", time);
    return 0;
}