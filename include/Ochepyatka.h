#ifndef FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H
#define FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H

#include <string>
#include <map>
#include <variant>
#include <cctype>
#include <algorithm>
#include <vector>
#include <windows.h>

constexpr int MAX_TYPOS = 5;

enum class Command {
    Determinant = 1, Inverse = 2, Transpose = 3, Rank = 4, Multiplication = 6,
    Sum = 7, Difference = 8, Identity = 9, Swap = 10, Trace = 11, CancelOperation = 12
};

class Lookalikeness{
private:
    std::u16string written;
    std::pair<std::u16string, int> match;
    int Levenshtein;
public:
    Lookalikeness(const std::string& s, std::map<std::u16string, int>& m) {
        written = toLowerCase(utf8_to_utf16(s));
        Levenshtein = 100;
        match = std::make_pair<std::u16string, int>(utf8_to_utf16(""), 0);
        for (const auto& t : m) {
            int l = LevenshteinDistance(t.first, written);
            if (l < Levenshtein) {
                Levenshtein = l;
                match = t;
            }
        }
    }
    std::variant<Command, int, bool> commandTranslation() {
        if (Levenshtein < MAX_TYPOS) {
            if (match.second != 5){
                return static_cast<Command>(match.second);
            }
            else {
                std::string s;
                for (char i : written) {
                    if (i <= '9' && i >= '0') {
                        s += i;
                    }
                }
                if (!s.empty()) {
                    return std::stoi(s);
                } else {
                    return static_cast<Command>(6);
                }
            }
        }
        return false;
    }
    int LevenshteinDistance(const std::u16string& s1, const std::u16string& s2){
        int m = s1.length();
        int n = s2.length();
        std::vector<int> prevRow(n + 1);
        std::vector<int> currRow(n + 1);
        for (int j = 0; j <= n; j++) {
            prevRow[j] = j;
        }
        for (int i = 1; i <= m; i++) {
            currRow[0] = i;
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    currRow[j] = prevRow[j - 1];
                }
                else {
                    currRow[j] = 1
                                + std::min(

                                    currRow[j - 1],
                                    std::min(
                                        prevRow[j],
                                        prevRow[j - 1]));
                }
            }

            prevRow = currRow;
        }
        return currRow[n];
    }
    std::u16string toLowerCase(std::u16string s) {
        for (char16_t& c : s)
        {
            if (c >= u'А' && c <= u'Я')
                c += 32;
            if (c == u'Ѣ') {
                c = u'ѣ';
            }
            if (c == u'I') {
                c = u'i';
            }
        }
        return s;
    }
    static std::u16string utf8_to_utf16(const std::string& input) {
        int size = MultiByteToWideChar(
            CP_UTF8,
            0,
            input.data(),
            (int)input.size(),
            nullptr,
            0
        );

        std::u16string result(size, 0);

        MultiByteToWideChar(
            CP_UTF8,
            0,
            input.data(),
            (int)input.size(),
            reinterpret_cast<wchar_t*>(result.data()),
            size
        );

        return result;
    }
};

#endif //FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H