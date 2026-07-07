#pragma once

#include <raylib.h>
#include <entt/entity/registry.hpp>
#include <entt_editor.hpp>

namespace cfu::comp {

struct SolidMaterial {
    Color color;
};

template<>
void ComponentEditorWidget<SolidMaterial>(entt::registry& reg, entt::registry::entity_type e);

struct Cube {
    Vector3 size;
};

template<>
void ComponentEditorWidget<cfu::comp::Cube>(entt::registry& reg, entt::registry::entity_type e);

} // namespace cfu::comp
