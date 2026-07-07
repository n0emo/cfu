#pragma once

#include <raylib.h>
#include <entt/entity/registry.hpp>
#include <entt_editor.hpp>

namespace cfu::comp {

struct BackgroundColor {
    Color color;
};

template<>
void ComponentEditorWidget<BackgroundColor>(entt::registry& reg, entt::registry::entity_type e);

} // namespace cfu::comp
