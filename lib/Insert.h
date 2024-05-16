bool is_Integer(char* Str){
    if(*Str == '\0'){
        return false;
    }

    while(*Str != '\0'){
        if(!isdigit((char) *Str)){
            return false;
        }
        Str++;
    }

    return true;
}

Adjacent_Node* CreateAdj_Node(char* Token){
    Adjacent_Node* newNode = (Adjacent_Node*)malloc(sizeof(Adjacent_Node));
    strcpy(newNode->Data, Token);
    newNode->Next = NULL;
    newNode->Prev = NULL;
    return newNode;
}

void InsertRecord(Node* First_Table_Head){
    Node* Curr_Table_Head = First_Table_Head;

    // Print Text
    printf("Input Data Seperated by space\nColumn Name: ");
    Node* Temp = Curr_Table_Head;
    while(Temp != NULL){
        printf("%s ", Temp->Data);
        Temp = Temp->Next;
    }
    printf("\n");

    // Get Input
    char InputLine[MAX_STRING_LENGTH];
    fgets(InputLine, MAX_STRING_LENGTH, stdin);

    // Remove the newline character if present
    InputLine[strcspn(InputLine, "\n")] = '\0';

    // Extract Input line
    // Get First Token
    char* Token = strtok(InputLine, " ");
    while(Token != NULL){
        
        Adjacent_Node* Curr_Adj_Node = Curr_Table_Head->Adj_Head;

        //Create newNode
        Adjacent_Node* newNode = CreateAdj_Node(Token);

        // Handle First Record
        if(Curr_Table_Head->Adj_Head == NULL){
            Curr_Table_Head->Adj_Head = newNode;
            Curr_Table_Head->Type = is_Integer(Token);
        } else { // Default Case : Add to Tail
            while(is_Integer(Token) != Curr_Table_Head->Type){ // Loop until get match Data Type
                // Get new Input only for this Column
                printf("ERROR: Not match Data Type\nPlase Enter new data for Column %s", Curr_Table_Head->Data);
                if(Curr_Table_Head->Type == true){
                    printf("(Integer): ");
                } else {
                    printf("(String): ");
                }
                fgets(Token, MAX_STRING_LENGTH, stdin);
                Token[strcspn(Token, "\n")] = '\0';
                // printf("%s\n", Token);
                
                // Check Data Type again
                if(is_Integer(Token) != Curr_Table_Head->Type){
                    continue;
                }

                strcpy(newNode->Data, Token);
            }
            Curr_Table_Head->Adj_Tail->Next = newNode;
            newNode->Prev = Curr_Table_Head->Adj_Tail;
        }

        //Undate Tail_Pointer
        Curr_Table_Head->Adj_Tail = newNode;

        Curr_Table_Head = Curr_Table_Head->Next;
        Token = strtok(NULL, " ");
        // printf("%s\n", Token);
    }
}

void InsertColumn(Node* First_Table_Head){
    // Get Column Name
    char Temp[MAX_STRING_LENGTH];
    printf("Column Name: ");
    fgets(Temp, MAX_STRING_LENGTH, stdin);
    Temp[strcspn(Temp, "\n")] = '\0';

    // Create Table_Head_Node
    Node* new_Head_Node = (Node*)malloc(sizeof(Node));
    strcpy(new_Head_Node->Data, Temp);
    new_Head_Node->Type = true;
    new_Head_Node->isIndexing = false;
    new_Head_Node->Indexing_Ptr = NULL;
    new_Head_Node->Next = NULL;
    new_Head_Node->Prev = NULL;
    new_Head_Node->Adj_Head = NULL;
    new_Head_Node->Adj_Tail = NULL;

    // Add new Column to Database
    Node* Curr_Table_Head = First_Table_Head;
    if(Curr_Table_Head == NULL){ // Handle for case First Column
        Curr_Table_Head = new_Head_Node;
    } else {
        while(Curr_Table_Head->Next != NULL){
            Curr_Table_Head = Curr_Table_Head->Next;
        }
        new_Head_Node->Prev = Curr_Table_Head;
        Curr_Table_Head->Next = new_Head_Node;
    }

    // Add Data to each Record
    // Print Text & Get Input
    printf("Input Data to each Record Seperated by space: ");
    char InputLine[MAX_STRING_LENGTH];
    fgets(InputLine, MAX_STRING_LENGTH, stdin);

    // Remove the newline character if present
    InputLine[strcspn(InputLine, "\n")] = '\0';

    // Fill new Data for each Record
    char* Token = strtok(InputLine, " ");

    while(Token != NULL){ // Add to Tail
        //Create new_Adj_Node
        Adjacent_Node* new_Adj_Node = CreateAdj_Node(Token);

        if(new_Head_Node->Adj_Head == NULL){
            new_Head_Node->Adj_Head = new_Adj_Node; // Add to Head
            new_Head_Node->Adj_Tail = new_Adj_Node;
        } else {
            new_Head_Node->Adj_Tail->Next = new_Adj_Node;
            new_Adj_Node->Prev = new_Head_Node->Adj_Tail;
            new_Head_Node->Adj_Tail = new_Adj_Node;
        }

        if(!is_Integer(Token)){
            new_Head_Node->Type = false;
        }

        Token = strtok(NULL, " ");
    }
}   

// Example of Usage
// int main()
// {
//     FILE *file = read_csv("../bin/test.csv");
//     if (file == NULL)
//     {
//         return 1;
//     }

//     Node *First_Table_Head = csv_to_linked_list(file);
//     fclose(file);

//     // InsertRecord(First_Table_Head);
//     // InsertColumn(First_Table_Head);

//     // linked_list_to_csv(First_Table_Head, "../bin/test_output.csv");

//     return 0;
// }