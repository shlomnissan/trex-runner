// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdlib.h>

#include "obstacle.h"
#include "spritesheet.h"
#include "sys/graphics.h"

// the type value corresponds to the
// position in spritesheet_definitions
ObstacleType obstacle_type[] = {
    {
        type: CACTUS_SMALL,
        width: 17,
        height: 35,
        y_pos: 105,
        multiple_speed: 4,
        min_gap: 120,
        min_speed: 0
    },
    {
        type: CACTUS_LARGE,
        width: 25,
        height: 50,
        y_pos: 90,
        multiple_speed: 7,
        min_gap: 120,
        min_speed: 0
    }
};

int GetGap(Obstacle* obstacle, double speed);

Obstacle* MakeObstacle(int type, double speed) {
    // allocate memory for a new obstacle
    Obstacle* obstacle = (Obstacle*) malloc(sizeof(Obstacle));
    int size = rand() % 3 + 1;
    obstacle->type_config = obstacle_type[type];
    obstacle->sprite_def = sprite_definitions[type];
    obstacle->pos.x = WINDOW_WIDTH - 200;
    obstacle->pos.y = obstacle_type[type].y_pos;
    obstacle->width = obstacle_type[type].width * size;
    obstacle->size = size;
    obstacle->speed_offset = 0;
    obstacle->is_visible = true;
    obstacle->gap = GetGap(obstacle, speed);

    return obstacle;
}

void DrawObstacle(Obstacle* obstacle) {
    int source_height = obstacle->type_config.height;
    int source_x = obstacle->width + obstacle->sprite_def.x;
    Texture texture = {
       .id = 0,
       .source = {
           .x = source_x,
           .y = obstacle->sprite_def.y,
           .width = obstacle->width,
           .height = source_height
       },
       .destination = {
           .x = obstacle->pos.x,
           .y = obstacle->pos.y,
           .width = obstacle->width,
           .height = obstacle->type_config.height
       }
    };

    DrawTexture(&texture);
}

int GetGap(Obstacle* obstacle, double speed) {
    int min_gap =
            obstacle->width * speed +
            obstacle->type_config.min_gap *
            OBSTACLE_MIN_GAP_COEFFICIENT;
    int max_gap =
            min_gap *
            OBSTACLE_MAX_GAP_COEFFICIENT;

    Range range = {
        .min = min_gap,
        .max = max_gap
    };
    return RandomFromRange(range);
}