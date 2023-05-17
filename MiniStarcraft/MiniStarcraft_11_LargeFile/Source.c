#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <time.h>

typedef struct info{
	char str[10];
	char name[20];
	int hp;
	int atk;
	int def;

	struct info* next;
}Info;

FILE* fp;

void Make_SL(Info* head);
void PrintAll_SL(Info* head);
void SortByName_SL(Info* head);
void FindTarget_SL(Info* head);


int main()
{
	Info* head = malloc(sizeof(Info));
	head->next = NULL;
	Make_SL(head);

	char order;
	while (1) {
		printf("명령어 : 1. Print 2. SortByName 3. FindTarget\n");
		scanf_s(" %c", &order, sizeof(order));
		switch (order)
		{
		case '1':
			PrintAll_SL(head);
			break;
		case '2':
			SortByName_SL(head);
			break;
		case '3':
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
	//fp = fopen("savegame.txt", "r");
	if (fp == NULL) {
		printf("Error: file not found\n");
		exit(1);
	}//안열리면 탈출
	Info temp = {0};

	while (!feof(fp)) {
		Info* p = malloc(sizeof(Info));
		fscanf(fp, "%s %s %d %d %d", temp.str, &temp.name, &temp.hp, &temp.atk, &temp.def);

		strcpy(p->str, temp.str);
		strcpy(p->name, temp.name);
		p->hp = temp.hp, p->atk = temp.atk, p->def = temp.def;

		p->next = head->next;
		head->next = p;
	}

	fclose(fp);
	clock_t end = clock();
	printf("입력 소요 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}
void PrintAll_SL(Info* head) {
	clock_t start = clock();
	Info* p = head->next;
	int escape = 0;
	while (p != NULL) {
		printf("%s %s %d %d %d\n", p->str, p->name, p->hp, p->atk, p->def);
		for (int i = 0; i < 100000; i++)//for문돌려서 1000번뒤로 가라
		{
			if (p->next == NULL) {
				escape = 1;
				break;
			}
			else
				p = p->next;
		}

		if (escape)
			break;
	}

	clock_t end = clock();
	printf("출력 소요 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}
void SortByName_SL(Info* head) {
	clock_t start = clock();

Info* p, *q, *temp;
for (p = head->next; p != NULL; p = p->next){
	for (q = head->next; q != NULL; q= q->next){
		if (strcmp(p, q) > 0) {//p가 크면
			temp = p->next;
			p->next = q->next;
			q->next = temp;
		}
	}
	clock_t end = clock();
	printf("정렬 소요 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

	clock_t end = clock();
	printf("정렬 소요 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void FindTarget_SL(Info* head) {
	clock_t start = clock();
	char str[20];
	scanf_s(" %s", &str, sizeof(str));
	
	Info* p = head->next;
	while (p != NULL) {
		if (strcmp(str, p->name) == 0) {
			printf("%s %s %d %d %d\n", p->str, p->name, p->hp, p->atk, p->def);
			break;
		}

		p = p->next;
		if (p == NULL) {
			printf("ERROR : Cannot Founded\n");
		}
	}
	clock_t end = clock();
	printf("탐색 소요 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}