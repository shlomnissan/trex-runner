// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_HORIZON_LINE_H
#define TREX_RUNNER_HORIZON_LINE_H

#include <stdint.h>

void InitHorizonLine();

void UpdateHorizonLine(uint32_t delta_time, double speed);

void DrawHorizonLine();

#endif  // TREX_RUNNER_HORIZON_LINE_H