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

    RegisterKeys();
}

auto MainStage::RegisterKeys() -> void {
    using enum RunnerState;

    constexpr static auto key_space = 32;
    constexpr static auto key_up = 82;
    Events::GetInstance()->AddEventListener<OnKeyUp>
        ("on_key_up", [this](uint8_t key){
        if ((key == key_space || key == key_up) && state_ == GameOver) {
            ResetGame();
        }
    });
}

auto MainStage::Update(const double dt) -> void {
    using enum RunnerState;
    if (state_ == Intro) UpdateIntro(dt);
    if (state_ == Running) UpdateRunning(dt);
}

auto MainStage::UpdateIntro(const double dt) -> void {
    trex_.Update(dt);
}

auto MainStage::UpdateRunning(const double dt) -> void {
    if (speed_ < kMaxSpeed) {
        speed_ += 0.001;
    }

    running_time_ += dt;
    trex_.Update(dt);

    if (clip_frame_->width < kWindowWidth) {
        // intro transition, expand view
        auto rate = static_cast<double>(kWindowWidth) / kIntroDuration * dt * 2;
        clip_frame_->width += static_cast<int>(rate);
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
            trex_.Update(dt);
            score_.UpdateHighScore();
            AddEntity(&restart_);
            state_ = RunnerState::GameOver;
        }
    }
}

auto MainStage::ResetGame() -> void {
    RemoveEntity(&restart_);
    trex_.Reset();
    obstacles_.Reset();
    score_.ResetScore();
    speed_ = kDefaultSpeed;
    running_time_ = 0.0;
    state_ = RunnerState::Running;
}