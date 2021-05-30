// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "game.h"
#include "sys/window.h"
#include "sys/utilities.h"
#include "sys/sounds.h"
#include "sys/input.h"
#include "globals.h"
#include "objects/horizon.h"
#include "objects/t_rex.h"
#include "objects/game_over_panel.h"
#include "objects/distance_meter.h"

typedef enum {
    GAME_INTRO = 0,
    GAME_PLAY,
    GAME_OVER
} GameState;

typedef struct {
    GameState state;
    double speed;
    double distance_ran;
    int running_time;
    int game_played;
    int game_over_time;
    int highest_score;
    int time;
} Game;

Game game = {
    .state = GAME_INTRO,
    .speed = SPEED,
    .distance_ran = 0,
    .game_over_time = 0,
    .highest_score = 0,
    .time = 0
};

bool CollisionTest();
void GameOver();
void Start();
void Restart();
void OnKeyUp(char key);

void InitGame() {
    InitDistanceMeter();
    InitHorizon();
    InitTRex();

    SetOnKeyUp(&OnKeyUp);
}

void Update(uint32_t delta_time) {
    bool play_sound = UpdateDistanceMeter(delta_time, game.distance_ran);
    if (game.state == GAME_INTRO) {
        UpdateTRex(delta_time, Start);
    }
    if (game.state == GAME_PLAY) {
        game.running_time += delta_time;

        bool has_obstacles = game.running_time > CLEAR_TIME;
        UpdateHorizon(delta_time, game.speed, has_obstacles);
        UpdateTRex(delta_time, NULL);

        bool collision = CollisionTest();
        if (collision) {
            GameOver();
        } else {
            if (game.speed < MAX_SPEED) {
                game.speed += ACCELERATION;
            }
            game.distance_ran += game.speed * delta_time / (1000 / FPS);
        }
    } else if (game.state == GAME_OVER){
        game.game_over_time += delta_time;
    }

    if (play_sound) {
        PlaySound(SFX_REACHED);
    }
}

void OnKeyUp(char key) {
    // restart game
    if (game.state == GAME_OVER &&
        game.game_over_time > GAME_OVER_CLEAR_TIME &&
        (key == KEY_UP || key == KEY_SPACE)) {
        Restart();
    }
}

bool CollisionTest() {
    Rectangle trex_frame = GetTRexFrame();
    Rectangle obstacle_frame = GetNearestObstacleFrame();

    // adjustments are made to the bounding box as there is a 1 pixel white
    // border around the t-rex and obstacles
    trex_frame.x += 1;
    trex_frame.y += 1;
    trex_frame.width -= 2;
    trex_frame.height -= 2;

    obstacle_frame.x += 1;
    obstacle_frame.y += 1;
    obstacle_frame.width -= 2;
    obstacle_frame.height -= 2;

    if (DEBUG_DRAW) {
        // debug outer boxes
        DrawRectangle(&trex_frame, HexToRGB(0xFF0000), false);
        DrawRectangle(&obstacle_frame, HexToRGB(0x0000FF), false);
    }

    // simple outer bounds check
    if (RectanglesIntersect(&trex_frame, &obstacle_frame)) {
        CollisionSet obstacle_collision = GetNearestObstacleCollisionSet();
        CollisionSet trex_collision = GetTRexCollisionSet();
        if (obstacle_collision.len) {
            // detailed axis aligned box check
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
        SetDistanceMeterHighScore(game.highest_score);
    }
}

void Start() {
    game.state = GAME_PLAY;
}

void Restart() {
    game.distance_ran = 0.0;
    game.running_time = 0;
    game.speed = SPEED;
    game.game_over_time = 0;
    game.state = GAME_PLAY;
    game.time = GetTicks();

    ResetTRex();
    ResetDistanceMeter();
    ResetHorizon();
    PlaySound(SFX_PRESS);
}

void DestroyGame() {
    FreeHorizonResources();
}