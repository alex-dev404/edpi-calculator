cmake_minimum_required(VERSION 3.0)

project(Sensi_Calculator)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Sensi_Calculator main.cpp)
target_link_libraries(Sensi_Calculator PRIVATE sfml-graphics sfml-window sfml-system)
