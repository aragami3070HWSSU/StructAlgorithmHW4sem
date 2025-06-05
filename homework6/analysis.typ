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
    prefixArr[0] = 0; // O(1)

    for (int i = 1; i < str.length(); i++) { // O(n)
        int k = prefixArr[i - 1]; // O(1)

        while (k > 0 && str[i] != str[k]) {
            k = prefixArr[k - 1]; // O(1)
        }

        if (str[i] == str[k]) {
            k++; // O(1)
        }
        prefixArr[i] = k; // O(1)
    }
    return prefixArr;
}
```
== Анализ сложности
+ Инициализация массива за $O(n)$
+ Внешний цикл работает за $O(n)$
	+ Индексация и присвоение текущего префикса за $O(1)$
	+ Внутренний цикл while в худшем случае выполняется не более $n$ раз за все итерации внешнего цикла. Значит сложность $O(n)$, при условии, что правило произведения тут не действует.

Общая временная сложность будет $O(n) + O(n) = O(n)$

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

В данной реализации каждый символ строки рассматривается не более двух раз: один раз при увеличении i и один раз внутри цикла while.
+ Инициализация массива за $O(n)$
+ Внешний цикл работает за $O(n)$
	+ Внутри цикла все сравнения выполняются за $O(1)$
	+ Когда выполняется сравнение пары символов, правая граница сдвигается, но не больше чем на $n$ символов. за все итерации внешнего цикла.

Общая временная сложность будет $O(n) + O(n) = O(n)$
// В худшем случае O(n) - если на каждом шаге z[i] увеличивается до конца строки (в строке с циклом)

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
- Префикс функция работает за $O(n + k)$ 
- Цикл работает за $O(n)$

Таким образом общая временная сложность будет: $O(n) + O(n + k) + O(n) = O(n + k)$
