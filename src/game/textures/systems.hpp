#pragma once

#include <entt/fwd.hpp>
#include <raylib.h>

namespace cfu::systems {

auto setup_texture_cache(entt::registry& registry) -> void;
auto reload_textures(entt::registry& registry) -> void;
auto draw_texrure(entt::registry& registry, Shader shader) -> void;

} // namespace cfu::systems
