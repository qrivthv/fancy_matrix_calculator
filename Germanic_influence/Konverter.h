#ifndef FANCY_MATRIX_CALCULATOR_KONVERTER_H
#define FANCY_MATRIX_CALCULATOR_KONVERTER_H

#include "Drobilnik.h"
#include "Ochepyatka.h"
#include <variant>

class Konverter{
public:
    inline static Perevodchik language;

    static std::variant<Command, int, bool> CommandFetch(std::istream& in){
        std::string command;
        std::getline(in, command);
        std::variant<Command, int, bool> value = Lookalikeness(command, language.CreateSlovar()).commandTranslation();
        return value;
    }
    static void ChangeLanguage() {
        language.Change();
    }
};

#endif //FANCY_MATRIX_CALCULATOR_KONVERTER_H