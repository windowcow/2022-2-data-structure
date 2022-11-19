#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 100
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct data
{
    int priority;
    char *c;
} data;

data heap[MAX_ELEMENTS];

char *randomStringGenerate(void)
{
    char *s = (char *)malloc(100);
    for (int i = 0; i < 100; i++)
    {
        s[i] = rand() % 26 + 'a';
    }
    s[99] = '\0';
    return s;
}

data *makeRandomData(void)
{
    data *d = (data *)malloc(sizeof(data));

    d->priority = rand() % 1000;
    d->c = randomStringGenerate();

    return d;
}

void push(data dataItem, int *n)
{
    int i;

    if (HEAP_FULL(*n))
    {
        fprintf(stderr, "The heap is full.\n");
    }

    i = ++(*n);

    while ((i != 1) && (dataItem.priority > heap[i / 2].priority))
    {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = dataItem;
}

data *popHeap(int *n)
{
    int parent, child;
    data item, temp;

    if (HEAP_EMPTY(*n))
    {
        fprintf(stderr, "The heap is empty.\n");
    }

    item = heap[1];
    temp = heap[(*n)--];

    parent = 1;
    child = 2;

    while (child <= *n)
    {
        if ((child < *n) && (heap[child].priority < heap[child + 1].priority))
        {
            child++;
        }
        if (temp.priority >= heap[child].priority)
        {
            break;
        }
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return &item;
}

int main(void)
{
    int n = 0;
    data *d;

    srand(time(NULL));

    for (int i = 0; i < 100; i++)
    {
        d = makeRandomData();
        push(*d, &n);
    }

    for (int i = 0; i < 100; i++)
    {
        d = popHeap(&n);
        printf("%d ", d->priority);
    }
    printf("\n");

    return 0;
}