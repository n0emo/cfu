#pragma once

#include <entt/entity/registry.hpp>

namespace cfu::systems {

auto setup_dev(entt::registry& registry) -> void;
auto draw_dev(entt::registry& registry) -> void;
auto update_dev(entt::registry& registry) -> void;

auto draw_dev_panel(entt::registry& registry) -> void;

auto setup_entt_editor(entt::registry& registry) -> void;
auto draw_entt_editor(entt::registry& registry) -> void;

auto setup_tilemap_editor(entt::registry& registry) -> void;
auto draw_tilemap_editor(entt::registry& registry) -> void;

auto setup_data_editor(entt::registry& registry) -> void;
auto draw_data_editor(entt::registry& registry) -> void;

} // namespace cfu::systems
