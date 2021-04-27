// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdlib.h>

#include "horizon_line.h"
#include "spritesheet.h"
#include "sys/graphics.h"

typedef struct {
    Point sprite_def;
    int bump_threshold;
    int width;
    int height;
    int pos_y;
    int pos_x[2];
    int source_x[2];

} HorizonLine;

HorizonLine horizon_line;

int GetRandomLinePosition(void);
void UpdateHorizonLineXPos(int32_t position, int increment);

void InitHorizonLine() {
    horizon_line.bump_threshold = 5;
    horizon_line.width = 600;
    horizon_line.height = 12;
    horizon_line.pos_y = 127;
    horizon_line.sprite_def = sprite_definitions[HORIZON];
    horizon_line.pos_x[0] = 0;
    horizon_line.pos_x[1] = horizon_line.width;
    horizon_line.source_x[0] = horizon_line.sprite_def.x;
    horizon_line.source_x[1] = horizon_line.sprite_def.x + horizon_line.width;
}

void UpdateHorizonLine(uint32_t delta_time, double speed) {
    int increment = speed * (60.0 / 1000.0) * delta_time;
    if (horizon_line.pos_x[0] <= 0) {
        UpdateHorizonLineXPos(0, increment);
    } else {
        UpdateHorizonLineXPos(1, increment);
    }
}

void UpdateHorizonLineXPos(int position, int increment) {
    int line_0 = position;
    int line_1 = position == 0 ? 1 : 0;
    horizon_line.pos_x[line_0] -= increment;
    horizon_line.pos_x[line_1] = horizon_line.pos_x[line_0] + horizon_line.width;
    if (horizon_line.pos_x[line_0] <= -horizon_line.width) {
        horizon_line.pos_x[line_0] += horizon_line.width * 2;
        horizon_line.source_x[line_0] = GetRandomLinePosition() + horizon_line.sprite_def.x;
    }
}

int GetRandomLinePosition() {
    return rand() % 10 >= horizon_line.bump_threshold ? horizon_line.width : 0;
}

void DrawHorizonLine() {
    Texture texture_0 = {
        .id = 0,
        .source = {
            .x = horizon_line.source_x[0],
            .y = horizon_line.sprite_def.y,
            .width = horizon_line.width,
            .height = horizon_line.pos_y
        },
        .destination = {
            .x = horizon_line.pos_x[0],
            .y = horizon_line.pos_y,
            .width = horizon_line.width,
            .height = horizon_line.height
        }
    };
    DrawTexture(&texture_0);

    Texture texture_1 = {
        .id = 0,
        .source = {
            .x = horizon_line.source_x[1],
            .y = horizon_line.sprite_def.y,
            .width = horizon_line.width,
            .height = horizon_line.pos_y
        },
        .destination = {
            .x = horizon_line.pos_x[1],
            .y = horizon_line.pos_y,
            .width = horizon_line.width,
            .height = horizon_line.height
        }
    };
    DrawTexture(&texture_1);
}
