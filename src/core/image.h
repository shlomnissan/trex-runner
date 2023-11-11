// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <stdexcept>
#include <string_view>

class Image {
public:
    explicit Image(std::string_view filename);

    // delete move/copy constructor and assignement operators
    Image(const Image&) = delete;
    Image(Image&&) noexcept = delete;
    auto operator=(const Image&) = delete;
    auto operator=(Image&& rhs) noexcept -> Image& = delete;

    auto width() const { return width_; }
    auto height() const { return height_; }
    auto bpp() const { return bytes_per_pixel_; }
    auto data() const { return data_; }

    ~Image();

private:
    int width_;
    int height_;
    int bytes_per_pixel_;
    unsigned char* data_ {nullptr};
};

struct ImageError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};