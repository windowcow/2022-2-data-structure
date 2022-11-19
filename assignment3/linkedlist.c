#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
linkedList에서는 차라리 우선순위 큰 순서대로 들어가게끔 만드는게 훨씬 쉽다.
온 순서대로 넣고 우선순위 큰 애들을 골라서 빼려면 엄청 복잡하다.

*/

typedef struct linkedNode *headPointer;

typedef struct data
{
    int priority;
    char *c;
} data;

typedef struct linkedNode
{
    data *data;
    struct linkedNode *next;
} linkedNode;

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

data *makeNode(void)
{
    data *n = malloc(sizeof(data));
    n->priority = rand() % 1000;
    printf("%d ", n->priority);
    n->c = randomStringGenerate();
    return n;
}

headPointer makeEmptyHeadPointer(void)
{
    headPointer headpointer = (headPointer)malloc(sizeof(linkedNode));
    headpointer->data = NULL;
    headpointer->next = NULL;

    return headpointer;
}

// link to linked list
void insertNodeToItsPriority(headPointer headpointer, linkedNode *insertedNodePointer)
{
    linkedNode *tempNodePointer = (linkedNode *)malloc(sizeof(linkedNode));
    *tempNodePointer = *headpointer; // 헤드를 받는다. (linkedNode로)

    printf("inserting %d\n", insertedNodePointer->data->priority);

    // head가 없는 경우
    if (headpointer->data == NULL)
    {
        *headpointer = *insertedNodePointer;
        return;
    }
    // head가 있는 경우 넣어 준 애가 맨 앞에 위치할 경우는 따로 생각한다.
    else if (headpointer->data->priority <= insertedNodePointer->data->priority)
    {
        insertedNodePointer->next = headpointer; // 헤드가됨

        headpointer = insertedNodePointer;
        return;
    }
    // 맨 앞에는 안들어가는 경우. 이 경우는 같은 코드로 반복이 가능하기에 이렇게함
    else
    {

        while (tempNodePointer->data->priority > insertedNodePointer->data->priority)
        {
            // 마지막까지 간 경우
            if (tempNodePointer->next == NULL)
            {
                tempNodePointer->next = insertedNodePointer;
                return;
            }
            // 마지막까지 가지 않은 경우
            else
            {
                tempNodePointer = tempNodePointer->next;
            }
        }
        insertedNodePointer->next = tempNodePointer->next;
        tempNodePointer->next = insertedNodePointer;
        return;
    }
}

// priority가 가장 큰 node를 지우는 함수 (끊고 연결해야함)
void popBiggestPriority(headPointer headpointer)
{
    linkedNode *tempLinkedNodePointer = headpointer;

    // 아무 것도 없는 경우
    if (tempLinkedNodePointer->data == NULL)
    {
        return;
    }
    // 하나 있는 경우 linkedListPointer은 NULL을 가리킨다.
    else if (tempLinkedNodePointer->next == NULL)
    {
        printf("%d ", tempLinkedNodePointer->data->priority);
        headpointer = NULL;
        return;
    }
    // 두 개 이상 있는 경우
    else
    {
        printf("%d ", tempLinkedNodePointer->data->priority);
        headpointer = tempLinkedNodePointer->next;
        return;
    }
    // 다음이 없는 경우에는 최고를 반환하면 된다.
}

int main(void)
{
    srand(time(NULL));
    double insertTime, popTime, totalTime;

    clock_t start, end;

    headPointer headpointer = makeEmptyHeadPointer();

    start = clock();

    for (int i = 0; i < 100; i++)
    {
        data *n = makeNode();
        linkedNode ln = {n, NULL};
        insertNodeToItsPriority(headpointer, &ln);
    }
    end = clock();

    for (int i = 0; i < 100; i++)
    {
        printf("%d ", headpointer->data->priority);
    }

    insertTime = (double)(end - start);
    printf("Insert에 소요 시간: %lfms\n", insertTime);

    start = clock();
    for (int i = 0; i < 100; i++)
    {
        // node *n = makeNode(); // 같은 조건을 위해서 넣었습니다.
        popBiggestPriority(headpointer);
    }

    end = clock();
    popTime = (double)(end - start);
    printf("\nPop에 소요 시간: %lfms\n", popTime);

    totalTime = insertTime + popTime;
    printf("전체 소요 시간!: %lfms", totalTime);

    return 0;
}