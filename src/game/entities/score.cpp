// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "score.h"

#include <fmt/format.h>

#include "core/events.h"
#include "game/shared.h"

auto Score::UpdateWithSpeed(const double dt, const double speed) -> void {
    distance_ += speed * (kFPS / 1000) * dt;
    sprites_.clear();

    auto score = GetScore();

    if (achievement_.has_achievement) {
        score = achievement_.last_achievement;
        ScoreFlashing(dt);        
    } else if (score > 0 && score % kAchievementDistance == 0) {
        Events::GetInstance()->Publish("on_play_sound", "achievement");
        achievement_.has_achievement = true;
        achievement_.flash_iterations = kFlashIterations;
        achievement_.last_achievement = score;
    }

    auto offset = 0.0;
    auto alpha = should_show_score_ ? 255 : 0;
    offset = DrawScore(score, kWindowWidth, alpha);
    if (high_score_ > 0) {
        offset = DrawScore(high_score_, offset, kHighScoreAlpha);
        DrawCharacter('i', offset - kCharOffset * 2, kHighScoreAlpha);
        DrawCharacter('h', offset - kCharOffset * 3, kHighScoreAlpha);
    }
}

auto Score::DrawScore(int score, double x_offset, int alpha) -> double {
    auto digits = NumberOfDigits(score);
    auto x_pos = 0.0;
    for (auto i = 0; i < std::max(digits, kMinDigits); ++i) {
        auto this_digit = score % 10;
        score /= 10;
        x_pos = double(x_offset - kCharOffset * (i + 2));
        DrawCharacter(static_cast<char>(this_digit + '0'), x_pos, alpha); 
    }
    return x_pos;
}

auto Score::DrawCharacter(char character, double x_pos, int alpha) -> void {
    auto frame_id = fmt::format("char_{}", character);
    sprites_.emplace_back(std::make_unique<Sprite>(
        "spritesheet", frame_id, Vector2 {x_pos, 10}
    ));
    sprites_.back()->alpha = alpha;
}

auto Score::UpdateHighScore() -> void {
    high_score_ = std::max(high_score_, GetScore());
}

auto Score::ResetScore() -> void {
    distance_ = 0.0;
}

auto Score::GetScore() const -> int {
    return static_cast<int>(kDistanceCoefficient * distance_);
}

auto Score::NumberOfDigits(int n) const -> int {
    if (n == 0) return 0;
    return static_cast<int>(std::log10(n) + 1);
}

auto Score::ScoreFlashing(const double dt) -> void {
    should_show_score_ = true;
    if (achievement_.flash_iterations > 0) {
        achievement_.flash_timer += dt;
        if (achievement_.flash_timer < kFlashDuration) {
            should_show_score_ = false;
        } else if (achievement_.flash_timer > kFlashDuration * 2) {
            achievement_.flash_iterations--;
            achievement_.flash_timer = 0.0;
        }
    } else {
        achievement_.has_achievement = false;
        achievement_.flash_timer = 0.0;
    }
}