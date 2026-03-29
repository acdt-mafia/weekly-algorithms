// 수 정렬하기 - 내가 익숙한 버전

#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);

    int arr[10001];
    int num;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num);
        arr[i] = num;
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d\n", arr[i]);
    }
}