// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "trex.h"

#include "core/keyboard.h"
#include "core/sprite_animated.h"
#include "game/shared.h"

const double kXPos = 50.0;
const double kYpos = 93.0;
const double kInitialJumpVelocity = -10.0;
const double kGravity = 0.6;
const double kMinJumpPosition = kYpos - 35;
const double kDropCoefficient = 3.0;

TRex::TRex(Events* events) : Entity(events) {
    auto sprite = std::make_unique<SpriteAnimated>(
        "spritesheet",
        Vector2 {
            .x = 0,
            .y = kYpos,
        },
        /* fps = */ 12
    );

    sprite->AddAnimation("idle", {
        "trex_idle_0"
    });

    sprite->AddAnimation("blink", {
        "trex_blink_0"
    });

    sprite->AddAnimation("jumping", {
        "trex_idle_0"
    });

    sprite->AddAnimation("ducking", {
        "trex_ducking_0",
        "trex_ducking_1"
    });

    sprite->AddAnimation("running", {
        "trex_running_0",
        "trex_running_1"
    });

    sprite->AddAnimation("crashed", {
        "trex_crashed"
    });

    sprite->SetAnimation("idle");

    sprites_.emplace_back(std::move(sprite));
    blink_time_ = blink_rand_();
}

auto TRex::Update(const double dt, const Keyboard &keyboard) -> void {
    Entity::Update(dt, keyboard);

    auto sprite = dynamic_cast<SpriteAnimated*>(sprites_.front().get());
    if (!sprite) return;

    if (did_start_game_ && sprite->x < kXPos) {
        // intro, move dino in from the left
        sprite->x += ceil(kXPos / kIntroDuration * dt);
    }

    if (state_ == TRexState::Idle) {
        Blink(dt, sprite);
    }

    if (state_ == TRexState::Jumping) {
        UpdateJump(dt, sprite);
    }

    UpdateAnimation(sprite);
    HandleKeys(keyboard);
}

auto TRex::Blink(const double dt, SpriteAnimated* sprite) -> void {
    blink_time_ -= static_cast<int>(dt);

    const auto curr_anim = sprite->curr_animation();
    if (blink_time_ < 0) {
        if (curr_anim == "idle") {
            sprite->SetAnimation("blink");
            blink_time_ = 100;
        }
        if (curr_anim == "blink") {
            sprite->SetAnimation("idle");
            blink_time_ = blink_rand_();
        }
    }
}

auto TRex::SetStartCallback(std::function<void()> f) -> void {
    start_callback_ = std::move(f);
}

auto TRex::HandleKeys(const Keyboard& keyboard) -> void {
    using enum TRexState;
    if (state_ == Crashed) {
        return;
    }

    // start ducking
    if (state_ == Running && IsDuckKeyDown(keyboard)) {
        state_ = Ducking;
    }

    // end ducking
    if (state_ == Ducking && !IsDuckKeyDown(keyboard)) {
        state_ = Running;
    }

    // start jumping
    if ((state_ == Running || state_ == Idle) && IsJumpKeyDown(keyboard)) {
        events_->Publish("on_play_sound", "jump");
        state_ = Jumping;
        vertical_velocity_ = kInitialJumpVelocity;
    }

    // shorten jump
    if (state_ == Jumping && !IsJumpKeyDown(keyboard)) {
        ShortenJump();
    }

    // cancel jump
    if (state_ == Jumping && IsDuckKeyDown(keyboard) && !cancel_jump_) {
        cancel_jump_ = true;
        vertical_velocity_ = 1;
    }
}

auto TRex::IsJumpKeyDown(const Keyboard& keyboard) const -> bool {
    return keyboard.IsKeyPressed(Key::Space) ||
           keyboard.IsKeyPressed(Key::Up);
}

auto TRex::IsDuckKeyDown(const Keyboard& keyboard) const -> bool {
    return keyboard.IsKeyPressed(Key::Down);
}

auto TRex::UpdateJump(const double dt, SpriteAnimated* sprite) -> void {
    auto offset = dt / (1000.0 / kFPS);

    if (cancel_jump_) {
        sprite->y += vertical_velocity_ * kDropCoefficient * offset;
    } else {
        sprite->y += vertical_velocity_ * offset;
    }

    vertical_velocity_ += kGravity * offset;

    if (sprite->y <= kMinJumpPosition) {
        reached_min_height_ = true;
    }

    if (sprite->y >= kYpos) {
        if (!did_start_game_) {
            start_callback_();
            did_start_game_ = true;
        }
        Reset();
    }
}

auto TRex::ShortenJump() -> void {
    // if the sprite is traveling upwards at a rate faster than half of the
    // initial velocity, set the vertical velocity to that value. the sprite
    // will continue moving upwards, but it will reach its peak and start
    // descending at a faster rate
    if (reached_min_height_ && vertical_velocity_ < kInitialJumpVelocity / 2) {
        vertical_velocity_ = kInitialJumpVelocity / 2;
    }
}

auto TRex::Crash() -> void {
    state_ = TRexState::Crashed;
}

auto TRex::UpdateAnimation(SpriteAnimated* sprite) -> void {
    using enum TRexState;

    if (state_ != prev_state_) {
        if (state_ == Running) {
            sprite->SetAnimation("running");
        }
        if (state_ == Jumping) {
            sprite->SetAnimation("jumping");   
        }
        if (state_ == Ducking) {
            sprite->SetAnimation("ducking");
        }
        if (state_ == Crashed) {
            sprite->SetAnimation("crashed");
        }
        prev_state_ = state_;
    }
}

auto TRex::Reset() -> void {
    sprites_.front()->y = kYpos;
    state_ = TRexState::Running;
    vertical_velocity_ = 0;
    reached_min_height_ = false;
    cancel_jump_ = false;
}