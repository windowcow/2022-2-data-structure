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
                printf("root->data : %c\n", root->data);
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

void treePrinter(nodePointer ptr)
{
    printf("/");
}

int main()
{
    char *input1 = (char *)malloc(sizeof(char) * 189);
    char *input2 = (char *)malloc(sizeof(char) * 189);

    char *inorderArray;   // = (char *)malloc(sizeof(char) * 63);
    char *postorderArray; // = (char *)malloc(sizeof(char) * 63);

    printf("inorder : ");
    scanf("%[^\n]s", input1);
    inorderArray = parser(input1);

    // 버퍼 초기화
    getchar();

    printf("postorder : ");
    scanf("%[^\n]s", input2);
    postorderArray = parser(input2);

    nodePointer root = makeTree(inorderArray, postorderArray);

    inorder(root);
    printf("\n");
    postorder(root);

    return 0;
}