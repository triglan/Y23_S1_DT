#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    FILE* fp;
    char str[100];

    // ���� ���� ����
    fp = fopen("myfile.txt", "w");
    fprintf(fp, "This is an example.\n");
    fputs("Another line.", fp);
    fclose(fp);

    // ���� �б� ����
    fp = fopen("myfile.txt", "r");
    fgets(str, 100, fp);
    printf("%s", str);
    fgets(str, 100, fp);
    printf("%s", str);
    fclose(fp);

    return 0;
}