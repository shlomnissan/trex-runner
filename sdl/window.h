// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUN_WINDOW_H
#define TREX_RUN_WINDOW_H

#include <stdbool.h>

#include <SDL2/SDL.h>

bool InitializeWindow(char* title, uint32_t width, uint32_t height);

SDL_Renderer* GetRenderer();

void DeinitWindow();

void StartGameLoop(void (*game_loop)());

uint32_t GetTicks();

#endif  // TREX_RUN_WINDOW_H
