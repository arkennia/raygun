cmake_minimum_required(VERSION 3.14)

project(raygun_test LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(raygun_tests
        Fade.cpp
        Fade.h
        Switch.cpp
        Switch.h
        test/main.cpp
        test/Arduino_mock.h
        test/Arduino_mock.c
)

target_compile_options(raygun_tests PRIVATE -g -pipe -Wall -W -Wextra -pedantic
        -Wno-unused-parameter -Wno-old-style-cast -fno-plt -fwrapv -DTESTING)