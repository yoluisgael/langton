cmake_minimum_required(VERSION 3.25)
project(langton)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
    src/main.cpp
    src/Ant.cpp
    src/Queen.cpp
    src/Breeder.cpp
    src/Soldier.cpp
    src/events.cpp
    src/graphics.cpp
)

add_executable(langton ${SOURCES})

target_include_directories(langton PRIVATE include)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(langton sfml-system sfml-window sfml-graphics sfml-audio)
