cmake_minimum_required(VERSION 3.13)

project(course)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(course   final_project/main.cpp
                        final_project/condition_parser.h
        final_project/condition_parser.cpp
                        final_project/condition_parser_test.cpp
                        final_project/token.cpp
                        final_project/token.h
                        final_project/database.h final_project/date.h final_project/node.h final_project/database.cpp final_project/node.cpp final_project/comparisons.h final_project/includes.h final_project/date.cpp)

