// Copyright 2023 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "audio.h"

#include <cstdint>
#include <fstream>

#include "fmt/format.h"

Audio::Audio() {
    if (!(SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO)) {
        throw AudioError {"The SDL audio subsystem was not initialized"};
    }
}

auto Audio::LoadAudio(std::string_view path, std::string_view id) -> void {
    std::ifstream audio_file {path.data()};
    if (!audio_file.is_open()) {
        throw AudioError {
            fmt::format("Unable to load audio file {}", path)
        };
    }

    auto spec = SDL_AudioSpec{};
    uint8_t* start;
    uint32_t length;
    if (SDL_LoadWAV(path.data(), &spec, &start, &length) == nullptr) {
        throw AudioError {
            fmt::format("SDL failed to load audio file {}", path)
        };
    }
    store[std::string{id}] = Sound{start, length};

    if (device == 0) {
        // this code assumes the spec is the same for all audio files
        device = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, 0);
        if (device == 0) {
            throw AudioError {
                fmt::format("SDL failed to open an audio device {}", id)
            };
        }
    }
}

auto Audio::PlayAudio(std::string_view id) -> void {
    auto key = std::string{id};
    if (!store.contains(key)) {
        throw AudioError {
            fmt::format("Failed to play audio, missing audio ID {}", id)
        };
    }
    SDL_QueueAudio(device, store[key].first, store[key].second);
    SDL_PauseAudioDevice(device, 0);
}

Audio::~Audio() {
    SDL_CloseAudioDevice(device);
    for (auto& [_key, sound] : store) {
        SDL_FreeWAV(sound.first);
    }
}