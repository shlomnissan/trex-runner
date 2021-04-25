// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "game.h"
#include "sys/window.h"
#include "globals.h"
#include "objects/obstacle.h"
#include "objects/horizon.h"
#include "objects/t_rex.h"

uint32_t game_time;
double game_speed = SPEED;

bool CollisionTest();

void InitGame() {
    game_time = 0;
    InitHorizon();
    InitTRex();
}

void Update(uint32_t delta_time) {
    if (game_speed < MAX_SPEED) {
        game_speed += ACCELERATION;
    }
    UpdateHorizon(delta_time, game_speed);
    UpdateTRex(delta_time);

    bool collision = CollisionTest();
}

bool CollisionTest() {
    Obstacle* obstacle = GetNearestObstacle();
    if (obstacle != NULL) {
        CollisionSet obstacle_collision = obstacle->type.collision_boxes;
        for (int i = 0; i < obstacle_collision.len; ++i) {
            obstacle_collision.rects[i].x += obstacle->pos.x;
            obstacle_collision.rects[i].y += obstacle->pos.y;
        }

        if (DEBUG_DRAW) {
            DrawCollisionSet(&obstacle_collision, HexToRGB(0xFF0000));
        }
    }
    return true;
}

void Draw() {
    DrawHorizon();
    DrawTRex();
}

void RunGame() {
    uint32_t now = GetTicks();
    uint32_t delta_time = now - game_time;
    game_time = now;
    Update(delta_time);
    Draw();
}

void DestroyGame() {
    FreeHorizonResources();
}
