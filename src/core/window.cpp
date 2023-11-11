// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "window.h"

#include <fmt/format.h>

#include "core/events.h"
#include "core/timer.h"

Window::Window(std::string_view title, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw WindowError("SDL_Init");
    }

    auto window_flags = SDL_WINDOW_SHOWN;
    window_ = SDL_CreateWindow(
        title.data(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        window_flags
    );

    if (window_ == nullptr) {
        throw WindowError("SDL_CreateWindow");
    }

    auto renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    renderer_ = SDL_CreateRenderer(window_, -1, renderer_flags);

    if (renderer_ == nullptr) {
        throw WindowError("SDL_CreateRenderer");
    }
}

auto Window::ClearScreen() -> void {
    SDL_SetRenderDrawColor(renderer_, 0xf7, 0xf7, 0xf7, 255);
    SDL_RenderClear(renderer_);
}

auto Window::DrawScreen(Frame* clip_frame) -> void {
    if (clip_frame != nullptr) {
        SDL_Rect clip {
            clip_frame->x,
            clip_frame->y,
            clip_frame->width,
            clip_frame->height
        };
        SDL_RenderSetClipRect(renderer_, &clip);
    }
    PollEvents();
    SDL_RenderPresent(renderer_);
}

auto Window::DrawImage(
    const Image& image,
    const Frame& src,
    const Frame& dest,
    const int alpha
) -> void {
    auto pitch = image.width() * image.bpp();
    pitch = (pitch + 3) & ~3;

    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        image.data(),
        image.width(),
        image.height(),
        image.bpp() * 8,
        pitch,
        0x000000FF, 0x0000FF00, 0x00FF0000,
        (image.bpp() == 4) ? 0xFF000000 : 0
    );

    // // TODO: handle big endian

    auto texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_SetTextureAlphaMod(texture, alpha);
    SDL_FreeSurface(surface);

    SDL_Rect source_rect {
        .x = src.x,
        .y = src.y,
        .w = src.width,
        .h = src.height
    };

    SDL_Rect destination_rect {
        .x = dest.x,
        .y = dest.y,
        .w = dest.width,
        .h = dest.height
    };

    SDL_RenderCopy(renderer_, texture, &source_rect, &destination_rect);
    SDL_DestroyTexture(texture);
}

auto Window::DrawRectangle(const Frame& src) -> void {
    SDL_Rect rect {
        .x = src.x,
        .y = src.y,
        .w = src.width,
        .h = src.height
    };

    SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer_, &rect);
}

auto Window::PollEvents() -> void {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            Events::GetInstance()->Publish("on_quit");
        }
        if (event.type == SDL_KEYDOWN) {
            Events::GetInstance()->Publish("on_key_down", event.key.keysym.sym);
        }
        if (event.type == SDL_KEYUP) {
            Events::GetInstance()->Publish("on_key_up", event.key.keysym.sym);
        }
    }
}

Window::~Window() {
    if (window_ != nullptr) SDL_DestroyWindow(window_);
    if (renderer_ != nullptr) SDL_DestroyRenderer(renderer_);
    SDL_Quit();
}

WindowError::WindowError(std::string_view loc) : std::runtime_error(
    fmt::format("SDL error ({}): {}", loc, SDL_GetError())
) {}