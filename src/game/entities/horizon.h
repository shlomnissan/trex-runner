// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "core/entity.h"
#include "core/random.h"

class Horizon : public Entity {
public:
    Horizon();

    auto UpdateWithSpeed(const double dt, const double speed) -> void;

private:
    Random rand_ {0, 10};

    auto ShouldRenderBumps() -> bool;
};