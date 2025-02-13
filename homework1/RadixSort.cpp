#include <iostream>
#include <vector>

// Exponentiation
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

void RadixSort(std::vector<int>& array, int size, int numOfDigits, int numSystem = 10) {
    // Create numSystem (= 10) temp vectors.
    std::vector<std::vector<int>> temp(numSystem, std::vector<int>());

    int index;
    for (int i = 0; i < numOfDigits; ++i) {
        // temp index
        index = 0;
        for (int j = 0; j < size; ++j) {
            index = (array[j] / Pow(numSystem, i)) % numSystem;
            temp[index].push_back(array[j]);
        }

        // array index
        index = 0;
        // temp elements to array
        for (int k = 0; k < numSystem; ++k) {
            for (int l = 0; l < temp[k].size(); ++l) {
                array[index] = temp[k][l];
                index++;
            }
            // Clear temp vectors
            temp[k].clear();
        }
    }
}


/* Test inputs
15

145 12 1766 3 288 99 2405 18 479 100 387 9095 88 206 473
*/


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
    // Count number of digits of max number 
    int numOfDigits = 0;
    while (maxElem > 0) {
        maxElem /= 10;
        numOfDigits++;
    }

    // Sort array
    RadixSort(array, size, numOfDigits);
    
    // Output
    std::cout << "Результат:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
}
