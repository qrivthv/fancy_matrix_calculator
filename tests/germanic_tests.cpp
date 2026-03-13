#include "../include/Konverter.h"
#include "../include/Drobilnik.h"
#include "../include/Ochepyatka.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <variant>
int GetCommand(const std::variant<Command, int, bool>& var) {
    return std::visit([](auto&& arg) -> int {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Command>) {
            return static_cast<int>(arg);
        }
        else if constexpr (std::is_same_v<T, int>) {
            return 5;
        }
        else if constexpr (std::is_same_v<T, bool>) {
            return 0;
        }
    }, var);
}

TEST(Lang_Test, Vocabs_exist) {
        EXPECT_NO_THROW({
            Konverter::ChangeLanguage();
        });
        EXPECT_NO_THROW({
            Konverter::ChangeLanguage();
        });
}
TEST(Lang_Test, Correct_language) {
        Konverter k;
        EXPECT_EQ(k.Vocab.What(), "Tsar is alive");
        Konverter::ChangeLanguage();
        EXPECT_EQ(k.Vocab.What(), "Tsar is dead");
}
TEST(Lang_Test, Undestands_commands_pre) {
        std::map<std::string, int> m;
        m["опредѣлитель"] = 1;
        m["инверсія"] = 2;
        m["обратная"] = 2;
        m["обратная матрица"] = 2;
        m["альтеръ-эго"] = 2;
        m["перевернуть матрицу"] = 3;
        m["перевернуть"] = 3;
        m["транспонировать"] = 3;
        m["транспонированная матрица"] = 3;
        m["табель о рангах"] =4;
        m["узнать ранг"] =4;
        m["табель"] =4;
        m["ранг"] =4;
        m["преумножить в 67 раз"] =5;
        m["умножiть на 67"] =5;
        m["умножiть 67"] =5;
        m["переумножить матрицы"] =6;
        m["умножiть матрицы"] =6;
        m["прибавлять матрицы"] = 7;
        m["складывать матрицы"] = 7;
        m["складывать"] = 7;
        m["прибавлять"] = 7;
        m["прибавить"] = 7;
        m["сложить"] = 7;
        m["вычесть"] = 8;
        m["вычтетъ"] = 8;
        m["вычесть матрицы"] = 8;
        m["вычтетъ матрицы"] = 8;
        m["идентичность"] = 9;
        m["помѣнять"] = 10;
        m["помѣнять мѣстами"] = 10;
        m["vice versa"] = 10;
        m["путь"] = 11;
        m["отмѣна"] = 12;
        Konverter test1;
        for (const auto& t : m) {
            EXPECT_EQ(GetCommand(test1.CommandFetch(t.first)), t.second);
        }
}

TEST(Lang_Test, Undestands_commands_post) {
    std::map<std::string, int> m;
    m["определитель"] = 1;
    m["детерминант"] =1;
    m["инверс"] = 2;
    m["обратная"] = 2;
    m["обратная матрица"] = 2;
    m["транспонировать"] = 3;
    m["транспонированная матрица"] = 3;
    m["найти ранг"] =4;
    m["ранг"] =4;
    m["умножить 67"] =5;
    m["умножить на 67"] =5;
    m["умножить на число 67"] = 5;
    m["умножить матрицы"] =6;
    m["умножить"] =6;
    m["перемножить матрицы"] = 6;
    m["перемножить"] = 6;
    m["суммировать матрицы"] = 7;
    m["сложить матрицы"] = 7;
    m["сложить"] = 7;
    m["суммировать"] = 7;
    m["вычесть матрицы"] = 8;
    m["вычесть"] = 8;
    m["айдентити"] = 9;
    m["поменять"] = 10;
    m["поменять матрицы местами"] = 10;
    m["поменять матрицы"] = 10;
    m["след"] = 11;
    m["трейс"] = 11;
    m["след матрицы"] = 11;
    m["отмена"] = 12;
    m["отменить"] = 12;
    Konverter test2;
    test2.ChangeLanguage();
    for (const auto& t : m) {
        EXPECT_EQ(GetCommand(test2.CommandFetch(t.first)), t.second);
    }
}
TEST(Lang_Test, Account_for_Misprints) {
    EXPECT_EQ(GetCommand(Konverter::CommandFetch("альтеръ-эго")), 2);

    EXPECT_EQ(GetCommand(Konverter::CommandFetch("альтер-эго")), 2);
    EXPECT_EQ(GetCommand(Konverter::CommandFetch("альтерэго")), 2);
    EXPECT_EQ(GetCommand(Konverter::CommandFetch("альтеэго")), 2);

    EXPECT_EQ(GetCommand(Konverter::CommandFetch("АЛЬТЕРЪ-ЭГО")), 2);
    EXPECT_EQ(GetCommand(Konverter::CommandFetch("АЛЬТЕРЭГО")), 2);

    EXPECT_EQ(GetCommand(Konverter::CommandFetch("АЛьТеРЪ-ЭгО")), 2);
    EXPECT_EQ(GetCommand(Konverter::CommandFetch("АЛьТеРЭгО")), 2);

    EXPECT_EQ(GetCommand(Konverter::CommandFetch("альтго")), 0);
    EXPECT_EQ(GetCommand(Konverter::CommandFetch("альтеръ-эго123456")), 0);
    EXPECT_EQ(GetCommand(Konverter::CommandFetch("АЛЬТЕРальтер-эго")), 0);
}