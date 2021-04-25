// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_T_REX_H
#define TREX_RUNNER_T_REX_H

#include <stdint.h>

#include "sys/graphics.h"

void InitTRex();

void UpdateTRex(uint32_t delta_time);

void DrawTRex();

CollisionSet GetTRexCollisionSet();

#endif  // TREX_RUNNER_T_REX_H
