#include <gtest/gtest.h>
#include "../include/Interface.h"


TEST(CalcInterfaceTest, just_create) {
    CalcInterface calc;
    ASSERT_TRUE(true);
}
TEST(CalcInterfaceTest, help) {
    CalcInterface calc;
    calc.processInput("help");
    SUCCEED();
}
TEST(CalcInterfaceTest, exit) {
    CalcInterface calc;
    calc.processInput("exit");
    SUCCEED();
}
TEST(CalcInterfaceTest, unknown_cmd) {
    CalcInterface calc;
    calc.processInput("smth");
    SUCCEED();
}
TEST(CalcInterfaceTest, det) {
    CalcInterface calc;
    calc.processInput("опредѣлитель");
    SUCCEED();
}
TEST(CalcInterfaceTest, scalar) {
    CalcInterface calc;
    calc.processInput("умножiть на 5");
    SUCCEED();
}
TEST(CalcInterfaceTest,cmd_works) {
    CalcInterface calc;
    auto mA = std::make_unique<v_of_LAaG>(2, 2, std::vector<double>{1, 2, 3, 4});
    auto mB = std::make_unique<v_of_LAaG>(2, 2, std::vector<double>{1, 2, 3, 4});
    calc.MatricesTest(std::move(mA),std::move(mB));
    std::stringstream output;
    auto buf = std::cout.rdbuf(output.rdbuf());
    calc.processInput("опредѣлитель");
    calc.processInput("ранг");
    calc.processInput("путь");
    std::string result = output.str();
    std::cout.rdbuf(buf);
    EXPECT_TRUE(result.find("-2") != std::string::npos);
    EXPECT_TRUE(result.find("5") != std::string::npos);
    EXPECT_TRUE(result.find("2") != std::string::npos);
}