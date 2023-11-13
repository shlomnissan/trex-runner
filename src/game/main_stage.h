// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "core/stage.h"
#include "entities/clouds.h"
#include "entities/horizon.h"
#include "entities/obstacles.h"
#include "entities/restart.h"
#include "entities/score.h"
#include "entities/trex.h"

enum class RunnerState {
    Intro,
    Running,
    GameOver
};

class MainStage : public Stage {
public:
    using Stage::Stage;

    auto Init() -> void override;
    auto Update(const double dt) -> void override;

    ~MainStage() override = default;

private:
    constexpr static auto kDefaultSpeed = 6.0;
    constexpr static auto kClearTime = 3000.0;
    constexpr static auto kMaxSpeed = 13.0;
    
    double running_time_ = 0.0;
    double speed_ {kDefaultSpeed};

    RunnerState state_ {RunnerState::Intro};
    Clouds clouds_;
    Restart restart_;
    Horizon horizon_;
    Obstacles obstacles_;
    TRex trex_;
    Score score_;

    auto UpdateIntro(const double dt) -> void;
    auto UpdateRunning(const double dt) -> void;
    auto RegisterKeys() -> void;
    auto ResetGame() -> void;
};