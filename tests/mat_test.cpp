#include "../include/victim_of_LAaG.h"
#include <iostream>
void test1() {
    std::cout << "TEST1\n";
    std::cout << "Starting test1...\n";
    v_of_LAaG a (3, 4, {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22});
    std::cout << "Initial matrix created...\n";
    v_of_LAaG const ans (3, 4, {1, 0, 0, -8, 0, 1, 0, 1, 0, 0, 1, -2});
    std::cout << "Second matrix created...\n";
    v_of_LAaG f = a.rref();
    std::cout << "RREF calculated...\n";
    std::cout << (f == ans ? "Success\n" : "Failed\n");
    std::cout << "-------------------------------------\n\n";

}

int main() {
    test1();
}