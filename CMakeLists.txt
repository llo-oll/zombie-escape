cmake_minimum_required(VERSION 3.12)
project(zombie_escape)

set(CMAKE_CXX_STANDARD 11)

add_executable(zombierun main.cpp)

include_directories(game)

add_subdirectory(game)
add_subdirectory(tests)

target_link_libraries(zombierun game)