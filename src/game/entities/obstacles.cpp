// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "obstacles.h"

#include <memory>
#include <string>

#include "core/types.h"
#include "game/shared.h"

const auto kGroundPosition = kWindowHeight - 23;
const auto kVerticalOffset = 13;
const auto kMinGap = 120;
const auto kMinGapCoefficient = 0.6;
const auto kMaxGapCoefficient = 1.5;

const std::array<std::string, 6> kObstacles {
    "obstacle_small_0",
    "obstacle_small_1",
    "obstacle_small_2",
    "obstacle_large_0",
    "obstacle_large_1",
    "obstacle_large_2"
};

auto Obstacles::UpdateWithSpeed(const double dt, const double speed) -> void {
    const auto rate = speed * (kFPS / 1000) * dt;
    for (const auto& sprite : sprites_) {
        if (sprite == nullptr) continue;
        sprite->x -= rate;
    }

    if (ShouldAddObstacles()) {
        AddObstacle(speed);
    }
}

auto Obstacles::AddObstacle(const double speed) -> void {
    auto obstacle = std::make_unique<Sprite>(
        "spritesheet",
        kObstacles[rand_obstacle_type_range_()],
        Vector2 {
            .x = kWindowWidth,
            .y = 0
        }
    );

    obstacle->y = kGroundPosition - obstacle->height + kVerticalOffset;
    
    // there can only be two obstacles on the screen at any given time
    const auto max_obstacles = 2;
    if (sprites_.size() < max_obstacles) {
        obstacle_gaps_[sprites_.size()] = GetGap(obstacle->width, speed);
        sprites_.emplace_back(std::move(obstacle));
    } else {
        obstacle_gaps_.front() = GetGap(obstacle->width, speed);
        sprites_.front() = std::move(obstacle);

        std::swap(sprites_.front(), sprites_.back());
        std::swap(obstacle_gaps_.front(), obstacle_gaps_.back());
    }
}

auto Obstacles::GetGap(const int width, const double speed) const -> int {
    const auto min_gap = width * speed + kMinGap * kMinGapCoefficient;
    const auto max_gap = min_gap * kMaxGapCoefficient;
    return Random {
        static_cast<int>(min_gap),
        static_cast<int>(max_gap)
    }();
}

auto Obstacles::ShouldAddObstacles() -> bool {
    if (sprites_.empty()) {
        return true;
    }

    // if there's more than one obstacles, make sure the first one is off the
    // screen before considering adding another
    if (sprites_.size() > 1 && sprites_.front()->x > -sprites_.front()->width) {
        return false;
    }

    auto last_idx = sprites_.size() - 1;
    const auto& obstacle = sprites_[last_idx];
    return obstacle->x + obstacle->width + obstacle_gaps_[last_idx] < kWindowWidth;
}

auto Obstacles::Reset() -> void {
    sprites_.clear();
}