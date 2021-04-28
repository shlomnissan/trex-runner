// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_DISTANCE_METER_H
#define TREX_RUNNER_DISTANCE_METER_H

#include <stdint.h>

void InitDistanceMeter();

void UpdateDistanceMeter(uint32_t delta_time, double distance);

void SetDistanceMeterHighScore(int high_score);

void ResetDistanceMeter();


#endif  // TREX_RUNNER_DISTANCE_METER_H
