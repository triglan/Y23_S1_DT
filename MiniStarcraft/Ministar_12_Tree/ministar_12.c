#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
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
typedef struct{
	char pos[20];
	char name[20];
	int hp;
	int atk;
	int def;

	struct Tree* left;
	struct Tree* right;
}Tree;

FILE* fp;

void Make_SL(Info* head);
void Make_BT(Info* head, Tree** root);

Tree* createNode(int atk, int def, int hp, char* name, char* pos);
Tree* Insert_BT(int atk, int def, int hp, char* name, char* pos, Tree* root);
Tree* FindMin(Tree* node);
Tree* Delete_BT(Tree* root, char* name);

void SearchByName(Tree* root, char* name);
void InorderTravel(Tree* root);

int count = 0;
int main()
{
	Info* head = malloc(sizeof(Info));
	head->next = NULL;
	Tree* root = NULL;
	clock_t start;
	clock_t end;

	char order;
	Make_SL(head);
	Make_BT(head, &root);

	while (1) {
		printf("명령어 1. 삽입 2.(정렬)출력 3. 서치 4. 제거: ");
		scanf_s(" %c", &order, 1);
		switch (order)
		{
		case '1'://TODO : scanf 받기
			start = clock();
			Insert_BT(10, 20, 30, "KAISA2525", "MID", root);
			end = clock();
			printf("입력 경과 시간 : %lf", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case '2':
			start = clock();
			InorderTravel(root);
			end = clock();
			printf("입력 경과 시간 : %lf", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case '3':
			start = clock();
			SearchByName(root, "KAISA2525");
			end = clock();
			printf("입력 경과 시간 : %lf", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case '4':
			start = clock();
			Delete_BT(root, "KAISA2525");
			end = clock();
			printf("입력 경과 시간 : %lf", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		default:
			break;
		}
	}
}

void Make_SL(Info* head) {
	clock_t start = clock();

	//fp = fopen("DS_Large.txt", "r");
	fp = fopen("temp.txt", "r");
	Info temp = { 0 };

	if (fp == NULL) {
		return;
	}

	while (!feof(fp)) {
		Info* p = malloc(sizeof(Info));
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
	printf("입력 경과 시간 : %lf", (double)(end - start) / CLOCKS_PER_SEC);
}
void Make_BT(Info* head, Tree** root) {
	clock_t start = clock();
	Info* p = head->next;

	while (1) {
		if (p == NULL)
			return;
		*root = Insert_BT(p->atk, p->def, p->hp, p->name, p->pos, *root);
		p = p->next;
	}
}
Tree* createNode(int atk, int def, int hp, char* name, char* pos) {
	clock_t start = clock();

	Tree* newNode = malloc(sizeof(Tree));
	newNode->atk = atk;
	newNode->def = def;
	newNode->hp = hp;
	strcpy(newNode->name, name);
	strcpy(newNode->pos, pos);
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;

	clock_t end = clock();
	printf("출력 경과 시간 : %lf", (double)(end - start) / CLOCKS_PER_SEC);
}//name, pos kaisa MID
Tree* Insert_BT(int atk, int def, int hp, char* name, char* pos, Tree* root) {
	if (root == NULL) {
		return createNode(atk, def, hp, name, pos);
	}
	else {
		if (strcmp(root->name, name) >= 0) {
			root->left = Insert_BT(atk, def, hp, name, pos, root->left);
		}
		else {
			root->right = Insert_BT(atk, def, hp, name, pos, root->right);
		}
	}
	return root;
}
Tree* FindMin(Tree* node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}
Tree* Delete_BT(Tree* root, char *name) {
	if (root == NULL) {
		printf("해당 유닛을 찾을 수 없음\n");
		return root;
	}
	if (strcmp(root->name, name) > 0) {
		root->left = Delete_BT(root->left, name);	
	}
	else if (strcmp(root->name, name) < 0) {
		root->right = Delete_BT(root->right, name);
	}
	else {
		printf("%s %s %d %d %d 유닛을 제거함\n", root->pos, root->name, root->hp, root->atk, root->def);
		if (root->left == NULL) {
			Tree* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			Tree* temp = root->left;
			free(root);
			return temp;
		}
		Tree* temp = FindMin(root->right);
		root->atk = temp->atk, root->def = temp->def, root->hp = temp->hp;
		root->right = Delete_BT(root->right, temp);
		free(temp);
	}
	return root;
}
void SearchByName(Tree* root, char* name) {
	if (root == NULL) {
		printf("해당 유닛을 찾을 수 없음\n");
		return;
	}
	if (strcmp(root->name, name) == 0) {
		printf("%s %s %d %d %d\n", root->pos, root->name, root->hp, root->atk, root->def);
		return;
	}
	else if (strcmp(root->name, name) > 0) {//왼쪽 이름이 더 크면
		SearchByName(root->left, name);
	}
	else {
		SearchByName(root->right, name);
	}
}
void InorderTravel(Tree* root) {
	if (root == NULL)
		return;
	//count++;
	InorderTravel(root->left);
	//if (count % 1000 == 0)
		printf("%s %s %d %d %d\n", root->pos, root->name, root->hp, root->atk, root->def);
	InorderTravel(root->right);
}