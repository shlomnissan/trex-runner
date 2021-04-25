// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "t_rex.h"
#include "globals.h"
#include "spritesheet.h"
#include "sys/utilities.h"
#include "sys/input.h"
#include "sys/sounds.h"

typedef enum {
    T_REX_RUNNING = 1,
    T_REX_JUMPING,
    T_REX_DUCKING,
} TRexState;

typedef struct {
    TRexState state;
    Point sprite_def;
    Point pos;
    AnimationFrames anim_frame;
    double jump_velocity;
    int width;
    int height;
    int ducking_width;
    int time;
    int curr_frame;
    int ground_pos;
    int min_jump_height;
    bool speed_drop;
    bool reached_min_height;
} TRex;

AnimationFrames trex_animation_frames[] = {
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

CollisionSet trex_collision_sets[] = {
    {
        // ducking
        .len = 1,
        .rects = {
            {.x = 1, .y = 18, .width = 55, .height = 25}
        }
    },
    {
        // running
        .len = 6,
        .rects = {
            {.x = 22, .y = 0, .width = 17, .height = 16},
            {.x = 1, .y = 18, .width = 30, .height = 9},
            {.x = 10, .y = 35, .width = 14, .height = 8},
            {.x = 1, .y = 24, .width = 29, .height = 5},
            {.x = 5, .y = 30, .width = 21, .height = 4},
            {.x = 9, .y = 34, .width = 15, .height = 4}
        }
    }
};

void UpdateState(TRexState state);
void HandleControls();
void UpdateAnimationFrames(uint32_t delta_time);
void StartJump();
void EndJump();
void SetSpeedDrop();
void UpdateJump(uint32_t delta_time);
void Reset();

bool IsJumpKeyPressed();
bool IsDuckKeyPressed();

TRex trex;

void InitTRex() {
    trex.state = T_REX_RUNNING;
    trex.width = 44;
    trex.height = 47;
    trex.ducking_width = 59;
    trex.time = 0;
    trex.curr_frame = 0;
    trex.ground_pos = WINDOW_HEIGHT - trex.height - GROUND_OFFSET;
    trex.min_jump_height = trex.ground_pos - MIN_JUMP_HEIGHT;
    trex.sprite_def = sprite_definitions[TREX];
    trex.anim_frame = trex_animation_frames[trex.state];
    trex.pos.x = 50;
    trex.pos.y = trex.ground_pos;
    trex.jump_velocity = 0.0;
    trex.speed_drop = false;
    trex.reached_min_height = false;
}

void UpdateTRex(uint32_t delta_time) {
    HandleControls();
    UpdateAnimationFrames(delta_time);

    if (trex.state == T_REX_JUMPING) {
        UpdateJump(delta_time);
    }
}

void HandleControls() {
    // jumping
    if (trex.state != T_REX_JUMPING && trex.state != T_REX_DUCKING && IsJumpKeyPressed()) {
        StartJump();
    }
    if (trex.state == T_REX_JUMPING && !IsJumpKeyPressed()) {
        EndJump();
    }
    if (trex.state == T_REX_JUMPING && IsDuckKeyPressed() && !trex.speed_drop) {
        SetSpeedDrop();
    }

    // ducking
    if (trex.state == T_REX_RUNNING && IsDuckKeyPressed()) {
        UpdateState(T_REX_DUCKING);
    }
    if (trex.state == T_REX_DUCKING && !IsDuckKeyPressed()) {
        Reset();
    }
}

bool IsJumpKeyPressed() {
    return IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE);
}

bool IsDuckKeyPressed() {
    return IsKeyPressed(KEY_DOWN);
}

void UpdateState(TRexState state) {
    trex.state = state;
    trex.anim_frame = trex_animation_frames[trex.state];
    trex.curr_frame = 0;
}

void StartJump() {
    UpdateState(T_REX_JUMPING);
    PlaySound(SFX_PRESS);
    trex.jump_velocity = INITIAL_JUMP_VELOCITY;
}

void UpdateJump(uint32_t delta_time) {
    double ms_per_frame = trex_animation_frames[trex.state].ms_per_frame;
    double frames_elapsed = delta_time / ms_per_frame;

    if (trex.speed_drop) {
        trex.pos.y += trex.jump_velocity * SPEED_DROP_COEFFICIENT * frames_elapsed;
    } else {
        trex.pos.y += trex.jump_velocity * frames_elapsed;
    }

    trex.jump_velocity += GRAVITY * frames_elapsed;

    if (trex.pos.y < trex.min_jump_height || trex.speed_drop) {
        trex.reached_min_height = true;
    }

    if (trex.pos.y < MAX_JUMP_HEIGHT || trex.speed_drop) {
        EndJump();
    }

    if (trex.pos.y > trex.ground_pos) {
        Reset();
    }
}

void EndJump() {
    if (trex.reached_min_height && trex.jump_velocity < DROP_VELOCITY) {
        trex.jump_velocity = DROP_VELOCITY;
    }
}

void SetSpeedDrop() {
    trex.speed_drop = true;
    trex.jump_velocity = 1;
}

void Reset() {
    trex.pos.y = trex.ground_pos;
    trex.jump_velocity = 0;
    trex.speed_drop = false;
    trex.reached_min_height = false;

    if (IsDuckKeyPressed()) {
        UpdateState(T_REX_DUCKING);
    } else {
        UpdateState(T_REX_RUNNING);
    }
}

void UpdateAnimationFrames(uint32_t delta_time) {
    trex.time += delta_time;
    if (trex.time >= trex.anim_frame.ms_per_frame) {
        if (trex.curr_frame == trex.anim_frame.len - 1) {
            trex.curr_frame = 0;
        } else {
            trex.curr_frame += 1;
        }
        trex.time = 0;
    }
}

void DrawTRex() {
    int width = trex.state != T_REX_DUCKING ? trex.width : trex.ducking_width;
    Texture texture = {
        .id = 0,
        .source = {
            .x = trex.sprite_def.x + trex.anim_frame.frames[trex.curr_frame],
            .y = trex.sprite_def.y,
            .width = width,
            .height = trex.height
        },
        .destination = {
                .x = trex.pos.x,
                .y = trex.pos.y,
                .width = width,
                .height = trex.height
        }
    };
    DrawTexture(&texture);
}

CollisionSet GetTRexCollisionSet() {
    CollisionSet collision_set = trex_collision_sets[1];
    if (trex.state == T_REX_DUCKING) {
        collision_set = trex_collision_sets[0];
    }
    for (int i = 0; i < collision_set.len; ++i) {
        collision_set.rects[i].x += trex.pos.x;
        collision_set.rects[i].y += trex.pos.y;
    }
    return collision_set;
}
