#include <stdio.h>
#include <stdlib.h>

void stringremove(char *, int, int);

int main(void)
{
    char string[] = "Hello, world!";
    stringremove(string, 3, 33);
}

void stringremove(char *s, int i, int j)
{
    // lens means a length of a string s
    int lens = 0;

    while (s[lens] != '\0')
    {
        lens++;
    }

    if (i + j - 1 <= lens - 1)
    {
        for (int k = i; k <= lens - i - j + 1; k++)
        {
            s[k] = s[k + j];
        }
        for (int k = lens - i - j + 1; k <= lens; k++)
        {
            s[k] = '\0';
        }
    }
    else
    {
        s[i] = '\0';
        for (int k = i + 1; k <= lens; k++)
        {
            s[k] = '\0';
        }
    }

    printf("\nThe result : %s\n", s);
}