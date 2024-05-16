<<<<<<< Updated upstream
#include "Header.c"
=======
#include "lib/Header.c"

int main()
{
    FILE *file = read_csv("bin/test.csv");
    if (file == NULL)
    {
        return 1;
    }

    Node *First_Table_Head = csv_to_linked_list(file);
    fclose(file);

    // MakeIndexing(First_Table_Head->Next);
    // int *ReturnIndex;
    // Adjacent_Node *Actual_Data = Search_Adj_Node(First_Table_Head->Next, "Hyderabad", ReturnIndex);
    // PrintRecord_by_Ref(Actual_Data, 3);

    // linked_list_to_csv(First_Table_Head, "bin/test_output.csv");

        return 0;
}
>>>>>>> Stashed changes
