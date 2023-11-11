// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <random>

class Random {
public:
    Random(int low, int high) : dist {low, high} {}

    auto operator()() -> int { return dist(engine); }

private:
    std::default_random_engine engine {std::random_device()()};
    std::uniform_int_distribution<> dist;
};