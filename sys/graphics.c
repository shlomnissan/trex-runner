// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"
#include "window.h"

#define MAX_TEXTURES 10

uint32_t last_texture_id = 0;
SDL_Texture* textures[MAX_TEXTURES] = {NULL};

SDL_Rect SDLRectFromFrame(Rectangle frame);

int32_t LoadTexture(char* filename) {
    if (last_texture_id == MAX_TEXTURES) {
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
        printf("Unable to draw texture. The renderer wasn't initialized.\n");
        return;
    }
    SDL_Rect source = SDLRectFromFrame(texture->source);
    SDL_Rect destination = SDLRectFromFrame(texture->destination);
    SDL_RenderCopy(renderer, textures[texture->id], &source, &destination);
}

void DrawRectangle(Rectangle* rect, RGB color, bool fill) {
    SDL_Renderer* renderer = GetRenderer();
    if (renderer == NULL) {
        printf("Unable to draw rectangle. The renderer wasn't initialized.\n");
        return;
    }
    SDL_Rect r = {
        .x = rect->x, .y = rect->y,
        .w = rect->width, .h = rect->height
    };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    fill ? SDL_RenderFillRect(renderer, &r) :
           SDL_RenderDrawRect(renderer, &r);
}

void SetTextureAlpha(int texture_id, double alpha) {
    SDL_SetTextureAlphaMod(textures[texture_id], alpha * 255);
}

void DrawCollisionSet(CollisionSet* collision_set, RGB color) {
    for (int i = 0; i < collision_set->len; ++i) {
        DrawRectangle(&collision_set->rects[i], color, false);
    }
}

RGB HexToRGB(int hex_value) {
    RGB rgb;
    rgb.r = ((hex_value >> 16) & 0xFF);
    rgb.g = ((hex_value >> 8) & 0xFF);
    rgb.b = hex_value & 0xFF;
    return rgb;
}

void FreeTextures() {
    for (int i = 0; i < MAX_TEXTURES; ++i) {
        if (textures[i] != NULL) {
            SDL_DestroyTexture(textures[i]);
            textures[i] = NULL;
        }
    }
}

SDL_Rect SDLRectFromFrame(Rectangle frame) {
    SDL_Rect output = {
        x: frame.x,
        y: frame.y,
        w: frame.width,
        h: frame.height
    };
    return output;
}