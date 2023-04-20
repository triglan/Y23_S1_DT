#include <stdio.h>
#include <windows.h>

//º¸µåÆÇ Å©±â
#define SIDE 40
#define UPDOWN 20

#define TERRAN 1
#define ZERG 2

//¸Ê ±¸Á¶Ã¼
struct Info
{//hp mp x,y unitID
	struct Info* next;

	char name;
	int HP;
	int MP;

	int x;
	int y;

	int unitID;
	int team;
};

//À¯´Ö »ý¼º ¼ö
int unitCount = 0;
int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;


int main()
{
	struct Info* head = malloc(sizeof(struct Info));
	head->next = head;
	MakeUL(head);


}




void DisplayMap(struct Info* head)
{
	struct Info* p = head->next;

	char board[UPDOWN][SIDE];
	for (int y = 0; y < UPDOWN; y++)
	{
		for (int x = 0; x < SIDE; x++)
		{
			board[y][x] = '+';
		}
	}
	while (p != head)
	{
		board[p->y][p->x] = p->name;
		p = p->next;
	}
	for (int y = 0; y < UPDOWN; y++)
	{
		for (int x = 0; x < SIDE; x++)
		{
			printf("%c", board[y][x]);
		}
		printf("\n");
	}

}

void Show_UL_SL(struct Info* head)
{
	struct Info* p = head->next;

	while (p != head)
	{
		printf("name : %c // HP : %d // MP : %d // ÁÂÇ¥ : (%d,%d) // ID : %c%03d\n",
			p->name, p->HP, p->MP, p->x, p->y, p->name, p->unitID);
		p = p->next;
	}
}

void SelectUL_SL(int x, int y, struct Info* head)
{
	struct Info* p = head->next;

	while (p != head)
	{
		if (p->x == x && p->y == y)
		{
			printf("name : %c // HP : %d // MP : %d // ÁÂÇ¥ : (%d,%d) // ID : %c%03d\n",
				p->name, p->HP, p->MP, p->x, p->y, p->name, p->unitID);
			return;
		}
		p = p->next;
	}
}
void Produce_UL_R(char unit, int x, int y, int hp, int mp, struct Info* head)
{
	Unit(unit, x, y, hp, mp, head);
}
void Destroy_UL_SL(int x, int y, struct Info* head)
{
	struct Info* p = head;
	struct Info* t = head;
	while (p->next != head)
	{
		if (p->next->x == x && p->next->y == y)
		{
			t = p->next;
			p->next = p->next->next;
			free(t);
			break;
		}
		p = p->next;
	}
}


void MakeUL(struct Info* head)
{
	Unit('m', 0, 0, 25, 0, head);
	Unit('m', 0, 1, 20, 0, head);
	Unit('m', 0, 2, 30, 0, head);
	Unit('m', 1, 3, 15, 0, head);
	Unit('m', 1, 4, 30, 0, head);
	Unit('m', 0, 5, 27, 0, head);

	Unit('t', 0, 3, 120, 0, head);
	Unit('t', 0, 4, 50, 0, head);

	Unit('v', 1, 2, 80, 0, head);
	Unit('v', 2, 2, 75, 0, head);

	Unit('h', 39, 19, 37, 0, head);
	Unit('h', 39, 18, 47, 0, head);
	Unit('h', 37, 17, 30, 0, head);
	Unit('h', 38, 16, 20, 0, head);
	Unit('h', 38, 15, 45, 0, head);
	Unit('h', 39, 14, 50, 0, head);

	Unit('q', 39, 17, 35, 0, head);
	Unit('q', 38, 17, 70, 0, head);

	Unit('d', 39, 16, 15, 0, head);
	Unit('d', 39, 15, 40, 0, head);

}
void Unit(char unit, int x, int y, int hp, int mp, struct Info* head)
{
	struct Info* p = malloc(sizeof(struct Info));

	if (unit == 'h') {
		p->name = 'H';
		p->unitID = HydraCount++;
		p->team = ZERG;
	}
	else if (unit == 'q')
	{
		p->name = 'Q';
		p->unitID = QueenCount++;
		p->team = ZERG;
	}
	else if (unit == 'd')
	{
		p->name = 'D';
		p->unitID = DefilerCount++;
		p->team = ZERG;
	}
	else if (unit == 'm')
	{
		p->name = 'M';
		p->unitID = MarineCount++;
		p->team = TERRAN;
	}
	else if (unit == 't')
	{
		p->name = 'T';
		p->unitID = TankCount++;
		p->team = TERRAN;
	}
	else if (unit == 'v')
	{
		p->name = 'V';
		p->unitID = VesselCount++;
		p->team = TERRAN;
	}
	else
		return;
	p->HP = hp;
	p->MP = mp;
	p->x = x;
	p->y = y;

	p->next = head->next;

	head->next = p;
}