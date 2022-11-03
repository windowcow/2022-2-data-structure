#include <stdio.h>

int main()
{
    for (int i=0; i < 10; i++)
    {
        printf("1: %d\n", i);
        i = i + 1;


        printf("2: %d\n", i);
    }
    return 0;
}