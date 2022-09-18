#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    int length[10];
    int *array[10];
    for (int i = 0; i<10; i++){
        length[i] = i+1;
    }

    for (int i = 0; i < 10; i++)
    {
        array[i] = malloc(sizeof(int) * length[i]);
    }

    return 1;
}