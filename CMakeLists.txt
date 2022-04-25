cmake_minimum_required(VERSION 3.14)

project(raygun-test LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_exectuable(raygun-tests
        Fade.cpp
        Fade.h
        Switch.cpp
        Switch.h
        test/main.cpp
)