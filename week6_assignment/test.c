#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int Strstr(char *str, char *pat);
int Nfind(char *str, char *pat);
int FastPatternMatching(char *str, char *pat);
int *fail(char *pat);
char *strGenerator(unsigned int sizeOfString, unsigned int seed);

int main()
{
    int sizeOfString;
    int sizeOfPattern;
    clock_t start, end;
    double spentTimeStrstr, spentTimeNfind, spentTimeFastPatternMatching;

    printf("What is the size of the target string in bytes? \n");
    scanf("%d", &sizeOfString);

    printf("What is the size of the pattern in bytes? \n");
    scanf("%d", &sizeOfPattern);

    char *str = strGenerator(sizeOfString, (unsigned int)time(NULL) + 1);
    char *pat = strGenerator(sizeOfPattern, (unsigned int)time(NULL));

    start = clock();
    int result1 = Strstr(str, pat);
    end = clock();
    spentTimeStrstr = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    int result2 = Nfind(str, pat);
    end = clock();
    spentTimeNfind = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    int result3 = FastPatternMatching(str, pat);
    end = clock();
    spentTimeFastPatternMatching = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("The result of Strstr is: %d and it took %lf seconds\n", result1, spentTimeStrstr);
    printf("The result of Nfind is: %d and it took %lf seconds\n", result2, spentTimeNfind);
    printf("The result of FastPatternMatching is: %d and it took %lf seconds\n", result3, spentTimeFastPatternMatching);
}

int Strstr(char *str, char *pat)
{

    int strSize = strlen(str);
    int patSize = strlen(pat);

    int count = 0;
    int isMatch;
    int i = 0;
    while (i < strSize)
    {
        for (int j = 0; j < patSize; j++)
        {
            if (str[i + j] != pat[j]) // 패턴이 맞지 않은 경우
            {
                if (j == 0)
                {
                    i++;
                    break;
                }
                else
                {
                    i += j;
                    break;
                }
            }
            else
            {
                if (j == patSize - 1) // 패턴 매칭이 하나 완료된 경우임. 즉 찾아버린 경우
                {
                    count++;
                    i += patSize;
                    break;
                }
            }
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
    int i = 0;

    while (i < strSize)
    {

        for (int j = 0; j < patSize; j++)
        {
            if (str[i + patSize - 1] != pat[patSize - 1])
            {
                i++;
                break;
            }

            if (str[i + j] != pat[j])
            {
                if (j == 0)
                {
                    i++;
                    break;
                }
                else
                {
                    i += j;
                    break;
                }
            }
            else
            {
                if (j == patSize - 1)
                {
                    count++;
                    i += patSize;
                    break;
                }
            }
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
    int i = 0;
    int j = 0;

    while (1)
    {
        if (i < strSize && j < patSize)
        {
            if (str[i] == pat[j])
            {
                i++;
                j++;
            }
            else if (j == 0)
            {
                i++;
            }
            else
            {
                j = failure[j - 1] + 1;
            }
        }
        else
        {
            if (j == patSize)
            {
                i = i - patSize + 1;
                j = 0;
                count++;
            }
            else // 하나 찾은 경우
            {
                return count;
            }
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

char *strGenerator(unsigned int sizeOfString, unsigned int seed)
{
    srand(seed);
    // a ... z : 97 ... 122 -> 26개
    // A ... Z : 65 ... 90 -> 26개
    int capitalFactor;
    int alphaFactor;

    char *str = malloc(sizeOfString * sizeof(char));

    for (int i = 0; i < sizeOfString; i++)
    {
        // capitalFactor = rand() % 2 ? 65 : 97; // capitalFactor: 65 or 97
        capitalFactor = 65;
        alphaFactor = rand() % 5; // alphaFactor: 0 ... 25
        str[i] = capitalFactor + alphaFactor;
    }
    return str;
}