#include <iostream>
#include <vector>

void HeapShifting(std::vector<int>& array, int index, int size) {
    while (true) {
        // Think index elem is max
        int indexMax = index;

        // Set index childs
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        // If exists left child and he > parent
        if (leftChild < size && array[indexMax] < array[leftChild]) {
            // Then change indexMax to leftChild
            indexMax = leftChild;
        }
        // If exists rightChild child and he > parent
        if (rightChild < size && array[indexMax] < array[rightChild]) {
            // Then change indexMax to rightChild
            indexMax = rightChild;
        }

        // If index max dont change
        if (indexMax == index) {
            // End
            return;
        }
        // Else swap child and parent
        else {
            // Swap
            int temp = array[index];
            array[index] = array[indexMax];
            array[indexMax] = temp;

            // index = new parent
            index = indexMax;
        }
    }
}

void HeapSort(std::vector<int>& array, int size) {
    for (int i = (size / 2) + 1; i >= 0; i--) {
        HeapShifting(array, i, size);
    }

    for (int j = size - 1; j > 0; j--) {
        int temp = array[0];
        array[0] = array[j];
        array[j] = temp;

        HeapShifting(array, 0, j);
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
    HeapSort(array, size);

    // Output array
    std::cout << "Результат:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
}
