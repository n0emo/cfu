#pragma once

#include <vector>

#include <raylib.h>
#include <entt/entity/registry.hpp>
#include <gsl/gsl>

namespace cfu::comp {

#define TILE_KIND_LIST                                                                                                 \
    CFU_X(Floor, "floor")                                                                                              \
    CFU_X(Wall, "wall")

enum class TileKind {
    #define CFU_X(name, ...) name,
    TILE_KIND_LIST
    #undef CFU_X
};

auto tile_kind_to_string(TileKind kind) -> gsl::czstring;
auto tile_kind_from_string(std::string_view string) -> TileKind;

#define TILE_ROTATION_LIST                                                                                             \
    CFU_X(None, "none")                                                                                                \
    CFU_X(Deg90, "90")                                                                                                 \
    CFU_X(Deg180, "180")                                                                                               \
    CFU_X(Deg270, "270")

enum class TileRotation {
    #define CFU_X(name, ...) name,
    TILE_ROTATION_LIST
    #undef CFU_X
};

auto tile_rotation_to_string(TileRotation rot) -> gsl::czstring;
auto tile_rotation_from_string(std::string_view str) -> TileRotation;

struct Tile {
    TileKind kind;
    TileRotation rotation;
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
