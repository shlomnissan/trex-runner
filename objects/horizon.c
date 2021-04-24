// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdlib.h>
#include <math.h>

#include "horizon.h"
#include "horizon_line.h"
#include "clouds.h"
#include "obstacle.h"

Cloud* clouds[MAX_CLOUD_LENGTH] = {NULL};
Obstacle* obstacles[MAX_OBSTACLE_LENGTH] = {NULL};

int cloud_last_idx = -1;
int obstacle_last_idx = -1;

int cloud_count = 0;
int obstacle_count = 0;

double cloud_speed = 0.2;

void AddCloud();
void UpdateClouds(uint32_t delta_time, double speed);

void AddObstacle();
void UpdateObstacles(uint32_t delta_time, double speed);

void InitHorizon() {
    InitHorizonLine();
    AddCloud();
}

void UpdateHorizon(uint32_t delta_time, double speed) {
    UpdateHorizonLine(delta_time, speed);
    UpdateClouds(delta_time, speed);
    UpdateObstacles(delta_time, speed);
}

void DrawHorizon() {
    DrawHorizonLine();

    // TODO: remove drawing test
    if (obstacles[0] != NULL) {
        DrawObstacle(obstacles[0]);
    }
}

void AddCloud() {
    ++cloud_last_idx;

    if (cloud_last_idx == MAX_CLOUD_LENGTH) cloud_last_idx = 0;
    if (clouds[cloud_last_idx] != NULL) return;

    clouds[cloud_last_idx] = MakeCloud();
    ++cloud_count;
}

void UpdateClouds(uint32_t delta_time, double speed) {
    double this_speed = ceil(cloud_speed / 1000 * delta_time * speed);

    // update clouds
    for (int i = 0; i < MAX_CLOUD_LENGTH; ++i) {
        if (clouds[i] != NULL) {
            // run update
            UpdateCloud(clouds[i], this_speed);

            if (clouds[i]->is_visible) {
                DrawCloud(clouds[i]);
            } else {
                free(clouds[i]);
                --cloud_count;
                clouds[i] = NULL;
            }
        }
    }

    // check for adding a new cloud
    Cloud* last = clouds[cloud_last_idx];
    if (
        cloud_count < MAX_CLOUD_LENGTH &&
        (WINDOW_WIDTH - last->pos.x) > last->cloud_gap &&
        rand() % 10 > CLOUDS_FREQUENCY
    ) {
        AddCloud();
    }
}

void AddObstacle() {
    ++obstacle_last_idx;

    if (obstacle_last_idx == MAX_OBSTACLE_LENGTH) obstacle_last_idx = 0;
    if (obstacles[obstacle_last_idx] != NULL) return;

    int obstacle_type_index = rand() % MAX_OBSTACLE_LENGTH;
    obstacles[obstacle_last_idx] = MakeObstacle(obstacle_type_index);
    ++obstacle_count;
}

void UpdateObstacles(uint32_t delta_time, double speed) {
    // TODO: update individual obstacles

    if (obstacle_count > 0) {
        // TODO: add obstacles if needed
    } else {
        AddObstacle();
    }
}

void FreeHorizonResources() {
    // free cloud resources
    for (int i = 0; i < MAX_CLOUD_LENGTH; ++i) {
        if (clouds[i] != NULL) {
            free(clouds[i]);
        }
    }
    // free obstacle resources
    for (int i = 0; i < MAX_OBSTACLE_LENGTH; ++i) {
        if (obstacles[i] != NULL) {
            free(obstacles[i]);
        }
    }
}