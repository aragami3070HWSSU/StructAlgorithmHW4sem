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
n --- количество элементов массива.

k --- значение максимального элемента.
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
		// Двойной цикл за время O(n * k), т.к.
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

+ Поиск максимального элемента идет за время $O(n)$
+ Создание вспомогательного массива идет за $O(k)$, где $k$ --- максимальный элемент массива.
+ Подсчет элементов работает за $O(n)$.
+ Цикл заполняющий массив array отсортированным массивом, работает за $O(n) + O(k)$

Таким образом общая временная сложность: $O(n) + O(k) + O(n) + O(n) * O(k) =  O(n k)$
- Сложность по памяти --- $O(k) = O(k)$ на хранение массива tempArray.

= Поразрядная сортировка
== Код программы.
n --- количество элементов массива.

k --- максимальное число разрядов числа.

p = numSystem --- основание системы счисления
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
		// За время O(n k^2)
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
				// За время O(numSystem * n) => O(n)
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
+ Поиск максимального элемента идет за время $O(n)$
+ Подсчет количества разрядов за $O(k)$
+ Создание вспомогательного массива идет за $O(p) = O(1)$, где $p$ --- основание системы счисления --- константа
+ Цикл по всем разрядам $O(k)$. Вложеные циклы:
	- Цикл распределения элементов в вспомогательный массив --- $O(n)$:
		- Подсчет степени $p^i$ --- $O(k)$
	- Двойной цикл на перезаписывание вектора от $#[temp] [0]$ до $#[temp] [p - 1]$ в массив array --- $O(p dot n) = O(n)$

Таким образом общая временная сложность: $O(n) + O(k) + O(k) dot (O(n) dot O(k) + O(n)) = O(n k^2)$. При малом числе разрядов сложность близка к линейной.
- Сложность по памяти --- $O(p) = O(1)$ на хранение массива temp.
