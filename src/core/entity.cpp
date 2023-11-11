// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "entity.h"

#include "core/resource_manager.h"
#include "core/sprite_animated.h"

auto Entity::Update(const double dt, const Keyboard &keyboard) -> void {
    for (const auto& sprite : sprites_) {
        if (auto animated = dynamic_cast<SpriteAnimated*>(sprite.get())) {
            animated->UpdateFrame();
        }
    }
}

auto Entity::GetCollisionRects(const Entity& entity) const -> std::vector<Frame> {
    std::vector<Frame> output;
    for (const auto& sprite : entity.sprites()) {
        const auto& ss = ResourceManager::GetSpritesheet(sprite->spritesheet_id());
        const auto& collision_rects = ss.GetCollisionFrames(sprite->frame_id());
        for (const auto& rect : collision_rects) {
            output.emplace_back(Frame{
                rect.x + static_cast<int>(sprite->x),
                rect.y + static_cast<int>(sprite->y),
                rect.width,
                rect.height
            });
        }
    }
    return output;
}

auto Entity::HasCollision(const Entity &entity) const -> bool {
    auto this_rects = GetCollisionRects(*this);
    for (const auto& rect : this_rects) {
        auto other_rects = GetCollisionRects(entity);
        for (const auto& other_rect : other_rects) {
            if (rect.HasCollision(other_rect)) {
                return true;
            }
        }
    }
    return false;
}