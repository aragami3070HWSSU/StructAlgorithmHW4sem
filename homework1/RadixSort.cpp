#include <iostream>
#include <vector>

int Pow(int input, int degree) {
    if (degree == 0) {
        return 1;
    }
    int output = input;
    for (int iter = 1; iter < degree; ++iter) {
        output *= input;
    }
    return output;
}

void RadixSort(std::vector<int>& array, int size, int bitDepth, int numberSystem = 10) {
    // Create numberSystem (= 10) temp vectors.
    std::vector<std::vector<int>> temp(numberSystem, std::vector<int>());

    int index;
    for (int i = 0; i < bitDepth; ++i) {
        index = 0;
        for (int j = 0; j < size; ++j) {
            index = (array[j] / Pow(numberSystem, i)) % numberSystem;
            temp[index].push_back(array[j]);
        }

        index = 0;
        for (int k = 0; k < numberSystem; ++k) {
            for (int l = 0; l < temp[k].size(); ++l) {
                array[index] = temp[k][l];
                index++;
            }
            temp[k].clear();
        }
    }
}

int main() {
    // Initialize array
    std::vector<int> array;

    // Input array size
    int size;
    std::cout << "Введите размер массива:" << std::endl;
    std::cin >> size;

    int maxElem = 0;

    // Filling array
    std::cout << "Введите массив:" << std::endl;
    int elemIn;
    for (int i = 0; i < size; ++i) {
        std::cin >> elemIn;
        array.push_back(elemIn);
        // Find maxElem
        if (elemIn > maxElem) {
            maxElem = elemIn;
        }
    }

    // Sort array
    RadixSort(array, size, 3);
    
    std::cout << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
}
