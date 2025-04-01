#include "BinarySearchTree.h"
#include <fstream>
#include <iostream>
#include <vector>

void InputFromFile(std::vector<int> &array, int size) {
    // Create input stream to read from file
    std::ifstream input;
    input.open("../input" + std::to_string(size) + ".txt");

    // Read from file
    int value;
    for (int i = 0; i < size; ++i) {
        input >> value;
        array.push_back(value);
    }
    // Close input stream
    input.close();
}

int main() {
    Tree *tr = nullptr;
    std::vector<int> inputArr;
    int size = 10;
    InputFromFile(inputArr, size);

    for (int i = 0; i < size; ++i) {
        Insert(tr, inputArr[i]);
    }

    std::cout << "Прямой обход:" << std::endl;
    PreOrder(tr);
    std::cout << std::endl;
    std::cout << "Симметричный обход:" << std::endl;
    InOrder(tr);
    std::cout << std::endl;
    std::cout << "Обратный обход:" << std::endl;
    PostOrder(tr);
    std::cout << std::endl;

    Delete(tr, Find(tr, 8));

    std::cout << "Нашли и удалили узел со значением 8." << std::endl;
    std::cout << "Прямой обход:" << std::endl;
    PreOrder(tr);
    std::cout << std::endl;
    std::cout << "Симметричный обход:" << std::endl;
    InOrder(tr);
    std::cout << std::endl;
    std::cout << "Обратный обход:" << std::endl;
    PostOrder(tr);
    std::cout << std::endl;
}
