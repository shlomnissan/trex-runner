// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "game.h"

#include "core/resource_manager.h"
#include "core/timer.h"

Game::Game(std::string_view title, int width, int height)
 : width_(width),
   height_(height),
   window_(title, width_, height_),
   keyboard_(events_)
{
    window_.SetEvents(&events_);
    events_.AddEventListener<OnQuit>("on_quit", [this](){
        running_ = false;
    });

    events_.AddEventListener<OnPlaySound>(
        "on_play_sound", [this](std::string_view sound){
            audio_.PlayAudio(sound);
        }
    );
}

auto Game::LoadAudio(std::string_view path, std::string_view id) -> void {
    audio_.LoadAudio(path, id);
}

auto Game::LoadSpritesheet(const std::string& id, const SpritesheetFiles& files) const -> void {
    ResourceManager::LoadSpritesheet(id, files);
}

auto Game::GetEvents() -> Events* {
    return &events_;
}

auto Game::Start(std::unique_ptr<Stage> scene) -> void {
    SetScene(std::move(scene));

    // game loop
    Timer timer_frame_delta;
    while (running_) {
        auto delta = static_cast<double>(timer_frame_delta.GetMilliseconds());
        timer_frame_delta.Reset();
        window_.ClearScreen();
        for (const auto entity : curr_stage_->entities()) {
            for (const auto& sprite : entity->sprites()) {
                if (sprite == nullptr) continue;
                DrawSprite(sprite.get());
            }
        }
        curr_stage_->Update(delta, keyboard_);
        window_.DrawScreen(curr_stage_->clip_frame());
    }
}

auto Game::DrawSprite(const Sprite* sprite) -> void {
    auto& spritesheet = ResourceManager::GetSpritesheet(sprite->spritesheet_id());
    auto frame = spritesheet.GetFrame(sprite->frame_id());
    window_.DrawImage(
        spritesheet.image(),
        frame,
        {
            .x = static_cast<int>(sprite->x),
            .y = static_cast<int>(sprite->y),
            .width = frame.width,
            .height = frame.height
        },
        sprite->alpha
    );

#if DRAW_COLLISION_FRAMES == 1
    auto collision_rects = spritesheet.GetCollisionFrames(sprite->frame_id());
    if (!collision_rects.empty()) {
        for (auto& rect : collision_rects) {
            rect.x += static_cast<int>(sprite->x);
            rect.y += static_cast<int>(sprite->y);
            window_.DrawRectangle(rect);
        }
    }
#endif
}

auto Game::SetScene(std::unique_ptr<Stage> scene) -> void {
    curr_stage_ = std::move(scene);
    curr_stage_->Init();
}