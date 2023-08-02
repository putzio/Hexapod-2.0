cmake_minimum_required(VERSION 3.15)

# project(try_googletest
#     VERSION 1.0
#     DESCRIPTION "test_googletest"
#     LANGUAGES CXX
# )

# include(CTest)
add_subdirectory(test_native)
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}-ut)



