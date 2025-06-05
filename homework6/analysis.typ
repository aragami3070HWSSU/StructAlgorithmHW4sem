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
Временная сложность данного алгоритма: \
T = O(1) + O(n) + O(n) $dot$ O(1) $approx$ O(n), где n — длина строки s

Это связано с тем, что несмотря на наличие вложенных циклов, внутренний цикл while в сумме по всем итерациям внешнего цикла выполняется не более n раз.

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
// В худшем случае O(n) - если на каждом шаге z[i] увеличивается до конца строки (в строке с циклом)
Поскольку каждый символ строки рассматривается не более двух раз: один раз при увеличении i и один раз внутри цикла while, то временная сложность алгоритма Z-функции: \
T = O(n) + O(n) $dot$ O(1) = O(n) + O(n) $approx$ O(n), где n — длина строки s. 

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
- Префикс функция работает  за $O(n)$ 
- Цикл работает за $O(n)$

Таким образом общая временная сложность будет: $O(n) + O(n) + O(n) = O(n)$
