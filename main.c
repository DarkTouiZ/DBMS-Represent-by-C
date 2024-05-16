#include "lib/Header.c"

int main()
{
    printf("Welcome to the Database Program\n");
    printf("please enter the name of new table or open an exist table with the name of file\n");
    char *Table_name = (char *)malloc(100 * sizeof(char));
    scanf(" %s", Table_name);
    FILE *file = read_csv(Table_name);
    Node *First_Table_Head = csv_to_linked_list(file);
    fclose(file);
    main_Page = false;
    while (1)
    {
        if (main_Page == true)
        {
            printTable(First_Table_Head);
        }
        else if (main_Page == false)
        {
            system("cls");
            printf("Please enter the command\n");
            printf("insert, delete, update, search, graph, exit\n");
            char *command = (char *)malloc(100 * sizeof(char));
            scanf(" %s", command);
            if (strcmp(command, "insert") == 0)
            {
                printf("What kind of insert do you want?\n");
                printf("1. Insert Row\n");
                printf("2. Insert Column\n");
                int choice;
                scanf(" %d", &choice);
                if (choice == 1)
                {
                    InsertRecord(First_Table_Head);
                }
                else if (choice == 2)
                {
                    InsertColumn(First_Table_Head);
                }
                else
                {
                    printf("Invalid choice\n");
                }
            }
            else if (strcmp(command, "delete") == 0)
            {
                printf("What kind of delete do you want?\n");
                printf("1. Delete entire Row\n");
                printf("2. Delete entire Column\n");
                printf("3. Delete by specific Row and Column\n");
                int choice;
                scanf(" %d", &choice);
                if (choice == 1)
                {
                    printf("What is the row number you want to delete: ");
                    int RowIndex;
                    scanf(" %d", &RowIndex);
                    printf("\n");
                    DeleteRow(First_Table_Head, RowIndex);
                }
                else if (choice == 2)
                {
                    printf("What is the column name you want to delete: ");
                    char *ColumnName;
                    scanf(" %s", ColumnName);
                    printf("\n");
                    DeleteColumn(First_Table_Head, ColumnName);
                }
                else if (choice == 3)
                {
                    printf("What is the row number & the column name you want to delete: ");
                    int RowIndex;
                    char *ColumnName;
                    scanf("%d %s", &RowIndex, ColumnName);
                    printf("\n");
                    DeleteDataAt(First_Table_Head, RowIndex, ColumnName);
                }
                else
                {
                    printf("Invalid choice\n");
                }
            }
            else if (strcmp(command, "update") == 0)
            {
                printf("enter the row number and the column name you want to update\n");
                int row;
                char *column;
                scanf(" %d %s", &row, column);
                printf("enter the new data\n");
                char *NewData = (char *)malloc(100 * sizeof(char));
                SelectToChangeAt(First_Table_Head, row, column, NewData);
            }
            else if (strcmp(command, "search") == 0)
            {
                printf("What kind of search do you want?\n");
                printf("1. Search for row number\n");
                printf("2. Search for record\n");
                printf("3. Make indexing\n");
                int choice;
                scanf(" %d", &choice);
                if (choice == 1)
                {
                    printf("What is the column name you want to search: ");
                    char *ColumnName;
                    scanf(" %s", ColumnName);
                    printf("\n");

                    Node *Curr = First_Table_Head;
                    while (Curr != NULL)
                    {
                        if (strcmp(Curr->Data, ColumnName) == 0)
                        {
                            break;
                        }
                        Curr = Curr->Next;
                    }
                    if (Curr == NULL)
                    {
                        printf("Column name not match any in database\n");
                    }
                    else
                    {
                        printf("What is the target do you search for: ");
                        char *Target;
                        scanf(" %s", Target);
                        printf("\n");
                        printf("Row number of %s in column %s is %d", Target, ColumnName, GetPosition(Curr, Target));
                    }
                }
                else if (choice == 2)
                {
                    printf("What is the column name You want to search: ");
                    char *ColumnName;
                    scanf(" %s", ColumnName);
                    printf("\n");

                    Node *Curr = First_Table_Head;
                    while (Curr != NULL)
                    {
                        if (strcmp(Curr->Data, ColumnName) == 0)
                        {
                            break;
                        }
                        Curr = Curr->Next;
                    }
                    if (Curr == NULL)
                    {
                        printf("Column name not match any in database\n");
                    }
                    else
                    {
                        printf("What is the target do you search for: ");
                        char *Target;
                        scanf(" %s", Target);
                        printf("\n");
                        int *ReturnIndex;
                        Adjacent_Node *Actual_Data = Search_Adj_Node(Curr, Target, ReturnIndex);
                        PrintRecord_by_Ref(Actual_Data, 5);
                    }
                }
                else if (choice == 3)
                {
                    printf("what is column name do you want to make indexing: ");
                    char *ColumnName;
                    scanf(" %s", ColumnName);
                    printf("\n");
                    Node *Curr = First_Table_Head;
                    while (Curr != NULL)
                    {
                        if (strcmp(Curr->Data, ColumnName) == 0)
                        {
                            break;
                        }
                        Curr = Curr->Next;
                    }
                    if (Curr == NULL)
                    {
                        printf("Column name not match any in database\n");
                    }
                    else
                    {
                        MakeIndexing(Curr);
                    }
                }
                else
                {
                    printf("Invalid choice\n");
                }
            }
            else if (strcmp(command, "graph") == 0)
            {
                printf("plase enter the column name follow these requirements\n");
                printf("initial vertex column name: ");
                char initialname[MAX_STRING_LENGTH];
                scanf(" %s", initialname);
                Node *Curr1 = First_Table_Head;
                while (Curr1 != NULL)
                {
                    if (strcmp(Curr1->Data, initialname) == 0)
                    {
                        break;
                    }
                    Curr1 = Curr1->Next;
                }
                if (Curr1 == NULL)
                {
                    printf("Column name not match any in database\n");
                }
                else
                {
                    printf("terminal vertex column name: ");
                    char terminalname[MAX_STRING_LENGTH];
                    scanf(" %s", terminalname);
                    Node *Curr2 = First_Table_Head;
                    while (Curr2 != NULL)
                    {
                        if (strcmp(Curr2->Data, terminalname) == 0)
                        {
                            break;
                        }
                        Curr2 = Curr2->Next;
                    }
                    if (Curr2 == NULL)
                    {
                        printf("Column name not match any in database\n");
                    }
                    else
                    {
                        printf("weight column name: ");
                        char weightname[MAX_STRING_LENGTH];
                        scanf(" %s", weightname);
                        Node *Curr3 = First_Table_Head;
                        while (Curr3 != NULL)
                        {
                            if (strcmp(Curr3->Data, weightname) == 0)
                            {
                                break;
                            }
                            Curr3 = Curr3->Next;
                        }
                        if (Curr3 == NULL)
                        {
                            printf("Column name not match any in database\n");
                        }
                        else
                        {
                            printf("What kind of graph algorithm you want to use?\n");
                            printf("1. Shortest Path\n");
                            printf("2. Breadth-First Search\n");
                            printf("3. Depth-First Search\n");
                            int choice;
                            scanf(" %d", &choice);
                            if (choice == 1)
                            {
                                GetShortestPathOF(Curr1, Curr2, Curr3);
                            }
                            else if (choice == 2)
                            {
                                GetBFS(Curr1, Curr2, Curr3);
                            }
                            else if (choice == 3)
                            {
                                GetDFS(Curr1, Curr2, Curr3);
                            }
                            else
                            {
                                printf("Invalid choice\n");
                            }
                        }
                    }
                }
            }
            else if (strcmp(command, "exit") == 0)
            {
                linked_list_to_csv(First_Table_Head, "../bin/test_output.csv");
                fclose(file);
                break;
            }
            else
            {
                printf("Invalid command\n");
            }
        }
    }
    return 0;
}