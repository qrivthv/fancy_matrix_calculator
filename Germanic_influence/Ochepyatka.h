#ifndef FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H
#define FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H

#include <string>
#include <map>
#include <variant>
#include <cctype>
#include <algorithm>
#include <vector>

constexpr int MAX_TYPOS = 3;

enum class Command {
    Determinant = 1, Inverse = 2, Transpose = 3, Rank = 4, Multiplication = 6,
    Sum = 7, Difference = 8, Identity = 9, Swap = 10, Trace = 11, CancelOperation = 12
};

class Lookalikeness{
private:
    std::string written;
    std::pair<std::string, int> match;
    int Levenshtein;
public:
    Lookalikeness(const std::string& s,const std::map<std::string, int>& m) : written(s), match(std::make_pair("temp", 0)), Levenshtein(100) {
        std::string Raskolnikov;
        for (char i : written) {
            Raskolnikov = Raskolnikov + (char)std::tolower(i);
        }
        for (const auto& t : m) {
            int l = LevenshteinDistance(t.first, Raskolnikov);
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
    int LevenshteinDistance(const std::string& s1, const std::string& s2){
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
};

#endif //FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H