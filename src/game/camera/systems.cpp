#include "./systems.hpp"

#include <raylib.h>

#include "../constants.hpp"
#include "../player/components.hpp"
#include "../physics/components.hpp"
#include "../raymath.hpp"

namespace cfu::systems {

auto create_camera(entt::registry& registry, entt::entity entity) -> void {
    registry.emplace<Camera3D>(entity);
}

auto update_camera(entt::registry& registry) -> void {
    const auto player = registry.view<const cfu::comp::Transform, const comp::Player>().back();
    if (player == entt::null) return;

    auto entity = registry.view<Camera3D>().back();
    if (entity == entt::null) return;

    const auto player_position = registry.get<const cfu::comp::Transform>(player).translation;
    auto& camera = registry.get<Camera3D>(entity);
    camera.target = Vector3Lerp(camera.target, player_position, GetFrameTime() * CAMERA_LERP);
    camera.position = camera.target + CAMERA_OFFSET;
    camera.up = CAMERA_UP;
    camera.fovy = CAMERA_FOVY;
    camera.projection = CAMERA_PROJECTION;
}

auto begin_camera_mode(entt::registry& registry) -> void {
    auto entity = registry.view<const Camera3D>().back();
    if (entity != entt::null) {
        auto camera = registry.get<const Camera3D>(entity);
        BeginMode3D(camera);
    }
}

auto end_camera_mode(entt::registry& registry) -> void {
    auto entity = registry.view<const Camera3D>().back();
    if (entity != entt::null) {
        EndMode3D();
    }
}

} // namespace cfu::systems
