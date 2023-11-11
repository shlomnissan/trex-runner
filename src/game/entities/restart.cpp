// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "restart.h"

#include "core/types.h"
#include "game/shared.h"

Restart::Restart(Events* events) : Entity(events) {
    sprites_.emplace_back(std::make_unique<Sprite>(
        "spritesheet",
        "restart_button",
        Vector2 {0.0, kWindowHeight >> 1}
    ));
    
    sprites_.emplace_back(std::make_unique<Sprite>(
        "spritesheet",
        "restart_text",
        Vector2 {0.0, (kWindowHeight - 50) >> 1}
    ));

    sprites_.front()->x = (kWindowWidth - sprites_.front()->width) >> 1;
    sprites_.back()->x = (kWindowWidth - sprites_.back()->width) >> 1;
}