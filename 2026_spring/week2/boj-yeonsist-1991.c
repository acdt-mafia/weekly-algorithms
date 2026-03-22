#include <stdio.h>

typedef struct
{
    char left;  // 노드가 전부 A,B,C같은 대문자 문자이므로 char
    char right; // 포인터 연결구조로 안 해도 됨.
} Node;

Node tree[26]; // A~Z 저장 tree[0] = A, tree[1] = B// 'B' - 'A' = 1 // tree[root-'A'] <- 어떤 노드가 root일 때 그 노드 정보를 이렇게 접근할 수 있다.

void preorder(char root)
{
    if (root == '.')
        return; // 자식이 없으면 종료

    printf("%c", root);               // 루트 출력
    preorder(tree[root - 'A'].left);  // 왼쪽 순회
    preorder(tree[root - 'A'].right); // 오른쪽 순회
}

void inorder(char root)
{
    if (root == '.')
        return;

    inorder(tree[root - 'A'].left);
    printf("%c", root);
    inorder(tree[root - 'A'].right);
}

void postorder(char root)
{
    if (root == '.')
        return;

    postorder(tree[root - 'A'].left);
    postorder(tree[root - 'A'].right);
    printf("%c", root);
}

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        char root, left, right;
        scanf(" %c %c %c", &root, &left, &right);

        tree[root - 'A'].left = left;
        tree[root - 'A'].right = right;
    }

    preorder('A');
    printf("\n");

    inorder('A');
    printf("\n");

    postorder('A');
    printf("\n");

    return 0;
}