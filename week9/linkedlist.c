#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode
{
    int data[4];
    listPointer link;
};

int main()
{
    listPointer first = NULL;
    MALLOC(first, sizeof(*first));
    strcpy(first->data, "DAY");
    first->link = NULL;
}

void insert50(listPointer *first, listPointer x) // *first 는 첫번째 노드를 의미한다.
{
    listPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->data = 50;
    if (*first == NULL)
    {
        temp->link = x->link;
        x->link = temp;
    }
    else
    {
        temp->link = NULL;
        *first = temp;
    }
}

// void delete (listPoint *first, listPointer trail, listPointer x)
// {
//     if (trail)
//         trail->link = NULL;

// }

// quiz19 : trail이 주어지지 않은 경우에 x 삭제하기
void delete (listPointer *first, listPointer x)
{
    listPointer trail = *first; // 1. 일단 trail이라는 포인터로 linked list의 맨 앞을 가리키도록 했습니다.
                                //    trail이라는 포인터는 x의 앞이 되도록 함이 목적입니다.
    while (trail->link)         // 2. trail이라는 포인터가 마지막이 아닌 경우를 의미합니다. (trail의 다음이 NULL이 아닌 경우)
    {
        if (trail->link == x) // 3.trail의 다음이 x인 경우를 의미합니다.
        {
            trail->link = x->link; // 4. trail의 다음이 x인 경우에는 x의 link를 trail의 link로 받으면 됩니다.
            free(x);               // 5. 그 경우에 x는 메모리를 이유 없이 사용하는 것이기 때문에 메모리에서 해제합니다.
        }
        else
        {
            trail = trail->link; // 6. trail의 다음이 x가 아닌 경우에는  trail을 그 다음 노드로 변경하고 루프를 진행합니다.
        }
    }
}

// Quiz 20 : multi-queues 에서 rear을 따로 가리키는 리스트가 없는 경우에 addq를 작성해라.
void addq(int i, element item)
{
    queuePointer temp;
    queuePointer temp1;
    MALLOC(temp, sizeof(*temp));
    temp->data = item;
    temp->link = NULL;
    if (front[i])
    {
        while (temp1->link) // temp1은 맨 뒤를 가리키기 위해 만든 포인터 변수이다.
        {
            temp1 = temp1.link; // temp1이 마지막이 아닌 경우에 temp1을 뒤에 따라오는 원소를 가리키게 해준다.
        }
        temp1.link = temp; // 마지막을 찾았고 이제 그 마지막의 다음을 아까 만든 temp로 만들어준다.
    }
    else
    {
        front[i] = temp; // front[i]가 비어있는 경우에는 temp가 그 첫번째가 되도록 한다.
    }
}

// Quiz 21 : erase 를 while 문을 쓰지 않고 작성하기

void erase(polyPointer *ptr)
{
    // *ptr은 polynomial의 항을 의미한다. 그러나 그 항은 우리가 맘대로 저장할 때 맨 앞을 의미한다.
    for (; *ptr; *ptr = (*ptr)->link) //마지막 parameter인 식은 루프 돈 이후에 일어난다. 따라서 저렇게 해도 된다.
    {
        free(ptr); // *ptr이 NULL이 아닌 이상 계속 해제한다.
    }
}