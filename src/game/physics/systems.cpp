#include "./systems.hpp"

#include "../constants.hpp"
#include "./components.hpp"

namespace game::systems {

auto setup_physics(entt::registry& registry) -> void {
    auto def = b2DefaultWorldDef();
    def.gravity = {.x = 0.0f, .y = 50.0f};
    auto world = b2CreateWorld(&def);
    registry.ctx().insert_or_assign(components::World {.id = world});
}

auto update_physics(entt::registry& registry) -> void {
    auto& world = registry.ctx().get<components::World>();
    b2World_Step(world.id, GetFrameTime(), B2_STEPS);
}

} // namespace game::systems
