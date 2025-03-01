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

void Insert(Tree *&tr, int value) {
    // Create new node
    Tree *newNode = Node(value);
    // If tree empty
    if (!tr) {
        // Then new node is root
        tr = newNode;
    } else {
        // Create temp pointer on tree
        Tree *temp = tr;
        while (temp) {
            // If new elem > temp elem
            if (newNode->Value > temp->Value){
                // If temp have right child
                if (temp->Right){
                    // Then move temp pointer to right child
                    temp = temp->Right;
                }
                else {
                    // New elem is right child temp
                    newNode->Parent =temp;
                    temp->Right = newNode;
                    break;
                }
            }
            // Esle if new elem < temp elem
            else {
                // If temp have left child
                if (temp->Left) {
                    // Then move temp pointer to left child
                    temp = temp->Left;
                }
                else{
                    // New elem is left child temp
                    newNode->Parent = temp;
                    temp->Left = newNode;
                }
            }
        }
    }
}
