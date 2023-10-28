cmake_minimum_required(VERSION 3.0)
project(project_4_4)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(project_4_4 main.cpp)
target_link_libraries(project_4_4 sfml-system sfml-window sfml-graphics)
