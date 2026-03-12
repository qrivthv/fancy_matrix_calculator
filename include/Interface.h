
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
#include <Drobilnik.h>

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
    void clear_buffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    void processMatCmd(Command cmd) {
        try {
            switch (cmd) {
                case Command::Determinant: {
                    std::cout<<matA->det()<<'\n';
                    Logger::getInstance().logInfo("Found determinant of matrix");
                    break;
                }
                    case Command::Rank:{
                    std::cout<<matA->rank()<<'\n';
                    Logger::getInstance().logInfo("Found rank of matrix");
                    break;
                    }
                case Command::Inverse: {
                    std::cout<<matA->inverse()<<'\n';
                    Logger::getInstance().logInfo("Found inverse of matrix");
                    break;
                }
                case Command::Transpose: {
                    std::cout<<matA->transpose()<<'\n';
                    Logger::getInstance().logInfo("Transposed matrix");
                    break;
                }
                case Command::Trace: {
                    std::cout<<matA->trace()<<'\n';
                    Logger::getInstance().logInfo("Found trace of matrix");
                    break;
                }
                case Command::Identity:{
                    std::cout<<"Введите размеры желаемой матрицы:"<<'\n';
                    int r;
                    std::cin>>r;
                    matA = std::make_unique<Identity>(r);
                    std::cout<<*matA<<'\n';
                    break;
                }
                case Command::Sum: {
                    std::cout<<*matA+*matB<<'\n';
                    break;
                }
                case Command::Multiplication: {
                    std::cout<<(*matA)*(*matB)<<'\n';
                    break;
                }
                case Command::Swap: {
                    swap(*matA, *matB);
                    std::cout<<*matA<<'\n';
                    std::cout<<*matB<<'\n';
                    break;
                }
                case Command::Difference:{
                    std::cout<<*matA-*matB<<'\n';
                    break;
                }
                case Command::CancelOperation: {
                    std::cout<<"Отменено."<<'\n';
                    break;
                }
                default:
                    throw std::runtime_error("cmd not done");
            }
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            Logger::getInstance().logError(e.what());
        }
    }
    std::unique_ptr<v_of_LAaG> enterMatrix(int rows=1, int cols=1,bool neededInput = 1){
        try {
            if (neededInput) {
                std::cout<<"Введите размеры матрицы:"<<'\n';
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
            }
            std::cout<<"Введите матрицу:"<<'\n';
            auto mat = std::make_unique<v_of_LAaG>(rows, cols);
            for (size_t i = 0; i < rows; i++) {
                for (size_t j = 0; j < cols; j++) {
                    std::cin>>(*mat)[i][j];
                }
            }
            clear_buffer();
            return mat;

        }
        catch (std::exception& e) {
            std::cerr<<"Ошибка: " << e.what() << std::endl;
            Logger::getInstance().logError(std::string(e.what()));
        }
    }
    void processCmd(const std::string& fullCmd) {
        std::stringstream ss(fullCmd);
        std::string cmd;
        ss >> cmd;
        if (cmd == "help") {
            std::cout<<"тут типа описание всех команд"<< std::endl; //TODO дописать вот это
            Logger::getInstance().logInfo("Cmd: help"); //TODO дописать все логи
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

    }
    void processInput(const std::string& fullcmd) {

        std::stringstream ss(fullcmd);
        std::string s;
        ss>>s;
        if (s == "enter") {
            processCmd(fullcmd);
            return;
        }
        else if (s == "print") {
            processCmd(fullcmd);
            return;
        }
        else if (s=="help") {
            processCmd(fullcmd);
            return;
        }
        else if (s == "exit") {
            return;
        }
        else if (s.empty()) {
            return;
        }

        auto res = Konverter::CommandFetch(s);
        if (std::holds_alternative<Command>(res)) {
            Command cmd = std::get<Command>(res);
            processMatCmd(cmd);
        }
        else if (std::holds_alternative<int>(res)) {
            int x = std::get<int>(res);
        }
        else {
            std::cout<<"Unknown cmd"<<std::endl;
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
                   "Введите 2 матрицы для работы:"<<'\n';

        matA = enterMatrix();
        matB = enterMatrix();
        std::cout<<"Вы успешно ввели матрицы!"<<'\n';

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

