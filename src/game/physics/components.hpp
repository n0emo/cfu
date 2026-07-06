#pragma once

#include <box2d/box2d.h>
#include <entt/entt.hpp>
#include <imgui_entt_entity_editor.hpp>
#include <raylib.h>

namespace game::components {

struct World {
    b2WorldId id;
};

struct Position {
    Vector2 vec;
};

struct Velocity {
    Vector2 vec;
};

} // namespace game::components

namespace MM {

template<>
void ComponentEditorWidget<game::components::Position>(entt::registry& reg, entt::registry::entity_type e);

template<>
void ComponentEditorWidget<game::components::Velocity>(entt::registry& reg, entt::registry::entity_type e);

} // namespace MM
