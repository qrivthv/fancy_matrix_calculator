#include <windows.h>
#include "include/Interface.h"
int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    CalcInterface i;
    i.run();
    return 0;
}