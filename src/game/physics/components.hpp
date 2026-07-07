#pragma once

#include <box2d/box2d.h>
#include <entt/entt.hpp>
#include <entt_editor.hpp>
#include <raylib.h>

namespace cfu::comp {

struct World {
    b2WorldId id;
};

struct Transform {
    Vector3 translation;
    Vector3 rotation;
    Vector3 scale;
};

template<>
void ComponentEditorWidget<Transform>(entt::registry& reg, entt::registry::entity_type e);

} // namespace cfu::comp
