// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUN_GRAPHICS_H
#define TREX_RUN_GRAPHICS_H

#include <stdint.h>

typedef struct {
   int x;
   int y;
} Point;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Frame;

typedef struct {
    int id;
    Frame source;
    Frame destination;
} Texture;

typedef struct {
    int frames[10];
    int len;
    int ms_per_frame;
} AnimFrame;

int32_t LoadTexture(char* filename);

void DrawTexture(Texture* texture);

void DestroyTextures();

#endif  // TREX_RUN_GRAPHICS_H
