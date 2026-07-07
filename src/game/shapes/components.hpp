#pragma once

#include <entt/entity/registry.hpp>
#include <entt_editor.hpp>
#include <raylib.h>

namespace cfu::comp {

struct ShapeColor {
    Color color;
};

template<>
void ComponentEditorWidget<ShapeColor>(entt::registry& reg, entt::registry::entity_type e);

struct Ball {
    float radius;
};

template<>
void ComponentEditorWidget<Ball>(entt::registry& reg, entt::registry::entity_type e);

} // namespace cfu::comp
