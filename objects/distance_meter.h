// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_DISTANCE_METER_H
#define TREX_RUNNER_DISTANCE_METER_H

#include <stdbool.h>
#include <stdint.h>

void InitDistanceMeter();

bool UpdateDistanceMeter(uint32_t delta_time, double distance, bool should_draw);

void SetDistanceMeterHighScore(int score);

void ResetDistanceMeter();


#endif  // TREX_RUNNER_DISTANCE_METER_H
