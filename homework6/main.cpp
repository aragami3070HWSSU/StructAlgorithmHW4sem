#include <iostream>
#include <string>
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

std::vector<int> ZFunction(std::string str) {
    // Массив под результат z-функции
    std::vector<int> zf(str.length());

    int left = 0, right = 0;

    for (int i = 1; i < str.length(); i++) {
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

int SubStringSearchZ(std::string text, std::string pattern) {
    // Массив z-функции
    std::vector<int> zf = ZFunction(pattern + '#' + text);

    // Проходимся по массиву
    for (int i = pattern.length(); i < zf.size(); i++) {
        // Если z-функция равна длине pattern, то нашли pattern
        if (zf[i] == pattern.length()) {
            // Выводим найденный индекс
            return i;
        }
    }
    return -1;
}
int SubStringSearchPrefix(std::string text, std::string pattern) {
    // Массив z-функции
    std::vector<int> prefixArr = PrefixFunction(pattern + '#' + text);

    // Проходимся по массиву
    for (int i = pattern.length(); i < prefixArr.size(); i++) {
        // Если z-функция равна длине pattern, то нашли pattern
        if (prefixArr[i] == pattern.length()) {
            // Выводим найденный индекс
            return i;
        }
    }
    return -1;
}

int main() {
    std::cout << "Введите строку:" << std::endl;
    std::string str;
    std::cin >> str;

    std::cout << "Введите паттерн:" << std::endl;
    std::string pattern;
    std::cin >> pattern;

    // Ищем подстроку в строке
    int test = SubStringSearchZ(str, pattern);
    std::cout << test << std::endl;
    if (test > -1) {
        std::cout << str.substr(test - pattern.length() - 1, pattern.length())
                  << std::endl;
    }
    // Ищем подстроку в строке
    test = SubStringSearchPrefix(str, pattern);
    std::cout << test << std::endl;
    if (test > -1) {
        std::cout << str.substr(test - (pattern.length() * 2), pattern.length())
                  << std::endl;
    }

    std::vector<int> pref = PrefixFunction(pattern + '#' + str);
    std::vector<int> zf = ZFunction(pattern + '#' + str);

    // Вывод префикс функции
    std::cout << "Результат префикс функции:" << std::endl;
    for (int i = 0; i < pref.size(); i++) {
        std::cout << pref[i] << ' ';
    }
    std::cout << std::endl;

    // Вывод z-функции
    std::cout << "Результат z-функции:" << std::endl;
    for (int i = 0; i < pref.size(); i++) {
        std::cout << zf[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
