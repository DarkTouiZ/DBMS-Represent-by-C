// Just use : printTable(head);

#define MAX_CELL_SIZE 13 // size = 12 char

void freeLinkedList(Node *head)
{
    Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->Next;

        Adjacent_Node *curr_adj_node = temp->Adj_Head;
        while (curr_adj_node != NULL)
        {
            Adjacent_Node *temp_adj = curr_adj_node;
            curr_adj_node = curr_adj_node->Next;
            free(temp_adj);
        }
        free(temp);
    }
}

void FindSize(Node *head)
{
    max_size_row = 0;
    max_size_col = 0;
    // Check if head is NULL
    if (head == NULL)
    {
        return;
    }
    Node *curr_Table_Head = head;
    while (curr_Table_Head != NULL)
    {
        int size = 1;
        max_size_col++;
        // Traverse the rows
        Adjacent_Node *curr_adj_node = curr_Table_Head->Adj_Head;
        while (curr_adj_node != NULL)
        {
            size++;
            curr_adj_node = curr_adj_node->Next;
        }
        // Update size
        if (size > max_size_row)
        {
            max_size_row = size;
        }
        curr_Table_Head = curr_Table_Head->Next;
    }
    return;
}

typedef struct SimpleLikedList
{
    char Data[100];
    struct SimpleLikedList *Next;
} SimpleLikedList;

void printTable(Node *Table)
{
    // Find Max Col and Row Size
    FindSize(Table);
    if(max_size_col == 0 || max_size_row == 0){
        printf(RED "No available data to display" RESET);
        main_Page = false;
        return;
    }
    // Begin Print Table Function
    //  int num_display_rowNcol;
    int num_display_row;
    int num_display_col;
    printf("\nHow many cols you want to display: ");
    scanf(" %d", &num_display_col);
    printf("How many rows you want to display: ");
    scanf(" %d", &num_display_row);

    // Initialize
    SimpleLikedList **Data = (SimpleLikedList **)malloc(sizeof(SimpleLikedList *) * max_size_col);
    for (int i = 0; i < max_size_col; i++)
    {
        Data[i] = (SimpleLikedList *)malloc(sizeof(SimpleLikedList) * max_size_row);
    }

    // Store value
    Node *Current_Column_Print = Table;
    Adjacent_Node *Current_Row_Print = NULL;
    int i = 0;
    while (Current_Column_Print != NULL)
    {
        Current_Row_Print = Current_Column_Print->Adj_Head;
        int j = 0;
        while (Current_Row_Print != NULL)
        {
            strncpy(Data[i][j].Data, Current_Row_Print->Data, MAX_CELL_SIZE - 1);
            Data[i][j].Data[MAX_CELL_SIZE - 1] = '\0'; // Ensure terminal
            Current_Row_Print = Current_Row_Print->Next;
            j++;
        }
        i++;
        Current_Column_Print = Current_Column_Print->Next;
    }

    // Ask for setting
    int curr_row = 0, curr_col = 0;
    int move_setting;
    char move_command;

    printf("How many cells do you want to move in a single command: ");
    scanf(" %d", &move_setting);

    while (1)
    {
        // Print Column Name
        Current_Column_Print = Table;
        Current_Row_Print = Current_Column_Print->Adj_Head;

        printf("\n");
        printf("    ");
        for (int i = 0; i < max_size_col; i++)
        {
            if (i >= curr_col && i < curr_col + num_display_col && i < max_size_col)
            {
                printf(BLUE"|%s %-12s ",RESET , Current_Column_Print->Data);
            }
                Current_Column_Print = Current_Column_Print->Next;
            // if(Current_Column_Print == NULL){
            //     break;
            // }
        }
        printf(BLUE "|\n" RESET);

        // Print A Separete Line
        for (int i = curr_row; i < curr_row + num_display_row && i < max_size_row; i++)
        {
            if (i == curr_row)
            {
                printf(CYAN "----");
                for (int j = 0; j < num_display_col; j++)
                {
                    printf("+");
                    for (int k = 0; k < MAX_CELL_SIZE + 1; k++)
                    {
                        printf("-");
                    }
                }
                printf("+\n" RESET);
            }

            // Print Record
            printf(" %-2d ", i + 1);
            for (int j = curr_col; j < curr_col + num_display_col && j < max_size_col; j++)
            {
                printf(CYAN "|%s %-12s ", RESET, Data[j][i].Data);
            }
            printf(CYAN "|\n" RESET);
        }

        // Ask for command (w a s d)
        printf("Enter 'w' to move up, 'a' to move left, 's' to move down, 'd' to move right, 'o' to option : ");
        scanf(" %c", &move_command);

        if (move_command == 'd' && curr_col + num_display_col < max_size_col)
        { // Right
            curr_col += move_setting;
        }
        else if (move_command == 'a' && curr_col - move_setting >= 0)
        { // Left
            curr_col -= move_setting;
        }
        else if (move_command == 's' && curr_row + num_display_row < max_size_row)
        { // Down
            curr_row += move_setting;
        }
        else if (move_command == 'w' && curr_row - move_setting >= 0)
        { // Up
            curr_row -= move_setting;
        }
        else if (move_command == 'o')
        { // move to option page
            main_Page = false;
            return;
        }
        system("cls");
    }

    // Free Data
    for (int i = 0; i < max_size_col; i++)
    {
        free(Data[i]);
    }
    free(Data);
}

// int main(){
//     FILE *file = read_csv("../bin/test2.csv");
//     if (file == NULL){
//         return 1;
//     }
//     Node *head = csv_to_linked_list(file);
//     printTable(head);
//     return 0;
// }