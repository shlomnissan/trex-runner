// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_UTILITIES_H
#define TREX_RUNNER_UTILITIES_H

#include <stdbool.h>

typedef struct {
    int min;
    int max;
} Range;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Rectangle;

int RandomFromRange(Range range);

bool RectanglesIntersect(Rectangle* rect_a, Rectangle* rect_b);

#endif  // TREX_RUNNER_UTILITIES_H
