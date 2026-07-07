#pragma once

#include <entt/entity/registry.hpp>

namespace cfu::systems {

auto create_camera(entt::registry& registry, entt::entity entity) -> void;
auto update_camera(entt::registry& registry) -> void;
auto begin_camera_mode(entt::registry& registry) -> void;
auto end_camera_mode(entt::registry& registry) -> void;

} // namespace cfu::systems
