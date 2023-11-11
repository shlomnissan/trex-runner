// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "clouds.h"

#include "core/entity.h"
#include "game/shared.h"

const auto kCloudWidth = 46;
const auto kCloudSpeed = 0.2;

Clouds::Clouds() {
    AddCloud();
}

auto Clouds::AddCloud() -> void {
    ++cloud_count_;
    last_cloud_idx_ = (last_cloud_idx_ + 1) % kMaxClouds;
    
    auto cloud = std::make_unique<Sprite>(
        "spritesheet",
        "cloud",
        Vector2 {
            .x = kWindowWidth,
            .y = static_cast<double>(rand_vertical_range_()),
        }
    );

    last_cloud_idx_ >= sprites_.size()
        ? sprites_.emplace_back(std::move(cloud))
        : sprites_[last_cloud_idx_] = std::move(cloud);

    cloud_gaps_[last_cloud_idx_] = rand_cloud_gap_range_();
}

auto Clouds::UpdateWithSpeed(const double dt, const double speed) -> void {
    auto rate = ceil(kCloudSpeed / 1000 * dt * speed);
    
    for (auto& sprite : sprites_) {
        if (sprite == nullptr) continue;
        
        sprite->x -= rate;

        // delete cloud when it's out of the frame
        if (sprite->x < -kCloudWidth) {
            sprite.reset(nullptr);
            --cloud_count_;
        }
    }

    if (ShouldAddAnohterCloud()) {
        AddCloud();
    }
}

auto Clouds::ShouldAddAnohterCloud() -> bool {
    if (cloud_count_ == kMaxClouds) {
        return false;
    }
    const auto gap =  cloud_gaps_[last_cloud_idx_];
    const auto last_cloud_pos_x = sprites_[last_cloud_idx_]->x;
    return (kWindowWidth - last_cloud_pos_x) > gap;
}