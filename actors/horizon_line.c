// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdlib.h>

#include "horizon_line.h"
#include "spritesheet.h"
#include "sdl/graphics.h"

int hl_bump_threshold = 5;
int hl_width = 600;
int hl_height = 12;
int hl_pos_y = 127;

int hl_pos_x[2];
int hl_source_x[2];

Point hl_sprite_def;

int GetRandomLinePosition(void);
void UpdateHorizonLineXPos(int32_t position, int increment);

void InitHorizonLine() {
    hl_sprite_def = sprite_definitions[HORIZON];
    hl_pos_x[0] = 0;
    hl_pos_x[1] = hl_width;
    hl_source_x[0] = hl_sprite_def.x;
    hl_source_x[1] = hl_sprite_def.x + hl_width;
}

void UpdateHorizonLine(uint32_t delta_time, double speed) {
    int increment = speed * (60.0 / 1000.0) * delta_time;
    if (hl_pos_x[0] <= 0) {
        UpdateHorizonLineXPos(0, increment);
    } else {
        UpdateHorizonLineXPos(1, increment);
    }
}

void UpdateHorizonLineXPos(int position, int increment) {
    int line_0 = position;
    int line_1 = position == 0 ? 1 : 0;
    hl_pos_x[line_0] -= increment;
    hl_pos_x[line_1] = hl_pos_x[line_0] + hl_width;
    if (hl_pos_x[line_0] <= -hl_width) {
        hl_pos_x[line_0] += hl_width * 2;
        hl_source_x[line_0] = GetRandomLinePosition() + hl_sprite_def.x;
    }
}

int GetRandomLinePosition() {
    return rand() % 10 >= hl_bump_threshold ? hl_width : 0;
}

void DrawHorizonLine() {
    Texture texture_0 = {
        .id = 0,
        .source = {
            .x = hl_source_x[0],
            .y = hl_sprite_def.y,
            .width = hl_width,
            .height = hl_pos_y
        },
        .destination = {
            .x = hl_pos_x[0],
            .y = hl_pos_y,
            .width = hl_width,
            .height = hl_height
        }
    };
    DrawTexture(&texture_0);

    Texture texture_1 = {
        .id = 0,
        .source = {
            .x = hl_source_x[1],
            .y = hl_sprite_def.y,
            .width = hl_width,
            .height = hl_pos_y
        },
        .destination = {
            .x = hl_pos_x[1],
            .y = hl_pos_y,
            .width = hl_width,
            .height = hl_height
        }
    };
    DrawTexture(&texture_1);
}
