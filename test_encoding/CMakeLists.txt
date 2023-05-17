cmake_minimum_required(VERSION 3.25)
project(test_encoding)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(test_encoding
        coding.cpp
        coding.h MainWindow.h test_result.cpp)
