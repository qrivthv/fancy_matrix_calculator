
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <chrono>

#include "victim_of_LAaG.h"
#include "Konverter.h"
#include "Ochepyatka.h"

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    void logInfo(const std::string& message) {
        writeLog("INFO",message);
    }
    void logWarning(const std::string& message) {
        writeLog("WARNING",message);
    }
    void logError(const std::string& message) {
        writeLog("ERROR",message);
    }
private:
    std::ofstream _logFile;
    Logger() {
        try {
            _logFile.open("mat_calc.log", std::ios::app);
            if (!_logFile.is_open()) {
                throw std::runtime_error("Couldn't open mat_calc.log");
            }
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

    };
    ~Logger() {
        if (_logFile.is_open()) _logFile.close();
    }
    void writeLog(const std::string& level, const std::string& message) {
        //TODO Add time of log
        std::string log_message = level + ": " + message;
        if (_logFile.is_open()) {
            _logFile << log_message << std::endl;
            _logFile.flush();
        }
    }
};
class CalcInterface {
private:
    std::unique_ptr<v_of_LAaG> matA;
    std::unique_ptr<v_of_LAaG> matB;

    void processCmd(const std::string& fullCmd) {
        std::stringstream ss(fullCmd);
        std::string cmd;
        ss >> cmd;
        if (cmd == "help") {
            std::cout<<"тут типа описание всех команд"<< std::endl; //TODO дописать вот это
            Logger::getInstance().logInfo("Cmd: help"); //TODO дописать все логи
        }
        if (cmd == "enter") {
            try {
                std::string m;
                if (!(ss>>m)) {
                    Logger::getInstance().logError("No matrix name entered");
                    throw std::runtime_error("Имя матрицы не было указано");
                }
                if (m!="A" && m!="B") {
                    Logger::getInstance().logError("Invalid matrix name");
                    throw std::runtime_error("Неверное имя матрицы. Доступны только матрицы A и B");
                }
                std::cout<<"Введите размеры матрицы через пробел:"<<'\n';
                int rows, cols;
                std::string input;
                std::getline(std::cin, input);
                std::stringstream ss(input);
                if (!(ss >> rows >> cols)) {
                    Logger::getInstance().logError("Wrong input format of matrix size");
                    throw std::runtime_error("Неверный формат ввода размеров");
                }
                std::string smth;
                if (ss>>smth) {
                    Logger::getInstance().logError("Wrong input format of matrix size");
                    throw std::runtime_error("Неверный формат ввода размеров");
                }
                if (rows<=0 or cols<=0) {
                    Logger::getInstance().logError("Not positive matrix size");
                    throw std::runtime_error("Размеры матрицы должны быть положительны");
                }
                std::cout<<"Введите матрицу:"<<'\n';
                if (m == "A") {
                    matA = std::make_unique<v_of_LAaG>(rows, cols);
                    for (size_t i = 0; i < rows; i++) {
                        for (size_t j = 0; j < cols; j++) {
                            std::cin>>(*matA)[i][j];
                        }
                    }
                    Logger::getInstance().logInfo("Entered matrix "+m);
                    std::cout<<"Вы успешно ввели матрицу!"<<'\n';
                }
                else if (m == "B") {
                    matB = std::make_unique<v_of_LAaG>(rows, cols);
                    for (size_t i = 0; i < rows; i++) {
                        for (size_t j = 0; j < cols; j++) {
                            std::cin>>(*matB)[i][j];
                        }
                    }
                    Logger::getInstance().logInfo("Entered matrix "+m);
                    std::cout<<"Вы успешно ввели матрицу!"<<'\n';
                }
                else {
                    std::cout<<"Матрицы "<<m<<" не существует"<<'\n';
                    Logger::getInstance().logWarning("Attempt to enter not existing matrix.");
                }

            }
            catch (std::exception& e) {
                std::cerr<<"Ошибка: " << e.what() << std::endl;
                Logger::getInstance().logError(std::string(e.what()));
            }
        }

        else if (cmd == "print") {
            try {
                std::string m;
                ss>>m;
                if (m == "A") {
                    std::cout<<*matA<<'\n';
                    Logger::getInstance().logInfo("Printed matrix A");
                }
                else if (m == "B") {
                    std::cout<<*matB<<'\n';
                    Logger::getInstance().logInfo("Printed matrix B");
                }
                else {
                    Logger::getInstance().logError("Invalid matrix name");
                    throw std::runtime_error("Неверное имя матрицы. Доступны только матрицы A и B");
                }
            }
            catch (std::exception& e) {
                std::cerr<<"Ошибка: " << e.what() << std::endl;
                Logger::getInstance().logError(std::string(e.what()));
            }
        }
        else if (cmd == "add") {
            v_of_LAaG matC = (*matA) + (*matB);
            std::cout << matC<<'\n';
            Logger::getInstance().logInfo("Added matrix B to A");
        }
        else if (cmd == "sub") {
            v_of_LAaG matC = (*matA) - (*matB);
            std::cout << matC<<'\n';
            Logger::getInstance().logInfo("Substituted matrix B from A");
        }
        else if (cmd == "mul") {
            v_of_LAaG matC = (*matA) * (*matB);
            std::cout << matC<<'\n';
            Logger::getInstance().logInfo("Multiplied matrix A by B");
        }
        else if (cmd == "mul_by_scalar") {
            try {
                std::string m;
                if (!(ss>>m)) {
                    Logger::getInstance().logError("No matrix name entered");
                    throw std::runtime_error("Имя матрицы не было указано");
                }
                if (m!="A" && m!="B") {
                    Logger::getInstance().logError("Invalid matrix name");
                    throw std::runtime_error("Неверное имя матрицы. Доступны только матрицы A и B");
                }

                std::cout<<"Введите число:"<<'\n';
                double x;
                std::string input;
                std::getline(std::cin, input);
                std::stringstream ss(input);
                if (!(ss >> x)) {
                    Logger::getInstance().logError("Wrong input format of scalar");
                    throw std::runtime_error("Скаляр может принимать только численное значение");
                }
                std::string smth;
                if (ss>>smth) {
                    Logger::getInstance().logError("Wrong input format of scalar");
                    throw std::runtime_error("Неверный формат ввода скаляра");
                }
                if (m == "A") {
                    v_of_LAaG matC = (*matA) * x;
                    std::cout << matC<<'\n';
                    Logger::getInstance().logInfo("Multiplied matrix A by scalar");
                }
                else if (m == "B") {
                    v_of_LAaG matC = (*matB) * x;
                    std::cout << matC<<'\n';
                    Logger::getInstance().logInfo("Multiplied matrix B by scalar");
                }
                else {
                    Logger::getInstance().logError("Invalid matrix name");
                    throw std::runtime_error("Неверное имя матрицы. Доступны только матрицы A и B");
                }
            }
            catch (std::exception& e) {
                std::cerr<<"Ошибка: " << e.what() << std::endl;
                Logger::getInstance().logError(std::string(e.what()));
            }
        }
        else if (cmd == "transpose") {
            try {
                std::string m;
                ss>>m;
                if (m == "A") {
                    *matA = matA->transpose();
                    std::cout<<*matA<<'\n';
                    Logger::getInstance().logInfo("Transposed matrix A");
                }
                else if (m == "B") {
                    *matB = matB->transpose();
                    std::cout<<*matB<<'\n';
                    Logger::getInstance().logInfo("Transposed matrix B");
                }
                else {
                    Logger::getInstance().logError("Invalid matrix name");
                    throw std::runtime_error("Неверное имя матрицы. Доступны только матрицы A и B");
                }
            }
            catch (std::exception& e) {
                std::cerr<<"Ошибка: " << e.what() << std::endl;
                Logger::getInstance().logError(std::string(e.what()));
            }
        }
        else if (cmd == "rref") {
            try {
                std::string m;
                ss>>m;
                if (m == "A") {
                    *matA = matA->rref();
                    std::cout<<*matA<<'\n';
                    Logger::getInstance().logInfo("Transformed matrix A into RREF");
                }
                else if (m == "B") {
                    *matB = matB->rref();
                    std::cout<<*matB<<'\n';
                    Logger::getInstance().logInfo("Transformed matrix B into RREF");
                }
                else {
                    Logger::getInstance().logError("Invalid matrix name");
                    throw std::runtime_error("Неверное имя матрицы. Доступны только матрицы A и B");
                }
            }
            catch (std::exception& e) {
                std::cerr<<"Ошибка: " << e.what() << std::endl;
                Logger::getInstance().logError(std::string(e.what()));
            }
        }
        else if (cmd == "det") {
            try {
                std::string m;
                ss>>m;
                if (m == "A") {
                    std::cout<<matA->det()<<'\n';
                    Logger::getInstance().logInfo("Found determinant of matrix A");
                }
                else if (m == "B") {
                    std::cout<<matB->det()<<'\n';
                    Logger::getInstance().logInfo("Found determinant of matrix B");
                }
                else {
                    Logger::getInstance().logError("Invalid matrix name");
                    throw std::runtime_error("Неверное имя матрицы. Доступны только матрицы A и B");
                }
            }
            catch (std::exception& e) {
                std::cerr<<"Ошибка: " << e.what() << std::endl;
                Logger::getInstance().logError(std::string(e.what()));
            }
        }
        else if (cmd == "inv") {
            try {
                std::string m;
                ss>>m;
                if (m == "A") {
                    *matA = matA->inverse();
                    std::cout<<*matA<<'\n';
                    Logger::getInstance().logInfo("Found inverse of matrix A");
                }
                else if (m == "B") {
                    *matB = matB->inverse();
                    std::cout<<*matB<<'\n';
                    Logger::getInstance().logInfo("Found inverse of matrix B");
                }
                else {
                    Logger::getInstance().logError("Invalid matrix name");
                    throw std::runtime_error("Неверное имя матрицы. Доступны только матрицы A и B");
                }
            }
            catch (std::exception& e) {
                std::cerr<<"Ошибка: " << e.what() << std::endl;
                Logger::getInstance().logError(std::string(e.what()));
            }
        }
        else if (cmd == "rank") {
            try {
                std::string m;
                ss>>m;
                if (m == "A") {
                    std::cout<<matA->rank()<<'\n';
                    Logger::getInstance().logInfo("Found rank of matrix A");
                }
                else if (m == "B") {
                    std::cout<<matB->rank()<<'\n';
                    Logger::getInstance().logInfo("Found rank of matrix B");
                }
                else {
                    Logger::getInstance().logError("Invalid matrix name");
                    throw std::runtime_error("Неверное имя матрицы. Доступны только матрицы A и B");
                }
            }
            catch (std::exception& e) {
                std::cerr<<"Ошибка: " << e.what() << std::endl;
                Logger::getInstance().logError(std::string(e.what()));
            }
        }
        else {

        }
    }
    void processInput(const std::string& fullcmd) {
        auto res = Konverter::CommandFetch(fullcmd);
        if (std::holds_alternative<Command>(res)) {
            Command cmd = std::get<Command>(res);
        }
        else if (std::holds_alternative<int>(res)) {
            int x = std::get<int>(res);
        }
        else {
            std::cout<<"Неизвестная команда";
        }
    }

public:
    CalcInterface() {
        matA = std::make_unique<v_of_LAaG>(3,3);
        matB = std::make_unique<v_of_LAaG>(3,3);
        Logger::getInstance().logInfo("Matrices A and B created");
    }
    void run() {
        Logger::getInstance().logInfo("Start");
        std::cout<<"Добро пожаловать в Fancy Matrix Calculator!\n"
                   " Для просмотра списка возможных команд введите help.\n"
                   "Введите команду и нажмите Enter"<<'\n';
        std::string cmd;
        while (true) {
            std::getline(std::cin, cmd);
            if (cmd == "exit") {
                break;
            }
            processInput(cmd);
        }
    }
    ~CalcInterface() {}
};

