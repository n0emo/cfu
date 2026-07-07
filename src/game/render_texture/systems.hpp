#pragma once

#include <entt/entity/registry.hpp>

namespace cfu::systems {

auto setup_main_render_texture(entt::registry& registry) -> void;
auto destroy_main_render_texture(entt::registry& registry) -> void;
auto begin_main_render_texture(entt::registry& registry) -> void;
auto end_main_render_texture(entt::registry& registry) -> void;

} // namespace cfu::systems
