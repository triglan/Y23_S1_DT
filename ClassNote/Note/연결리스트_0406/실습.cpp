#include <stdio.h>

int main() {
	int *hpp = NULL;
	new = malloc(**);
	new->hp = 100;
	new->mp = 35;
	new->next = NULL;

	//ù �ּҸ� ����Ű�� hpp�� ù �ּҸ� ����Ű�� ��
	hpp = new;

	//���� �� ����
	new = malloc();
	new->hp = 97;
	new->mp = 47;

	//1�� �迭�� �ּҴ� hpp�� �����ϱ� �� new�� �ְ� 
	new->next = hpp;
	hpp = new;
}