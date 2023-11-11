// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "horizon.h"

#include "game/shared.h"

constexpr int kBumpThreshold = 5;
constexpr int kGroundWidth = 600;

Horizon::Horizon() {
    const auto y_pos = kWindowHeight - 23;

    sprites_.emplace_back(std::make_unique<Sprite>(
        "spritesheet", "ground_0", Vector2 {.x = 0, .y = y_pos}
    ));

    sprites_.emplace_back(std::make_unique<Sprite>(
        "spritesheet", "ground_1", Vector2 {.x = 600, .y = y_pos}
    ));
}

auto Horizon::UpdateWithSpeed(const double dt, const double speed) -> void {
    if (sprites_.back()->x <= 0) {
        sprites_.back()->x = 0;
        sprites_.front()->x = kGroundWidth;

        sprites_.front()->SetFrame(
            ShouldRenderBumps()
                ? "ground_1"
                : "ground_0"
        );

        swap(sprites_.front(), sprites_.back());
    }

    const auto rate = speed * (kFPS / 1000) * dt;
    sprites_.front()->x -= rate;
    sprites_.back()->x -= rate;
}

auto Horizon::ShouldRenderBumps() -> bool {
    return rand_() > kBumpThreshold;
}