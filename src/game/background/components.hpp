#pragma once

#include <raylib.h>
#include <entt/entt.hpp>
#include <entt_editor.hpp>

namespace cfu::comp {

struct BackgroundColor {
    Color color;
};

template<>
void ComponentEditorWidget<BackgroundColor>(entt::registry& reg, entt::registry::entity_type e);

} // namespace cfu::comp
