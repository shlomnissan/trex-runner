// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "spritesheet.h"

#include <array>
#include <fstream>

#include <fmt/format.h>

Spritesheet::Spritesheet(const SpritesheetFiles& files)
  : image_(files.image) {
    std::ifstream json_file {files.dictionary};
    if (!json_file.is_open()) {
        throw SpritesheetError {
            fmt::format("Unable to load JSON file {}", files.dictionary)
        };
    }

    std::string content {
        std::istreambuf_iterator<char>(json_file),
        std::istreambuf_iterator<char>()
    };

    document_.Parse(content.c_str());
    if (document_.HasParseError()) {
        throw SpritesheetError {
            fmt::format("Failed to parse JSON file {}", files.dictionary)
        };
    }
}

auto Spritesheet::ValidateEntry(std::string_view frame) const -> void {
    if (!document_.HasMember(frame.data())) {
        throw SpritesheetError {
            fmt::format("Missing frame {} in spritesheet", frame)
        };
    }

    const auto& obj = document_[frame.data()];
    if (!obj.IsObject()) {
        throw SpritesheetError {
            fmt::format("{} is an invalid frame", frame)
        };
    }
}

auto Spritesheet::ValidateFrame(const JsonObject& obj) const -> void {
    auto fields = std::array<const char*, 4>{"x", "y", "width", "height"};
    for (const auto& field : fields) {
        if (!obj.HasMember(field) || !obj[field].IsInt()) {
            throw SpritesheetError {
                fmt::format("The {} field is missing for a given frame", field)
            };
        }
    }
}

auto Spritesheet::GetFrame(std::string_view frame) -> Frame {
    ValidateEntry(frame);
    const auto& obj = document_[frame.data()];
    ValidateFrame(obj);
    return {
        .x = obj["x"].GetInt(),
        .y = obj["y"].GetInt(),
        .width = obj["width"].GetInt(),
        .height = obj["height"].GetInt()
    };
}

auto Spritesheet::GetCollisionFrames(std::string_view frame) const -> std::vector<Frame> {
    ValidateEntry(frame);
    const auto& obj = document_[frame.data()];

    auto output = std::vector<Frame>{};
    if (!obj.HasMember("collision") || !obj["collision"].IsArray()) {
        return output;
    }

    for (const auto& entry : obj["collision"].GetArray()) {
        ValidateFrame(entry);
        output.emplace_back(Frame{
            entry["x"].GetInt(),
            entry["y"].GetInt(),
            entry["width"].GetInt(),
            entry["height"].GetInt()
        });
    }
    
    return output;
}