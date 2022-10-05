#include <stdio.h>
#include <string.h>
#include <time.h>

int Strstr(char *str, char *pat);
// int strstr(char *s, char *pat);
int main()
{
    char *str = "ProgrammingAssignmentProgrammingAssignmentProgrammingAssignmentProgrammingAssignmentProgrammingAssignmentProgrammingAssignmentProgrammingAssignmentProgrammingAssignmentProgrammingAssignmentProgrammingAssignmentProgrammingAssignmentProgrammingAssignmentProgrammingAssignmentProgrammingAssignment";
    char *pat = "gram";
    int result = Strstr(str, pat);
    printf("%d", result);
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
