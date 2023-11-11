// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <chrono>

class Timer {
public:
    Timer() : start_time_(Now()) {};

    auto GetMilliseconds() const { return (Now() - start_time_).count(); }
    auto GetSeconds() const { return static_cast<double>(GetMilliseconds()) / 1000.0; }
    auto Reset() { start_time_ = Now(); }

private:
    std::chrono::milliseconds start_time_ {0};

    auto Now() const -> std::chrono::milliseconds {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    }
};