// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shloi Nissan (shlomi@betamark.com)

#include <stdlib.h>

#include "sdl/window.h"
#include "sdl/graphics.h"

#include "game.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 150
#define WINDOW_TITLE "T-Rex Runner"

int main() {
    srand(GetTicks());

    InitializeWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    LoadTexture("assets/spritesheet.png");

    InitGame();
    StartGameLoop(RunGame);

    DeinitWindow();
    DestroyTextures();
    return 0;
}