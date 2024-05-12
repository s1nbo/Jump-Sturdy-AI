cmake_minimum_required(VERSION 3.6)

project(JumpSturdy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g3 -Wall -Wextra -pedantic")
set(CMAKE_CPP_COMPILER g++)

add_executable(jumpsturdy main.cpp ai.cpp board.cpp moves.cpp connect.cpp)
target_include_directories(jumpsturdy PRIVATE ${CMAKE_SOURCE_DIR})