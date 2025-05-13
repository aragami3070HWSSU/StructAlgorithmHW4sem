#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define ALPHABET_LEN 256

int charsCompared;

void preBmBc(std::vector<int> &table, std::string pattern) {
    for (int i = 0; i < ALPHABET_LEN; i++) {
        table[i] = pattern.length();
    }
    for (int i = 0; i < pattern.length() - 1; i++) {
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

    charsCompared = 0;

    int i = patternL - 1; // Позиция в тексте
    while (i < textL) {
        int j = patternL - 1; // Позиция в шаблоне
        // Сравниваем справа налево
        while (j >= 0 && text[i] == pattern[j]) {
			--i;
			--j;
			charsCompared++;
        }

        if (j < 0) {
            // Найдено совпадение
            return i + 1;
        }
        charsCompared++;

        // Сдвиг по максимальному из двух правил
		i += std::max(badChar[text[i]], goodSuf[j]);
    }
    return 0;
}

int main() {
    std::string text, pattern;
    std::cout << "Введите строку, в которой будет искать подстроку:"
              << std::endl;
    std::cin >> text;
    std::cout << "введите подстроку:" << std::endl;
    std::cin >> pattern;
    int ans = BM(text, pattern);
    for (int i = ans; i < ans + pattern.length(); i++) {
        std::cout << text[i];
    }
    return 0;
}
