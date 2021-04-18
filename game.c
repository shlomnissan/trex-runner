// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "game.h"

#include "sdl/window.h"

#include "game/horizon_line.h"
#include "game/t_rex.h"

uint32_t time;

void InitGame() {
    time = 0;
    InitHorizonLine();
    InitTRex();
}

void Update(uint32_t delta_time) {
    UpdateHorizonLine(delta_time);
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
