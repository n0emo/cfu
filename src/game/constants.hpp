#pragma once

#include <raylib.h>
#include <array>

namespace cfu {

struct PlayerStatsDescriptor {
    float max_hp = 0;
    float move_speed = 0;
    float damage = 0;
    float attack_speed = 0;
    float attack_radius = 0;
};

constexpr auto WINDOW_WIDTH = 720;
constexpr auto WINDOW_HEIGHT = 720;

constexpr auto B2_STEPS = 4;

constexpr auto CAMERA_LERP = 15.0f;
constexpr auto CAMERA_OFFSET = Vector3(100.0f, 100.0f, 100.0f);
constexpr auto CAMERA_UP = Vector3(0.0f, 1.0f, 0.0f);
constexpr auto CAMERA_FOVY = 120.0f;
constexpr auto CAMERA_PROJECTION = CAMERA_ORTHOGRAPHIC;

constexpr auto PLAYER_STATS_DESCS = std::array<PlayerStatsDescriptor, 3> {
    PlayerStatsDescriptor {
        .max_hp = 10.0f,
        .move_speed = 100.0f,
        .damage = 1.0f,
        .attack_speed = 1.0f,
        .attack_radius = 20.0f,
    },

    PlayerStatsDescriptor {
        .max_hp = 20.0f,
        .move_speed = 120.0f,
        .damage = 1.0f,
        .attack_speed = 1.0f,
        .attack_radius = 20.0f,
    },

    PlayerStatsDescriptor {
        .max_hp = 30.0f,
        .move_speed = 140.0f,
        .damage = 1.0f,
        .attack_speed = 1.0f,
        .attack_radius = 20.0f,
    },
};

} // namespace cfu
