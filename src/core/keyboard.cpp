// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "keyboard.h"

#include "core/events.h"

Keyboard::Keyboard() {
    const auto on_key_up = [this](uint8_t key) {
        keymap_[key] = false;
        if (key_up_callbacks_.contains(key)) {
            for (const auto& f : key_up_callbacks_.at(key)) f();
        }
    };

    const auto on_key_down = [this](uint8_t key) {
        keymap_[key] = true;
    };

    Events::GetInstance()->AddEventListener<OnKeyDown>("on_key_down", on_key_down);
    Events::GetInstance()->AddEventListener<OnKeyUp>("on_key_up", on_key_up);
}

auto Keyboard::IsKeyPressed(Key key) const -> bool {
    return keymap_[static_cast<int>(key)];
}

auto Keyboard::AddOnKeyUpCallback(Key key, std::function<void()> func) -> void {
    key_up_callbacks_[static_cast<uint8_t>(key)].emplace_back(func);
}