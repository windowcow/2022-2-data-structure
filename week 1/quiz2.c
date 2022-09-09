#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int list[3]; // 어차피 3개인거 알기 때문에 이렇게 함
    int x, y, z;

    x = rand() % 123;
    y = rand() % 123;
    z = rand() % 123;

    list[0] = x;
    list[1] = y;
    list[2] = z;

    printf("<정렬 전> : %d, %d, %d\n", list[0], list[1], list[2]);

    // 무작위 상태

    if (x >= y)
    {
        // [y, x, _] 의 상태가 되도록
        list[0] = y;
        list[1] = x;
    }
    else
    {
        list[0] = x;
        list[1] = y;
    }

    // list[0], list[1]의 대소는 가려진 상태

    if (list[2] >= list[1])
    {
        printf("<정렬 후1> : %d, %d, %d", list[0], list[1], list[2]);
        return 0;
    }

    if (list[1] > list[2] && list[2] >= list[0])
    {
        int tmp = list[2];
        list[2] = list[1];
        list[1] = tmp;
        printf("<정렬 후2> : %d, %d, %d", list[0], list[1], list[2]);
        return 0;
    }
    if (list[2] < list[0])
    {
        int tmp0 = list[0];
        int tmp1 = list[1];
        list[0] = list[2];
        list[1] = tmp0;
        list[2] = tmp1;
        printf("<정렬 후3> : %d, %d, %d", list[0], list[1], list[2]);
        return 0;
    }

    return 0;
}