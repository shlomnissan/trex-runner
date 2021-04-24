// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdlib.h>

#include "clouds.h"
#include "globals.h"
#include "spritesheet.h"
#include "sys/graphics.h"

Range cloud_sky_level_range = {
    .min = CLOUD_SKY_LEVEL_MIN,
    .max = CLOUD_SKY_LEVEL_MAX
};

Range cloud_gap_range = {
    .min = CLOUD_GAP_MIN,
    .max = CLOUD_GAP_MAX
};

Point cloud_sprite_def = {
    .x = -1,
    .y = -1
};

int cloud_width = 46;
int cloud_height = 14;

int RandomFromRange(Range range);

Cloud* MakeCloud() {
    // initialize sprite definition if needed
    if (cloud_sprite_def.x == -1 && cloud_sprite_def.y == -1) {
        cloud_sprite_def = sprite_definitions[CLOUD];
    }

    // allocate memory for new cloud
    Cloud* cloud = (Cloud*) malloc(sizeof(Cloud));

    cloud->pos.x = WINDOW_WIDTH;
    cloud->pos.y = RandomFromRange(cloud_sky_level_range);
    cloud->cloud_gap = RandomFromRange(cloud_gap_range);
    cloud->is_visible = true;

    return cloud;
}

void UpdateCloud(Cloud* cloud, double speed) {
    cloud->pos.x -= speed;
    if (cloud->pos.x + cloud_width < 0) {
        cloud->is_visible = false;
    }
}

void DrawCloud(Cloud* cloud) {
    Texture texture = {
            .id = 0,
            .source = {
                    .x = cloud_sprite_def.x,
                    .y = cloud_sprite_def.y,
                    .width = cloud_width,
                    .height =  cloud_height
            },
            .destination = {
                    .x = cloud->pos.x,
                    .y = cloud->pos.y,
                    .width = cloud_width,
                    .height = cloud_height
            }
    };
    DrawTexture(&texture);
}

int RandomFromRange(Range range) {
    return range.min + rand() % (range.max - range.min);
}