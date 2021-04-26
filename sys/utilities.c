// Copyright 2021 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <stdlib.h>

#include "utilities.h"

int RandomFromRange(Range range) {
    return range.min + rand() % (range.max - range.min);
}

bool RectanglesIntersect(Rectangle* rect_a, Rectangle* rect_b) {
    return rect_a->x < rect_b->x + rect_b->width &&
           rect_b->x < rect_a->x + rect_a->width &&
           rect_a->y < rect_b->y + rect_b->height &&
           rect_b->y < rect_a->y + rect_a->height;
}
