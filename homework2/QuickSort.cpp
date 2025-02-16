#include <fstream>
#include <iostream>
#include <vector>

void QuickSort(std::vector<int>& array, int leftBorder, int rightBorder) {
    int left = leftBorder;
    int right = rightBorder;
    
    // Choose support element
    int middle = array[(left + right) / 2];

    while (left <= right) {
        // While a[left] < support elem, left++
        while (array[left] < middle) {
            left++;
        }
        // While a[right] > support elem, right--
        while (array[right] > middle) {
            right--;
        }

        if (left <= right) {
            // swap elements
            int temp = array[left];
            array[left] = array[right];
            array[right] = temp;

            left++;
            right--;
        }
    }
    // if left don't got to rightBorder
    if (left < rightBorder){
        // then sort again
        QuickSort(array, left, rightBorder);
    }
    // if right don't got to leftBorder
    if (right > leftBorder){
        // then sort again
        QuickSort(array, leftBorder, right);
    }
}

void InputFromFile(std::vector<int>& array, int size) {
    // Create input stream to read from file
    std::ifstream input;
    input.open("input" + std::to_string(size) + ".txt");

    // Read from file
    int value;
    while (input >> value) {
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

    int size;
    size = 50000;
    // Input from file
    InputFromFile(array, size);

    // Sort array
    QuickSort(array, 0, size - 1);

    // Output in file
    OutputInFile(array, size);
}
