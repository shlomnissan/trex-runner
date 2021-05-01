// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <math.h>

#include "distance_meter.h"
#include "spritesheet.h"
#include "sys/utilities.h"
#include "sys/graphics.h"

typedef struct {
    Point sprite_def;
    Point pos;
    int max_digits;
    int width;
    int height;
    int dest_width;
    int max_score;
} DistanceMeter;

DistanceMeter distance_meter = {
    .pos = {
        .x = 0,
        .y = 10
    },
    .max_digits = MAX_DISTANCE_UNITS,
    .width = 10,
    .height = 13,
    .dest_width = 11,
};

bool achievement = false;
int high_score = 0;
uint32_t last_distance = 0;
uint32_t flash_iterations = 0;
uint32_t flash_timer = 0;

int GetActualDistance(double distance);
void DrawDistanceMeterDigit(int digit_pos, int value, bool opt_high_score);
void DrawScore(int score, bool opt_max_score);
void DrawHighScore();
void ResetXPos();

void InitDistanceMeter() {
    distance_meter.sprite_def = sprite_definitions[TEXT_SPRITE];
    for (int i = 0; i < distance_meter.max_digits; ++i) {
        DrawDistanceMeterDigit(i, 0, false);
    }
    distance_meter.max_score = pow(10, distance_meter.max_digits) - 1;
    ResetXPos();
}

void ResetXPos() {
    distance_meter.pos.x = WINDOW_WIDTH -
            (distance_meter.dest_width * (distance_meter.max_digits + 1));
}

void DrawDistanceMeterDigit(int digit_pos, int value, bool opt_high_score) {
    int source_x = distance_meter.width * value;
    int source_y = 0;
    int target_x = digit_pos * distance_meter.dest_width;
    int target_y = distance_meter.pos.y;
    int offset_x = distance_meter.pos.x;

    source_x += distance_meter.sprite_def.x;
    source_y += distance_meter.sprite_def.y;

    if (opt_high_score) {
        SetTextureAlpha(0, 0.8);
        offset_x -= (distance_meter.max_digits + 2) * distance_meter.width;
    }

    Texture texture = {
        .id = 0,
        .source = {
            .x = source_x,
            .y = source_y,
            .width = distance_meter.width,
            .height = distance_meter.height
        },
        .destination = {
            .x = target_x + offset_x,
            .y = target_y,
            .width = distance_meter.width,
            .height = distance_meter.height
        }
    };
    DrawTexture(&texture);

    if (opt_high_score) {
        SetTextureAlpha(0, 1);
    }
}

bool UpdateDistanceMeter(uint32_t delta_time, double distance) {
    bool paint = true;
    bool play_sound = false;

    if (!achievement) {
        int actual_distance = GetActualDistance(distance);

        if (actual_distance > distance_meter.max_score) {
            // score has gone beyond the initial digit count
            ++distance_meter.max_digits;
            distance_meter.max_score = distance_meter.max_score * 10 + 9;
            ResetXPos();
        }

        if (actual_distance > 0) {
            if (actual_distance % ACHIEVEMENT_DISTANCE == 0) {
                achievement = true;
                play_sound = true;
            }
        }

        last_distance = actual_distance;
    } else {
        if (flash_iterations <= DISTANCE_FLASH_ITERATIONS) {
            flash_timer += delta_time;
            if (flash_timer < DISTANCE_FLASH_DURATION) {
                paint = false;
            } else if (flash_timer > DISTANCE_FLASH_DURATION * 2) {
                flash_timer = 0;
                ++flash_iterations;
            }
        } else {
            achievement = false;
            flash_iterations = 0;
            flash_timer = 0;
        }
    }

    if (paint) {
        DrawScore(last_distance, false);
    }

    if (high_score) {
        DrawHighScore();
    }

    return play_sound;
}

void DrawScore(int digits, bool opt_max_score) {
    for (int i = distance_meter.max_digits - 1; i >= 0; --i) {
        int digit = 0;
        if (digits != 0) {
            digit = digits % 10;
            digits /= 10;
        }
        DrawDistanceMeterDigit(i, digit, opt_max_score);
    }
}

void DrawHighScore() {
    DrawDistanceMeterDigit(-3, 10, true); // H
    DrawDistanceMeterDigit(-2, 11, true); // I
    DrawDistanceMeterDigit(-1, 12, true); // space
    DrawScore(high_score, true);
}

int GetActualDistance(double distance) {
    return distance ? (int)(distance * DISTANCE_COEFFICIENT) : 0;
}

void SetDistanceMeterHighScore(int score) {
    high_score = GetActualDistance(score);
}

void ResetDistanceMeter() {
    achievement = false;
    flash_iterations = 0;
    flash_timer = 0;
    last_distance = 0;
}