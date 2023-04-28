#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//#define MAX_STACK_SIZE 100
//
//typedef struct {
//    int data[MAX_STACK_SIZE];
//    int top;
//} Stack;
//
//void init(Stack* s) {
//    s->top = -1; // 스택 초기화
//}
//
//int is_empty(Stack* s) {
//    return (s->top == -1); // 스택이 비어있는지 검사
//}
//
//int is_full(Stack* s) {
//    return (s->top == MAX_STACK_SIZE - 1); // 스택이 가득 차 있는지 검사
//}
//
//void push(Stack* s, int item) {
//    if (is_full(s)) {
//        printf("Stack is full.\n");
//        return;
//    }
//    s->data[++(s->top)] = item; // 스택에 데이터 추가
//}
//
//int pop(Stack* s) {
//    if (is_empty(s)) {
//        printf("Stack is empty.\n");
//        return -1;
//    }
//    return s->data[(s->top)--]; // 스택에서 데이터 삭제
//}

//int main() {
//    int num;
//    FILE* fp = fopen("input.txt", "r");
//    fscanf(fp, "%d", &num);
//    printf("%d\n", num);
//    fclose(fp);
//    return 0;
//}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    FILE* fp;
    char str[100];

    // 파일 쓰기 예제
    fp = fopen("myfile.txt", "w");
    fprintf(fp, "This is an example.\n");
    fputs("Another line.", fp);
    fclose(fp);

    // 파일 읽기 예제
    fp = fopen("myfile.txt", "r");
    fgets(str, 100, fp);
    printf("%s", str);
    fgets(str, 100, fp);
    printf("%s", str);
    fclose(fp);

    return 0;
}