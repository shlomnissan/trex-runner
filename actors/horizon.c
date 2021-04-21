// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdlib.h>

#include "horizon.h"

#include "horizon_line.h"
#include "clouds.h"

void AddCloudIfNeeded();

void InitHorizon() {
    InitHorizonLine();
    AddCloud();
}

void UpdateHorizon(uint32_t delta_time, double speed) {
    UpdateHorizonLine(delta_time, speed);
    UpdateClouds(delta_time, speed);
    AddCloudIfNeeded();
}

void AddCloudIfNeeded() {
    Cloud* last = clouds[last_cloud];
    if (
        cloud_count < MAX_CLOUDS &&
        (WINDOW_WIDTH - last->pos.x) > last->cloud_gap &&
        rand() % 10 > CLOUDS_FREQUENCY
    ) {
        AddCloud();
    }
}

void DrawHorizon() {
    DrawHorizonLine();
    DrawClouds();
}

void DestroyHorizon() {
    DestroyClouds();
}