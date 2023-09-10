#pragma once

int board_2021180006[19][19];

#define BLACK			-1
#define WHITE			 1

#define SIZE			 19

int CntB = 0, CntW = 0, CntAll = 0;
//=============================================================================
// 빈칸 확인 함수
bool BlankCHK(int x, int y) {
	if (board_2021180006[x][y] == -1 || board_2021180006[x][y] == 1) return false;
	else return true;
}

// 총 돌 개수 세는 함수
void CntStone() {
	
	int tempB = 0, tempW = 0;

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j <SIZE; ++j) {

			if (BlankCHK(i, j) == -1)		tempB += 1;
			else if (BlankCHK(i, j) == 1)	tempW += 1;
		}
	}
	
	CntB = tempB;
	CntW = tempW;

	CntAll = tempB + tempW;		//다 더한 값

}

//우하단 대각선 공격 함수
void blackAttack(int* x, int* y) {

	int startX = 13, startY = 17;

	int tempX = 0, tempY = 0;

	for (int i = 0; i < 5; i++)
	{
		tempX = startX + i;
		tempY = startY - i;
		if (BlankCHK(tempX, tempY))
		{
			board_2021180006[tempX][tempY] = BLACK;
			*x = tempX;
			*y = tempY;
			return;
		}
	}

}

void whiteAttack(int* x, int* y) {

	int startX = 13, startY = 0;
	int tempX = 0, tempY = 0;

	for (int i = 0; i < 5; i++)
	{
		tempX = startX - i;
		tempY = startY + i;
		if (BlankCHK(tempX, tempY))
		{
			board_2021180006[tempX][tempY] = WHITE;
			*x = tempX;
			*y = tempY;
			return;
		}
	}

}

void defece(int Iam, int* x, int* y) {

	int BB = 0, WW = 0;
	int temp_BB = 0, temp_WW = 0;
	int IdB = 0, IdW = 0;					// 4번용 좌표저장 변수
	int tempIndex_B = 0, tempIndex_W = 0;	// 좌표저장 임시변수

	if (Iam == -1)	//흑돌일때 돌아가는 코드
	{
		//가로 세로 확인
		for (int i = 0; i < SIZE; i++)
		{
			//한 줄 넘길때 마다 값 초기화
			BB = 0;				WW = 0;
			temp_BB = 0;		temp_WW = 0;

			IdB = 0;			IdW = 0;
			tempIndex_B = 0, tempIndex_W = 0;

			//한 줄 검사하기 (가로)
			for (int j = 1; j < SIZE; j++)
			{
				if (board_2021180006[i][j] == -1)
				{
					//이전에 w가 연속된 적이 있으면
					//1. 처음으로 연속되는 경우
					if (WW != 0 && temp_WW == 0)
					{
						temp_WW = WW;		//W의 연속이 끊김, 얼마가 연속이었는지 넣어주기
						WW = 0;				//W가 다시 연속 될 수도 있기에 초기화 해주기

						tempIndex_W = IdW;	//이전에 연속이었던 부분 인덱스 넣어주기
						IdW = 0;
					}
					//2. 연속된 경우가 2회 이상이었을 경우
					else if (WW != 0 && temp_WW != 0)
					{
						if (temp_WW <= WW)
						{
							temp_WW = WW;	//temp_WW가 가장 큰 값을 가질 수 있도록
							tempIndex_W = IdW;
						}
						WW = 0;	//다음 값 저장을 위하여 초기화
						IdW = 0;
					}


					//B가 연속이면
					if (board_2021180006[i][j - 1] == -1)
					{
						++BB;	//BB값 늘려주기
						IdB = j;//(가로기준) 맨 오른쪽 돌의 인덱스
					}

				}
				if (board_2021180006[i][j] == 1)
				{
					//이전에 w가 연속된 적이 있으면
					//1. 처음으로 연속되는 경우
					if (BB != 0 && temp_BB == 0)
					{
						temp_BB = BB;	//W의 연속이 끊김, 얼마가 연속이었는지 넣어주기
						BB = 0;			//W가 다시 연속 될 수도 있기에 초기화 해주기

						tempIndex_B = IdB;	//이전에 연속이었던 부분 인덱스 넣어주기
						IdB = 0;
					}
					//2. 연속된 경우가 2회 이상이었을 경우
					else if (BB != 0 && temp_BB != 0)
					{
						if (temp_BB <= BB)
						{
							temp_BB = BB;	//temp_WW가 가장 큰 값을 가질 수 있도록
							tempIndex_B = IdB;
						}
						BB = 0;	//다음 값 저장을 위하여 초기화
						IdB = 0;
					}

					//W가 연속이면
					if (board_2021180006[i][j - 1] == 1)
					{
						++WW; //WW값 늘려주기
						IdW = j;
					}
				}
				if (WW > 1)	//가로줄에 연속 3개 이상 있으면 우측에 돌 놓고 나옴
				{
					if ( IdW+1<19 && BlankCHK(IdW+1,i))
					{
						board_2021180006[IdW + 1][i] = BLACK;
						*x = IdW + 1;
						*y = i;
						return;
					}
				}
			}

			//------------------------------------------------------------------------------
			//한 줄 검사하기 (세로)
			for (int j = 0; j < SIZE; j++)
			{
				//한 줄 넘길때 마다값 초기화
				BB = 0;			WW = 0;
				temp_BB = 0;	temp_WW = 0;

				//한 줄 검사하기
				for (int i = 1; i < SIZE; i++)
				{
					if (board_2021180006[i][j] == -1)
					{
						//이전에 w가 연속된 적이 있으면
						//1. 처음으로 연속되는 경우
						if (WW != 0 && temp_WW == 0)
						{
							temp_WW = WW;	//W의 연속이 끊김, 얼마가 연속이었는지 넣어주기
							WW = 0;			//W가 다시 연속 될 수도 있기에 초기화 해주기
							tempIndex_W = IdW;	//이전에 연속이었던 부분 인덱스 넣어주기
							IdW = 0;
						}
						//2. 연속된 경우가 2회 이상이었을 경우
						else if (WW != 0 && temp_WW != 0)
						{
							if (temp_WW <= WW)
							{
								temp_WW = WW;	//temp_WW가 가장 큰 값을 가질 수 있도록
								tempIndex_W = IdW;
							}
							WW = 0;	//다음 값 저장을 위하여 초기화
							IdW = 0;
						}


						//B가 연속이면
						if (board_2021180006[i-1][j] == -1)
						{
							++BB; //BB값 늘려주기
							IdB = j;//맨 아래 돌 위치
						}

					}
					if (board_2021180006[i][j] == 1)
					{
						//이전에 w가 연속된 적이 있으면
						//1. 처음으로 연속되는 경우
						if (BB != 0 && temp_BB == 0)
						{
							temp_BB = BB;	//W의 연속이 끊김, 얼마가 연속이었는지 넣어주기
							BB = 0;			//W가 다시 연속 될 수도 있기에 초기화 해주기
							tempIndex_B = IdB;	//이전에 연속이었던 부분 인덱스 넣어주기
							IdB = 0;
						}
						//2. 연속된 경우가 2회 이상이었을 경우
						else if (BB != 0 && temp_BB != 0)
						{
							if (temp_BB <= BB)
							{
								temp_BB = BB;	//temp_WW가 가장 큰 값을 가질 수 있도록
								tempIndex_B = IdB;
							}
							BB = 0;	//다음 값 저장을 위하여 초기화
							IdB = 0;
						}

						//W가 연속이면
						if (board_2021180006[i-1][j] == 1)
						{
							++WW; //WW값 늘려주기
							IdW = j;
						}
					}
				}
				if (WW > 1)	//가로줄에 연속 3개 이상 있으면 우측에 돌 놓고 나옴
				{
					if (IdW+1<19 && BlankCHK(i, IdW+1))
					{
						board_2021180006[i][IdW + 1] = BLACK;
						*x = i;
						*y = IdW + 1;
						return;
					}
				}
				
			}

		}


	}
	else {

		//가로 세로 확인
		for (int i = 0; i < SIZE; i++)
		{
			//한 줄 넘길때 마다 값 초기화
			BB = 0;				WW = 0;
			temp_BB = 0;		temp_WW = 0;

			IdB = 0;			IdW = 0;
			tempIndex_B = 0, tempIndex_W = 0;

			//한 줄 검사하기 (가로)
			for (int j = 1; j < SIZE; j++)
			{
				if (board_2021180006[i][j] == -1)
				{
					//이전에 w가 연속된 적이 있으면
					//1. 처음으로 연속되는 경우
					if (WW != 0 && temp_WW == 0)
					{
						temp_WW = WW;		//W의 연속이 끊김, 얼마가 연속이었는지 넣어주기
						WW = 0;				//W가 다시 연속 될 수도 있기에 초기화 해주기

						tempIndex_W = IdW;	//이전에 연속이었던 부분 인덱스 넣어주기
						IdW = 0;
					}
					//2. 연속된 경우가 2회 이상이었을 경우
					else if (WW != 0 && temp_WW != 0)
					{
						if (temp_WW <= WW)
						{
							temp_WW = WW;	//temp_WW가 가장 큰 값을 가질 수 있도록
							tempIndex_W = IdW;
						}
						WW = 0;	//다음 값 저장을 위하여 초기화
						IdW = 0;
					}


					//B가 연속이면
					if (board_2021180006[i][j - 1] == -1)
					{
						++BB;	//BB값 늘려주기
						IdB = j;//(가로기준) 맨 오른쪽 돌의 인덱스
					}

				}
				if (board_2021180006[i][j] == 1)
				{
					//이전에 w가 연속된 적이 있으면
					//1. 처음으로 연속되는 경우
					if (BB != 0 && temp_BB == 0)
					{
						temp_BB = BB;	//W의 연속이 끊김, 얼마가 연속이었는지 넣어주기
						BB = 0;			//W가 다시 연속 될 수도 있기에 초기화 해주기

						tempIndex_B = IdB;	//이전에 연속이었던 부분 인덱스 넣어주기
						IdB = 0;
					}
					//2. 연속된 경우가 2회 이상이었을 경우
					else if (BB != 0 && temp_BB != 0)
					{
						if (temp_BB <= BB)
						{
							temp_BB = BB;	//temp_WW가 가장 큰 값을 가질 수 있도록
							tempIndex_B = IdB;
						}
						BB = 0;	//다음 값 저장을 위하여 초기화
						IdB = 0;
					}

					//W가 연속이면
					if (board_2021180006[i][j - 1] == 1)
					{
						++WW; //WW값 늘려주기
						IdW = j;
					}
				}
				if (BB > 2)	//가로줄에 연속 3개 이상 있으면 우측에 돌 놓고 나옴
				{
					if (IdB + 1 < 19 && BlankCHK(IdB + 1, i))
					{
						board_2021180006[IdB + 1][i] = 1;
						*x = IdB + 1;
						*y = i;
						return;
					}
				}
			}

			//------------------------------------------------------------------------------
			//한 줄 검사하기 (세로)
			for (int j = 0; j < SIZE; j++)
			{
				//한 줄 넘길때 마다값 초기화
				BB = 0;			WW = 0;
				temp_BB = 0;	temp_WW = 0;

				//한 줄 검사하기
				for (int i = 1; i < SIZE; i++)
				{
					if (board_2021180006[i][j] == -1)
					{
						//이전에 w가 연속된 적이 있으면
						//1. 처음으로 연속되는 경우
						if (WW != 0 && temp_WW == 0)
						{
							temp_WW = WW;	//W의 연속이 끊김, 얼마가 연속이었는지 넣어주기
							WW = 0;			//W가 다시 연속 될 수도 있기에 초기화 해주기
							tempIndex_W = IdW;	//이전에 연속이었던 부분 인덱스 넣어주기
							IdW = 0;
						}
						//2. 연속된 경우가 2회 이상이었을 경우
						else if (WW != 0 && temp_WW != 0)
						{
							if (temp_WW <= WW)
							{
								temp_WW = WW;	//temp_WW가 가장 큰 값을 가질 수 있도록
								tempIndex_W = IdW;
							}
							WW = 0;	//다음 값 저장을 위하여 초기화
							IdW = 0;
						}


						//B가 연속이면
						if (board_2021180006[i - 1][j] == -1)
						{
							++BB; //BB값 늘려주기
							IdB = j;//맨 아래 돌 위치
						}

					}
					if (board_2021180006[i][j] == 1)
					{
						//이전에 w가 연속된 적이 있으면
						//1. 처음으로 연속되는 경우
						if (BB != 0 && temp_BB == 0)
						{
							temp_BB = BB;	//W의 연속이 끊김, 얼마가 연속이었는지 넣어주기
							BB = 0;			//W가 다시 연속 될 수도 있기에 초기화 해주기
							tempIndex_B = IdB;	//이전에 연속이었던 부분 인덱스 넣어주기
							IdB = 0;
						}
						//2. 연속된 경우가 2회 이상이었을 경우
						else if (BB != 0 && temp_BB != 0)
						{
							if (temp_BB <= BB)
							{
								temp_BB = BB;	//temp_WW가 가장 큰 값을 가질 수 있도록
								tempIndex_B = IdB;
							}
							BB = 0;	//다음 값 저장을 위하여 초기화
							IdB = 0;
						}

						//W가 연속이면
						if (board_2021180006[i - 1][j] == 1)
						{
							++WW; //WW값 늘려주기
							IdW = j;
						}
					}
				}
				if (BB > 2)	//가로줄에 연속 3개 이상 있으면 우측에 돌 놓고 나옴
				{
					if (IdB + 1 < 19 && BlankCHK(i, IdB + 1))
					{
						board_2021180006[i][IdB + 1] = 1;
						*x = i;
						*y = IdB + 1;
						return;
					}
				}

			}

		}


	}
}

//=============================================================================
// 흑돌
void BlackAttack_2021180006(int* x, int* y) {

	//선공 첫 돌 놓기
	blackAttack(x, y);
	defece(BLACK, x, y);

}

void BlackDefence_2021180006(int x, int y) {

	board_2021180006[x][y] = WHITE;
}



//=============================================================================
// 백돌
void WhiteAttack_2021180006(int* x, int* y) {
	
	//선공 첫 돌 놓기
	whiteAttack(x, y);
	defece(WHITE, x, y);
}

void WhiteDefence_2021180006(int x, int y) {

	board_2021180006[x][y] = BLACK;
}
