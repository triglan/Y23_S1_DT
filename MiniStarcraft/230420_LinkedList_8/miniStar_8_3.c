#include <stdio.h>
#include <windows.h>

//보드판 크기
#define SIDE 40
#define UPDOWN 20

#define TERRAN 1
#define ZERG 2

//맵 구조체
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


//유닛 생성 수
int unitCount = 0;
int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;

void ShowBoard(struct Info* head);
void ShowUL_SL(struct Info* head);
void SelectUL_SL(int x, int y, struct Info* head);
void ProduceUL_SL(char unit, int x, int y, int hp, int mp, struct Info* head);
void Destroy_UL_SL(int x, int y, struct Info* head);
void FindWeakEnemy_UL_SL(int x, int y, int distance, struct Info* head);
void SortByIDUL_SL(struct Info* head);

int Distance(int x, int y, struct Info* p);
int scanteam(int x, int y, struct Info* head);

void MakeUL(struct Info* head);
void Unit(char unit, int x, int y, int hp, int mp, struct Info* head);
void UnitID(char unit, int x, int y, int hp, int mp, int id, struct Info* head);


int main()
{
	//단일 환형 연결리스트
	struct Info* head = malloc(sizeof(struct Info));
	head->next = head;

	MakeUL(head);

	char order, unit;
	int x, y, hp, mp, distance;

	while (1)
	{
		ShowBoard(head);
		printf("명령어 1 : Show 2 : Select(x,y) 3 : Produce(unit,x,y,hp,mp) 4 : Destroy(x,y) \n5 : FindWeakEnemy(x,y,distance) 6 : SortByIDUL_SL q : 종료 : ");
		scanf_s(" %c", &order, 1);
		system("cls");
		switch (order)
		{
		case '1':
			ShowUL_SL(head);
			break;
		case '2':
			scanf_s("%d %d", &x, &y);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
			{
				printf("잘못된 값.\n");
				break;
			}
			SelectUL_SL(x, y, head);
			break;
		case '3':
			scanf_s(" %c %d %d %d %d", &unit, 1, &x, &y, &hp, &mp);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN || hp < 0 || mp < 0)
			{
				printf("잘못된 값.\n");
				break;
			}
			if (unit == 'h' || unit == 'q' || unit == 'm' || unit == 'd' || unit == 't' || unit == 'v')
			{
				ProduceUL_SL(unit, x, y, hp, mp, head);
			}
			else
				printf("잘못된 값.\n");
			break;
		case '4':
			scanf_s("%d %d", &x, &y);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
			{
				printf("잘못된 값.\n");
				break;
			}
			Destroy_UL_SL(x, y, head);
			break;
		case '5':
			scanf_s("%d %d %d", &x, &y, &distance);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN || distance < 0)
			{
				printf("잘못된 값.\n");
				break;
			}
			FindWeakEnemy_UL_SL(x, y, distance, head);
			break;
		case '6':
			SortByIDUL_SL(head);
			break;
		case 'q':
			return;
		default:
			printf("잘못된 값.\n");
			break;
		}
	}
}

char board[UPDOWN][SIDE];
void ShowBoard(struct Info* head)
{
	struct Info* p = head->next;
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
void ShowUL_SL(struct Info* head)
{
	struct Info* p = head->next;

	while (p != head)
	{
		printf("name : %c HP : %d MP : %d (%d,%d) unitID : %c%03d\n", p->name, p->HP, p->MP, p->x, p->y, p->name, p->unitID);
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
			printf("선택 유닛 : name : %c HP : %d MP : %d (%d,%d) unitID : %c%03d\n", p->name, p->HP, p->MP, p->x, p->y, p->name, p->unitID);
			return;
		}
		p = p->next;
	}
}
void ProduceUL_SL(char unit, int x, int y, int hp, int mp, struct Info* head)
{
	struct Info* p = head->next;
	while (p != head)
	{
		if (p->x == x && p->y == y)
		{
			printf("이미 유닛이 있는 땅!\n");
			return;
		}
		p = p->next;
	}
	Unit(unit, x, y, hp, mp, head);
}
void Destroy_UL_SL(int x, int y, struct Info* head)
{
	struct Info* p = head;
	while (p->next != head)
	{
		if (p->next->x == x && p->next->y == y)
		{
			printf("(%d,%d)좌표의 유닛 제거\n", x, y);
			p->next = p->next->next;

			return;
		}
		p = p->next;
	}
}
void FindWeakEnemy_UL_SL(int x, int y, int distance, struct Info* head)
{
	int minHP = 1000000;
	struct Info Enemy[100];
	int minCount = 0;
	struct Info* p = head->next;
	while (p != head)
	{//적이면서 거리 내에 잇으면서 가장 HP가 작은
		if (Distance(x, y, p) < distance && p->team != scanteam(x, y, head))
		{
			if (p->HP < minHP)
			{
				minCount = 0;
				Enemy[minCount++] = *p;
				minHP = p->HP;
			}
			else if (p->HP == minHP)
			{
				Enemy[minCount++] = *p;
			}
		}
		p = p->next;
	}

	for (int i = 0; i < minCount; i++)
	{
		printf("약한 적 : name : %c HP : %d MP : %d (%d,%d) unitID : %c%03d\n", Enemy[i].name, Enemy[i].HP, Enemy[i].MP, Enemy[i].x, Enemy[i].y, Enemy[i].name, Enemy[i].unitID);
	}

}
void SortByIDUL_SL(struct Info* head)
{
	struct Info* p = head->next;
	struct Info sort[800];
	int count = 0;
	while (p != head)
	{
		sort[count].name = p->name;
		sort[count].HP = p->HP;
		sort[count].MP = p->MP;
		sort[count].x = p->x;
		sort[count].y = p->y;
		sort[count].team = p->team;
		sort[count].unitID = p->unitID;
		sort[count++].next = p->next;
		p = p->next;
	}
	struct Info temp;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (sort[i].name > sort[j].name)//이름 정렬
			{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
			}
			else if (sort[i].name == sort[j].name)
			{
				if (sort[i].unitID > sort[j].unitID)//ID 정렬
				{
					temp = sort[i];
					sort[i] = sort[j];
					sort[j] = temp;
				}
			}
		}
	}
	head->next = head;
	for (int i = 0; i < count; i++)
	{
		UnitID(sort[i].name, sort[i].x, sort[i].y, sort[i].HP, sort[i].MP, sort[i].unitID, head);
	}
	ShowUL_SL(head);
}

int Distance(int x, int y, struct Info* p)
{
	int a = p->y - y;
	int b = p->x - x;
	if (a > b)
		return a;
	else
		return b;
}
int scanteam(int x, int y, struct Info* head)
{
	struct Info* p = head->next;
	while (p != head)
	{
		if (p->x == x && p->y == y)
			return p->team;
		p = p->next;
	}

	return 0;
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
void UnitID(char unit, int x, int y, int hp, int mp, int id, struct Info* head)
{
	struct Info* p = malloc(sizeof(struct Info));

	if (unit == 'h' || unit == 'H') {
		p->name = 'H';
		p->unitID = id;
		p->team = ZERG;
	}
	else if (unit == 'q' || unit == 'Q')
	{
		p->name = 'Q';
		p->unitID = id;
		p->team = ZERG;
	}
	else if (unit == 'd' || unit == 'D')
	{
		p->name = 'D';
		p->unitID = id;
		p->team = ZERG;
	}
	else if (unit == 'm' || unit == 'M')
	{
		p->name = 'M';
		p->unitID = id;
		p->team = TERRAN;
	}
	else if (unit == 't' || unit == 'T')
	{
		p->name = 'T';
		p->unitID = id;
		p->team = TERRAN;
	}
	else if (unit == 'v' || unit == 'V')
	{
		p->name = 'V';
		p->unitID = id;
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
void Unit(char unit, int x, int y, int hp, int mp, struct Info* head)
{
	struct Info* p = malloc(sizeof(struct Info));

	if (unit == 'h' || unit == 'H') {
		p->name = 'H';
		p->unitID = HydraCount++;
		p->team = ZERG;
	}
	else if (unit == 'q' || unit == 'Q')
	{
		p->name = 'Q';
		p->unitID = QueenCount++;
		p->team = ZERG;
	}
	else if (unit == 'd' || unit == 'D')
	{
		p->name = 'D';
		p->unitID = DefilerCount++;
		p->team = ZERG;
	}
	else if (unit == 'm' || unit == 'M')
	{
		p->name = 'M';
		p->unitID = MarineCount++;
		p->team = TERRAN;
	}
	else if (unit == 't' || unit == 'T')
	{
		p->name = 'T';
		p->unitID = TankCount++;
		p->team = TERRAN;
	}
	else if (unit == 'v' || unit == 'V')
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