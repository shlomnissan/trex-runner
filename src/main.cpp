// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#define SDL_MAIN_HANDLED

#include <memory>

#include "core/game.h"
#include "game/main_stage.h"
#include "game/shared.h"

int main() {
    Game game {"Trex Runner!", kWindowWidth, kWindowHeight};

    // load assets
    game.LoadAudio("sfx_achievement.wav", "achievement");
    game.LoadAudio("sfx_hit.wav", "hit");
    game.LoadAudio("sfx_jump.wav", "jump");
    game.LoadSpritesheet(
        "spritesheet",
        {"spritesheet.png", "spritesheet.json"}
    );

    // start game
    game.Start(std::make_unique<MainStage>());

    return 0;
}