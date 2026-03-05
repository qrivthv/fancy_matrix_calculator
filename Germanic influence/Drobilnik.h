#ifndef FANCY_MATRIX_CALCULATOR_DROBILNIK_H
#define FANCY_MATRIX_CALCULATOR_DROBILNIK_H

#include <iostream>
#include <fstream>
#include <string>

class Drobilnik{
private:
    std::ofstream partition;
    std::string nameFile;
    int size;
public:
    Drobilnik(std::string list, int i = 3) {
        nameFile = list;
        size = i;
        std::string Name = list.substr(0, list.find('.'));
        Name = Name + " partition";
        std::ofstream f (Name, std::ios::app);
        partition = std::move(f);
    }

    ~Drobilnik() {
        if (partition) {
            partition.close();
        }
    }
};
#endif //FANCY_MATRIX_CALCULATOR_DROBILNIK_H