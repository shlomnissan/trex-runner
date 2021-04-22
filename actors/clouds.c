// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdlib.h>
#include <math.h>

#include "clouds.h"
#include "globals.h"
#include "sys/graphics.h"
#include "spritesheet.h"

Range cl_sky_level = {
    .min = 30,
    .max = 71
};

Range cl_cloud_gap = {
    .min = 100,
    .max = 400
};

Point cl_sprite_def = {
    .x = -1,
    .y = -1
};

Cloud* clouds[MAX_CLOUDS] = {NULL};
int last_cloud = -1;
int cloud_count = 0;

int cl_width = 46;
int cl_height = 14;

double cl_speed = 0.2;

int RandomFromRange(Range range);

void AddCloud() {
    ++last_cloud;
    if (last_cloud == MAX_CLOUDS) last_cloud = 0;
    if (clouds[last_cloud] != NULL) return;

    // initialize sprite definition if needed
    if (cl_sprite_def.x == -1 && cl_sprite_def.y == -1) {
        cl_sprite_def = sprite_definitions[CLOUD];
    }

    // allocate memory for new cloud
    Cloud* cloud = (Cloud*) malloc(sizeof(Cloud));
    cloud->pos.x = WINDOW_WIDTH;
    cloud->pos.y = RandomFromRange(cl_sky_level);
    cloud->cloud_gap = RandomFromRange(cl_cloud_gap);
    clouds[last_cloud] = cloud;
    cloud_count++;
}

void UpdateClouds(uint32_t delta_time, double speed) {
    double cloud_speed = ceil(cl_speed / 1000 * delta_time * speed);
    for (int i = 0; i < MAX_CLOUDS; ++i) {
        if (clouds[i] != NULL) {
            clouds[i]->pos.x -= cloud_speed;

            // remove cloud when it's out of screen
            if (clouds[i]->pos.x + cl_width < 0) {
                --cloud_count;
                free(clouds[i]);
                clouds[i] = NULL;
            }
        }
    }
}

void DrawClouds() {
    for (int i = 0; i < MAX_CLOUDS; ++i) {
        if (clouds[i] != NULL) {
            Texture texture = {
                    .id = 0,
                    .source = {
                            .x = cl_sprite_def.x,
                            .y = cl_sprite_def.y,
                            .width = cl_width,
                            .height =  cl_height
                    },
                    .destination = {
                            .x = clouds[i]->pos.x,
                            .y = clouds[i]->pos.y,
                            .width = cl_width,
                            .height = cl_height
                    }
            };
            DrawTexture(&texture);
        }
    }
}

void DestroyClouds() {
    for (int i = 0; i < MAX_CLOUDS; ++i) {
        if (clouds[i] != NULL) {
            free(clouds[i]);
        }
    }
}

int RandomFromRange(Range range) {
    return range.min + rand() % (range.max - range.min);
}