#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

typedef struct info {
	int hp, atk, def;
	char name[20], pos[20];
	struct Info* next;
}Info;

typedef struct {
	int hp, atk, def;
	char name[20], pos[20];
	struct Tree* left;
	struct Tree* right;
}Tree;
void Make_SL(Info* head);
void Make_BT(Tree** tree, Info* head);
Tree* createNode(char* pos, char* name, int hp, int atk, int def);
Tree* Insert_BT(char* pos, char* name, int hp, int atk, int def, Tree* tree);
Tree* Delete_BT(char* name, Tree* node);
Tree* findMin(Tree* tree);
void SearchByName_BT(char* name, Tree* node);
void PrintAll_BT(Tree* node);

FILE* fp;
int main()
{
	Info* head = malloc(sizeof(Info));
	head->next = NULL;
	Tree* root = NULL;

	clock_t start;
	clock_t end;

	char order;
	Make_SL(head);
	Make_BT(&root, head);

	while (1) {
		printf("명령어 1. 삽입 2.(정렬)출력 3. 서치 4. 제거: ");
		scanf_s(" %c", &order, 1);
		switch (order)
		{
		case '1'://TODO : scanf 받기
			start = clock();
			Insert_BT("KAISA2525", "MID", 10, 20, 30, root);
			end = clock();
			printf("입력 경과 시간 : %lf", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case '2':
			start = clock();
			PrintAll_BT(root);
			end = clock();
			printf("입력 경과 시간 : %lf", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case '3':
			start = clock();
			SearchByName_BT("KAISA2525", root);
			end = clock();
			printf("입력 경과 시간 : %lf", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case '4':
			start = clock();
			Delete_BT("KAISA2525", root);
			end = clock();
			printf("입력 경과 시간 : %lf", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		default:
			break;
		}
	}
}

void Make_SL(Info* head)
{
	clock_t start = clock();
	fp = fopen("DS_Large.txt", "r");

	Info temp = { 0 };
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
	printf("연결리스트 제작 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}
void Make_BT(Tree** tree, Info* head) {
	Info* p = head->next;
	while (1) {
		if (p == NULL)
			return;
		*tree = Insert_BT(p->pos, p->name, p->hp, p->atk, p->def, *tree);
		p = p->next;
	}
}
Tree* createNode(char* pos, char* name, int hp, int atk, int def) {
	Tree* tree = malloc(sizeof(Info));
	strcpy(tree->name, name);
	strcpy(tree->pos, pos);
	tree->hp = hp;
	tree->atk = atk;
	tree->def = def;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}
Tree* Insert_BT(char* pos, char* name, int hp, int atk, int def, Tree* tree) {
	if (tree == NULL)
		return createNode(pos, name, hp, atk, def);
	if (strcmp(tree->name, name) >= 0) {
		tree->left = Insert_BT(pos, name, hp, atk, def, tree->left);
	}
	else {
		tree->right = Insert_BT(pos, name, hp, atk, def, tree->right);
	}
	return tree;
}
Tree* Delete_BT(char* name, Tree* node) {
	if (node == NULL) {
		printf("해당 유닛이 없음.\n");
		return node;
	}
	if (strcmp(node->name, name) > 0) {
		node->left = Delete_BT(name, node->left);
	}
	else if (strcmp(node->name, name) < 0) {
		node->right = Delete_BT(name, node->right);
	}
	else {
		if (node->left == NULL) {
			Tree* temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL) {
			Tree* temp = node->left;
			free(node);
			return temp;
		}
		else {
			Tree* temp = findMin(node->right);
			node->atk = temp->atk, node->def = temp->def, node->hp = temp->hp;
			node->right = Delete_BT(name, node->right);
			strcpy(node->name, temp->name), strcpy(node->pos, temp->pos);
			free(temp);
		}
	}
	return node;
}
Tree* findMin(Tree* tree) {
	while (tree->left != NULL) {
		tree = tree->left;
	}
	return tree;
}
void SearchByName_BT(char* name, Tree* node) {
	if (node == NULL)
	{
		printf("유닛을 찾을 수 없음\n");
		return;
	}
	if (strcmp(name, node->name) == 0) {
		printf("%s %s %d %d %d\n", node->pos, node->name, node->hp, node->atk, node->def);
		return;
	}
	else if (strcmp(name, node->name) > 0) {
		SearchByName_BT(name, node->right);
	}
	else {
		SearchByName_BT(name, node->left);
	}
}
void PrintAll_BT(Tree* node) {
	if (node == NULL)
		return;
	PrintAll_BT(node->left);
	printf("%s %s %d %d %d\n", node->pos, node->name, node->hp, node->atk, node->def);
	PrintAll_BT(node->right);
}