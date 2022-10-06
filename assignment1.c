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
    printf("%lu\n\n", sizeof(char));

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

    // printf("Generated string: %s\n", str);
    // printf("Generated pattern: %s\n", pat);

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

    // printf("%d\n", result1);
    // printf("%d\n", result2);
    // printf("%d\n", result3);
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
        capitalFactor = rand() % 2 ? 65 : 97; // capitalFactor: 65 or 97
        alphaFactor = rand() % 26;            // alphaFactor: 0 ... 25
        str[i] = capitalFactor + alphaFactor;
    }
    return str;
}