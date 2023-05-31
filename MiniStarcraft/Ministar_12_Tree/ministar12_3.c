#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include<stdlib.h>
#include<time.h>

typedef struct info {
	int hp, atk, def;
	char name[10], pos[10];
	struct Info *next;
}Info;
typedef struct tree{
	int hp, atk, def;
	char name[10], pos[10];
	struct Tree *left;
	struct Tree *right;
}Tree;

void Make_SL(Info* head);
void Make_BT(Info* head, Tree** node);
void SearchByName_BT(char* name, Tree* node);
Tree* createNode(char* pos, char* name, int hp, int atk, int def);
Tree* Insert_BT(char* pos, char* name, int hp, int atk, int def, Tree* node);
Tree* Delete_BT(char* name, Tree* node);
Tree* searchMin(Tree* node);
void PrintAll_BT(Tree* node);
int main() {
	Info* head = malloc(sizeof(Info));
	head->next = NULL;
	Tree* node = NULL;
	clock_t start;
	clock_t end;

	char order;
	char pos[20], name[20];
	int hp, atk, def;

	start = clock();
	Make_SL(head);
	end = clock();
	printf("연결리스트 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	Make_BT(head, &node);
	end = clock();
	printf("트리 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

	while (1) {
		printf("명령어 1. 삽입 2.삭제 3. 서치 4. 출력: ");
		scanf_s(" %c", &order, 1);
		switch (order) {
		case '1':
			start = clock();
			scanf_s("%s %s %d %d %d", &pos, sizeof(pos), &name, sizeof(name), &hp, &atk, &def);
			Insert_BT(pos, name, hp, atk, def, node);
			end = clock(); 
			printf("입력 경과 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case '2':
			start = clock();
			scanf_s("%s", &name, sizeof(name));
			Delete_BT(name, node);
			end = clock(); 
			printf("삭제 경과 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case '3':
			start = clock();
			scanf_s("%s", &name, sizeof(name));
			SearchByName_BT(name, node);
			end = clock(); 
			printf("서치 경과 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case '4':
			start = clock();
			PrintAll_BT(node);
			end = clock();
			printf("출력(정렬) 경과 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		}

	}
}
FILE* fp;
void Make_SL(Info* head) {
	fp = fopen("DS_Large.txt", "r");
	Info temp;
	int count = 0;
	while (!feof(fp)) {
		Info* p = malloc(sizeof(Info));
		fscanf(fp, "%s %s %d %d %d\n", &temp.pos, &temp.name, &temp.hp, &temp.atk, &temp.def);
		strcpy(p->pos, temp.pos);
		strcpy(p->name, temp.name);
		p->hp = temp.hp;
		p->atk = temp.atk;
		p->def = temp.def;

		count++;
		if (count % 10000 == 0)
			printf("count : %d\n", count);
		p->next = head->next;
		head->next = p;
	}
	fclose(fp);

	Info* current = head->next;
	while (current != NULL) {
		Info* temp = current;
		current = current->next;
		free(temp);
	}
}
void Make_BT(Info* head, Tree** node) {
	Info* p = head->next;
	while (1) {
		if (p == NULL)
			return;
		*node = Insert_BT(p->pos, p->name, p->hp, p->atk, p->def, *node);
		p = p->next;
	}
}
void SearchByName_BT(char* name, Tree* node) {
	if (node == NULL){
		printf("못찾음\n");
		return;
	}
	if (strcmp(node->name, name) > 0) {
		SearchByName_BT(name, node->left);
	}
	else if (strcmp(node->name, name) < 0) {
		SearchByName_BT(name, node->right);
	}
	else {
		printf("%s %s %d %d %d\n", node->pos, node->name, node->hp, node->atk, node->def);
		return;
	}
}
Tree* createNode(char* pos, char* name, int hp, int atk, int def) {
	Tree* node = malloc(sizeof(Tree));
	strcpy(node->name, name);
	strcpy(node->pos, pos);
	node->hp = hp;
	node->atk = atk;
	node->def = def;
	node->left = NULL;
	node->right = NULL;
	return node;
}
Tree* Insert_BT(char* pos, char* name, int hp, int atk, int def, Tree* node) {
	if (node == NULL)
		return createNode(pos, name, hp, atk, def);
	if (strcmp(node->name, name) >= 0) {
		node->left = Insert_BT(pos, name, hp, atk, def, node->left);
	}
	else {
		node->right = Insert_BT(pos, name, hp, atk, def, node->right);
	}
	return node;//??????????
}
Tree* Delete_BT(char* name, Tree* node) {
	if (node == NULL) {
		printf("찾지 못함.\n");
	}
	if (strcmp(node->name, name) > 0) {
		node->left = Delete_BT(name, node->left);
	}
	else if (strcmp(node->name, name) < 0){
		node->right = Delete_BT(name, node->right);
	}
	else {//찾았으면
		if (node->left == NULL) {
			Tree* temp = node->right;
			free(node);
			return temp;
		}
		if (node->right == NULL) {
			Tree* temp = node->left;
			free(node);
			return temp;
		}
		else {
			Tree* temp = searchMin(node->right);
			strcpy(node->name, temp->name), strcpy(node->pos, temp->pos);
			node->atk = temp->atk, node->hp = temp->hp, node->def = temp->def;
			free(temp);
		}
	}
	return node;
}
Tree* searchMin(Tree* node) {
	while (1) {
		if (node->left == NULL)
			return node;
		node = node->left;
	}
}
int count = 0;
void PrintAll_BT(Tree* node) {
	if (node == NULL)
		return;
	count++;

	PrintAll_BT(node->left);
	if(count%10000==0)
		printf("%s %s %d %d %d\n", node->pos, node->name, node->hp, node->atk, node->def);
	PrintAll_BT(node->right);
}