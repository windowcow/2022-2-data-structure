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

data *makeRandomData(void)
{
    data *d = (data *)malloc(sizeof(data));

    d->priority = rand() % 1000;
    d->c = randomStringGenerate();

    return d;
}

linkedNode *makeLinkedNode(void)
{
    linkedNode *linkedNodePointer = (linkedNode *)malloc(sizeof(linkedNode));

    linkedNodePointer->data = makeRandomData();
    linkedNodePointer->next = NULL;

    return linkedNodePointer;
}

void insertLinkedNodeInOrder(linkedNode *headpointer, linkedNode *insertedNodePointer)
{
    linkedNode *tempNode = headpointer;
    // headpointer는 첨부터 하나 가지고 있음
    if (insertedNodePointer->data->priority >= headpointer->data->priority)
    {
        insertedNodePointer->next = headpointer;
        headpointer = insertedNodePointer;
    }
    else
    {
        while (tempNode->next != NULL)
        {
            if (insertedNodePointer->data->priority >= tempNode->next->data->priority)
            {
                insertedNodePointer->next = tempNode->next;
                tempNode->next = insertedNodePointer;
                return;
            }
            tempNode = tempNode->next;
        }
        if (tempNode == NULL)
        {
            tempNode = insertedNodePointer;
        }
    }
}
// }

// while (insertedNodePointer->data->priority <= tempNode->data->priority)
// {
//     if (tempNode->next == NULL)
//     {
//         tempNode->next = insertedNodePointer;
//         return;
//     }
//     // tempNode가 next가 있는 경우
//     else
//     {

//         if (tempNode->next->next != NULL)
//         {
//             // 아직 한번 더 바꿔야함
//             if (insertedNodePointer->data->priority <= tempNode->next->data->priority)
//             {
//                 tempNode = tempNode->next;
//             }

//             //드갈 곳을 찾았다?
//             else
//             {
//                 insertedNodePointer->next = tempNode->next;
//                 tempNode->next = insertedNodePointer;
//                 return;
//             }
//         }
//         // 다다음이 없는 경우
//         else
//         {
//             //제 자리를 찾은 경우
//             if (insertedNodePointer->data->priority >= tempNode->next->data->priority)
//             {
//                 insertedNodePointer->next = tempNode->next;
//                 tempNode->next = insertedNodePointer;
//                 return;
//             }
//             // 마지막이 자리인 경우 인스터 포인터가!.
//             else
//             {
//                 tempNode->next->next = insertedNodePointer;
//                 return;
//             }
//         }
//     }
// }
// 이제 tempNode 다음에 들어가면 됨

int main(void)
{
    srand(time(NULL));
    double insertTime, popTime, totalTime;

    clock_t start, end;

    linkedNode *headpointer = makeLinkedNode();

    start = clock();

    for (int i = 0; i < 99; i++)
    {
        insertLinkedNodeInOrder(headpointer, makeLinkedNode());
    }

    end = clock();

    for (int i = 0; i < 99; i++)
    {
        printf("%d ", headpointer->data->priority);
        headpointer = headpointer->next;
    }
    return 0;
}
// for (int i = 0; i < 100; i++)
// {
//     printf("%d ", headpointer->data->priority);
// }

// insertTime = (double)(end - start);
// printf("Insert에 소요 시간: %lfms\n", insertTime);

// start = clock();
// for (int i = 0; i < 100; i++)
// {
//     // node *n = makeNode(); // 같은 조건을 위해서 넣었습니다.
//     popBiggestPriority(headpointer);
// }

// end = clock();
// popTime = (double)(end - start);
// printf("\nPop에 소요 시간: %lfms\n", popTime);

// totalTime = insertTime + popTime;
// printf("전체 소요 시간!: %lfms", totalTime);
