#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    int *ptr;

    ptr = malloc(sizeof(int) * 10);

    ptr[9] = 10;
    ptr[10] = 11;
    ptr[20] = 111;
    printf("%d\n", ptr[9]);
    printf("%d\n", ptr[10]);
    printf("%d\n", ptr[20]);
    

    return 1;
}