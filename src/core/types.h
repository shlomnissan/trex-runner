// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <string>
#include <string_view>

struct Vector2 {
    double x;
    double y;
};

struct Frame {
    int x;
    int y;
    int width;
    int height;

    auto HasCollision(const Frame& rhs) const {
        if (std::max(x, rhs.x) > std::min(x + width, rhs.x + rhs.width)) {
            return false;
        }

        if (std::max(y, rhs.y) > std::min(y + height, rhs.y + rhs.height)) {
            return false;
        }

        return true;
    }
};