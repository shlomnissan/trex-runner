// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "core/resource_manager.h"
#include "core/types.h"

class Sprite : public Vector2 {
public:
    int width {0};
    int height {0};
    int alpha {255};

    Sprite(std::string_view spritesheet_id, std::string_view frame_id, Vector2 pos)
      : spritesheet_id_(spritesheet_id), frame_id_(frame_id) {
        this->x = pos.x;
        this->y = pos.y;

        if (!frame_id_.empty()) {
            auto& spritesheet = ResourceManager::GetSpritesheet(spritesheet_id_);
            const auto frame = spritesheet.GetFrame(frame_id_);
            this->width = frame.width;
            this->height = frame.height;
        }       
    }

    virtual auto frame_id() const -> std::string { return frame_id_; }
    auto spritesheet_id() const { return spritesheet_id_; }

    auto SetFrame(std::string_view frame) { frame_id_ = frame; }
    
    virtual ~Sprite() = default;

private:
    std::string spritesheet_id_;
    std::string frame_id_;
};