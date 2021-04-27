// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "game_over_panel.h"
#include "sys/utilities.h"
#include "sys/graphics.h"
#include "spritesheet.h"
#include "globals.h"

typedef struct {
    Point text_pos;
    int text_width;
    int text_height;
    int restart_width;
    int restart_height;
} GameOverPanel;

GameOverPanel game_over_panel = {
    .text_pos = {
        .x = 0,
        .y = 13
    },
    .text_width = 191,
    .text_height = 11,
    .restart_width = 36,
    .restart_height = 32
};

void DrawGameOverPanel() {
    int text_source_x = game_over_panel.text_pos.x;
    int text_source_y = game_over_panel.text_pos.y;
    int text_target_x = (WINDOW_WIDTH - game_over_panel.text_width) >> 1;
    int text_target_y = (WINDOW_HEIGHT - 25) / 3;
    text_source_x += sprite_definitions[TEXT_SPRITE].x;
    text_source_y += sprite_definitions[TEXT_SPRITE].y;

    Texture text_texture = {
        .id = 0,
        .source = {
            text_source_x,
            text_source_y,
            game_over_panel.text_width,
            game_over_panel.text_height
        },
        .destination = {
            text_target_x,
            text_target_y,
            game_over_panel.text_width,
            game_over_panel.text_height
        }
    };
    DrawTexture(&text_texture);

    int restart_target_x = (WINDOW_WIDTH - game_over_panel.restart_width) >> 1;
    int restart_target_y = WINDOW_HEIGHT >> 1;

    Texture restart_texture = {
        .id = 0,
        .source = {
            sprite_definitions[RESTART].x,
            sprite_definitions[RESTART].y,
            game_over_panel.restart_width,
            game_over_panel.restart_height
        },
        .destination = {
            restart_target_x,
            restart_target_y,
            game_over_panel.restart_width,
            game_over_panel.restart_height
        }
    };
    DrawTexture(&restart_texture);
}
