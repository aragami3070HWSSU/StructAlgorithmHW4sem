#import "../conf.typ" : conf
#show: conf.with(title: [Анализ префикс функции, z-функции и алгоритма КМП], type: "referat", info: (
  author: (name: [Смирнова Егора], faculty: [КНиИТ], group: "251", sex: "male"),
  inspector: (degree: "", name: ""),
), settings: (title_page: (enabled: true), contents_page: (enabled: true)))

= Префикс функция
== Текст программы
```cpp
std::vector<int> PrefixFunction(std::string str) {
    // Массив под результат префикс функции
    std::vector<int> prefixArr(str.length()); // O(n)
    prefixArr[0] = 0;

    for (int i = 1; i < str.length(); i++) { // O(n)
        int k = prefixArr[i - 1];

        while (k > 0 && str[i] != str[k]) {
            k = prefixArr[k - 1];
        }

        if (str[i] == str[k]) {
            k++;
        }
        prefixArr[i] = k;
    }
    return prefixArr;
}
```
== Анализ сложности
$n$ --- длина строки.
- Инициализация массива за $O(n)$
- Цикл for работает за $O(n)$
  - Внутренний цикл while. $k$ увеличивается на каждом шаге не более, чем на единицу, значит максимальное значение $k = n - 1$. Внутри цикла $k$ только уменьшается. Значит, $k$ не может уменьшится более, чем $n - 1$ раз за все итерации цикла for. Значит сложность выполнения одного цикла while $O(1)$

Таким образом общая временная сложность составит: $O(n) + O(n) * O(1) = O(n)$

= Z-функция
== Текст программы
```cpp
std::vector<int> ZFunction(std::string str) {
    // Массив под результат z-функции
    std::vector<int> zf(str.length()); // O(n)

    int left = 0, right = 0;

    for (int i = 1; i < str.length(); i++) { // O(n)
        zf[i] = std::max(0, std::min(right - i, zf[i - left]));

        while (i + zf[i] < str.length() && str[zf[i]] == str[i + zf[i]]) {
            zf[i]++;
        }
        if (i + zf[i] > right) {
            left = i;
            right = i + zf[i];
        }
    }
    return zf;
}
```
== Анализ сложности
$n$ --- длина строки
- Инициализация массива за $O(n)$
- Цикл for работает за $O(n)$
  - Внутренний цикл while увеличивает $z f [i]$, кол-во повторов не более $n - i$, то есть $O(n - i) = O(n)$ в худшем случае (например для строки "aaaaaa"), а в лучшем случае будет $O(1)$ (например для строки "abcde")

Таким образом общая худашая сложность будет: $O(n) + O(n) * O(n) = O(n^2)$, а лучшая будет: $O(n) + O(n) * O(1) = O(n)$

= Алгоритм Кнута-Морриса-Пратта
== Текст программы
```cpp
std::vector<int> kmp(std::string text, std::string pattern) {
    int patternLength = pattern.length(); // O(1)
    int textLength = text.length(); // O(1)
    std::vector<int> answer(textLength); // O(n)
    // Значение префикс-функции
    std::vector<int> p = PrefixFunction(pattern + "#" + text); // O(n + k)
    int count = 0;
    for (int i = patternLength; i < p.size(); i++) { // O(n)
        if (p[i] == patternLength) {
            answer[count++] = i - 2 * patternLength + 1; // + если считать с 1
        }
    }
    return answer;
}
```
== Анализ сложности
$n$ --- длина строки, $k$ --- длина паттерна
- Инициализация массива за $O(n)$
- Префикс функция работает за $O(n^2)$ в худшем и за $O(n)$ в лучшем случаях
- Цикл работает за $O(n)$

Таким образом общая временная сложность будет: $O(n) + O(n) + O(n) = O(n)$
