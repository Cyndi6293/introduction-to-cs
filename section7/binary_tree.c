#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//Tree Node
typedef struct node
{
    int Data;
    struct node* Left;
    struct node* Right;
}
node;

//Root of the tree - global
node* Root;

//function that finds number in tree
bool contains(int value);

//function that inserts number in a tree
bool insert(int value);

int main(void)
{
    //Init Root node of Tree
    Root = malloc( sizeof(node) );
    Root->Data = 7;
    Root->Left = NULL;
    Root->Right = NULL;
    //Adding nodes
    node* NewNode;
    NewNode = malloc(sizeof(node));
    NewNode->Data = 3;
    NewNode->Left = NULL;
    NewNode->Right = NULL;
    Root->Left = NewNode;
    NewNode = malloc(sizeof(node));
    NewNode->Data = 9;
    NewNode->Left = NULL;
    NewNode->Right = NULL;
    Root->Right = NewNode;
    NewNode = malloc(sizeof(node));
    NewNode->Data = 6;
    NewNode->Left = NULL;
    NewNode->Right = NULL;
    Root->Left->Right = NewNode;  
    printf("%3d\n%2d %d\n%3d\n", Root->Data, Root->Left->Data, Root->Right->Data, Root->Left->Right->Data);
    printf("-------------------\n");
    //Testing contains()
    printf("%d\n",contains(7));
    printf("%d\n",contains(3));
    printf("%d\n",contains(6));
    printf("%d\n",contains(9));
    printf("%d\n",contains(911));
    printf("%d\n",contains(45));
    printf("%d\n",contains(93));
    printf("%d\n",contains(0));
    printf("%d\n",contains(-9));
    printf("-------------------\n");
    //testing insert()
    assert( insert(11) == true );
    insert(2);
    assert( insert(3) == false);
    insert(111);
    insert(0);
    insert(8);
    printf("%d\n",contains(11));
    printf("%d\n",contains(2));
    printf("%d\n",contains(111));
    printf("%d\n",contains(0));
    printf("%d\n",contains(8));
    printf("%d\n",  Root->Left->Left->Data);
    printf("%d\n",  Root->Left->Left->Left->Data);
    printf("%d\n",  Root->Right->Right->Data);
    printf("%d\n",  Root->Right->Left->Data);
    printf("%d\n",  Root->Right->Right->Right->Data);
}

bool contains(int value)
{
    node* pNode = Root;
    while (pNode != NULL)
    {
        if (pNode->Data == value)
        {            
            return true;
        }
        else if (value > pNode->Data)
        {
            pNode = pNode->Right;
        }
        else if (value < pNode->Data)
        {
            pNode = pNode->Left;
        }
    }
    return false;
}

//assumes that there has at least root node
bool insert(int value)
{
    if ( contains(value) )
    {
        return false;
    }
    else
    {
        node* pNode = Root;
        while (true)
        {            
            if (value > pNode->Data)
            {
                if (pNode->Right == NULL)
                {
                    node* NewNode;
                    NewNode = malloc(sizeof(node));
                    NewNode->Data = value;
                    NewNode->Left = NULL;
                    NewNode->Right = NULL;
                    pNode->Right = NewNode;
                    return true;                
                }
                else
                    pNode = pNode->Right;
                
            }
            else if (value < pNode->Data)
            {
                if (pNode->Left == NULL)
                {
                    node* NewNode;
                    NewNode = malloc(sizeof(node));
                    NewNode->Data = value;
                    NewNode->Left = NULL;
                    NewNode->Right = NULL;
                    pNode->Left = NewNode;
                    return true;                
                }
                else
                    pNode = pNode->Left;
            }
        }
    }
}
