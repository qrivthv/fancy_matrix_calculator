    cmake_minimum_required(VERSION 4.0)
    project(fancy_calculator)

    add_subdirectory(Germanic influence)
    add_subdirectory(matrix)

    set(CMAKE_CXX_STANDARD 26)

    add_executable(
            fancy_calculator main.cpp
    )