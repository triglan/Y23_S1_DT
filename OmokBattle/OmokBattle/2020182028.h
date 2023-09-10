#pragma once
int board_2020182028[19][19];
typedef struct {
	int x, y, size, shape;
}LINE2018;

//흰돌	 1
//검은돌	-1
#define BLACK -1
#define WHITE 1
//바둑판 크기
#define SIZE 19
#define LINE 37

LINE2018 BestStone_2020182028 = { 0 };
int BanStone_2020182028[19][19];
int Bturn2018_2020182028 = 0, Wturn2028_2020182028 = 0;
int BWcol2028_2020182028_2020182028 = 0, Wcol2028_2020182028 = 0;

void MovingStone_2020182028(int* x, int* y, int color);
void ScanSide_2020182028();


void WhiteAttack_2020182028(int* x, int* y)
{
	MovingStone_2020182028(x, y, WHITE);

}
void WhiteDefence_2020182028(int x, int y)
{
	// 상대가 놓은 돌의 위치를 전달받아서 저장합니다
	board_2020182028[y][x] = BLACK;
}
void BlackAttack_2020182028(int* x, int* y)
{
	MovingStone_2020182028(x, y, BLACK);

}
void BlackDefence_2020182028(int x, int y)
{
	// 상대가 놓은 돌의 위치를 전달받아서 저장합니다
	board_2020182028[y][x] = WHITE;
}

void MovingStone_2020182028(int *x, int *y, int color) {
	int randtemp2018[2] = { 0 };
	
	color = 10 + color;
	while (1) {
		ScanSide_2020182028();
		if (color == BLACK) {
			if (BestStone_2020182028.shape == 0) {//가로
				if (board_2020182028[BestStone_2020182028.y][BestStone_2020182028.x + 1] == 0 && BestStone_2020182028.y < 19 && BestStone_2020182028.x + 1 < 19 && BestStone_2020182028.y > 0 && BestStone_2020182028.x + 1 > 0) {
					board_2020182028[BestStone_2020182028.y][BestStone_2020182028.x + 1] = BLACK;
					*x = BestStone_2020182028.x + 1, *y = BestStone_2020182028.y;
				}
				else if (board_2020182028[BestStone_2020182028.y][BestStone_2020182028.x - BestStone_2020182028.size - 1] == 0 && BestStone_2020182028.y < 19 && BestStone_2020182028.x - BestStone_2020182028.size - 1 < 19 && BestStone_2020182028.y > 0 && BestStone_2020182028.x - BestStone_2020182028.size - 1 > 0) {
					board_2020182028[BestStone_2020182028.y][BestStone_2020182028.x - BestStone_2020182028.size - 1] = BLACK;
					*x = BestStone_2020182028.x - BestStone_2020182028.size - 1, * y = BestStone_2020182028.y;
				}
				else {
					for (int i = 0; i < BestStone_2020182028.size; i++)
					{
						BanStone_2020182028[BestStone_2020182028.y][BestStone_2020182028.x - i] = 1;
						continue;
					}
				}
			}
			else if (BestStone_2020182028.shape == 1) {//세로
				if (board_2020182028[BestStone_2020182028.y + 1][BestStone_2020182028.x] == 0 && BestStone_2020182028.y + 1 < 19 && BestStone_2020182028.x < 19 && BestStone_2020182028.y + 1 > 0 && BestStone_2020182028.x > 0) {
					board_2020182028[BestStone_2020182028.y + 1][BestStone_2020182028.x] = BLACK;
					*x = BestStone_2020182028.x, * y = BestStone_2020182028.y + 1;
				}
				else if (board_2020182028[BestStone_2020182028.y - BestStone_2020182028.size - 1][BestStone_2020182028.x] == 0 && BestStone_2020182028.y - BestStone_2020182028.size - 1 < 19 && BestStone_2020182028.x < 19 && BestStone_2020182028.y - BestStone_2020182028.size - 1 > 0 && BestStone_2020182028.x > 0) {
					board_2020182028[BestStone_2020182028.y - BestStone_2020182028.size - 1][BestStone_2020182028.x] = BLACK;
					*x = BestStone_2020182028.x, * y = BestStone_2020182028.y - BestStone_2020182028.size - 1;
				}
				else {
					for (int i = 0; i < BestStone_2020182028.size; i++)
					{
						BanStone_2020182028[BestStone_2020182028.y - i][BestStone_2020182028.x] = 1;
						continue;
					}
				}
			}
			else if (BestStone_2020182028.shape == 2) {//우하향
				if (board_2020182028[BestStone_2020182028.x + BestStone_2020182028.y + 1][BestStone_2020182028.x + 1] == 0 && BestStone_2020182028.x + BestStone_2020182028.y + 1 < 19 && BestStone_2020182028.x + 1 < 19 && BestStone_2020182028.x + BestStone_2020182028.y + 1 > 0 && BestStone_2020182028.x + 1> 0) {
					board_2020182028[BestStone_2020182028.x + BestStone_2020182028.y + 1][BestStone_2020182028.x + 1] = BLACK;
					*x = BestStone_2020182028.x + 1, * y = BestStone_2020182028.x + BestStone_2020182028.y + 1;
				}
				else if (board_2020182028[BestStone_2020182028.x + BestStone_2020182028.y - BestStone_2020182028.size - 1][BestStone_2020182028.x - BestStone_2020182028.size - 1] == 0 && BestStone_2020182028.y < 19 && BestStone_2020182028.x < 19 && BestStone_2020182028.y > 0 && BestStone_2020182028.x > 0) {
					board_2020182028[BestStone_2020182028.x + BestStone_2020182028.y - BestStone_2020182028.size - 1][BestStone_2020182028.x - BestStone_2020182028.size - 1] = BLACK;
					*x = BestStone_2020182028.x - BestStone_2020182028.size - 1, * y = BestStone_2020182028.x + BestStone_2020182028.y - BestStone_2020182028.size - 1;
				}
				else {
					for (int i = 0; i < BestStone_2020182028.size; i++)
					{
						BanStone_2020182028[BestStone_2020182028.x + BestStone_2020182028.y - i][BestStone_2020182028.x - 1] = 1;
						continue;
					}
				}
			}
			else if (BestStone_2020182028.shape == 3) {//우상향
				if (board_2020182028[BestStone_2020182028.y - BestStone_2020182028.x + 1][BestStone_2020182028.x + 1] == 0) {
					board_2020182028[BestStone_2020182028.y - BestStone_2020182028.x + 1][BestStone_2020182028.x + 1] = BLACK;
					*x = BestStone_2020182028.x + 1, * y = BestStone_2020182028.y - BestStone_2020182028.x + 1;
				}
				else if (board_2020182028[BestStone_2020182028.y - BestStone_2020182028.x - BestStone_2020182028.size - 1][BestStone_2020182028.x - BestStone_2020182028.size - 1] == 0) {
					board_2020182028[BestStone_2020182028.y - BestStone_2020182028.x - BestStone_2020182028.size - 1][BestStone_2020182028.x - BestStone_2020182028.size - 1] = BLACK;
					*x = BestStone_2020182028.x - BestStone_2020182028.size - 1, * y = BestStone_2020182028.y - BestStone_2020182028.x - BestStone_2020182028.size - 1;
				}
				else {
					for (int i = 0; i < BestStone_2020182028.size; i++)
					{
						BanStone_2020182028[BestStone_2020182028.y - BestStone_2020182028.x - i][BestStone_2020182028.x - i] = 1;
						continue;
					}
				}
			}
			else {
				while (1) {
					randtemp2018[1] = rand() % 19, randtemp2018[0] = rand() % 19;
					if (board_2020182028[randtemp2018[1]][randtemp2018[0]] == 0) {
						board_2020182028[randtemp2018[1]][randtemp2018[0]] = BLACK;
						*x = randtemp2018[0], * y = randtemp2018[1];
						break;
					}
				}
			}
		}
		else if(color == WHITE) {
			if (BestStone_2020182028.shape == 0) {//가로
				if (board_2020182028[BestStone_2020182028.y][BestStone_2020182028.x + 1] == 0) {
					board_2020182028[BestStone_2020182028.y][BestStone_2020182028.x + 1] = WHITE;
					*x = BestStone_2020182028.x + 1, *y = BestStone_2020182028.y;
				}
				else if (board_2020182028[BestStone_2020182028.y][BestStone_2020182028.x - BestStone_2020182028.size - 1] == 0) {
					board_2020182028[BestStone_2020182028.y][BestStone_2020182028.x - BestStone_2020182028.size - 1] = WHITE;
					*x = BestStone_2020182028.x - BestStone_2020182028.size - 1, * y = BestStone_2020182028.y;
				}
				else {
					for (int i = 0; i < BestStone_2020182028.size; i++)
					{
						BanStone_2020182028[BestStone_2020182028.y][BestStone_2020182028.x - i] = 1;
						continue;
					}
				}
			}
			else if (BestStone_2020182028.shape == 1) {//세로
				if (board_2020182028[BestStone_2020182028.y + 1][BestStone_2020182028.x] == 0) {
					board_2020182028[BestStone_2020182028.y + 1][BestStone_2020182028.x] = WHITE;
					*x = BestStone_2020182028.x, * y = BestStone_2020182028.y + 1;
				}
				else if (board_2020182028[BestStone_2020182028.y - BestStone_2020182028.size - 1][BestStone_2020182028.x] == 0) {
					board_2020182028[BestStone_2020182028.y - BestStone_2020182028.size - 1][BestStone_2020182028.x] = WHITE;
					*x = BestStone_2020182028.x, * y = BestStone_2020182028.y - BestStone_2020182028.size - 1;
				}
				else {
					for (int i = 0; i < BestStone_2020182028.size; i++)
					{
						BanStone_2020182028[BestStone_2020182028.y - i][BestStone_2020182028.x] = 1;
						continue;
					}
				}
			}
			else if (BestStone_2020182028.shape == 2) {//우하향
				if (board_2020182028[BestStone_2020182028.x + BestStone_2020182028.y + 1][BestStone_2020182028.x + 1] == 0) {
					board_2020182028[BestStone_2020182028.x + BestStone_2020182028.y + 1][BestStone_2020182028.x + 1] = WHITE;
					*x = BestStone_2020182028.x + 1, * y = BestStone_2020182028.x + BestStone_2020182028.y + 1;
				}
				else if (board_2020182028[BestStone_2020182028.x + BestStone_2020182028.y - BestStone_2020182028.size - 1][BestStone_2020182028.x - BestStone_2020182028.size - 1] == 0) {
					board_2020182028[BestStone_2020182028.x + BestStone_2020182028.y - BestStone_2020182028.size - 1][BestStone_2020182028.x - BestStone_2020182028.size - 1] = WHITE;
					*x = BestStone_2020182028.x - BestStone_2020182028.size - 1, * y = BestStone_2020182028.x + BestStone_2020182028.y - BestStone_2020182028.size - 1;
				}
				else {
					for (int i = 0; i < BestStone_2020182028.size; i++)
					{
						BanStone_2020182028[BestStone_2020182028.x + BestStone_2020182028.y - i][BestStone_2020182028.x - 1] = 1;
						continue;
					}
				}
			}
			else if (BestStone_2020182028.shape == 3) {//우상향
				if (board_2020182028[BestStone_2020182028.y - BestStone_2020182028.x + 1][BestStone_2020182028.x + 1] == 0) {
					board_2020182028[BestStone_2020182028.y - BestStone_2020182028.x + 1][BestStone_2020182028.x + 1] = WHITE;
					*x = BestStone_2020182028.x + 1, * y = BestStone_2020182028.y - BestStone_2020182028.x + 1;
				}
				else if (board_2020182028[BestStone_2020182028.y - BestStone_2020182028.x - BestStone_2020182028.size - 1][BestStone_2020182028.x - BestStone_2020182028.size - 1] == 0) {
					board_2020182028[BestStone_2020182028.y - BestStone_2020182028.x - BestStone_2020182028.size - 1][BestStone_2020182028.x - BestStone_2020182028.size - 1] = WHITE;
					*x = BestStone_2020182028.x - BestStone_2020182028.size - 1, * y = BestStone_2020182028.y - BestStone_2020182028.x - BestStone_2020182028.size - 1;
				}
				else {
					for (int i = 0; i < BestStone_2020182028.size; i++)
					{
						BanStone_2020182028[BestStone_2020182028.y - BestStone_2020182028.x - i][BestStone_2020182028.x - i] = 1;
						continue;
					}
				}
			}
			else {
				while (1) {
					randtemp2018[1] = rand() % 19, randtemp2018[0] = rand() % 19;
					if (board_2020182028[randtemp2018[1]][randtemp2018[0]] == 0) {
						board_2020182028[randtemp2018[1]][randtemp2018[0]] = WHITE;
						*x = randtemp2018[0], * y = randtemp2018[1];
						break;
					}
				}
			}
		}
		else if(color == 10 + BLACK){
			while (1) {
				if (board_2020182028[8 - Bturn2018_2020182028][3 + BWcol2028_2020182028_2020182028 + Bturn2018_2020182028] != 0) {
					BWcol2028_2020182028_2020182028++;
					continue;
				}
				break;
			}
			*x = 3 + BWcol2028_2020182028_2020182028 + Bturn2018_2020182028;
			*y = 8 - Bturn2018_2020182028;
			Bturn2018_2020182028++;
		}
		else {
		while (1) {
			if (board_2020182028[8 - Wturn2028_2020182028][3 + Wcol2028_2020182028 + Wturn2028_2020182028] != 0) {
				Wcol2028_2020182028++;
				continue;
			}
			break;
		}
			*x = 13 + Wturn2028_2020182028 - Wcol2028_2020182028;
			*y = 6 + Wturn2028_2020182028;
			Wturn2028_2020182028++;
		}
		break;
	}
}

void ScanSide_2020182028()
{
	int maxb = 0, maxw = 0;
	LINE2018 lineb[LINE] = { 0 }, linew[LINE] = { 0 };
	LINE2018 bestLineb = { 0,0,-1,-1 };
	LINE2018 bestLinew = { 0,0,-1,-1 };
	//우상향 검사
	{
		//초기화
		{
			maxb = 0, maxw = 0;
			for (int i = 0; i < LINE; i++)
			{
				lineb[i] = { 0 };
				linew[i] = { 0 };
			}
		}
		//검사
		for (int y = 0; y < LINE; y++)
		{
			for (int x = 0; x < LINE; x++)
			{
				if (x >= 0 && x < SIZE && y - x >=
					0 && y - x < SIZE)
				{
					if (board_2020182028[y - x][x] == BLACK && BanStone_2020182028[y][x] != 1)
					{
						while (1)
						{
							maxb++;
							x++;
							if (board_2020182028[y - x][x] != BLACK)
							{
								if (lineb[y].size < maxb) {
									lineb[y].x = x, lineb[y].y = y, lineb[y].size = maxb;
								}
								x--;
								break;
							}
						}
					}
					if (board_2020182028[y - x][x] == WHITE && BanStone_2020182028[y][x] != 1)
					{
						while (1)
						{
							maxw++;
							x++;
							if (board_2020182028[y - x][x] != WHITE)
							{
								if (linew[y].size < maxw) {
									linew[y].x = x, linew[y].y = y, linew[y].size = maxw;
								}
								x--;
								break;
							}
						}

					}
				}
				maxb = 0;
				maxw = 0;
			}

		}
		//최대값
		for (int i = 0; i < SIZE; i++)
		{
			if (lineb[i].size > bestLineb.size) {
				bestLineb.size = lineb[i].size;
				bestLineb.x = lineb[i].x;
				bestLineb.y = lineb[i].y;
				bestLineb.shape = 3;
			}
			if (linew[i].size > bestLinew.size) {
				bestLinew.size = linew[i].size;
				bestLinew.x = linew[i].x;
				bestLinew.y = linew[i].y;
				bestLinew.shape = 3;
			}
		}
	}
	//우하향 검사
	{
		//초기화
		{
			maxb = 0, maxw = 0;
			for (int i = 0; i < LINE; i++)
			{
				lineb[i] = { 0 };
				linew[i] = { 0 };
			}
		}
		//검사
		for (int y = 0; y < SIZE; y++)
		{
			for (int x = 0; x < SIZE - y; x++)
			{
				if (board_2020182028[x + y][x] == BLACK)
				{
					while (1)
					{
						maxb++;
						x++;
						if (board_2020182028[x + y][x] != BLACK && BanStone_2020182028[x + y][x] != 1)
						{
							if (lineb[y].size < maxb) {
								lineb[y].x = x, lineb[y].y = y, lineb[y].size = maxb;
							}
							x--;
							break;
						}
					}
				}
				if (board_2020182028[x + y][x] == WHITE)
				{
					while (1)
					{
						maxw++;
						x++;
						if (board_2020182028[x + y][x] != WHITE && BanStone_2020182028[x + y][x] != 1)
						{
							if (linew[y].size < maxw) {
								linew[y].x = x, linew[y].y = y, linew[y].size = maxw;
							}
							x--;
							break;
						}
					}

				}
				maxb = 0;
				maxw = 0;
			}
		}
		//최대값
		for (int i = 0; i < SIZE; i++)
		{
			if (lineb[i].size > bestLineb.size) {
				bestLineb.size = lineb[i].size;
				bestLineb.x = lineb[i].x;
				bestLineb.y = lineb[i].y;
				bestLineb.shape = 2;
			}
			if (linew[i].size > bestLinew.size) {
				bestLinew.size = linew[i].size;
				bestLinew.x = linew[i].x;
				bestLinew.y = linew[i].y;
				bestLinew.shape = 2;
			}
		}
	}
	//가로 검사
	{
		//초기화
		{
			maxb = 0, maxw = 0;
			for (int i = 0; i < LINE; i++)
			{
				lineb[i] = { 0 };
				linew[i] = { 0 };
			}
		}
		//검사
		for (int y = 0; y < SIZE; y++)
		{
			for (int x = 0; x < SIZE; x++)
			{
				if (board_2020182028[y][x] == BLACK && BanStone_2020182028[y][x] != 1)
				{
					while (1)
					{
						maxb++;
						x++;
						if (board_2020182028[y][x] != BLACK)
						{
							if (lineb[y].size < maxb)
							{
								lineb[y].x = x, lineb[y].y = y, lineb[y].size = maxb;
							}
							x--;
							break;
						}
					}
				}
				if (board_2020182028[y][x] == WHITE)
				{
					while (1)
					{
						maxw++;
						x++;
						if (board_2020182028[y][x] != WHITE && BanStone_2020182028[y][x] != 1)
						{
							if (linew[y].size < maxw)
							{
								linew[y].x = x, linew[y].y = y, linew[y].size = maxw;
							}
							x--;
							break;
						}
					}

				}
				maxb = 0;
				maxw = 0;
			}

		}
		//최대값
		for (int i = 0; i < SIZE; i++)
		{
			if (lineb[i].size > bestLineb.size) {
				bestLineb.size = lineb[i].size;
				bestLineb.x = lineb[i].x;
				bestLineb.y = lineb[i].y;
				bestLineb.shape = 0;
			}
			if (linew[i].size > bestLinew.size) {
				bestLinew.size = linew[i].size;
				bestLinew.x = linew[i].x;
				bestLinew.y = linew[i].y;
				bestLinew.shape = 0;
			}
		}
	}
	//세로 검사
	{
		//초기화
		{
			maxb = 0, maxw = 0;
			for (int i = 0; i < LINE; i++)
			{
				lineb[i] = { 0 };
				linew[i] = { 0 };
			}
		}
		//검사
		for (int x = 0; x < SIZE; x++)
		{
			for (int y = 0; y < SIZE; y++)
			{
				if (board_2020182028[y][x] == BLACK && BanStone_2020182028[y][x] != 1)
				{
					while (1)
					{
						maxb++;
						y++;
						if (board_2020182028[y][x] != BLACK)
						{
							if (lineb[x].size < maxb) {
								lineb[y].x = x, lineb[y].y = y, lineb[y].size = maxb;
							}
							y--;
							break;
						}
					}
				}
				if (board_2020182028[y][x] == WHITE && BanStone_2020182028[y][x] != 1)
				{
					while (1)
					{
						maxw++;
						y++;
						if (board_2020182028[y][x] != WHITE)
						{
							if (linew[x].size < maxw) {
								linew[y].x = x, linew[y].y = y, linew[y].size = maxw;
							}
							y--;
							break;
						}
					}

				}
				maxb = 0;
				maxw = 0;
			}

		}
		//최대값
		for (int i = 0; i < SIZE; i++)
		{
			if (lineb[i].size > bestLineb.size) {
				bestLineb.size = lineb[i].size;
				bestLineb.x = lineb[i].x;
				bestLineb.y = lineb[i].y;
				bestLineb.shape = 1;
			}
			if (linew[i].size > bestLinew.size) {
				bestLinew.size = linew[i].size;
				bestLinew.x = linew[i].x;
				bestLinew.y = linew[i].y;
				bestLinew.shape = 1;
			}
		}
	}

	if (bestLineb.size >= bestLinew.size) {
		BestStone_2020182028.size	 = bestLineb.size;
		BestStone_2020182028.x		 = bestLineb.x;
		BestStone_2020182028.y		 = bestLineb.y;
		BestStone_2020182028.shape	 = bestLineb.shape;
	}
	else {
		BestStone_2020182028.size	= bestLinew.size;
		BestStone_2020182028.x		= bestLinew.x;
		BestStone_2020182028.y		= bestLinew.y;
		BestStone_2020182028.shape = bestLinew.shape;
	}
		
}