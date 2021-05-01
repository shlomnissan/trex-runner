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

void AddObstacle(double speed);
void UpdateObstacles(uint32_t delta_time, double speed);
bool ShouldAddObstacle(Obstacle* last_obstacle);

void InitHorizon() {
    InitHorizonLine();
    AddCloud();
}

void UpdateHorizon(uint32_t delta_time, double speed, bool has_obstacles) {
    UpdateHorizonLine(delta_time, speed);
    UpdateClouds(delta_time, speed);

    if (has_obstacles) {
        UpdateObstacles(delta_time, speed);
    }
}

void DrawHorizon() {
    DrawHorizonLine();

    for (int i = 0; i < MAX_CLOUD_LENGTH; ++i) {
        if (clouds[i] != NULL && clouds[i]->is_visible) {
            DrawCloud(clouds[i]);
        }
    }
    for (int i = 0; i < MAX_OBSTACLE_LENGTH; ++i) {
        if (obstacles[i] != NULL && obstacles[i]->is_visible) {
            DrawObstacle(obstacles[i]);
        }
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

    for (int i = 0; i < MAX_CLOUD_LENGTH; ++i) {
        if (clouds[i] != NULL) {
            UpdateCloud(clouds[i], this_speed);

            if (!clouds[i]->is_visible) {
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

void AddObstacle(double speed) {
    ++obstacle_last_idx;

    if (obstacle_last_idx == MAX_OBSTACLE_LENGTH) obstacle_last_idx = 0;
    if (obstacles[obstacle_last_idx] != NULL) return;

    int obstacle_type_index = rand() % MAX_OBSTACLE_LENGTH;
    obstacles[obstacle_last_idx] = MakeObstacle(obstacle_type_index, speed);
    ++obstacle_count;
}

void UpdateObstacles(uint32_t delta_time, double speed) {
    for (int i = 0; i < MAX_OBSTACLE_LENGTH; ++i) {
        if (obstacles[i] != NULL) {
            UpdateObstacle(obstacles[i], delta_time, speed);

            if (!obstacles[i]->is_visible) {
                free(obstacles[i]);
                --obstacle_count;
                obstacles[i] = NULL;
            }
        }
    }

    if (obstacle_count > 0) {
        Obstacle* last_obstacle = obstacles[obstacle_last_idx];
        if (ShouldAddObstacle(last_obstacle)) {
            AddObstacle(speed);
            last_obstacle->following_obstacle_created = true;
        }
    } else {
        AddObstacle(speed);
    }
}

bool ShouldAddObstacle(Obstacle* last_obstacle) {
    return last_obstacle != NULL &&
        !last_obstacle->following_obstacle_created &&
        last_obstacle->pos.x + last_obstacle->width + last_obstacle->gap < WINDOW_WIDTH;
}

CollisionSet GetNearestObstacleCollisionSet() {
    Obstacle* nearest = NULL;
    int min_x = INT32_MAX;
    for (int i = 0; i < MAX_OBSTACLE_LENGTH; ++i) {
        if (obstacles[i] != NULL && obstacles[i]->is_visible) {
            if (obstacles[i]->pos.x < min_x) {
                nearest = obstacles[i];
                min_x = nearest->pos.x;
            }
        }
    }

    CollisionSet collision_set = {.len = 0, .rects = {}};
    if (nearest == NULL) return collision_set;

    collision_set = nearest->type.collision_boxes;
    for (int i = 0; i < collision_set.len; ++i) {
        collision_set.rects[i].x += nearest->pos.x;
        collision_set.rects[i].y += nearest->pos.y;
    }

    return collision_set;
}

void ResetHorizon() {
    for (int i = 0; i < MAX_OBSTACLE_LENGTH; ++i) {
        if (obstacles[i] != NULL) {
            free(obstacles[i]);
            obstacles[i] = NULL;
        }
    }
    obstacle_count = 0;
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