#include <stdio.h>

#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)
typedef struct
{
    int key;
} element;

void push(element item, int *n)
{
    int i;
    if (HEAP_FULL(*n))
    {
        fprintf(stderr, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }

    i = ++(*n); // 다음 인덱스를 의미 그리고 함수 밖에서도 유지됨.
    while ((i != 1) && (item.key > heap[i / 2].key))
    {
        heap[i] = heap[i / 2];
        i /= 2;
    }
}

int main(void)
{
    element heap[MAX_ELEMENTS];
}