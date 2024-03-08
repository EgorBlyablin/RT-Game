cmake_minimum_required(VERSION 3.0.0)
project(RTetris VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(RTetris main.cpp)

target_link_libraries(RTetris sfml-graphics sfml-window sfml-system)