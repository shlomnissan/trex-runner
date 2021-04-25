// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdlib.h>

#include "obstacle.h"
#include "spritesheet.h"

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
        min_speed: 0,
        collision_boxes: {
            {.x = 0, .y = 7, .width = 5, .height = 27},
            {.x = 4, .y = 0, .width = 6, .height = 34},
            {.x = 10, .y = 4, .width = 7, .height = 14}
        }
    },
    {
        type: CACTUS_LARGE,
        width: 25,
        height: 50,
        y_pos: 90,
        multiple_speed: 7,
        min_gap: 120,
        min_speed: 0,
        collision_boxes: {
            {.x = 0, .y = 12, .width = 7, .height = 38},
            {.x = 8, .y = 0, .width = 7, .height = 49},
            {.x = 13, .y = 10, .width = 10, .height = 38}
        }
    }
};

int GetGap(Obstacle* obstacle, double speed);

Obstacle* MakeObstacle(int type, double speed) {
    // allocate memory for a new obstacle
    Obstacle* obstacle = (Obstacle*) malloc(sizeof(Obstacle));
    int size = rand() % 3 + 1;
    obstacle->type = obstacle_type[type];
    obstacle->sprite_def = sprite_definitions[type];
    obstacle->pos.x = WINDOW_WIDTH;
    obstacle->pos.y = obstacle_type[type].y_pos;
    obstacle->width = obstacle_type[type].width * size;
    obstacle->size = size;
    obstacle->speed_offset = 0;
    obstacle->following_obstacle_created = false;
    obstacle->is_visible = true;
    obstacle->gap = GetGap(obstacle, speed);

    // make collision box adjustments,
    // central box is adjusted to the size as one box.
    //      ____        ______        ________
    //    _|   |-|    _|     |-|    _|       |-|
    //   | |<->| |   | |<--->| |   | |<----->| |
    //   | | 1 | |   | |  2  | |   | |   3   | |
    //   |_|___|_|   |_|_____|_|   |_|_______|_|

    if (obstacle->size > 1) {
        obstacle->type.collision_boxes[1].width =
                obstacle->width -
                obstacle->type.collision_boxes[0].width -
                obstacle->type.collision_boxes[2].width;
        obstacle->type.collision_boxes[2].x =
                obstacle->width -
                obstacle->type.collision_boxes[2].width;
    }

    return obstacle;
}

void UpdateObstacle(Obstacle* obstacle, uint32_t delta_time, double speed) {
    int obstacle_speed = (speed * FPS / 1000) * delta_time;
    obstacle->pos.x -= obstacle_speed;

    if (!IsObstacleVisible(obstacle)) {
        obstacle->is_visible = false;
    }
}

void DrawObstacle(Obstacle* obstacle) {
    int source_height = obstacle->type.height;
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
           .height = obstacle->type.height
       }
    };

    DrawTexture(&texture);
}

bool IsObstacleVisible(Obstacle* obstacle) {
    return obstacle->pos.x + obstacle->width > 0;
}

int GetGap(Obstacle* obstacle, double speed) {
    int min_gap =
            obstacle->width * speed +
            obstacle->type.min_gap *
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