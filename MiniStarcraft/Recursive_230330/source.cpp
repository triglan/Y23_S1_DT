//º¸µåÆÇ Å©±â
#define SIDE 40
#define UPDOWN 20


//¸Ê ±¸Á¶Ã¼
typedef struct
{//hp mp x,y unitID
	char name;
	int HP;
	int MP;

	int x;
	int y;

	int unitID;
}UnitInfo;

//À¯´Ö
UnitInfo unitList[UPDOWN * SIDE + 1];

//À¯´Ö »ý¼º ¼ö
int unitCount = 0;
int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;

//À¯´Ö Á¤º¸
void Unit_H(int x, int y);
void Unit_Q(int x, int y);
void Unit_D(int x, int y);
void Unit_M(int x, int y);
void Unit_T(int x, int y);
void Unit_V(int x, int y);



void MakeUL()
{
	Unit_M(0, 0);
	Unit_M(0, 1);
	Unit_M(0, 2);
	Unit_M(1, 3);
	Unit_M(1, 4);
	Unit_M(0, 5);

	Unit_T(0, 3);
	Unit_T(0, 4);

	Unit_V(1, 2);
	Unit_V(2, 2);


	Unit_H(39, 19);
	Unit_H(39, 18);
	Unit_H(37, 17);
	Unit_H(38, 16);
	Unit_H(38, 15);
	Unit_H(39, 14);

	Unit_Q(39, 17);
	Unit_Q(38, 17);

	Unit_D(39, 16);
	Unit_D(39, 15);
}

void Unit_H(int x, int y)
{
	unitList[unitCount].name = 'H';
	unitList[unitCount].HP = 50;
	unitList[unitCount].MP = 0;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].unitID = HydraCount++;
}

void Unit_Q(int x, int y)
{
	unitList[unitCount].name = 'Q';
	unitList[unitCount].HP = 70;
	unitList[unitCount].MP = 150;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].unitID = QueenCount++;
}

void Unit_D(int x, int y)
{
	unitList[unitCount].name = 'D';
	unitList[unitCount].HP = 60;
	unitList[unitCount].MP = 200;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].unitID = DefilerCount++;

}

void Unit_M(int x, int y)
{
	unitList[unitCount].name = 'M';
	unitList[unitCount].HP = 30;
	unitList[unitCount].MP = 0;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].unitID = MarineCount++;

}

void Unit_T(int x, int y)
{
	unitList[unitCount].name = 'T';
	unitList[unitCount].HP = 120;
	unitList[unitCount].MP = 0;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].unitID = TankCount++;

}

void Unit_V(int x, int y)
{
	unitList[unitCount].name = 'V';
	unitList[unitCount].HP = 80;
	unitList[unitCount].MP = 140;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].unitID = VesselCount++;
}
