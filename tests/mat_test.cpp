#include "../include/victim_of_LAaG.h"
#include <iostream>
void test1() {
    std::cout << "TEST1 - RREF\n";
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

void test2() {
    std::cout << "TEST2 - DETERMINANT\n";
    std::cout << "Starting test2...\n";
    v_of_LAaG a (3, 3, {1, 2, -1, -4, 2, 3, -1, -11, -2});
    std::cout << "Matrix created...\n";
    double ans = -39.0;
    double d = a.det();
    std::cout << "Det calculated\n";
    std::cout << (d == ans ? "Success\n" : "Failed\n");
    std::cout << "-------------------------------------\n\n";
}

void test3() {
    std::cout << "TEST3 - INVERSE\n";
    std::cout << "Starting test3...\n";
    v_of_LAaG a (3, 3, {1, 2, 1, 2, 2, 3, -1, 1, -2});
    std::cout << "Initial matrix created...\n";
    v_of_LAaG const ans (3, 3, {7, -5, -4, -1, 1, 1, -4, 3, 2});
    std::cout << "Second matrix created...\n";
    v_of_LAaG f = a.inverse();
    std::cout << "Inverse calculated...\n";
    std::cout << (f == ans ? "Success\n" : "Failed\n");
    std::cout << "-------------------------------------\n\n";

}
int main() {
    test1();
    test2();
    test3();
}