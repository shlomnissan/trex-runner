// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "events.h"

Events* Events::instance_ {nullptr};
std::mutex Events::mutex_;

auto Events::GetInstance() -> Events* {
    std::lock_guard lock(mutex_);
    if (instance_ == nullptr) {
        instance_ = new Events();
    }
    return instance_;
}