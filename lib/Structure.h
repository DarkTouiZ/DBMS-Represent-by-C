typedef enum { false, true } bool;// Define bool type -> 0 = false, 1 = true

#define MAX_STRING_LENGTH 1000

bool main_Page = true;

typedef struct Linked Adjacent_Node;
typedef struct Tree Tree;

typedef struct Table_Head
{
    bool Type; // false/true :: This Column contain with String/Integer
    bool isIndexing; // false/true :: This Column has been Indexing(By B-Tree)
    Tree* Indexing_Ptr; // Ptr to B-Tree
    char Data[MAX_STRING_LENGTH]; // Name of Column Header
    struct Table_Head* Next; // Ptr to Next Column
    struct Table_Head* Prev; // Ptr to Prev Column
    Adjacent_Node* Adj_Head; // Ptr to first Row through this Column
    Adjacent_Node* Adj_Tail; // Ptr to last Row through this Column
}Node;

typedef struct Linked{
    char Data[MAX_STRING_LENGTH]; // Data in Row
    struct Linked* Next; // Next Row
    struct Linked* Prev; // Prev Row
    struct Linked* Left; // Left Column
    struct Linked* Right; // Right Column
} Adjacent_Node;

typedef struct Tree{
    char Key[100]; // Key used for sorted in the Tree
    int Height;
    Adjacent_Node* Actual_Ptr; // Ptr to actual data in Database
    int RowIndex; // Number of Record Above
    struct Tree* LeftChild; // Left Child Node
    struct Tree* RightChild; // Right Child Node
}Tree;
