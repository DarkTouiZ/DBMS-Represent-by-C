#include "lib/Header.c"

int main()
{
    printf("Welcome to the Database Program\n");
    printf("please enter the name of new table or open an exist table with the name of file\n");
    char* Table_name = (char*)malloc(100 * sizeof(char));
    scanf(" %s", Table_name);
    FILE* file = read_csv(Table_name);
    Node *First_Table_Head = csv_to_linked_list(file);
    fclose(file);
    while(1){
        if (main_Page == true)
        {
            printTable(First_Table_Head);
        }
        else if (main_Page == false) {
        printf("Please enter the command\n");
        char* command = (char*)malloc(100 * sizeof(char));
        scanf(" %s", command);
        if(strcmp(command, "insert") == 0){
            printf("What kind of insert do you want?\n");
            printf("1. Insert Row\n");
            printf("2. Insert Column\n");
            int choice;
            scanf(" %d", &choice);
            if(choice == 1){
                InsertRecord(First_Table_Head);
            }
            else if(choice == 2){
                InsertColumn(First_Table_Head);
            }
            else{
                printf("Invalid choice\n");
            }
        }
        else if(strcmp(command, "delete") == 0){
            printf("What kind of delete do you want?\n");
            printf("1. Delete entire Row\n");
            printf("2. Delete entire Column\n");
            printf("3. Delete by specific Row and Column\n");
            int choice;
            scanf(" %d", &choice);
            if(choice == 1){
                deleteRow(First_Table_Head);
            }
            else if(choice == 2){
                deleteColumn(First_Table_Head);
            }
            else if(choice == 3){
                deleteDataAt(First_Table_Head);
            }
            else{
                printf("Invalid choice\n");
            }
        }
        else if(strcmp(command, "update") == 0){
            printf("enter the row and column you want to update\n");
            int row, column;
            scanf(" %d %d", &row, &column);
            printf("enter the new data\n");
            char* NewData = (char*)malloc(100 * sizeof(char));
            SelectToChangeAt(First_Table_Head, row, column, NewData);
        }
        else if(strcmp(command, "exit") == 0){
            break;
        }
        else{
            printf("Invalid command\n");
        }
        }
    }
    
    // FILE *file = read_csv("../bin/test.csv");
    // if (file == NULL)
    // {
    //     return 1;
    // }
    // Node *First_Table_Head = csv_to_linked_list(file);
    // fclose(file);

    // // First_Table_Head = MakeIndexing(First_Table_Head);
    // // int Index = GetPosition(First_Table_Head, "Delhi");
    // // PrintRecord(First_Table_Head, Index);
    
    // // printf("%s %d", Actual_Data_Curr->Data, *Return_RowIndex);


    return 0;
}