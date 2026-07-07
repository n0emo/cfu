#pragma once

#include <entt/entt.hpp>
#include <entt_editor.hpp>

namespace cfu::comp {

struct Hp {
    float max;
    float current;
};

template<>
void ComponentEditorWidget<Hp>(entt::registry& reg, entt::registry::entity_type e);

struct MoveSpeed {
    float value;
};

template<>
void ComponentEditorWidget<MoveSpeed>(entt::registry& reg, entt::registry::entity_type e);

struct MeleeAttack {
    float damage;
    float attack_speed;
    float attack_radius;
};

template<>
void ComponentEditorWidget<MeleeAttack>(entt::registry& reg, entt::registry::entity_type e);

} // namespace cfu::comp
