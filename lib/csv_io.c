#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Structure.h"

#define MAX_LINE_LENGTH 1000
#define MAX_FIELD_LENGTH 100

// read csv function
FILE *read_csv(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return NULL;
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
    Node *head = NULL;
    Node *curr_node = NULL;
    Adjacent_Node *curr_adj_node = NULL;
    int row_count = 0;

    while (fgets(line, sizeof(line), file)) {
        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';

        if (row_count == 0) {
            // First row contains column headers
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
                new_node->Head = NULL;
                new_node->Tail = NULL;

                if (head == NULL) {
                    head = new_node;
                } else {
                    curr_node->Next = new_node;
                }
                curr_node = new_node;
                token = strtok(NULL, ",");
            }
        } else {
            // Subsequent rows contain data
            curr_node = head;
            // printf("curr_node->Data: %s\n", curr_node->Data);
            token = strtok(line, ",");
            while (token != NULL && curr_node != NULL) {
                // printf("%s\n", token);
                Adjacent_Node *new_adj_node = (Adjacent_Node *)malloc(sizeof(Adjacent_Node));
                strcpy(new_adj_node->Data, token);
                new_adj_node->Next = NULL;
                new_adj_node->Prev = curr_adj_node;

                if (curr_node->Head == NULL) {
                    curr_node->Head = new_adj_node;
                } else {
                    curr_node->Tail->Next = new_adj_node;
                }
                curr_node->Tail = new_adj_node;
                curr_adj_node = new_adj_node;

                // Check if the data is an integer
                if (!curr_node->Type && atoi(token) != 0) {
                    curr_node->Type = true;
                }

                curr_node = curr_node->Next;
                token = strtok(NULL, ",");
            }
        }
        row_count++;
    }

    return head;
}

// display linked list function
void display_linked_list(Node *head) {
    Node *curr_node = head;
    Adjacent_Node *curr_adj_node = NULL;
    while (curr_node != NULL) {
        printf("%s\n", curr_node->Data);
        curr_adj_node = curr_node->Head;
        while (curr_adj_node != NULL) {
            printf("%s\n", curr_adj_node->Data);
            curr_adj_node = curr_adj_node->Next;
        }
        curr_node = curr_node->Next;
    }
}

// save linked list to csv function
void linked_list_to_csv(Node *head, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    Node *curr_node = head;
    Adjacent_Node *curr_adj_node = NULL;

    // Write column headers
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
    curr_node = head;
    curr_adj_node = curr_node->Head;
    while (curr_adj_node != NULL) {
        row_number++;
        curr_adj_node = curr_adj_node->Next;
    }

    // Write all rows
    curr_node = head;
    int column_count = 0;
    int row_count = 0;

    while (row_count < row_number) {
        curr_node = head;
        while (curr_node != NULL) {
            curr_adj_node = curr_node->Head;

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
void check_type(Node *head) {
    Node *curr_node = head;
    while (curr_node != NULL) {
        if (curr_node->Type) {
            printf("%s\n: Integer\n", curr_node->Data);
        } else {
            printf("%s\n: String\n", curr_node->Data);
        }
        curr_node = curr_node->Next;
    }
}

// ตัวอย่างการใช้งาน
int main()
{
    FILE *file = read_csv("../bin/test.csv");
    if (file == NULL)
    {
        return 1;
    }

    Node *head = csv_to_linked_list(file);
    // display_linked_list(head);
    // check_type(head);

    linked_list_to_csv(head, "../bin/test_output.csv");

    fclose(file);

    return 0;
}