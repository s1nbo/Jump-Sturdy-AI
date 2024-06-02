cmake_minimum_required(VERSION 3.6)

project(JumpSturdy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g3 -Wall -Wextra -pedantic")
set(CMAKE_CPP_COMPILER g++)

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(jumpsturdy main.cpp tt.cpp ai.cpp board.cpp moves.cpp connect.cpp test.cpp )
target_include_directories(jumpsturdy PRIVATE ${CMAKE_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(jumpsturdy ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)
