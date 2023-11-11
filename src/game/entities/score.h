// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "core/entity.h"

struct Achievement {
    bool has_achievement;
    int last_achievement;
    int flash_iterations;
    double flash_timer;
};

class Score : public Entity {
public:
    using Entity::Entity;

    auto UpdateWithSpeed(const double dt, const double speed) -> void;
    auto UpdateHighScore() -> void;
    auto ResetScore() -> void;

private:
    constexpr static auto kDistanceCoefficient = 0.025;
    constexpr static auto kCharOffset = 11;
    constexpr static auto kMinDigits = 5;
    constexpr static auto kAchievementDistance = 100;
    constexpr static auto kHighScoreAlpha = 208;
    constexpr static auto kFlashIterations = 3;
    constexpr static auto kFlashDuration = 1000.0 / 4.0;

    bool should_show_score_ {true};
    int n_digits_ {5};
    int high_score_ {0};
    double distance_ {0.0};
    Achievement achievement_ {false, 0, 0, 0.0};

    auto DrawCharacter(char character, double x_pos, int alpha) -> void;
    auto DrawScore(int score, double x_offset, int alpha) -> double;
    auto GetScore() const -> int;
    auto NumberOfDigits(int n) const -> int;
    auto ScoreFlashing(const double dt) -> void;
};