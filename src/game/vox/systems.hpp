#pragma once

#include <entt/fwd.hpp>

namespace cfu::systems {

auto setup_vox_model_cache(entt::registry& registry) -> void;
auto reload_voxel_models(entt::registry& registry) -> void;
auto draw_voxel_models(entt::registry& registry) -> void;

} // namespace cfu::systems
