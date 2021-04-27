// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "game.h"
#include "sys/window.h"
#include "sys/utilities.h"
#include "sys/sounds.h"
#include "globals.h"
#include "objects/horizon.h"
#include "objects/t_rex.h"
#include "objects/game_over_panel.h"

typedef enum {
    GAME_INTRO = 0,
    GAME_PLAY,
    GAME_OVER
} GameState;

typedef struct {
    GameState state;
    double speed;
    double distance_ran;
    int highest_score;
    int time;
} Game;

Game game = {
    .state = GAME_PLAY,
    .speed = SPEED,
    .distance_ran = 0,
    .highest_score = 0,
    .time = 0
};

bool CollisionTest();

void GameOver();

void InitGame() {
    InitHorizon();
    InitTRex();
}

void Update(uint32_t delta_time) {
    if (game.state == GAME_PLAY) {
        UpdateHorizon(delta_time, game.speed);
        UpdateTRex(delta_time);

        bool collision = CollisionTest();
        if (collision) {
            GameOver();
        } else {
            if (game.speed < MAX_SPEED) {
                game.speed += ACCELERATION;
            }
            game.distance_ran += game.speed * delta_time / (1000 / FPS);
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

    if (game.state == GAME_OVER) {
        DrawGameOverPanel();
    }
}

void RunGame() {
    uint32_t now = GetTicks();
    uint32_t delta_time = now - game.time;
    game.time = now;
    Update(delta_time);
    Draw();
}

void GameOver() {
    PlaySound(SFX_HIT);
    game.state = GAME_OVER;
    SetTRexState(T_REX_HIT);
    if (game.distance_ran > game.highest_score) {
        game.highest_score = (int)game.distance_ran;
    }
}

void DestroyGame() {
    FreeHorizonResources();
}
