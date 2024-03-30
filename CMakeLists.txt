cmake_minimum_required(VERSION 3.22)
project(RTetris)

include(FetchContent)

# SFML Fetch
FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "2.5.1"
    GIT_PROGRESS ON
)
FetchContent_MakeAvailable(sfml)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_REQUIRED ON)

add_executable(RTetris main.cpp)
add_subdirectory(UI)

configure_file(assets/Fonts/Arial.ttf assets/Fonts/Arial.ttf COPYONLY)

target_link_libraries(RTetris
    PUBLIC
    sfml-audio
    sfml-graphics
    sfml-window
    sfml-system

    UI
)
target_compile_options(RTetris PRIVATE -Wall -Wextra -pedantic)