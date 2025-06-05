#import "../conf.typ" : conf
#show: conf.with(
  title: [Анализ сложности быстрой и пирамидальной сортировок],
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

= Быстрая сортировка
== Код программы

```cpp
void QuickSort(std::vector<int>& array, int leftBorder, int rightBorder) {
    int left = leftBorder; // O(1)
    int right = rightBorder; // O(1)
    
    // Choose support element
    int middle = array[(left + right) / 2]; // O(1)

		// O(right - left) = O(n), т.к. это правая и левая границы диапазона
    while (left <= right) {
        // While a[left] < support elem, left++
        while (array[left] < middle) {
            left++;
        }
        // While a[right] > support elem, right--
        while (array[right] > middle) {
            right--;
        }

        if (left <= right) { // O(1)
            // swap elements
            int temp = array[left]; // O(1)
            array[left] = array[right]; // O(1)
            array[right] = temp; // O(1)

            left++; // O(1)
            right--; // O(1)
        }
    }

		// Рекурсивные вызовы для сортировки левого и правого подмассивов
		// временная сложность зависит от размера подмассивов
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
```

== Анализ сложности

Для двух вложенных циклов while общая словность равна $O(t + m) = O(n)$, где $t$ --- количество элементов слева от опорного элемента, $m$ --- количество элементов справа от опорного элемента, а $n = t + m$

Для внешнего цикла while временная сложность равна $O(k n)$, где $k$ --- количество повторений цикла внешнего цикла

Если  удачно выбран опорный элемент, то в лучшем случае алгоритм пройдется по всем $n$ элементам в массиве и поделит его рекурсивно пополам $log n$ раз

Согласно теореме о рекурсивном вызове:

$T(n) = c$, если $n = 1 alpha T (n/k) + b n^tau$, если $n > 1$

$
T(n) = cases(
	c,
	2T(n/2) + b n
)
$

$a = 2$ --- количество порождаемых рекурсией подзадач, $n/k$ --- размер подзадач, $k = 2$ --- постоянная.

Трудоемкость рекурсивного перехода имеет сложность $O(n)$

// По следствию теоремы для лучшего случая $T(n) = O(n^tau log_k n) = O(n log n)$

По следствию теоремы для лучшего случая $T(n) = 2T(n/2) + O(n) => T(n) = O(n log n)$

При неудачном выборе опорного элемента (например, самый большой или самый маленький элемент), массив делится на части размера $n - 1$ и $1$. Таким образом количество уровней рекурсии будет $n$. На каждом уровне рекурсии мы выполняем $O(n)$ опреаций по разделению массива и сравнению элементов. В сумме на всех уровня это дает $O(n^2)$. 

// Для худшего случая получим $T(n) = O(n^2)$

Для худшего случая получим $T(n) = T(1) + T(n - 1) = T(n) = O(n^2)$















// === Худший случай
// При неудачном выборе опорного элемента (например, самый большой или самый маленький элемент), массив делится на части размера $n - 1$ и $0$. В этом случае временная сложность:
// $
// T(n) = T(n - 1) + T(n) = T(n) = O(n^2)
// $
// === Лучший случай
// При удачном выборе опорного элемента, массив делится на две примерно равные части. В этом случае временная сложность:
// $
// T(n) = 2 T(n/2) + O(n) => T(n) = O(n log n)
// $

= Пирамидальная сортировка
== Код программы
```cpp
void HeapShifting(std::vector<int>& array, int index, int size) {
		// зависит от высоты кучи, в худшем случае O(log n)
		// в среднем O(1)
    while (true) { 
        // Think index elem is max
        int indexMax = index; // O(1)

        // Set index childs
        int leftChild = 2 * index + 1; // O(1)
        int rightChild = 2 * index + 2; // O(1)

        // If exists left child and he > parent
        if (leftChild < size && array[indexMax] < array[leftChild]) { // O(1)
            // Then change indexMax to leftChild
            indexMax = leftChild; // O(1)
        }
        // If exists rightChild child and he > parent
        if (rightChild < size && array[indexMax] < array[rightChild]) { // O(1)
            // Then change indexMax to rightChild
            indexMax = rightChild; // O(1)
        }

        // If index max dont change
        if (indexMax == index) { // O(1)
            // End
            return; // O(1)
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
    // Build heap by calling HeapShifting
    // i --- parent index
		// O(n/2) => O(n)
    for (int i = (size / 2) + 1; i >= 0; i--) {
				// зависит от высоты кучи, в худшем случае O(log n)
				// в среднем O(1)
        HeapShifting(array, i, size);
    }

    // max elem at head of the pyramid => change head with j elem
    // (last elem from unsorted part of array)
		// O(n log n)
    for (int j = size - 1; j > 0; j--) {
        int temp = array[0]; // O(1)
        array[0] = array[j]; // O(1)
        array[j] = temp; // O(1)
        
        // Rebuild pyramid first without including sorted elem's
        HeapShifting(array, 0, j); // O(log i) <= O(log n)
    }
}
```

== Анализ сложности
Построение кучи:
Несмотря на вызов HeapShifting для приблизительно n/2 элементов, общая сложность построения кучи -- O(n).(Результат основыввается на сумме высот всех узлов)

Сортировка (извлечение элементов):
Цикл выполняется n-1 раз, каждый раз вызывается HeapShifting с временной сложностью O(log n).

Общая временная сложность: O(n $dot$ log n).

