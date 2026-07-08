#include "./systems.hpp"

#include <raylib.h>

#include "../player/components.hpp"
#include "../physics/components.hpp"
#include "../raymath.hpp"
#include "../data/components.hpp"
#include "./components.hpp"

namespace cfu::systems {

auto create_camera(entt::registry& registry, entt::entity entity) -> void {
    const auto& d = registry.ctx().get<comp::GameData>();

    registry.emplace<Camera3D>(
        entity,
        Camera3D {
            .position = d.balance.camera.offset,
            .target = Vector3 {},
            .up = d.balance.camera.up,
            .fovy = d.balance.camera.fovy,
            .projection = CAMERA_ORTHOGRAPHIC,
        }
    );
    registry.emplace<comp::CameraLerp>(entity, d.balance.camera.lerp);
    registry.emplace<comp::CameraOffset>(entity, d.balance.camera.offset);
}

auto update_camera(entt::registry& registry) -> void {
    update_camera_target(registry);
    update_camera_position(registry);
}

auto update_camera_target(entt::registry& registry) -> void {
    const auto player = registry.view<const cfu::comp::Transform, const comp::Player>().back();
    if (player == entt::null) return;
    const auto player_position = registry.get<const cfu::comp::Transform>(player).translation;

    auto view = registry.view<Camera3D, comp::CameraLerp>();
    for (auto [entity, camera, lerp] : view.each()) {
        camera.target = Vector3Lerp(camera.target, player_position, GetFrameTime() * lerp.amount);
    }
}

auto update_camera_position(entt::registry& registry) -> void {
    auto view = registry.view<Camera3D, comp::CameraOffset>();
    for (auto [entity, camera, offset] : view.each()) {
        camera.position = camera.target + offset.offset;
    }
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
