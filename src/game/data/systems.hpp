#pragma once

#include <entt/fwd.hpp>

namespace cfu::systems {

auto save_game_data_to_disk(entt::registry& registry) -> void;
auto load_game_data_from_disk(entt::registry& registry) -> void;
auto apply_game_data_to_game(entt::registry& registry) -> void;
auto apply_game_camera_data_to_game(entt::registry& registry) -> void;
auto apply_game_player_data_to_game(entt::registry& registry) -> void;

} // namespace cfu::systems
