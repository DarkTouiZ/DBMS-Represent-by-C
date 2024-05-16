void DeleteDataAt(Node *Table, int rowIndex, char *column)
{
    // find the column
    Node *Current_Column = Table;
    while (Current_Column != NULL)
    {
        if (strcmp(Current_Column->Data, column) == 0)
        {
            break;
        }
        Current_Column = Current_Column->Next;
    }

    if (Current_Column == NULL)
    {
        printf("column name not found\n");
        return;
    }

    // find the row
    Adjacent_Node *Current_Row = Current_Column->Adj_Head;
    int Count = 0;
    while (Count < rowIndex)
    {
        if (Current_Row == NULL)
        {
            printf("index not found please enter again ( 'c' to cancel): ");
            int RowIndex;
            char ColumnName[MAX_STRING_LENGTH];
            scanf("%d %s", &RowIndex, ColumnName);
            if (strcmp(ColumnName, "c") == 0)
            {
                return;
            }
            DeleteDataAt(Table, RowIndex, ColumnName);
            return;
        }
        Current_Row = Current_Row->Next;
        Count++;
    }

    // Delete the data at the position (change the data to Nan)
    strcpy(Current_Row->Data, "NaN");
}

void DeleteColumn(Node *Table, char *column)
{
    // find the column
    Node *Current_Column = Table;
    Node *Previous_Column = Table;
    while (Current_Column != NULL)
    {
        if (strcmp(Current_Column->Data, column) == 0)
        {
            break;
        }
        Previous_Column = Current_Column;
        Current_Column = Current_Column->Next;
    }
    if (Current_Column == NULL)
    {
        printf("column name not found\n");
        return;
    }

    // Delete the column
    Previous_Column->Next = Current_Column->Next;
    free(Current_Column);
}

void DeleteRow(Node *Table, int rowindex)
{
    // find the row
    Node *Current_Column = Table;
    while (Current_Column != NULL)
    {
        Adjacent_Node *Current_Row = Current_Column->Adj_Head;
        Adjacent_Node *Previous_Row = Current_Column->Adj_Head;
        int Count = 0; // Start at 0
        while (Count < rowindex)
        {
            if (Current_Row == NULL)
            {
                printf("index not found\n");
                return;
            }
            Previous_Row = Current_Row;
            Current_Row = Current_Row->Next;
            Count++;
        }

        // Delete the row
        Previous_Row->Next = Current_Row->Next;
        if (Current_Row->Left != NULL)
        {
            Current_Row->Left->Right = Current_Row->Right;
        }
        if (Current_Row->Right != NULL)
        {
            Current_Row->Right->Left = Current_Row->Left;
        }
        free(Current_Row);
        Current_Column = Current_Column->Next;
    }
}

// int main()
// {
//     FILE *file = read_csv("../bin/test.csv");
//     if (file == NULL)
//     {
//         return 1;
//     }

//     Node *First_Table_Head = csv_to_linked_list(file);
//     fclose(file);

//     DeleteDataAt(First_Table_Head, 9, "Distance");

//     linked_list_to_csv(First_Table_Head, "../bin/test_output.csv");

//     return 0;
// }