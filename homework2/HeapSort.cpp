#include <fstream>
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
    // Build pyramid by calling HeapShifting
    // i --- parent index
    for (int i = (size / 2) + 1; i >= 0; i--) {
        HeapShifting(array, i, size);
    }

    // max elem at head of the pyramid => change head with j elem
    // (last elem from unsorted part of array)
    for (int j = size - 1; j > 0; j--) {
        int temp = array[0];
        array[0] = array[j];
        array[j] = temp;
        
        // Rebuild pyramid first without including sorted elem's
        HeapShifting(array, 0, j);
    }
}

void InputFromFile(std::vector<int>& array, int size) {
    // Create input stream to read from file
    std::ifstream input;
    input.open("input" + std::to_string(size) + ".txt");

    // Read from file
    int value;
    for (int i = 0; i < size; ++i) {
        input >> value;
        array.push_back(value);
    }
    // Close input stream
    input.close();
}

void OutputInFile(std::vector<int>& array, int size) {
    // Create output stream to write in file
    std::ofstream output;
    output.open("output" + std::to_string(size) + ".txt");

    // Write in file
    for (int i = 0; i < size; ++i) {
        output << array[i] << " ";
    }

    // Close output stream
    output.close();
}

int main() {
    // Initialize array
    std::vector<int> array;

    // Array size
    int size;
    size = 1000000;
    // Input from file
    InputFromFile(array, size);

    // For count sort time
    clock_t before = clock();

    // Sort array
    HeapSort(array, size);

    // For count sort time
    clock_t end = clock() - before;
    std::cout << "Sort time: " << (float)end / CLOCKS_PER_SEC << " seconds" << std::endl;

    // Output in file
    OutputInFile(array, size);
}
