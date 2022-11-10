#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node *nodePointer;

typedef struct node
{
    char data;
    nodePointer leftChild;
    nodePointer rightChild;
    nodePointer leftGroup;
    nodePointer rightGroup;
} node;

nodePointer *makeEmptyGroup(void)
{
    nodePointer *emptyGroup = (nodePointer *)malloc(sizeof(nodePointer) * 63);

    for (int i = 0; i < 63; i++)
    {
        emptyGroup[i] = (nodePointer)malloc(sizeof(node));
        emptyGroup[i]->data = '0';
        emptyGroup[i]->leftChild = NULL;
        emptyGroup[i]->rightChild = NULL;
        emptyGroup[i]->leftGroup = NULL;
        emptyGroup[i]->rightGroup = NULL;
    }

    return emptyGroup;
}

nodePointer *strToTempNode(char *input)
{
    char *inputStr = (char *)malloc(sizeof(char) * 189);
    strcpy(inputStr, input);

    nodePointer *tempNodeGroup = (nodePointer *)malloc(sizeof(nodePointer) * 63);

    // 초기화
    tempNodeGroup = makeEmptyGroup();

    char *temp = strtok(inputStr, ", ");

    int i = 0;
    while (temp != NULL)
    {
        tempNodeGroup[i]->data = temp[0];
        tempNodeGroup[i]->leftChild = NULL;
        tempNodeGroup[i]->rightChild = NULL;
        tempNodeGroup[i]->leftGroup = NULL;
        tempNodeGroup[i]->rightGroup = NULL;
        temp = strtok(NULL, ", ");
        i++;
    }

    return tempNodeGroup;
}

char popLastNodeindex(nodePointer *nodeGroup)
{
    int i = 0;
    while (nodeGroup[i]->data != '0')
    {
        i++;
    }
    return nodeGroup[i - 1]->data;
}

node makeAsRoot(char c, nodePointer *nodeGroup)
{
    int i = 0;

    while (nodeGroup[i]->data != '0')
    {
        if (nodeGroup[i]->data == c)
        {
            node temp = *nodeGroup[i];
            nodeGroup[i]->data = '0';
            return temp;
        }
        i++;
    }
}

node makeTree(node *root, nodePointer *leftNodeGroup, nodePointer *rightNodeGroup)
{
    root->data = popLastNode(leftNodeGroup).data;
}

int main(void)
{
    char *input = "A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z";
    nodePointer *tempNodeGroup = strToTempNode(input);

    return 0;
}