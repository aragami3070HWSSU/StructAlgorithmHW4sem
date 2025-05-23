#include <iostream>
#include <string>
class AVLNode {
  public:
    int Value;
    AVLNode *Left;
    AVLNode *Right;
    int Height;

    AVLNode(int k) : Value(k), Left(nullptr), Right(nullptr), Height(1) {
    }
};

class AVLTree {
  private:
    AVLNode *root;

    int Height(AVLNode *node);
    int BalanceFactor(AVLNode *node);
    AVLNode *RightRotate(AVLNode *y);
    AVLNode *LeftRotate(AVLNode *x);
    AVLNode *Insert(AVLNode *node, int key);
    AVLNode *MinValueNode(AVLNode *node);
    AVLNode *DeleteNode(AVLNode *node, int key);
    void PrintHelper(AVLNode *root, std::string indent, bool last);

  public:
    AVLTree() : root(nullptr) {
    }

    void Insert(int key);
    void Remove(int key);
    void Print();
};
