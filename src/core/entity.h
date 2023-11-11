// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <memory>
#include <vector>

#include "core/types.h"
#include "core/keyboard.h"
#include "core/sprite.h"

class Entity {
public:
    virtual auto Update(const double dt, const Keyboard& keyboard) -> void;

    auto HasCollision(const Entity& entity) const -> bool;

    const auto& sprites() const { return sprites_; }

    virtual ~Entity() = default;

protected:
    std::vector<std::unique_ptr<Sprite>> sprites_;

    auto GetCollisionRects(const Entity& entity) const -> std::vector<Frame>;
};