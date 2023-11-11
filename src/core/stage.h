// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "core/entity.h"
#include "core/events.h"
#include "core/keyboard.h"
#include "core/types.h"

class Stage {
public:
    explicit Stage(Events* events) : events_(events) {}

    virtual auto Init() -> void = 0;
    virtual auto Update(const double dt, Keyboard& keyboard) -> void = 0; 

    auto AddEntity(Entity* entity) {
        entities_.emplace_back(entity);
    }

    auto RemoveEntity(Entity* entity) {
        auto iter = std::find(begin(entities_), end(entities_), entity);
        entities_.erase(iter);
    }

    auto entities() const { return entities_; }
    auto clip_frame() const { return clip_frame_.get(); }

    virtual ~Stage() = default;

protected:
    std::unique_ptr<Frame> clip_frame_;
    Events* events_ {nullptr};

private:
    std::vector<Entity*> entities_;
};