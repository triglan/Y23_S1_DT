#include<iostream>
#include "Judgment.h"

#include "2020182028.h"
//#include "2020182001.h"
using namespace std;

int main(void)
{
	Judgment judgment;

	judgment.SetYourFunc(
		BlackAttack_2020182028/*����*/,
		BlackDefence_2020182028,
		WhiteAttack_2020182028/*�İ�*/,
		WhiteDefence_2020182028
	);
	judgment.GamePlay();

}