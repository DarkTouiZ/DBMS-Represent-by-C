#define MAX_LINE_LENGTH MAX_STRING_LENGTH
#define MAX_FIELD_LENGTH 100

// Define ANSI escape codes for styling
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define MAGENTA "\x1b[35m"

bool is_Integer(char* Str);
void Linked_Left_Right(Node* First_Head_Table){
    Adjacent_Node* Data_PreCurr = NULL;
    Node* Head_Table_Curr = First_Head_Table;
    while(Head_Table_Curr != NULL){ // Loop for each in Column
        Adjacent_Node* Head_Adj_Node = Head_Table_Curr->Adj_Head;
        while(Head_Adj_Node != NULL){ // Loop for each in Record
            Head_Adj_Node->Left = Data_PreCurr; // Update Left Pointer
            if(Data_PreCurr != NULL){
                Data_PreCurr->Right = Head_Adj_Node;// Update Right Pointer
                Data_PreCurr = Data_PreCurr->Next;
            }
            Head_Adj_Node = Head_Adj_Node->Next;
        }
        Data_PreCurr = Head_Table_Curr->Adj_Head;
        Head_Table_Curr = Head_Table_Curr->Next;
    }
}

void Linked_Prev_Next(Node* First_Head_Table)
{
    Node* Head_Table_Curr = First_Head_Table;
    while (Head_Table_Curr != NULL)
    { // Loop for each in Column
        Adjacent_Node* PreCurr_Adj_Node = NULL;
        Adjacent_Node* Curr_Adj_Node = Head_Table_Curr->Adj_Head;
        while (Curr_Adj_Node != NULL)
        { // Loop for each in Record
            Curr_Adj_Node->Prev = PreCurr_Adj_Node;
            PreCurr_Adj_Node = Curr_Adj_Node;
            Curr_Adj_Node = Curr_Adj_Node->Next;
        }
        Head_Table_Curr = Head_Table_Curr->Next;
    }
}

// read csv function
FILE *read_csv(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf(RED "The file is not exist\n\n" RESET);
        printf("Do you want to create a new table with this name? (y/n)\n");
        char c;
        scanf(" %c", &c);
        if (c == 'y')
        {
            file = fopen(filename, "w");
            if (file == NULL)
            {
                printf(RED "Failed to open the file.\n"RESET);
                return 0;
            }
            printf(GREEN "FILE created successfully\n" RESET);
        }
        else
        {
            printf(GREEN "\nGoodbye...\n" RESET);
            exit(0);
        }
    }
    // Check if the file has a .csv extension
    char *extension = strrchr(filename, '.');
    if (extension != NULL && strcmp(extension, ".csv") == 0)
    {
        return file;
    }
    else
    {
        printf(RED "File format not supported. Only .csv files are supported.\n" RESET);
        fclose(file);
        exit(0);
        return NULL;
    }
}

// convert csv to our linked list structure
Node *csv_to_linked_list(FILE *file) {
    char line[MAX_LINE_LENGTH];
    char *token;
    Node *Adj_Head = NULL;
    Node *curr_node = NULL;
    Adjacent_Node *curr_adj_node = NULL;
    int row_count = 0;

    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';

        if (row_count == 0) {
            // First row contains column Adj_Headers
            token = strtok(line, ",");
            while (token != NULL) {
                // printf("%s\n", token);

                Node *new_node = (Node *)malloc(sizeof(Node));
                strcpy(new_node->Data, token);
                new_node->Type = false;  // Assume all columns contain strings initially
                new_node->isIndexing = false;
                new_node->Indexing_Ptr = NULL;
                new_node->Next = NULL;
                new_node->Prev = curr_node;
                new_node->Adj_Head = NULL;
                new_node->Adj_Tail = NULL;

                if (Adj_Head == NULL) {
                    Adj_Head = new_node;
                } else {
                    curr_node->Next = new_node;
                }
                curr_node = new_node;
                token = strtok(NULL, ",");
            }
        } else {
            // Subsequent rows contain data
            curr_node = Adj_Head;
            // printf("curr_node->Data: %s\n", curr_node->Data);
            token = strtok(line, ",");
            while (token != NULL && curr_node != NULL) {
                // printf("%s\n", token);
                Adjacent_Node *new_adj_node = (Adjacent_Node *)malloc(sizeof(Adjacent_Node));
                strcpy(new_adj_node->Data, token);
                new_adj_node->Next = NULL;
                new_adj_node->Prev = curr_adj_node;
                new_adj_node->Left = NULL;
                new_adj_node->Right = NULL;

                if (curr_node->Adj_Head == NULL) { // Handle First Data is NULL
                    curr_node->Adj_Head = new_adj_node;
                } else { // case default :: add to Tail
                    curr_node->Adj_Tail->Next = new_adj_node;
                }
                curr_node->Adj_Tail = new_adj_node;      
                curr_adj_node = new_adj_node;

                // Check if the data is an integer
                if (!curr_node->Type && is_Integer(token)) {
                    curr_node->Type = true; // Type true = Integer
                }

                curr_node = curr_node->Next;
                token = strtok(NULL, ",");
            }
        }
        row_count++;
    }

    Linked_Left_Right(Adj_Head); // Linked Left and Right Node for each Data
    Linked_Prev_Next(Adj_Head);
    return Adj_Head;
}

// display linked list function
void display_linked_list(Node *Adj_Head) {
    Node *curr_node = Adj_Head;
    Adjacent_Node *curr_adj_node = NULL;
    while (curr_node != NULL) {
        printf("%s\n", curr_node->Data);
        curr_adj_node = curr_node->Adj_Head;
        while (curr_adj_node != NULL) {
            printf("%s\n", curr_adj_node->Data);
            curr_adj_node = curr_adj_node->Next;
        }
        curr_node = curr_node->Next;
    }
}

// save linked list to csv function
void linked_list_to_csv(Node *Adj_Head, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf(RED "Failed to open the file.\n" RESET);
        return;
    }

    Node *curr_node = Adj_Head;
    Adjacent_Node *curr_adj_node = NULL;

    // Write column Adj_Headers
    while (curr_node != NULL) {
        if (curr_node->Prev != NULL) {
            fprintf(file, ",");
        }
        fprintf(file, "%s", curr_node->Data);
        curr_node = curr_node->Next;

        if (curr_node == NULL) {
            fprintf(file, "\n");
        }
    }

    // get row number
    int row_number = 0;
    curr_node = Adj_Head;
    curr_adj_node = curr_node->Adj_Head;
    while (curr_adj_node != NULL) {
        row_number++;
        curr_adj_node = curr_adj_node->Next;
    }

    // Write all rows
    curr_node = Adj_Head;
    int column_count = 0;
    int row_count = 0;

    while (row_count < row_number) {
        curr_node = Adj_Head;
        while (curr_node != NULL) {
            curr_adj_node = curr_node->Adj_Head;

            // Move to the current row
            for (int i = 0; i < row_count; i++) {
                curr_adj_node = curr_adj_node->Next;
            }

            if (column_count > 0) {
                fprintf(file, ",");
            }
            fprintf(file, "%s", curr_adj_node->Data);
            curr_node = curr_node->Next;
            column_count++;
        }
        fprintf(file, "\n");
        column_count = 0;
        row_count++;
    }

    fclose(file);
}

// print type each column
void check_type(Node *Adj_Head) {
    Node *curr_node = Adj_Head;
    while (curr_node != NULL) {
        if (curr_node->Type) {
            printf(MAGENTA "%s\n: Integer\n" RESET, curr_node->Data);
        } else {
            printf(MAGENTA "%s\n: String\n" RESET, curr_node->Data);
        }
        curr_node = curr_node->Next;
    }
}

// // ตัวอย่างการใช้งาน
// int main()
// {
//     FILE *file = read_csv("../bin/test.csv");
//     if (file == NULL)
//     {
//         return 1;
//     }

//     Node *Adj_Head = csv_to_linked_list(file);
//     display_linked_list(Adj_Head);
//     // check_type(Adj_Head);

//     // linked_list_to_csv(Adj_Head, "../bin/test_output.csv");

//     fclose(file);

//     return 0;
// }