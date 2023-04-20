


//º¸µåÆÇ Å©±â
#define SIDE 40
#define UPDOWN 20

#define TERRAN 1
#define ZERG 2

//¸Ê ±¸Á¶Ã¼
typedef struct
{//hp mp x,y unitID
	char name;
	int HP;
	int MP;

	int x;
	int y;

	int unitID;
	int team;
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
	Unit('m', 0, 0, 25, 0, unitCount);
	Unit('m', 0, 1, 20, 0, unitCount);
	Unit('m', 0, 2, 30, 0, unitCount);
	Unit('m', 1, 3, 15, 0, unitCount);
	Unit('m', 1, 4, 30, 0, unitCount);
	Unit('m', 0, 5, 27, 0, unitCount);

	Unit('t', 0, 3, 120, 0, unitCount);
	Unit('t', 0, 4, 50, 0, unitCount);

	Unit('v', 1, 2, 80, 0, unitCount);
	Unit('v', 2, 2, 75, 0, unitCount);

	Unit('h', 39, 19, 37, 0, unitCount);
	Unit('h', 39, 18, 47, 0, unitCount);
	Unit('h', 37, 17, 30, 0, unitCount);
	Unit('h', 38, 16, 20, 0, unitCount);
	Unit('h', 38, 15, 45, 0, unitCount);
	Unit('h', 39, 14, 50, 0, unitCount);

	Unit('q', 39, 17, 35, 0, unitCount);
	Unit('q', 38, 17, 70, 0, unitCount);

	Unit('d', 39, 16, 15, 0, unitCount);
	Unit('d', 39, 15, 40, 0, unitCount);

}
void Unit(char unit, int x, int y, int hp, int mp, int i)
{
	if (unit == 'h') {
		unitList[i].name = 'H';
		unitList[i].unitID = HydraCount++;
		unitList[i].team = ZERG;
	}
	else if (unit == 'q')
	{
		unitList[i].name = 'Q';
		unitList[i].unitID = QueenCount++;
		unitList[i].team = ZERG;
	}
	else if (unit == 'd')
	{
		unitList[i].name = 'D';
		unitList[i].unitID = DefilerCount++;
		unitList[i].team = ZERG;
	}
	else if (unit == 'm')
	{
		unitList[i].name = 'M';
		unitList[i].unitID = MarineCount++;
		unitList[i].team = TERRAN;
	}
	else if (unit == 't')
	{
		unitList[i].name = 'T';
		unitList[i].unitID = TankCount++;
		unitList[i].team = TERRAN;
	}
	else if (unit == 'v')
	{
		unitList[i].name = 'V';
		unitList[i].unitID = VesselCount++;
		unitList[i].team = TERRAN;
	}
	else
		return;
	unitList[i].HP = hp;
	unitList[i].MP = mp;

	unitList[i].x = x;
	unitList[i].y = y;
	if (i >= unitCount)
		unitCount++;
}