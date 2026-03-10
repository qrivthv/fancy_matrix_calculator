#ifndef FANCY_MATRIX_CALCULATOR_KONVERTER_H
#define FANCY_MATRIX_CALCULATOR_KONVERTER_H

#include "Drobilnik.h"
#include "Ochepyatka.h"
#include <variant>

class Konverter{
public:
    inline static Perevodchik Vocab;

    static std::variant<Command, int, bool> CommandFetch(const std::string& s){
        std::variant<Command, int, bool> value = Lookalikeness(s, Vocab.CreateSlovar()).commandTranslation();
        return value;
    }
    static void ChangeLanguage() {
        Vocab.Change();
    }
};


#endif //FANCY_MATRIX_CALCULATOR_KONVERTER_H