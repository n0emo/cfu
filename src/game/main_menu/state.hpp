#pragma once

#include <entt/entity/registry.hpp>

namespace cfu {

class MainMenuState {
  public:
    auto on_enter(entt::registry& registry) -> void;
    auto on_exit(entt::registry& registry) -> void;
    auto update(entt::registry& registry) -> void;
    auto draw(entt::registry& registry) -> void;
};

} // namespace cfu
