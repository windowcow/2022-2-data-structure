elements stack[MAX_STACK_SIZE];
offset move[8];
int maze[MAX_ROWS][MAX_COLS];
int mark[MAX_ROWS][MAX_COLS];
int top;

void path(void)
{
    int i, row, col, nextRow, nextCol, dir, found = FALSE;
    element position;

    mark[1][1] = 1;
    top = 0;
    stack[0].row = 1;
    stack[0].col = 1;
    stack[0].dir = 1;

    while (top > -1 && !found)
    {
        position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;
    }
    // 수정한 코드
    while (dir < 4 && !found) // dir : 0...3
    {
        /* move[0].vert : 0 / move[0].horiz : 1 */
        /* move[1].vert : 1 / move[1].horiz : 0 */ 
        /* move[2].vert : 0 / move[2].horiz : -1 */
        /* move[3].vert : -1 / move[3].horiz : 0 */
        nextRow = row + move[dir].vert; //
        nextCol = col + move[dir].horiz;
        if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
            found = TRUE;
        else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])
        {
            mark[nextRow][nextCol] = 1;
            position.row = row;
            position.col = col;
            position.dir = ++dir;
            push(position);
            row = nextRow;
            col = nextCol;
            dir = 0;
        }
        else
            ++dir;
    }

    if (found)
    {
        printf("The path is:\n");
        printf("row col\n");
        for (i = 0; i <= top; i++)
            printf("%2d%5d\n", stack[i].row, stack[i].col);
        printf("%2d%5d\n", row, col);
        printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
    }
    else
        printf("The maze does not have a path\n");
}