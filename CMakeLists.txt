cmake_minimum_required(VERSION 3.22)

project(trex_runner)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt REQUIRED)
find_package(RapidJSON REQUIRED)
find_package(SDL2 REQUIRED)

set(CORE_SOURCES
    libs/stb_image.h
    src/core/audio.cpp
    src/core/audio.h
    src/core/entity.cpp
    src/core/entity.h
    src/core/events.cpp
    src/core/events.h
    src/core/game.cpp
    src/core/game.h
    src/core/image.cpp
    src/core/image.h
    src/core/random.h
    src/core/resource_manager.cpp
    src/core/resource_manager.h
    src/core/sprite.h
    src/core/sprite_animated.cpp
    src/core/sprite_animated.h
    src/core/spritesheet.cpp
    src/core/spritesheet.h
    src/core/stage.h
    src/core/timer.h
    src/core/types.h
    src/core/window.cpp
    src/core/window.h
)

set(GAME_SOURCES
    src/game/entities/clouds.cpp
    src/game/entities/clouds.h
    src/game/entities/horizon.cpp
    src/game/entities/horizon.h
    src/game/entities/obstacles.cpp
    src/game/entities/obstacles.h
    src/game/entities/restart.cpp
    src/game/entities/restart.h
    src/game/entities/score.cpp
    src/game/entities/score.h
    src/game/entities/trex.cpp
    src/game/entities/trex.h
    src/game/main_stage.cpp
    src/game/main_stage.h
    src/game/shared.h
    src/main.cpp
)

FILE(GLOB ASSETS ${CMAKE_SOURCE_DIR}/assets/*)
FILE(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

add_executable(trex_runner ${CORE_SOURCES} ${GAME_SOURCES})

target_include_directories(trex_runner PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/libs
)

target_link_libraries(trex_runner PRIVATE fmt::fmt rapidjson SDL2::SDL2)