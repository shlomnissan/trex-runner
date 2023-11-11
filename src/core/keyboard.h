// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <unordered_map>
#include <vector>

enum class Key : uint8_t {
    Down = 81,
    Space = 32,
    Up = 82
};

using CallbackVector = std::vector<std::function<void()>>;

class Keyboard {
public:
    explicit Keyboard();

    auto AddOnKeyUpCallback(Key key, std::function<void()> func) -> void;
    auto IsKeyPressed(Key key) const -> bool;

private:
    std::array<bool, 256> keymap_ {false};
    std::unordered_map<uint8_t, CallbackVector> key_up_callbacks_;
};