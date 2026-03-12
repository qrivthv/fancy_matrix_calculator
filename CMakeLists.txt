    cmake_minimum_required(VERSION 4.0)
    project(fancy_calculator)

    add_subdirectory(tests)
    set(CMAKE_CXX_STANDARD 26)

    add_executable(
            fancy_calculator main.cpp
            include/victim_of_LAaG.h
            include/Drobilnik.h
            include/Konverter.h
            include/Ochepyatka.h
            include/table_of_ranks.h
            include/Interface.h
    )