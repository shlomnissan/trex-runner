// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_UTILITIES_H
#define TREX_RUNNER_UTILITIES_H

typedef struct {
    int min;
    int max;
} Range;

typedef struct {
    int x;
    int y;
} Point;

int RandomFromRange(Range range);

#endif  // TREX_RUNNER_UTILITIES_H
