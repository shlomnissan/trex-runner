// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

#include "core/audio.h"
#include "core/keyboard.h"
#include "core/spritesheet.h"
#include "core/stage.h"
#include "core/window.h"

#define DRAW_COLLISION_FRAMES 0

class Game {
public:
    Game(std::string_view title, int width, int height);

    auto LoadAudio(std::string_view path, std::string_view id) -> void;
    auto LoadSpritesheet(const std::string& id, const SpritesheetFiles& files) const -> void;
    auto Start(std::unique_ptr<Stage> scene) -> void;

private:
    bool running_ {true};
    int width_ {0};
    int height_ {0};

    std::unique_ptr<Stage> curr_stage_ {nullptr};

    Window window_;
    Keyboard keyboard_;
    Audio audio_;

    auto SetScene(std::unique_ptr<Stage> scene) -> void;
    auto DrawSprite(const Sprite* sprite) -> void;
};