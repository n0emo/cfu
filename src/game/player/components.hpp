#pragma once

#include <entt/entity/registry.hpp>

namespace cfu::comp {

struct Player {};

auto create_player(entt::registry& registry, entt::entity entity) -> void;

} // namespace cfu::comp
