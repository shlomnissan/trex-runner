// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdbool.h>
#include <stdio.h>
#include <SDL_mixer.h>

#include "sounds.h"

#define MAX_SOUND_EFFECTS 3

Mix_Chunk* sound_effects[MAX_SOUND_EFFECTS] = {NULL};

int last_sound_id = 0;
int mixer_chunk_size = 1024;

bool did_init_mixer = false;

void InitializeMixer() {
    if (Mix_OpenAudio(
            MIX_DEFAULT_FREQUENCY,
            MIX_DEFAULT_FORMAT,
            MIX_DEFAULT_CHANNELS,
            mixer_chunk_size
            ) == -1) {
        printf("Unable to initialize mixer. Audio will not be supported!\n");
        return;
    }
    did_init_mixer = true;
}

int LoadSoundEffect(char* path) {
    if (did_init_mixer) {
        sound_effects[last_sound_id] = Mix_LoadWAV(path);
        if (sound_effects[last_sound_id] != NULL) {
        } else {
            printf("Unable to load sound fx %s\n", path);
            return -1;
        }
    } else {
        printf("Sound fx is not loaded, the mixer must be initialized first.\n");
        return -1;
    }
    return last_sound_id++;
}

void PlaySound(SoundFX sfx_id) {
    if (sound_effects[sfx_id] != NULL) {
        Mix_PlayChannel(-1, sound_effects[sfx_id], 0);
    }
}

void FreeSoundEffects() {
    for (int i = 0; i < MAX_SOUND_EFFECTS; ++i) {
        if (sound_effects[i] != NULL) {
            Mix_FreeChunk(sound_effects[i]);
            sound_effects[i] = NULL;
        }
    }
}

void DeinitMixer() {
    Mix_CloseAudio();
}