#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
Node *csv_to_linked_list(FILE *file)
{
    char line[MAX_LINE_LENGTH];
    char *field;

    // Read and apply data structure from structure.h
    Node *head = (Node *)malloc(sizeof(Node));
    Node *current = head;
    head->Next = NULL;
    head->Prev = NULL;
    head->Head = NULL;
    head->Tail = NULL;
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        field = strtok(line, ",");
        while (field)
        {
            Adjacent_Node *new_node = (Adjacent_Node *)malloc(sizeof(Adjacent_Node));
            strcpy(new_node->Data, field);
            new_node->Next = NULL;
            new_node->Prev = NULL;
            if (current->Head == NULL)
            {
                current->Head = new_node;
                current->Tail = new_node;
            }
            else
            {
                current->Tail->Next = new_node;
                new_node->Prev = current->Tail;
                current->Tail = new_node;
            }
            field = strtok(NULL, ",");
        }
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->Next = NULL;
        new_node->Prev = current;
        current->Next = new_node;
        current = new_node;
    }
    return head;
}

// save linked list to csv
void linked_list_to_csv(Node *head, char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }
    Node *current = head;
    while (current)
    {
        Adjacent_Node *current_adj = current->Head;
        while (current_adj)
        {
            fprintf(file, "%s", current_adj->Data);
            if (current_adj->Next)
            {
                fprintf(file, ",");
            }
            current_adj = current_adj->Next;
        }
        fprintf(file, "\n");
        current = current->Next;
    }
    fclose(file);
}