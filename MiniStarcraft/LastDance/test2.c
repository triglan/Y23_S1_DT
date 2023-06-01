#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

typedef struct info {
	char name[20], pos[20];
	int hp, atk, def;
	struct info *next;
}Info;
typedef struct tree {
	char name[20], pos[20];
	int hp, atk, def;
	struct tree* left;
	struct tree* right;
}Tree;

void MakeSL(Info* head);
void MakeBT(Info* head, Tree** node);
Tree* createNode(char* pos, char* name, int hp, int atk, int def);
Tree* InsertBT(char* pos, char* name, int hp, int atk, int def, Tree* node);
Tree* DeleteBT(char* name, Tree* node);
Tree* searchMin(Tree* node);
void PrintALL(Tree* node);
void SearchByNameBT(char* name, Tree* node);

int main() {
	int hp, atk, def;
	char name[20], pos[20], order;

	Info* head = (Info*)malloc(sizeof(Info));
	head->next = NULL;
	Tree* node = NULL;

	clock_t start, end;

	start = clock();
	MakeSL(head);
	MakeBT(head, &node);
	end = clock();
	printf("%lf초 걸림.\n", (double)(end - start) / CLOCKS_PER_SEC);

	while (1) {
		printf("명령어 : ");
		scanf_s(" %c", &order);
		system("cls");
		switch (order)
		{
		case '1':
			PrintALL(node);
			break;
		case '2':
			scanf_s("%s %s %d %d %d", &pos, sizeof(pos), &name, sizeof(name), &hp, &atk, &def);
			InsertBT(pos, name, hp, atk, def, node);
			break;
		case '3':
			scanf_s("%s", &name, sizeof(name));
			DeleteBT(name, node);
			break;
		case '4':
			scanf_s("%s", &name, sizeof(name));
			SearchByNameBT(name, node);
			break;
		default:
			break;
		}
	}
}
void MakeSL(Info* head) {
	FILE* fp;
	fp = fopen("temp.txt", "r");

	while (!feof(fp)) {
		Info* p = (Info*)malloc(sizeof(Info));
		fscanf_s(fp, "%s %s %d %d %d", &p->pos, sizeof(p->pos), &p->name, sizeof(p->name), &p->hp, &p->atk, &p->def);

		p->next = head->next;
		head->next = p;
	}
	fclose(fp);
}
void MakeBT(Info* head, Tree** node) {
	Info* p = head->next;

	while (1) {
		if (p == NULL)
			return;
		*node = InsertBT(p->pos, p->name, p->hp, p->atk, p->def, *node);
		p = p->next;
	}
}
Tree* createNode(char* pos, char* name, int hp, int atk, int def) {
	Tree* node = (Tree*)malloc(sizeof(Tree));
	strcpy(node->pos, pos);
	strcpy(node->name, name);
	node->hp = hp;
	node->atk = atk;
	node->def = def;
	node->left = NULL;
	node->right = NULL;
	return node;
}
Tree* InsertBT(char* pos, char* name, int hp, int atk, int def, Tree* node) {
	if (node == NULL)
		return createNode(pos, name, hp, atk, def);
	if (strcmp(node->name, name) > 0)
		node->left = InsertBT(pos, name, hp, atk, def, node->left);
	else
		node->right = InsertBT(pos, name, hp, atk, def, node->right);
	return node;
}
Tree* DeleteBT(char* name, Tree* node) {
	if (node == NULL) {
		printf("NULL\n");
		return;
	}
	if (strcmp(node->name, name) > 0)
		node->left = DeleteBT(name, node->left);
	else if(strcmp(node->name, name) < 0)
		node->right = DeleteBT(name, node->right);
	else {//발견했으면
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
			Tree* temp = searchMin(node->right);
			strcmp(node->pos, temp->pos), strcmp(node->name, temp->name), node->hp = temp->hp, node->atk = temp->atk, node->def = temp->def;
			temp = NULL;
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
	return;
}
void PrintALL(Tree* node) {
	if (node == NULL)
		return;
	PrintALL(node->left);
	printf("%s %s %d %d %d\n", node->pos, node->name, node->hp, node->atk, node->def);
	PrintALL(node->right);
}
void SearchByNameBT(char* name, Tree* node) {
	if (node == NULL) {
		printf("NULL\n");
		return;
	}
	if (strcmp(node->name, name) > 0)
		SearchByNameBT(name, node->left);
	else if (strcmp(node->name, name) < 0)
		SearchByNameBT(name, node->right);
	else {//발견했으면
		printf("%s %s %d %d %d\n", node->pos, node->name, node->hp, node->atk, node->def);
		return;
	}
}