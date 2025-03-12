#include "BinarySearchTree.h"
#include <iostream>

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
    }
    else {
        // Create temp pointer on tree
        Tree *temp = tr;
        while (temp) {
            // If new elem > temp elem
            if (newNode->Value > temp->Value) {
                // If temp have right child
                if (temp->Right) {
                    // Then move temp pointer to right child
                    temp = temp->Right;
                }
                else {
                    // New elem is right child temp
                    newNode->Parent = temp;
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
                else {
                    // New elem is left child temp
                    newNode->Parent = temp;
                    temp->Left = newNode;
                    break;
                }
            }
        }
    }
}

Tree *Min(Tree *tr) {
    // If not left child
    if (!tr->Left) {
        // Return tr
        return tr;
    }
    else {
        // Go to left branch to the end
        return Min(tr->Left);
    }
}

Tree *Next(Tree *tr, int value) {
    Tree *node = Find(tr, value);
    // Have right child
    if (node->Right) {
        // Min in right branch
        return Min(node->Right);
    }
    // Parent
    Tree *nodeParent = node->Parent;
    // While not root or node is right parent
    while (nodeParent && node == nodeParent->Right) {
        // Go up the tree
        node = nodeParent;
        nodeParent = nodeParent->Parent;
    }
    return nodeParent;
}

void Delete(Tree *&tr, Tree *node) {
    // Create delete node parent
    Tree *nodeParent = node->Parent;
    // Tree have only one node
    if (!nodeParent) {
        tr = nullptr;
    }
    // Node haven't children
    else if (!node->Left && !node->Right) {
        // Set nullptr pointer on node in parent
        if (nodeParent->Left == node) {
            nodeParent->Left = nullptr;
        }
        if (nodeParent->Right == node) {
            nodeParent->Right = nullptr;
        }
        delete node;
    }
    // If only one child
    else if (!node->Left || !node->Right) {
        // If delete root which have 1 child
        if (!nodeParent) {
            // If have right child
            if (!node->Left) {
                // His become root
                tr = node->Right;
                node->Parent = nullptr;
            }
            // If have left child
            else {
                // His become root
                tr = node->Left;
                node->Parent = nullptr;
            }
        }
        else {
            // If have right child
            if (!node->Left) {
                if (nodeParent->Left == node) {
                    // child of node become child of his "grandpa"
                    nodeParent->Left = node->Right;
                }
                else {
                    // child of node become child of his "grandpa"
                    nodeParent->Right = node->Right;
                }
                // "Grandpa" become parent of this child
                node->Right->Parent = nodeParent;
            }
            else {
                if (nodeParent->Left == node) {
                    // child of node become child of his "grandpa"
                    nodeParent->Left = node->Left;
                }
                else {
                    // child of node become child of his "grandpa"
                    nodeParent->Right = node->Left;
                }
                // "Grandpa" become parent of this child
                node->Left->Parent = nodeParent;
            }
            delete node;
        }
    }
    // Have 2 child
    else {
        // Next after deleting node
        Tree *succ = Next(tr, node->Value);
        node->Value = succ->Value;

        // succ is left child
        if (succ->Parent->Left == succ) {
            // His right child become left child of child's "grandpa"
            succ->Parent->Left = succ->Right;
            // This child exist
            if (succ->Right) {
                // His "grandpa" become his parent
                succ->Right->Parent = succ->Parent;
            }
        }
        else {
            // His right child become right child of child's "grandpa"
            succ->Parent->Right = succ->Right;
            // This child exist
            if (succ->Right) {
                // His "grandpa" become his parent
                succ->Right->Parent = succ->Parent;
            }
        }
		delete succ;
    }
}

Tree *Find(Tree *tr, int value) {
    // If find or tree end
    if (tr->Value == value || !tr) {
        return tr;
    }
    // If value > this elem
    if (tr->Value < value) {
        // Go to right child
        return Find(tr->Right, value);
    }
    else {
        // Go to left child
        return Find(tr->Left, value);
    }
}

void InOrder(Tree *tr) {
    if (tr) {
        // Go to Left child
        InOrder(tr->Left);
        // Output elem
        std::cout << tr->Value << " ";
        // Go to Right child
        InOrder(tr->Right);
    }
}

void PreOrder(Tree *tr) {
    if (tr) {
        // Output elem
        std::cout << tr->Value << " ";
        // Go to Left child
        PreOrder(tr->Left);
        // Go to Right child
        PreOrder(tr->Right);
    }
}

void PostOrder(Tree *tr) {
    if (tr) {
        // Go to Left child
        PostOrder(tr->Left);
        // Go to Right child
        PostOrder(tr->Right);
        // Output elem
        std::cout << tr->Value << " ";
    }
}
