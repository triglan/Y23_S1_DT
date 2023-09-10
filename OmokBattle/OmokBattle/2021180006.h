#pragma once

int board_2021180006[19][19];

#define BLACK			-1
#define WHITE			 1

#define SIZE			 19

int CntB = 0, CntW = 0, CntAll = 0;
//=============================================================================
// ��ĭ Ȯ�� �Լ�
bool BlankCHK(int x, int y) {
	if (board_2021180006[x][y] == -1 || board_2021180006[x][y] == 1) return false;
	else return true;
}

// �� �� ���� ���� �Լ�
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

	CntAll = tempB + tempW;		//�� ���� ��

}

//���ϴ� �밢�� ���� �Լ�
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
	int IdB = 0, IdW = 0;					// 4���� ��ǥ���� ����
	int tempIndex_B = 0, tempIndex_W = 0;	// ��ǥ���� �ӽú���

	if (Iam == -1)	//�浹�϶� ���ư��� �ڵ�
	{
		//���� ���� Ȯ��
		for (int i = 0; i < SIZE; i++)
		{
			//�� �� �ѱ涧 ���� �� �ʱ�ȭ
			BB = 0;				WW = 0;
			temp_BB = 0;		temp_WW = 0;

			IdB = 0;			IdW = 0;
			tempIndex_B = 0, tempIndex_W = 0;

			//�� �� �˻��ϱ� (����)
			for (int j = 1; j < SIZE; j++)
			{
				if (board_2021180006[i][j] == -1)
				{
					//������ w�� ���ӵ� ���� ������
					//1. ó������ ���ӵǴ� ���
					if (WW != 0 && temp_WW == 0)
					{
						temp_WW = WW;		//W�� ������ ����, �󸶰� �����̾����� �־��ֱ�
						WW = 0;				//W�� �ٽ� ���� �� ���� �ֱ⿡ �ʱ�ȭ ���ֱ�

						tempIndex_W = IdW;	//������ �����̾��� �κ� �ε��� �־��ֱ�
						IdW = 0;
					}
					//2. ���ӵ� ��찡 2ȸ �̻��̾��� ���
					else if (WW != 0 && temp_WW != 0)
					{
						if (temp_WW <= WW)
						{
							temp_WW = WW;	//temp_WW�� ���� ū ���� ���� �� �ֵ���
							tempIndex_W = IdW;
						}
						WW = 0;	//���� �� ������ ���Ͽ� �ʱ�ȭ
						IdW = 0;
					}


					//B�� �����̸�
					if (board_2021180006[i][j - 1] == -1)
					{
						++BB;	//BB�� �÷��ֱ�
						IdB = j;//(���α���) �� ������ ���� �ε���
					}

				}
				if (board_2021180006[i][j] == 1)
				{
					//������ w�� ���ӵ� ���� ������
					//1. ó������ ���ӵǴ� ���
					if (BB != 0 && temp_BB == 0)
					{
						temp_BB = BB;	//W�� ������ ����, �󸶰� �����̾����� �־��ֱ�
						BB = 0;			//W�� �ٽ� ���� �� ���� �ֱ⿡ �ʱ�ȭ ���ֱ�

						tempIndex_B = IdB;	//������ �����̾��� �κ� �ε��� �־��ֱ�
						IdB = 0;
					}
					//2. ���ӵ� ��찡 2ȸ �̻��̾��� ���
					else if (BB != 0 && temp_BB != 0)
					{
						if (temp_BB <= BB)
						{
							temp_BB = BB;	//temp_WW�� ���� ū ���� ���� �� �ֵ���
							tempIndex_B = IdB;
						}
						BB = 0;	//���� �� ������ ���Ͽ� �ʱ�ȭ
						IdB = 0;
					}

					//W�� �����̸�
					if (board_2021180006[i][j - 1] == 1)
					{
						++WW; //WW�� �÷��ֱ�
						IdW = j;
					}
				}
				if (WW > 1)	//�����ٿ� ���� 3�� �̻� ������ ������ �� ���� ����
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
			//�� �� �˻��ϱ� (����)
			for (int j = 0; j < SIZE; j++)
			{
				//�� �� �ѱ涧 ���ٰ� �ʱ�ȭ
				BB = 0;			WW = 0;
				temp_BB = 0;	temp_WW = 0;

				//�� �� �˻��ϱ�
				for (int i = 1; i < SIZE; i++)
				{
					if (board_2021180006[i][j] == -1)
					{
						//������ w�� ���ӵ� ���� ������
						//1. ó������ ���ӵǴ� ���
						if (WW != 0 && temp_WW == 0)
						{
							temp_WW = WW;	//W�� ������ ����, �󸶰� �����̾����� �־��ֱ�
							WW = 0;			//W�� �ٽ� ���� �� ���� �ֱ⿡ �ʱ�ȭ ���ֱ�
							tempIndex_W = IdW;	//������ �����̾��� �κ� �ε��� �־��ֱ�
							IdW = 0;
						}
						//2. ���ӵ� ��찡 2ȸ �̻��̾��� ���
						else if (WW != 0 && temp_WW != 0)
						{
							if (temp_WW <= WW)
							{
								temp_WW = WW;	//temp_WW�� ���� ū ���� ���� �� �ֵ���
								tempIndex_W = IdW;
							}
							WW = 0;	//���� �� ������ ���Ͽ� �ʱ�ȭ
							IdW = 0;
						}


						//B�� �����̸�
						if (board_2021180006[i-1][j] == -1)
						{
							++BB; //BB�� �÷��ֱ�
							IdB = j;//�� �Ʒ� �� ��ġ
						}

					}
					if (board_2021180006[i][j] == 1)
					{
						//������ w�� ���ӵ� ���� ������
						//1. ó������ ���ӵǴ� ���
						if (BB != 0 && temp_BB == 0)
						{
							temp_BB = BB;	//W�� ������ ����, �󸶰� �����̾����� �־��ֱ�
							BB = 0;			//W�� �ٽ� ���� �� ���� �ֱ⿡ �ʱ�ȭ ���ֱ�
							tempIndex_B = IdB;	//������ �����̾��� �κ� �ε��� �־��ֱ�
							IdB = 0;
						}
						//2. ���ӵ� ��찡 2ȸ �̻��̾��� ���
						else if (BB != 0 && temp_BB != 0)
						{
							if (temp_BB <= BB)
							{
								temp_BB = BB;	//temp_WW�� ���� ū ���� ���� �� �ֵ���
								tempIndex_B = IdB;
							}
							BB = 0;	//���� �� ������ ���Ͽ� �ʱ�ȭ
							IdB = 0;
						}

						//W�� �����̸�
						if (board_2021180006[i-1][j] == 1)
						{
							++WW; //WW�� �÷��ֱ�
							IdW = j;
						}
					}
				}
				if (WW > 1)	//�����ٿ� ���� 3�� �̻� ������ ������ �� ���� ����
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

		//���� ���� Ȯ��
		for (int i = 0; i < SIZE; i++)
		{
			//�� �� �ѱ涧 ���� �� �ʱ�ȭ
			BB = 0;				WW = 0;
			temp_BB = 0;		temp_WW = 0;

			IdB = 0;			IdW = 0;
			tempIndex_B = 0, tempIndex_W = 0;

			//�� �� �˻��ϱ� (����)
			for (int j = 1; j < SIZE; j++)
			{
				if (board_2021180006[i][j] == -1)
				{
					//������ w�� ���ӵ� ���� ������
					//1. ó������ ���ӵǴ� ���
					if (WW != 0 && temp_WW == 0)
					{
						temp_WW = WW;		//W�� ������ ����, �󸶰� �����̾����� �־��ֱ�
						WW = 0;				//W�� �ٽ� ���� �� ���� �ֱ⿡ �ʱ�ȭ ���ֱ�

						tempIndex_W = IdW;	//������ �����̾��� �κ� �ε��� �־��ֱ�
						IdW = 0;
					}
					//2. ���ӵ� ��찡 2ȸ �̻��̾��� ���
					else if (WW != 0 && temp_WW != 0)
					{
						if (temp_WW <= WW)
						{
							temp_WW = WW;	//temp_WW�� ���� ū ���� ���� �� �ֵ���
							tempIndex_W = IdW;
						}
						WW = 0;	//���� �� ������ ���Ͽ� �ʱ�ȭ
						IdW = 0;
					}


					//B�� �����̸�
					if (board_2021180006[i][j - 1] == -1)
					{
						++BB;	//BB�� �÷��ֱ�
						IdB = j;//(���α���) �� ������ ���� �ε���
					}

				}
				if (board_2021180006[i][j] == 1)
				{
					//������ w�� ���ӵ� ���� ������
					//1. ó������ ���ӵǴ� ���
					if (BB != 0 && temp_BB == 0)
					{
						temp_BB = BB;	//W�� ������ ����, �󸶰� �����̾����� �־��ֱ�
						BB = 0;			//W�� �ٽ� ���� �� ���� �ֱ⿡ �ʱ�ȭ ���ֱ�

						tempIndex_B = IdB;	//������ �����̾��� �κ� �ε��� �־��ֱ�
						IdB = 0;
					}
					//2. ���ӵ� ��찡 2ȸ �̻��̾��� ���
					else if (BB != 0 && temp_BB != 0)
					{
						if (temp_BB <= BB)
						{
							temp_BB = BB;	//temp_WW�� ���� ū ���� ���� �� �ֵ���
							tempIndex_B = IdB;
						}
						BB = 0;	//���� �� ������ ���Ͽ� �ʱ�ȭ
						IdB = 0;
					}

					//W�� �����̸�
					if (board_2021180006[i][j - 1] == 1)
					{
						++WW; //WW�� �÷��ֱ�
						IdW = j;
					}
				}
				if (BB > 2)	//�����ٿ� ���� 3�� �̻� ������ ������ �� ���� ����
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
			//�� �� �˻��ϱ� (����)
			for (int j = 0; j < SIZE; j++)
			{
				//�� �� �ѱ涧 ���ٰ� �ʱ�ȭ
				BB = 0;			WW = 0;
				temp_BB = 0;	temp_WW = 0;

				//�� �� �˻��ϱ�
				for (int i = 1; i < SIZE; i++)
				{
					if (board_2021180006[i][j] == -1)
					{
						//������ w�� ���ӵ� ���� ������
						//1. ó������ ���ӵǴ� ���
						if (WW != 0 && temp_WW == 0)
						{
							temp_WW = WW;	//W�� ������ ����, �󸶰� �����̾����� �־��ֱ�
							WW = 0;			//W�� �ٽ� ���� �� ���� �ֱ⿡ �ʱ�ȭ ���ֱ�
							tempIndex_W = IdW;	//������ �����̾��� �κ� �ε��� �־��ֱ�
							IdW = 0;
						}
						//2. ���ӵ� ��찡 2ȸ �̻��̾��� ���
						else if (WW != 0 && temp_WW != 0)
						{
							if (temp_WW <= WW)
							{
								temp_WW = WW;	//temp_WW�� ���� ū ���� ���� �� �ֵ���
								tempIndex_W = IdW;
							}
							WW = 0;	//���� �� ������ ���Ͽ� �ʱ�ȭ
							IdW = 0;
						}


						//B�� �����̸�
						if (board_2021180006[i - 1][j] == -1)
						{
							++BB; //BB�� �÷��ֱ�
							IdB = j;//�� �Ʒ� �� ��ġ
						}

					}
					if (board_2021180006[i][j] == 1)
					{
						//������ w�� ���ӵ� ���� ������
						//1. ó������ ���ӵǴ� ���
						if (BB != 0 && temp_BB == 0)
						{
							temp_BB = BB;	//W�� ������ ����, �󸶰� �����̾����� �־��ֱ�
							BB = 0;			//W�� �ٽ� ���� �� ���� �ֱ⿡ �ʱ�ȭ ���ֱ�
							tempIndex_B = IdB;	//������ �����̾��� �κ� �ε��� �־��ֱ�
							IdB = 0;
						}
						//2. ���ӵ� ��찡 2ȸ �̻��̾��� ���
						else if (BB != 0 && temp_BB != 0)
						{
							if (temp_BB <= BB)
							{
								temp_BB = BB;	//temp_WW�� ���� ū ���� ���� �� �ֵ���
								tempIndex_B = IdB;
							}
							BB = 0;	//���� �� ������ ���Ͽ� �ʱ�ȭ
							IdB = 0;
						}

						//W�� �����̸�
						if (board_2021180006[i - 1][j] == 1)
						{
							++WW; //WW�� �÷��ֱ�
							IdW = j;
						}
					}
				}
				if (BB > 2)	//�����ٿ� ���� 3�� �̻� ������ ������ �� ���� ����
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
// �浹
void BlackAttack_2021180006(int* x, int* y) {

	//���� ù �� ����
	blackAttack(x, y);
	defece(BLACK, x, y);

}

void BlackDefence_2021180006(int x, int y) {

	board_2021180006[x][y] = WHITE;
}



//=============================================================================
// �鵹
void WhiteAttack_2021180006(int* x, int* y) {
	
	//���� ù �� ����
	whiteAttack(x, y);
	defece(WHITE, x, y);
}

void WhiteDefence_2021180006(int x, int y) {

	board_2021180006[x][y] = BLACK;
}
