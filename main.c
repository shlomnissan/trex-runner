// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shloi Nissan (shlomi@betamark.com)

#include <stdlib.h>

#include "game.h"
#include "globals.h"
#include "sys/window.h"
#include "sys/graphics.h"
#include "sys/sounds.h"

bool Initialize() {
    return InitializeWindow(
        WINDOW_TITLE,
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );
}

bool LoadAssets() {
    if (LoadTexture("assets/textures/spritesheet.png") == -1) {
        return false;
    }
    LoadSoundEffect("assets/sounds/sfx-hit.wav");
    LoadSoundEffect("assets/sounds/sfx-press.wav");
    LoadSoundEffect("assets/sounds/sfx-reached.wav");
    return true;
}

void StartGame() {
    srand(GetTicks());
    InitGame();
    StartGameLoop(RunGame);
}

void FreeResources() {
    FreeTextures();
    FreeSoundEffects();
    DestroyGame();
    DeinitMixer();
    DeinitWindow();
}

int main() {
    if (!Initialize() || !LoadAssets()) return -1;

    StartGame();

    FreeResources();

    return 0;
}