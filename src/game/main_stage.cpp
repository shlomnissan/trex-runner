// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "main_stage.h"

#include "core/events.h"
#include "game/shared.h"

auto MainStage::Init() -> void {
    AddEntity(&clouds_);
    AddEntity(&horizon_);
    AddEntity(&obstacles_);
    AddEntity(&score_);
    AddEntity(&trex_);

    clip_frame_ = std::make_unique<Frame>(Frame {
        .x = 0,
        .y = 0,
        .width = 45,
        .height = 150
    });

    trex_.SetStartCallback([&state = state_]() {
        state = RunnerState::Running;
    });
}

auto MainStage::Update(const double dt, Keyboard& keyboard) -> void {
    using enum RunnerState;
    if (state_ == Intro) UpdateIntro(dt, keyboard);
    if (state_ == Running) UpdateRunning(dt, keyboard);
    if (state_ == GameOver) UpdateGameOver(keyboard);
}

auto MainStage::UpdateIntro(const double dt, const Keyboard& keyboard) -> void {
    trex_.Update(dt, keyboard);
}

auto MainStage::UpdateRunning(const double dt, const Keyboard& keyboard) -> void {
    if (speed_ < kMaxSpeed) {
        speed_ += 0.001;
    }

    running_time_ += dt;
    trex_.Update(dt, keyboard);

    if (clip_frame_->width < kWindowWidth) {
        // intro, expand view
        auto rate = static_cast<double>(kWindowWidth) / kIntroDuration * dt * 2;
        clip_frame_->width += rate;
    } else {
        horizon_.UpdateWithSpeed(dt, speed_);
        clouds_.UpdateWithSpeed(dt, speed_);
        score_.UpdateWithSpeed(dt, speed_);
    }

    if (running_time_ > kClearTime) {
        obstacles_.UpdateWithSpeed(dt, speed_);
        if (trex_.HasCollision(obstacles_)) {
            Events::GetInstance()->Publish("on_play_sound", "hit");
            trex_.Crash();
            trex_.Update(dt, keyboard);
            score_.UpdateHighScore();
            AddEntity(&restart_);
            state_ = RunnerState::GameOver;
        }
    }
}

auto MainStage::UpdateGameOver(Keyboard& keyboard) -> void {
    const auto on_key_up = [&]() {
        if (state_ == RunnerState::GameOver) {
            RemoveEntity(&restart_);
            trex_.Reset();
            obstacles_.Reset();
            score_.ResetScore();
            speed_ = kDefaultSpeed;
            running_time_ = 0.0;
            state_ = RunnerState::Running;
        }
    };
    
    keyboard.AddOnKeyUpCallback(Key::Up, on_key_up);
    keyboard.AddOnKeyUpCallback(Key::Space, on_key_up);
}