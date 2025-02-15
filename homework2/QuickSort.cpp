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
    QuickSort(array, 0, size);

    std::cout << "Результат:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
}
