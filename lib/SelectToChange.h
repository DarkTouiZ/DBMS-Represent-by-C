void SelectToChangeAt(Node *Table, int rowindex, char *column, char *NewData)
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
    while (Count < rowindex)
    {
        if (Current_Row == NULL)
        {
            printf("index not found\n");
            return;
        }

        Current_Row = Current_Row->Next;
        Count++;
    }

    // Change the data at the position
    strcpy(Current_Row->Data, NewData);
    return;
}

// Example of Usage
// int main()
// {
//     FILE *file = read_csv("../bin/test.csv");
//     if (file == NULL)
//     {
//         return 1;
//     }

//     Node *First_Table_Head = csv_to_linked_list(file);
//     fclose(file);

//     SelectToChangeAt(First_Table_Head, 9, "Distance", "newData");

//     linked_list_to_csv(First_Table_Head, "../bin/test_output.csv");

//     return 0;
// }