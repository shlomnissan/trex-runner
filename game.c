// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "game.h"
#include "sys/window.h"
#include "sys/utilities.h"
#include "globals.h"
#include "objects/horizon.h"
#include "objects/t_rex.h"

uint32_t game_time;
double game_speed = SPEED;

bool CollisionTest();

void GameOver();

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
    if (collision) {
        GameOver();
    }
}

bool CollisionTest() {
    CollisionSet obstacle_collision = GetNearestObstacleCollisionSet();
    CollisionSet trex_collision = GetTRexCollisionSet();
    if (obstacle_collision.len) {
        for (int i = 0; i < trex_collision.len; ++i) {
            for (int j = 0; j < obstacle_collision.len; ++j) {
                if (RectanglesIntersect(
                    &trex_collision.rects[i],
                    &obstacle_collision.rects[j])
                ) {
                    return true;
                }
            }
        }

        if (DEBUG_DRAW) {
            DrawCollisionSet(&obstacle_collision, HexToRGB(0xFF0000));
            DrawCollisionSet(&trex_collision, HexToRGB(0x0000FF));
        }
    }
    return false;
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

void GameOver() {
    // TODO: handle game over
}

void DestroyGame() {
    FreeHorizonResources();
}
