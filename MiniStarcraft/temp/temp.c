#include <stdio.h>
#include <windows.h>
typedef struct info {
	int hp;

	struct info* next;
}Info;

typedef struct Tree {
	int hp;

	struct Tree* l;
	struct Tree* r;
};

int main()
{
	

    Info* head= malloc(sizeof(Info));
	head->next = NULL;

	Info* a = malloc(sizeof(Info));
	a->hp = 10;
	a->next = head->next;
	head->next = a;
	
	Info* b = malloc(sizeof(Info));
	b->hp = 20;
	b->next = head->next;
	head->next = b;
	
	Info* c = malloc(sizeof(Info));
	c->hp = 30;
	c->next = head->next;
	head->next = c;
	
	Info* d = malloc(sizeof(Info));
	d->hp = 40;
	d->next = head->next;
	head->next = d;

	Info* e = malloc(sizeof(Info));
	e->hp = 40;
	e->next = head->next;
	head->next = e;

	Info *temp = malloc(sizeof(Info));
	temp = b->next;
	//b->next = dz
	//b->next = d->next;
	//d->next = temp;

	printf("1");
}

