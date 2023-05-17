#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <time.h>

typedef struct info {
	char pos[20];
	char name[20];
	int hp;
	int atk; 
	int def;

	struct Info* next;
}Info;

FILE* fp;

void Make_SL(Info* head);
void PrintAll_SL(Info* head);
void FindTarget_SL(Info* head);

int main()
{
	Info* head = malloc(sizeof(Info));
	head->next = NULL;

	char order;
	Make_SL(head);
	while (1) {
		printf("��ɾ� 1. ��� 2.Ž��(�����̸�) : ");
		scanf_s(" %c", &order, sizeof(order));
		switch (order)
		{
		case '1':
			PrintAll_SL(head);
			break;
		case '2':
			FindTarget_SL(head);
			break;
		default:
			break;
		}
	}
}

void Make_SL(Info* head) {
	clock_t start = clock();

	fp = fopen("DS_Large.txt", "r");
	Info temp = { 0 };
	
	if (fp == NULL) {
		return;
	}

	while (!feof(fp)) {
		Info* p = malloc(sizeof(Info));
		memset(p, 0, sizeof(Info));
		fscanf(fp, "%s %s %d %d %d", &temp.pos, &temp.name, &temp.hp, &temp.atk, &temp.def);

		strcpy(p->pos, temp.pos); 
		strcpy(p->name, temp.name);
		p->hp = temp.hp; 
		p->atk = temp.atk;
		p->def = temp.def;

		p->next = head->next;
		head->next = p;
	}

	fclose(fp);

	clock_t end = clock();
	printf("�Է� ��� �ð� : %lf", (double)(end - start) / CLOCKS_PER_SEC);
}
void PrintAll_SL(Info* head) {
	clock_t start = clock();

	Info *p = head->next;

	while (1) {
		printf("%s %s %d %d %d\n", p->pos, p->name, p->hp, p->atk, p->def);

		for (int i = 0; i < 1000; i++)
		{
			p = p->next;
			if (p == NULL) {
				clock_t end = clock();
				printf("��� ��� �ð� : %lf", (double)(end - start) / CLOCKS_PER_SEC);
				return;
			}
		}
	}


	clock_t end = clock();
	printf("��� ��� �ð� : %lf", (double)(end - start) / CLOCKS_PER_SEC);
}
void FindTarget_SL(Info* head) {
	clock_t start = clock();

	Info* p = head->next;
	char str[20];
	scanf_s(" %s", &str, sizeof(str));

	while (p != NULL) {
		if (strcmp(str, p->name) == 0) {
			printf("%s %s %d %d %d", p->pos, p->name, p->hp, p->atk, p->def);

			clock_t end = clock();
			printf("Ž�� ��� �ð� : %lf", (double)(end - start) / CLOCKS_PER_SEC);
			return;
		}

		p = p->next;
	}


	clock_t end = clock();
	printf("�ش� ������ ã�� ���� : %lf", (double)(end - start) / CLOCKS_PER_SEC);
}