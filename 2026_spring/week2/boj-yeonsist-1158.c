// 요세푸스 - circular queue로 구현!

#include <stdio.h>
#include <stdlib.h>

typedef struct Queue
{
    int capacity;
    int front;
    int rear;
    int size;
    int *data;
} Queue;

void initQueue(Queue *q, int capacity)
{
    q->capacity = capacity;
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->data = (int *)malloc(capacity * sizeof(int));
    if (q->data == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
    }
}

// void printQueue(Queue *q)
// {
//     printf("<");
//     for (i =0; i<q->size; i++){
//         printf("%d, ", q->data[(q->front + i) % q->capacity].key);
//     }
//     printf(">");
// }
// 이렇게 하면 제거된 사람 모으는 큐 따로 만들어야 함
// 이거 대신 main 에서 dequeue의 return item으로 출력 만들면 한 번에 끝낼 수 있따

void enqueue(Queue *q, int element)
{
    q->data[q->rear] = element;
    q->rear = (q->rear + 1) % q->capacity; // rear 값 업데이트
    q->size++;
}

int dequeue(Queue *q)
{
    int item = q->data[q->front];
    q->front = (q->front + 1) % q->capacity; // front 값 업데이트
    q->size--;
    return item;
}

int isEmpty(Queue *q)
{
    return q->size == 0;
}

void freeQueue(Queue *q)
{
    free(q->data);
}

int main()
{
    int N, K;
    int i;

    scanf("%d %d", &N, &K);

    // N명을 저장할 원형 큐 생성
    Queue q;
    initQueue(&q, N);

    for (int i = 1; i < N + 1; i++)
    {
        enqueue(&q, i); // N까지 q에 넣기
    }

    // //제거된 사람 순서대로 저장할 큐
    // Queue avoid;
    // initQueue(&avoid, N);

    printf("<");
    while (!isEmpty(&q))
    {
        for (int i = 0; i < K - 1; i++)
        { // K-1일일 때까지의 수를 뒤로 보내기
            int moved = dequeue(&q);
            enqueue(&q, moved);
        }
        int removed = dequeue(&q); // 이게 없어져야 하는 애.

        // 마지막 원소인지 아닌지에 따라 출력 형식 구분
        if (isEmpty(&q))
        {
            printf("%d", removed);
        }
        else
        {
            printf("%d, ", removed);
        }
    }
    printf(">\n");
}