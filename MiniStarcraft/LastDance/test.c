#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <time.h>

typedef struct info {
	char pos[20], name[20];
	int hp, atk, def;
	struct info* next;
}Info;
typedef struct tree {
	char pos[20], name[20];
	int hp, atk, def;
	struct tree* left;
	struct tree* right;
}Tree;

void MakeSL(Info* head);
void MakeBT(Tree** node, Info* head);
Tree* InsertBT(char* pos, char* name, int hp, int atk, int def, Tree* node);
Tree* createNode(char* pos, char* name, int hp, int atk, int def);
Tree* DeleteBT(char* name, Tree* node);
Tree* findMin(Tree* node);
void PrintAll(Tree* node);
int main()
{
	Info* head = (Info*)malloc(sizeof(Info));
	head->next = NULL;
	Tree* node = NULL;
	char order;
	char pos[20], name[20];
	int hp, atk, def;

	MakeSL(head);
	MakeBT(&node, head);
	while (1) {
		printf("명령어 1. 삽입 2.삭제 3. 서치 4. 출력: ");
		scanf_s(" %c", &order, 1);
		switch (order) {
		case '1':
			scanf_s("%s %s %d %d %d", &pos, sizeof(pos), &name, sizeof(name), &hp, &atk, &def);
			InsertBT(pos, name, hp, atk, def, node);
			break;
		case '2':
			scanf_s("%s", &name, sizeof(name));
			DeleteBT(name, node);
			break;
		case '3':
			PrintAll(node);
			break;
		}
	}
	printf("test");

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

	printf("Done.\n");
}
void MakeBT(Tree** node, Info* head) {
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
	node->hp = hp, node->atk = atk, node->def = def;
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
		printf("CannotFindEnemy\n");
		return;
	}
	if (strcmp(node->name, name) > 0)
		node->left = DeleteBT(name, node->left);
	else if(strcmp(node->name, name) < 0)
		node->right = DeleteBT(name, node->right);
	else {
		if (node->left == NULL) {
			Tree* temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL) {
			Tree* temp = node->right;
			free(node);
			return temp;
		}
		else {
			Tree* temp = findMin(node->right);
			strcpy(node->pos, temp->pos), strcpy(node->name, temp->name);
			node->hp = temp->hp, node->atk = temp->atk, node->def = temp->def;
			temp = NULL;
		}
	}
	return node;
}
Tree* findMin(Tree* node) {
	while (1) {
		if (node->left == NULL)
			return node;
		node = node->left;
	}
}
void PrintAll(Tree* node) {
	if (node == NULL)
		return;

	PrintAll(node->left);
	printf("%s %s %d %d %d\n", node->pos, node->name, node->hp, node->atk, node->def);
	PrintAll(node->right);
}