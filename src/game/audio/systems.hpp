#pragma once

#include <entt/fwd.hpp>
#include <raylib.h>

namespace cfu::systems {

auto setup_audio(entt::registry& registry) -> void;
auto destroy_audio() -> void;

auto reload_audio(entt::registry& registry) -> void;
auto update_audio(entt::registry& registry) -> void;

} // namespace cfu::systems
