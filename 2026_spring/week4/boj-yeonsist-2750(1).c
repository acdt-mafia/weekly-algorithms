// 수 정렬하기- 학교에서 배운 버전으로 풀면

#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);

    int arr[1001];
    int num;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &num);
        arr[i] = num;
    }

    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j;
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d\n", arr[i]);
    }
}