typedef enum { false, true } bool;// Define bool type -> 0 = false, 1 = true

typedef struct Linked Adjacent_Node;
typedef struct Tree Tree;

typedef struct Table_Head
{
    bool Type; // false/true :: This Column contain with String/Integer
    bool isIndexing; // false/true :: This Column has been Indexing(By B-Tree)
    Tree* Indexing_Ptr; // Ptr to B-Tree
    char Data[100]; // Name of Column Header
    struct Table_Head* Next; // Ptr to Next Column
    struct Table_Head* Prev; // Ptr to Prev Column
    Adjacent_Node* Head; // Ptr to first Row through this Column
    Adjacent_Node* Tail; // Ptr to last Row through this Column
}Node;

typedef struct Linked{
    char Data[100]; // Data in Row
    struct Linked* Next; // Next Row
    struct Linked* Prev; // Prev Row
} Adjacent_Node;

typedef struct Tree{
    char Key[100]; // Key used for sorted in the Tree
    int Height;
    Adjacent_Node* Ptr; // Ptr to actual data in Database
    struct Tree* Left; // LeftChild
    struct Tree* Right; // RightChild
}Tree;
