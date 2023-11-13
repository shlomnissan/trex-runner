// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <functional>

#include "core/entity.h"
#include "core/random.h"
#include "core/sprite_animated.h"

enum class TRexState {
    Idle,
    Running,
    Jumping,
    Ducking,
    Crashed
};

class TRex : public Entity {
public:
    TRex();

    auto Crash() -> void;
    auto Reset() -> void;
    auto Update(const double dt) -> void override;
    auto SetStartCallback(std::function<void()> callback) -> void;

private:
    bool duck_key_down_ {false};
    bool jump_key_down_ {false};

    bool reached_min_height_ {false};
    bool cancel_jump_ {false};
    bool did_start_game_ {false};
    int blink_time_ {0};
    double vertical_velocity_ {0.0};

    std::function<void()> start_callback_;

    TRexState state_ {TRexState::Idle};
    TRexState prev_state_ {TRexState::Running};
    Random blink_rand_{1000, 7000};

    auto Blink(const double dt, SpriteAnimated* sprite) -> void;
    auto RegisterKeys() -> void;
    auto HandleControls() -> void;
    auto ShortenJump() -> void;
    auto UpdateAnimation(SpriteAnimated* sprite) -> void;
    auto UpdateJump(const double dt, SpriteAnimated* sprite) -> void;
};