// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <stdexcept>
#include <string_view>

#include <SDL2/SDL.h>

#include "core/image.h"
#include "core/types.h"
#include "core/events.h"

class Window {
public:
    Window(std::string_view title, int width, int height);

    auto SetEvents(Events* events) -> void;
    auto ClearScreen() -> void;
    auto DrawScreen(Frame* clip_frame) -> void;
    auto DrawRectangle(const Frame& src) -> void;
    auto DrawImage(
        const Image& image,
        const Frame& src,
        const Frame& dest,
        const int alpha
    ) -> void;

    ~Window();

private:
    Events* events_ {nullptr};
    SDL_Window* window_ {nullptr};
    SDL_Renderer* renderer_ {nullptr};

    auto PollEvents() -> void;
};

struct WindowError : public std::runtime_error {
    explicit WindowError(std::string_view loc);
};