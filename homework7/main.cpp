#include <iostream>
#include <vector>
std::vector<int> PrefixFunction(std::string str) {
    // Массив под результат префикс функции
    std::vector<int> prefixArr(str.length());
    prefixArr[0] = 0;

    for (int i = 1; i < str.length(); i++) {
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

std::vector<int> kmp(std::string text, std::string pattern) {
    int patternLength = pattern.length();
    int textLength = text.length();
    std::vector<int> answer(textLength);

    // Значение префикс-функции
    std::vector<int> p = PrefixFunction(pattern + "#" + text);

    int count = 0;
    for (int i = patternLength; i < p.size(); i++) {
        if (p[i] == patternLength) {
            answer[count++] = i - 2 * patternLength + 1; // + если считать с 1
        }
    }
    return answer;
}

int main() {
    std::cout << "Введите строку:" << std::endl;
    std::string text, pattern;
    std::cin >> text;
    std::cout << "Введите паттерн:" << std::endl;
    std::cin >> pattern;
    std::vector<int> kmpv = kmp(text, pattern);
    for (int i = 0; i < kmpv.size(); i++)
        std::cout << kmpv[i] << ' ';
    std::cout << std::endl;

    return 0;
}
