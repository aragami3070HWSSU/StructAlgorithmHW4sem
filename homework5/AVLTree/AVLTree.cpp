#include "AVLTree.h"

#include <algorithm>

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

template <typename T> AVLNode<T> *AVLTree<T>::RightRotate(AVLNode<T> *y) {
    AVLNode<T> *x = y->Left;
    AVLNode<T> *T2 = x->Right;

    x->Right = y;
    y->Left = T2;

    y->Height = std::max(Height(y->Left), Height(y->Right)) + 1;
    x->Height = std::max(Height(x->Left), Height(x->Right)) + 1;

    return x;
}

template <typename T> AVLNode<T> *AVLTree<T>::LeftRotate(AVLNode<T> *x) {
    AVLNode<T> *y = x->Right;
    AVLNode<T> *T2 = y->Left;

    y->Left = x;
    x->Right = T2;

    x->Height = std::max(Height(x->Left), Height(x->Right)) + 1;
    y->Height = std::max(Height(y->Left), Height(y->Right)) + 1;

    return y;
}

template <typename T> AVLNode<T> *AVLTree<T>::Insert(AVLNode<T> *node, T key) {
    if (node == nullptr)
        return new AVLNode<T>(key);
    if (key < node->Value)
        node->Left = Insert(node->Left, key);
    else if (key > node->Value)
        node->Right = Insert(node->Right, key);
    else
        return node;

    node->Height = 1 + std::max(Height(node->Left), Height(node->Right));
    int balance = BalanceFactor(node);

    if (balance > 1 && key < node->Left->Value)
        return RightRotate(node);

    if (balance < -1 && key > node->Right->Value)
        return LeftRotate(node);

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
    if (root == nullptr)
        std::cout << "Дерево пустое." << std::endl;
    else {
        std::cout << "AVL дерево:" << std::endl;
        PrintHelper(root, "", true);
    }
}

template <typename T> void AVLTree<T>::Insert(T key) {
    root = Insert(root, key);
}

template class AVLTree<int>;
template class AVLTree<float>;
