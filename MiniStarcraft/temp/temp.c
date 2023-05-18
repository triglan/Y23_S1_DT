#define _CRT_SECURE_NO_WARNINGS

#include<string.h>    //strcmp
#include<stdio.h>    //printf

int main(void)
{
    const char* str1 = "Block235423";
    const char* str2 = "Block59999";
    char str3[20];
    char str4[20];

    scanf_s("%s %s", str3, sizeof(str3), str4, sizeof(str4));

    //문자열 비교 반환값 확인
    printf("strcmp(%s, %s)\t = %d\n", str1, str2, strcmp(str1, str2));
    printf("str3 : %s str4 : %s\n", str3, str4);

    //문자열이 같은지를 판단할때는 이와같이 사용합니다.
    if (strcmp(str1, str2) == 0)
    {
        printf("%s, %s 는 같습니다.", str1, str2);
    }
    else
    {
        printf("%s, %s 는 다릅니다.", str1, str2);
    }

    return 0;
}