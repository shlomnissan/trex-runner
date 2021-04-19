// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "game.h"

#include "sdl/window.h"
#include "globals.h"
#include "actors/horizon_line.h"
#include "actors/t_rex.h"

uint32_t time;
double currentSpeed = SPEED;

void InitGame() {
    time = 0;
    InitHorizonLine();
    InitTRex();
}

void Update(uint32_t delta_time) {
    if (currentSpeed < MAX_SPEED) {
        currentSpeed += ACCELERATION;
    }
    UpdateHorizonLine(delta_time, currentSpeed);
    UpdateTRex(delta_time);
}

void Draw() {
    DrawHorizonLine();
    DrawTRex();
}

void RunGame() {
    uint32_t now = GetTicks();
    uint32_t delta_time = now - time;
    time = now;
    Update(delta_time);
    Draw();
}
