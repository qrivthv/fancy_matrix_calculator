#ifndef FANCY_MATRIX_CALCULATOR_KONVERTER_H
#define FANCY_MATRIX_CALCULATOR_KONVERTER_H

#include "Drobilnik.h"
#include "Ochepyatka match.h"
#include <variant>

// TODO:: ТЕСТЫ!!!!

class Konverter{
private:
    static Perevodchik language;
public:
    Konverter() {
        language = Perevodchik();
    }
    std::variant<Command, int, bool> CommandFetch(std::istream& in){
        std::string command;
        std::getline(in, command);
        std::variant<Command, int, bool> value = Lookalikeness(command, language.CreateVector(command[0])).commandTranslation();
        return value;
    }
    void ChangeLanguage() {
        language.ChangeLanguage();
    }
};

#endif //FANCY_MATRIX_CALCULATOR_KONVERTER_H