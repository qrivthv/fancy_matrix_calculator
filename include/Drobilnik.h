#ifndef FANCY_MATRIX_CALCULATOR_DROBILNIK_H
#define FANCY_MATRIX_CALCULATOR_DROBILNIK_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <cctype>
#include <filesystem>
#include <stdexcept>

enum Language {PreReform, PostReform};
class Perevodchik {
private:
    std::map<std::string, int> slovar;
    Language currentLanguage;
public:
    Perevodchik() {
        currentLanguage = PreReform;
        SetLanguage(PreReform);
    }
    void Change() {
        if (currentLanguage == PreReform) {
            SetLanguage(PostReform);
        } else {
            SetLanguage(PreReform);
        }
    }
    void SetLanguage(Language l) {
        std::fstream Source;
        std::cout << std::filesystem::current_path() << std::endl;
        if (l == PreReform) {
            Source.open("../../strings/OperationsPreReform", std::ios::in);
        } else {
            Source.open("../../strings/OperationsPostReform", std::ios::in);
        }
        if (!Source.is_open()) {
            throw std::runtime_error("Сударь, у вас нету доступа к документу!\n No document access");
        }
        std::string s;
        std::getline(Source, s);
        int x = 0;
        try {
            x = std::stoi(s);
        }
        catch (const std::invalid_argument&) {
            std::cout << "Сударь, первая строка это не цифра!\n First line isn't a number";
        }
        slovar.clear();
        for (int i = 1; i < (x+1); i++) {
            std::getline(Source, s);
            std::stringstream ss(s);
            std::string word;
            while (std::getline(ss, word, ',')) {
                slovar.emplace(word,i);
            }
        }
        currentLanguage = l;
        Source.close();
    }
    const std::map<std::string, int>& CreateSlovar() const {
        return slovar;
    }
    std::string What() {
        if (currentLanguage == PreReform) {
            return "Tsar is alive";
        }
        else {
            return "Tsar is dead";
        }
    }
};

#endif //FANCY_MATRIX_CALCULATOR_DROBILNIK_H