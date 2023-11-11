// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <rapidjson/document.h>

#include "image.h"
#include "types.h"

struct SpritesheetFiles {
    std::string image;
    std::string dictionary;
};

using JsonObject = rapidjson::GenericValue<rapidjson::UTF8<>>;

class Spritesheet {
public:
    explicit Spritesheet(const SpritesheetFiles& files);

    auto GetFrame(std::string_view frame) -> Frame;
    auto GetCollisionFrames(std::string_view frame) const -> std::vector<Frame>;

    const auto& image() const { return image_; }

private:
    Image image_;
    rapidjson::Document document_;

    auto ValidateEntry(std::string_view frame) const -> void;
    auto ValidateFrame(const JsonObject& obj) const -> void;
};

struct SpritesheetError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};