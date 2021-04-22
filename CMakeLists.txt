cmake_minimum_required(VERSION 3.17)
project(trex_runner C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

SET(INCLUDE
        sdl/window.h
        sdl/input.h
        sdl/graphics.h
        sdl/sounds.h
        actors/t_rex.h
        actors/horizon.h
        actors/horizon_line.h
        actors/clouds.h
        globals.h
        spritesheet.h
        game.h
)

set(SOURCE
        sdl/window.c
        sdl/input.c
        sdl/graphics.c
        sdl/sounds.c
        actors/t_rex.c
        actors/horizon.c
        actors/horizon_line.c
        actors/clouds.c
        spritesheet.c
        game.c
 )

add_executable(${PROJECT_NAME} main.c ${INCLUDE} ${SOURCE})

target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_MIXER_LIBRARY}
    m
)