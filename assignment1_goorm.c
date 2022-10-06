#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int Strstr(char *str, char *pat);
int Nfind(char *str, char *pat);
int FastPatternMatching(char *str, char *pat);
int *fail(char *pat);

int main()
{
    char *str = malloc(1000000);
    scanf("%s", str);
    char *pat = malloc(1000000);
    scanf("%s", pat);

    int result1 = Strstr(str, pat);
    printf("%d\n", result1);
    int result2 = Nfind(str, pat);
    printf("%d\n", result2);
    int result3 = FastPatternMatching(str, pat);
    printf("%d\n", result3);
}

int Strstr(char *str, char *pat)
{
    int strSize = strlen(str);
    int patSize = strlen(pat);

    int count = 0;
    int isMatch;
    for (int i = 0; i < strSize; i++)
    {
        isMatch = 1;
        for (int j = 0; j < patSize; j++)
        {
            if (str[i + j] != pat[j])
            {
                i += j;
                isMatch = 0;
                break;
            }
        }
        if (isMatch)
        {
            count++;
        }
    }
    return count;
}

int Nfind(char *str, char *pat)
{
    int strSize = strlen(str);
    int patSize = strlen(pat);

    int count = 0;
    int isMatch;
    for (int i = 0; i < strSize; i++)
    {
        isMatch = 1;
        if (str[i + patSize - 1] != pat[patSize - 1])
        {
            continue;
        }
        for (int j = 0; j < patSize - 1; j++)
        {
            if (str[i + j] != pat[j])
            {
                i += j;
                isMatch = 0;
                break;
            }
        }
        if (isMatch)
        {
            count++;
        }
    }
    return count;
}

int FastPatternMatching(char *str, char *pat)
{
    int strSize = strlen(str);
    int patSize = strlen(pat);

    int count = 0;
    int isMatch;
    int *failure = fail(pat);

    for (int i = 0; i < strSize; i++)
    {
        isMatch = 1;
        for (int j = 0; j < patSize; j++)
        {
            if (str[i + j] != pat[j]) // 패턴의 0...j-1까지 일치하고 j는 일치하지 않는 경우
            {
                if (j == 0)
                {
                    isMatch = 0;
                    break;
                }
                else
                { // 패턴의 0...j-1까지 일치하고 j는 일치하지 않는 경우 중 j == 0 은 아닌 경우 (패턴의 적어도 앞 1개는 일치하는 경우)
                    j = failure[j - 1];
                    isMatch = 0;
                    break;
                }
                i += j;
            }
        }
        // 패턴이 0...patSize-1까지 일치하는 경우 아래가 실행된다.

        if (isMatch)
        {
            count++;
        }
    }
    return count;
}

int *fail(char *pat)
{
    int n = strlen(pat);
    int *failure = (int *)malloc(sizeof(int) * n);
    failure[0] = -1;
    int i, j;
    for (j = 1; j < n; j++)
    {
        i = failure[j - 1];
        while (pat[j] != pat[i + 1] && i >= 0)
            i = failure[i];
        if (pat[j] == pat[i + 1])
        {
            failure[j] = i + 1;
        }
        else
        {
            failure[j] = -1;
        }
    }
    return failure;
}
