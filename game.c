// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "game.h"
#include "sdl/window.h"
#include "globals.h"
#include "actors/horizon.h"
#include "actors/t_rex.h"

uint32_t time;
double current_speed = SPEED;

void InitGame() {
    time = 0;
    InitHorizon();
    InitTRex();
}

void Update(uint32_t delta_time) {
    if (current_speed < MAX_SPEED) {
        current_speed += ACCELERATION;
    }
    UpdateHorizon(delta_time, current_speed);
    UpdateTRex(delta_time);
}

void Draw() {
    DrawHorizon();
    DrawTRex();
}

void RunGame() {
    uint32_t now = GetTicks();
    uint32_t delta_time = now - time;
    time = now;
    Update(delta_time);
    Draw();
}

void DestroyGame() {
    DestroyHorizon();
}
