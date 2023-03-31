#include <stdio.h>

void again(int x);

int main()
{
	int x = 20;
	printf("%d ", x++);
	printf("%d ", x);

	again(10);
}


void again(int x)
{
	if (x <= 0)
		return;

	printf("%d ", x);
	again(--x);
}

//void Search(int x)
//{
//	if (x.id <= MAXSIZE)
//		return;
//	if (x.name == "v")
//		return Search(x);
//	else
//		Search(++x);
// 
//	printf("ERROR");
//	return;
//}