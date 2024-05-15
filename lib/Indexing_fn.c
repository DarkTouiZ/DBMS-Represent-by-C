#include <stdio.h>
#include <stdlib.h>
#include "csv_io.c"

// Function to compute maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Function to compute Height of a tree node
int getHeight(Tree *node)
{
    if (!node)
    {
        return 0;
    }
    return node->Height;
}

// Right rotate
Tree *RightRotate(struct Tree *y)
{
    Tree *x = y->Left;
    Tree *T2 = x->Right;

    x->Right = y;
    y->Left = T2;

    y->Height = max(getHeight(y->Left), getHeight(y->Right)) + 1;
    x->Height = max(getHeight(x->Left), getHeight(x->Right)) + 1;

    return x;
}

// Left rotate
Tree *LeftRotate(Tree *x)
{
    Tree *y = x->Right;
    Tree *T2 = y->Left;

    y->Left = x;
    x->Right = T2;

    x->Height = max(getHeight(x->Left), getHeight(x->Right)) + 1;
    y->Height = max(getHeight(y->Left), getHeight(y->Right)) + 1;

    return y;
}

// Get the balance factor
int getBalance(Tree *N)
{
    if (N == NULL)
        return 0;
    return getHeight(N->Left) - getHeight(N->Right);
}

// Function to insert a new node into the AVL tree
Tree *insertNode(Tree *root, Adjacent_Node *ptr)
{
    char value[100];
    strcpy(value, ptr->Data);
    if (!root)
    {
        // root->Ptr = root;
        Tree *newNode = (Tree *)malloc(sizeof(Tree));
        strcpy(newNode->Key, value); // Copy the string Key
        newNode->Left = newNode->Right = NULL;
        newNode->Height = 1;
        newNode->Ptr = ptr;
        return newNode;
    }

    if ((strcmp(value,"NULL") == 0))
    {
        return root;
    }
    int cmp = strcmp(value, root->Key);
    if (cmp < 0)
    {
        root->Left = insertNode(root->Left, ptr);
    }
    else if (cmp > 0)
    {
        root->Right = insertNode(root->Right, ptr);
    }

    // Update Height and balance the tree
    root->Height = 1 + max(getHeight(root->Left), getHeight(root->Right));
    // Perform AVL balancing (rotation) if needed
    int balance = getBalance(root);
    if (balance > 1 && cmp < 0)
        return RightRotate(root);

    if (balance < -1 && cmp > 0)
        return LeftRotate(root);

    if (balance > 1 && cmp < 0)
    {
        root->Left = LeftRotate(root->Left);
        return RightRotate(root);
    }

    if (balance < -1 && cmp > 0)
    {
        root->Right = RightRotate(root->Right);
        return LeftRotate(root);
    }
    return root;
}

int binarySearchString(const char *arr[], int size, const char *target)
{
    int Left = 0;
    int Right = size - 1;

    while (Left <= Right)
    {
        int mid = Left + (Right - Left) / 2;
        int cmp = strcmp(target, arr[mid]);

        if (cmp == 0)
        {
            return mid; // Found the target string
        }
        else if (cmp < 0)
        {
            Right = mid - 1; // Search the Left half
        }
        else
        {
            Left = mid + 1; // Search the Right half
        }
    }

    return -1; // Target string not found
}

// Function to search for a string in the binary tree
Tree *searchNode(Tree *root, const char *target)
{
    if (!root || strcmp(root->Key, target) == 0)
    {
        return root; // When no found return "NULL"
    }

    int cmp = strcmp(target, root->Key);
    if (cmp < 0)
    {
        return searchNode(root->Left, target);
    }
    else
    {
        return searchNode(root->Right, target);
    }
}

// Function to print the AVL tree (in-order traversal)
void printTree(Tree *root)
{
    if (root)
    {
        printTree(root->Left);
        printf("%s ", root->Key);
        printTree(root->Right);
    }
}

// Example usage
int main()
{

    FILE *file = read_csv("../bin/test.csv");
    if (file == NULL)
    {
        return 1;
    }

    Node *head = csv_to_linked_list(file);
    fclose(file);

    Tree *avlRoot = NULL;
    Node *currNode = head;
    Adjacent_Node *currAdjNode = currNode->Next->Next->Head;
    while (currAdjNode)
    {
        avlRoot = insertNode(avlRoot, currAdjNode);
        currAdjNode = currAdjNode->Next;
    }

    // Print the AVL tree
    printf("In-order traversal of AVL tree %d:\n", avlRoot->Height);
    printTree(avlRoot);

    // search the AVL tree
    const char *target = "Bengaluru";
    Tree *result = searchNode(avlRoot, target);
    if (result)
    {
        printf("\n'%s' found in the binary tree.", target);
    }
    else
    {
        printf("\n'%s' not found in the binary tree.", target);
    }

    return 0;
}
