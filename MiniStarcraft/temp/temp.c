#include <stdio.h>

int main()
{
    char str[20];
    scanf_s("%s", &str, sizeof(str));
    printf("%s", str);
    return 0;
}

