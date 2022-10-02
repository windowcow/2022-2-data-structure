#include <stdio.h>

int strnchar(char *, char);
int main(void)
{
    int result;
    result = strnchar("sung kyun kwan", 'n');
    printf("%d", result);
}

int strnchar(char *s, char p)
{
    int ans = 0;
    // s is starting point of string. and s + 1 means the starting point of the next char.
    while (*s != '\0')
    {
        if (*s == p)
        {
            ans = ans + 1;
        }
        s = s + 1;
    }
    return ans;
}