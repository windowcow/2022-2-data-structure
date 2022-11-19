#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
linkedList에서는 차라리 우선순위 큰 순서대로 들어가게끔 만드는게 훨씬 쉽다.
온 순서대로 넣고 우선순위 큰 애들을 골라서 빼려면 엄청 복잡하다.

*/

typedef struct data
{
    int priority;
    char *c;
} data;

typedef struct node
{
    data *data;
    struct node *next;
} node;

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

node *makeLinkedNode(void)
{
    node *linkedNodePointer = (node *)malloc(sizeof(node));

    linkedNodePointer->data = makeRandomData();
    linkedNodePointer->next = NULL;

    return linkedNodePointer;
}

void insertNode(node **headPointer)
{
    node *newNode = makeLinkedNode();
    printf("%d ", newNode->data->priority);
    node *temp = *headPointer;

    if (*headPointer == NULL)
    {
        *headPointer = newNode;
    }
    else
    {
        *headPointer = newNode;
        newNode->next = temp;
    }
}

void deleteTopPriority(node **headPointer)
{
    node *temp = *headPointer;
    node *temp2 = *headPointer;
    node *tempMax = *headPointer;

    if (*headPointer == NULL)
    {
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->data->priority > tempMax->data->priority)
            {
                tempMax = temp;
            }
            temp = temp->next;
        }
        if (tempMax == *headPointer)
        {
            *headPointer = (*headPointer)->next;
        }
        else
        {
            while (temp2->next != tempMax)
            {
                temp2 = temp2->next;
            }
            temp2->next = tempMax->next;
        }
    }
    printf("%d ", tempMax->data->priority);
}

int main(void)
{
    srand(time(NULL));
    node *head = NULL;

    printf("넣은 순서: \n");
    for (int i = 0; i < 100; i++)
    {
        insertNode(&head);
    }
    printf("\n삭제 된 순서: \n");
    for (int i = 0; i < 100; i++)
    {
        deleteTopPriority(&head);
    }

    return 0;
}