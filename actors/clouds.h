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

extern int last_cloud;
extern Cloud* clouds[];

void AddCloud();

void UpdateClouds(uint32_t delta_time, double speed);

void DrawClouds();

void DestroyClouds();

#endif  // TREX_RUNNER_CLOUDS_H
