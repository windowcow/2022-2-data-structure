#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node *nodePointer;

typedef struct node
{
    char data;
    nodePointer leftChild;
    nodePointer rightChild;
} node;

char *parser(char *inputString)
{
    char *resultString = (char *)malloc(sizeof(char) * 63);

    for (int i = 0; i < 63; i++)
    {
        resultString[i] = '\0';
    }

    char *temp = strtok(inputString, ", ");

    int i = 0;

    while (temp != NULL)
    {
        resultString[i] = temp[0];
        temp = strtok(NULL, ", ");
        i++;
    }

    return resultString;
}

nodePointer makeTree(char *inorder, char *postorder)
{

    nodePointer root = (nodePointer)malloc(sizeof(node));

    int inorderSize = strlen(inorder);
    int postorderSize = strlen(postorder);
    int foundIndex = -1;

    if (inorderSize == 1)
    {
        root->data = inorder[0];
        root->leftChild = NULL;
        root->rightChild = NULL;
        return root;
    }

    for (int j = postorderSize - 1; j >= 0; j--)
    {
        for (int i = 0; i < inorderSize; i++)
        {
            if (inorder[i] == postorder[j])
            {
                foundIndex = i;
                root->data = postorder[j];
                break;
            }
        }
        if (foundIndex != -1)
        {
            break;
        }
    }

    if (foundIndex == -1)
    {
        return NULL;
    }
    // 여기서 나온 i는 inorder에서 postorder의 마지막 글자가 위치한 인덱스이다.

    else if (foundIndex == 0)
    {
        root->leftChild = NULL;

        char *rightInorder = (char *)malloc(sizeof(char) * (inorderSize - foundIndex));

        rightInorder[strlen(inorder) - foundIndex - 1] = '\0';

        for (int j = 0; j < strlen(inorder) - foundIndex - 1; j++)
        {
            rightInorder[j] = inorder[foundIndex + j + 1];
        }

        root->rightChild = makeTree(rightInorder, postorder);
    }
    else if (foundIndex == inorderSize - 1)
    {
        root->rightChild = NULL;

        char *leftInorder = (char *)malloc(sizeof(char) * (foundIndex + 1));

        leftInorder[foundIndex] = '\0';

        for (int j = 0; j < foundIndex; j++)
        {
            leftInorder[j] = inorder[j];
        }

        root->leftChild = makeTree(leftInorder, postorder);
    }
    else
    {
        char *leftInorder = (char *)malloc(sizeof(char) * (foundIndex + 1));
        char *rightInorder = (char *)malloc(sizeof(char) * (inorderSize - foundIndex));

        leftInorder[foundIndex] = '\0';
        rightInorder[strlen(inorder) - foundIndex - 1] = '\0';

        for (int j = 0; j < strlen(inorder) - foundIndex - 1; j++)
        {
            rightInorder[j] = inorder[foundIndex + j + 1];
        }

        for (int j = 0; j < foundIndex; j++)
        {
            leftInorder[j] = inorder[j];
        }

        root->leftChild = makeTree(leftInorder, postorder);
        root->rightChild = makeTree(rightInorder, postorder);
    }

    return root;
}

int treeHeight(nodePointer root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int leftHeight = treeHeight(root->leftChild);
        int rightHeight = treeHeight(root->rightChild);

        if (leftHeight > rightHeight)
        {
            return leftHeight + 1;
        }
        else
        {
            return rightHeight + 1;
        }
    }
}

int relativeIndexOfRoot(int height)
{
    if (height == 1)
    {
        return 0;
    }
    else
    {
        int result = 1;

        for (int i = 2; i < height; i++)
        {
            result *= 2;
        }

        return 3 * result - 1;
    }
}

char **makeEmptyCanvas(int height) // root의 height를 받는다.
{
    int mid = relativeIndexOfRoot(height);

    int canvasWidth = 2 * mid + 1; // 열의 수
    int canvasHeight = mid + 1;    // 행의 수

    char **canvas = (char **)malloc(sizeof(char *) * canvasHeight);

    for (int i = 0; i < canvasHeight; i++)
    {
        canvas[i] = (char *)malloc(sizeof(char) * canvasWidth);
    }

    for (int i = 0; i < canvasHeight; i++)
    {
        for (int j = 0; j < canvasWidth; j++)
        {
            canvas[i][j] = ' ';
        }
    }

    return canvas;
}

void drawSubtree(char **canvas, int row, int col, nodePointer ptr)
{
    int height = treeHeight(ptr);
    int legSize;
    if (height == 1)
    {
        legSize = 0;
    }
    else if (height == 2)
    {
        legSize = 1;
    }
    else
    {
        legSize = relativeIndexOfRoot(height - 1);
    }

    if (ptr == NULL)
    {
        return;
    }
    if (ptr->data == NULL)
    {
        return;
    }

    canvas[row][col] = ptr->data;

    if (ptr->leftChild)
    {
        for (int i = 1; i < legSize + 1; i++)
        {

            canvas[row + i][col - i] = '/';
        }
        drawSubtree(canvas, row + legSize + 1, col - legSize - 1, ptr->leftChild);
    }
    if (ptr->rightChild)
    {
        for (int i = 1; i < legSize + 1; i++)
        {

            canvas[row + i][col + i] = '\\';
        }
        drawSubtree(canvas, row + legSize + 1, col + legSize + 1, ptr->rightChild);
    }
}

int main()
{
    char *input1 = (char *)malloc(sizeof(char) * 189);
    char *input2 = (char *)malloc(sizeof(char) * 189);
    char *inorderArray;
    char *postorderArray;

    scanf("%[^\n]s", input1);
    inorderArray = parser(input1);

    // 버퍼 초기화
    getchar();

    scanf("%[^\n]s", input2);
    postorderArray = parser(input2);

    nodePointer root = makeTree(inorderArray, postorderArray);

    int rootHeight = treeHeight(root);
    int rootRelativeIndex = relativeIndexOfRoot(rootHeight);

    int canvasWidth = 2 * rootRelativeIndex + 1;
    int canvasHeight = rootRelativeIndex + 1;

    char **canvas = makeEmptyCanvas(rootHeight);

    drawSubtree(canvas, 0, rootRelativeIndex, root);

    for (int i = 0; i < canvasHeight; i++)
    {
        for (int j = 0; j < canvasWidth; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }

    return 0;
}