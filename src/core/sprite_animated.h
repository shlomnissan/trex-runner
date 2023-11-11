// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "sprite.h"
#include "timer.h"
#include "types.h"

class SpriteAnimated : public Sprite {
public:
    using vec_string = std::vector<std::string>;

    SpriteAnimated(std::string_view spritesheet_id, Vector2 pos, int fps);

    auto frame_id() const -> std::string override;
    auto curr_animation() const { return curr_animation_; }

    auto AddAnimation(const std::string& name, const vec_string& frames) -> void;
    auto SetAnimation(std::string_view name) -> void;
    auto UpdateFrame() -> void;

private:
    int curr_frame_ {0};
    int fps_ {0};
    
    std::string curr_animation_;
    std::unordered_map<std::string, vec_string> animations_;

    Timer timer_;
};

struct SpriteAnimatedError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};