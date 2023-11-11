// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "sprite_animated.h"

#include <fmt/format.h>

SpriteAnimated::SpriteAnimated(std::string_view spritesheet_id, Vector2 pos, int fps)
  : Sprite(spritesheet_id, "", pos), fps_(fps) {}

auto SpriteAnimated::frame_id() const -> std::string {
    if (!animations_.contains(curr_animation_)) {
        throw SpriteAnimatedError {
            fmt::format(
                "Unable to get frame ID, the animation {} is undefined",
                curr_animation_
            )  
        };
    }
    return animations_.at(curr_animation_)[curr_frame_];
}

auto SpriteAnimated::AddAnimation(const std::string& name, const vec_string& frames) -> void {
    if (animations_.contains(name)) {
        throw SpriteAnimatedError {
            fmt::format("An animation with the name {} already exists", name)  
        };
    }
    animations_.emplace(name, frames);
}

auto SpriteAnimated::SetAnimation(std::string_view name) -> void {
    curr_animation_ = name;
    curr_frame_ = 0;

    auto& spritesheet = ResourceManager::GetSpritesheet(spritesheet_id());
    const auto frame = spritesheet.GetFrame(frame_id());
    width = frame.width;
    height = frame.height;
}

auto SpriteAnimated::UpdateFrame() -> void {
    if (timer_.GetMilliseconds() > 1000 / fps_) {
        timer_.Reset();
        const auto& frames = animations_.at(curr_animation_);
        curr_frame_ += 1;
        curr_frame_ %= frames.size();
    }
}