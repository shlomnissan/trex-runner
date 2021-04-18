// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUN_T_REX_H
#define TREX_RUN_T_REX_H

#include <stdint.h>

void InitTRex();

void UpdateTRex(uint32_t delta_time);

void DrawTRex();

#endif  // TREX_RUN_T_REX_H
