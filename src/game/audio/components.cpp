#include "./components.hpp"
#include "entt/entity/fwd.hpp"
#include "physics/components.hpp"

namespace cfu::comp {

auto create_sound(entt::registry& registry, entt::entity entity) -> void {
    registry.emplace<CfuSound>(entity);
    registry.emplace<comp::Position>(entity, 0.0f, 0.0f);
}
} // namespace cfu::comp
