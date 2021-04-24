// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "t_rex.h"
#include "globals.h"
#include "spritesheet.h"
#include "sys/utilities.h"
#include "sys/graphics.h"
#include "sys/input.h"
#include "sys/sounds.h"

typedef enum {
    RUNNING = 1,
    JUMPING,
    DUCKING,
} TRexState;

AnimFrame tx_anim[] = {
    {
        // waiting
        .frames = {44, 0},
        .len = 2,
        .ms_per_frame = 1000 / 3
    },
    {
        // running
        .frames = {88, 132},
        .len = 2,
        .ms_per_frame = 1000 / 12
    },
    {
        // jumping
        .frames = {0},
        .len = 1,
        .ms_per_frame = 1000 / 60
    },
    {
        // ducking
        .frames = {264, 323},
        .len = 2,
        .ms_per_frame = 1000 / 8
    }
};

int tx_width = 44;
int tx_height = 47;
int tx_ducking_width = 59;
int tx_time = 0;
int tx_curr_frame = 0;
int tx_ground_pos = 0;

double tx_jump_velocity = 0.0;

bool tx_speed_drop = false;

Point tx_sprite_def;
Point tx_pos;

TRexState tx_state = RUNNING;
AnimFrame tx_anim_frame;

void UpdateState(TRexState state);
void HandleControls();
void UpdateAnimationFrames(uint32_t delta_time);
void StartJump();
void EndJump();
void SetSpeedDrop();
void UpdateJump(uint32_t delta_time);
void Reset();

bool IsJumpKeyPressed();

void InitTRex() {
    tx_sprite_def = sprite_definitions[TREX];
    tx_anim_frame = tx_anim[tx_state];
    tx_ground_pos = WINDOW_HEIGHT - tx_height - GROUND_OFFSET;
    tx_pos.x = 50;
    tx_pos.y = tx_ground_pos;
    tx_time = 0;
}

void UpdateTRex(uint32_t delta_time) {
    HandleControls();
    UpdateAnimationFrames(delta_time);

    if (tx_state == JUMPING) {
        UpdateJump(delta_time);
    }
}

void HandleControls() {
    // jumping
    if (tx_state != JUMPING && tx_state != DUCKING && IsJumpKeyPressed()) {
        StartJump();
    }
    if (tx_state == JUMPING && !IsJumpKeyPressed()) {
        EndJump();
    }
    if (tx_state == JUMPING && IsKeyPressed(KEY_DOWN) && !tx_speed_drop) {
        SetSpeedDrop();
    }

    // ducking
    if (tx_state == RUNNING && IsKeyPressed(KEY_DOWN)) {
        UpdateState(DUCKING);
    }
    if (tx_state == DUCKING && !IsKeyPressed(KEY_DOWN)) {
        Reset();
    }
}

bool IsJumpKeyPressed() {
    return IsKeyPressed(KEY_UP) ||
           IsKeyPressed(KEY_SPACE);
}

void UpdateState(TRexState state) {
    tx_state = state;
    tx_anim_frame = tx_anim[tx_state];
    tx_curr_frame = 0;
}

void StartJump() {
    UpdateState(JUMPING);
    PlaySound(SFX_PRESS);
    tx_jump_velocity = INITIAL_JUMP_VELOCITY;
}

void UpdateJump(uint32_t delta_time) {
    double ms_per_frame = tx_anim[tx_state].ms_per_frame;
    double frames_elapsed = delta_time / ms_per_frame;

    if (tx_speed_drop) {
        tx_pos.y += tx_jump_velocity * SPEED_DROP_COEFFICIENT * frames_elapsed;
    } else {
        tx_pos.y += tx_jump_velocity * frames_elapsed;
    }

    tx_jump_velocity += GRAVITY * frames_elapsed;

    if (tx_pos.y < MAX_JUMP_HEIGHT || tx_speed_drop) {
        EndJump();
    }

    if (tx_pos.y > tx_ground_pos) {
        Reset();
    }
}

void EndJump() {
    if (tx_jump_velocity < DROP_VELOCITY) {
        tx_jump_velocity = DROP_VELOCITY;
    }
}

void SetSpeedDrop() {
    tx_speed_drop = true;
    tx_jump_velocity = 1;
}

void Reset() {
    tx_pos.y = tx_ground_pos;
    tx_jump_velocity = 0;
    tx_speed_drop = false;
    UpdateState(RUNNING);
}

void UpdateAnimationFrames(uint32_t delta_time) {
    tx_time += delta_time;
    if (tx_time >= tx_anim_frame.ms_per_frame) {
        if (tx_curr_frame == tx_anim_frame.len - 1) {
            tx_curr_frame = 0;
        } else {
            tx_curr_frame += 1;
        }
        tx_time = 0;
    }
}

void DrawTRex() {
    int width = tx_state != DUCKING ? tx_width : tx_ducking_width;
    Texture texture = {
        .id = 0,
        .source = {
            .x = tx_sprite_def.x + tx_anim_frame.frames[tx_curr_frame],
            .y = tx_sprite_def.y,
            .width = width,
            .height = tx_height
        },
        .destination = {
                .x = tx_pos.x,
                .y = tx_pos.y,
                .width = width,
                .height = tx_height
        }
    };
    DrawTexture(&texture);
}