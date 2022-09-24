// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <SDL.h>

#include "input.h"

bool keyboard[256] = {false};

void (*key_up_callback)(char key) = NULL;

void PollEvents(void (*on_quit)()) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) on_quit();

        if (event.type == SDL_KEYDOWN) {
            const uint8_t key = event.key.keysym.sym;
            keyboard[key] = true;
        }
        if (event.type == SDL_KEYUP) {
            const uint8_t key = event.key.keysym.sym;
            keyboard[key] = false;
            if (key_up_callback != NULL) {
                key_up_callback(key);
            }
        }
    }
}

void SetOnKeyUp(void (*on_key_up)(char key)) {
    key_up_callback = on_key_up;
}

bool IsKeyDown(char key) {
    return keyboard[key];
}