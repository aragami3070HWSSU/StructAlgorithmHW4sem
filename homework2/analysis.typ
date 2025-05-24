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
=== Худший случай
При неудачном выборе опорного элемента (например, самый большой или самый маленький элемент), массив делится на части размера $n - 1$ и $0$. В этом случае временная сложность:
$
T(n) = T(n - 1) + T(0) = T(n) = O(n^2)
$
=== Лучший случай
При удачном выборе опорного элемента, массив делится на две примерно равные части. В этом случае временная сложность:
$
T(n) = 2 T(n/2) + O(n) => T(n) = O(n log n)
$


