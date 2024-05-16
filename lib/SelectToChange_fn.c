#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structure.h"

void SelectToChangeData(Node* Table, char* row, char* column, char* NewData)
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

    //Update the Data
    strcpy(Current_Row->Data, NewData);
}
// Does not have any test with that function