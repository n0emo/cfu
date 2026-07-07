#include "./systems.hpp"

#include "../constants.hpp"
#include "../physics/components.hpp"
#include "../raymath.hpp"
#include "./components.hpp"

#include <rlgl.h>

namespace cfu::systems {

auto draw_solids(entt::registry& registry) -> void {
    auto view = registry.view<const cfu::comp::Transform, const comp::Cube, const comp::SolidMaterial>();

    auto camera_entity = registry.view<Camera3D>().back();
    if (camera_entity == entt::null) return;
    const auto camera_position_3d = registry.get<Camera3D>(camera_entity).position - CAMERA_OFFSET;
    const auto camera_position = Vector2(camera_position_3d.x, camera_position_3d.z);

    for (const auto [entity, transform, cube, material] : view.each()) {
        const auto position_2d = Vector2(transform.translation.x, transform.translation.z);
        if (Vector2DistanceSqr(camera_position, position_2d) > BOX_CULLING_RADIUS) continue;

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
