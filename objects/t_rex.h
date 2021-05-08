// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_T_REX_H
#define TREX_RUNNER_T_REX_H

#include <stdint.h>

#include "sys/graphics.h"

typedef enum {
    T_REX_RUNNING = 1,
    T_REX_JUMPING,
    T_REX_DUCKING,
    T_REX_HIT
} TRexState;

void InitTRex();

void UpdateTRex(uint32_t delta_time);

void SetTRexState(TRexState state);

void DrawTRex();

void ResetTRex();

Rectangle GetTRexFrame();

CollisionSet GetTRexCollisionSet();

#endif  // TREX_RUNNER_T_REX_H
