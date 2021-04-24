// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_OBSTACLE_H
#define TREX_RUNNER_OBSTACLE_H

#include <stdbool.h>

#include "sys/utilities.h"
#include "globals.h"

typedef struct {
    int type;
    int width;
    int height;
    int y_pos;
    int multiple_speed;
    int min_gap;
    int min_speed;
    int speed_offset;
} ObstacleType;

typedef struct {
    ObstacleType type_config;
    Point sprite_def;
    Point pos;
    int size;
    int width;
    int gap;
    int speed_offset;
    bool is_visible;
} Obstacle;

Obstacle* MakeObstacle(int type, double speed);

void UpdateObstacle(Obstacle* obstacle);

void DrawObstacle(Obstacle* obstacle);

#endif  // TREX_RUNNER_OBSTACLE_H
