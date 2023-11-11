// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <cstdint>
#include <functional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

#include <fmt/format.h>

using OnQuit = std::function<void()>; 
using OnKeyDown = std::function<void(uint8_t)>;
using OnKeyUp = std::function<void(uint8_t)>;
using OnPlaySound = std::function<void(std::string_view)>;

using EventListener = std::variant<
    std::function<void()>,
    std::function<void(uint8_t)>,
    std::function<void(std::string_view)>
>;

using Callbacks = std::vector<EventListener>;

struct EventError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Events {
public:
    template <typename EventType>
    auto AddEventListener(std::string label, EventType listener) {
        if (callbacks.contains(label)) {
            callbacks.at(label).emplace_back(listener);
        } else {
            callbacks.emplace(label, Callbacks{listener});
        }
    }

    template <typename... Args>
    auto Publish(std::string label, Args... args) {
        if (!callbacks.contains(label)) return;

        for (const auto& callback : callbacks[label]) {
            std::visit([&](auto& f) {
                if constexpr (std::is_invocable_v<decltype(f), Args...>) {
                    f(args...);
                } else {
                    throw EventError {
                        fmt::format(
                            "Failed to invoke event '{}'. "
                            "Check the parameters passed to Events::Publish"
                        , label)
                    };
                }
            }, callback);
        }
    }

private:
    std::unordered_map<std::string, Callbacks> callbacks;
};