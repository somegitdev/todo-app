cmake_minimum_required(VERSION 3.10)

project(todo_app VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)

add_executable(todo_app
    src/main.cpp
    src/Task.cpp
)