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
    Tree *x = y->LeftChild;
    Tree *T2 = x->RightChild;

    x->RightChild = y;
    y->LeftChild = T2;

    y->Height = max(getHeight(y->LeftChild), getHeight(y->RightChild)) + 1;
    x->Height = max(getHeight(x->LeftChild), getHeight(x->RightChild)) + 1;

    return x;
}

// Left rotate
Tree *LeftRotate(Tree *x)
{
    Tree *y = x->RightChild;
    Tree *T2 = y->LeftChild;

    y->LeftChild = x;
    x->RightChild = T2;

    x->Height = max(getHeight(x->LeftChild), getHeight(x->RightChild)) + 1;
    y->Height = max(getHeight(y->LeftChild), getHeight(y->RightChild)) + 1;

    return y;
}

// Get the balance factor
int getBalance(Tree *N)
{
    if (N == NULL)
        return 0;
    return getHeight(N->LeftChild) - getHeight(N->RightChild);
}

// Function to insert a new node into the AVL tree
Tree *insertNode(Tree *root, Adjacent_Node *Actual_Ptr, int Count)
{
    // get value from Ptr
    char value[100];
    strcpy(value, Actual_Ptr->Data);

    // Handle for NULL value in Data
    if ((strcmp(value,"NaN") == 0))
    {
        return root;
    }

    // Insert Node in Tree
    if (!root)
    {
        // root->Actual_Ptr = root;
        Tree *newNode = (Tree *)malloc(sizeof(Tree));
        if(newNode == NULL){
            return NULL;
        }

        strcpy(newNode->Key, value); // Copy the string Key
        newNode->LeftChild = newNode->RightChild = NULL;
        newNode->Height = 1;
        newNode->Actual_Ptr = Actual_Ptr;
        newNode->RowIndex = Count;
        return newNode;
    }

    int cmp = strcmp(value, root->Key);
    if (cmp < 0)
    {
        root->LeftChild = insertNode(root->LeftChild, Actual_Ptr, Count);
    }
    else if (cmp > 0)
    {
        root->RightChild = insertNode(root->RightChild, Actual_Ptr, Count);
    }

    // Update Height and balance the tree
    root->Height = 1 + max(getHeight(root->LeftChild), getHeight(root->RightChild));
    // Perform AVL balancing (rotation) if needed
    int balance = getBalance(root);
    if (balance > 1 && cmp < 0)
        return RightRotate(root);

    if (balance < -1 && cmp > 0)
        return LeftRotate(root);

    if (balance > 1 && cmp < 0)
    {
        root->LeftChild = LeftRotate(root->LeftChild);
        return RightRotate(root);
    }

    if (balance < -1 && cmp > 0)
    {
        root->RightChild = RightRotate(root->RightChild);
        return LeftRotate(root);
    }
    return root;
}

// Function to print the AVL tree (in-order traversal)
void printTree(Tree *root)
{
    if (root)
    {
        printTree(root->LeftChild);
        printf("%s ", root->Key);
        printTree(root->RightChild);
    }
}

Tree* CreateAVLTree(Adjacent_Node* Curr_Adj_Node){
    Tree* AVLRoot = NULL;

    int Count = 0;
    while(Curr_Adj_Node != NULL)
    {
        AVLRoot = insertNode(AVLRoot, Curr_Adj_Node, Count);
        if(AVLRoot == NULL){
            return NULL; // can't allocate memory
        }
        Count++;
        Curr_Adj_Node = Curr_Adj_Node->Next;
    }
    return AVLRoot;
}

// // Example usage
// int main()
// {

//     FILE *file = read_csv("../bin/test.csv");
//     if (file == NULL)
//     {
//         return 1;
//     }

//     Node *head = csv_to_linked_list(file);
//     fclose(file);

//     Node *currNode = head;
//     Adjacent_Node *currAdjNode = currNode->Next->Next->Adj_Head;
    
//     Tree *avlRoot = CreateAVLTree(currAdjNode);

//     // Print the AVL tree
//     printf("In-order traversal of AVL tree %d:\n", avlRoot->Height);
//     printTree(avlRoot);

//     // search the AVL tree
//     const char *target = "Bengaluru";
//     Tree *result = searchNode(avlRoot, target);
//     if (result)
//     {
//         printf("\n'%s' found in the binary tree.", target);
//     }
//     else
//     {
//         printf("\n'%s' not found in the binary tree.", target);
//     }

//     return 0;
// }
