void MakeIndexing(Node *Table_Head)
{
    Tree *Root = CreateAVLTree(Table_Head->Adj_Head);

    if (Root == NULL)
    {
        printf("Failed to Create Indexing by Memory issue");
        return;
    }

    Table_Head->Indexing_Ptr = Root;
    Table_Head->isIndexing = true;
}

// Function to search for a string in the binary tree
Tree *Search_Tree_Node(Tree *Root, char *Target)
{
    if (Root == NULL)
    {
        return NULL; // not found
    }

    int Cmp = strcmp(Target, Root->Key);
    if (Cmp == 0)
    {
        return Root;
    }
    else if (Cmp < 0)
    {
        return Search_Tree_Node(Root->LeftChild, Target);
    }
    else
    {
        return Search_Tree_Node(Root->RightChild, Target);
    }
}

Adjacent_Node *Search_Adj_Node(Node *Table_Head, char *Target, int *Return_RowIndex)
{
    Adjacent_Node *Actual_Data;

    if (Table_Head->isIndexing)
    { // Search in Tree
        Tree *get_TreeNode = Search_Tree_Node(Table_Head->Indexing_Ptr, Target);
        if (get_TreeNode == NULL)
        {
            return NULL; // Not Found
        }
        Actual_Data = get_TreeNode->Actual_Ptr;
        *Return_RowIndex = get_TreeNode->RowIndex;
    }
    else
    {
        Actual_Data = Table_Head->Adj_Head;
        int Count = 0;
        while (Actual_Data != NULL)
        {
            if (strcmp(Actual_Data->Data, Target) == 0)
            {
                break;
            }
            Actual_Data = Actual_Data->Next;
            Count++;
        }
        (*Return_RowIndex) = Count;
        return (Actual_Data);
    }
    return Actual_Data;
}

// Return RowIndex and Actual Data Node
int GetPosition(Node *Column_Head, char *Target)
{
    int Return_RowIndex;
    Adjacent_Node *Actual_Data_Curr = Search_Adj_Node(Column_Head, Target, &Return_RowIndex);
    if (Actual_Data_Curr == NULL)
    {
        printf(RED "\nData not found\n" RESET);
        return -2;
    }
    return Return_RowIndex;
}

// Usage the Return to print that Record
void PrintRecord_by_Ref(Adjacent_Node *Ref_Node, int Num)
{
    Adjacent_Node *Curr = Ref_Node;
    for (int i = 0; i < Num; i++)
    { // Back to Top
        if (Curr->Prev != NULL)
        {
            Curr = Curr->Prev;
        }
    }
    while (Curr->Left != NULL)
    { // Back to Left
        Curr = Curr->Left;
    }
    for (int i = 0; i < (Num * 2) + 1; i++)
    {
        Adjacent_Node *Curr_Temp = Curr;
        while (Curr_Temp != NULL)
        {
            printf(CYAN "|%s %-12s ", RESET, Curr_Temp->Data);
            Curr_Temp = Curr_Temp->Right;
        }
        printf("\n");
        Curr = Curr->Next;
    }
}

void PrintRecord_by_Index(Node *First_Coulmn_Head, int RowIndex)
{
    Node *Curr_Column_Head = First_Coulmn_Head;
    while (Curr_Column_Head != NULL)
    {
        Adjacent_Node *Curr_Adjacent_Node = Curr_Column_Head->Adj_Head;
        int CountIndex = 0;
        while (CountIndex != RowIndex)
        {
            Curr_Adjacent_Node = Curr_Adjacent_Node->Next;
            CountIndex++;
        }
        printf("%s ", Curr_Adjacent_Node->Data);
        Curr_Column_Head = Curr_Column_Head->Next;
    }
}

// Example of Usage
// int main(){
//     FILE *file = read_csv("../bin/test.csv");
//     if (file == NULL)
//     {
//         return 1;
//     }
//     Node *First_Table_Head = csv_to_linked_list(file);
//     fclose(file);

//     First_Table_Head = MakeIndexing(First_Table_Head);
//     int Index = GetPosition(First_Table_Head, "Delhi");
//     PrintRecord(First_Table_Head, Index);

//     // printf("%s %d", Actual_Data_Curr->Data, *Return_RowIndex);

//     return 0;
// }