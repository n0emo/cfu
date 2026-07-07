#pragma once

#include <entt/entity/registry.hpp>
#include <raylib.h>

namespace cfu::dev {

auto mouse_ray(entt::registry& registry) -> Ray;

}
