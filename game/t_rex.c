// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "t_rex.h"

#include "sdl/graphics.h"
#include "assets/spritesheet.h"

typedef enum {
    RUNNING = 1,
} TRexState;

AnimFrame tx_anim[] = {
    {
        .frames = {44, 0},
        .len = 2,
        .ms_per_frame = 1000 / 3
    },
    {
        .frames = {88, 132},
        .len = 2,
        .ms_per_frame = 1000 / 12
    }
};

int tx_width = 44;
int tx_height = 47;
int tx_ground_offset = 10;
int tx_time = 0;
int tx_curr_frame = 0;

Point tx_sprite_def;
Point tx_pos;

TRexState tx_state = RUNNING;
AnimFrame tx_anim_frame;

void DrawTRex(void);

void InitTRex() {
    tx_sprite_def = sprite_definitions[TREX];
    tx_anim_frame = tx_anim[tx_state];
    tx_pos.x = 50;
    tx_pos.y = 150 - tx_height - tx_ground_offset;
    tx_time = 0;
}

void UpdateTRex(uint32_t delta_time) {
    tx_time += delta_time;
    if (tx_time >= tx_anim_frame.ms_per_frame) {
        if (tx_curr_frame == tx_anim_frame.len) {
            tx_curr_frame = 0;
        } else {
            tx_curr_frame += 1;
        }
        tx_time = 0;
    }
}

void DrawTRex() {
    Texture texture = {
        .id = 0,
        .source = {
            .x = tx_sprite_def.x + tx_anim_frame.frames[tx_curr_frame],
            .y = tx_sprite_def.y,
            .width = tx_width,
            .height = tx_height
        },
        .destination = {
                .x = tx_pos.x,
                .y = tx_pos.y,
                .width = tx_width,
                .height = tx_height
        }
    };
    DrawTexture(&texture);
}