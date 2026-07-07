#pragma once

#include <vector>

#include <raylib.h>
#include <entt/entity/registry.hpp>
#include <gsl/gsl>

namespace cfu::comp {

enum class TileKind {
    Floor,
    Wall,
    // Staircase,
};

struct Tile {
    TileKind kind;
};

struct TileMap {
    std::size_t tiles_x;
    std::size_t tiles_y;
};

struct HeightMap {
    std::size_t width;
    std::size_t height;
    std::vector<float> map;

    static auto create(std::size_t width, std::size_t height) -> HeightMap;

    auto set_height_for_tile(gsl::index tile_x, gsl::index tile_y, float height) -> void;
    auto set_height_for_region(Rectangle region, float height) -> void;
    [[nodiscard]] auto get_height(float x, float y) const -> float;
};

struct Grounded {
    float y;
};

auto create_map(entt::registry& registry, entt::entity entity, std::size_t tiles_x, std::size_t tiles_y) -> void;
auto create_tile(entt::registry& registry, entt::entity entity, TileKind kind, gsl::index x, gsl::index y, gsl::index z)
    -> void;

} // namespace cfu::comp
