// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_GLOBALS_H
#define TREX_RUNNER_GLOBALS_H

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 150
#define WINDOW_TITLE "T-Rex Runner"
#define GRAVITY 0.6
#define GROUND_OFFSET 10
#define SPEED 6
#define INITIAL_JUMP_VELOCITY -10
#define ACCELERATION 0.001
#define MAX_SPEED 13
#define MAX_CLOUD_LENGTH 6
#define MAX_OBSTACLE_LENGTH 2
#define MAX_OBSTACLE_DUPLICATION 2
#define OBSTACLE_GAP_COEFFICIENT 1.5
#define CLOUDS_FREQUENCY 5
#define CLOUD_SKY_LEVEL_MIN 30
#define CLOUD_SKY_LEVEL_MAX 71
#define CLOUD_GAP_MIN 100
#define CLOUD_GAP_MAX 400
#define DROP_VELOCITY -5
#define MAX_JUMP_HEIGHT 30
#define SPEED_DROP_COEFFICIENT 3

typedef struct {
    int min;
    int max;
} Range;

typedef struct {
    int x;
    int y;
} Point;

#endif  // TREX_RUNNER_GLOBALS_H
