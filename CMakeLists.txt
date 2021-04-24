cmake_minimum_required(VERSION 3.17)
project(trex_runner C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

SET(INCLUDE
        sys/window.h
        sys/input.h
        sys/graphics.h
        sys/sounds.h
        sys/utilities.h
        objects/t_rex.h
        objects/horizon.h
        objects/horizon_line.h
        objects/obstacle.h
        objects/clouds.h
        globals.h
        spritesheet.h
        game.h
)

set(SOURCE
        sys/window.c
        sys/input.c
        sys/graphics.c
        sys/sounds.c
        sys/utilities.c
        objects/t_rex.c
        objects/horizon.c
        objects/horizon_line.c
        objects/obstacle.c
        objects/clouds.c
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