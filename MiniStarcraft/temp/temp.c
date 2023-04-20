#include <stdio.h>
#include <stdlib.h>

// ���� ����Ʈ ��� ����ü
struct Info {
    int data;           // ��尡 �����ϴ� ������
    struct Info* next;  // ���� ��带 ����Ű�� ������
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