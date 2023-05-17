#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <time.h>

typedef struct info{
	char pos[20];
	char name[20];
	int hp, atk, def;
	struct info* next;
}Info;

void Make_SL(Info* head);
void PrintAll_SL(Info* head);
void FindTarget_SL(Info* head);


int main()
{
	Info* head = malloc(sizeof(Info));
	head->next = NULL;
	Make_SL(head);
	char order;
	while (1) {
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
	FILE* fp;
	fp = fopen("DS_Large.txt", "r");
	Info temp = { 0 };

	while (!feof(fp)) {
		Info* p = malloc(sizeof(Info));
		fscanf(fp, "%s %s %d %d %d", &temp.pos, &temp.name, &p->hp, &p->atk, &p->def);
		strcpy(p->pos, temp.pos);
		strcpy(p->name, temp.name);

		p->next = head->next;
		head->next = p;
	}

	fclose(fp);
	clock_t end = clock();
	printf("연결리스트 제작 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}
void PrintAll_SL(Info* head) {
	clock_t start = clock();
	Info* p = head->next;
	int escape = 0;
	while (p != NULL) {
		printf("%s %s %d %d %d\n", p->pos, p->name, p->hp, p->atk, p->def);

		for (int i = 0; i < 100000; i++)
		{
			p = p->next;
			if (p == NULL) {
				escape = 1;
				break;
			}
		}
		if (escape)
			break;
	}
	clock_t end = clock();
	printf("프린트 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}
void FindTarget_SL(Info* head) {
	clock_t start = clock();
	Info* p = head->next;
	char temp[20];
	scanf_s(" %s", &temp, sizeof(temp));


	while (p != NULL) {
		if (strcmp(temp,p->name) == 0) {
			printf("%s %s %d %d %d\n", p->pos, p->name, p->hp, p->atk, p->def);
			break;
		}
		p = p->next;
	}


	clock_t end = clock();
	printf("탐색 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}