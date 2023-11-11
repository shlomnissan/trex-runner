// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <array>

#include "core/entity.h"
#include "core/keyboard.h"
#include "core/random.h"

class Clouds : public Entity {
public:
    Clouds(Events* events);

    auto UpdateWithSpeed(const double dt, const double speed) -> void;

private:
    static constexpr int kMaxClouds = 6;

    int cloud_count_ = 0;
    int last_cloud_idx_ = -1;

    std::array<int, kMaxClouds> cloud_gaps_ = {0};

    Random rand_vertical_range_ {30, 70};
    Random rand_cloud_gap_range_ {100, 400};

    auto AddCloud() -> void;
    auto ShouldAddAnohterCloud() -> bool;
};