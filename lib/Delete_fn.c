#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structure.h"

void DeleteDataAt(Node* Table, char* row, char* column)
{
    //find the column
    Node* Current_Column = Table;
    while (Current_Column != NULL)
    {
        if (strcmp(Current_Column->Data, column) == 0)
        {
            break;
        }
        Current_Column = Current_Column->Next;
    }

    //find the row
    Adjacent_Node* Current_Row = Current_Column->Head;
    while (Current_Row != NULL)
    {
        if (strcmp(Current_Row->Data, row) == 0)
        {
            break;
        }
        Current_Row = Current_Row->Next;
    }

    //Delete the data at the position (change the data to Nan)
    strcpy(Current_Row->Data, "Nan");
}

void DeleteColumn(Node* Table, char* column)
{
    //find the column
    Node* Current_Column = Table;
    Node* Previous_Column = Table;
    while (Current_Column != NULL)
    {
        if (strcmp(Current_Column->Data, column) == 0)
        {
            break;
        }
        Previous_Column = Current_Column;
        Current_Column = Current_Column->Next;
    }

    //Delete the column
    Previous_Column->Next = Current_Column->Next;
    free(Current_Column);
}

void DeleteRow(Node* Table, char* row)
{
    //find the row
    Node* Current_Column = Table;
    while (Current_Column != NULL)
    {
        Adjacent_Node* Current_Row = Current_Column->Head;
        Adjacent_Node* Previous_Row = Current_Column->Head;
        while (Current_Row != NULL)
        {
            if (strcmp(Current_Row->Data, row) == 0)
            {
                break;
            }
            Previous_Row = Current_Row;
            Current_Row = Current_Row->Next;
        }

        //Delete the row
        Previous_Row->Next = Current_Row->Next;
        free(Current_Row);
        Current_Column = Current_Column->Next;
    }
}
