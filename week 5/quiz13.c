#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
typedef struct
{
    int key;
} element;
element stack[MAX_STACK_SIZE];
int top = -1;

void push(element item)
{

    stack[++top] = item;
}

element pop()
{
    return stack[top--];
}

main()
{
    element e;
    int a;
    printf("생성된 스택: ");
    for (int i = 0; i < 10; i++)
    {
        a = rand() % 100;
        printf("%d ", a);
        e.key = a;
        push(e);
    }
    printf("\n");
    printf("거꾸로 출력된 스택: ");
    for (int i = 9; i >= 0; i--)
    {
        e = pop();
        printf("%d ", e.key);
    }
}