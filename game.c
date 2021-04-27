// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "game.h"
#include "sys/window.h"
#include "sys/utilities.h"
#include "sys/sounds.h"
#include "globals.h"
#include "objects/horizon.h"
#include "objects/t_rex.h"

typedef enum {
    GAME_INTRO = 0,
    GAME_PLAY,
    GAME_OVER
} GameState;

uint32_t game_time;
GameState game_state;
double game_speed = SPEED;

bool CollisionTest();

void GameOver();

void InitGame() {
    game_time = 0;
    game_state = GAME_PLAY;
    InitHorizon();
    InitTRex();
}

void Update(uint32_t delta_time) {
    if (game_state == GAME_PLAY) {
        if (game_speed < MAX_SPEED) {
            game_speed += ACCELERATION;
        }
        UpdateHorizon(delta_time, game_speed);
        UpdateTRex(delta_time);

        bool collision = CollisionTest();
        if (collision) {
            GameOver();
        }
    } else {
        // TODO: handle input
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
    PlaySound(SFX_HIT);
    game_state = GAME_OVER;
    SetTRexState(T_REX_HIT);
    // TODO: DrawGameOverPanel

    game_time = 0;
}

void DestroyGame() {
    FreeHorizonResources();
}
