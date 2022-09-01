#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{

    int row, column;

    scanf("%d %d", &row, &column);

    // int **pi의 의미는 int 를 담는 포인터를 담는 포인터가 pi라는 뜻임
    int **pi;

    // pi에다가 정수 포인터 (int * 타입을 말임) row개 담을 수 있는 만큼의 크기를 할당한다.
    pi = (int **)malloc(sizeof(int *) * row); // 이제 pi[1]같이 쓸 수 있음

    for (int i = 0; i < row; i++)
    {
        pi[i] = (int *)malloc(sizeof(int) * column); // 이제 pi[1][1] 같이 쓸 수 있음
        for (int j = 0; j < column; j++)
        {
            // pi[i][j] = malloc ~~ 이렇게 할 필요는 없는 이유는 pi[i][j]에 값 넣어도 어차피 int만큼 크기만큼 건너 건너 넣음
            // 즉 pi[i] 처럼 적을때 다음 차원의 공간까지 나눠서 쓸 수 있게 한거임 (2차원 배열의 안쪽까지)

            pi[i][j] = rand() % 100; // 0...99 의 정수임
        }
    }

    //이제 값이 차있는 배열을 출력하면 됨
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%d ", pi[i][j]);
        }
        printf("\n");
    }

    // 이제 pi[3] 이렇게 접근할 수 있다.
    return 0;
}