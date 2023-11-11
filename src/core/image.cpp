// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "image.h"

#include <fmt/format.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(std::string_view filename) {
    data_ = stbi_load(
        filename.data(),
        &width_, &height_,
        &bytes_per_pixel_, 0
    );

    if (data_ == nullptr) {
        throw ImageError {fmt::format("Unable to load image {}", filename)};
    }
}

Image::~Image() {
    stbi_image_free(data_);
}