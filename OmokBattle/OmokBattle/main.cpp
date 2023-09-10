#include<iostream>
#include "Judgment.h"

#include "2021180004.h"
#include "2021180006.h"
#include "2022184009.h"
#include "Omock_2020182012.h"
#include "Omock_2020182015.h"
#include "2020182028.h"
#include "2020180036.h"
using namespace std;

int main(void)
{
	Judgment judgment;

	judgment.SetYourFunc(
		BlackAttack_2021180004/*선공*/,
		BlackDefence_2021180004,
		WhiteAttack_2020182015/*후공*/,
		WhiteDefence_2020182015
	);
	judgment.GamePlay();
}