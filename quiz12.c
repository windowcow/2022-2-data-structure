while (i < lens && j < lenp)
{
    if (string[i] == pat[j])
    {
        i++;
        j++;
    }
    else if (j == 0)
        i++;
    else
    {
        j = failure[j - 1] + 1;
    }
}

for (int k = 0; k < lens; k++)
{
    if (i < lens && j < lenp)
    {
        break;
    }
    if (string[i] == pat[j])
    {
        i++;
        j++;
    }
    else if (j == 0)
        i++;
    else
    {
        j = failure[j - 1] + 1;
    }
}