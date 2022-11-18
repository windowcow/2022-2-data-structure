#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
linkedList에서는 차라리 우선순위 큰 순서대로 들어가게끔 만드는게 훨씬 쉽다.
온 순서대로 넣고 우선순위 큰 애들을 골라서 빼려면 엄청 복잡하다.

*/

typedef struct linkedNode *linkedList;

typedef struct node
{
    int priority;
    char *c;
} node;

typedef struct linkedNode
{
    node *data;
    linkedNode *next;
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

node *makeNode(void)
{
    node *n = malloc(sizeof(node));
    n->priority = rand() % 1000;
    printf("%d ", n->priority);
    n->c = randomStringGenerate();
    return n;
}

linkedList makeNewLinkedList(void)
{
    linkedList l = malloc(sizeof(linkedNode));
    l->data = NULL;
    l->next = NULL;
    return l;
}

void makeHead(linkedList l, node *n)
{
    l->data = n;
}

// link to linked list
void insertNodeToArray(linkedList *linkedListPointer, linkedNode *insertTargetNode)
{
    linkedNode *tempLinkedNode = *linkedListPointer; // 헤드를 받는다. (linkedNode로)

    if (tempLinkedNode->data == NULL)
    {
        tempLinkedNode->data = insertTargetNode->data;
        tempLinkedNode->next = insertTargetNode->next;
        return;
    }

    while (tempLinkedNode -)
}

// priority가 가장 큰 node를 지우는 함수 (끊고 연결해야함)
void popBiggestPriority(linkedList *linkedListPointer)
{
    linkedNode *tempLinkedNode = *linkedListPointer;  // 일단 헤드로 받는다.
    linkedNode *tempLinkedNode2 = *linkedListPointer; // priority가 가장 큰 애를 기록하는 애.
    linkedNode *tempLinkedNode3 = *linkedListPointer; // priority가 가장 큰 애의 앞 애를 기록하는 애.

    // 헤드가 NULL인경우 : 그냥 return
    if (tempLinkedNode->data == NULL)
    {
        return;
    }
    // 헤드만 있는 경우
    else if (tempLinkedNode->next == NULL)
    {
        printf("%d ", tempLinkedNode->data->priority);
        tempLinkedNode->data = NULL;
        tempLinkedNode->next = NULL;
    }
    // 헤드랑 헤드 다음게 있는 경우
    else
    {
        // priority가 가장 큰 애를 찾는다.
        while (tempLinkedNode->next != NULL)
        {
            if (tempLinkedNode->data->priority < tempLinkedNode->next->data->priority)
            {
                tempLinkedNode2 = tempLinkedNode->next; // 다음 놈 기록
                tempLinkedNode3 = tempLinkedNode;
            }
            tempLinkedNode = tempLinkedNode->next;
        }
        // priority가 가장 큰 애를 출력한다.
        printf("%d ", tempLinkedNode2->data->priority);
        // priority가 가장 큰 애를 지운다.
        tempLinkedNode3->next = tempLinkedNode2->next;
    }
    // 다음이 없는 경우에는 최고를 반환하면 된다.
}

int main(void)
{
    srand(time(NULL));
    double insertTime, popTime, totalTime;

    clock_t start, end;

    node **array = makeLinkedList();

    start = clock();
    for (int i = 0; i < 100; i++)
    {

        node *n = makeNode();
        insertNodeToArray(array, n);
    }
    end = clock();

    insertTime = (double)(end - start);
    printf("Insert에 소요 시간: %lfms\n", insertTime);

    start = clock();
    for (int i = 0; i < 100; i++)
    {
        node *n = makeNode(); // 같은 조건을 위해서 넣었습니다.
        popBiggestPriority(array);
    }

    end = clock();
    popTime = (double)(end - start);
    printf("\nPop에 소요 시간: %lfms\n", popTime);

    totalTime = insertTime + popTime;
    printf("전체 소요 시간!: %lfms", totalTime);

    return 0;
}