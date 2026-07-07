#pragma once

#include <entt/entity/registry.hpp>

namespace cfu {

struct Game {
    entt::registry registry;

    static auto init(Game& game) -> void;
    static auto deinit(Game& game) -> void;

    auto frame(this Game& self) -> void;
    auto running(this const Game& self) -> bool;
};

} // namespace cfu
