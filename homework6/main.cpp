#include <iostream>
#include <string>
#include <vector>

std::vector<int> PrefixFunction(std::string s) {
    std::vector<int> p(s.length());
    p[0] = 0;
    for (int i = 1; i < s.length(); i++) {
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k])
            k = p[k - 1];
        if (s[i] == s[k])
            k++;
        p[i] = k;
    }
    return p;
}

std::vector<int> ZFunction(std::string s) {
    std::vector<int> zf(s.length());
    int left = 0, right = 0;

    for (int i = 1; i < s.length(); i++) {
        zf[i] = std::max(0, std::min(right - i, zf[i - left]));
        while (i + zf[i] < s.length() && s[zf[i]] == s[i + zf[i]])
            zf[i]++;
        if (i + zf[i] > right) {
            left = i;
            right = i + zf[i];
        }
    }
    return zf;
}

int main() {
    std::cout << "Введите строку:" << std::endl;
    std::string str;
	std::cin >> str;
    std::cout << "Её префикс и z-функции:" << std::endl;
    std::vector<int> pref = PrefixFunction(str);
    std::vector<int> zf = ZFunction(str);
    for (int i = 0; i < str.length(); i++)
        std::cout << pref[i] << ' ';
    std::cout << std::endl;
    for (int i = 0; i < str.length(); i++)
        std::cout << zf[i] << ' ';
    std::cout << std::endl;

    return 0;
}
