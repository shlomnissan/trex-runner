// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_HORIZON_H
#define TREX_RUNNER_HORIZON_H

#include <stdint.h>

#include "sys/graphics.h"

void InitHorizon();

void UpdateHorizon(uint32_t delta_time, double speed);

void DrawHorizon();

CollisionSet GetNearestObstacleCollisionSet();

void FreeHorizonResources();

#endif  // TREX_RUNNER_HORIZON_H
