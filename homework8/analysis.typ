#import "../conf.typ" : conf
#show: conf.with(
  title: [Анализ алгоритма Бойера-Мура],
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

= Код программы
$n$ --- длина строки/текста, в котором мы ищем шаблон

$m$ --- длина шаблона (искомой строки)

```cpp
// Заполняем таблицу badChar за O(m)
void preBmBc(std::vector<int> &table, std::string pattern) {
    for (int i = 0; i < ALPHABET_LEN; i++) { // O(ALPHABET_LEN)
        table[i] = pattern.length();
    }
    for (int i = 0; i < pattern.length() - 1; i++) { // O(m)
        table[pattern[i]] = pattern.length() - 1 - i;
    }
}

bool isPrefix(std::string word, int pos) {
    int suffixLen = word.length() - pos;

    for (int i = 0; i < suffixLen; i++) {
        if (word[i] != word[pos + i]) {
            return false;
        }
    }
    return true;
}

int suffixLength(std::string word, int pos) {
    int len = 0;
    for (len = 0;
         (word[pos - len] == word[word.length() - 1 - len]) && (len < pos);
         len++)
        ;
    return len;
}

void preBmGc(std::vector<int> &table, std::string pattern) {
    int lastPrefixIndex = 1;
    // Этап 1: Находим границы совпадений
    for (int pos = pattern.length() - 1; pos >= 0; pos--) {
        if (isPrefix(pattern, pos + 1)) {
            lastPrefixIndex = pos + 1;
        }
        table[pos] = (pattern.length() - 1 - pos) + lastPrefixIndex;
    }

    // Этап 2: Заполняем таблицу хороших суффиксов
    for (int pos = 0; pos < pattern.length() - 1; pos++) {
        int suffixLen = suffixLength(pattern, pos);
        if (pattern[pos - suffixLen] !=
            pattern[pattern.length() - 1 - suffixLen]) {
            table[pattern.length() - 1 - suffixLen] =
                pattern.length() - 1 - pos + suffixLen;
        }
    }
}

int BM(std::string text, std::string pattern) {
    std::vector<int> badChar(ALPHABET_LEN);
    std::vector<int> goodSuf(pattern.length());
    int textL = text.length();
    int patternL = pattern.length();

    preBmBc(badChar, pattern);
    preBmGc(goodSuf, pattern);

    int i = patternL - 1; // Позиция в тексте
    while (i < textL) {
        int j = patternL - 1; // Позиция в шаблоне
        // Сравниваем справа налево
        while (j >= 0 && text[i] == pattern[j]) {
			--i;
			--j;
        }

        if (j < 0) {
            // Найдено совпадение
            return i + 1;
        }

        // Сдвиг по максимальному из двух правил
		i += std::max(badChar[text[i]], goodSuf[j]);
    }
    return 0;
}
```

= Анализ сложности
== Построение таблиц
Построение таблиц происходит за $O(m)$ и для "Плохих символов" и "Хороших суффиксов".
== Поиск подстроки
В основном цикле количество сдвигов не может превышать $n/m$, причем каждый сдвиг как минимум на одну позицию.

При выполнении каждого сдвига берутся данные из таблиц "Плохих символов" и "Хороших суффиксов" и из них выбирается максимальное значение. В худшем случае определение каждого займет $O(n dot m)$.

Следовательно, в худшем случае алгоритм работает за:
$
O(m) + O(m) + O(n) dot O(m) = O(n dot m)
$

В лучшем случае алгоритм, применяя таблицы, будет выполнять крупные сдвиги. Это сокращает число сравнений и сдвигов. При этомобщее количество сдвигов не превышает $n/m$:
$
O(m) + O(m) + O(n/m) dot O(m) = O(n)
$

В среднем случае алгоритм так же работает за $O(n)$
