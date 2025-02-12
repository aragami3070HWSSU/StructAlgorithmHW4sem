#include <iostream>
#include <vector>

void CountingSort(std::vector<int>& array, int size, int maxElem) {
    // Create temp array with elements = 0
    std::vector<int> tempArray = std::vector<int>(maxElem + 1, 0);

    // Count numbers
    for (int i = 0; i < size; ++i) {
        tempArray[array[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= maxElem; ++i) {
        for (int j = 0; j < tempArray[i]; ++j) {
            array[index] = i;
            index++;
            std::cout << i << std::endl;
        }
    }
}


int main() {
    // Initialize array
    std::vector<int> array;

    // Input array size
    int size;
    std::cin >> size;

    int maxElem = 0;

    // Filling array
    int elemIn;
    for (int i = 0; i < size; ++i) {
        std::cin >> elemIn;
        array.push_back(elemIn);
        // Find maxElem
        if (elemIn > maxElem) {
            maxElem = elemIn;
        }
    }

    CountingSort(array, size, maxElem);
}
