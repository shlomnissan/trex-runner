// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "horizon.h"

#include "horizon_line.h"
#include "clouds.h"

void InitHorizon() {
    InitHorizonLine();
    AddCloud();
}

void UpdateHorizon(uint32_t delta_time, double speed) {
    UpdateHorizonLine(delta_time, speed);
    UpdateClouds(delta_time, speed);
}

void DrawHorizon() {
    DrawHorizonLine();
    DrawClouds();
}

void DestroyHorizon() {
    DestroyClouds();
}