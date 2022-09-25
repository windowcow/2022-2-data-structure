startingPos[0] = 1;

for (i = 1; i < numCols; i++)
{
    for (i = 1; i < numCols; i++)
    {
        int sum = 0;
        if (a[i - 1].col == i)
        {
            sum++;
        }
        startingPos[i] = startingPos[i - 1] + sum;
    }
}
