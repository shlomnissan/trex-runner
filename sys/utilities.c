// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdlib.h>

#include "utilities.h"

int RandomFromRange(Range range) {
    return range.min + rand() % (range.max - range.min);
}
