#ifndef FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H
#define FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H

#include <string>
#include <map>
#include <variant>
#include <cctype>
#include <algorithm>

enum Command {
    Determinant = 1, Inverse = 2, Transpose = 3, Rank = 4, Multiplication = 6,
    Sum = 7, Difference = 8, Identity = 9, Swap = 10, Trace = 11, CancelOperation = 12
};

class Lookalikeness{
private:
    std::string written;
    std::pair<std::string, int> match;
    double level;
public:
    Lookalikeness(const std::string& s,const std::map<std::string, int>& m) : written(s), match(std::make_pair("temp", 0)), level(0) {
        for (std::pair<std::string, int> t : m) {
            unsigned long f = std::min(t.first.size(), written.size());
            unsigned long score = 0;
            for (unsigned long i = 0; i < f; i++) {
                if (std::tolower(t.first[i]) == std::tolower(written[i])) {
                    score++;
                }
            }
            score = static_cast<double>(score) / written.size();
            if (level < score) {
                level = score;
                match = t;
            }
        }
    }
    std::variant<Command, int, bool> commandTranslation() {
        if (level > 0.7) {
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
                if (s != "") {
                    return std::stoi(s);
                } else {
                    return static_cast<Command>(5);
                }
            }
        }
        return false;
    }
};

#endif //FANCY_MATRIX_CALCULATOR_OCHEPYATKA_MATCH_H