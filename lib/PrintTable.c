#include <stdio.h>
#include "csv_io.c"

int max_size_row = 0; // Max Number of Row <-> Record
int max_size_col = 0; // Max Number of Column

void FindSize(Node *head){
    // Check if head is NULL
    if (head == NULL) {
        printf("Error: Head node is NULL\n");
        return ;
    }
    Node *curr_Table_Head = head;
    while (curr_Table_Head != NULL){
        int size = 1;
        max_size_col++;
        // Traverse the rows
        Adjacent_Node *curr_adj_node = curr_Table_Head->Head;
        //printf ("%s\n",curr_Table_Head->Data);
        while (curr_adj_node != NULL){
            size++;
            //printf ("%s\n",curr_adj_node->Data);
            curr_adj_node = curr_adj_node->Next;
        }
        // Update size
        if (size > max_size_row ){
            max_size_row = size;
        }
        curr_Table_Head = curr_Table_Head->Next;
    }
    printf ("ROW>> %d COLUMM>> %d",max_size_row, max_size_col);
    return ;
}


//Print Table
#define MAX_CELL_SIZE 13

typedef struct SimpleLikedList
{
    char Data[100];
    struct SimpleLikedList* Next;
}SimpleLikedList;

void printTable(Node* Table, int row, int col)
{
    //print Header of the Table
    Node* Current_Column_Print = Table;
    Adjacent_Node* Current_Row_Print = Current_Column_Print->Head;

    printf("\n");
    while (Current_Column_Print != NULL)
    {
        printf("| %-12s ", Current_Column_Print->Data);             //*****
        Current_Column_Print = Current_Column_Print->Next;
    }
    printf("|\n");

    Current_Column_Print = Table;
    Current_Row_Print = Current_Column_Print->Head;
    //Store the data in the column to 2D Array (all column)
    SimpleLikedList** Data = (SimpleLikedList**)malloc(sizeof(SimpleLikedList*) * 100);
    for (int i = 0; i < 100; i++)
    {
        Data[i] = (SimpleLikedList*)malloc(sizeof(SimpleLikedList) * 100); //initialize
    }
    int i = 0;
    while (Current_Column_Print != NULL)
    {
        Current_Row_Print = Current_Column_Print->Head;
        int j = 0;
        while (Current_Row_Print != NULL)
        {
            strncpy(Data[i][j].Data, Current_Row_Print->Data, MAX_CELL_SIZE - 1); //12
            Data[i][j].Data[MAX_CELL_SIZE - 1] = '\0'; // Ensure null termination
            Current_Row_Print = Current_Row_Print->Next;
            j++;
        }
        i++;
        Current_Column_Print = Current_Column_Print->Next;
    }
    
    //Print out the Value in the table interm of row and column
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("| %-12s ", Data[j][i].Data);                //*****
        }
        printf("|\n");
    }
}

int main(){
    FILE *file = read_csv("../bin/test.csv");
    if (file == NULL){
        return 1;
    }
    Node *head = csv_to_linked_list(file);
    FindSize(head);
    printTable(head, max_size_row, max_size_col);
    return 0; 
}