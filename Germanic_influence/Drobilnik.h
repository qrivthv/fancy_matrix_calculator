#ifndef FANCY_MATRIX_CALCULATOR_DROBILNIK_H
#define FANCY_MATRIX_CALCULATOR_DROBILNIK_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <unordered_map>

enum Language {PreReform, PostReform};
class Perevodchik {
private:
    std::unordered_map<std::string, int> slovar;
    Language currentLanguage;
public:
    Perevodchik() {
        SetLanguage(PreReform);
    }
    void ChangeLanguage() {
        if (currentLanguage == PreReform) {
            SetLanguage(PostReform);
        } else {
            SetLanguage(PreReform);
        }
    }
    void SetLanguage(Language l) {
        std::fstream Source;
        if (l == PreReform) {
            std::fstream Source("OperationsPreReform", std::ios::in);
        } else {
            std::fstream Source("OperationsPostReform", std::ios::in);
        }
        if (!Source.is_open()) {
            throw std::runtime_error("Cannot open file");
        }
        std::string s;
        std::getline(Source, s);
        int x = 0;
        try {
            x = std::stoi(s);
        }
        catch (const std::invalid_argument&) {
            std::cout << "First line is not int\n";
        }
        std::unordered_map<std::string, int> temp;
        for (int i = 1; i < (x+1); i++) {
            std::getline(Source, s);
            std::stringstream ss(s);
            std::string word;
            while (std::getline(ss, word, ',')) {
                temp.emplace(word,i);
            }
        }
        slovar = std::move(temp);
        currentLanguage = l;
        Source.close();
    }
};
#endif //FANCY_MATRIX_CALCULATOR_DROBILNIK_H