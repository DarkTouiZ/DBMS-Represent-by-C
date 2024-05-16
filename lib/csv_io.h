#define MAX_LINE_LENGTH MAX_STRING_LENGTH
#define MAX_FIELD_LENGTH 100

bool is_Integer(char* Str);

// read csv function
FILE *read_csv(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("The file is not exist\n");
        printf("Do you want to create a new table with this name? (y/n)\n");
        char c;
        scanf(" %c", &c);
        if (c == 'y')
        {
            file = fopen(filename, "w");
            if (file == NULL)
            {
                printf("Failed to open the file.\n");
                return 0;
            }
            printf("The table is created successfully\n");
        }
        else
        {
            printf("Goodbye\n");
            return 0;
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
        printf("File format not supported. Only .csv files are supported.\n");
        fclose(file);
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
        printf("Failed to open the file.\n");
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
            printf("%s\n: Integer\n", curr_node->Data);
        } else {
            printf("%s\n: String\n", curr_node->Data);
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