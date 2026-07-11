#include "./resource.hpp"
#include <format>
#include "raylib.h"

namespace cfu::res {

// TODO: implement audio resources

CfuMusic::CfuMusic(std::string_view path) {
    auto final_path = std::format("assets/music/{}", path);
    this->music = LoadMusicStream(final_path.c_str());
}

CfuMusic::CfuMusic(CfuMusic&& other) noexcept : music(other.music) {
    other.music = {};
}

auto CfuMusic::operator=(CfuMusic&& other) noexcept -> CfuMusic& {
    this->music = other.music;
    other.music = {};
    return *this;
}

CfuMusic::~CfuMusic() {
    if (IsMusicValid(this->music)) UnloadMusicStream(this->music);
}

CfuMusic::operator Music() {
    return music;
}

CfuSound::CfuSound(std::string_view path) {
    auto final_path = std::format("assets/sounds/{}", path);
    this->sound = LoadSound(final_path.c_str());
}

CfuSound::CfuSound(CfuSound&& other) noexcept : sound(other.sound) {
    other.sound = {};
}

auto CfuSound::operator=(CfuSound&& other) noexcept -> CfuSound& {
    this->sound = other.sound;
    other.sound = {};
    return *this;
}

CfuSound::~CfuSound() {
    if (IsSoundValid(this->sound)) UnloadSound(this->sound);
}

CfuSound::operator Sound() {
    return sound;
}

} // namespace cfu::res
