#include "./systems.hpp"

#include "../physics/components.hpp"
#include "./components.hpp"

namespace cfu::systems {

auto draw_shapes(entt::registry& registry) -> void {
    auto view = registry.view<const comp::Ball, const cfu::comp::Transform, const comp::ShapeColor>();
    for (auto [entity, ball, transform, color] : view.each()) {
        const auto pos = Vector2(transform.translation.x, transform.translation.z);
        DrawCircleV(pos, ball.radius, color.color);
    }
}

} // namespace cfu::systems
