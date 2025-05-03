cmake_minimum_required(VERSION 3.28)
project(Connect_4)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Connect_4 game.cpp engine.cpp)
target_compile_features(Connect_4 PRIVATE cxx_std_17)
target_link_libraries(Connect_4 PRIVATE SFML::Graphics)