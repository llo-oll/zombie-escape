cmake_minimum_required(VERSION 3.12)
project(zombie_escape)

set(CMAKE_CXX_STANDARD 11)

add_executable(zombie_escape main.cpp)

include_directories(gameset)

add_subdirectory(gameset)
add_subdirectory(tests)

target_link_libraries(zombie_escape gameset)


#set(CMAKE_CXX_FLAGS "-lncurses")
#is this a more portable way of linking curses than the line above?
set(CURSES_NEED_CURSES, TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(zombie_escape ${CURSES_LIBRARIES})