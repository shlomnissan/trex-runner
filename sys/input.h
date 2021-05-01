// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#ifndef TREX_RUNNER_INPUT_H
#define TREX_RUNNER_INPUT_H

#include <stdbool.h>

#define KEY_SPACE 32
#define KEY_UP 82
#define KEY_DOWN 81

void PollEvents(void (*on_quit)());

bool IsKeyDown(char key);

void SetOnKeyUp(void (*on_key_up)(char key));

#endif  // TREX_RUNNER_INPUT_H
