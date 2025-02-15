#include <iostream>
#include <vector>

// Merge two sorted arrays
void Merge(std::vector<int>& array, int leftBorder, int rightBorder, int middle){
    if (leftBorder >= rightBorder || rightBorder < middle || leftBorder > middle) {
        // End
        return;
    }
    // If only 2 elem in array and they not sorted
    if ((rightBorder - leftBorder == 1) && (array[leftBorder] > array[rightBorder])) {
        // Swap elemenst
        int temp = array[leftBorder];
        array[leftBorder] = array[rightBorder];
        array[rightBorder] = temp;
        // End
        return;
    }
    // Create temp array
    std::vector<int> tempArray(rightBorder - leftBorder + 1);

    int current = 0;

    int left = leftBorder;
    int right = middle + 1;

    while (rightBorder - leftBorder + 1 > current) {
        // If left met middle
        if (left > middle) {
            // Add to temp array all elem from right to right border
            for (int i = right; i <= rightBorder; ++i) {
                tempArray[current] = array[i];
                current++;
            }
        }
        // If right met right border
        else if (right > rightBorder) {
            // Add to temp array all elem from left to middle
            for (int i = left; i <= middle; ++i) {
                tempArray[current] = array[i];
                current++;
            }
        }
        // If left elem > right
        else if (array[left] > array[right]) {
            // Add to temp array right elem
            tempArray[current] = array[right];
            current++;
            right++;
        }
        // Else add to temp array left elem
        else {
            tempArray[current] = array[left];
            current++;
            left++;
        }
    }

    // Index in array
    current = leftBorder;
    // Write in array begin left border all elem from temp array
    for (auto iter = tempArray.begin(); iter < tempArray.end(); ++iter) {
        array[current] = *iter;
        current++;
    }
}


void MergeSort(std::vector<int>& array, int leftBorder, int rightBorder) {
    // If left border met right border
    if (leftBorder >= rightBorder) {
        // Then end
        return;
    }

    // Set middle
    int middle = (leftBorder + rightBorder) / 2;

    // Sort from left border to middle
    MergeSort(array, leftBorder, middle);
    // Sort from middle + 1 to right border
    MergeSort(array, middle + 1, rightBorder);

    // Merge
    Merge(array, leftBorder, rightBorder, middle);
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
    MergeSort(array, 0, size);

    // Output array
    std::cout << "Результат:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
}
