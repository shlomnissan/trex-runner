// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_CLOUDS_H
#define TREX_RUNNER_CLOUDS_H

#include <stdbool.h>
#include <stdint.h>

#include "globals.h"

typedef struct {
    Point pos;
    int cloud_gap;
    bool is_visible;
} Cloud;

Cloud* MakeCloud();

void UpdateCloud(Cloud* cloud, double speed);

void DrawCloud(Cloud* cloud);

#endif  // TREX_RUNNER_CLOUDS_H
