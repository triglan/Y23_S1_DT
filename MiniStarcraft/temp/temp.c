#include <stdio.h>
#include <stdlib.h>

// 연결 리스트 노드 구조체
struct Info {
    int data;           // 노드가 저장하는 데이터
    struct Info* next;  // 다음 노드를 가리키는 포인터
};

void addFirst(struct Info* target, int data)
{
    struct Info* newNode = malloc(sizeof(struct Info));
    newNode->next = target->next;
    newNode->data = data;

    target->next = newNode;
}

int main()
{
    struct Info* head = malloc(sizeof(struct Info));

    head->next = NULL;

    addFirst(head, 10);
    addFirst(head, 20);
    addFirst(head, 30);

    struct Info* p = head->next;
    while (p != NULL)
    {
        printf("%d\n", p->data);
        p = p->next;
    }
    
}