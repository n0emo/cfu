#include "./systems.hpp"

#include "../raymath.hpp"
#include "../physics/components.hpp"
#include "../combat/components.hpp"
#include "../constants.hpp"
#include "../tilemap/components.hpp"
#include "./components.hpp"

namespace cfu::systems {

auto update_player(entt::registry& registry) -> void {
    const auto dt = GetFrameTime();

    auto view = registry.view<comp::Transform, comp::Grounded, const comp::MoveSpeed, const comp::Player>();
    for (auto [entity, transform, grounded, move_speed] : view.each()) {
        auto input2d = Vector2();
        if (IsKeyDown(KEY_A)) input2d.x -= 1.0f;
        if (IsKeyDown(KEY_D)) input2d.x += 1.0f;
        if (IsKeyDown(KEY_W)) input2d.y -= 1.0f;
        if (IsKeyDown(KEY_S)) input2d.y += 1.0f;

        if (Vector2LengthSqr(input2d) == 0) continue;

        const auto offset_normalized = Vector2Normalize(Vector2(CAMERA_OFFSET.x, CAMERA_OFFSET.y));
        const auto angle = Vector2Angle(Vector2(0.0f, 1.0f), offset_normalized);
        input2d = Vector2Normalize(Vector2Rotate(input2d, angle));
        transform.rotation.y = Vector2Angle(Vector2(0.0f, 1.0f), input2d);
        auto input3d = Vector3(input2d.x, 0.0f, input2d.y);

        transform.translation += input3d * move_speed.value * dt;

        grounded.y = 32.0f;
    }
}

} // namespace cfu::systems
