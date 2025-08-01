cmake_minimum_required(VERSION 3.25)
project(langton)

set(CMAKE_CXX_STANDARD 11)

add_executable(langton main.cpp ant.cpp ant.h queen.cpp queen.h graphics.h graphics.cpp Breeder.cpp Breeder.h Soldier.cpp Soldier.h events.cpp events.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio REQUIRED)

include_directories(c:/SFML/include)
target_link_libraries(langton sfml-system sfml-window sfml-graphics sfml-audio)