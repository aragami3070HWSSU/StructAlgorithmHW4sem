#include <iostream>
#include <string>
template <typename T> class AVLNode {
  public:
    T Value;
    AVLNode *Left;
    AVLNode *Right;
    int Height;

    AVLNode(T k) : Value(k), Left(nullptr), Right(nullptr), Height(1) {
    }
};

template <typename T> class AVLTree {
  private:
    AVLNode<T> *root;

    int Height(AVLNode<T> *node);
    int BalanceFactor(AVLNode<T> *node);
    AVLNode<T> *RightRotate(AVLNode<T> *y);
    AVLNode<T> *LeftRotate(AVLNode<T> *x);
    AVLNode<T> *Insert(AVLNode<T> *node, T key);
    AVLNode<T> *MinValueNode(AVLNode<T> *node);
    AVLNode<T> *DeleteNode(AVLNode<T> *root, T key);
    void PrintHelper(AVLNode<T> *root, std::string indent, bool last);

  public:
    AVLTree() : root(nullptr) {
    }

    void Insert(T key);
    void Remove(T key);
    void Print();
};
