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

    //���ڿ� �� ��ȯ�� Ȯ��
    printf("strcmp(%s, %s)\t = %d\n", str1, str2, strcmp(str1, str2));
    printf("str3 : %s str4 : %s\n", str3, str4);

    //���ڿ��� �������� �Ǵ��Ҷ��� �̿Ͱ��� ����մϴ�.
    if (strcmp(str1, str2) == 0)
    {
        printf("%s, %s �� �����ϴ�.", str1, str2);
    }
    else
    {
        printf("%s, %s �� �ٸ��ϴ�.", str1, str2);
    }

    return 0;
}