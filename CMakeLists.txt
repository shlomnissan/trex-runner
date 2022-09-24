cmake_minimum_required(VERSION 3.17)
project(trex_runner C)

set(CMAKE_C_STANDARD 99)

include_directories(${PROJECT_SOURCE_DIR})

set(SDL2MIXER_OPUS false)

add_subdirectory(lib/SDL)
add_subdirectory(lib/SDL_image)
add_subdirectory(lib/SDL_mixer)

set(INCLUDE
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
    objects/game_over_panel.h
    objects/distance_meter.h
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
    objects/game_over_panel.c
    objects/distance_meter.c
    spritesheet.c
    game.c
)

add_executable(${PROJECT_NAME} main.c ${INCLUDE} ${SOURCE})

target_link_libraries(
    ${PROJECT_NAME}
    SDL2
    SDL2_image
    SDL2_mixer
    m
)