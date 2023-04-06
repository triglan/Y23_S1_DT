#include <stdio.h>

int main() {
	int *hpp = NULL;
	new = malloc(**);
	new->hp = 100;
	new->mp = 35;
	new->next = NULL;

	//첫 주소를 가리키는 hpp가 첫 주소를 가리키게 함
	hpp = new;

	//새로 또 선언
	new = malloc();
	new->hp = 97;
	new->mp = 47;

	//1번 배열의 주소는 hpp에 있으니까 새 new에 넣고 
	new->next = hpp;
	hpp = new;
}