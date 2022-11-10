typedef struct node
{
    char data;
    nodePointer leftChild;
    nodePointer rightChild;
} node;

// 아직 트리가 되지 않은 노드의 그룹을 의미한다.
typedef struct nodeGroup
{
    nodePointer node;
    nodePointer next;
} nodeGroup;