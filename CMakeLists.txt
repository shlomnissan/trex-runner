cmake_minimum_required(VERSION 3.19)
project(trex_runner C)

set(CMAKE_C_STANDARD 99)

include_directories(${PROJECT_SOURCE_DIR})

if (NOT SDL_FOUND OR NOT SDLIMAGE_FOUND OR NOT SDLMIXER_FOUND)
    include(FetchContent)

    if (NOT SDL_FOUND)
        FetchContent_Declare(
            sdl
            GIT_REPOSITORY https://github.com/libsdl-org/SDL
            GIT_TAG 8d2cb15
            GIT_PROGRESS TRUE
        )
        if(NOT sdl_POPULATED)
            FetchContent_Populate(sdl)
            add_subdirectory(${sdl_SOURCE_DIR} ${sdl_BINARY_DIR})
        endif()
    endif()

    if (NOT SDLIMAGE_FOUND)
        FetchContent_Declare(
            sdlimage
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
            GIT_TAG 71229fe
            GIT_PROGRESS TRUE
        )
        if(NOT sdlimage_POPULATED)
            FetchContent_Populate(sdlimage)
            add_subdirectory(${sdlimage_SOURCE_DIR} ${sdlimage_BINARY_DIR})
        endif()
    endif()

    if (NOT SDLMIXER_FOUND)
        FetchContent_Declare(
            sdlmixer
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
            GIT_TAG 267a198f 
            GIT_PROGRESS TRUE
        )

        if(NOT sdlmixer_POPULATED)
            FetchContent_Populate(sdlmixer)
            add_subdirectory(${sdlmixer_SOURCE_DIR} ${sdlmixer_BINARY_DIR})
        endif()
    endif()
endif()

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

add_executable(trex main.c ${INCLUDE} ${SOURCE})

target_link_libraries(
    trex 
    SDL2
    SDL2_image
    SDL2_mixer
    m
)
