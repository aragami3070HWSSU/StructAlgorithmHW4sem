#import "../conf.typ" : conf
#show: conf.with(
  title: [Анализ сложности сортировок, не использующих сравнение элементов],
  type: "referat",
  info: (
      author: (
        name: [Смирнова Егора],
        faculty: [КНиИТ],
        group: "251",
        sex: "male"
      ),
      inspector: (
        degree: "",
        name: ""
      )
  ),
  settings: (
    title_page: (
      enabled: true
    ),
    contents_page: (
      enabled: true
    )
  )
)

= Сортировка подсчетом
== Код программы
```cpp
void CountingSort(std::vector<int>& array, int size, int maxElem) {
    // Create temp array with elements = 0
		// Создаем вспомагательный массив с индексами от 0 до k. За время O(k + 1)
    std::vector<int> tempArray = std::vector<int>(maxElem + 1, 0);

    // Count numbers
		// Подсчет элементов O(n)
    for (int i = 0; i < size; ++i) {
        tempArray[array[i]]++;
    }

    std::cout << "Результат:" << std::endl;
    // Index for main array
    int index = 0;
		// Двойной цикл за время O(n), т.к.
		// кол-во итераций второго цикла не больше n
    for (int i = 0; i <= maxElem; ++i) {
        for (int j = 0; j < tempArray[i]; ++j) {
            array[index] = i;
            index++;
            std::cout << i << " ";
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
				// Поиск максимального элемента идет во время
				// заполнения массива, то есть за O(n)
        if (elemIn > maxElem) {
            maxElem = elemIn;
        }
    }

    // Sort array
    CountingSort(array, size, maxElem);
}
```
== Анализ сложности
*Поиск минимального и максимального элемента:*

O(n) — проходим по всему массиву для нахождения минимального и максимального элементов (n --- количество элементов в массиве).

*Создание вспомогательного массива для подсчёта:*

O(k), где k — это максимальный элемент. В худшем случае k может быть O(n).

*Подсчет вхождений каждого элемента:*

O(n) — снова проходим по всему массиву и увеличиваем соответствующие счетчики.

*Перезапись исходного массива в отсортированном порядке:*

O(n + k) — проходим по счетчикам по счетчику, который имеет размер k, и восстанавливаем элементы исходного массива.

*Общая временная сложность:* 

O(n + k), n — количество элементов в исходном массиве, k —  это максимальный элемент

= Поразрядная сортировка
== Код программы.
```cpp
// Exponentiation
// За время = O(k - 1) = O(k) тк degree не больше максимального числа разрядов - 1,
// а цикл O(degree) => O(k - 1) = O(k)
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
		// O(numSystem) (в данном случае от 10) => O(1)
    std::vector<std::vector<int>> temp(numSystem, std::vector<int>());

    int index;
    for (int i = 0; i < numOfDigits; ++i) {
        // temp index
        index = 0;
				
				// Distribution of items in temp
				// За время O(n k)
        for (int j = 0; j < size; ++j) {
						// За время O(k)
            index = (array[j] / Pow(numSystem, i)) % numSystem;
            temp[index].push_back(array[j]);
        }

        // array index
        index = 0;
        // temp elements to array
        for (int k = 0; k < numSystem; ++k) {
						// За время O(n)
            for (int l = 0; l < temp[k].size(); ++l) {
                array[index] = temp[k][l];
                index++;
            }
            // Clear temp vectors
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
				// Поиск максимального элемента идет во время
				// заполнения массива, то есть за O(n)
        if (elemIn > maxElem) {
            maxElem = elemIn;
        }
    }
    // Count number of digits of max number 
		// Подсчет количества разрядов за O(k)
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
```
== Анализ сложности
*Проверка на пустой массив:*

O(1) — проверка на пустой массив занимает постоянное время.

*Разделение массива на отрицательные и неотрицательные числа:*

O(n) — проходим по всему массиву и делим его на две группы.

*Сортировка положительных чисел:*

  Проход по группе — O(m), где m — количество положительных чисел.

  Пусть k — это количество разрядов в максимальном положительном числе, тогда временная сложность для положительных чисел будет: O(k $dot$ m).

*Сортировка отрицательных чисел:* 
Так же как с положительными.

#v(1em)
*Общая временная сложность:*

O(1) + O(k $dot$ n) + O(n) = O(k $dot$ n), k — максимальное количество разрядов в числах массива. 

