#include "AVLTree/AVLTree.h"

int main() {
    AVLTree<int> tree;
    int n, x;
    std::cout << "Введите размер дерева:" << std::endl;
    std::cin >> n;
    std::cout << "Введите дерево:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> x;
        tree.Insert(x);
    }
    tree.Print();
}
