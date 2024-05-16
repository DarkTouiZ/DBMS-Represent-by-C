#include "Header.c"

int main()
{
    // printf("Welcome to the Database Program\n");
    // printf("please enter the name of new table or open an exist table with the name of file\n");
    // char* Table_name = (char*)malloc(100 * sizeof(char));
    // scanf(" %s", Table_name);
    // read_csv(Table_name);
    // while(1){
    //     printf("Please enter the command\n");
    //     char* command = (char*)malloc(100 * sizeof(char));
    //     scanf(" %s", command);
    //     if(strcmp(command, "insert") == 0){
    //         printf("What kind of insert do you want?\n");
    //         printf("1. Insert Row\n");
    //         printf("2. Insert Column\n");
    //         int choice;
    //         scanf(" %d", &choice);
    //         if(choice == 1){
    //             insertRecord(Table_name);
    //         }
    //         else if(choice == 2){
    //             insertColumn(Table_name);
    //         }
    //         else{
    //             printf("Invalid choice\n");
    //         }
    //     }
    //     else if(strcmp(command, "delete") == 0){
    //         printf("What kind of delete do you want?\n");
    //         printf("1. Delete entire Row\n");
    //         printf("2. Delete entire Column\n");
    //         printf("3. Delete by specific Row and Column\n");
    //         int choice;
    //         scanf(" %d", &choice);
    //         if(choice == 1){
    //             deleteRow(Table_name);
    //         }
    //         else if(choice == 2){
    //             deleteColumn(Table_name);
    //         }
    //         else if(choice == 3){
    //             deleteDataAt(Table_name);
    //         }
    //         else{
    //             printf("Invalid choice\n");
    //         }
    //     }
    //     else if(strcmp(command, "update") == 0){
    //         printf("enter the row and column you want to update\n");
    //         int row, column;
    //         scanf(" %d %d", &row, &column);
    //         printf("enter the new data\n");
    //         char* NewData = (char*)malloc(100 * sizeof(char));
    //         SelectToChangeAt(Table_name, row, column, NewData);
    //     }
    //     else if(strcmp(command, "exit") == 0){
    //         break;
    //     }
    //     else{
    //         printf("Invalid command\n");
    //     }
    // }
    FILE *file = read_csv("../bin/test.csv");
    if (file == NULL)
    {
        return 1;
    }
    Node *First_Table_Head = csv_to_linked_list(file);
    fclose(file);

    printTable(First_Table_Head);

    // First_Table_Head = MakeIndexing(First_Table_Head);
    // int Index = GetPosition(First_Table_Head, "Delhi");
    // PrintRecord(First_Table_Head, Index);

    // InsertRecord(First_Table_Head);
    // Adjacent_Node* Curr = First_Table_Head->Next->Adj_Tail; 
    // printf("%s %s %s", Curr->Left->Data, Curr->Data, Curr->Right->Data);
    
    // printf("%s %d", Actual_Data_Curr->Data, *Return_RowIndex);


    return 0;
}