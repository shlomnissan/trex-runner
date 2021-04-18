// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "graphics.h"
#include "window.h"

#define TEXTURES_LEN 10

uint32_t last_texture_id = 0;
SDL_Texture* textures[TEXTURES_LEN] = {NULL};

SDL_Rect SDLRectFromFrame(Frame frame);

int32_t LoadTexture(char* filename) {
    if (last_texture_id == TEXTURES_LEN) {
        printf("Unable to load %s. There's no more room left in the textures array.", filename);
        return -1;
    }
    SDL_Renderer* renderer = GetRenderer();
    if (renderer == NULL) {
        printf("Unable to load %s. The window wasn't initialized.\n", filename);
        return -1;
    }
    SDL_Surface* surface = IMG_Load(filename);
    if (surface == NULL) {
        printf("Unable to open the file %s.\n", filename);
        return -1;
    }
    textures[last_texture_id] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return last_texture_id++;
}

void DrawTexture(Texture* texture) {
    SDL_Renderer* renderer = GetRenderer();
    if (renderer == NULL) {
        printf("Unable to draw texture. The window wasn't initialized.\n");
        return;
    }
    SDL_Rect source = SDLRectFromFrame(texture->source);
    SDL_Rect destination = SDLRectFromFrame(texture->destination);
    SDL_RenderCopy(renderer, textures[texture->id], &source, &destination);
}

void DestroyTextures() {
    uint32_t len = last_texture_id;
    for (int i = 0; i < len; ++i) {
        if (textures[i] != NULL) {
            SDL_DestroyTexture(textures[i]);
            textures[i] = NULL;
            --last_texture_id;
        }
    }
}

SDL_Rect SDLRectFromFrame(Frame frame) {
    SDL_Rect output = {
        x: frame.x,
        y: frame.y,
        w: frame.width,
        h: frame.height
    };
    return output;
}