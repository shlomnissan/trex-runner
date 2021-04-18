cmake_minimum_required(VERSION 3.17)
project(trex_runner C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

SET(INCLUDE
        sdl/window.h
        sdl/input.h
        sdl/graphics.h
        assets/spritesheet.h
        game/horizon_line.h
        game/t_rex.h
        game.h
        )

set(SOURCE
        sdl/window.c
        sdl/input.c
        sdl/graphics.c
        assets/spritesheet.c
        game/horizon_line.c
        game/t_rex.c
        game.c
        )

add_executable(${PROJECT_NAME} main.c ${INCLUDE} ${SOURCE})

target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
)