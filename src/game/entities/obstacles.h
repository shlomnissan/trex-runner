// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <array>

#include "core/entity.h"
#include "core/random.h"

class Obstacles : public Entity {
public:
    auto UpdateWithSpeed(const double dt, const double speed) -> void;
    auto Reset() -> void;

private:
    Random rand_obstacle_type_range_ {0, 5};

    std::array<int, 2> obstacle_gaps_ {0};

    auto AddObstacle(const double speed) -> void;
    auto GetGap(const int width, const double speed) const -> int;
    auto ShouldAddObstacles() -> bool;
};