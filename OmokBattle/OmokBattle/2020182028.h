#pragma once
int board_2020182028[19][19];

//��		1
//������	-1
#define BLACK -1
#define WHITE 1

void WhiteAttack_2020182028(int* x, int* y)
{
	// ���� �����Ͻ� �� ���� ������ �־��ּ���
	//
	//

	// ���÷� �׻� [5,5]���� ���� �ΰ���
	*x = 5;
	*y = 5;

	board_2020182028[*y][*x] = WHITE;
}
void WhiteDefence_2020182028(int x, int y)
{
	// ��밡 ���� ���� ��ġ�� ���޹޾Ƽ� �����մϴ�
	board_2020182028[y][x] = BLACK;
}
void BlackAttack_2020182028(int* x, int* y)
{
	// ���� �����Ͻ� �� ���� ������ �־��ּ���
	//
	//

	// ���÷� �׻� [5,5]���� ���� �ΰ���
	*x = 5;
	*y = 5;

	board_2020182028[*y][*x] = BLACK;
}
void BlackDefence_2020182028(int x, int y)
{
	// ��밡 ���� ���� ��ġ�� ���޹޾Ƽ� �����մϴ�
	board_2020182028[y][x] = WHITE;
}