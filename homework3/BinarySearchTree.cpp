#include "BinarySearchTree.h"

Tree *Node(int value) {
    // Create new node
    Tree *newNode = new Tree;
    newNode->Value = value;
    // Set null for parent and childern
    newNode->Parent = nullptr;
    newNode->Left = nullptr;
    newNode->Right = nullptr;
    return newNode;
}


