// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_SOUNDS_H
#define TREX_RUNNER_SOUNDS_H

typedef enum {
    SFX_HIT = 0,
    SFX_PRESS,
    SFX_REACHED
} SoundFX;

void InitializeMixer();

int LoadSoundEffect(char* path);

void PlaySound(SoundFX sfx_id);

void FreeSoundEffects();

void DeinitMixer();

#endif  // TREX_RUNNER_SOUNDS_H
