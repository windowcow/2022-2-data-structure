#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

int count = 0;

typedef struct
{
    int key;
} element;

element queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

void addq(element item)
{
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if (front == rear)
        queueFull();
    count++;
    queue[rear] = item;
}

element deleteq()
{

    if (front == rear)
    {
        queueEmpty();
    }
    front = (front + 1) % MAX_QUEUE_SIZE;
    count--;
    return queue[front];
}

void queueFull()
{
    if (count != MAX_QUEUE_SIZE)
    {
        printf("Queue is not full\n");
        return;
    }
    else
    {
        printf("queue is full.\n");
        exit(1);
    }
}

void queueEmpty()
{
    printf("queue is empty.\n");
    exit(1);
}

int main()
{
}