// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "resource_manager.h"

#include <fmt/format.h>

std::unordered_map<std::string, Spritesheet> ResourceManager::sprites_;

auto ResourceManager::LoadSpritesheet(const std::string& id, const SpritesheetFiles& files) -> void {
    sprites_.emplace(id, files);
}

auto ResourceManager::GetSpritesheet(const std::string &id) -> Spritesheet& {
    if (!sprites_.contains(id)) {
        throw ResourceManagerError {
            fmt::format("Missing spritesheet with ID '{}'", id)
        };
    }

    return sprites_.at(id);
}