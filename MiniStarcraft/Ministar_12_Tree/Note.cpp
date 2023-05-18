/*
#include <stdio.h>
#include <windows.h>
#include <time.h>

typedef struct Info{
int hp,atk,def,pos[20],name[20]
}
typedef struct Tree{
int hp,atk,def,char pos[20],name[20]
}
FILE *fp;
MakeSL(Info* head)
clock_t start = clock();
fp=fopen("DS_Large.txt", "r")
Info temp;
if(fp == NULL)
return

while(feof(fp)){
Info* p = malloc(sizeof(Info));
fscanf(fp, "%s %s %d %d %d, &temp.pos, &temp.name, temp~~)
strcpy(p->pos, temp.pos)
strcpy(p->name, temp.name
p.hp=temp.pos~~
p->next = head->next
head->next=p
}
fclose(fp);
clock_t end = clock()

Make_BT(



*/