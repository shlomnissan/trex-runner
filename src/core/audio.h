// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

#include <SDL2/SDL.h>

using Sound = std::pair<uint8_t*, uint32_t>;

class Audio {
public:
    Audio();
    ~Audio();

    auto LoadAudio(std::string_view path, std::string_view id) -> void;
    auto PlayAudio(std::string_view id) -> void;

private:
    SDL_AudioDeviceID device {0};
    std::unordered_map<std::string, Sound> store;
};

struct AudioError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};