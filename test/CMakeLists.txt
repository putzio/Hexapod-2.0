cmake_minimum_required(VERSION 3.15)

project(try_googletest
    VERSION 1.0
    DESCRIPTION "test_googletest"
    LANGUAGES CXX
)

include(CTest)

add_subdirectory(test_native)

