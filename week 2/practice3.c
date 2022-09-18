#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    unsigned i = 10;
    int count = 0;

    for (i = 10; i >= 0; i--)
    {
        printf("%u\n", i);
        count++;
        if (count == 30)
        {
            break;
        }
    }
}