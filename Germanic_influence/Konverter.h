#ifndef FANCY_MATRIX_CALCULATOR_KONVERTER_H
#define FANCY_MATRIX_CALCULATOR_KONVERTER_H

#include "Drobilnik.h"
#include "Ochepyatka match.h"

class Konverter{
private:
    static Perevodchik language;
public:
    Konverter() {
        language = Perevodchik();
    }
    std::optional<int> Command(std::istream& in){
        std::string command;
        std::getline(in, command);
        auto a = Lookalikeness(command, language.CreateVector(command[0])).commandNumber();
        if (a) {
            return a;
        }
        return -1;
    }
    void ChangeLanguage() {
        language.ChangeLanguage();
    }
};

#endif //FANCY_MATRIX_CALCULATOR_KONVERTER_H