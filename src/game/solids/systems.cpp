#include "./systems.hpp"

#include "../data/components.hpp"
#include "../physics/components.hpp"
#include "../raymath.hpp"
#include "../camera/components.hpp"
#include "./components.hpp"

#include <rlgl.h>

namespace cfu::systems {

auto draw_solids(entt::registry& registry) -> void {
    auto d = registry.ctx().get<comp::GameData>();
    auto camera_entity = registry.view<Camera3D, comp::CameraOffset>().back();
    if (camera_entity == entt::null) return;
    const auto camera_offset = registry.get<comp::CameraOffset>(camera_entity);
    const auto camera_position_3d = registry.get<Camera3D>(camera_entity).position - camera_offset.offset;
    const auto camera_position = Vector2(camera_position_3d.x, camera_position_3d.z);

    auto view = registry.view<const cfu::comp::Transform, const comp::Cube, const comp::SolidMaterial>();
    for (const auto [entity, transform, cube, material] : view.each()) {
        const auto position_2d = Vector2(transform.translation.x, transform.translation.z);
        if (Vector2DistanceSqr(camera_position, position_2d) > d.balance.camera.box_culling) continue;

        rlPushMatrix();
        const auto position = transform.translation;
        rlTranslatef(position.x, position.y, position.z);

        auto quaternion = QuaternionFromEuler(transform.rotation.x, transform.rotation.y, transform.rotation.z);
        auto rotation = QuaternionToMatrix(quaternion);
        rlMultMatrixf(reinterpret_cast<float *>(&rotation)); // NOLINT

        const auto size = cube.size * transform.scale;
        rlScalef(size.x, size.y, size.z);

        DrawCubeV({}, Vector3One(), material.color);
        auto wiresColor = ColorToHSV(material.color);
        wiresColor.x += 180.0f;
        DrawCubeWiresV({}, Vector3One(), ColorFromHSV(wiresColor.x, wiresColor.y, wiresColor.z));
        rlPopMatrix();
    }
}

} // namespace cfu::systems
