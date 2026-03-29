// 이진 찾기 - 선형 탐색(내가할줄아는거) 말고 이진 탐색으로 풀기
// 중간값보다 내가 찾는게 작은지 큰지로 반씩 줄여나가는 탐색->insertion 필요
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

int binarySearch(int arr[], int n, int target)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (arr[mid] == target)
            return 1;
        else if (arr[mid] > target)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return 0;
}
int main()
{
    int n, m;
    scanf("%d", &n);

    int *arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    qsort(arr, n, sizeof(int), compare); // sort 함수가 c에도 내장으로 있다! 하지만 compare 함수(기준함수)를 만들어줘야 한다. 오름차순, 내림차순 등을 설정해줘야 하기 떄문에
    //(배열 위치 주소, 요소 개수, 요소 크기, 기준 함수)
    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        int target;
        scanf("%d", &target);
        printf("%d\n", binarySearch(arr, n, target));
    }

    free(arr);
    return 0;
}