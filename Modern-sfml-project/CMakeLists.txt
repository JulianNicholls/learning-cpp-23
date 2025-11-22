cmake_minimum_required(VERSION 3.31)

project(breakout VERSION 1.7)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME}
    breakout.cpp
    game.cpp
    entity_manager.cpp
    background.cpp
    ball.cpp
    entity.cpp
    paddle.cpp
    brick.cpp
    interactions.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
