// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>

#include "spritesheet.h"

class ResourceManager {
public:
    ResourceManager() = delete;

    static auto LoadSpritesheet(const std::string& id, const SpritesheetFiles& files) -> void;
    static auto GetSpritesheet(const std::string& id) -> Spritesheet&;

private:
    static std::unordered_map<std::string, Spritesheet> sprites_;
};

struct ResourceManagerError : std::runtime_error {
    using std::runtime_error::runtime_error;
};