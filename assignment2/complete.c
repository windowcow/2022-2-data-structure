#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node *nodePointer;
typedef struct linkedNode *linkedNodePointer;

typedef struct node
{
    char data;
    nodePointer leftChild;
    nodePointer rightChild;
} node;

typedef struct linkedNode
{
    char data;
    linkedNodePointer next;
} linkedNode;

char *parser(char *input)
{
    char *charArray = (char *)malloc(sizeof(char) * 63);
    char *inputStr = (char *)malloc(sizeof(char) * 189);

    strcpy(inputStr, input);

    for (int i = 0; i < 63; i++)
    {
        charArray[i] = '\0';
    }

    char *temp = strtok(inputStr, ", ");

    int i = 0;

    while (temp != NULL)
    {
        charArray[i] = temp[0];
        temp = strtok(NULL, ", ");
        i++;
    }

    return charArray;
}

int findIndex(char *inputString, char c)
{
    int stringLength = strlen(inputString);
    int i = 0;
    while (inputString[i] != c)
    {
        i++;
    }

    if (i == stringLength)
    {
        return -1;
    }
    else
    {
        return i;
    }
}

nodePointer makeTree(char *inorder, char *postorder)
{

    nodePointer root = (nodePointer)malloc(sizeof(node));

    int inordersize = strlen(inorder);
    int postordersize = strlen(postorder);
    int index = -1;

    if (inordersize == 1)
    {
        root->data = inorder[0];
        root->leftChild = NULL;
        root->rightChild = NULL;
        return root;
    }

    for (int j = postordersize - 1; j >= 0; j--)
    {
        for (int i = 0; i < inordersize; i++)
        {
            if (inorder[i] == postorder[j])
            {
                index = i;
                root->data = postorder[j];
                // printf("root->data : %c\n", root->data);
                break;
            }
        }
        if (index != -1)
        {
            break;
        }
    }

    if (index == -1)
    {
        return NULL;
    }
    // 여기서 나온 i는 inorder에서 postorder의 마지막 글자가 위치한 인덱스이다.

    else if (index == 0)
    {
        root->leftChild = NULL;

        char *rightInorder = (char *)malloc(sizeof(char) * (inordersize - index));

        rightInorder[strlen(inorder) - index - 1] = '\0';

        for (int j = 0; j < strlen(inorder) - index - 1; j++)
        {
            rightInorder[j] = inorder[index + j + 1];
        }

        root->rightChild = makeTree(rightInorder, postorder);
    }
    else if (index == inordersize - 1)
    {
        root->rightChild = NULL;

        char *leftInorder = (char *)malloc(sizeof(char) * (index + 1));

        leftInorder[index] = '\0';

        for (int j = 0; j < index; j++)
        {
            leftInorder[j] = inorder[j];
        }

        root->leftChild = makeTree(leftInorder, postorder);
    }
    else
    {
        char *leftInorder = (char *)malloc(sizeof(char) * (index + 1));
        char *rightInorder = (char *)malloc(sizeof(char) * (inordersize - index));

        leftInorder[index] = '\0';
        rightInorder[strlen(inorder) - index - 1] = '\0';

        for (int j = 0; j < strlen(inorder) - index - 1; j++)
        {
            rightInorder[j] = inorder[index + j + 1];
        }

        for (int j = 0; j < index; j++)
        {
            leftInorder[j] = inorder[j];
        }

        root->leftChild = makeTree(leftInorder, postorder);
        root->rightChild = makeTree(rightInorder, postorder);
    }

    return root;
}

void inorder(nodePointer ptr)
{
    if (ptr)
    {
        inorder(ptr->leftChild);
        printf("%c", ptr->data);
        inorder(ptr->rightChild);
    }
}

void postorder(nodePointer ptr)
{
    if (ptr)
    {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data);
    }
}

void preorder(nodePointer ptr)
{
    if (ptr)
    {
        printf("%c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void treePrinter(nodePointer ptr)
{
    printf("/");
}

int treeHeight(nodePointer root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int left_height = treeHeight(root->leftChild);
        int right_height = treeHeight(root->rightChild);

        if (left_height > right_height)
        {
            return left_height + 1;
        }
        else
        {
            return right_height + 1;
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
    // printf("canvasWidth : %d, canvasHeight : %d\n", canvasWidth, canvasHeight);

    return canvas;
}

void drawSubtree(char **canvas, int row, int col, nodePointer ptr)
{
    int height = treeHeight(ptr);
    int legsize;
    if (height == 1)
    {
        legsize = 0;
    }
    else if (height == 2)
    {
        legsize = 1;
    }
    else
    {
        legsize = relativeIndexOfRoot(height - 1);
    }

    // printf("legsize : %d\n", legsize);

    if (ptr == NULL)
    {
        return;
    }
    if (ptr->data == NULL)
    {
        return;
    }
    // 루트의 표시

    canvas[row][col] = ptr->data;

    if (ptr->leftChild)
    {
        for (int i = 1; i < legsize + 1; i++)
        {

            canvas[row + i][col - i] = '/';
        }
        drawSubtree(canvas, row + legsize + 1, col - legsize - 1, ptr->leftChild);
    }
    if (ptr->rightChild)
    {
        for (int i = 1; i < legsize + 1; i++)
        {

            canvas[row + i][col + i] = '\\';
        }
        drawSubtree(canvas, row + legsize + 1, col + legsize + 1, ptr->rightChild);
    }
}

int main()
{
    char *input1 = (char *)malloc(sizeof(char) * 189);
    char *input2 = (char *)malloc(sizeof(char) * 189);

    char *inorderArray;   // = (char *)malloc(sizeof(char) * 63);
    char *postorderArray; // = (char *)malloc(sizeof(char) * 63);

    // printf("inorder : ");
    scanf("%[^\n]s", input1);
    inorderArray = parser(input1);

    // 버퍼 초기화
    getchar();

    // printf("postorder : ");
    scanf("%[^\n]s", input2);
    postorderArray = parser(input2);

    nodePointer root = makeTree(inorderArray, postorderArray);

    int rootHeight = treeHeight(root);
    int canvaswidth = 2 * relativeIndexOfRoot(rootHeight) + 1;
    int canvasheight = relativeIndexOfRoot(rootHeight) + 1;
    int rootColIndex = relativeIndexOfRoot(rootHeight);

    // inorder(root);
    // printf("\n");
    // postorder(root);
    // printf("\n");
    // preorder(root);

    // printf("\n");
    // printf("height : %d\n", rootHeight);

    char **canvas = makeEmptyCanvas(rootHeight);

    drawSubtree(canvas, 0, rootColIndex, root);

    for (int i = 0; i < canvasheight; i++)
    {
        for (int j = 0; j < canvaswidth; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }

    return 0;
}