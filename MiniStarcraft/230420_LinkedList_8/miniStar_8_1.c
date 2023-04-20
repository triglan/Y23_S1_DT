#include <stdio.h>
#include <windows.h>

//보드판 크기
#define SIDE 40
#define UPDOWN 20

#define TERRAN 1
#define ZERG 2

//유닛 구조체
struct Info{//hp mp x,y unitID
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

//유닛 정보
void Unit_H(int x, int y);
void Unit_Q(int x, int y);
void Unit_D(int x, int y);
void Unit_M(int x, int y);
void Unit_T(int x, int y);
void Unit_V(int x, int y);


void DisplayMap_UL(struct Info* head);
void Show_UL_SL(struct Info* head);
void Select_UL_SL(int x, int y, struct Info* head);
void Produce_UL_R(char unit, int x, int y, int hp, int mp, struct Info* head);
void DestroyUL_SL(int x, int y, struct Info* head);
void FindWeakEnemy(int x, int y, int distance, struct Info* head);
void SortByID_UL_SL(struct Info* head);
void EndProgram(struct Info* head);

int Distance(int x, int y, struct Info* p);
int scanteam(int x, int y, struct Info* head);
void swap(struct Info* a, struct Info* b, struct Info* head);

void MakeUL(struct Info* head);
void Unit(char unit, int x, int y, int hp, int mp, struct Info* target);

int main()
{
	struct Info* head = (Info*)malloc(sizeof(struct Info));
	head->next = head;

	MakeUL(head);
	char unit, order;
	int x, y, hp, mp, distance;

	while (1)
	{
		//Show_UL_SL(head);
		DisplayMap_UL(head);
		printf("명령어 Show : 1 // produce : 2 (unit,x,y,hp,mp) // SelectAll : 3 (x1,y1,x2,y2)\nDestroy : 4 (x,y) // FindWeakEnemy : 5(x,y,distance) : ");
		scanf_s(" %c", &order, 1);
		system("cls");
		switch (order)
		{
		case '1':
			Show_UL_SL(head);
			break;
		case '2':
			scanf_s(" %c %d %d %d %d", &unit, 1, &x, &y, &hp, &mp);
			Produce_UL_R(unit, x, y, hp, mp, head);
			break;
		case '3':
			scanf_s("%d %d", &x, &y);
			Select_UL_SL(x, y, head);
			break;
		case '4':
			scanf_s("%d %d", &x, &y);
			DestroyUL_SL(x, y, head);
			break;
		case '5':
			scanf_s("%d %d %d", &x, &y, &distance);
			FindWeakEnemy(x, y, distance, head);
			break;
		case '6':
			SortByID_UL_SL(head);
			break;
		case 'q':
			EndProgram(head);
			return;
		default:
			break;
		}
	}

	
}

char board[UPDOWN][SIDE];
void DisplayMap_UL(struct Info* head)
{
	for (int y = 0; y < UPDOWN; y++)
	{
		for (int x = 0; x < SIDE; x++)
		{
			board[y][x] = '+';
		}
	}
	struct Info* p = head->next;
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
		printf("name : %c // HP : %d // MP : %d // 좌표 : (%d,%d) // ID : %c%03d\n",
			p->name, p->HP, p->MP, p->x, p->y, p->name, p->unitID);
		p = p->next;
	}

}
void Select_UL_SL(int x, int y, struct Info* head)
{
	struct Info* p = head->next;

	while(p != head)
	{
		if (p->x == x && p->y == y)
		{
			printf("찾은 유닛 : name : %c // HP : %d // MP : %d // 좌표 : (%d,%d) // ID : %c%03d\n",
				p->name, p->HP, p->MP, p->x, p->y, p->name, p->unitID);
			break;
		}
		p = p->next;
	}
}
void Produce_UL_R(char unit, int x, int y, int hp, int mp, struct Info* head)
{
	Unit(unit, x, y, hp, mp, head);
}
void DestroyUL_SL(int x, int y, struct Info* head)
{
	struct Info* destroyp = head;
	struct Info* temp = head;

	while (destroyp->next != head)
	{
		if (destroyp->next->x == x && destroyp->next->y == y)
		{
			temp = destroyp->next;
			destroyp->next = destroyp->next->next;
			free(temp);
			break;
		}
		destroyp = destroyp->next;
	}
	
}
void FindWeakEnemy(int x, int y, int distance, struct Info* head)
{
	struct Info* p = head->next;
	int minHP = 10000000;
	int minCount = 0;
	struct Info enemy[100];
	while (p != head)
	{//거리가 더 작으면서 빈땅이 아니면서 HP가 더 적은
		if (Distance(x, y, p) <= distance && p->team != scanteam(x, y, head))
		{
			if (p->HP < minHP)
			{
				minHP = p->HP;
				minCount = 0;
				enemy[minCount++] = *p;
			}
			else if (p->HP == minHP)
				enemy[minCount++] = *p;
		}
		p = p->next;
	}

	for (int i = 0; i < minCount; i++)
	{
		printf("약한 유닛 : name : %c // HP : %d // MP : %d // 좌표 : (%d,%d) // ID : %c%03d\n",
			enemy[i].name, enemy[i].HP, enemy[i].MP, enemy[i].x, enemy[i].y, enemy[i].name, enemy[i].unitID);
	}
}
void SortByID_UL_SL(struct Info* head)
{
	/*
		1. 구조체에 처넣는다.
		2. 
	*/
	struct Info unit[800];
	struct Info* p = head->next;

	int count = 0;
	while (p != head)
	{
		unit[count].name = p->name;
		unit[count].HP = p->HP;
		unit[count].MP = p->MP;
		unit[count].x = p->x;
		unit[count].y = p->y;
		unit[count].team = p->team;
		unit[count].unitID = p->unitID;
		unit[count++].next = p->next;
		
	}
	for (int i = 0; i < count - 1; i++)
	{
		for (int i = 0; i < count - 1; i++)
		{
			if (unit[i].name < unit[i + 1].name)
			{
				struct Info temp = unit[i];
				unit[i] = unit[i + 1];
				unit[i + 1] = temp;
			}
			else if (unit[i].name == unit[i + 1].name)
			{
				if (unit[i].unitID > unit[i + 1].unitID)
				{
					struct Info temp = unit[i];
					unit[i] = unit[i + 1];
					unit[i + 1] = temp;
				}
			}

		}
	}
	//p = head->next;
	head->next = head;
	unitCount = 0;
	HydraCount = 0;
	QueenCount = 0;
	DefilerCount = 0;
	MarineCount = 0;
	TankCount = 0;
	VesselCount = 0;
	for(int i = count - 1; i >= 0; i--)
	{
		Unit(unit[i].name, unit[i].x, unit[i].y, unit[i].HP, unit[i].MP, head);

	}


	//struct Info* s = head->next;
	//struct Info* e = head->next;
	//struct Info* temp = malloc(sizeof(struct Info));;
	//if (e == head)//없을 때
	//{
	//	return;
	//}
	//if (e->next == head->next)//필드에 한명 밖에 없을 때
	//{
	//	printf("유닛 : name : %c // HP : %d // MP : %d // 좌표 : (%d,%d) // ID : %c%03d\n",
	//		e->name, e->HP, e->MP, e->x, e->y, e->name, e->unitID);
	//	return;
	//}
	////닉네임 먼저 검사, 그뒤 아이디 번호 검사
	//while (s->next != head)
	//{
	//	if (s->next->next == head && e->next == head)//s,e가 마지막에서 검사까지 끝내면
	//	{
	//		break;
	//	}
	//	if(e->next != head)//end가 NULL까지 검사
	//		e = e->next;//s = = = = e
	//	else//NULL만나면 start++ end = start
	//	{
	//		s = s->next;
	//		e = s->next;
	//	}
	//	if (s->name > e->name)//이름이 크면
	//	{
	//		swap(s, e, head);
	//		s = head;
	//		e = head->next;
	//	}
	//	else if (s->name == e->name)//ID가 크면
	//	{
	//		if (s->unitID > e->unitID)
	//		{
	//			swap(s, e, head);
	//			s = head;
	//			e = head->next;
	//		}
	//	}
	//}

	Show_UL_SL(head);
}

void swap(struct Info* a, struct Info* b, struct Info* head)
{
	struct Info* aprv = head;
	struct Info* bprv = head;
	struct Info* acur = head;
	struct Info* bcur = head;
	struct Info* temp = head;
	while (aprv->next != a) {//a가 첫번째 원소인 경우 마지막 원소를 가리키게 해야함
		aprv = aprv->next;
	}
	while (bprv->next != b) {
		bprv = bprv->next;
	}
	acur = aprv->next;
	bcur = bprv->next;

	temp = acur->next;
	acur->next = bcur->next;
	bcur->next = temp;

	
	if (aprv == head) {
		head->next = b;
		//bprv가 마지막 원소이어야함
		temp = head;
		while (temp->next == head)
			temp = temp->next;
		bprv = temp;

	}
	else if (bprv == head) {
		head->next = a;
		aprv->next = b;
	}
	else {
		aprv->next = b;
		bprv->next = a;
	}

	Show_UL_SL(head);

}

int Distance(int x, int y, struct Info* p)
{
	int a = abs(x - p->x);
	int b = abs(y - p->y);
	if (a > b)
		return a;
	else
		return b;
}
int scanteam(int x, int y, struct Info* head)
{
	struct Info* p = head->next;
	while (p != NULL)
	{
		if (x == p->x && y == p->y)
			return p->team;
		p = p->next;
	}
	return 0;
}
void EndProgram(struct Info* head)
{
	struct Info* destroyp = head;
	struct Info* temp = head;

	while (destroyp->next != NULL)
	{
		temp = destroyp->next;
		destroyp->next = destroyp->next->next;
		free(temp);
		//destroyp = destroyp->next;
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
	Unit('d', 39, 15, 20, 0, head);
}
void Unit(char unit, int x, int y, int hp, int mp, struct Info* target)
{
	//새 유닛 생성
	struct Info* newUnit = malloc(sizeof(struct Info));
	if (unit == 'h' || unit == 'H') {
		newUnit->name = 'H';
		newUnit->unitID = HydraCount++;
		newUnit->team = ZERG;
	}
	else if (unit == 'q' || unit == 'Q')
	{
		newUnit->name = 'Q';
		newUnit->unitID = QueenCount++;
		newUnit->team = ZERG;
	}
	else if (unit == 'd' || unit == 'D')
	{
		newUnit->name = 'D';
		newUnit->unitID = DefilerCount++;
		newUnit->team = ZERG;
	}
	else if (unit == 'm' || unit == 'M')
	{
		newUnit->name = 'M';
		newUnit->unitID = MarineCount++;
		newUnit->team = TERRAN;
	}
	else if (unit == 't' || unit == 'T')
	{
		newUnit->name = 'T';
		newUnit->unitID = TankCount++;
		newUnit->team = TERRAN;
	}
	else if (unit == 'v' || unit == 'V')
	{
		newUnit->name = 'V';
		newUnit->unitID = VesselCount++;
		newUnit->team = TERRAN;
	}
	else
		return;

	newUnit->HP = hp;
	newUnit->MP = mp;
	newUnit->x = x;
	newUnit->y = y;

	newUnit->next = target->next;

	target->next = newUnit;
}