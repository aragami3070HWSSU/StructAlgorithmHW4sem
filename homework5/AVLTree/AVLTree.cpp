#include "AVLTree.h"

template <typename T> int AVLTree<T>::Height(AVLNode<T> *node) {
    if (node == nullptr)
        return 0;
    return node->Height;
}

template <typename T> int AVLTree<T>::BalanceFactor(AVLNode<T> *node) {
    if (node == nullptr)
        return 0;
    return Height(node->Left) - Height(node->Right);
}

template <typename T> AVLNode<T> *AVLTree<T>::RightRotate(AVLNode<T> *node) {
    AVLNode<T> *leftNode = node->Left;
    AVLNode<T> *T2 = leftNode->Right;

    leftNode->Right = node;
    node->Left = T2;

    node->Height = std::max(Height(node->Left), Height(node->Right)) + 1;
    leftNode->Height =
        std::max(Height(leftNode->Left), Height(leftNode->Right)) + 1;

    return leftNode;
}

template <typename T> AVLNode<T> *AVLTree<T>::LeftRotate(AVLNode<T> *node) {
    AVLNode<T> *rightChild = node->Right;
    AVLNode<T> *T2 = rightChild->Left;

    rightChild->Left = node;
    node->Right = T2;

    node->Height = std::max(Height(node->Left), Height(node->Right)) + 1;
    rightChild->Height =
        std::max(Height(rightChild->Left), Height(rightChild->Right)) + 1;

    return rightChild;
}

template <typename T> AVLNode<T> *AVLTree<T>::Insert(AVLNode<T> *node, T key) {
    if (node == nullptr) {
        return new AVLNode<T>(key);
    }
    if (key < node->Value) {
        node->Left = Insert(node->Left, key);
    }
    else if (key > node->Value) {
        node->Right = Insert(node->Right, key);
    }
    else {
        return node;
    }

    node->Height = 1 + std::max(Height(node->Left), Height(node->Right));
    int balance = BalanceFactor(node);

    if (balance > 1 && key < node->Left->Value) {
        return RightRotate(node);
    }

    if (balance < -1 && key > node->Right->Value) {
        return LeftRotate(node);
    }

    if (balance > 1 && key > node->Left->Value) {
        node->Left = LeftRotate(node->Left);
        return RightRotate(node);
    }

    if (balance < -1 && key < node->Right->Value) {
        node->Right = RightRotate(node->Right);
        return LeftRotate(node);
    }
    return node;
}
template <typename T>
void AVLTree<T>::PrintHelper(AVLNode<T> *root, std::string indent, bool last) {
    if (root != nullptr) {

        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        }
        else {
            std::cout << "L----";
            indent += "|  ";
        }
        std::cout << root->Value << "(" << root->Height << ")" << std::endl;
        PrintHelper(root->Left, indent, false);
        PrintHelper(root->Right, indent, true);
    }
}
template <typename T> void AVLTree<T>::Print() {
    if (root == nullptr) {
        std::cout << "Дерево пустое." << std::endl;
    }
    else {
        std::cout << "AVL дерево:" << std::endl;
        PrintHelper(root, "", true);
    }
}

template <typename T> AVLNode<T> *AVLTree<T>::MinValueNode(AVLNode<T> *node) {
    AVLNode<T> *current = node;
    while (current->Left != nullptr)
        current = current->Left;
    return current;
}

template <typename T>
AVLNode<T> *AVLTree<T>::DeleteNode(AVLNode<T> *root, T key) {
    // Perform standard BST delete
    if (root == nullptr)
        return root;

    if (key < root->Value)
        root->Left = DeleteNode(root->Left, key);
    else if (key > root->Value)
        root->Right = DeleteNode(root->Right, key);
    else {
        // Node with only one child or no child
        if ((root->Left == nullptr) || (root->Right == nullptr)) {
            AVLNode<T> *temp = root->Left ? root->Left : root->Right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
        }
        else {

            AVLNode<T> *temp = MinValueNode(root->Right);
            root->Value = temp->Value;
            root->Right = DeleteNode(root->Right, temp->Value);
        }
    }

    if (root == nullptr)
        return root;

    // Update height of the current node
    root->Height = 1 + std::max(Height(root->Left), Height(root->Right));

    // Get the balance factor of this node
    int balance = BalanceFactor(root);

    // If this node becomes unbalanced, then there are 4
    // cases

    // Left Left Case
    if (balance > 1 && BalanceFactor(root->Left) >= 0)
        return RightRotate(root);

    // Left Right Case
    if (balance > 1 && BalanceFactor(root->Left) < 0) {
        root->Left = LeftRotate(root->Left);
        return RightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && BalanceFactor(root->Right) <= 0)
        return LeftRotate(root);

    // Right Left Case
    if (balance < -1 && BalanceFactor(root->Right) > 0) {
        root->Right = RightRotate(root->Right);
        return LeftRotate(root);
    }

    return root;
}

template <typename T> void AVLTree<T>::Insert(T key) {
    root = Insert(root, key);
}

template <typename T> void AVLTree<T>::Remove(T key) {
    root = DeleteNode(root, key);
}

template class AVLTree<int>;
