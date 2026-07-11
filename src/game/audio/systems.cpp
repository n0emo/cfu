#include "./systems.hpp"
#include "audio/components.hpp"
#include "audio/resource.hpp"
#include "physics/components.hpp"
#include "player/components.hpp"
#include "raylib.h"
#include "raymath.h"
#include <entt/entity/registry.hpp>
#include <gsl/zstring>

namespace cfu::systems {

auto setup_audio(entt::registry& registry) -> void {
    InitAudioDevice();
    registry.ctx().insert_or_assign(res::MusicCache {});
    registry.ctx().insert_or_assign(res::SoundCache {});
    reload_audio(registry);
}

auto destroy_audio() -> void {
    CloseAudioDevice();
}

auto reload_single_music(res::MusicCache& cache, res::music::MusicId id, gsl::czstring path) -> void {
    auto [it, loaded] = cache.load(id, path);
    if (!loaded) *it->second.handle() = res::CfuMusic(path);
}

auto reload_music(entt::registry& registry) -> void {
    auto& cache = registry.ctx().get<res::MusicCache>();
    #define CFU_X(name, path) reload_single_music(cache, res::music::name, path);
    RES_MUSIC_ID_LIST
    #undef CFU_X
}

static auto reload_single_sound(res::SoundCache& cache, res::sounds::SoundId id, gsl::czstring path) -> void {
    auto [it, loaded] = cache.load(id, path);
    if (!loaded) *it->second.handle() = res::CfuSound(path);
}

auto reload_sound(entt::registry& registry) -> void {
    auto& cache = registry.ctx().get<res::SoundCache>();
    #define CFU_X(name, path) reload_single_sound(cache, res::sounds::name, path);
    RES_SOUND_ID_LIST
    #undef CFU_X
}

auto reload_audio(entt::registry& registry) -> void {
    reload_music(registry);
    reload_sound(registry);
}

static auto update_sounds(entt::registry& registry) -> void {
    auto player_view = registry.view<comp::Player, comp::Transform, comp::Position>();
    auto sound_view = registry.view<comp::CfuSound, comp::Position>();
    const float max_distance = 15.0f;
    for (auto [id, transform, p_pos] : player_view.each()) {
        for (auto [id, sound, s_pos] : sound_view.each()) {
            float distance = Vector2Distance(p_pos, s_pos);
            float volume = 1.0f - (distance / max_distance);
            if (volume < 0.0f) volume = 0.0f;
            SetSoundVolume(sound.handle->sound, volume);
        }
    }
}

static auto update_music(entt::registry& registry) -> void {
    auto view = registry.view<comp::CfuMusic>();
    for (auto [id, music] : view.each()) {
        UpdateMusicStream(music.handle->music);
    }
}

auto update_audio(entt::registry& registry) -> void {
    update_music(registry);
    update_sounds(registry);
}

} // namespace cfu::systems
