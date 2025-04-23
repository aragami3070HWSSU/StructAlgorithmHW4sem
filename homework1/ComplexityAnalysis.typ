#import "conf.typ" : conf
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
		// Создаем вспомагательный массив с индексами от 0 до k
		// где k --- значение макс. элемента. За время O(k + 1)
    std::vector<int> tempArray = std::vector<int>(maxElem + 1, 0);

    // Count numbers
		// Подсчет элементов O(n)
    for (int i = 0; i < size; ++i) {
        tempArray[array[i]]++;
    }

    std::cout << "Результат:" << std::endl;
    // Index for main array
    int index = 0;
		// Двойной цикл за время O(n + k + 1), т.к.
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
+ Создание вспомогательного массива идет за $O(k + 1)$, где $k$ --- максимальный элемент массива.
+ Подсчет элементов работает за $O(n)$.
+ Цикл заполняющий массив array отсортированным массивом, работает за $O(n + k + 1)$
+ Таким образом общая временная сложность: $O(n) + O(k + 1) + O(n) + O(n + k + 1) = O(3n + 2k + 2) = O(n + k)$
+ Сложность по памяти --- $O(k + 1) = O(k)$ на хранение массива tempArray.

= Поразрядная сортировка
== Код программы.

== Анализ сложности
