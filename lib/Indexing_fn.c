#include <stdio.h>
#include <stdlib.h>
#include "csv_io.c"

// Define an AVL tree node
struct TreeNode {
    char data[100]; // Assuming a maximum string length of 100 characters
    struct TreeNode* left;
    struct TreeNode* right;
    int height; // Height of the subtree rooted at this node
};

// Function to compute maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to compute height of a tree node
int getHeight(struct TreeNode* node) {
    if (!node) {
        return 0;
    }
    return node->height;
}

// Right rotate
struct TreeNode *rightRotate(struct TreeNode *y) {
  struct TreeNode *x = y->left;
  struct TreeNode *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

  return x;
}

// Left rotate
struct TreeNode *leftRotate(struct TreeNode *x) {
  struct TreeNode *y = x->right;
  struct TreeNode *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(struct TreeNode *N) {
  if (N == NULL)
    return 0;
  return getHeight(N->left) - getHeight(N->right);
}

// Function to insert a new node into the AVL tree
struct TreeNode* insertNode(struct TreeNode* root, const char* value) {
    if (!root) {
        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        strcpy(newNode->data, value); // Copy the string data
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    int cmp = strcmp(value, root->data);
    if (cmp < 0) {
        root->left = insertNode(root->left, value);
    } else if (cmp > 0) {
        root->right = insertNode(root->right, value);
    }

    // Update height and balance the tree
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    // Perform AVL balancing (rotation) if needed
    int balance = getBalance(root);
  if (balance > 1 && cmp < 0)
    return rightRotate(root);

  if (balance < -1 && cmp > 0)
    return leftRotate(root);

  if (balance > 1 && cmp < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && cmp > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
    return root;
}

int binarySearchString(const char* arr[], int size, const char* target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(target, arr[mid]);

        if (cmp == 0) {
            return mid; // Found the target string
        } else if (cmp < 0) {
            right = mid - 1; // Search the left half
        } else {
            left = mid + 1; // Search the right half
        }
    }

    return -1; // Target string not found
}

// Function to search for a string in the binary tree
struct TreeNode* searchNode(struct TreeNode* root, const char* target) {
    if (!root || strcmp(root->data, target) == 0) {
        return root; //When no found return "NULL"
    }

    int cmp = strcmp(target, root->data);
    if (cmp < 0) {
        return searchNode(root->left, target);
    } else {
        return searchNode(root->right, target);
    }
}

// Function to print the AVL tree (in-order traversal)
void printTree(struct TreeNode* root) {
    if (root) {
        printTree(root->left);
        printf("%s ", root->data);
        printTree(root->right);
    }
}

// // Example usage
// int main() {

//     FILE *file = read_csv("../bin/test.csv");
//     if (file == NULL)
//     {
//         return 1;
//     }

//     Node *head = csv_to_linked_list(file);
//     fclose(file);

//     struct TreeNode* avlRoot = NULL;
//     Node* currNode = head;
//     Adjacent_Node* currAdjNode = currNode->Next->Next->Head;
//     while (currAdjNode) {
//         avlRoot = insertNode(avlRoot, currAdjNode->Data);
//         currAdjNode = currAdjNode->Next;
//     }

//     // Print the AVL tree
//     printf("In-order traversal of AVL tree %d:\n", avlRoot->height);
//     printTree(avlRoot);

//     // search the AVL tree
//     const char* target = "Bengaluru";
//     struct TreeNode* result = searchNode(avlRoot, target);
//     if (result) {
//         printf("\n'%s' found in the binary tree.", target);
//     } else {
//         printf("\n'%s' not found in the binary tree.", target);
//     }

//     return 0;
// }
