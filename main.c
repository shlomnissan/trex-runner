// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shloi Nissan (shlomi@betamark.com)

#include <stdlib.h>

#include "game.h"
#include "globals.h"
#include "sdl/window.h"
#include "sdl/graphics.h"
#include "sdl/sounds.h"

int main() {
    InitializeWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    LoadTexture("assets/textures/spritesheet.png");

    srand(GetTicks());

    InitGame();
    StartGameLoop(RunGame);

    DeinitWindow();
    DestroyTextures();
    DestroyGame();
    return 0;
}