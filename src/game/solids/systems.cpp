#include "./systems.hpp"

#include "../raymath.hpp"
#include "../physics/components.hpp"
#include "./components.hpp"

#include <rlgl.h>

namespace cfu::systems {

auto draw_solids(entt::registry& registry) -> void {
    auto view = registry.view<const cfu::comp::Transform, const comp::Cube, const comp::SolidMaterial>();

    for (const auto [entity, transform, cube, material] : view.each()) {
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
