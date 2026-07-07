#include "./components.hpp"

#include "../physics/components.hpp"
#include "../solids/components.hpp"
#include "../constants.hpp"
#include "../raymath.hpp"

namespace cfu::comp {

auto HeightMap::create(std::size_t tiles_x, std::size_t tiles_y) -> HeightMap {
    const auto width = tiles_x * TILE_SIZE;
    const auto height = tiles_y * TILE_SIZE;
    return HeightMap {
        .width = width,
        .height = height,
        .map = std::vector<float>(width * height),
    };
}

auto HeightMap::set_height_for_tile(gsl::index tile_x, gsl::index tile_y, float height) -> void {
    const auto size = float(TILE_SIZE);
    const auto region = Rectangle {
        .x = float(tile_x) * size,
        .y = float(tile_y) * size,
        .width = size,
        .height = size,
    };
    set_height_for_region(region, height);
}

auto HeightMap::set_height_for_region(Rectangle region, float height) -> void {
    for (auto x = gsl::index(region.x); x < gsl::index(region.x + region.width); x++) {
        for (auto y = gsl::index(region.y); y < gsl::index(region.y + region.height); y++) {
            if (x < 0 || x >= gsl::index(this->width)) continue;
            if (y < 0 || y >= gsl::index(this->height)) continue;
            map[y * width + x] = height;
        }
    }
}

auto HeightMap::get_height(float x, float y) const -> float {
    auto x_index = gsl::index(x);
    auto y_index = gsl::index(y);
    if (x_index < 0 || x_index >= gsl::index(this->width) || y_index < 0 || y_index >= gsl::index(this->height)) {
        return 0.0f;
    }

    return map[y_index * width + x_index];
}

auto create_map(entt::registry& registry, entt::entity entity, std::size_t tiles_x, std::size_t tiles_y) -> void {
    registry.emplace<TileMap>(entity, tiles_x, tiles_y);
    registry.emplace<HeightMap>(entity, HeightMap::create(tiles_x, tiles_y));
}

auto create_tile(entt::registry& registry, entt::entity entity, TileKind kind, gsl::index x, gsl::index y, gsl::index z)
    -> void {
    registry.emplace<Tile>(entity, kind);

    auto cube_size = Vector3 {};
    auto cube_color = Color {};
    auto height = float {};
    switch (kind) {
        case TileKind::Floor:
            cube_size = Vector3(1.0f, 0.5f, 1.0f) * TILE_SIZE;
            cube_color = MAROON;
            height = TILE_SIZE * 0.5f;
            break;
        case TileKind::Wall:
            cube_size = Vector3One() * TILE_SIZE;
            cube_color = DARKGRAY;
            height = TILE_SIZE;
            break;
    };

    registry.emplace<Transform>(
        entity,
        Transform {
            .translation =
                Vector3(float(x) * TILE_SIZE, float(y) * TILE_SIZE + height - TILE_SIZE * 0.5f, float(z) * TILE_SIZE),
            .rotation = Vector3Zero(),
            .scale = Vector3One(),
        }
    );

    registry.emplace<Cube>(entity, cube_size);
    registry.emplace<SolidMaterial>(entity, cube_color);

    auto height_map_entity = registry.view<HeightMap>().back();
    if (height_map_entity != entt::null) {
        auto& height_map = registry.get<HeightMap>(height_map_entity);
        height_map.set_height_for_tile(x, z, float(y) * TILE_SIZE + height);
    }
}

} // namespace cfu::comp
