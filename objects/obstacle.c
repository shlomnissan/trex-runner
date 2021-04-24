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

Obstacle* MakeObstacle(int type) {
    // allocate memory for a new obstacle
    Obstacle* obstacle = (Obstacle*) malloc(sizeof(Obstacle));

    obstacle->type_config = obstacle_type[type];
    obstacle->sprite_def = sprite_definitions[type];
    obstacle->pos.x = WINDOW_WIDTH - 200;
    obstacle->pos.y = obstacle_type[type].y_pos;
    obstacle->size = (rand() % 3) + 1;
    obstacle->gap = 0;
    obstacle->speed_offset = 0;
    obstacle->is_visible = true;

    return obstacle;
}

void DrawObstacle(Obstacle* obstacle) {
    int source_width = obstacle->type_config.width;
    int source_height = obstacle->type_config.height;
    int texture_width = source_width * obstacle->size;
    int source_x = source_width * obstacle->size + obstacle->sprite_def.x;
    Texture texture = {
       .id = 0,
       .source = {
           .x = source_x,
           .y = obstacle->sprite_def.y,
           .width = texture_width,
           .height = source_height
       },
       .destination = {
           .x = obstacle->pos.x,
           .y = obstacle->pos.y,
           .width = texture_width,
           .height = obstacle->type_config.height
       }
    };

    DrawTexture(&texture);
}