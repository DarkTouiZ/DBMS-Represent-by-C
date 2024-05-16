#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Structure.h"

typedef struct SimpleLikedList
{
    char Data[100];
    struct SimpleLikedList* Next;
}SimpleLikedList;


void insertRow(Node* Table, char* Data)
{
    //Create a new Row
    Adjacent_Node* New_Row = (Adjacent_Node*)malloc(sizeof(Adjacent_Node));
    New_Row->Next = NULL;
    New_Row->Prev = NULL;
    strcpy(New_Row->Data, Data);
    //Insert the Row
    if (Table->Head == NULL)
    {
        Table->Head = New_Row;
        Table->Tail = New_Row;
    }
    else
    {
        Table->Tail->Next = New_Row;
        New_Row->Prev = Table->Tail;
        Table->Tail = New_Row;
    }
}

void createNewcolumn(Node* Table, char* Data, bool Type)
{
    //Create a new Column
    Node* New_Column = (Node*)malloc(sizeof(Node));
    New_Column->Type = Type;
    New_Column->isIndexing = false;
    strcpy(New_Column->Data, Data);
    New_Column->Next = NULL;
    New_Column->Prev = NULL;
    New_Column->Head = NULL;
    New_Column->Tail = NULL;
    New_Column->Indexing_Ptr = NULL;
    //Insert the Column
    if (Table->Next == NULL)
    {
        Table->Next = New_Column;
        New_Column->Prev = Table;
    }
    else
    {
        Node* Current = Table;
        while (Current->Next != NULL)
        {
            Current = Current->Next;
        }
        Current->Next = New_Column;
        New_Column->Prev = Current;
    }
}

void printTable(Node* Table)
{
    //print Header of the Table
    Node* Current_Column_Print = Table;
    Adjacent_Node* Current_Row_Print = Current_Column_Print->Head;
    Current_Column_Print = Table;
    Current_Row_Print = Current_Column_Print->Head;
    while (Current_Column_Print != NULL)
    {
        printf("%s\t", Current_Column_Print->Data);
        Current_Column_Print = Current_Column_Print->Next;
    }
    printf("\n");
    Current_Column_Print = Table;
    Current_Row_Print = Current_Column_Print->Head;
    //Store the data in the column to 2D Array (all column)
    SimpleLikedList** Data = (SimpleLikedList**)malloc(sizeof(SimpleLikedList*) * 100);
    for (int i = 0; i < 100; i++)
    {
        Data[i] = (SimpleLikedList*)malloc(sizeof(SimpleLikedList) * 100);
    }
    int i = 0;
    while (Current_Column_Print != NULL)
    {
        Current_Row_Print = Current_Column_Print->Head;
        int j = 0;
        while (Current_Row_Print != NULL)
        {
            strcpy(Data[i][j].Data, Current_Row_Print->Data);
            Current_Row_Print = Current_Row_Print->Next;
            j++;
        }
        i++;
        Current_Column_Print = Current_Column_Print->Next;
    }
    //Print out the Value in the table interm of row and column
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%s\t", Data[j][i].Data);
        }
        printf("\n");
    }
}

void UpdateNode(Node* Table, char* Row, char* Column, char* Data)
{
    //Find the Column
    Node* Current_Column = Table->Next;
    while (Current_Column != NULL)
    {
        if (strcmp(Current_Column->Data, Column) == 0)
        {
            break;
        }
        Current_Column = Current_Column->Next;
    }
    //Find the Row
    Adjacent_Node* Current_Row = Current_Column->Head;
    while (Current_Row != NULL)
    {
        if (strcmp(Current_Row->Data, Row) == 0)
        {
            break;
        }
        Current_Row = Current_Row->Next;
    }
    //Update the Data
    strcpy(Current_Row->Data, Data);
    
    printTable(Table);
}

int main()
{
    //Define a Table with Double Linked List
    Node* Table = (Node*)malloc(sizeof(Node));
    Table->Type = false;
    Table->isIndexing = false;
    strcpy(Table->Data, "ID");
    Table->Next = NULL;
    Table->Prev = NULL;
    Table->Head = NULL;
    Table->Tail = NULL;
    Table->Indexing_Ptr = NULL;
    Adjacent_Node* Current = Table->Head;
    //Call function to insert a Row
    insertRow(Table, "1");
    insertRow(Table, "2");
    insertRow(Table, "3");
    insertRow(Table, "4");
    insertRow(Table, "5");
    //Call function to create new Column
    createNewcolumn(Table, "Name", false);
    createNewcolumn(Table, "Age", false);
    
    //insert a Row in new Column (Name)
    Node *Current_Column = Table->Next;
    insertRow(Current_Column, "John");
    insertRow(Current_Column, "Doe");
    insertRow(Current_Column, "Jane");
    insertRow(Current_Column, "Dane");
    insertRow(Current_Column, "Smith");
    //insert a Row in new Column (Age)
    Current_Column = Current_Column->Next;
    insertRow(Current_Column, "20");
    insertRow(Current_Column, "21");
    insertRow(Current_Column, "22");
    insertRow(Current_Column, "23");
    insertRow(Current_Column, "24");

    //Print out the Table
    printTable(Table);
    

    return 0;
}