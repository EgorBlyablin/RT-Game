cmake_minimum_required(VERSION 3.0.0)
project(RTetris)

set(CMAKE_CXX_STANDARD 17)

add_executable(RTetris main.cpp)

add_subdirectory(Graphics)
add_subdirectory(UI)

configure_file(Fonts/Arial.ttf Fonts/Arial.ttf COPYONLY)

target_link_libraries(RTetris
    Graphics UI
    sfml-graphics sfml-window sfml-system)