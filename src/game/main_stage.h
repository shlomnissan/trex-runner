// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "core/keyboard.h"
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
    auto Update(const double dt, Keyboard& keyboard) -> void override;

    ~MainStage() override = default;

private:
    constexpr static auto kDefaultSpeed = 6.0;
    constexpr static auto kClearTime = 3000.0;
    constexpr static auto kMaxSpeed = 13.0;
    
    double running_time_ = 0.0;
    double speed_ {kDefaultSpeed};

    RunnerState state_ {RunnerState::Intro};
    Clouds clouds_ {events_};
    Restart restart_ {events_};
    Horizon horizon_ {events_};
    Obstacles obstacles_ {events_};
    TRex trex_ {events_};
    Score score_ {events_};

    auto UpdateIntro(const double dt, const Keyboard& keyboard) -> void;
    auto UpdateRunning(const double dt, const Keyboard& keyboard) -> void;
    auto UpdateGameOver(Keyboard& keyboard) -> void;
};